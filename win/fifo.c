/*******************************************************************************
 * MODULE:	FIFO.C
 *
 * PURPOSE:	Utilities to use POSIX.1 FIFOs to provide bidirectional
 *		communication between a server process and its fork()ed child
 *		processes
 *
 * FUNCTIONS DECLARED
 *	EXTERNAL:	<required>
 *	LOCAL:		<optional>
 *
 * USE:
 *
 *	The data passed between processes is in the following format when
 *	it is written to/read from any of the FIFOs:
 *	<sender process ID string><blank><command num string><blank><data len>
 *		<blank><data>
 *
 * PROTOCOL:
 *
 *	IN SERVER PROCESS, BEFORE CALLING fork():
 *
 *	shared_fifodata_tt *parent2child;
 *	char            parent_pidstr[INTLEN]; --String representation of the
 *					parent (server) process ID.
 *	pid_t           pid; --Process ID returned from fork()
 *
 *	sprintf (parent_pidstr, "%d", (int) getpid ());
 *	parent2child = init_parent2child_fifo (parent_pidstr);
 *	if ((pid = fork ()) == -1)
 *	{
 *		perror ("Erron in fork()");
 *		exit (-1);
 *	}
 *	else if (pid == 0)
 *		client (parent2child); --Execute client (child) code.
 *	else
 *		server (parent2child); --Execute server (parent) code.
 *
 *
 *	IN THE CLIENT CODE:
 *	void            client (shared_fifodata_tt * parent2child)
 *	{
 *		char            child_pidstr[INTLEN];
 *		char	       *message;
 *		reply_fifodata_tt *child2parent = NULL;
 *		const char     *reply_ptr;
 *		size_t          reply_len;
 *		server_command_tt command; -- Vaule from an enumerated type.
 *
 *		sprintf (child_pidstr, "%d", getpid ());
 *		connect_to_parent (parent2child, child_pidstr, &child2parent);
 *
 *		message = malloc (shared_fifo_bufsiz(parent2child));
 *		sprintf (message, "sub_client's message.");
 *		send2parent (parent2child, SRV_ECHO, message);
 *		receive_fm_parent (child2parent, &reply_len);
 *		reply_ptr = reply_fifo_data (child2parent);
 *
 *		... continue sending messages and getting replies ...
 *		--CRITICAL only let ONE client send the shutdown message to
 *		--the server; call wait() once for each spawned subchild.
 *		sprintf (message, "");
 *		send2parent (parent2child, SRV_SHUTDOWN, message);
 *		destroy_child2parent (child2parent);
 *		free (child2parent);
 *		free (message);
 *		exit (0);
 *	}
 *
 *
 *	IN THE SERVER CODE
 *	void            server (shared_fifodata_tt * parent2child)
 *	char            child_pidstr[INTLEN];
 *	server_command_tt command;
 *	const char     *dataptr; -- Points at data in the parent2child
 *				 -- internal structures; therefore const.
 *	char           *echobuf; -- Make a local copy of the data before
 *			         -- echoing it back to client, during the
 *				 -- SRV_ECHO command  (Dont pass a ptr into
 *				 -- the parent2child internal structures).
 *	size_t          datalen;
 *
 *	open_parent2child_fifo (parent2child, O_RDONLY);
 *	echobuf = malloc (shared_fifo_bufsiz (parent2child));
 *
 *	do
 *	{ -- Process commands until you get an SRV_SHUTDOWN command.
 *		command = receive_fm_child (parent2child, child_pidstr,
 *						&datalen);
 *		dataptr = shared_fifo_data (parent2child);
 *		switch (command)
 *		{
 *			-- The SRV_CONNECT message is automatically sent by the
 *			-- client process when it calls connect_to_parent()
 *			case SRV_CONNECT:
 *				parent_open_reply_fifo (parent2child,
 *								child_pidstr);
 *				break;
 *
 *			-- SRV_ECHO is a test message you can send.  You should
 *			-- get your message echoed right back to you.
 *			case SRV_ECHO:
 *				strcpy (echobuf, dataptr);
 *				send2child (parent2child, child_pidstr,
 *							command, echobuf);
 *				break;
 *
 *			... any other commands you add here are handled here ...
 *
 *			default:
 *				printf ("Parent received %d byte message from "
 *					"%s.  Command %d, message:\n\t\"%s\"\n",
 *					 datalen, child_pidstr, command,
 *					 dataptr);
 *		} -- end switch
 *	} while (command != SRV_SHUTDOWN);
 *	destroy_fifos (parent2child);
 *	free (echobuf);
 *
 *
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 * $Author: franklin $
 *******************************************************************************
 * $Date: 1994/08/22 00:22:28 $
 * $State: Exp $
 * $Locker: franklin $
 * $Source: /all/franklin/thesis/descartes/win/RCS/fifo.c,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: fifo.c,v $
 * Revision 1.37  1994/08/22  00:22:28  franklin
 * Add the server processes PID to the name of the FIFO file.
 * Indent.
 *
 * Revision 1.36  1994/08/12  15:56:28  franklin
 * Try to recover from read() fetching a NULL character
 * from a FIFO, even though nobody should have put it in
 * the stream.
 *
 * Revision 1.35  1994/08/12  05:01:54  franklin
 * On the HP, read() will claim to have read a full message
 * header, even though buf[] contains no new data!  Try to
 * recover when this happens.
 *
 * Revision 1.34  1994/08/12  04:31:23  franklin
 * WARNING:
 * Version 1.33 of fifo.c IS ACTUALLY A COPY OF A PREVIOUS
 * VERSION!  This is the correct file.  Here are the changes:
 * read() and write() operations can fail when the timeout() SIGALRM
 * message is received.  Made read/write operations tolerant of this (they
 * can abort with errno == EINTR.
 *
 * Revision 1.32  1994/08/10  19:08:38  franklin
 * 1. Abort if sscanf() fails to translate a FIFO message header.
 * 2. Move the SIGPIPE handler to safe.c, and make it reentrant.
 * 3. Move the #definition of MSG_HEADER_SIZ to fifo.h, so that safe.c can
 *    see it.  The timeout() signal handler has to build a message header
 *    manually, because send2parent() and functions that it calls, are not
 *    reentrant.
 * 4. Make multiple attempts to read a message header.
 *
 * Revision 1.31  1994/08/09  01:08:16  franklin
 * Added utility function commandval2string()
 *
 * Revision 1.30  1994/08/06  22:34:35  franklin
 * Remove several printf()s that were really slowing down performance.
 *
 * Revision 1.29  1994/08/06  18:48:00  franklin
 * Add "const" qualifier to parameters that are not modified by
 * the FIFO utilities
 *
 * Revision 1.28  1994/08/05  18:47:57  franklin
 * Dont quit just because you called mkfifo() for a FIFO file
 * that already existed.
 *
 * Revision 1.27  1994/08/05  17:06:04  franklin
 * Remove "static" keyword from functions parent_open_reply_fifo()
 * and connect_to_parent.
 * Remove dataptr parameter from receive_fm_child()
 * and receive_fm_parent().
 * Make corrections to PROTOCOL comments.
 *
 * Revision 1.26  1994/08/05  02:33:56  franklin
 * closing parend.
 *
 * Revision 1.25  1994/08/05  02:32:45  franklin
 * and semicolon.
 *
 * Revision 1.24  1994/08/05  02:31:43  franklin
 * Add missing closing brace.
 *
 * Revision 1.23  1994/08/05  02:27:32  franklin
 * 1. Identify static and non-static functions.
 * 2. Fix error in the "PROTOCOL" comments.
 * 3. Add utilities for fetching data from a FIFO struct pointer:
 *    reply_fifo_bufsiz(), reply_fifo_data(),
 *    shared_fifo_bufsiz(), shared_fifo_data()
 *
 * Revision 1.22  1994/08/05  00:14:53  franklin
 * Move typedefs, #defines, and prototypes required to use this module,
 * in to fifo.h.
 *
 * Revision 1.21  1994/08/04  17:58:17  franklin
 * Add #includes for cchk_missing_<standard include>.h in order
 * to get prototypes that CodeCheck doesnt think are there.
 *
 * Revision 1.20  1994/08/04  16:44:33  franklin
 * Moved #include ctype.h before string.h and stdio.h to shut up CodeCheck
 * message: Prefix "to" was used 1 times before this #include.
 *
 * Revision 1.19  1994/08/01  23:38:30  franklin
 * The suffix "_t" is reserved by POSIX.1
 *
 * Revision 1.18  1994/08/01  18:52:19  franklin
 * This version successfully coordinates server shutdown with the child
 * and several subchild processes.
 *
 * Revision 1.17  1994/08/01  18:08:42  franklin
 * 1.  I tried to get fancy with the hashing algorithm, and all
 *    I ended up doing is breaking how the hastable functions
 *    handled collisions.  Use the integer version of the PID as
 *    the key field, and let the hash functions do the rest.
 * 2. Deleted a semicolon after while statement, which resulted in
 *    an infinite loop ==> "while (subchild_cnt > 0);"
 *
 * Revision 1.16  1994/07/31  23:51:35  franklin
 * Try waiting (wait(0)) for each sub-subprocess to die before sending
 * the shutdown message to the server.  I do not know if this works or
 * not, because I goobered up how the hash table handles collisions.
 *
 * Revision 1.15  1994/07/31  23:17:23  franklin
 * First attempt to syncronize server shutdown with multiple child
 * processes.  The server dies too soon.
 *
 * Revision 1.14  1994/07/31  22:00:57  franklin
 * Free of Purify(tm) errors.
 *
 * Revision 1.13  1994/07/30  19:02:37  franklin
 * Let receive_fm_child() share read_header() and read_msgtext() with
 * receive_rm_parent.
 *
 * Revision 1.12  1994/07/30  17:36:23  franklin
 * indent
 *
 * Revision 1.11  1994/07/30  17:29:57  franklin
 * The server DOES send replies back to the child that requested the reply.
 *
 * Revision 1.8  1994/07/28  04:49:10  franklin
 * Fixed two BIG problems
 * 1. I was setting the wrong bits in the call to open().  DONT set the same
 *    flags you used when you called mkfifo().  mkfifo() creates an object
 *    in the file sytem.  mkfifo() expects read/write permission bit settings
 *    a la chmod(1)(2).
 * 2. Allocate enough room in header_string[] for 3 integers and their delimite
 *    not just 1 integer.
 *
 * Revision 1.7  1994/07/27  20:39:30  franklin
 * Version ftpd to ASU to try on Solaris 2.3.  BAD NEWS: The fifo works FINE
 * on HP-UX 9, seems to work OK on Solaris 2.3, but HANGS DEAD on SunOS 4.1.3.
 * Even worse, it HANGS OBJECTCENTER when I try to debug it!
 *
 * Revision 1.6  1994/07/25  21:36:02  franklin
 * I tried to use variable message header lengths.  It did not work.
 *
 * Revision 1.5  1994/07/25  00:11:00  franklin
 * Integrage hash table functions.
 *
 * Revision 1.4  1994/07/23  22:32:51  franklin
 * indent
 *
 * Revision 1.3  1994/07/23  21:47:42  franklin
 * First version that will pass data from the child to the parent.
 *
 * Revision 1.1  1994/07/23  04:24:59  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif

static char    *rcsid = "$Id: fifo.c,v 1.37 1994/08/22 00:22:28 franklin Exp franklin $";


#include <stdlib.h>
#include "cchk_missing_stdlib.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>		       /* perror() */
#include <unistd.h>
#include "cchk_missing_unistd.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <signal.h>		       /* signal() */
#include "cchk_missing_signal.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */

