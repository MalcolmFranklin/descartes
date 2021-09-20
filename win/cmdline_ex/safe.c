#define _POSIX_SOURCE	1
/*******************************************************************************
 * MODULE:	SAFE.C
 *
 * PURPOSE:	Contains signal handlers, and reentrant functions that are safe
 *		to call from within a signal handler.
 * MOTIVATION:
 *
 * The printf()/scanf() functions used in the FIFO module are not re-entrant,
 * therefore they MUST NOT BE called from within a signal handler (Believe
 * me, this took me three days to debug.) You must manually build the message
 * header and send it to the FIFO package via "write()".  POSIX.1 does
 * guarantee that write() is reentrant.  A list of reentrant functions is
 * given in section 3.3.1.3 of POSIX.1-1990.  POSIX.1 also says that any
 * functions listed in the ANSI C standard as reentrant, may be called from
 * within a signal handler BUT ANSI/ISO 9899-1990 section 7.7.1 says that the
 * behavior of a signal handler is undefined if it calls any function in the
 * Standard C library other than signal() itself (to re-register itself as a
 * signal handler). THE POINT: the only safe functions provided by the
 * system, are those listed in POSIX.1, and the Standard C "signal()"
 * function.
 *
 * FUNCTIONS DECLARED
 *	EXTERNAL:	<required>
 *	LOCAL:		<optional>
 *
 * EXTERNAL INTERFACES
 *	INCLUDES:       <optional>
 *	GLOBALS:	<optional>
 *	FILES:		<optional>
 *	OTHER:		<optional>
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 * $Author: franklin $
 *******************************************************************************
 * $Date: 1994/08/12 17:43:19 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/cmdline_ex/RCS/safe.c,v $
 *
 ******************************************************************************/



#if 0
/******************************************************************************
 *
$Log: safe.c,v $
 * Revision 1.6  1994/08/12  17:43:19  franklin
 * Echo timeout message to stdout.
 *
 * Revision 1.5  1994/08/12  15:55:16  franklin
 * When printing the timeout message to stdout, put quotes
 * around it.
 *
 * Revision 1.4  1994/08/12  05:03:57  franklin
 * Correct comments.
 *
 * Revision 1.3  1994/08/11  22:53:20  franklin
 * Perform the SIGALRM timeout() processing inside a
 * child process, to ensure mutually-exclusive
 * access to the parent2child FIFO.
 *
 * Revision 1.2  1994/08/10  18:56:28  franklin
 * Provide "right-justified in fieldwidth" and regular integer-to-string
 * functions.  MUST BE REENTRANT: (safe_int2string_rj() and safe_int2string()).
 *
 * Move sigchild_handler() from exec_rtn1.c to this file.
 * Move sigpipe_handler()  from fifo.c to this file.
 *
 * Revision 1.1  1994/08/10  17:23:00  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif

static char    *rcsid = "$Id: safe.c,v 1.6, h4_3_8 1994/08/12 17:43:19 franklin Exp $";


#include <stdlib.h>
#include "cchk_missing_stdlib.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <stdio.h>		       /* Required by exec_rtn.h */

#include <unistd.h>		       /* write() */
#include "cchk_missing_unistd.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <signal.h>		       /* signal() */

#ifdef __CLCC__			       /* Work around CenterLine clcc bogosity handling system header files. */

#ifdef __STDC__
#undef __STDC__
#endif

#define __STDC__ 1
#endif

#include <X11/Intrinsic.h>	       /* required by exec_rtn1.h (definition of type "Widget") */
#include <Xm/PushBG.h>		       /* required by exec_rtn1.h (definition of type "XmPushButtonCallbackStruct" */

#include "semops.h"		       /* required by fifo.h */
#include "some_utils.h"		       /* required by fifo.h */
#include "hash.h"		       /* required by fifo.h */
#include "fifo.h"
#include "desc_struct.h"	       /* required by exec_rtn.h */
#include "exec_rtn1.h"		       /* parent2child FIFO object. */
#include "safe.h"

/******************************************************************************
 * FUNCTION:	safe_int2string
 *	Convert an integer into a character string.
 ******************************************************************************/
void            safe_int2string (int val, char buf[])
{
	int             num;	       /* A modifiable copy of val. */
	int             idx = 0;       /* Index into buf */
	int             digits = 0;    /* Number of decimal digits required to represent an integer. */
	int             digitnum;      /* Left to right (most significant to least significant) offset of the current decimal
				        * digit. */
	int             power_of_10;   /* 10 raised to an integral exponent. */
	int             exponent;      /* The integral exponent to raise 10 to. */

	num = val;
	do			/* count the number of digits you need */
	{
		++digits;
		num /= 10;
	} while (num != 0);

	num = val;

/*
 * Build the string from the most significant digit, to the least significant
 * digit.
 */
	for (digitnum = digits; digitnum > 0; digitnum--)
	{
		power_of_10 = 1;
		for (exponent = 0; exponent < (digitnum - 1); exponent++)
			power_of_10 *= 10;

	/*
	 * Convert to a digit character, assuming the value of the character
	 * '1' == (int)'0' + 1
	 */
		buf[idx] = '0' + (num / power_of_10);
		num %= power_of_10;	/* 359 becomes 59, for example. */
		++idx;
	}
	buf[idx] = 0;
}

