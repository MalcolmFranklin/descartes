#ifndef FIFO_H
#define FIFO_H	1
/*******************************************************************************
 * MODULE:	FIFO_H
 *
 * PURPOSE:	<required>
 *
 * FUNCTIONS DECLARED
 *	EXTERNAL:	<required>
 *
 * USE:	<optional>
 *
 * IMPLEMENTATION:	<optional>
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 * $Author: franklin $
 *******************************************************************************
 * $Date: 1994/08/22 00:23:21 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/cmdline_ex/RCS/fifo.h,v $
 *
 ******************************************************************************/



#if 0
/******************************************************************************
 *
$Log: fifo.h,v $
 * Revision 1.9  1994/08/22  00:23:21  franklin
 * Add a string-representation of the PID of the server
 * process to the definition of shared_fifodata_tt.  That way
 * we can have multiple "servers" at different levels of the
 * "client - server" hierarchy.  In other words, a child proces
 * can act as a seperate server to its own children.
 *
 * Revision 1.8  1994/08/10  19:11:58  franklin
 * Move the #definition of MSG_HEADER_SIZ to fifo.h, so that safe.c can
 * see it.  The timeout() signal handler has to build a message header
 * manually, because send2parent() and functions that it calls, are not
 * reentrant.  Warn users not to use MSG_HEADER_SIZ in their code if they
 * can avoid it.
 *
 * Revision 1.7  1994/08/09  01:08:53  franklin
 * Added utility function commandval2string(), and two
 * new enumerated values.
 *
 * Revision 1.6  1994/08/06  22:25:17  franklin
 * Delete SRV_NO_OP.  It was not needed.
 *
 * Revision 1.5  1994/08/06  18:46:16  franklin
 * Add "const" qualifier to parameters that are not modified by
 * the FIFO utilities
 *
 * Revision 1.4  1994/08/05  17:08:15  franklin
 * Remove "static" keyword from functions parent_open_reply_fifo()
 * and connect_to_parent.
 * Remove dataptr parameter from receive_fm_child()
 * and receive_fm_parent().
 *
 * Revision 1.3  1994/08/05  14:56:59  franklin
 * Add parent_open_reply_fifo(), open_parent2child_fifo(),
 * and connect_to_parent().
 *
 * Revision 1.2  1994/08/05  02:35:03  franklin
 * 1. Add new enumerated values for the commands in parse() in wid1.c
 * 2. Add prototypes for utilities to get data from FIFO structs.
 *
 * Revision 1.1  1994/08/05  00:06:04  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif

static char    *fifo_h_rcsid = "$Id: fifo.h,v 1.9 1994/08/22 00:23:21 franklin Exp $";


#define	INTLEN		11	       /* Big enough to handle the string representation of 32 bit integers. 2^32 = 4294967296
				        * ==> 10 digits + 1 null terminator.  If you port this to a 64 bit machine, use 21 bytes:
				        * 2^64 = 18446744073709551616 ==> 20 digits + 1 for null terminator. */


/******************************************************************************
 * NOTE: DO NOT USE the value MSG_HEADER_SIZ unless you absolutely have to.
 * 	I put the definition of this symbol in this header file, so that I
 *	could write a signal handler routine capable of sending a message.
 *	The FIFO package routines are not reentrant, and must not be called
 *	from within a signal handler.  See the comments of the timeout()
 *	function in analysis1.c for details.
 *
 * Message headers contain the string representations of 3 integers:
 * sender_pid, command, and  data_len.  These strings are delimited with
 * whitespace, so that the receiver of the message can convert the 3 strings
 * back to integers, with a call to sscanf().  The header has to have a fixed
 * length, so the reader knows how much stuff to read.  Otherwise it is
 * possible to read multiple messages with one FIFO read.
 *****************************************************************************/
#define MSG_HEADER_SIZ          (INTLEN + 1 + INTLEN + 1 + INTLEN + 1)


/* Message types, tells the recipient what a particular message is for. */
typedef enum
{
	SRV_CONNECT,
	SRV_PRINT,
	SRV_TIMEOUT,		       /* Used to implement TIMER_, DELAY_, and GTIME_ language features. */
	SRV_ECHO,
	SRV_POPUP_ERROR_DIALOG,	       /* 'e' */
	SRV_DRAW_LINE,		       /* 'd' */
	SRV_COPY_AREA,		       /* 'c' */
	SRV_DRAW_STRING,	       /* 't' */
	SRV_DISPLAY_EXEC_MSG,	       /* 'm' */
	SRV_BELL,		       /* 'b' */
	SRV_BLINK,		       /* 'k' */
	SRV_SHUTDOWN		       /* 'f' */
}               server_command_tt;