#include <fcntl.h>		       /* open() */
#include <sys/types.h>		       /* mkfifo() */
#include <sys/stat.h>		       /* mkfifo() */
#include <errno.h>		       /* Operating system error condition definitions. */

#include "semops.h"		       /* To create semaphore for the child process. */
#include "some_utils.h"		       /* util_abort() and growstr() utilities. */
#include "hash.h"		       /* Hash table to match process ID to a FIFO. */
#include "safe.h"		       /* sigpipe_handler() */
#include "fifo.h"

static const    HASHTABLESIZ = 23;     /* There is nothing special about this value.  Use what works for you.  Increase the value
				        * if performance drags down.  If that doesnt work, then change hash algorithm.  NOTE:
				        * Prime numbers seem to make the best hash table sizes. */

/*
 * FIFO_PRIVILEGES is a constant that specifies read/write privs on the FIFOs
 * Set owner-read, and owner-writee access on the FIFOs.  Note: Solaris 2
 * does not have symbolic names for these privileges.
 */

#ifdef S_IRUSR
static const mode_t FIFO_PRIVILEGES = S_IRUSR | S_IWUSR;

#else
static const mode_t FIFO_PRIVILEGES = 0600;

#endif

/*******************************************************************************
 * FUNCTION:	DUMP_SHAREDFIFO_STRUCT
 ******************************************************************************/