/******************************************************************************
 * FUNCTION:	safe_int2string_rj
 *	(Right Justified version of safe_int2string)
 *	Convert an integer into a character string.  Right-justify the string
 *	in the specified field width.  The function is "safe_" because it
 *	contains no writes to static data, and has no other side effects,
 *	and is therefore -- reentrant.  It is "safe_" to call this function
 *	from a signal handler (registered with the signal() function).
 ******************************************************************************/
void            safe_int2string_rj (int val, char buf[], int fieldwidth)
{
	int             num;	       /* A modifiable copy of val. */
	int             idx = 0;       /* Index into buf */
	int             digits = 0;    /* Number of decimal digits required to represent an integer. */
	int             digitnum;      /* Left to right (most significant to least significant) offset of the current decimal
				        * digit. */
	int             power_of_10;   /* 10 raised to an integral exponent. */
	int             exponent;      /* The integral exponent to raise 10 to. */
	int             num_blanks;    /* number of blanks (' ') to insert before each integer string written to buf. */

	num = val;
	do			/* count the number of digits you need */
	{
		++digits;
		num /= 10;
	} while (num != 0);

	num_blanks = fieldwidth - digits;

	for (idx = 0; idx < num_blanks; idx++)
		buf[idx] = ' ';

	num = val;

/*
 * Build the string from the most significant digit, to the least significant
 * digit.
 */
	for (digitnum = digits; digitnum > 0; digitnum--)
	{
		power_of_10 = 1;
		for (exponent = 0; exponent < (digitnum - 1); exponent++)
			power_of_10 *= 10;

	/*
	 * Convert to a digit character, assuming the value of the character
	 * '1' == (int)'0' + 1
	 */
		buf[idx] = '0' + (num / power_of_10);
		num %= power_of_10;	/* 359 becomes 59, for example. */
		++idx;
	}
	buf[idx] = 0;
}

/******************************************************************************
 * FUNCTION:	SAFE_STRLEN
 *****************************************************************************/
int             safe_strlen (const char buf[])
{
	int             len = 0;

	while (buf[len])
		++len;
	return (len);
}

/******************************************************************************
 * FUNCTION:	SAFE_STRCPY
 *****************************************************************************/
int             safe_strcpy (char dest[], const char src[])
{
	int             idx = 0;

	while (src[idx])
	{
		dest[idx] = src[idx];
		++idx;
	}
	dest[idx] = '\0';
	return (idx);		/* Returns the length of the copied string. */
}


/******************************************************************************
 * FUNCTION:	TIMEOUT / TIMEOUT_CHILD
 *
 *	Catches SIGALRM signals
 *	Functionally equivalent to:
 *		"send2parent (parent2child, SRV_TIMEOUT, "TIMEOUT");"
 *
 *	It works, but for very sneaky reasons:  BEWARE
 *
 *	Note: timeout() spawns timeout_child(), so that timeout_child() will
 *	have a different process id than the process that caught the signal.
 *
 *	The reason you need a new pid, is so that you will BLOCK when you
 *	call sem_wait() -- sem_wait() uses advisory record locks on
 *	a temp file -- it is possible that the main execution thread of the
 *	process that caught the signal, already had access to parent2child, and
 *      therefore, would not block when requesting a lock. (Remember, signal
 *	handlers are a new execution thread WITHIN an existing process.)  You
 *	cannot write to the FIFO safely, unless you do so as a new process.
 *
 *	Another sneaky thing:
 *	The SRV_TIMEOUT command sendsa process ID to the server, so the server
 *	can send back a REPLY!  make sure you send the proccess ID of the
 *	process that caught the SIGALRM signal -- not the PID of the child
 *	process sending the message.
 *****************************************************************************/