/*
 * Type reply_fifodata_tt is for reply FIFOs used by a parent to write to a
 * child.
 */
typedef struct reply_fifodata_ss
{
	int             pid;	       /* First field of any data item stored in the hashtable utilities we are using, must be a
				        * UNIQUE KEY (we use the process id (pid).  DO NOT MOVE this field. */
	char            childstr[INTLEN];	/* PID of child process that this reply FIFO is connected to. */
	int             fd;	       /* FIFO descriptor returned by mkfifo */
	int             bufsiz;	       /* The value PIPE_BUF, which represents the maximum number of bytes that can be written to
				        * a pipe or FIFO in a single atomic operation, is NOT ALWAYS #defined <limits.h>.  For
				        * some operating systems, (such as SunOS), the number of bytes that can be transferred
				        * atomically, depends upon the device on which the FIFO was created.  You must create the
				        * FIFO, and then use either pathconf() or fpathconf() to determine the maximum blocksize
				        * at runtime.  */
	char           *pathname;
	growbuf_tt     *data_gbuf;     /* Contains the text of the most recent message received by the child.  Note that this
				        * buffer will always be empty for reply_fifodata_tt structs in the parent processes
				        * address space, it will only contain data in the child process. */
}               reply_fifodata_tt;


/*
 * Type shared_fifodata_tt is for a FIFO written to by all child processes.
 * Not used for reply FIFOs from the parent back to a child.
 */


typedef struct shared_fifodata_ss
{
	int             fd;	       /* FIFO descriptor returned by mkfifo */
	char            server_pidstr[INTLEN];	/* Process ID of the parent/server process which reads this FIFO. */
	int             bufsiz;	       /* The value PIPE_BUF, which represents the maximum number of bytes that can be written to
				        * a pipe or FIFO in a single atomic operation, is NOT ALWAYS #defined <limits.h>.  For
				        * some operating systems, (such as SunOS), the number of bytes that can be transferred
				        * atomically, depends upon where the FIFO was created.  You must create the FIFO, and
				        * then use either pathconf() or fpathconf() to determine the maximum blocksize at
				        * runtime.  */
	char           *pathname;
	int             semaphore;     /* Only let one child process write to the shared FIFO at a time. */
	char            fromstr[INTLEN];	/* PID of the sender of the most recent message. */
	growbuf_tt     *data_gbuf;     /* Contains the text of the most recent message. */
	hash_table     *reply_htab;    /* This is a hashtable containing pointers to structs of type reply_fifodata_tt.  One
				        * reply fifo for each child; the table is keyed by string representations of the child
				        * processes pid. */
}               shared_fifodata_tt;


extern void     dump_sharedfifo_struct (FILE * fp, shared_fifodata_tt * parent2child);
extern void     dump_replyfifo_struct (FILE * fp, reply_fifodata_tt * child2parent);
extern shared_fifodata_tt *init_parent2child_fifo (const char *pidstr);
extern void     send2parent (shared_fifodata_tt * parent2child, server_command_tt command, const char *dataptr);
extern void     send2child (shared_fifodata_tt * parent2child, const char *child_pidstr,
			                    server_command_tt command, const char *dataptr);
extern void     connect_to_parent (shared_fifodata_tt * parent2child, const char *pidstr, reply_fifodata_tt ** child2parent);
extern void     destroy_child2parent (reply_fifodata_tt * child2parent);
extern void     destroy_fifos (shared_fifodata_tt * parent2child);
extern server_command_tt receive_fm_parent (reply_fifodata_tt * child2parent, size_t * datalen_ptr);
extern server_command_tt receive_fm_child (shared_fifodata_tt * parent2child, char child_pidstr[INTLEN], size_t * datalenptr);
extern void     parent_open_reply_fifo (shared_fifodata_tt * parent2child, const char *child_pidstr);
extern void     open_parent2child_fifo (shared_fifodata_tt * parent2child, mode_t flags);
extern void     connect_to_parent (shared_fifodata_tt * parent2child, const char *pidstr, reply_fifodata_tt ** child2parent);
extern int      reply_fifo_bufsiz (reply_fifodata_tt * child2parent);
extern const char *reply_fifo_data (reply_fifodata_tt * child2parent);
extern int      shared_fifo_bufsiz (shared_fifodata_tt * parent2child);
extern const char *shared_fifo_data (shared_fifodata_tt * parent2child);
extern const char *commandval2string (server_command_tt val);

#endif				       /* FIFO_H not already included. */