void            dump_sharedfifo_struct (FILE * fp, shared_fifodata_tt * parent2child)
{
	fprintf (fp, "fd\t\t= %d\n", parent2child->fd);
	fflush (fp);
	fprintf (fp, "bufsiz\t= %d\n", parent2child->bufsiz);
	fflush (fp);
	fprintf (fp, "pathname\t= \"%s\"\n", parent2child->pathname ? parent2child->pathname : "(Null)");
	fflush (fp);
	fprintf (fp, "semaphore\t= %d\n", parent2child->semaphore);
	fflush (fp);
	fprintf (fp, "fromstr\t= \"%s\"\n", parent2child->fromstr ? parent2child->fromstr : "(Null)");
	fflush (fp);
	fprintf (fp, "data_gbuf\t= \"%s\"\n", parent2child->data_gbuf ? growbuf_str (parent2child->data_gbuf) : "(Null)");
	fflush (fp);
	fprintf (fp, "reply_htab\t= 0x%X\n", parent2child->reply_htab);
	fflush (fp);
}

/*******************************************************************************
 * FUNCTION:	DUMP_REPLYFIFO_STRUCT
 ******************************************************************************/
void            dump_replyfifo_struct (FILE * fp, reply_fifodata_tt * child2parent)
{
	fprintf (fp, "pid\t= %d\n", child2parent->pid);
	fflush (fp);
	fprintf (fp, "childstr\t= \"%s\"\n", child2parent->childstr ? child2parent->childstr : "(Null)");
	fflush (fp);
	fprintf (fp, "fd\t\t= %d\n", child2parent->fd);
	fflush (fp);
	fprintf (fp, "bufsiz\t= %d\n", child2parent->bufsiz);
	fflush (fp);
	fprintf (fp, "pathname\t= \"%s\"\n", child2parent->pathname ? child2parent->pathname : "(Null)");
	fflush (fp);
	fprintf (fp, "data_gbuf\t= \"%s\"\n", child2parent->data_gbuf ? growbuf_str (child2parent->data_gbuf) : "(Null)");
	fflush (fp);
}

/*******************************************************************************
 * FUNCTION:	CREATE_NEW_FIFONAME
 *
 * PURPOSE:	Create a pathname suitable for use by mkfifo(), based on the
 *		process ID of the process that will read from the FIFO, and
 *		the process ID of the server process. ex:
 *		"prefix.server_pidstr.pidstr"
 ******************************************************************************/
static char    *create_new_fifoname (const shared_fifodata_tt * parent2child, const char *pidstr)
{

/*
 * Allocate enough room for the name of the temporary directory (P_tmpdir),
 * the prefix string, a period, the length of the string representation of
 * the server process ID, another period, the string representation of the
 * callers process ID, and the NULL terminator. (the caller may be the
 * server, but does not have to be.
 */
	const char     *prefix = "fifo";
	char           *name = malloc (strlen (P_tmpdir) + strlen (prefix) + 1 + INTLEN + 1 + INTLEN + 1);

	if (name == NULL)
	{
		util_abort (__LINE__, __FILE__, "malloc() failed.\n");
	}
	sprintf (name, "%s%s.%s.%s", P_tmpdir, prefix, parent2child->server_pidstr, pidstr);

	return (name);
}

