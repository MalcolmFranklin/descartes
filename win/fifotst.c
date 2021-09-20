/*******************************************************************************
 * MODULE:	FIFOTST.C
 *
 * PURPOSE:	Test driver program for the FIFO module (fifo.c)
 *
 * USE:
 *
 *	The data passed between processes is in the following format when
 *	it is written to/read from any of the FIFOs:
 *	<sender process ID string><blank><command number string><blank><data len>
 *		<blank><data>
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 * $Author: franklin $
 *******************************************************************************
 * $Date: 1994/08/05 17:19:42 $
 * $State: Exp $
 * $Locker: franklin $
 * $Source: /all/franklin/thesis/descartes/win/RCS/fifotst.c,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: fifotst.c,v $
 * Revision 1.1  1994/08/05  17:19:42  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif

static char    *rcsid = "$Id: fifotst.c,v 1.1 1994/08/05 17:19:42 franklin Exp franklin $";


#include <stdlib.h>
#include "cchk_missing_stdlib.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include <errno.h>		       /* perror() */
#include <unistd.h>
#include "cchk_missing_unistd.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <fcntl.h>		       /* O_RDONLY - file open mode needed by open_parent2child_fifo() -- called in the server
				        * (client calls it via connect_to_parent() */
#include <sys/wait.h>		       /* wait(), waitpid() */

#include "semops.h"		       /* To create semaphore for the child process. */
#include "some_utils.h"		       /* util_abort() and growstr() utilities. */
#include "hash.h"		       /* Hash table to match process ID to a FIFO. */
#include "fifo.h"

/*******************************************************************************
 * FUNCTION:	SUB_CLIENT
 *	Another sub-process
 ******************************************************************************/
static void     sub_client (shared_fifodata_tt * parent2child)
{
	char            child_pidstr[INTLEN];
	char            message[1024];
	reply_fifodata_tt *child2parent = NULL;	/* Important!  Initialize to NULL to keep destroy_child2parent() from freeing
						 * stuff, in case you never call connect_to_parent() */
	const char     *reply_ptr;
	size_t          reply_len;     /* Length of the parents reply to your message. */
	server_command_tt command;

	sprintf (child_pidstr, "%d", getpid ());
	printf ("Sub-Child created.  PID = %s\n", child_pidstr);
	fflush (stdout);
	connect_to_parent (parent2child, child_pidstr, &child2parent);
	(void) sprintf (message, "sub_client's message.");
	send2parent (parent2child, SRV_ECHO, message);
	command = receive_fm_parent (child2parent, &reply_len);
	reply_ptr = reply_fifo_data (child2parent);

	printf ("Subclient %d received reply: command = %d; "
		"reply_len = %d  reply_ptr:\n",
		getpid (), command, reply_len);
	printf ("\t\"%s\"\n", reply_ptr);
	fflush (stdout);
/* CRITICAL: dont forget to free up memory and die! */
	destroy_child2parent (child2parent);
	free (child2parent);
	exit (0);
}

/*******************************************************************************
 * FUNCTION:	CLIENT
 ******************************************************************************/
void            client (shared_fifodata_tt * parent2child)
{
	char            child_pidstr[INTLEN];
	char            message[1024];
	reply_fifodata_tt *child2parent = NULL;	/* Important!  Initialize to NULL to keep destroy_child2parent() from freeing
						 * stuff, in case you never call connect_to_parent() */
	const char     *reply_ptr;
	size_t          reply_len;     /* Length of the parents reply. */
	server_command_tt command;
	int             subchild_cnt = 0;

	sprintf (child_pidstr, "%d", getpid ());

	printf ("Child created.  PID = %s\n", child_pidstr);
	fflush (stdout);

/*
 * Later, parent will create and open a reply FIFO back to each child.
 */
	(void) sprintf (message, "This is the message");

	connect_to_parent (parent2child, child_pidstr, &child2parent);

	if (fork () == 0)
		sub_client (parent2child);
	else
		subchild_cnt++;

	(void) sprintf (message, "echomeback echomeback echomeback");
	send2parent (parent2child, SRV_ECHO, message);
	if (fork () == 0)
		sub_client (parent2child);
	else
		subchild_cnt++;
	printf ("Client() At line %d of %s\n", __LINE__, __FILE__);
	fflush (stdout);

	command = receive_fm_parent (child2parent, &reply_len);
	reply_ptr = reply_fifo_data (child2parent);

/*
 * CRITICAL: exactly ONE (1) child process may send a shutdown command to the
 * parent, otherwise the other children will be left orphaned without a
 * server.
 */
	while (subchild_cnt > 0)
	{
		int             waitretval;

		printf ("Client(): subchild_cnt = %d at line %d of %s\n",
			subchild_cnt, __LINE__, __FILE__);
		fflush (stdout);
		waitretval = wait (0);
		printf ("wait() returned %d to client()\n", waitretval);
		fflush (stdout);
		--subchild_cnt;
	}
	sprintf (message, "shutdownmsg shutdownmsg shutdownmsg");
	send2parent (parent2child, SRV_SHUTDOWN, message);

	printf ("client() At line %d of %s\n", __LINE__, __FILE__);
	fflush (stdout);

	destroy_child2parent (child2parent);
	free (child2parent);
}

/*******************************************************************************
 * FUNCTION:	SERVER
 ******************************************************************************/
void            server (shared_fifodata_tt * parent2child)
{
	char            child_pidstr[INTLEN];
	server_command_tt command;
	const char     *dataptr;
	char           *echobuf;       /* We must make our own copy of the data we get from shared_fifo_data() before passing it
				        * back to the child in the SRV_ECHO command, because shared_fifo_data() returns a const
				        * char*. */
	size_t          datalen;

	printf ("Executing parent code.\n");
	fflush (stdout);

/* Later, child will open a reply fifo to get data back from parent */
	open_parent2child_fifo (parent2child, O_RDONLY);

	if ((echobuf = malloc (shared_fifo_bufsiz (parent2child))) == NULL)
		util_abort (__LINE__, __FILE__, "malloc() failed.\n");

	do
	{			/* Process client commands until you get a shutdown command. */
		command = receive_fm_child (parent2child, child_pidstr, &datalen);
		dataptr = shared_fifo_data (parent2child);

		switch (command)
		{
			case SRV_CONNECT:
				printf ("SRV_CONNECT: Parent received %d "
				"byte message from %s.  message:\n\t\"%s\"\n",
					datalen, child_pidstr, dataptr);
				parent_open_reply_fifo (parent2child, child_pidstr);
				break;
			case SRV_ECHO:
				printf ("SRV_ECHO: parent received \"%s\".\n"
				        "\tSending string back to child.\n", dataptr);
				strcpy (echobuf, dataptr);
				send2child (parent2child, child_pidstr, command, echobuf);

			default:
				printf ("Parent received %d byte message"
					"from %s.  Command %d, message:\n"
					"\t\"%s\"\n", datalen, child_pidstr,
					command, dataptr);
		}

	/*
	 * CRITICAL: exactly ONE (1) child process may send a shutdown
	 * command to the parent, otherwise the other children will be left
	 * orphaned without a server.
	 */

	} while (command != SRV_SHUTDOWN);

	destroy_fifos (parent2child);
	free (echobuf);

/*
 * Stay alive long enough to get a SIGPIPE error in case the shutdown command
 * was sent before all children were ready to die.
 */
	sleep (1);

}

/*******************************************************************************
 * FUNCTION:	MAIN
 ******************************************************************************/
shared_fifodata_tt *parent2child;
int             main (void)
{
	char            parent_pidstr[INTLEN];	/* String representation of the parent process ID. */
	pid_t           pid;	       /* Process ID returned from fork() */

	sprintf (parent_pidstr, "%d", (int) getpid ());
	parent2child = init_parent2child_fifo (parent_pidstr);

	if ((pid = fork ()) == -1)
	{
		perror ("Erron in fork()");
		exit (-1);
	}
	else if (pid == 0)
		client (parent2child);	/* Child */
	else
		server (parent2child);	/* Parent */

	return (0);
}