static void     timeout_child (int signo, int parent_pid)
{
	int             command = (int) SRV_TIMEOUT;

	char            buf[MSG_HEADER_SIZ + 7 + 1];	/* Message header, the text "TIMEOUT", and a NULL terminator. */
	int             idx = 0;       /* Index into buf */
	static char    *timeoutmsg = "\nIn timeout signal handler, received SIGALRM\n";	/* const, but prototype for write() on
											 * SunOS 4.1.x does not have const in the
											 * prototype. */
	static char    *timeout_text = "TIMEOUT";	/* const, but prototype for write() on SunOS 4.1.x does not have const in
							 * the prototype. */

	write (STDOUT_FILENO, timeoutmsg, safe_strlen (timeoutmsg));

	safe_int2string_rj (parent_pid, &buf[idx], INTLEN);
	idx += INTLEN;
	buf[idx] = ' ';
	++idx;

	safe_int2string_rj (command, &buf[idx], INTLEN);
	idx += INTLEN;
	buf[idx] = ' ';
	++idx;

	safe_int2string_rj (safe_strlen (timeout_text), &buf[idx], INTLEN);
	idx += INTLEN;
	buf[idx] = ' ';
	++idx;

	safe_strcpy (&buf[idx], timeout_text);

/*
 * CRITICAL: remember, the parent2child fifo has multiple writers.
 *
 * sem_wait() and sem_signal write to no static or global data, and the only
 * function they call is fcntl(); fcntl() is listed as a "safe" system call
 * in POSIX.1.  Therefore, sem_wait() and sem_signal() are safe.
 */
	sem_wait (parent2child->semaphore);
	if (write (parent2child->fd, buf, safe_strlen (buf)) < 0)
	{
		perror ("write() in timeout()");
	}
	sem_signal (parent2child->semaphore);

	write (STDOUT_FILENO, "\"", 1);
	write (STDOUT_FILENO, buf, safe_strlen (buf));
	write (STDOUT_FILENO, "\"\n", strlen ("\"\n"));

	exit (0);
}
void            timeout (int signo)
{
	int             parent_pid = getpid ();
	int             child_pid;

	if ((child_pid = fork ()) == -1)
	{

	/*
	 * perror() and util_abort() are not re-entrant, but let the guy say
	 * his dying words.
	 */
		perror ("fork() in timeout()");
		util_abort (__LINE__, __FILE__, "fork() failed in timeout() for process %d\n", getpid ());
	}

	/* Do the "real" work in a spawned process.  Do not wait for child to return. */
	if (child_pid == 0)
		timeout_child (signo, parent_pid);

	signal (SIGALRM, timeout);	/* Re register yourself for the next SIGALRM signal. */
}

/******************************************************************************
 * FUNCTION:	SIGCHLD_HANDLER
 *	Simply prints a message telling you that a SIGCHLD signal was
 *	received.
 *****************************************************************************/
void            sigchild_handler (int signo)
{
	char           *part1 = "Process ";	/* const, but prototype for write() on SunOS 4.1.x does not have const in the
						 * prototype. */
	char            part2[INTLEN + 1];
	char           *part3 = " received signal ";	/* const, but prototype for write() on SunOS 4.1.x does not have const in
							 * the prototype. */
	char            part4[INTLEN + 1];	/* const, but prototype for write() on SunOS 4.1.x does not have const in the
						 * prototype. */
	char           *part5 = " (SIGCHLD).\n";


	write (STDOUT_FILENO, part1, safe_strlen (part1));
	safe_int2string (getpid (), part2);
	write (STDOUT_FILENO, part2, safe_strlen (part2));
	write (STDOUT_FILENO, part3, safe_strlen (part3));
	safe_int2string (signo, part4);
	write (STDOUT_FILENO, part4, safe_strlen (part4));
	write (STDOUT_FILENO, part5, safe_strlen (part5));

	signal (SIGCHLD, sigchild_handler);
}

/******************************************************************************
 * FUNCTION:	SIGPIPE_HANDLER
 *	Used in FIFO.c to let you know that one of the ends of a pipe died.
 *****************************************************************************/
void            sigpipe_handler (int signo)
{

/*
 * All of the following static strings are READ ONLY.  The "const" qualifier
 * was removed, because the prototype for write() on SunOS 4.1.3 did not
 * specify a const pointer for the second parameter.
 */
	static char    *part1 = "Process ";
	char            part2[INTLEN + 1];
	static char    *part3 = " caught SIGPIPE signal.  This usually means that the\n";
	static char    *part4 = "reader process at the end of a pipe or FIFO has died.\n";
	static char    *part5 = "Actual signal number passed to this handler == ";
	char            part6[INTLEN + 1];
	static char    *part7 = ".\n";


	write (STDOUT_FILENO, part1, safe_strlen (part1));
	safe_int2string (getpid (), part2);
	write (STDOUT_FILENO, part2, safe_strlen (part2));
	write (STDOUT_FILENO, part3, safe_strlen (part3));
	write (STDOUT_FILENO, part4, safe_strlen (part4));
	write (STDOUT_FILENO, part5, safe_strlen (part5));
	safe_int2string (signo, part6);
	write (STDOUT_FILENO, part6, safe_strlen (part6));
	write (STDOUT_FILENO, part7, safe_strlen (part7));
}