/*******************************************************************************
 * FUNCTION: CREATE_FIFO
 *	Used to create either the parent2child FIFO, or the reply FIFOs.
 *	NOTE: the FIFO is not actually OPENED until AFTER a fork() operation.
 *	This means that parent and child processes will have different file
 *	descriptors for the fifo, and often open the FIFO in different modes,
 *	i.e. The parent may open for read/write, and the child open for
 *	write-only.  Opening for read/write prevents signals every time a
 *	child process close()es the FIFO -- useful when multiple children
 *	are writing to the FIFO.
 *
 *	NOTE: mkfifo() sets plain-jane "read write execute" type permissions.
 *	      DO NOT SET THESE PERMISSIONS in the subsequent call to open();
 *	      Give open() flags like readonly readwrite writeonly and
 *	      open for non-blocking IO.
 ******************************************************************************/
static void     create_fifo (const char *pathname)
{
	if (mkfifo (pathname, FIFO_PRIVILEGES) == -1)
	{
		if (errno != EEXIST)   /* It is OK if the FIFO file object already exists. */
		{
			perror ("mkfifo()");
			util_abort (__LINE__, __FILE__, "mkfifo() failed to create FIFO %s.\n", *pathname);
		}
	}
}

/*******************************************************************************
 * FUNCTION:	INIT_PARENT2CHILD_FIFO
 *	NOTE: It is CRITICAL that you call this function BEFORE you fork()
 *	      off your client sub-processes.
 ******************************************************************************/
shared_fifodata_tt *init_parent2child_fifo (const char *pidstr)
{
	static int      sigpipe_handler_registered = 0;	/* Set to nonzero after the SIGPIPE signal handler has been registered. */
	shared_fifodata_tt *parent2child = (shared_fifodata_tt *) calloc (1, sizeof (shared_fifodata_tt));

	if (!sigpipe_handler_registered)
	{
		sigpipe_handler_registered = (!0);
		signal (SIGPIPE, sigpipe_handler);
	}

	if (parent2child == NULL)
	{
		util_abort (__LINE__, __FILE__, "calloc() failed.\n");
	}
	parent2child->semaphore = sem_create ();
	strcpy (parent2child->server_pidstr, pidstr);
	parent2child->pathname = create_new_fifoname (parent2child, pidstr);
	create_fifo (parent2child->pathname);
	parent2child->bufsiz = -1;	/* Not known until the FIFO is opened.  Set to an invalid value for now. */
	parent2child->reply_htab = hash_new (HASHTABLESIZ);
	parent2child->data_gbuf = NULL;

	return (parent2child);
}

/*******************************************************************************
 * FUNCTION:	OPEN_FIFO
 *	Opens a FIFO and determines the buffer size.
 *
 * NOTE:
 *	Must be called AFTER fork(), because a process will block until there
 *	is another process on the other end of this FIFO.
 ******************************************************************************/
static int      open_fifo (const char *pathname, mode_t flags, int *bufsizptr)
{
	int             fd = -1;       /* The CenterLine clcc compiler does not know that util_abort() halts execution, therefore
				        * it generates a warning that "fd is possibly referenced before set."  I initialized fd
				        * to suppress that warning message. */

	if ((fd = open (pathname, flags)) == -1)
	{
		perror ("open() in open_fifo()");
		util_abort (__LINE__, __FILE__, "open(%s, 0%03o (octal)) failed to open a FIFO."
			    " fd == %d; my PID == %d\n",
			    pathname, flags, fd, getpid ());
	}
	*bufsizptr = fpathconf (fd, _PC_PIPE_BUF);	/* Get the buffer size for this particular FIFO. */

	fflush (stdout);

	if (*bufsizptr == -1)
	{
		perror ("fpathconf()");
		util_abort (__LINE__, __FILE__, "pathconf() failed to return the buffer size for FIFO %s.\n"
			    "parent2child->bufsiz == %d\n", *bufsizptr, pathname);
	}
	return (fd);
}

/*******************************************************************************
 * FUNCTION:	OPEN_PARENT2CHILD_FIFO
 *	Both the parent (server) process, and all child processes will call
 *	this function.  Parent will pass flags to open for read only(O_RDONLY),
 * 	and child processes will open for write-only (O_WRONLY).
 *
 *	NOTE: In the end-user code, only the SERVER process will directly call
 *	      this function.  The end-user CLIENT code calls this function
 *	      indirectly, by calling connect_to_parent().
 ******************************************************************************/
void            open_parent2child_fifo (shared_fifodata_tt * parent2child, mode_t flags)
{
	parent2child->fd = open_fifo (parent2child->pathname, flags, &parent2child->bufsiz);
}

/*******************************************************************************
 * FUNCTION:	PARENT_OPEN_REPLY_FIFO
 *	Called from the server (parent) process, when the server process
 *	receives a SRV_CONNECT message.
 ******************************************************************************/
void            parent_open_reply_fifo (shared_fifodata_tt * parent2child, const char *child_pidstr)
{
	reply_fifodata_tt *child2parent = (reply_fifodata_tt *) calloc (1, sizeof (reply_fifodata_tt));

	if (child2parent == NULL)
	{
		util_abort (__LINE__, __FILE__, "calloc() failed.\n");
	}
	child2parent->pid = atoi (child_pidstr);

/* Check to see if it has already been created and added to the hash table. */
	if (!hash_find (parent2child->reply_htab, child2parent->pid))
	{
	/* make fifo, initialize fields, open fifo */
		child2parent->pathname = create_new_fifoname (parent2child, child_pidstr);
		child2parent->fd = open_fifo (child2parent->pathname, O_WRONLY, &child2parent->bufsiz);

		hash_add (parent2child->reply_htab, child2parent);
	}
	else
	{
		free (child2parent);	/* A node for this childs reply FIFO already existed in the hash table. */
		fprintf (stderr, "Warning: line %d of %s.  You have already created a reply FIFO for child pid %s.\n",
			 __LINE__, __FILE__, child_pidstr);
	}
}

/*******************************************************************************
 * FUNCTION:	SEND2PARENT
 ******************************************************************************/
void            send2parent (shared_fifodata_tt * parent2child, server_command_tt command, const char *dataptr)
{

/*
 * header_string contains three integer strings delimited by 3 spaces, ending
 * with a NULL terminator.
 */
	char            header_string[INTLEN + 1 + INTLEN + 1 + INTLEN + 1 + 1];
	static growbuf_tt *gbuf = NULL;/* A buffer which grows as you append data to it.  It grows to the size of the longest
				        * data stream copied to it. */
	size_t          sendsize;
	size_t          bytes_left;
	size_t          bytes_sent;

	if (gbuf == NULL)	/* First call to this function. */
	{
		growbuf_init (&gbuf);
	}
/* Note: the space after the third number is required later by sscanf(). */
	sprintf (header_string, "%*d %*d %*d ", INTLEN, getpid (), INTLEN, command, INTLEN, strlen (dataptr));

	growbuf_strcpy (gbuf, header_string);
	growbuf_strcat (gbuf, dataptr);

	sem_wait (parent2child->semaphore);	/* You can get interleaved writes from different child processes if you need to
						 * send more bytes than can be written in a single atomic write to a FIFO. */
	bytes_left = strlen (growbuf_str (gbuf));	/* Length EXCLUDES header length. */
	while (bytes_left)
	{
		if (bytes_left > parent2child->bufsiz)
		{
			sendsize = parent2child->bufsiz;
		}
		else
		{
			sendsize = bytes_left;
		}
		bytes_sent = write (parent2child->fd, growbuf_str (gbuf), sendsize);
		if (sendsize != bytes_sent)
		{
			perror ("write() in send2parent()");
			printf ("*---- Only able to write %d bytes.  Requested size = %d.  Line %d of %s ----*\n",
				bytes_sent, sendsize, __LINE__, __FILE__);
			fflush (stdout);
			if (bytes_sent < 0)
				bytes_sent = 0;
		}
		bytes_left -= bytes_sent;
	}
	sem_signal (parent2child->semaphore);
	return;
}

/*******************************************************************************
 *FUNCTION:	SEND2CHILD
 *	NOTE: The sender simply echos the "command" token it received back to
 *	the child.   I did this to keep all message headers the same.
 *
 *	This function needs the parent2child struct, so it can look up the
 *	reply FIFO in the hash table of reply nodes.
 ******************************************************************************/
void            send2child (shared_fifodata_tt * parent2child, const char *child_pidstr,
			                    server_command_tt command, const char *dataptr)
{
	char            header_string[INTLEN + 1 + INTLEN + 1 + INTLEN + 1 + 1];
	static growbuf_tt *gbuf = NULL;/* A buffer which grows as you append data to it.  It grows to the size of the longest
				        * data stream copied to it. */
	size_t          sendsize;
	size_t          bytes_left;
	size_t          bytes_sent;
	reply_fifodata_tt *child2parent;
	int             hashkey;

	hashkey = atoi (child_pidstr);
	child2parent = (reply_fifodata_tt *) hash_find (parent2child->reply_htab, hashkey);
	if (child2parent == NULL)
	{
		util_abort (__LINE__, __FILE__, "The reply_fifodata_tt struct pointer, for Child pid %s was not "
			    "in the parent2child->reply_htab hash table.  hashkey == %d\n",
			    child_pidstr ? child_pidstr : "(Null String)", hashkey);
	}

	if (gbuf == NULL)	/* First call to this function. */
	{
		growbuf_init (&gbuf);
	}
/* Note: the space after the third number is required later by sscanf(). */
	sprintf (header_string, "%*d %*d %*d ", INTLEN, getpid (), INTLEN, command, INTLEN, strlen (dataptr));

	growbuf_strcpy (gbuf, header_string);
	growbuf_strcat (gbuf, dataptr);

	bytes_left = strlen (growbuf_str (gbuf));	/* Length EXCLUDES header length. */
	while (bytes_left)
	{
		if (bytes_left > child2parent->bufsiz)
		{
			sendsize = child2parent->bufsiz;
		}
		else
		{
			sendsize = bytes_left;
		}

		bytes_sent = write (child2parent->fd, growbuf_str (gbuf), sendsize);
		if (sendsize != bytes_sent)
		{
			perror ("write() in send2child()");
			printf ("*---- Process %d only able to write %d bytes.  Requested size = %d.  Line %d of %s ----*\n",
				getpid (), bytes_sent, sendsize, __LINE__, __FILE__);
			fflush (stdout);
			if (bytes_sent < 0)
				bytes_sent = 0;
		}
		bytes_left -= bytes_sent;
	}
	return;
}

/*******************************************************************************
 * FUNCTION:	CONNECT_TO_PARENT
 *	Called from child processes.  You only want to call this function once
 *	for each connection opened to an ancestor process.  Note that it is
 *	possible that you would want to connect to your mother process and
 *	your grandmother process.
 *	1. Allocate a child2parent struct, and fill in the childstr and
 *	   pathname filelds
 *	2. Get a pathname for, and create the FIFO in the file system and open it
 *	   (by calling open_parent2child_fifo())
 *	3. Open the shared fifo for writing.
 *	4. Tell the server to create a reply fifo.
 *	5. Open the reply fifo for reading.
 ******************************************************************************/
void            connect_to_parent (shared_fifodata_tt * parent2child, const char *pidstr, reply_fifodata_tt ** child2parent)
{
	char            message[128];

	*child2parent = (reply_fifodata_tt *) calloc (1, sizeof (reply_fifodata_tt));
	if (child2parent == NULL)
	{
		util_abort (__LINE__, __FILE__, "calloc() failed.\n");
	}
	strcpy ((*child2parent)->childstr, pidstr);
	(*child2parent)->pathname = create_new_fifoname (parent2child, pidstr);
	create_fifo ((*child2parent)->pathname);
	open_parent2child_fifo (parent2child, O_WRONLY);
	sprintf (message, "This is an SRV_CONNECT message.");
	send2parent (parent2child, SRV_CONNECT, message);
	(*child2parent)->fd = open_fifo ((*child2parent)->pathname, O_RDONLY, &(*child2parent)->bufsiz);
}

/*******************************************************************************
 * FUNCTION:	DESTROY_CHILD2PARENT
 *	Each child process allocates memory for handling the reply FIFO, in
 *	its own address space.  Unlink the child2parent FIFOs in the file
 *	system from the parent process.
 ******************************************************************************/
void            destroy_child2parent (reply_fifodata_tt * child2parent)
{
	/*** printf ("destroy_child2parent( 0x%X ) called by PID %d\n", child2parent, getpid ()); ***/
	/*** fflush (stdout); ***/
	if (child2parent != NULL)
	{
		close (child2parent->fd);
		if (child2parent->pathname)
		{
			free (child2parent->pathname);
		}
		if (child2parent->data_gbuf != NULL)
		{
			growbuf_free (&(child2parent->data_gbuf));
		}
	}
}

/*******************************************************************************
 * FUNCTION:	DESTROY_FIFOS
 *	This function cannot destroy the reply FIFO data structures created by
 *	child processes, because those data structures are in another
 *	address space.
 ******************************************************************************/
void            destroy_fifos (shared_fifodata_tt * parent2child)
{
	reply_fifodata_tt *child2parent;
	void           *pos;	       /* A context reference used by hash_getfirst() and hash_getnext() */

	/*** printf ("destroy_fifos() is blasting the following:\nShared parent FIFO:\n"); ***/
	/*** dump_sharedfifo_struct (stdout, parent2child); ***/
	/*** printf ("\nChild FIFOs:\n"); ***/

/* Remove the parent FIFO from the file system. */
	close (parent2child->fd);
	unlink (parent2child->pathname);

/*
 * Destroy the data items referenced by each child2parent struct in the hash
 * table.  Use hash_free() to destroy the child2parent nodes themselves
 * (hash_free calls free() on the data pointers for each hash table entry.)
 * Do not forget to unlink() the child2parent FIFOs from the file system.
 */
	child2parent = (reply_fifodata_tt *) hash_getfirst (&pos, parent2child->reply_htab);
	if (child2parent != NULL)
	{
		/*** dump_replyfifo_struct (stdout, child2parent); ***/
		/*** printf ("\n"); ***/
		unlink (child2parent->pathname);
		destroy_child2parent (child2parent);
		while ((child2parent = (reply_fifodata_tt *) hash_getnext (&pos, parent2child->reply_htab)) != NULL)
		{
			/*** dump_replyfifo_struct (stdout, child2parent); ***/
			/*** printf ("\n"); ***/
			unlink (child2parent->pathname);
			destroy_child2parent (child2parent);
		}
	}
	hash_free (parent2child->reply_htab);

/* Free the rest of the data fields */
	free (parent2child->pathname);
	if (parent2child->data_gbuf)
	{
		growbuf_free (&parent2child->data_gbuf);
	}

/* Free the shared fifo struct itself. */
	free (parent2child);
}

/*******************************************************************************
 * FUNCTION:	READ_HEADER
 *	Reads the fixed-lengtn message header, which contains the PID of process
 *	sending the message, a "command" value from the enumerated type
 *	server_command_tt, and the length of the text of the message which
 *	follows the header.
 *
 *	This function tries to recover from interrupted calls to read().
 ******************************************************************************/
static void     read_header (int fd, const char *sender_pidstr, server_command_tt * command, size_t * msglen)
{
	char            buf[MSG_HEADER_SIZ + 1];
	size_t          recvsize;
	size_t          bytes_read = 0;
	int             num_translations;	/* Number of fields successfully translated by sscanf(). */
	int             retry_count = 10;	/* Maximum number of read attempts before giving up. */

	buf[MSG_HEADER_SIZ] = '\0';
	do
	{
		if (bytes_read)
		{
			printf ("Attempting follow-up read.  bytes_read == %d\n", bytes_read);
		}

		if ((recvsize = read (fd, &buf[bytes_read], MSG_HEADER_SIZ)) == -1)
		{
			if (errno == EINTR)	/* Caught an interrupt? no problem, just try again. */
			{
				recvsize = 0;
			}
			else
			{
				perror ("read() in read_header()");
				util_abort (__LINE__, __FILE__, "Process %d failed to read a message header.\n"
					    "read (%d, 0x%X, %d); errno == %d\n", getpid (), fd, buf, MSG_HEADER_SIZ, errno);
			}
		}
		bytes_read += recvsize;
		if (bytes_read < MSG_HEADER_SIZ)
		{
			printf ("Partial read(): retries left %d; bytes_read %d; process %d\n"
				"\trecvsize %d, header size %d; line %d of %s.\n",
				retry_count, bytes_read, getpid (), recvsize, MSG_HEADER_SIZ, __LINE__, __FILE__);
			fflush (stdout);
			--retry_count;
			if (!retry_count)
				abort ();

		}
		if (strlen (buf) == 0)
		{
			if (bytes_read > 0)
			{

			/*
			 * On the HP, if a write() operation gets
			 * interrupted, you still get a NULL char on the
			 * receiving end.
			 */
				int             idx;
				int             shiftcount;

				printf ("Zero length read, but read() returned nonzero.  errno = %d\n"
					"\tretries left %d: bytes_read %d; process %d\n"
					"\trecvsize %d, header size %d; line %d of %s.\n",
					errno, retry_count, bytes_read, getpid (), recvsize, MSG_HEADER_SIZ, __LINE__, __FILE__);
				printf ("Contents of buf[]:\n");
				for (idx = 0; idx < MSG_HEADER_SIZ; idx++)
				{
					printf ("buf [%2d] = '%c' == %d  == Ox%X\n", idx, buf[idx], buf[idx], buf[idx]);
				}
				fflush (stdout);

				--retry_count;
				if (!retry_count)
					abort ();

			/*
			 * On the HP, if a write() operation gets
			 * interrupted, you get an extraneous NULL char in
			 * the data stream, that the reader has to throw
			 * away.
			 */

				shiftcount = 0;
				while ((buf[0] == '\0') && (shiftcount < MSG_HEADER_SIZ))
				{
					for (idx = 0; idx < (MSG_HEADER_SIZ - shiftcount); ++idx)
					{
						buf[idx] = buf[idx + 1];
					}
					++shiftcount;
				}
				bytes_read -= shiftcount;
				buf[MSG_HEADER_SIZ] = '\0';
				printf ("buf[] after shift: \"%s\"\n\tbytes_read = %d; shiftcount = %d\n", buf, bytes_read, shiftcount);
				fflush (stdout);
			}
		}
	} while (bytes_read < MSG_HEADER_SIZ);
	buf[bytes_read] = '\0';
	num_translations = sscanf (buf, "%s %d %d ", sender_pidstr, command, msglen);

	if (num_translations < 3)
	{
		util_abort (__LINE__, __FILE__, "sscanf() failed to translate the following message header:"
			    "\t\"%s\"\nOnly %d translations were made.\n", buf, num_translations);
	}
}

/*******************************************************************************
 * FUNCTION:	read_msgtext
 ******************************************************************************/
static int      read_msgtext (int fd, int bufsiz, size_t msglen, growbuf_tt * gbuf)
{
	static int      buflen = 0;
	size_t          recvsize;
	int             bytes_read = 0;
	int             bytes2go;
	static char    *buf = NULL;

	if (buf == NULL)
	{
		buflen = bufsiz + 1;
		if ((buf = calloc (buflen, sizeof (char))) == NULL)
		{
			perror ("calloc()");
			util_abort (__LINE__, __FILE__, "calloc(%d, %d) failed.\n", buflen, sizeof (char));
		}
	}

	growbuf_strcpy (gbuf, "");
	bytes_read = 0;

	while ((bytes_read < msglen))
	{
		bytes2go = msglen - bytes_read;
		if (bytes2go < bufsiz)
			recvsize = bytes2go;
		else
			recvsize = bufsiz;
		if ((recvsize = read (fd, buf, recvsize)) == -1)
		{
			if (errno == EINTR)	/* Caught an interrupt? no problem, just try again. */
			{
				recvsize = 0;
			}
			else
			{
				perror ("read() in read_msgtext()");
				util_abort (__LINE__, __FILE__, "Process %d failed calling read(%d, 0x%X, %d)\n",
					    getpid (), fd, buf, recvsize);
			}
		}
		bytes_read += recvsize;
		buf[bytes_read] = '\0';
		growbuf_strcat (gbuf, buf);
	}
	return (bytes_read);
}

/*******************************************************************************
 * FUNCTION:	RECEIVE_FM_PARENT
 *	1. Find out a)who is sending the message, b)what kind of message it
 *	   is, and c) how big the message is.
 *	2. Make sure your buffer object has been initialized.
 *	3. Fetch the actual text of the message, pass back the message size via
 *	   the datalen_ptr parameter.
 *	3. Pass back a pointer to the message via the dataptr parameter.
 *	4. Return the message type/command to the caller.
 ******************************************************************************/
server_command_tt receive_fm_parent (reply_fifodata_tt * child2parent, size_t * datalen_ptr)
{
	server_command_tt command;
	size_t          msglen;
	char            sender_pidstr[INTLEN + 1];

	read_header (child2parent->fd, sender_pidstr, &command, &msglen);
	if (child2parent->data_gbuf == NULL)
	{
		growbuf_init (&child2parent->data_gbuf);
	}

	*datalen_ptr = read_msgtext (child2parent->fd, child2parent->bufsiz, msglen, child2parent->data_gbuf);
	return (command);
}

/*******************************************************************************
 * FUNCTION:	RECEIVE_FM_CHILD
 *	Read a complete message from the shared FIFO.  Return the command
 *	value to the caller.  Pass the string representation of the message,
 *	a pointer to the text of the message, and the length of the message
 *	text (EXCLUDING the header length) to the caller.
 ******************************************************************************/
server_command_tt receive_fm_child (shared_fifodata_tt * parent2child, char child_pidstr[INTLEN], size_t * datalenptr)
{
	server_command_tt command;     /* Return value. */
	size_t          msgsize;

	read_header (parent2child->fd, child_pidstr, &command, &msgsize);

	if (parent2child->data_gbuf == NULL)	/* First read from the shared FIFO. */
	{
		growbuf_init (&parent2child->data_gbuf);
	}
	growbuf_strcpy (parent2child->data_gbuf, "");

	*datalenptr = read_msgtext (parent2child->fd, parent2child->bufsiz, msgsize, parent2child->data_gbuf);

	return (command);
}				       /* end receive_fm_child() */

/*******************************************************************************
 * FUNCTION:	REPLY_FIFO_BUFSIZ
 *	The size of the FIFO buffer may depend on the device on which it
 *	was created.
 ******************************************************************************/
int             reply_fifo_bufsiz (reply_fifodata_tt * child2parent)
{
	return (child2parent->bufsiz);
}

/*******************************************************************************
 * FUNCTION:	REPLY_FIFO_DATA
 *	NOTE: this function returns a pointer to storage inside the FIFO
 *	      modules internal data structures; so give the caller a pointer
 *	      that cannot be written to (const).  If the caller wants to
 *	      modify the data, then it must make its own copy.  (this internal
 *	      data is overwritten whenever a read() is perfomed on the FIFO
 *	      anyway).
 ******************************************************************************/
const char     *reply_fifo_data (reply_fifodata_tt * child2parent)
{
	return (growbuf_str (child2parent->data_gbuf));
}

/*******************************************************************************
 * FUNCTION:	SHARED_FIFO_BUFSIZ
 *	The size of the FIFO buffer may depend on the device on which it
 *	was created.
 ******************************************************************************/
int             shared_fifo_bufsiz (shared_fifodata_tt * parent2child)
{
	return (parent2child->bufsiz);
}

/*******************************************************************************
 * FUNCTION:	SHARED_FIFO_DATA
 *	NOTE: this function returns a pointer to storage inside the FIFO
 *	      modules internal data structures; so give the caller a pointer
 *	      that cannot be written to (const).  If the caller wants to
 *	      modify the data, then it must make its own copy.  (this internal
 *	      data is overwritten whenever a read() is perfomed on the FIFO
 *	      anyway).
 ******************************************************************************/
const char     *shared_fifo_data (shared_fifodata_tt * parent2child)
{
	return (growbuf_str (parent2child->data_gbuf));
}

/*******************************************************************************
 * FUNCTION:	COMMANDVAL2STRING
 *	Returns a pointer to the string representation of an element of the
 *	enumerated type "server_command_tt".
 ******************************************************************************/
typedef struct server_command_lookup_ss
{
	server_command_tt enum_val;
	const char     *valstr;
}               server_command_lookup_tt;

const char     *commandval2string (server_command_tt val)
{
	static server_command_lookup_tt lookup_table[] = {
		SRV_CONNECT, "SRV_CONNECT",
		SRV_PRINT, "SRV_PRINT",
		SRV_TIMEOUT, "SRV_TIMEOUT",
		SRV_ECHO, "SRV_ECHO",
		SRV_POPUP_ERROR_DIALOG, "SRV_POPUP_ERROR_DIALOG",
		SRV_DRAW_LINE, "SRV_DRAW_LINE",
		SRV_COPY_AREA, "SRV_COPY_AREA",
		SRV_DRAW_STRING, "SRV_DRAW_STRING",
		SRV_DISPLAY_EXEC_MSG, "SRV_DISPLAY_EXEC_MSG",
		SRV_BELL, "SRV_BELL",
		SRV_BLINK, "SRV_BLINK",
		SRV_SHUTDOWN, "SRV_SHUTDOWN"
	};

	if (val != lookup_table[(int) val].enum_val)
	{
		util_abort (__LINE__, __FILE__, "The lookup table for translating values from the enumerated type \n"
			    "\"server_command_tt\" into character strings, is out of order.   Compare the \n"
			    "definition of type server_command_tt in fifo.h, to the lookup table in\n"
			    "commandval2string().  Value %d incorrectly maps to the string representation \n"
			    "for value %d (\"%s\")\n", val, lookup_table[(int) val].enum_val, lookup_table[(int) val].valstr);
	}

	return (lookup_table[(int) val].valstr);
}
