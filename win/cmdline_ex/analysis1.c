#undef _POSIX_SOURCE		       /* This file uses shared memory calls, which is not POSIX.1-1990 compliant. */
/*******************************************************************************
 * Program Name:	analysis.c
 * Written Date:	Oct. 23, 1992
 * Modified Date:	Nov. 18, 1992
 *******************************************************************************
 * $Date: 1994/08/21 00:58:25 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/cmdline_ex/RCS/analysis1.c,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: analysis1.c,v $
 * Revision 1.65  1994/08/21  00:58:25  franklin
 * According to ANSI/ISO 9899-1990, fputs() does NOT have to return the number
 * of bytes it wrote.  You cannot (in a portable way) recover from fputs()
 * being interrupted (hopefully, the guy who implemented fputs() took care
 * of this for you. ).
 *
 * Revision 1.64  1994/08/21  00:26:28  franklin
 * indent.
 *
 * Revision 1.63  1994/08/21  00:01:52  franklin
 * Remove the unused "para[5]" variable.
 *
 * Revision 1.62  1994/08/13  18:59:29  franklin
 * Remove unused global "para[]"
 *
 * Revision 1.61  1994/08/12  23:47:02  franklin
 * More attempts to locate and fix the TIMEOUT bug.  The error seems to be
 * that an incorrect offset it used when reading the value of the GTIME_
 * (referenced by CHECK in timing.des) node.
 *
 * Revision 1.60  1994/08/12  15:57:59  franklin
 * Fix printf()s
 *
 * Revision 1.59  1994/08/12  05:04:46  franklin
 * Try to recover from interrupted writes to a file
 *
 * Revision 1.58  1994/08/12  00:29:48  franklin
 * WARNING:
 * The file checked in to RCS as version 1.57 of this file
 * is actually a COPY OF version 1.55!  This version (1.58
 * contains the intended changes:
 * 1. Force writes to  the S_Output file immediately (no buffering).
 * 2. Null terminate numerous strings that previously had not been --
 *    because strncpy() does NOT copy the NULL string terminator.
 * 3. Attempted to fix the TIMEOUT mechanism.  It does work on occasion, at
 *    other times it dumps core!
 *
 * Revision 1.56  1994/08/10  19:02:59  franklin
 * 1. Replace message queue "msgid" (had a key value of MSGKEY) with a message
 *    from the timeout() signal handler, to the FIFO package.
 * 2. Identify the hardcoded constant "39" as being the ASCII escape (ESC)
 *    character.
 * 3. Replaced escaped newlines, with ANSI/ISO C string concatenation.
 *
 * Revision 1.55  1994/08/06  22:20:14  franklin
 * Replace Blink_Window() with client_blink_window()
 * Replace Bell() with clientXBell().
 *
 * Revision 1.54  1994/08/06  18:53:46  franklin
 * Remove calls to sem_close(); it is not needed by the new
 * semaphore implementation.
 *
 * Revision 1.53  1994/08/05  23:10:28  franklin
 * Use MAX_NODE_NAME_LEN instead of hardcoded constant 132.
 *
 * Revision 1.52  1994/08/05  18:10:22  franklin
 * exec_rtn1.h now requires hash.h and fifo.h to get the definition
 * for parent2child and child2parent.
 *
 * Revision 1.51  1994/08/04  17:40:41  franklin
 * Add #includes for cchk_missing_<standard include>.h in order
 * to get prototypes that CodeCheck doesnt think are there.
 *
 * Revision 1.50  1994/08/03  17:29:37  franklin
 * Get prototype for time() from time.h
 *
 * Revision 1.49  1994/08/03  16:29:02  franklin
 * Changed Exec_Run2() -> exec_run2; Execution_Proc() -> execution_proc()
 * E prefix is reserved by errno.h
 *
 * Revision 1.48  1994/08/03  16:13:23  franklin
 * The Abraxas Software CodeCheck tool "posix.cc" rules file said that the
 * identifiers beginning with "S_" had to be preceeded by $undef, to eliminate
 * the possibility of unintended macro expansions.  The tool gave no other
 * information; and I, for the life of me, cannot figure out why it is
 * complaining.  The following #undef statements do not seem to bother any of
 * the C compilers I am using, so I guess it wont hurt anything to put them
 * here.  Malcolm 8/2/94
 *
 * Revision 1.47  1994/08/02  18:16:49  franklin
 * Changed isempty() -> itisempty() (prefix "is" is reserved by ctype.h)
 *
 * Revision 1.46  1994/08/02  13:38:32  franklin
 * EQUAL -> ISEQUAL (E prefix is reserved by ANSI)
 *
 * Revision 1.45  1994/08/02  00:29:56  franklin
 * Change top_of_stack to ttop_of_stack, because prefix "to" is reserved by
 * ctype.h
 *
 * Revision 1.44  1994/07/21  13:07:28  franklin
 * Fix printf() format specifier.  It was trying to use an integer as a char
 * pointer ( Using "%s" for an int.  Very bad.)  This crashed the tool on
 * Solaris 2.3 compiled w/ gcc.
 *
 * Revision 1.43  1994/07/01  17:36:57  franklin
 * Flush the output to the log file.  This helps you find out
 * what the language processor was doing before it started
 * acting strange.
 *
 * Revision 1.42  1994/06/06  23:05:59  franklin
 * Use a variable named "msgid" when referencing queue MSGKEY, and
 * use msgid1 when referencing MSGKEY1.  MSGKEY handles graphics,
 * and MSGKEY1 handles communications between parallel Descartes
 * sub-processes.
 *
 * Revision 1.41  1994/06/02  17:15:32  franklin
 * Enable stricter type checking when running the CenterLine "clcc" in
 * K&R compatibility mode (-Xa switch) by re-defining __STDC__ after processing
 * the non-ansi SunOS system include files.
 *
 * Revision 1.40  1994/05/24  18:41:04  franklin
 * Set pointers to NULL after you have free()d them.  This
 * is an attempt to keep from referencing free()d memory.
 *
 * Revision 1.39  1994/05/24  01:59:15  franklin
 * ObjectCenter also detected "defaults" instead of "default" inside
 * of two switch() statements.
 *
 * Revision 1.38  1994/05/24  01:57:11  franklin
 * ObjectCenter 2.0.2 detected 5 "auto" variables that were assigned
 * values which were never used (the variables were useless).
 * CLCC did not detect these.  ObjectCenter detected them when I
 * loaded source (rather than object).
 *
 * Revision 1.37  1994/05/23  22:56:13  franklin
 * Remove obvious comments and extra whitespace.
 *
 * Revision 1.36  1994/05/23  22:45:12  franklin
 * 1. Remove useless and redundant comments.
 * 2. Make several globals "static", because they are no longer referenced
 *    from outside this file.
 *
 * Revision 1.35  1994/05/23  20:25:31  franklin
 * Delete unused variables and commented-out code.
 *
 * Revision 1.34  1994/05/16  23:22:29  franklin
 * Get prototype for signal(), and the definition of SIGALRM
 * from <signal.h>.  Note that this is an ANSI/ISO C
 * feature.
 *
 * Revision 1.33  1994/05/16  21:07:49  franklin
 * Use the revised sem_create() function, which needs no arguments and
 * performs its own exception handling.
 *
 * Remove extraneous "errno = 0;" statements.
 *
 * Revision 1.32  1994/05/06  16:56:03  franklin
 * Use perror() instead of printf() to report failed system calls.
 *
 * Revision 1.31  1994/05/03  01:00:16  franklin
 * Just re-run through "indent".
 *
 * Revision 1.30  1994/05/02  17:42:23  franklin
 * unistd.h does NOT replace sys/stat.h.  You still need to #include it too!
 *
 * Revision 1.29  1994/05/02  16:55:40  franklin
 * 1. Now uses POSIX <unistd.h> instead of <sys/types.h>,
 *    <sys/file.h> and <sys/stat.h>.
 * 2. Changed the third parameter to fseek() calls from a
 *    non-standard "L_SET" macro, and hardcoded constants,
 *    to the following ANSI/ISO C values:
 *    From     | To
 *    ---------+-------
 *    L_SET    | SEEK_SET
 *    0        | SEEK_SET
 *    1        | SEEK_CUR (I do not think this was used in this file.)
 *    2        | SEEK_END
 *
 * Revision 1.28  1994/05/02  05:06:26  franklin
 * Include semops.h for the declaration of semaphore operations.
 *
 * Revision 1.27  1994/04/14  23:07:03  franklin
 * 1. Removed a couple of auto variables which were declared
 *    but never used.
 * 2. ** BIG BUG ** In function S_Parallel(): Variable P_activity was
 *    supposed to be set to a value returned from shmat() BUT the statement
 *    used a logical-equal "==" operator instead of an assignment "="
 *    operator.  ObjecCenter/clcc detected this by reporting that the result
 *    of the "==" operation was not used.
 *
 * Revision 1.26  1994/04/14  22:17:20  franklin
 * Remove #include alert_dcl.h.  The information once there is now in
 * share_rtn.h and share_rtn.c
 *
 * Revision 1.25  1994/04/14  20:10:42  franklin
 * Removed Get_Module_Name().  ObjectCenter/clcc discovered that
 * this function was never called.
 *
 * Revision 1.24  1994/04/14  20:05:15  franklin
 * Deleted function Search_Sub_Module().  ObjetcCenter/clcc found that this
 * function was never called.
 *
 * Revision 1.23  1994/04/14  19:31:22  franklin
 * Remove A_Module_Call1().  It was never called from anywhere.
 * Detected by ObjectCenter/clcc
 *
 * Revision 1.22  1994/04/14  18:23:44  franklin
 * Suppress ObjectCenter warnings about "static variable rcsid unused".
 *
 * Revision 1.21  1994/04/12  08:57:51  franklin
 * Dont use an end-of-comment (star slash) in the RCS Checkin log.  gcc
 * starts reading the #if 0 bloc in the log if you do.
 *
 * Revision 1.20  1994/04/12  08:49:51  franklin
 * Allocate enough storage for a string AND its null terminator.
 * CRITICAL:  I may have goofed up when converting
 *     *Current_output->data = NL; -- Or some other value
 * to
 *     Current_output->data[0] = NL;
 *     Current_output->data[1] = '\0';
 * The old code only allocated 1 byte of memory, stored a value in it, and
 * may or may not have treated single-char values differently than strings.
 *
 * Revision 1.19  1994/04/12  07:17:00  franklin
 * Re-run through "indent".
 *
 * Revision 1.18  1994/04/12  07:12:47  franklin
 * Re-order the functions so that function definitions precede
 * uses of the functions.
 *
 * Revision 1.17  1994/04/11  23:23:04  franklin
 * Escaped the backslash ('\') in the definition of the "WORD" macro.
 *
 * Revision 1.16  1994/04/11  23:10:28  franklin
 * Intermediate checkpoint.  I am re-ordering the appearance of
 * functions, so that function definitions  appear befor their
 * use.
 *
 * Revision 1.15  1994/04/11  22:47:16  franklin
 * Delete function declarations in the variable declarations
 * of other functions.  We need to read these declarations
 * from the appropriate ".h" files.
 *
 * Revision 1.14  1994/04/09  23:49:48  franklin
 * Move the declarations of globals used in wid1.c to analysis1.h.
 *
 * Revision 1.13  1994/04/09  23:05:28  franklin
 * Re-run through "indent".
 *
 * Revision 1.12  1994/04/09  22:59:20  franklin
 * Add "static" qualifier to all functions which are only called from
 * within this file.
 *
 * Revision 1.11  1994/04/09  22:37:37  franklin
 * Read wid1.h to get declarations of the functions and globals used from
 * wid1.c
 *
 * Revision 1.10  1994/04/09  22:00:23  franklin
 * Remove unused #defines.  Get the declarations of functions and globals
 * from exec_rtn1.c, by reading exec_rtn1.h.
 *
 * Revision 1.8  1994/04/08  06:37:44  franklin
 * Move the definition of BACKWARD and FORWARD into analysis1.h
 * along with the prototype for Execution_Proc()
 *
 * Revision 1.7  1994/04/08  05:42:46  franklin
 * Get the declaration of Get_File_Stat() from share_rtn.h
 *
 * Revision 1.6  1994/03/30  07:48:03  franklin
 * Ran through the SunOS "indent" program.
 *
 ******************************************************************************/
#endif
static char    *rcsid = "@(#) $Id: analysis1.c,v 1.65, h4_3_8 1994/08/21 00:58:25 franklin Exp $";

#include <stdlib.h>
#include "cchk_missing_stdlib.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>		       /* POSIX replacement for <sys/file.h>. */
#include "cchk_missing_unistd.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <signal.h>		       /* Definition of SIGALRM */
#include "cchk_missing_signal.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <time.h>		       /* time() */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/msg.h>

/******************************************************************************
 * NOTE TO FUTURE MAINTAINERS USING CenterLine "clcc" COMPILER:
 *
 * Nearly all the SunOS 4.x Operating System include files (<sys/xxx.h>)
 * cause compilation errors under a strict ANSI/ISO compiler running in anal-
 * retentive mode such as CenterLine "clcc".  In order to get these to compile,
 * with clcc, you have to pass the  -Xa (K&R C compatibility switch) to the
 * compiler.  BUT (get this) when we do this, the CenterLine preprocessor
 * #defines __STDC__ to 0 (zero); when this happens, we dont see the vararg
 * prototypes for the X functions -- and get warning messages for calling them
 * with different numbers of arguments.  On top of all this noise, we DONT GET
 * all the ANSI/ISO C type checking that we could have.
 *
 * WORKAROUND:
 *      When compiling with clcc, #define __STDC__ to 1 AFTER #including the
 * system header files you need (<sys/xxx.h>), and hopefully before #including
 * any of the header files you (or I, or Yu-Kuh, or someone else) wrote.
 * Here is the code:
 ******************************************************************************/

#ifdef __CLCC__

#ifdef __STDC__
#undef __STDC__
#endif

#define __STDC__ 1
#endif

/* add April  1992  */
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <Xm/PushB.h>

#include "desc_struct.h"
#include "share_rtn.h"
#include "analysis1.h"
#include "mesg.h"
#include "wid1.h"		       /* Definition of mesg_d */
#include "some_utils.h"
#include "hash.h"
#include "fifo.h"
#include "exec_rtn1.h"
#include "semops.h"
#include "safe.h"		       /* timeout() signal handler for SIGALRM */
/* #include "purify.h" */

/*
 * The Abraxas Software CodeCheck tool "posix.cc" rules file said that the
 * following identifirers had to be preceeded by #undef, to eliminate the
 * possibility of unintended macro expansions.  The tool gave no other
 * information; and I, for the life of me, cannot figure out why it is
 * complaining.  The following #undef statements do not seem to bother any of
 * the C compilers I am using, so I guess it wont hurt anything to put them
 * here.  Malcolm 8/2/94
 */
#undef S_Current_Node
#undef S_Root_Stack
#undef S_Input_File
#undef S_Output_File
#undef S_Hoare_Root_Dummy
#undef S_Temp_Stack
#undef S_Current_Stack
#undef S_Check_Module
#undef S_Find_Corr_Match1
#undef S_Direct_Product1
#undef S_Parallel
#undef S_Primitives
#undef S_GTimer
#undef S_Timer
#undef S_Delay
#undef S_Receive
#undef S_Send
#undef S_Primitives2
#undef S_Literal
#undef S_Module_Call
#undef S_Find_Corr_Match
#undef S_Find_Corr_Match2
#undef S_Direct_Product
#undef S_Temp_Stack
#undef S_Discriminated_Union
#undef S_Successful_Element
#undef S_Failed_Element
#undef S_Sequence
#undef S_Sequence_No
#undef S_Node_Type_Check
#undef S_Input_File
#undef S_Output_File

#define		NL	0x0a	       /* carriage return */
#define		NP	0x0b	       /* new page */

#define		DIGIT	"0123456789"
#define		LETTER	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

/*
 * Note: I had to replace '\' with '\\' to have the backslash included in the
 * string; otherwise, it just escaped the open-bracket. -- Malcolm Franklin,
 * 4/11/94
 */
#define		WORD	" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\
0123456789!@#$%^&*()_+|-=\\[]{},./;'`<>?:~\""

static int      shmid_p[3];	       /* Shared memory id array */
static int      server;		       /* Semaphore. */

/* addd   April   1992    */
static struct Template_Node *S_Hoare_Root_Dummy;
static struct Template_Node *S_Current_Node;
static struct Stack_Node *S_Root_Stack;/* save for the stack free in Stack_Free() */
static struct Stack_Node *S_Temp_Stack;/* save for the stack free in Stack_Free() */
static struct Stack_Node *S_Current_Stack;	/* save for the stack free in Stack_Free() */

/* Note: Stack_Free() is in exec_rtn1.c */

static int      recursion = NO;

struct pro_table		       /* Process table */
{
	char           *root_node;
	char           *Input_buffer;
	int             pid;
};
static struct pro_table pcb[5];

int             p_cnt;		       /* Process count.  I think it is the number of parallel processesn S_Parallel().  Used
				        * here and in exec_rtn1.c */
static int      no_of_elements;
static int      client;		       /* Semaphore to enforce syncronization between communicating parallel processes. */

struct data_node
{
	char           *data;
	struct data_node *next;
	struct data_node *front;
};
static struct data_node *Output_data,
               *Current_output,
               *Wk_data,
               *Current_wk;	       /* for concurrency */

static short    Output_data_c_ptr,
                W_Output_data_c_ptr;
FILE           *retry_fopen (const char *fname, const char *mode)
{
	FILE           *retval;

	if ((retval = fopen (fname, mode)) == NULL)
	{
		perror ("fopen()");
		printf ("\nFailure:  fopen (\"%s\", \"%s\") returned NULL.\n\n",
			fname ? fname : "(Null)", mode ? mode : "(Null)");
	}
	else
	{
		if (ferror (retval))
		{
			perror ("fopen()");
			printf ("\nferror() detected an error after: fopen (\"%s\", \"%s\");\n\n",
				fname ? fname : "(Null)", mode ? mode : "(Null)");
			clearerr (retval);
		}

	}
	return (retval);
}
char           *retry_fgets (char *buf, int bytes_requested, FILE * fp)
{
	int             done = FALSE;
	char           *retval;
	static const int num_retries = 10;
	int             retry_count = num_retries;

	*buf = '\0';
	do
	{
		if (retry_count < num_retries)
			printf ("Trying again to read in retry_fgets.  num_retries == %d\n\t", num_retries);
		clearerr (fp);
		retval = fgets (buf, bytes_requested, fp);
		if (ferror (fp))
		{
			perror ("ferror() after fgets () in retry_fgets()");
			printf ("\terrno = %d bytes_requested = %d buf = \"%s\".\n", errno, bytes_requested, buf);
			fflush (stdout);
		}
		--retry_count;
	} while (retry_count && ferror (fp));

	return (retval);
}


int             retry_fputs (char *buf, FILE * fp)
{
	int             retval;

	clearerr (fp);
	retval = fputs (buf, fp);
	if ((retval < 0) || ferror (fp))
	{
		perror ("fputs()");
		printf ("Error while trying to write \"%s\" to file pointer 0x%X\n", buf ? buf : "(Null)");
	}
	return (retval);
}

int             retry_fputc (int ch, FILE * fp)
{
	int             status = 0;
	int             retry_count = 10;

	while ((retry_count) && ((status = fputc (ch, fp)) == EOF))
	{
		perror ("fputc() in retry_fputc()");
		--retry_count;
	}
	if (status == EOF)
		util_abort (__LINE__, __FILE__, "Could not write '%c' to the file.\n", ch);
	return (status);
}

/*******************************************************************************
 * FUNCTION:	ADD_CARRIAGE_RETURN
 *	Add a  carriage return  to the output file of parameters.  Without it,
 *	analysis can not reach the end of file; analysis will fail.  Call this
 *	function after each value you write to S_Output_File.
 ******************************************************************************/
static void     add_carriage_return (FILE * S_Output_File_f_ptr)
{
	retry_fputc ('\n', S_Output_File_f_ptr);
}


static void     Output_Decision (void) /* write into file system  */
{
	if (Trace_Flag)
	{
		Display_Exec_Msg (User_Msg);
	}
	if (Log_Flag)
	{
		retry_fputs (User_Msg, Log_File.f_ptr);
		fflush (Log_File.f_ptr);
	}
}

static void     Locate_Stack_Element (void)
{
/* at least 1 stack element associated with current template node */
	if (Current_Node->ttop_of_stack)
	{
	/* point down to the previous stack element in the same stack */
		Temp_Stack->prev_stack_element = Current_Node->ttop_of_stack;
		sprintf (User_Msg, "\n !!!assign value to prev_stack_element\n");
		Output_Decision ();
	}

	Current_Stack->forward_stack_ptr = Temp_Stack;
	Temp_Stack->backward_stack_ptr = Current_Stack;
	Temp_Stack->template_node_ptr = Current_Node;
	Current_Node->ttop_of_stack = Temp_Stack;
	Current_Stack = Temp_Stack;
}



static void     Adjust_Stack_and_Input_Ptrs (void)
{
/* free the stack */
	Temp_Stack = Current_Node->ttop_of_stack;
	Current_Stack = Current_Node->ttop_of_stack->backward_stack_ptr;
	Current_Stack->forward_stack_ptr = NULL;

/* Adjust the template stack pointer */
	if (Current_Node->ttop_of_stack->prev_stack_element)
	/* more stack elements */
		Current_Node->ttop_of_stack = Current_Node->ttop_of_stack->prev_stack_element;
	else
		Current_Node->ttop_of_stack = NULL;

/* <<  Adjust the input string pointer backward  >> */
	Input_File.c_ptr = Temp_Stack->begin;
	sprintf (User_Msg, " <- Backward input buffer pointer at location %d\n",
		 Input_File.c_ptr);
	Output_Decision ();
	sprintf (User_Msg, " ** Free a stack element at Node %s; adjust stack & "
		 "input pointers.\n",
		 Current_Node->name);
	Output_Decision ();
	free (Temp_Stack);
	Temp_Stack = NULL;
}



static void     Adjust_Stack_and_Output_Ptrs (void)
{
/* free the stack */
	Temp_Stack = Current_Node->ttop_of_stack;
	Current_Stack = Current_Node->ttop_of_stack->backward_stack_ptr;
	Current_Stack->forward_stack_ptr = NULL;

/* Adjust the template stack pointer */
	if (Current_Node->ttop_of_stack->prev_stack_element)
	/* more stack elements */
		Current_Node->ttop_of_stack = Current_Node->ttop_of_stack->prev_stack_element;
	else
		Current_Node->ttop_of_stack = NULL;

/* <<  Adjust the input string pointer backward  >> */
	if (return_flag)
	{
		if (concurrent)
			Output_data_c_ptr = Temp_Stack->begin;
		else
			Output_File.c_ptr = Temp_Stack->begin;
	}
	else
	{
		if (concurrent)
			W_Output_data_c_ptr = Temp_Stack->begin;
		else
			W_Output_File.c_ptr = Temp_Stack->begin;
	}
	sprintf (User_Msg, " <- Backward input buffer pointer at location %d\n",
		 Output_File.c_ptr);
	Output_Decision ();
	sprintf (User_Msg, " ** Free a stack element at Node %s; adjust stack & \
input pointers.\n",
		 Current_Node->name);
	Output_Decision ();
	free (Temp_Stack);
	Temp_Stack = NULL;
}

/*
 * ....................................................................
 * A_Abstract_Exec	for terminal match node (DP) treated as Literal
 * ....................................................................
 */

static void     A_Abstarct_Exec (void)
{
	if (Animate_Flag)
	{
	/* Animate the node edge left to the node; from top to bottom */
		Inverse_Node_Edge (Current_Node, FORWARD);
	/* Whiten the node chars; blacken background */
		Inverse_Tree_Node (Current_Node);
	}

	switch (Activity)
	{
		case FIRST:
			sprintf (User_Msg, "__(Abstract_M_first) Node %s\n", Current_Node->name);
			Output_Decision ();

		/* push a stack element for template node */
			Temp_Stack = Stack_Allocation ();
		/* set up the starting point of the matching */
			Temp_Stack->begin = Input_File.c_ptr;
			Temp_Stack->from_tree_type = ANALYSIS;

			if (!strncmp (Input_File.buffer + Input_File.c_ptr, Current_Node->name,
				      strlen (Current_Node->name)))
			{	/* matched */
				sprintf (User_Msg, " => Successful matching at node %s with input string\n",
					 Current_Node->name);
				Output_Decision ();

			/* <<  Adjust the input string pointer forward  >> */
				Input_File.c_ptr += (strlen (Current_Node->name));
				sprintf (User_Msg, " -> Forward input buffer pointer to location %d\n",
					 Input_File.c_ptr);
				Output_Decision ();
			/* set up the ending point of the matching */
				Temp_Stack->end = Input_File.c_ptr;

				Locate_Stack_Element ();
				clientXBell ();
				Activity = SUCCEED;
			}
			else
			{
				sprintf (User_Msg, " => Unsuccessful matching at node %s with input string\n",
					 Current_Node->name);
				Output_Decision ();
				free (Temp_Stack);	/* pop up the stack element */
				Temp_Stack = NULL;

				client_blink_window ();
				Activity = FAIL;
			}	/* else */

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

		/* adjust template node pointer to ancestor node */
			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}


		/* Note: back to its ancestor */
			sprintf (User_Msg, " << Back to Node %s\n", Current_Node->name);
			Output_Decision ();
			break;

		case NEXT:
			sprintf (User_Msg, "__(Abstract_M_next) Node %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

			Adjust_Stack_and_Input_Ptrs ();

			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			sprintf (User_Msg, " << Fail; Back to Node %s\n", Current_Node->name);
			Output_Decision ();

			client_blink_window ();
			Activity = FAIL;
			break;

		default:
			break;

	}			/* switch */
}


/*
 * ....................................................... A_Literal
 * .......................................................
 */

/* Utility used by A_Literal() */
static int      A_Literal_Test (void)
{
/* save the current input buffer pointer for non-matching situation */
	Input_File.s_ptr = Input_File.c_ptr;
	if (strncmp (Input_File.buffer + Input_File.c_ptr, Current_Node->name + 1,
		     strlen (Current_Node->name) - 2))
	{			/* not matched */
		return (0);
	}
	else
	{
		return (1);
	}
}

static void     A_Literal (void)
{

	if (Animate_Flag)
	{
		Inverse_Node_Edge (Current_Node, FORWARD);
		Inverse_Tree_Node (Current_Node);
	}

	switch (Activity)
	{
		case FIRST:
			sprintf (User_Msg, "__(AL_first) Literal %s\n", Current_Node->name);
			Output_Decision ();

		/* push a stack element for template node */
			Temp_Stack = Stack_Allocation ();
		/* set up the starting point of the matching */
			Temp_Stack->begin = Input_File.c_ptr;
			Temp_Stack->from_tree_type = ANALYSIS;

			if (A_Literal_Test ())
			{	/* matched */
				sprintf (User_Msg, " => Successful matching at node %s with input string\n",
					 Current_Node->name);
				Output_Decision ();

			/* <<  Adjust the input string pointer forward  >> */
				Input_File.c_ptr += (strlen (Current_Node->name) - 2);
				sprintf (User_Msg, " -> Forward input buffer pointer to location %d\n",
					 Input_File.c_ptr);
				Output_Decision ();

			/* set up the ending point of the matching */
				Temp_Stack->end = Input_File.c_ptr;

				Locate_Stack_Element ();

				clientXBell ();
				Activity = SUCCEED;
			}
			else
			{
				sprintf (User_Msg, " => Unsuccessful matching at node %s with input string\n",
					 Current_Node->name);
				Output_Decision ();
				free (Temp_Stack);	/* pop up the stack element */
				Temp_Stack = NULL;

				Input_File.c_ptr = Input_File.s_ptr;
				client_blink_window ();
				Activity = FAIL;
			}	/* else */
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

		/* adjust template node pointer to ancestor node */
			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

		/* Note: back to its ancestor */
			sprintf (User_Msg, " << Back to Node %s\n", Current_Node->name);
			Output_Decision ();
			break;

		case NEXT:
			sprintf (User_Msg, "__(AL_next) Literal %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

			Adjust_Stack_and_Input_Ptrs ();

			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			sprintf (User_Msg, " << Fail; Back to Node %s\n", Current_Node->name);
			Output_Decision ();

			client_blink_window ();
			Activity = FAIL;
			break;

		default:
			break;

	}			/* switch */
}

/*
 * ....................................................... Direct Product
 * .......................................................
 */

/* Utility used by A_Direct_Product() */
static int      A_Check_Reference (void)
{
	int             done = NO;

/* there are some default module calls */

	if (!strncmp (Current_Node->name, "NL", 2))	/* new line */
	{
	/* printf("NL %c %c \n",Input_File.buffer+Input_File.c_ptr, NL ); */
		if (*(Input_File.buffer + Input_File.c_ptr) == NL)
		{		/* matched */
			Input_File.c_ptr++;
			return (1);
		}
		else
		{
			return (0);
		}
	}
	else if (!strncmp (Current_Node->name, "DIGIT", 5))
	{
		if (strchr (DIGIT, *(Input_File.buffer + Input_File.c_ptr)))
		{
			Input_File.c_ptr++;
			return (1);
		}
		else
			return (0);
	}
	else if (!strncmp (Current_Node->name, "INTEGER", 7))
	{
		while (strchr (DIGIT, *(Input_File.buffer + Input_File.c_ptr)))
		{
			Input_File.c_ptr++;
			done = YES;
		}

		if (done)
			return (1);
		else
			return (0);
	}
	else if (!strncmp (Current_Node->name, "LETTER", 6))
	{
		if (strchr (LETTER, *(Input_File.buffer + Input_File.c_ptr)))
		{
			Input_File.c_ptr++;
			return (1);
		}
		else
			return (0);
	}
	else if (!strncmp (Current_Node->name, "WORD", 4))
	{
		if (strchr (WORD, *(Input_File.buffer + Input_File.c_ptr)))
		{
			Input_File.c_ptr++;
			return (1);
		}
		else
			return (0);
	}
	else if (!strncmp (Current_Node->name, "NULL", 4))	/* null */
	{
	/* printf("NL %c %c \n",Input_File.buffer+Input_File.c_ptr, NL ); */
		if (*(Input_File.buffer + Input_File.c_ptr) == NL)
		{		/* matched */
			return (1);
		}
		else
			return (0);
	}
	else
		return (0);	/* non-module call */
}


static void     A_Direct_Product (void)
{

	if (Current_Node->type & REFERENCE_NODE)
	{
	/* reference node not at level 1 */
		if (Current_Node->level_no != 1)
		{

			sprintf (User_Msg, "(ADP)_Node %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Node_Edge (Current_Node, FORWARD);
				Inverse_Tree_Node (Current_Node);
			}

			switch (Activity)
			{

				case FIRST:
					sprintf (User_Msg, "__(ADP_first)Node %s\n", Current_Node->name);
					Output_Decision ();

					Temp_Stack = Stack_Allocation ();
				/* set up the starting point of the matching */
					Temp_Stack->begin = Input_File.c_ptr;
					Temp_Stack->from_tree_type = ANALYSIS;

					if (!A_Check_Reference ())
					{
						sprintf (User_Msg, " => Unsuccessful matching with module call\n");
						Output_Decision ();
						free (Temp_Stack);
						Temp_Stack = NULL;

						client_blink_window ();
						Activity = FAIL;
					}
					else
					{
						sprintf (User_Msg, " => Successful matching with module call\n");
						Output_Decision ();

					/*
					 * <<  Adjust the input string
					 * pointer forward  >>
					 */
						sprintf (User_Msg, " -> Forward input buffer pointer to location %d\n",
							 Input_File.c_ptr);
						Output_Decision ();

					/*
					 * set up the ending point of the
					 * matching
					 */
						Temp_Stack->end = Input_File.c_ptr;

						Locate_Stack_Element ();

						clientXBell ();
						Activity = SUCCEED;
					}	/* else */

					if (Animate_Flag)
					{
						Inverse_Tree_Node (Current_Node);
						Inverse_Node_Edge (Current_Node, BACKWARD);
					}

				/* adjust template node pointers  */
					Prev_Node = Current_Node;
					Current_Node = Current_Node->ancestor;
					if (Animate_Flag)
					{
						Inverse_Tree_Node (Current_Node);
					}

				/*
				 * BACK TO ANCESTOR & INVERSE THE NODE WITH
				 * NODE EDGE
				 */
					sprintf (User_Msg, " << Back to Node %s\n", Current_Node->name);
					Output_Decision ();
					return;

				case NEXT:
					sprintf (User_Msg, "__(ADP_next)Node %s\n", Current_Node->name);
					Output_Decision ();
					if (Animate_Flag)
					{
						Inverse_Tree_Node (Current_Node);
						Inverse_Node_Edge (Current_Node, BACKWARD);
					}

					Adjust_Stack_and_Input_Ptrs ();

					Prev_Node = Current_Node;
					Current_Node = Current_Node->ancestor;

					if (Animate_Flag)
					{
						Inverse_Tree_Node (Current_Node);
					}
					sprintf (User_Msg, " << Fail; Back to Node %s\n", Current_Node->name);
					Output_Decision ();

					client_blink_window ();
					Activity = FAIL;
					return;

				default:
					break;

			}	/* switch */

		}		/* level_no != 1 */

	}			/* if */

/* ...........................................  */
/* other match nodes              */
/* ...........................................  */

	switch (Activity)
	{
		case FIRST:
			sprintf (User_Msg, "__(aDP_first) Direct Product %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Node_Edge (Current_Node, FORWARD);
				Inverse_Tree_Node (Current_Node);
				Inverse_Tree_Node (Current_Node);
			}

			Temp_Stack = Stack_Allocation ();
		/* set up the starting point of the matching */
			Temp_Stack->begin = Input_File.c_ptr;
			Temp_Stack->from_tree_type = ANALYSIS;

			Locate_Stack_Element ();

		/* point to the first immediate sibling */
			Current_Node = Current_Node->level_point;
			sprintf (User_Msg, " >> Go to Node %s\n", Current_Node->name);
			Output_Decision ();
			break;

		case NEXT:
			sprintf (User_Msg, "__(aDP_next) Direct Product %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Node_Edge (Current_Node, FORWARD);
				Inverse_Tree_Node (Current_Node);
				Inverse_Tree_Node (Current_Node);
			}

		/*
		 * get the last processed template node which is the last
		 * sibling; but Discriminated Union is different from this
		 */

		/*
		 * Method 1: indirectly get the last processed template node
		 * Temp_Node = Current_Node->level_point; while (
		 * Temp_Node->front )  { Temp_Node = Temp_Node->front; }
		 */
		/* Method 2: directly get the last processed template node */
			Temp_Node = Current_Node->ttop_of_stack->tcp_save->template_node_ptr;

			sprintf (User_Msg, " >> Go to the last processed %s under node %s\n",
				 Temp_Node->name, Current_Node->name);
			Output_Decision ();
			Current_Node = Temp_Node;
			break;

		case SUCCEED:
			sprintf (User_Msg, "__(aDP_succeed) Direct Product %s\n", Current_Node->name);
			Output_Decision ();

		/* set up the ending point of the matching */
			Current_Node->ttop_of_stack->end = Input_File.c_ptr;

			Output_Decision ();

		/*
		 * store the pointer which points to the last processed
		 * template node
		 */
			Current_Node->ttop_of_stack->tcp_save = Prev_Node->ttop_of_stack;

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			if (Prev_Node->front)
			{	/* more subnodes to process */

			/* point to the next immediate sibling */
				Current_Node = Prev_Node->front;
				Activity = FIRST;

				sprintf (User_Msg, " >> Succeed; Go to Node %s\n", Current_Node->name);
				Output_Decision ();

			}	/* if */
			else
			{	/* back to a ancestor node */
				if (Animate_Flag)
				{
					Inverse_Node_Edge (Current_Node, BACKWARD);
				}

				Prev_Node = Current_Node;
				Current_Node = Current_Node->ancestor;

				sprintf (User_Msg, " << Succeed; Back to Node %s\n", Current_Node->name);
				Output_Decision ();

				if (Animate_Flag)
				{
					Inverse_Tree_Node (Current_Node);
				}

			}	/* else */
			break;

		case FAIL:
			sprintf (User_Msg, "__(aDP_fail) Direct Product %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

		/* if the node is NOT the first immediate son  */
			if (Prev_Node != Prev_Node->ancestor->level_point)
			{

				Current_Node = Prev_Node->back;	/* !!!  */
				Activity = NEXT;

				sprintf (User_Msg, " ?? Try to check node %s\n", Current_Node->name);
				Output_Decision ();

			}	/* if */
			else
			{

				sprintf (User_Msg, " // All subnodes are tried; all of them failed\n");
				Output_Decision ();

				if (Animate_Flag)
				{
					Inverse_Node_Edge (Current_Node, BACKWARD);
				}

				Adjust_Stack_and_Input_Ptrs ();

				Prev_Node = Current_Node;
				Current_Node = Current_Node->ancestor;

				sprintf (User_Msg, " << Back to Node %s\n", Current_Node->name);
				Output_Decision ();

				if (Animate_Flag)
				{
					Inverse_Tree_Node (Current_Node);
				}

			}	/* else */
			break;

		default:
			break;

	}			/* switch */
}

/*
 * ....................................................... Discriminated
 * Union .......................................................
 */

static void     A_Discriminated_Union (void)
{
	switch (Activity)
	{
			case FIRST:
			sprintf (User_Msg, "__(ADU_first) Discriminated Union %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Node_Edge (Current_Node, FORWARD);
				Inverse_Tree_Node (Current_Node);
				Inverse_Tree_Node (Current_Node);
			}

			Temp_Stack = Stack_Allocation ();
		/* set up the starting point of the matching */
			Temp_Stack->begin = Input_File.c_ptr;
			Temp_Stack->from_tree_type = ANALYSIS;

			Locate_Stack_Element ();

		/* point to the first immediate sibling */
			Current_Node = Current_Node->level_point;

			sprintf (User_Msg, " >> Go to Node %s\n", Current_Node->name);
			Output_Decision ();
			break;

		case NEXT:
			sprintf (User_Msg, "__(ADU_next) Discriminated Union %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Node_Edge (Current_Node, FORWARD);
				Inverse_Tree_Node (Current_Node);
				Inverse_Tree_Node (Current_Node);
			}

		/* get the last processed template node */
			Temp_Node = Current_Node->ttop_of_stack->tcp_save->template_node_ptr;

			sprintf (User_Msg, " >> Go to the last processed %s under node %s\n",
				 Temp_Node->name, Current_Node->name);
			Output_Decision ();
			Current_Node = Temp_Node;
			break;

		case SUCCEED:
			sprintf (User_Msg, "__(ADU_succeed) Discriminated Union %s\n", Current_Node->name);
			Output_Decision ();

		/* set up the ending point of the matching */
			Current_Node->ttop_of_stack->end = Input_File.c_ptr;

			Output_Decision ();

		/*
		 * store the pointer which points to the last processed
		 * template node
		 */
			Current_Node->ttop_of_stack->tcp_save = Prev_Node->ttop_of_stack;

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

		/* back to a ancestor node */
			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;

			sprintf (User_Msg, " << Succeed; Back to Node %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}
			break;

		case FAIL:
			sprintf (User_Msg, "__(ADU_fail) Discriminated Union %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			if (Prev_Node->front)
			{	/* need to try to check another sibling subnode */
			/* point to the next immediate sibling */
				Current_Node = Prev_Node->front;
				Activity = FIRST;

				sprintf (User_Msg, " ?? Try to check node %s\n", Current_Node->name);
				Output_Decision ();

			}	/* if */
			else
			{

				sprintf (User_Msg, " // All subnodes are tried; none of them matched\n");
				Output_Decision ();

				if (Animate_Flag)
				{
					Inverse_Node_Edge (Current_Node, BACKWARD);
				}

				Adjust_Stack_and_Input_Ptrs ();

				Prev_Node = Current_Node;
				Current_Node = Current_Node->ancestor;

				sprintf (User_Msg, " << Back to Node %s\n", Current_Node->name);
				Output_Decision ();

				if (Animate_Flag)
				{
					Inverse_Tree_Node (Current_Node);
				}

			}	/* else */
			break;

		default:
			break;

	}			/* switch */
}

/* range (digit..digit)            */
static void     A_Successful_Element (void)
{
	if (Current_Node->ttop_of_stack->no_of_elements < Current_Node->lower)
	{
	/* point to the first immediate sibling */
		Current_Node->ttop_of_stack->no_of_elements++;
		Current_Node = Current_Node->level_point;
		Activity = FIRST;

		sprintf (User_Msg, " >>(Suc_1) Go to node %s\n", Current_Node->name);
		Output_Decision ();

	/*
	 * need some more work to check Dummy Node (future work)
	 * A_Sequence_Dummy();
	 */
	}
	else if (Current_Node->ttop_of_stack->no_of_elements == Current_Node->lower)
	{
		if (Animate_Flag)
		{
			Inverse_Node_Edge (Current_Node, BACKWARD);
		}
	/* !! when the occurrence is the same as lower bound  */

		Current_Node->ttop_of_stack->tcp_save = NULL;	/* !!!  temporary */

	/* set up the ending point of the matching */
		Current_Node->ttop_of_stack->end = Input_File.c_ptr;
		sprintf (User_Msg, "A sequecne pointer%d %d\n", Current_Node->ttop_of_stack->end, Input_File.c_ptr);
		Output_Decision ();
		sprintf (User_Msg, "Input_File %d %d\n", Current_Node->ttop_of_stack->begin, Current_Node->ttop_of_stack->end);
		Output_Decision ();

	/* back to ancestor node */
		Prev_Node = Current_Node;
		Current_Node = Current_Node->ancestor;

		if (Animate_Flag)
		{
			Inverse_Tree_Node (Current_Node);
		}

		sprintf (User_Msg, " <<(Suc_2) Succeed; Back to node %s\n", Current_Node->name);
		Output_Decision ();
		Activity = SUCCEED;
	}
	else if ((Current_Node->ttop_of_stack->no_of_elements > Current_Node->lower)
			&& (Current_Node->ttop_of_stack->end == Input_File.c_ptr))
	{
		Current_Node = Current_Node->level_point;

		sprintf (User_Msg, " >>(Suc_3) Go to node %s\n", Current_Node->name);
		Output_Decision ();
		Activity = NEXT;
	}
	else if ((Current_Node->ttop_of_stack->no_of_elements > Current_Node->lower)
			&&
			(Current_Node->ttop_of_stack->end < Input_File.c_ptr))
	{
	/* set up the ending point of the matching */
		Current_Node->ttop_of_stack->end = Input_File.c_ptr;
		sprintf (User_Msg, "A sequecne pointer%d %d\n", Current_Node->ttop_of_stack->end, Input_File.c_ptr);
		Output_Decision ();

		sprintf (User_Msg, "Input_File %d %d\n", Current_Node->ttop_of_stack->begin, Current_Node->ttop_of_stack->end);
		Output_Decision ();

	/* store the pointer which points to the last processed template node */
		Current_Node->ttop_of_stack->tcp_save = Prev_Node->ttop_of_stack;

		if (Animate_Flag)
		{
			Inverse_Node_Edge (Current_Node, BACKWARD);
		}

		Prev_Node = Current_Node;
		Current_Node = Current_Node->ancestor;

		if (Animate_Flag)
		{
			Inverse_Tree_Node (Current_Node);
		}

		sprintf (User_Msg, " <<(Suc_4) Succeed; Back to node %s\n",
			 Current_Node->name);
		Output_Decision ();
		Activity = SUCCEED;
	}
	else
	{
	/* no_of_element > lower && attempted match string > buffer string */
		Current_Node = Current_Node->level_point;

		sprintf (User_Msg, " >>(Suc_5) Go to node %s\n", Current_Node->name);
		Output_Decision ();
		Activity = NEXT;
	}			/* else */
}



static void     A_Failed_Element (void)
{
/* determine the next activity when element fails */
	if (Current_Node->ttop_of_stack->no_of_elements > 1)
	{
		Current_Node->ttop_of_stack->no_of_elements--;
		Current_Node = Current_Node->level_point;

		sprintf (User_Msg, " >>(Fail_1) Go to node %s\n", Current_Node->name);
		Output_Decision ();
		Activity = NEXT;
	}
	else
	{			/* no_of_elements == 1 */
		Adjust_Stack_and_Input_Ptrs ();

		if (Animate_Flag)
		{
			Inverse_Node_Edge (Current_Node, BACKWARD);
		}

		Prev_Node = Current_Node;
		Current_Node = Current_Node->ancestor;

		if (Animate_Flag)
		{
			Inverse_Tree_Node (Current_Node);
		}

		sprintf (User_Msg, " <<(Fail_2) Back to Node %s\n", Current_Node->name);
		Output_Decision ();
		Activity = FAIL;
	}
}

/*
 * ....................................................... Sequence
 * .......................................................
 */

static void     A_Sequence (void)
{
	switch (Activity)
	{
			case FIRST:
			sprintf (User_Msg, "__(AS_first) Sequence Node %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Node_Edge (Current_Node, FORWARD);
				Inverse_Tree_Node (Current_Node);
				Inverse_Tree_Node (Current_Node);
			}

			Temp_Stack = Stack_Allocation ();
		/* set up the starting & ending points of the matching */
			Temp_Stack->begin = Input_File.c_ptr;
			Temp_Stack->end = Input_File.c_ptr;
			Temp_Stack->from_tree_type = ANALYSIS;

		/* initialize the number of elements (occurrence) */
			Temp_Stack->no_of_elements = 0;

			Locate_Stack_Element ();

		/* determine activity when element is successful */
			A_Successful_Element ();
			break;

		case NEXT:
			sprintf (User_Msg, "__(AS_next) Sequence Node %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Node_Edge (Current_Node, FORWARD);
				Inverse_Tree_Node (Current_Node);
				Inverse_Tree_Node (Current_Node);
			}

			if (Current_Node->ttop_of_stack->no_of_elements < Current_Node->upper)
			{
				Current_Node->ttop_of_stack->no_of_elements++;
				Current_Node = Current_Node->level_point;

				sprintf (User_Msg, " >> (No. < upper) Go to node %s\n",
					 Current_Node->name);
				Output_Decision ();
				Activity = FIRST;
			}
			else if (Current_Node->ttop_of_stack->no_of_elements == Current_Node->upper)
			{
				sprintf (User_Msg, " .. (No. = upper)\n");
				Output_Decision ();
				Current_Node->ttop_of_stack->no_of_elements++;
				A_Failed_Element ();
			}

			break;

		case SUCCEED:
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			sprintf (User_Msg, "__(AS_succeed) Sequence Node %s\n", Current_Node->name);
			Output_Decision ();
			sprintf (User_Msg, "B sequecne pointer%d %d\n", Current_Node->ttop_of_stack->end, Input_File.c_ptr);
			Output_Decision ();
			A_Successful_Element ();

			sprintf (User_Msg, "A sequecne pointer%d %d\n", Current_Node->ttop_of_stack->end, Input_File.c_ptr);
			Output_Decision ();
			break;

		case FAIL:
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			sprintf (User_Msg, "__(AS_fail) Sequence Node %s\n", Current_Node->name);
			Output_Decision ();
			A_Failed_Element ();

			break;

		default:
			break;

	}			/* switch */
}



/*
 * ....................................................... Sequence Number  #
 * .......................................................
 */

static void     A_Sequence_No (void)
{
	short           i;

	switch (Activity)
	{

		case FIRST:
			sprintf (User_Msg, "__(ASN_first) Squence No. %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Node_Edge (Current_Node, FORWARD);
				Inverse_Tree_Node (Current_Node);
			}

		/* ---  convert the reference node into the match node  --- */
			sprintf (User_Msg, "");
			strncat (User_Msg, Current_Node->name, strlen (Current_Node->name) - 1);
			User_Msg[strlen (Current_Node->name) - 1] = '\0';	/* MALCOLM, why the strlen() - 1 ? */
			for (i = 0; User_Msg[i]; i++)
				if (isupper (User_Msg[i]))
					User_Msg[i] = tolower (User_Msg[i]);

		/* ****************************************  */
		/* search for the corr. sequence match node  */
		/* ****************************************  */
			Temp_Stack = Root_Stack->forward_stack_ptr;

			for (;;)
			{

			/*
			 * consider checking the node type in the future
			 * because of diff. type but same name; here aviod
			 * the testing of itself (SN)
			 */
				while (strncmp (Temp_Stack->template_node_ptr->name, User_Msg,
						strlen (User_Msg))
						&& Temp_Stack->forward_stack_ptr)
				{
					Temp_Stack = Temp_Stack->forward_stack_ptr;
				}
			/* nothing found */
				if (!Temp_Stack->forward_stack_ptr)
					break;
			/* found the exactly same node name */
				if (Temp_Stack->template_node_ptr->ttop_of_stack == Temp_Stack)
					break;
			}	/* for */

		/* Check nothing found  */
			if (!Temp_Stack->forward_stack_ptr)
			{
				sprintf (User_Msg, " => There is no corresponding match node found.\n");
				Output_Decision ();
				goto not_found1;
			}

		/* convert no_of_elements into a string */
			sprintf (User_Msg, "%d", Temp_Stack->no_of_elements);
			Output_Decision ();	/* print number of matching string */


		/* **************************************************  */
		/* check the string of sequence no. with input buffer  */
		/* **************************************************  */
			if (!strncmp (Input_File.buffer + Input_File.c_ptr, User_Msg,
				      strlen (User_Msg)))
			{
			/* -----  equally same  -----  */

			/* push a stack element for template node */
				Temp_Stack = Stack_Allocation ();
			/* set up the starting point of the matching */
				Temp_Stack->begin = Input_File.c_ptr;
				Temp_Stack->from_tree_type = ANALYSIS;

			/* <<  Adjust the input string pointer forward  >> */
				Input_File.c_ptr += strlen (User_Msg);

				Locate_Stack_Element ();

			/* set up the ending point of the matching */
				Current_Stack->end = Input_File.c_ptr;

				sprintf (User_Msg, " -> Forward input buffer pointer to location %d\n",
					 Input_File.c_ptr);
				Output_Decision ();

				sprintf (User_Msg, " => Successful matching at node %s with input string\n",
					 Current_Node->name);
				Output_Decision ();

				clientXBell ();
				Activity = SUCCEED;
			}
			else
			{

				sprintf (User_Msg, " => Unsuccessful matching at node %s with input string\n",
					 Current_Node->name);
				Output_Decision ();

		not_found1:
				client_blink_window ();
				Activity = FAIL;
			}	/* else */

		/* <<<<  continue the rest of processing  >>>>  */
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

		/* adjust template node pointer to ancestor node */
			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

		/* Note: back to its ancestor */
			sprintf (User_Msg, " << Back to Node %s\n", Current_Node->name);
			Output_Decision ();

			break;

		case NEXT:
			sprintf (User_Msg, "__(ASN_next) Squence No. %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

			Adjust_Stack_and_Input_Ptrs ();

			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			sprintf (User_Msg, " << Fail; Back to Node %s\n", Current_Node->name);
			Output_Decision ();
			Activity = FAIL;
			break;

		default:
			break;

	}			/* switch */
}


/*
 * ....................................................... Analysis
 * Processing .......................................................
 */


static void     A_Node_Type_Check (void)
{

/* check if match node has no immediate sibling- "abstract execution"  */
	if ((Current_Node->type & MATCH_NODE) && !Current_Node->level_point)
	{
		printf ("\n abstraction exection%s %d\n", Current_Node->name, Current_Node->type);
		A_Abstarct_Exec ();
	}

	switch (Current_Node->type)
	{

		case LITERAL:
			A_Literal ();
			break;

		case MATCH_DIRECT_PRODUCT:
		case REFERENCE_DIRECT_PRODUCT:
			A_Direct_Product ();
			break;

		case MATCH_DISCRIMINATED_UNION:
		case REFERENCE_DISCRIMINATED_UNION:

			A_Discriminated_Union ();
			break;

		case MATCH_SEQUENCE:
		case MATCH_SEQUENCE_UNION:
		case MATCH_SEQUENCE_RANGE:
		case REFERENCE_SEQUENCE:
		case REFERENCE_SEQUENCE_UNION:
		case REFERENCE_SEQUENCE_RANGE:
		/* minimize the occurrence of matching */
			A_Sequence ();
			break;

		case REFERENCE_SEQUENCE_NO:
			A_Sequence_No ();
			break;

		case MODULE_CALL:
			printf ("module call\n");
			break;

		default:
			break;

	}			/* switch */
}

static struct data_node *seek_data (struct data_node * cur_data, int count)
{
	int             i;
	struct data_node *prev_data;

	for (i = 1; i <= count; i++)
	{
		prev_data = cur_data;
		cur_data = cur_data->front;
		free (prev_data);
		prev_data = NULL;
	}
	return (cur_data);
}

static void     Save_variables (void)
{
	S_Input_File.c_ptr = Input_File.c_ptr;
	S_Output_File.c_ptr = Output_File.c_ptr;
	S_Hoare_Root_Dummy = Hoare_Root_Dummy;
	S_Root_Stack = Root_Stack;
	S_Temp_Stack = Temp_Stack;
	S_Current_Stack = Current_Stack;
	S_Current_Node = Current_Node;
}

static void     Restore_variables (void)
{
	Input_File.c_ptr = S_Input_File.c_ptr;
/* Output_File.c_ptr=S_Output_File.c_ptr; */
	Hoare_Root_Dummy = S_Hoare_Root_Dummy;
	Root_Stack = S_Root_Stack;
	Temp_Stack = S_Temp_Stack;
	Current_Stack = S_Current_Stack;
	Current_Node = S_Current_Node;
}


static void     free_data_node (struct data_node * cur_node)
{
	struct data_node *tmp_node;

	while (cur_node)
	{
		tmp_node = cur_node;
		printf ("FREE DATA %s \n", tmp_node->data);
		cur_node = cur_node->next;
		free (tmp_node);
		tmp_node = NULL;
	}
}


/* number of maxium processors is 5  */
/* maxium length of node name is 132 */

static struct Template_Node *Search_Module_Root (struct Template_Node * cur_node)
{

	struct Template_Node *Root_Dummy;

	printf ("sub module %s\n", Hoare_Root_Dummy->level_point->module_name);

	Root_Dummy = F_Hoare_Root_Dummy;
	while (Root_Dummy)
		if (strcmp (cur_node->module_name, Root_Dummy->level_point->module_name))
		{
			Root_Dummy = Root_Dummy->front;
		}
		else
		{
		/* Hoare_Root_Dummy=Root_Dummy; */
			return (Root_Dummy);
		}

	printf ("no such module\n");
	return (NULL);
}


static int      S_Check_Module (void)
{
	struct data_node *Prev_output;
	struct data_node *Prev_wk;

	if (!strncmp (Current_Node->name, "NL", 2))
	{
		if (return_flag)
		{
			retry_fputc (NL, Output_File.f_ptr);
			Output_File.c_ptr++;
			if (concurrent)
			{
				Current_output->next = (struct data_node *) calloc (1, sizeof (struct data_node));
				Prev_output = Current_output;
				Current_output = Current_output->next;
				Current_output->data = (char *) calloc (1 + 1, sizeof (char));
				Current_output->data[0] = NL;
				Current_output->data[1] = '\0';
				Current_output->next = NULL;
				Current_output->front = Prev_output;
				Output_data_c_ptr++;
			}
		}
		else
		{
			retry_fputc (NL, W_Output_File.f_ptr);
			W_Output_File.c_ptr++;
			if (concurrent)
			{
				Current_wk->next = (struct data_node *) calloc (1, sizeof (struct data_node));
				Prev_wk = Current_wk;
				Current_wk = Current_wk->next;
				Current_wk->data = (char *) calloc (1 + 1, sizeof (char));
				Current_wk->data[0] = NL;
				Current_wk->data[1] = '\0';
				Current_wk->next = NULL;
				Current_wk->front = Prev_wk;
				W_Output_data_c_ptr++;
			}
		}		/* end else */
		return (1);
	}
	else if (!strncmp (Current_Node->name, "NP", 2))
	{
		if (return_flag)
		{
			retry_fputc (NP, Output_File.f_ptr);
			Output_File.c_ptr++;
			if (concurrent)
			{
				Current_output->next = (struct data_node *) calloc (1, sizeof (struct data_node));
				Prev_output = Current_output;
				Current_output = Current_output->next;
				Current_output->data = (char *) calloc (1 + 1, sizeof (char));
				Current_output->data[0] = NP;
				Current_output->data[1] = '\0';
				Current_output->next = NULL;
				Current_output->front = Prev_output;
				Output_data_c_ptr++;
			}
		}
		else
		{
			retry_fputc (NP, W_Output_File.f_ptr);
			W_Output_File.c_ptr++;
			if (concurrent)
			{
				Current_wk->next = (struct data_node *) calloc (1, sizeof (struct data_node));
				Prev_wk = Current_wk;
				Current_wk = Current_wk->next;
				Current_wk->data = (char *) calloc (1 + 1, sizeof (char));
				Current_wk->data[0] = NP;
				Current_wk->data[1] = '\0';
				Current_wk->next = NULL;
				Current_wk->front = Prev_wk;
				W_Output_data_c_ptr++;
			}
		}		/* end else */
		return (1);
	}
	else
		return (0);
}				       /* end S_Check_Module() */

static void     find_data (struct data_node * cur_data, int from, int count)
{
	int             i;
	struct data_node *tmp_data;

	tmp_data = cur_data;

	for (i = 0; i <= from; i++)
		tmp_data = tmp_data->next;
	for (i = 1; i <= count; i++)
	{
		printf ("FIND DATA %s \n", tmp_data->data);
		strcat (User_Msg, tmp_data->data);
	}
}


/* Note: there also exists S_Find_Corr_Match() and S_Find_Corr_Match2() */
static int      S_Find_Corr_Match1 (struct link_list * cur_para)
{
	short           i;
	struct Stack_Node *TOS,
	               *t1;

/* ---  convert the reference node into the match node  --- */
	sprintf (User_Msg, "");
	strncat (User_Msg, cur_para->name, strlen (cur_para->name));
	User_Msg[strlen (cur_para->name)] = '\0';
	for (i = 0; User_Msg[i]; i++)
		if (isupper (User_Msg[i]))
			User_Msg[i] = tolower (User_Msg[i]);

/* ****************************************  */
/* search for the corr. sequence match node  */
/* ****************************************  */
	Prev_Stack = Root_Stack->forward_stack_ptr;

	for (;;)
	{

		while (strncmp (Prev_Stack->template_node_ptr->name, User_Msg,
				strlen (User_Msg))
				&& Prev_Stack->forward_stack_ptr)
		{
			Prev_Stack = Prev_Stack->forward_stack_ptr;
			printf ("initial search->%s %s\n", Prev_Stack->template_node_ptr->name, User_Msg);
		}
	/* nothing found */
		if (!Prev_Stack->forward_stack_ptr)
			return (0);
	/* found the exactly same node name */
		if (Prev_Stack->template_node_ptr->ttop_of_stack == Prev_Stack)
		{
			break;
		}
	}			/* for */

/* process needs to start from the bottom of the stack; searching BOS  */
	TOS = Prev_Stack;
	while (Prev_Stack->prev_stack_element)
	{
		Prev_Stack = Prev_Stack->prev_stack_element;
	}

	for (;;)
	{

		sprintf (User_Msg, "");
		printf ("matching in tree \n");
		printf ("matched node name ->%s\n", Prev_Stack->template_node_ptr->name);
		if (Prev_Stack->from_tree_type == ANALYSIS)
		{		/* 1 */
			printf ("match in analysis tree %d\n", Prev_Stack->from_tree_type);
			printf ("match in analysis tree %d\n", TOS->from_tree_type);
			strncat (User_Msg, Input_File.buffer + Prev_Stack->begin,
				 Prev_Stack->end - Prev_Stack->begin);
		}
		else
		{		/* else 1 */
			printf ("match in synthesis tree \n");
			printf ("ptr %d %d %d\n", Prev_Stack->end, Prev_Stack->begin, W_Output_File.c_ptr);
			if (Prev_Stack->from_tree_type == SYNTHESIS1)
			{	/* if 2 */
				if (concurrent)
				{	/* if 3 */
					find_data (Wk_data, Prev_Stack->begin, Prev_Stack->end - Prev_Stack->begin);
				}
				else
				{	/* else 3 */
					fseek (W_Output_File.f_ptr, Prev_Stack->begin, SEEK_SET);
					retry_fgets (User_Msg, Prev_Stack->end - Prev_Stack->begin + 1, W_Output_File.f_ptr);
					fseek (W_Output_File.f_ptr, 0, SEEK_END);
				}	/* end else 3 */
			}
			else
			{	/* else 2 */
				if (concurrent)
				{	/* if 4 */
					find_data (Output_data, Prev_Stack->begin, Prev_Stack->end - Prev_Stack->begin);
				}
				else
				{	/* else 4 */
					printf ("o ptr %d %d %d\n", Prev_Stack->end, Prev_Stack->begin, Output_File.c_ptr);
					fseek (Output_File.f_ptr, Prev_Stack->begin, SEEK_SET);
					retry_fgets (User_Msg, Prev_Stack->end - Prev_Stack->begin + 1, Output_File.f_ptr);
					fseek (Output_File.f_ptr, 0, SEEK_END);
				}	/* end else 4 */
			}	/* end else 2 */
		}		/* end else 1 */
		retry_fputs (User_Msg, S_Output_File.f_ptr);	/* Value that matched (substring in the output stream) */

		Output_Decision ();	/* for debuging */

		printf ("match with match node %s<=\n", User_Msg);
	/* add April  1992  */
	/* adjust the output file pointer   */
		S_Output_File.c_ptr = S_Output_File.c_ptr + Prev_Stack->end - Prev_Stack->begin;

		if (concurrent && (Prev_Stack->from_tree_type != ANALYSIS))
			S_Output_File.c_ptr = S_Output_File.c_ptr + strlen (User_Msg) - 1;

	/* does reach the top of the stack */
		if (Prev_Stack == TOS)
			break;
		else
		{

			for (t1 = TOS; t1->prev_stack_element != Prev_Stack;)
			{
				t1 = t1->prev_stack_element;
			}

		/* move one stack element upward */
			Prev_Stack = t1;
		}
	}
	return (1);
}				       /* end S_Find_Corr_Match1() */


/*
 * NOTE: There exists a function with ALMOST the same name later on in this
 * file, namely, S_Direct_Product ()
 */

static void     S_Direct_Product1 (struct link_list * cur_para)
{

	switch (Activity)
	{

			case FIRST:
			sprintf (User_Msg, "__(SDP1_first)Node %s\n", cur_para->name);
			Output_Decision ();


			if (S_Check_Module ())
			{

				sprintf (User_Msg, " => Successfully matched at module call\n");
				Output_Decision ();

			/* set up the ending point of synthesis */

			/*
			 * Temp_Stack->end = S_Output_File.c_ptr;
			 */
				clientXBell ();
				Activity = SUCCEED;
			}
			else
			{

				printf (" search  parameter\n");
				switch (S_Find_Corr_Match1 (cur_para))
				{

					case 0:	/* no corr. match node */
						printf (" => It is non-defined para\n");
						sprintf (User_Msg, " => It is non-defined reference node\n");
						printf (" It is non-defined parameter\n");
						Output_Decision ();

						client_blink_window ();
						Activity = FAIL;
						break;

					case 1:	/* a corr. match node */
						printf (" => Found a corresponding match node for para\n");
						sprintf (User_Msg, " => Found a corresponding match node\n");
						Output_Decision ();

					/*
					 * set up the ending point of
					 * synthesis
					 */

					/*
					 * Temp_Stack->end =
					 * S_Output_File.c_ptr;
					 */
						clientXBell ();
						Activity = SUCCEED;
						break;

					default:
						break;
				}	/* switch */
			}	/* else */
			return;

		case NEXT:
			sprintf (User_Msg, "__(SDP_next)Node %s\n", Current_Node->para->name);
			Output_Decision ();

		/* Adjust the template stack pointer */
			if (Current_Node->ttop_of_stack->prev_stack_element)
			/* more stack elements */
				Current_Node->ttop_of_stack = Current_Node->ttop_of_stack->prev_stack_element;
			else
				Current_Node->ttop_of_stack = NULL;

		/*
		 * << move backward to the previous position in output file
		 * >>
		 */
			if (return_flag)
			{
				Output_File.c_ptr = Temp_Stack->begin;
				fseek (Output_File.f_ptr, Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_output = seek_data (Current_output, Output_data_c_ptr - Temp_Stack->begin);
					Output_data_c_ptr = Temp_Stack->begin;
				}
			}
			else
			{
				W_Output_File.c_ptr = Temp_Stack->begin;
				fseek (W_Output_File.f_ptr, W_Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_wk = seek_data (Current_wk, W_Output_data_c_ptr - Temp_Stack->begin);
					W_Output_data_c_ptr = Temp_Stack->begin;
				}
			}	/* end else */
			sprintf (User_Msg, " <- Backward output buffer pointer at location %d\n",
				 Output_File.c_ptr);
			Output_Decision ();

			sprintf (User_Msg, " ** Free a stack element at Node %s; adjust stack & "
				 "output pointers.\n",
				 Current_Node->name);
			Output_Decision ();
		/* free the stack */
			free (Temp_Stack);
			Temp_Stack = NULL;

			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;

			sprintf (User_Msg, " << Fail; Back to Node %s\n", Current_Node->name);
			Output_Decision ();

			client_blink_window ();
			Activity = FAIL;
			return;

		default:
			break;

	}			/* switch */

}

static void     S_Parallel (void)
{
	struct link_list *cur_para;
	struct Template_Node *Tmp_node;
	int             i,
	                j;
	QUEUE          *ready_q;       /* Shared memory.  related to addr1 and  shmid_p[0] */
	char           *addr1;	       /* Shared memory.  related to ready_q and shmid_p[0] */
	int            *pid_no;	       /* Shared memory.  related to shmid_p[1]. */
	short          *P_activity;    /* Shared memory.  related to shmid_p[2]. */
	int             id[5];
	int             pid = 1;
	int             semid;	       /* Semaphore protecting access to dequeue() operations in ready_q */

	shmid_p[0] = shmget (SHMKEY, 300, 0777 | IPC_CREAT);
	if (shmid_p[0] == -1)
		printf ("can not create shared mem\n");
	addr1 = (char *) shmat (shmid_p[0], NULL, 0);
	printf ("addr1 0x%x \n", addr1);
	ready_q = (struct queue *) addr1;

	shmid_p[1] = shmget (SHMKEY + 1, 30, 0777 | IPC_CREAT);
	if (shmid_p[1] == -1)
		printf ("can not create shared mem\n");
	pid_no = (int *) shmat (shmid_p[1], 0, 0);

	shmid_p[2] = shmget (SHMKEY + 2, 4, 0777 | IPC_CREAT);
	if (shmid_p[2] == -1)
		printf ("can not create shared mem\n");
	P_activity = (short *) shmat (shmid_p[2], 0, 0);	/* YIKES! this used to have an "==" instead of an "=" operator! */

	semid = sem_create ();
	server = sem_create ();
	client = sem_create ();

	switch (Activity)
	{
		case FIRST:
			Save_variables ();
			printf ("BBinformation of cur node %d %d\n", Current_Node->row, Current_Node->col);
			sprintf (User_Msg, "__(SPa_first) parallel %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Node_Edge (Current_Node, FORWARD);
				Inverse_Tree_Node (Current_Node);
				Inverse_Tree_Node (Current_Node);
			}
			Tmp_node = Current_Node->level_point;
			Current_Node = Tmp_node;

			i = 0;
			while (Current_Node != NULL)
			{
				i++;

			/*
			 * Get_Parameters();
			 */
			/* add   April  1992    */
				printf ("check parameteres \n");
				pcb[i].root_node = (char *) Search_Module_Root (Current_Node);
				printf ("2check parameteres \n");

				sprintf (User_Msg, "__ parallel--Process id= %d\n", getpid ());
				Output_Decision ();

			/* add   April  1992    */

			/*
			 * S_Output_File  for storing the results of
			 * parameters' matching
			 */
				S_Output_File.c_ptr = 0;
				S_Output_File.f_ptr = retry_fopen (S_Output_File.name, "w");
				setbuf (S_Output_File.f_ptr, NULL);	/* Do not buffer I/O */


			/* add   April  1992    */
				cur_para = Current_Node->para;	/* Linked list of parameters of Current_Node->name */
				while (cur_para)
				{
					printf ("check parameteres \n");
					Activity = FIRST;
					S_Direct_Product1 (cur_para);
					if (Activity == SUCCEED)
					{
						cur_para = cur_para->next;
					}
					else
						break;
				}

			/*
			 * add   carriage return  to the output file of
			 * parameters without it, analysis can not reach the
			 * end of file, analysis will fail
			 */
				add_carriage_return (S_Output_File.f_ptr);
				fclose (S_Output_File.f_ptr);



				printf (" put the input data to file buffer\n");
			/* put the input data to file buffer            */
				S_Output_File.f_ptr = retry_fopen (S_Output_File.name, "r");
				setbuf (S_Output_File.f_ptr, NULL);	/* Do not buffer I/O */
				DESC_File_Stat = Get_File_Stat (S_Output_File.name);

				pcb[i].Input_buffer = (char *) calloc (DESC_File_Stat.st_size + 1, sizeof (char));

				strcpy (DESC_Line_Str, "");
				strcpy (pcb[i].Input_buffer, "");
				printf ("before in file -%s\n", pcb[i].Input_buffer);
				while (retry_fgets (DESC_Line_Str, MAX_LINE_SIZE, S_Output_File.f_ptr) != NULL)
				{
					printf ("put input data >>\n");
					strcat (pcb[i].Input_buffer, DESC_Line_Str);
				}

				fclose (S_Output_File.f_ptr);
				printf ("before enqueue addr2 0x%x \n", pcb[i].root_node);
				enqueue (ready_q, i);
				Current_Node = Current_Node->front;
			}	/* end of while loop  */

		/* concurrent  execution     */
			printf ("    concurrent  execution    \n");
			*pid_no = i;

		/*
		 * shared variable must be inintialized in the parent process
		 * WHY?
		 */
			*P_activity = SUCCEED;


			concurrent = 1;	/* set concurrent flag */

			for (p_cnt = 1; p_cnt <= *pid_no; p_cnt++)
			{
				if ((pcb[p_cnt].pid = pid = fork ()) == 0)
				{
					id[p_cnt] = getpid ();
					break;
				}
				else if (pid == -1)
					perror ("can not fork() in S_Parallel()");
			}

			if (pid != 0)
			{
				printf ("__ parent --Process id= %d\n", getpid ());

				for (j = 1; j <= *pid_no; j++)
				{
					printf ("##parent        waiting###\n");
					wait ((int *) 0);
				}
				printf (" FINISH  ---- WAITING \n");
				printf ("finish waiting one processor \n");
			}



			if (pid == 0)
			{
				printf (" before go to exec \n");
				printf ("__ parallel--Process id= %d\n", getpid ());
			/* put data of parameters to file buffer      */
			/* add  April    1992   */
				Input_File.c_ptr = 0;
				Output_data = (struct data_node *) calloc (1, sizeof (struct data_node));
				Current_output = Output_data;
				Wk_data = (struct data_node *) calloc (1, sizeof (struct data_node));
				Current_wk = Wk_data;

				Output_data_c_ptr = 0;
				W_Output_data_c_ptr = 0;

				sem_wait (semid);
				dequeue (ready_q, &p_cnt);
				sem_signal (semid);

				printf ("after dqueue addr1 0x%x and %d\n", pcb[p_cnt].root_node, p_cnt);
				Hoare_Root_Dummy = (struct Template_Node *) pcb[p_cnt].root_node;
				strcpy (Input_File.buffer, "");
				strcpy (Input_File.buffer, pcb[p_cnt].Input_buffer);
				printf ("in file -%s len %d \n", pcb[p_cnt].Input_buffer, strlen (pcb[p_cnt].Input_buffer));

				exec_run2 ();

				free_data_node (Output_data);
				free_data_node (Wk_data);

				printf (" after  exec \n");

				printf ("before SUCCEED--%d------\n", *P_activity);

				sem_wait (semid);
				if (Activity == SUCCEED)
				{
					*P_activity = SUCCEED;
					printf ("SUCCEED--%d------\n", *P_activity);
				}
				else
					*P_activity = FAIL;
			/* *pid_no = *pid_no -1;  */
				printf ("In crtical section : pid count %d\n", *pid_no);
				sem_signal (semid);

			/* sem_signal(server); */
				printf ("FREE P_CNT  %d\n", p_cnt);

				exit (0);

			}	/* end of pid */


			concurrent = 0;	/* set concurrent flag */

			printf (" after  go to exec \n");
			Restore_variables ();

			printf ("PACTIVITY --%d------\n", *P_activity);
			if (*P_activity == SUCCEED)
			{
				printf ("SUCCEED--------\n");
				Activity = SUCCEED;
			}
			else
				Activity = FAIL;

		/* push a stack element for template node */
			Temp_Stack = Stack_Allocation ();
			if (return_flag)
			{
				Temp_Stack->begin = Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS;
			}
			else
			{
				Temp_Stack->begin = W_Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = W_Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS1;
			}

		/* add April    1992   */
		/* restore input file      */
			Input_File.f_ptr = retry_fopen (Input_File.name, "r");
			strcpy (Input_File.buffer, "");
			strcpy (DESC_Line_Str, "");
			printf ("before old in file -%s", Input_File.buffer);
			while (retry_fgets (DESC_Line_Str, MAX_LINE_SIZE, Input_File.f_ptr) != NULL)
			{
				strcat (Input_File.buffer, DESC_Line_Str);
			}
			printf ("old in file -%s", Input_File.buffer);

			fclose (Input_File.f_ptr);

		/*
		 * fclose(Log_File.f_ptr);
		 */
			if (return_flag)
			{
				Temp_Stack->end = Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->end = Output_data_c_ptr;
			}
			else
			{
				Temp_Stack->end = W_Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->end = W_Output_data_c_ptr;
			}
			Locate_Stack_Element ();

			printf (" => Output a string with Literal\n");
			Output_Decision ();
			printf ("information of cur node %d %d\n", Current_Node->row, Current_Node->col);

			printf ("BEFORE FINISH PARALELL \n");
		/* adjust template node pointer to ancestor node */
			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;
			if (Animate_Flag)
			{
				Inverse_Node_Edge (Current_Node, BACKWARD);
				Inverse_Tree_Node (Current_Node);
			}
			printf ("BEFORE FINISH PARALELL \n");

			if (Activity == SUCCEED)
			{
				sprintf (User_Msg, " SUCCEED<< Back to Node %s\n", Current_Node->name);
				printf (" SUCCEED<< Back to Node \n");
				Output_Decision ();
				Activity = SUCCEED;

			}
			else
			{
				sprintf (User_Msg, " FAIL<< Back to Node %s\n", Current_Node->name);
				printf (" FAIL<< Back to Node \n");
				Output_Decision ();
				Activity = FAIL;
			}
			shmctl (shmid_p[0], IPC_RMID, 0);
			shmctl (shmid_p[1], IPC_RMID, 0);
			shmctl (shmid_p[2], IPC_RMID, 0);
			printf ("END PARALLEL\n");
			break;

		case NEXT:
			sprintf (User_Msg, "__(SM_next) Module %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

		/* free the stack */
			Temp_Stack = Current_Node->ttop_of_stack;
			Current_Stack = Current_Node->ttop_of_stack->backward_stack_ptr;
			Current_Stack->forward_stack_ptr = NULL;

		/* Adjust the template stack pointer */
			if (Current_Node->ttop_of_stack->prev_stack_element)
			/* more stack elements */
				Current_Node->ttop_of_stack = Current_Node->ttop_of_stack->prev_stack_element;
			else
				Current_Node->ttop_of_stack = NULL;

		/*
		 * Move backward to the previous position in output file
		 */
			if (return_flag)
			{
				Output_File.c_ptr = Temp_Stack->begin;
				fseek (Output_File.f_ptr, Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_output = seek_data (Current_output, Output_data_c_ptr - Temp_Stack->begin);
					Output_data_c_ptr = Temp_Stack->begin;
				}
			}
			else
			{
				W_Output_File.c_ptr = Temp_Stack->begin;
				fseek (W_Output_File.f_ptr, W_Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_wk = seek_data (Current_wk, W_Output_data_c_ptr - Temp_Stack->begin);
					W_Output_data_c_ptr = Temp_Stack->begin;
				}
			}	/* end else */
			sprintf (User_Msg, " <- Backward output buffer pointer at location %d\n",
				 Output_File.c_ptr);
			Output_Decision ();

			sprintf (User_Msg, " ** Free a stack element at Node %s; adjust stack & "
				 "output pointers.\n",
				 Current_Node->name);
			Output_Decision ();
			free (Temp_Stack);
			Temp_Stack = NULL;

			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			sprintf (User_Msg, " << Fail; Back to Node %s\n", Current_Node->name);
			Output_Decision ();

			client_blink_window ();
			Activity = FAIL;
			break;

		default:
			break;

	}			/* switch */
}




/* The Show_Node_Type()  function is only for internal testing */

static void     Show_Node_Type (void)
{

	switch (Current_Node->type)
	{
			case MATCH_DIRECT_PRODUCT:
			sprintf (User_Msg, "$match direct product - %s\n", Current_Node->name);
			Output_Decision ();
			break;

		case MATCH_DISCRIMINATED_UNION:
			sprintf (User_Msg, "$match discriminated union - %s\n", Current_Node->name);
			Output_Decision ();
			break;

		case MATCH_SEQUENCE:
			sprintf (User_Msg, "$match sequence - %s\n", Current_Node->name);
			Output_Decision ();
			break;

		case LITERAL:
			sprintf (User_Msg, "$literal - %s\n", Current_Node->name);
			Output_Decision ();
			break;

		case MODULE_TITLE:
			sprintf (User_Msg, "$module title - %s\n", Current_Node->name);
			Output_Decision ();
			break;

		case REFERENCE_DIRECT_PRODUCT:
			sprintf (User_Msg, "$reference direct product - %s\n", Current_Node->name);
			Output_Decision ();
			break;

		case REFERENCE_DISCRIMINATED_UNION:
			sprintf (User_Msg, "$reference discriminated union - %s\n", Current_Node->name);
			printf ("$reference discriminated union - %s\n", Current_Node->name);
			Output_Decision ();
			break;

		case REFERENCE_SEQUENCE:
			sprintf (User_Msg, "$reference sequence - %s\n", Current_Node->name);
			Output_Decision ();
			break;

		case REFERENCE_SEQUENCE_NO:
			sprintf (User_Msg, "$reference sequence no - %s\n", Current_Node->name);
			Output_Decision ();
			break;

		case MODULE_CALL:
			sprintf (User_Msg, "$module call - %s\n", Current_Node->name);
			Output_Decision ();
			break;

		default:
			break;

	}
}


/* primitives    add April  1992      */

/* NOTE: there also exists S_Primitives2() */
static void     S_Primitives (void)
{
	struct link_list *cur_para;
	int             separter[3];
	char            para_data1[80];
	char            para_data2[80];
	int             para_datai1;
	int             para_datai2;
	int             i;

	switch (Activity)
	{
		case FIRST:
			Save_variables ();

			sprintf (User_Msg, "__(SP_first) primitive  %s\n", Current_Node->name);
			Output_Decision ();

			printf ("__(SP_first) primitive  %s\n", Current_Node->name);

			if (Animate_Flag)
			{
				Inverse_Node_Edge (Current_Node, FORWARD);
				Inverse_Tree_Node (Current_Node);
				Inverse_Tree_Node (Current_Node);
			}

		/*
		 * S_Output_File  for storing the results of parameters'
		 * matching
		 */
			S_Output_File.c_ptr = 0;
			S_Output_File.f_ptr = retry_fopen (S_Output_File.name, "w");
			setbuf (S_Output_File.f_ptr, NULL);	/* Do not buffer I/O */

		/* add   April  1992    */
			cur_para = Current_Node->para;	/* Linked list of parameters of Current_Node->name */
		/* while(cur_para) */
			for (i = 0; i < 2; i++)
			{
				if (*(cur_para->name) == 39)	/* ESC character. */
				{

				/*
				 * Strip the opening and closing single-quote
				 * chars off of cur_para->name, and put the
				 * resulting string into para_data1
				 */
					strncpy (para_data1, cur_para->name + 1, strlen (cur_para->name) - 2);
					para_data1[strlen (cur_para->name) - 2] = '\0';
					printf ("=====>para_data %s\n", para_data1);
					retry_fputs (para_data1, S_Output_File.f_ptr);
					S_Output_File.c_ptr += strlen (para_data1);

					printf ("pointer loc %d\n", S_Output_File.c_ptr);
					printf ("=====>para_data %s------ %s\n", User_Msg, cur_para->name);
					separter[i] = S_Output_File.c_ptr;
					cur_para = cur_para->next;
				}
				else
				{
					printf ("check parameteres \n");
					Activity = FIRST;
					S_Direct_Product1 (cur_para);
					separter[i] = S_Output_File.c_ptr;
					if (Activity == SUCCEED)
					{
						cur_para = cur_para->next;
					}
					else
						break;
				}
			}

		/*
		 * add   carriage return  to the output file of parameters
		 * without it, analysis can not reach the end of file,
		 * analysis will fail
		 */
			add_carriage_return (S_Output_File.f_ptr);
			fclose (S_Output_File.f_ptr);

			Restore_variables ();
		/* push a stack element for template node */
			Temp_Stack = Stack_Allocation ();
			if (return_flag)
			{
				Temp_Stack->begin = Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS;
			}
			else
			{
				Temp_Stack->begin = W_Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = W_Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS1;
			}

		/* add April    1992   */
		/* restore input file      */
			S_Output_File.f_ptr = retry_fopen (S_Output_File.name, "r");
			setbuf (S_Output_File.f_ptr, NULL);	/* Do not buffer I/O */
			retry_fgets (para_data1, separter[0] + 1, S_Output_File.f_ptr);
			*
				retry_fgets (para_data2, S_Output_File.c_ptr - separter[0] + 1, S_Output_File.f_ptr);

			printf ("COMPARE compar %s %s \n", para_data1, para_data2);
		/* comparsion of two parameters */
			switch (Current_Node->type)
			{
				case ISEQUAL:
					sprintf (User_Msg, "equal compare %s,%s\n", para_data1, para_data2);
					Output_Decision ();
					if (strcmp (para_data1, para_data2) == 0)
						Activity = SUCCEED;
					else
						Activity = FAIL;
					break;

				case NOT_EQUAL:
					if (strcmp (para_data1, para_data2) == 0)
						Activity = FAIL;
					else
						Activity = SUCCEED;
					break;

				case GREATER_THAN:
					sscanf (para_data1, "%d", &para_datai1);
					sscanf (para_data2, "%d", &para_datai2);
					if (para_datai1 > para_datai2)
						Activity = SUCCEED;
					else
						Activity = FAIL;
					break;

				case GREATER_THAN_OR_EQUAL:
					sscanf (para_data1, "%d", &para_datai1);
					sscanf (para_data2, "%d", &para_datai2);
					if (para_datai1 >= para_datai2)
						Activity = SUCCEED;
					else
						Activity = FAIL;
					break;

				case LESS_THAN:
					sscanf (para_data1, "%d", &para_datai1);
					sscanf (para_data2, "%d", &para_datai2);
					printf ("compar %d %d \n", para_datai1, para_datai2);
					if (para_datai1 < para_datai2)
						Activity = SUCCEED;
					else
						Activity = FAIL;
					break;

				case LESS_THAN_OR_EQUAL:
					sscanf (para_data1, "%d", &para_datai1);
					sscanf (para_data2, "%d", &para_datai2);
					printf ("compar %d %d \n", para_datai1, para_datai2);
					if (para_datai1 <= para_datai2)
						Activity = SUCCEED;
					else
						Activity = FAIL;
					break;

				default:
					break;
			}


			fclose (S_Output_File.f_ptr);

			if (return_flag)
			{
				Temp_Stack->end = Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->end = Output_data_c_ptr;
			}
			else
			{
				Temp_Stack->end = W_Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->end = W_Output_data_c_ptr;
			}
			Locate_Stack_Element ();
			Output_Decision ();

			if (Activity == SUCCEED)
			{

			/*
			 * adjust template node pointer to first immediate
			 * sibling  node
			 */
				Prev_Node = Current_Node;
				Current_Node = Current_Node->level_point;
				sprintf (User_Msg, " SUCCEED<< Go to Node %s\n", Current_Node->name);
				printf (" SUCCEED<< Back to Node \n");
				Output_Decision ();
				Activity = FIRST;

			}
			else
			{
			/* adjust template node pointer to ancestor node */
				Prev_Node = Current_Node;
				Current_Node = Current_Node->ancestor;
				sprintf (User_Msg, " FAIL<< Back to Node %s\n", Current_Node->name);
				printf (" FAIL<< Back to Node \n");
				Output_Decision ();
				Activity = FAIL;
			/* add   NOV 21 1992   */
				if (Animate_Flag)
				{
					Inverse_Tree_Node (Current_Node);
				}
			}

			break;

		case NEXT:
			sprintf (User_Msg, "__(SM_next) Module %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

		/* free the stack */
			Temp_Stack = Current_Node->ttop_of_stack;
			Current_Stack = Current_Node->ttop_of_stack->backward_stack_ptr;
			Current_Stack->forward_stack_ptr = NULL;

		/* Adjust the template stack pointer */
			if (Current_Node->ttop_of_stack->prev_stack_element)
			/* more stack elements */
				Current_Node->ttop_of_stack = Current_Node->ttop_of_stack->prev_stack_element;
			else
				Current_Node->ttop_of_stack = NULL;

		/*
		 * Move backward to the previous position in output file
		 */
			if (return_flag)
			{
				Output_File.c_ptr = Temp_Stack->begin;
				fseek (Output_File.f_ptr, Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_output = seek_data (Current_output, Output_data_c_ptr - Temp_Stack->begin);
					Output_data_c_ptr = Temp_Stack->begin;
				}
			}
			else
			{
				W_Output_File.c_ptr = Temp_Stack->begin;
				fseek (W_Output_File.f_ptr, W_Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_wk = seek_data (Current_wk, W_Output_data_c_ptr - Temp_Stack->begin);
					W_Output_data_c_ptr = Temp_Stack->begin;
				}
			}	/* end else */
			sprintf (User_Msg, " <- Backward output buffer pointer at location %d\n",
				 Output_File.c_ptr);
			Output_Decision ();

			sprintf (User_Msg, " ** Free a stack element at Node %s; adjust stack & "
				 "output pointers.\n",
				 Current_Node->name);
			Output_Decision ();
			free (Temp_Stack);
			Temp_Stack = NULL;

			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			sprintf (User_Msg, " << Fail; Back to Node %s\n", Current_Node->name);
			Output_Decision ();

			client_blink_window ();
			Activity = FAIL;
			break;

		case SUCCEED:
			sprintf (User_Msg, "__(SP1_succeed) Primitive1 %s\n", Current_Node->name);
			Output_Decision ();

		/* set up the ending point of synthesis */
			if (return_flag)
			{
				Current_Node->ttop_of_stack->end = Output_File.c_ptr;
				if (concurrent)
					Current_Node->ttop_of_stack->end = Output_data_c_ptr;
			}
			else
			{
				Current_Node->ttop_of_stack->end = W_Output_File.c_ptr;
				if (concurrent)
					Current_Node->ttop_of_stack->end = W_Output_data_c_ptr;
			}

		/*
		 * store the pointer which points to the last processed
		 * template node
		 */
			Current_Node->ttop_of_stack->tcp_save = Prev_Node->ttop_of_stack;

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			if (Prev_Node->front)
			{	/* more subnodes to process */
			/* point to the next immediate sibling */
				Current_Node = Prev_Node->front;
				Activity = FIRST;

				sprintf (User_Msg, " >> Succeed; Go to Node %s\n", Current_Node->name);
				Output_Decision ();

			}	/* if */
			else
			{	/* back to a ancestor node */
				if (Animate_Flag)
				{
					Inverse_Node_Edge (Current_Node, BACKWARD);
				}

				Prev_Node = Current_Node;
				Current_Node = Current_Node->ancestor;

				sprintf (User_Msg, " << Succeed; Back to Node %s\n", Current_Node->name);
				Output_Decision ();

				if (Animate_Flag)
				{
					Inverse_Tree_Node (Current_Node);
				}
			}	/* else */
			break;

		case FAIL:
			sprintf (User_Msg, "__(SP_fail) Primitive1 %s\n", Current_Node->name);
			Output_Decision ();
			printf ("__(SP_fail) Primitive1 %s\n", Current_Node->name);

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

		/* if the node is NOT the first immediate son  */
			if (Prev_Node != Prev_Node->ancestor->level_point)
			{

				Current_Node = Prev_Node->back;	/* !!!  */
				Activity = NEXT;

				sprintf (User_Msg, " ?? Try to check node %s\n", Current_Node->name);
				Output_Decision ();

			}	/* if */
			else
			{

				sprintf (User_Msg, " // All subnodes are tried; all of them failed\n");
				Output_Decision ();

				if (Animate_Flag)
				{
					Inverse_Node_Edge (Current_Node, BACKWARD);
				}

			/* free the stack */
				Temp_Stack = Current_Node->ttop_of_stack;
				Current_Stack = Current_Node->ttop_of_stack->backward_stack_ptr;
				Current_Stack->forward_stack_ptr = NULL;

			/* Adjust the template stack pointer */
				if (Current_Node->ttop_of_stack->prev_stack_element)
				/* more stack elements */
					Current_Node->ttop_of_stack = Current_Node->ttop_of_stack->prev_stack_element;
				else
					Current_Node->ttop_of_stack = NULL;

			/*
			 * << move backward to the previous position in
			 * output file >>
			 */
				if (return_flag)
				{
					Output_File.c_ptr = Temp_Stack->begin;
					fseek (Output_File.f_ptr, Output_File.c_ptr, SEEK_SET);
					if (concurrent)
					{
						Current_output = seek_data (Current_output, Output_data_c_ptr - Temp_Stack->begin);
						Output_data_c_ptr = Temp_Stack->begin;
					}
				}
				else
				{
					W_Output_File.c_ptr = Temp_Stack->begin;
					fseek (W_Output_File.f_ptr, W_Output_File.c_ptr, SEEK_SET);
					if (concurrent)
					{
						Current_wk = seek_data (Current_wk, W_Output_data_c_ptr - Temp_Stack->begin);
						W_Output_data_c_ptr = Temp_Stack->begin;
					}
				}	/* end else */
				sprintf (User_Msg, " <- Backward output buffer pointer at location %d\n",
					 Output_File.c_ptr);
				Output_Decision ();

				sprintf (User_Msg, " ** Free a stack element at Node %s; adjust stack & "
					 "output pointers.\n",
					 Current_Node->name);
				Output_Decision ();
				free (Temp_Stack);
				Temp_Stack = NULL;

				Prev_Node = Current_Node;
				Current_Node = Current_Node->ancestor;

				sprintf (User_Msg, " << Back to Node %s\n", Current_Node->name);
				Output_Decision ();

				if (Animate_Flag)
				{
					Inverse_Tree_Node (Current_Node);
				}
			}	/* else */
			break;

		default:
			break;

	}			/* switch */
}




static void     S_GTimer (void)
{
	struct link_list *cur_para,
	               *tmp_para;
	char           *file_buffer;
	int             para_datai;    /* Seems to be useless.  Just read it to get it out of the file & not break anyting
				        * (Malcolm 8/8/94 */
	struct data_node *Prev_output;
	struct data_node *Prev_wk;
	size_t          timeout_msg_len;	/* Added 8/8/94 Malcolm. */
	const char     *timeout_msg;   /* Added 8/8/94 Malcolm. */
	server_command_tt command;     /* Make sure you only read a reply to the "SRV_TIMEOUT" message sent by timeout_child() */

	if (Animate_Flag)
	{
		Inverse_Node_Edge (Current_Node, FORWARD);
		Inverse_Tree_Node (Current_Node);
	}

	switch (Activity)
	{
		case FIRST:
			sprintf (User_Msg, "__(ST_first) primitive %s\n", Current_Node->name);
			Output_Decision ();
			printf ("current stck %d %s\n", Current_Stack->from_tree_type, Current_Stack->template_node_ptr->name);
			Save_variables ();

		/*
		 * Get_Parameters();
		 */

		/*
		 * S_Output_File  for storing the results of parameters'
		 * matching
		 */
			S_Output_File.c_ptr = 0;
			S_Output_File.f_ptr = retry_fopen (S_Output_File.name, "w");
			setbuf (S_Output_File.f_ptr, NULL);	/* Do not buffer I/O */

		/* add   April  1992    */
			cur_para = Current_Node->para;	/* Linked list of parameters of Current_Node->name */
			if (*(cur_para->name) == 39)	/* ESC character. */
			{

			/*
			 * Strip the leading and trailing single-quote
			 * characters from cur_para-> name, and store the
			 * resulting string in User_Msg.
			 */
				sprintf (User_Msg, "");
				strncat (User_Msg, cur_para->name + 1, strlen (cur_para->name) - 2);
				User_Msg[strlen (cur_para->name) - 2] = '\0';
				retry_fputs (User_Msg, S_Output_File.f_ptr);
				printf ("pointer loc %d\n", S_Output_File.c_ptr);
				S_Output_File.c_ptr = S_Output_File.c_ptr + strlen (cur_para->name) - 2;
				printf ("pointer loc %d\n", S_Output_File.c_ptr);
				printf ("=====>para_data %s------ %s\n", User_Msg, cur_para->name);
				cur_para = cur_para->next;
			}
			else
			{
				printf ("check parameteres \n");
				tmp_para = cur_para;
				Activity = FIRST;
				S_Direct_Product1 (tmp_para);
				printf ("pointer loc %d\n", S_Output_File.c_ptr);
			}

		/* add   carriage return  to the output file of parameters   */

		/*
		 * without it, analysis can not reach the end of file,
		 * analysis will fail
		 */
			add_carriage_return (S_Output_File.f_ptr);
			fclose (S_Output_File.f_ptr);

			Restore_variables ();
		/* push a stack element for template node */
			Temp_Stack = Stack_Allocation ();
			if (return_flag)
			{
				Temp_Stack->begin = Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS;
			}
			else
			{
				Temp_Stack->begin = W_Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = W_Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS1;
			}

		/* add April    1992   */
		/* restore input file      */
			S_Output_File.f_ptr = retry_fopen (S_Output_File.name, "r");
			setbuf (S_Output_File.f_ptr, NULL);	/* Do not buffer I/O */
			DESC_File_Stat = Get_File_Stat (S_Output_File.name);
			file_buffer = (char *) calloc (DESC_File_Stat.st_size + 1, sizeof (char));
			while (retry_fgets (DESC_Line_Str, MAX_LINE_SIZE, S_Output_File.f_ptr) != NULL)
			{
				strcat (file_buffer, DESC_Line_Str);
			}

			fclose (S_Output_File.f_ptr);
			sscanf (file_buffer, "%d", &para_datai);
			free (file_buffer);
			printf ("(Processing TIMEOUT:)$$$$$$$pid in gtime %d (actually para_datai)\n", para_datai);
			while ((command = receive_fm_parent (child2parent, &timeout_msg_len)) != SRV_TIMEOUT)
			{
			/* You intercepted the wrong message! send it back! */
				timeout_msg = reply_fifo_data (child2parent);
				printf ("Wrong message! %s \"%s\"\n", commandval2string (command), timeout_msg);
				fflush (stdout);
				send2parent (parent2child, command, timeout_msg);
			}
			timeout_msg = reply_fifo_data (child2parent);
			printf ("Received \"%s\" from timeout() in pid %d.\n", timeout_msg, getpid ());
			fflush (stdout);
			sprintf (User_Msg, "%s", timeout_msg);
			if (return_flag)
			{
				retry_fputs (User_Msg, Output_File.f_ptr);
				Output_File.c_ptr = Output_File.c_ptr + strlen (User_Msg);
				if (concurrent)
				{
					Current_output->next = (struct data_node *) calloc (1, sizeof (struct data_node));
					Prev_output = Current_output;
					Current_output = Current_output->next;
					Current_output->data = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
					strcpy (Current_output->data, User_Msg);
					Current_output->next = NULL;
					Current_output->front = Prev_output;
					Output_data_c_ptr++;
				}
			}
			else
			{
				retry_fputs (User_Msg, W_Output_File.f_ptr);
				W_Output_File.c_ptr = W_Output_File.c_ptr + strlen (User_Msg);
				if (concurrent)
				{
					Current_wk->next = (struct data_node *) calloc (1, sizeof (struct data_node));
					Prev_wk = Current_wk;
					Current_wk = Current_wk->next;
					Current_wk->data = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
					strcpy (Current_wk->data, User_Msg);
					Current_wk->next = NULL;
					Current_wk->front = Prev_wk;
					W_Output_data_c_ptr++;
				}
			}	/* end else */

			Activity = SUCCEED;

			if (return_flag)
			{
				Temp_Stack->end = Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->end = Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS;
			}
			else
			{
				Temp_Stack->end = W_Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->end = W_Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS1;
			}
			Locate_Stack_Element ();
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

		/* adjust template node pointer to ancestor node */
			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			if (Activity == FAIL)
			{
				sprintf (User_Msg, " FAIL<< Back to Node %s\n", Current_Node->name);
				printf (" FAIL<< Back to Node \n");
				Output_Decision ();
			}
			else if (Activity == SUCCEED)
			{
				sprintf (User_Msg, " SUCCEED<< Back to Node %s\n", Current_Node->name);
				printf (" SUCCEED<< Back to Node \n");
				Output_Decision ();
			}


			break;

		case NEXT:
			sprintf (User_Msg, "__(ST_next) Module %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

		/* free the stack */
			Temp_Stack = Current_Node->ttop_of_stack;
			Current_Stack = Current_Node->ttop_of_stack->backward_stack_ptr;
			Current_Stack->forward_stack_ptr = NULL;

		/* Adjust the template stack pointer */
			if (Current_Node->ttop_of_stack->prev_stack_element)
			/* more stack elements */
				Current_Node->ttop_of_stack = Current_Node->ttop_of_stack->prev_stack_element;
			else
				Current_Node->ttop_of_stack = NULL;

		/*
		 * Move backward to the previous position in output file
		 */
			if (return_flag)
			{
				Output_File.c_ptr = Temp_Stack->begin;
				fseek (Output_File.f_ptr, Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_output = seek_data (Current_output, Output_data_c_ptr - Temp_Stack->begin);
					Output_data_c_ptr = Temp_Stack->begin;
				}
			}
			else
			{
				W_Output_File.c_ptr = Temp_Stack->begin;
				fseek (W_Output_File.f_ptr, W_Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_wk = seek_data (Current_wk, W_Output_data_c_ptr - Temp_Stack->begin);
					W_Output_data_c_ptr = Temp_Stack->begin;
				}
			}	/* end else */
			sprintf (User_Msg, " <- Backward output buffer pointer at location %d\n",
				 Output_File.c_ptr);
			Output_Decision ();

			sprintf (User_Msg, " ** Free a stack element at Node %s; adjust stack & "
				 "output pointers.\n",
				 Current_Node->name);
			Output_Decision ();
			free (Temp_Stack);
			Temp_Stack = NULL;

			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			sprintf (User_Msg, " << Fail; Back to Node %s\n", Current_Node->name);
			Output_Decision ();

			client_blink_window ();
			Activity = FAIL;
			break;

		default:
			break;

	}			/* switch */
}



static void     S_Timer (void)
{
	struct link_list *cur_para,
	               *tmp_para;
	char           *file_buffer;
	int             para_datai,
	                pid;
	struct data_node *Prev_output;
	struct data_node *Prev_wk;

	printf ("Process %d ENTERING S_Timer()\n", getpid ());
	fflush (stdout);
	if (Animate_Flag)
	{
		Inverse_Node_Edge (Current_Node, FORWARD);
		Inverse_Tree_Node (Current_Node);
	}

	switch (Activity)
	{
		case FIRST:
			sprintf (User_Msg, "__(ST_first) primitive %s\n", Current_Node->name);
			Output_Decision ();
			printf ("current stck %d %s\n", Current_Stack->from_tree_type, Current_Stack->template_node_ptr->name);
			fflush (stdout);
			Save_variables ();

		/*
		 * Get_Parameters();
		 */

		/*
		 * S_Output_File  for storing the results of parameters'
		 * matching
		 */
			S_Output_File.c_ptr = 0;
			S_Output_File.f_ptr = retry_fopen (S_Output_File.name, "w");
			setbuf (S_Output_File.f_ptr, NULL);	/* Do not buffer I/O */

		/* add   April  1992    */
			cur_para = Current_Node->para;	/* Linked list of parameters of Current_Node->name */
			printf ("S_Timer() looking for ESC(39): cur_para-> name == \"%s\" first ch = '%c' == %d\n",
				cur_para->name, *(cur_para->name), *(cur_para->name));
			if (*(cur_para->name) == 39)	/* ESC character. */
			{
				sprintf (User_Msg, "");
				strncat (User_Msg, cur_para->name + 1, strlen (cur_para->name) - 2);
				User_Msg[strlen (cur_para->name) - 2] = '\0';
				retry_fputs (User_Msg, S_Output_File.f_ptr);
				printf ("S_Timer() wrote \"%s\" to S_Output_File \"%s\" line %d of %s\n",
					User_Msg, S_Output_File.name, __LINE__, __FILE__);
				fflush (stdout);
				printf ("pointer loc %d\n", S_Output_File.c_ptr);
				fflush (stdout);
				S_Output_File.c_ptr = S_Output_File.c_ptr + strlen (cur_para->name) - 2;
				printf ("pointer loc %d\n", S_Output_File.c_ptr);
				fflush (stdout);
				printf ("=====>para_data %s------ %s\n", User_Msg, cur_para->name);
				fflush (stdout);
				cur_para = cur_para->next;
			}
			else
			{
				printf ("check parameteres \n");
				fflush (stdout);
				tmp_para = cur_para;
				Activity = FIRST;
				S_Direct_Product1 (tmp_para);
				printf ("pointer loc %d\n", S_Output_File.c_ptr);
				fflush (stdout);
			}

		/* add   carriage return  to the output file of parameters   */

		/*
		 * without it, analysis can not reach the end of file,
		 * analysis will fail
		 */
			add_carriage_return (S_Output_File.f_ptr);
			fclose (S_Output_File.f_ptr);

			Restore_variables ();
		/* push a stack element for template node */
			Temp_Stack = Stack_Allocation ();
			if (return_flag)
			{
				Temp_Stack->begin = Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS;
			}
			else
			{
				Temp_Stack->begin = W_Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = W_Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS1;
			}

		/* add April    1992   */
		/* restore input file      */
			S_Output_File.f_ptr = retry_fopen (S_Output_File.name, "r");
			setbuf (S_Output_File.f_ptr, NULL);	/* Do not buffer I/O */
			DESC_File_Stat = Get_File_Stat (S_Output_File.name);
			file_buffer = (char *) calloc (DESC_File_Stat.st_size + 1, sizeof (char));
			while (retry_fgets (DESC_Line_Str, MAX_LINE_SIZE, S_Output_File.f_ptr) != NULL)
			{
				strcat (file_buffer, DESC_Line_Str);
				printf ("S_Timer() read \"%s\" from S_Output_File \"%s\" line %d of %s\n",
					DESC_Line_Str, S_Output_File.name, __LINE__, __FILE__);
				fflush (stdout);
			}

			fclose (S_Output_File.f_ptr);
			sscanf (file_buffer, "%d", &para_datai);
			Activity = FAIL;
			signal (SIGALRM, timeout);
			alarm (para_datai);

			if (para_datai != 0)
			{
				strcpy (User_Msg, "");
				pid = getpid ();
				sprintf (User_Msg, "%d", pid);
				if (return_flag)
				{
					retry_fputs (User_Msg, Output_File.f_ptr);
					Output_File.c_ptr = Output_File.c_ptr + strlen (User_Msg);
					printf ("***pid %d %s %d\n", pid, User_Msg, Output_File.c_ptr);
					fflush (stdout);
					if (concurrent)
					{
						Current_output->next = (struct data_node *) calloc (1, sizeof (struct data_node));
						Prev_output = Current_output;
						Current_output = Current_output->next;
						Current_output->data = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
						strcpy (Current_output->data, User_Msg);
						Current_output->next = NULL;
						Current_output->front = Prev_output;
						Output_data_c_ptr++;
					}
				}
				else
				{
					retry_fputs (User_Msg, W_Output_File.f_ptr);
					W_Output_File.c_ptr = W_Output_File.c_ptr + strlen (User_Msg);
					if (concurrent)
					{
						Current_wk->next = (struct data_node *) calloc (1, sizeof (struct data_node));
						Prev_wk = Current_wk;
						Current_wk = Current_wk->next;
						Current_wk->data = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
						strcpy (Current_wk->data, User_Msg);
						Current_wk->next = NULL;
						Current_wk->front = Prev_wk;
						W_Output_data_c_ptr++;
					}
				}	/* end else */
			}
			Activity = SUCCEED;

			if (return_flag)
			{
				Temp_Stack->end = Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->end = Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS;
			}
			else
			{
				Temp_Stack->end = W_Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->end = W_Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS1;
			}
			Locate_Stack_Element ();
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}



		/* adjust template node pointer to ancestor node */
			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			if (Activity == FAIL)
			{
				sprintf (User_Msg, " FAIL<< Back to Node %s\n", Current_Node->name);
				printf (" FAIL<< Back to Node \n");
				fflush (stdout);
				Output_Decision ();
			}
			else if (Activity == SUCCEED)
			{
				sprintf (User_Msg, " SUCCEED<< Back to Node %s\n", Current_Node->name);
				printf (" SUCCEED<< Back to Node \n");
				fflush (stdout);
				Output_Decision ();
			}


			break;

		case NEXT:
			sprintf (User_Msg, "__(ST_next) Module %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

		/* free the stack */
			Temp_Stack = Current_Node->ttop_of_stack;
			Current_Stack = Current_Node->ttop_of_stack->backward_stack_ptr;
			Current_Stack->forward_stack_ptr = NULL;

		/* Adjust the template stack pointer */
			if (Current_Node->ttop_of_stack->prev_stack_element)
			/* more stack elements */
				Current_Node->ttop_of_stack = Current_Node->ttop_of_stack->prev_stack_element;
			else
				Current_Node->ttop_of_stack = NULL;

		/*
		 * Move backward to the previous position in output file
		 */
			if (return_flag)
			{
				Output_File.c_ptr = Temp_Stack->begin;
				fseek (Output_File.f_ptr, Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_output = seek_data (Current_output, Output_data_c_ptr - Temp_Stack->begin);
					Output_data_c_ptr = Temp_Stack->begin;
				}
			}
			else
			{
				W_Output_File.c_ptr = Temp_Stack->begin;
				fseek (W_Output_File.f_ptr, W_Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_wk = seek_data (Current_wk, W_Output_data_c_ptr - Temp_Stack->begin);
					W_Output_data_c_ptr = Temp_Stack->begin;
				}
			}	/* end else */
			sprintf (User_Msg, " <- Backward output buffer pointer at location %d\n",
				 Output_File.c_ptr);
			Output_Decision ();

			sprintf (User_Msg, " ** Free a stack element at Node %s; adjust stack & "
				 "output pointers.\n",
				 Current_Node->name);
			Output_Decision ();
			free (Temp_Stack);
			Temp_Stack = NULL;

			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			sprintf (User_Msg, " << Fail; Back to Node %s\n", Current_Node->name);
			Output_Decision ();

			client_blink_window ();
			Activity = FAIL;
			break;

		default:
			break;

	}			/* switch */
	printf ("Process %d LEAVING S_Timer()\n", getpid ());
	fflush (stdout);
}


static void     S_Delay (void)
{
	struct link_list *cur_para,
	               *tmp_para;
	char           *file_buffer;
	int             para_datai;

	if (Animate_Flag)
	{
		Inverse_Node_Edge (Current_Node, FORWARD);
		Inverse_Tree_Node (Current_Node);
	}

	printf ("Process %d ENTERING S_Delay()\n", getpid ());
	fflush (stdout);

	switch (Activity)
	{
		case FIRST:
			sprintf (User_Msg, "__(SD_first) Delay %s\n", Current_Node->name);
			Output_Decision ();
			printf ("current stck %d %s\n", Current_Stack->from_tree_type, Current_Stack->template_node_ptr->name);
			fflush (stdout);
			Save_variables ();

		/*
		 * S_Output_File  for storing the results of parameters'
		 * matching
		 */
			S_Output_File.c_ptr = 0;
			S_Output_File.f_ptr = retry_fopen (S_Output_File.name, "w");
			setbuf (S_Output_File.f_ptr, NULL);	/* Do not buffer I/O */

		/* add   April  1992    */
			cur_para = Current_Node->para;	/* Linked list of parameters of Current_Node->name */
			printf ("S_Delay() looking for ESC(39): cur_para-> name == \"%s\" first ch = '%c' == %d\n",
				cur_para->name, *(cur_para->name), *(cur_para->name));
			if (*(cur_para->name) == 39)	/* ESC character. */
			{
				sprintf (User_Msg, "");
				strncat (User_Msg, cur_para->name + 1, strlen (cur_para->name) - 2);
				User_Msg[strlen (cur_para->name) - 2] = '\0';
				retry_fputs (User_Msg, S_Output_File.f_ptr);
				printf ("S_Delay() wrote \"%s\" to S_Output_File \"%s\" line %d of %s\n",
					User_Msg, S_Output_File.name, __LINE__, __FILE__);
				printf ("pointer loc %d\n", S_Output_File.c_ptr);
				fflush (stdout);
				S_Output_File.c_ptr = S_Output_File.c_ptr + strlen (cur_para->name) - 2;
				printf ("pointer loc %d\n", S_Output_File.c_ptr);
				fflush (stdout);
				printf ("=====>para_data %s------ %s\n", User_Msg, cur_para->name);
				fflush (stdout);
				cur_para = cur_para->next;
			}
			else
			{
				printf ("check parameteres \n");
				fflush (stdout);
				tmp_para = cur_para;
				Activity = FIRST;
				S_Direct_Product1 (tmp_para);
				printf ("pointer loc %d\n", S_Output_File.c_ptr);
				fflush (stdout);

			}

		/*
		 * Add   carriage return  to the output file of parameters.
		 * Without it, analysis can not reach the end of file,
		 * analysis will fail
		 */
			add_carriage_return (S_Output_File.f_ptr);
			fclose (S_Output_File.f_ptr);

			Restore_variables ();
		/* push a stack element for template node */
			Temp_Stack = Stack_Allocation ();
			if (return_flag)
			{
				Temp_Stack->begin = Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS;
			}
			else
			{
				Temp_Stack->begin = W_Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = W_Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS1;
			}

		/* add April    1992   */
		/* restore input file      */
			S_Output_File.f_ptr = retry_fopen (S_Output_File.name, "r");
			setbuf (S_Output_File.f_ptr, NULL);	/* Do not buffer I/O */
			DESC_File_Stat = Get_File_Stat (S_Output_File.name);
			file_buffer = (char *) calloc (DESC_File_Stat.st_size + 1, sizeof (char));
			while (retry_fgets (DESC_Line_Str, MAX_LINE_SIZE, S_Output_File.f_ptr) != NULL)
			{
				strcat (file_buffer, DESC_Line_Str);
				printf ("S_Delay() read \"%s\" from S_Output_File \"%s\" line %d of %s\n",
					DESC_Line_Str, S_Output_File.name, __LINE__, __FILE__);
				fflush (stdout);
			}

			fclose (S_Output_File.f_ptr);
			sscanf (file_buffer, "%d", &para_datai);
			printf ("delay time= %d\n", para_datai);
			fflush (stdout);
			Activity = FAIL;
			sleep (para_datai);
			Activity = SUCCEED;

			if (return_flag)
			{
				Temp_Stack->end = Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->end = Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS;
			}
			else
			{
				Temp_Stack->end = W_Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->end = W_Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS1;
			}
			Locate_Stack_Element ();
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}



		/* adjust template node pointer to ancestor node */
			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			if (Activity == FAIL)
			{
				sprintf (User_Msg, " FAIL<< Back to Node %s\n", Current_Node->name);
				printf (" FAIL<< Back to Node \n");
				fflush (stdout);
				Output_Decision ();
			}
			else if (Activity == SUCCEED)
			{
				sprintf (User_Msg, " SUCCEED<< Back to Node %s\n", Current_Node->name);
				printf (" SUCCEED<< Back to Node \n");
				fflush (stdout);
				Output_Decision ();
			}


			break;

		case NEXT:
			sprintf (User_Msg, "__(SD_next) Delay %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

		/* free the stack */
			Temp_Stack = Current_Node->ttop_of_stack;
			Current_Stack = Current_Node->ttop_of_stack->backward_stack_ptr;
			Current_Stack->forward_stack_ptr = NULL;

		/* Adjust the template stack pointer */
			if (Current_Node->ttop_of_stack->prev_stack_element)
			/* more stack elements */
				Current_Node->ttop_of_stack = Current_Node->ttop_of_stack->prev_stack_element;
			else
				Current_Node->ttop_of_stack = NULL;

		/*
		 * Move backward to the previous position in output file
		 */
			if (return_flag)
			{
				Output_File.c_ptr = Temp_Stack->begin;
				fseek (Output_File.f_ptr, Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_output = seek_data (Current_output, Output_data_c_ptr - Temp_Stack->begin);
					Output_data_c_ptr = Temp_Stack->begin;
				}
			}
			else
			{
				W_Output_File.c_ptr = Temp_Stack->begin;
				fseek (W_Output_File.f_ptr, W_Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					W_Output_data_c_ptr = Temp_Stack->begin;
					Current_wk = seek_data (Current_wk, W_Output_data_c_ptr - Temp_Stack->begin);
				}
			}	/* end else  */
			sprintf (User_Msg, " <- Backward output buffer pointer at location %d\n",
				 Output_File.c_ptr);
			Output_Decision ();

			sprintf (User_Msg, " ** Free a stack element at Node %s; adjust stack & "
				 "output pointers.\n",
				 Current_Node->name);
			Output_Decision ();
			free (Temp_Stack);
			Temp_Stack = NULL;

			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			sprintf (User_Msg, " << Fail; Back to Node %s\n", Current_Node->name);
			Output_Decision ();

			client_blink_window ();
			Activity = FAIL;
			break;

		default:
			break;

	}			/* switch */
	printf ("Process %d LEAVING S_Delay()\n", getpid ());
	fflush (stdout);
}



static void     S_Receive (int syn)
{
	struct link_list *cur_para,
	               *tmp_para;
	char           *file_buffer;
	char            para_data[80];
	int             para_datai;
	int             msgid1;
	int             n;
	Mesg            mesg;
	long            key;
	struct data_node *Prev_output;
	struct data_node *Prev_wk;

	if (Animate_Flag)
	{
		Inverse_Node_Edge (Current_Node, FORWARD);
		Inverse_Tree_Node (Current_Node);
	}

	switch (Activity)
	{
		case FIRST:
			sprintf (User_Msg, "__(SR_first) Receive  %s\n", Current_Node->name);
			Output_Decision ();

			Save_variables ();

		/*
		 * S_Output_File  for storing the results of parameters'
		 * matching
		 */
			S_Output_File.c_ptr = 0;
			S_Output_File.f_ptr = retry_fopen (S_Output_File.name, "w");
			setbuf (S_Output_File.f_ptr, NULL);	/* Do not buffer I/O */

		/* add   April  1992    */
			cur_para = Current_Node->para;	/* Linked list of parameters of Current_Node->name */
			if (*(cur_para->name) == 39)	/* ESC character. */
			{
				sprintf (User_Msg, "");
				strncat (User_Msg, cur_para->name + 1, strlen (cur_para->name) - 2);
				User_Msg[strlen (cur_para->name) - 2] = '\0';
				retry_fputs (User_Msg, S_Output_File.f_ptr);
				printf ("pointer loc %d\n", S_Output_File.c_ptr);
				S_Output_File.c_ptr = S_Output_File.c_ptr + strlen (cur_para->name) - 2;
				printf ("pointer loc %d\n", S_Output_File.c_ptr);
				printf ("=====>para_data %s------ %s\n", User_Msg, cur_para->name);
				cur_para = cur_para->next;
			}
			else
			{
				printf ("check parameteres \n");
				tmp_para = cur_para;
				Activity = FIRST;
				S_Direct_Product1 (tmp_para);
				printf ("pointer loc %d\n", S_Output_File.c_ptr);

			}

		/*
		 * Add   carriage return  to the output file of parameters.
		 * Without it, analysis can not reach the end of file,
		 * analysis will fail
		 */
			add_carriage_return (S_Output_File.f_ptr);
			fclose (S_Output_File.f_ptr);

			Restore_variables ();
		/* push a stack element for template node */
			Temp_Stack = Stack_Allocation ();
			if (return_flag)
			{
				Temp_Stack->begin = Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS;
			}
			else
			{
				Temp_Stack->begin = W_Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = W_Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS1;
			}

		/* add April    1992   */
		/* restore input file      */
			S_Output_File.f_ptr = retry_fopen (S_Output_File.name, "r");
			setbuf (S_Output_File.f_ptr, NULL);	/* Do not buffer I/O */
			DESC_File_Stat = Get_File_Stat (S_Output_File.name);
			file_buffer = (char *) calloc (DESC_File_Stat.st_size + 1, sizeof (char));
			strcpy (file_buffer, "");
			while (retry_fgets (DESC_Line_Str, MAX_LINE_SIZE, S_Output_File.f_ptr) != NULL)
			{
				strcat (file_buffer, DESC_Line_Str);
			}

			fclose (S_Output_File.f_ptr);
			printf ("S file ptr  %d %s\n", S_Output_File.c_ptr, file_buffer);
			strcpy (para_data, file_buffer);
			free (file_buffer);
			file_buffer = NULL;
			sscanf (para_data, "%d", &para_datai);
			printf ("sum of output in rece  %s-\n", para_data);

			if (syn == 1)
			{
			/* wait for send     */
				sem_wait (client);
			}
			printf ("waiting in rece  %s-\n", para_data);

			key = (long) para_datai;
			if ((msgid1 = msgget (MSGKEY1, 0)) < 0)
				printf ("can not get message queue \n");
			mesg.mesg_type = key;

			if (syn == 1)
			{
				if ((n = mesg_recv (msgid1, &mesg)) <= 0)
					printf ("message read error \n");
			}
			else
			{
				if ((n = mesg_arecv (msgid1, &mesg)) <= 0)
					printf ("message read error \n");
			}
			mesg.mesg_data[n] = '\0';

			printf ("RECEIVE message data len %s %d\n", mesg.mesg_data, n);
			sprintf (User_Msg, "%s", mesg.mesg_data);

			Output_Decision ();

			if (return_flag)
			{
				retry_fputs (User_Msg, Output_File.f_ptr);
				Output_File.c_ptr = Output_File.c_ptr + strlen (User_Msg);
				if (concurrent)
				{
					Current_output->next = (struct data_node *) calloc (1, sizeof (struct data_node));
					Prev_output = Current_output;
					Current_output = Current_output->next;
					Current_output->data = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
					strcpy (Current_output->data, User_Msg);
					Current_output->next = NULL;
					Current_output->front = Prev_output;
					Output_data_c_ptr++;
				}
			}
			else
			{
				retry_fputs (User_Msg, W_Output_File.f_ptr);
				W_Output_File.c_ptr = W_Output_File.c_ptr + strlen (User_Msg);
				if (concurrent)
				{
					Current_wk->next = (struct data_node *) calloc (1, sizeof (struct data_node));
					Prev_wk = Current_wk;
					Current_wk = Current_wk->next;
					Current_wk->data = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
					strcpy (Current_wk->data, User_Msg);
					Current_wk->next = NULL;
					Current_wk->front = Prev_wk;
					W_Output_data_c_ptr++;
				}
			}	/* end else */

			if (return_flag)
			{
				Temp_Stack->end = Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->end = Output_data_c_ptr;
			}
			else
			{
				Temp_Stack->end = W_Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->end = W_Output_data_c_ptr;
			}
			Locate_Stack_Element ();

			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}



		/* adjust template node pointer to ancestor node */
			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			if (Activity == FAIL)
			{
				sprintf (User_Msg, " FAIL<< Back to Node %s\n", Current_Node->name);
				printf (" FAIL<< Back to Node \n");
				Output_Decision ();
			}
			else if (Activity == SUCCEED)
			{
				sprintf (User_Msg, " SUCCEED<< Back to Node %s\n", Current_Node->name);
				printf (" SUCCEED<< Back to Node \n");
				Output_Decision ();
			}


			break;

		case NEXT:
			sprintf (User_Msg, "__(SR_next) Receive  %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

		/* free the stack */
			Temp_Stack = Current_Node->ttop_of_stack;
			Current_Stack = Current_Node->ttop_of_stack->backward_stack_ptr;
			Current_Stack->forward_stack_ptr = NULL;

		/* Adjust the template stack pointer */
			if (Current_Node->ttop_of_stack->prev_stack_element)
			/* more stack elements */
				Current_Node->ttop_of_stack = Current_Node->ttop_of_stack->prev_stack_element;
			else
				Current_Node->ttop_of_stack = NULL;

		/*
		 * Move backward to the previous position in output file
		 */
			if (return_flag)
			{
				Output_File.c_ptr = Temp_Stack->begin;
				fseek (Output_File.f_ptr, Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_output = seek_data (Current_output, Output_data_c_ptr - Temp_Stack->begin);
					Output_data_c_ptr = Temp_Stack->begin;
				}
			}
			else
			{
				W_Output_File.c_ptr = Temp_Stack->begin;
				fseek (W_Output_File.f_ptr, W_Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_wk = seek_data (Current_wk, W_Output_data_c_ptr - Temp_Stack->begin);
					W_Output_data_c_ptr = Temp_Stack->begin;
				}
			}	/* end else */
			sprintf (User_Msg, " <- Backward output buffer pointer at location %d\n",
				 Output_File.c_ptr);
			Output_Decision ();

			sprintf (User_Msg, " ** Free a stack element at Node %s; adjust stack & "
				 "output pointers.\n",
				 Current_Node->name);
			Output_Decision ();
			free (Temp_Stack);
			Temp_Stack = NULL;

			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			sprintf (User_Msg, " << Fail; Back to Node %s\n", Current_Node->name);
			Output_Decision ();

			client_blink_window ();
			Activity = FAIL;
			break;

		default:
			break;

	}			/* switch */
}




static void     S_Send (int syn)
{
	struct link_list *cur_para,
	               *tmp_para;
	char           *file_buffer;
	int             separter[3];
	char            para_data1[80];
	char            para_data2[80];
	int             para_datai1;
	int             para_datai2;
	int             i;
	int             msgid1;
	Mesg            mesg;
	long            key;
	struct data_node *Prev_output;
	struct data_node *Prev_wk;

	if (Animate_Flag)
	{
		Inverse_Node_Edge (Current_Node, FORWARD);
		Inverse_Tree_Node (Current_Node);
	}

	switch (Activity)
	{
		case FIRST:
			sprintf (User_Msg, "__(SS_first) send  %s\n", Current_Node->name);
			Output_Decision ();
			Save_variables ();

		/*
		 * S_Output_File  for storing the results of parameters'
		 * matching
		 */
			S_Output_File.c_ptr = 0;
			S_Output_File.f_ptr = retry_fopen (S_Output_File.name, "w");
			setbuf (S_Output_File.f_ptr, NULL);	/* Do not buffer I/O */

		/* add   April  1992    */
			cur_para = Current_Node->para;	/* Linked list of parameters of Current_Node->name */
		/* while(cur_para)  */
			for (i = 0; i < 2; i++)
			{
				if (*(cur_para->name) == 39)	/* ESC character. */
				{
					sprintf (User_Msg, "");
					strncat (User_Msg, cur_para->name + 1, strlen (cur_para->name) - 2);
					User_Msg[strlen (cur_para->name) - 2] = '\0';
					retry_fputs (User_Msg, S_Output_File.f_ptr);
					printf ("pointer loc %d\n", S_Output_File.c_ptr);
					S_Output_File.c_ptr = S_Output_File.c_ptr + strlen (cur_para->name) - 2;
					printf ("pointer loc %d\n", S_Output_File.c_ptr);
					printf ("=====>para_data %s------ %s\n", User_Msg, cur_para->name);
					separter[i] = S_Output_File.c_ptr;
					cur_para = cur_para->next;
				}
				else
				{
					printf ("check parameteres in send\n");
					tmp_para = cur_para;
					Activity = FIRST;
					S_Direct_Product1 (tmp_para);
					separter[i] = S_Output_File.c_ptr;
					printf ("pointer loc %d\n", S_Output_File.c_ptr);
					if (Activity == SUCCEED)
					{
						cur_para = cur_para->next;
					}
					else
						break;

				}
			}

		/*
		 * Add   carriage return  to the output file of parameters.
		 * Without it, analysis can not reach the end of file,
		 * analysis will fail
		 */
			add_carriage_return (S_Output_File.f_ptr);
			fclose (S_Output_File.f_ptr);

			Restore_variables ();
		/* push a stack element for template node */
			Temp_Stack = Stack_Allocation ();
			if (return_flag)
			{
				Temp_Stack->begin = Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS;
			}
			else
			{
				Temp_Stack->begin = W_Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = W_Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS1;
			}

		/* add April    1992   */
		/* restore input file      */
			S_Output_File.f_ptr = retry_fopen (S_Output_File.name, "r");
			setbuf (S_Output_File.f_ptr, NULL);	/* Do not buffer I/O */
			retry_fgets (para_data1, separter[0] + 1, S_Output_File.f_ptr);
			retry_fgets (para_data2, S_Output_File.c_ptr - separter[0] + 1, S_Output_File.f_ptr);

			DESC_File_Stat = Get_File_Stat (S_Output_File.name);
			file_buffer = (char *) calloc (DESC_File_Stat.st_size + 1, sizeof (char));
			while (retry_fgets (DESC_Line_Str, MAX_LINE_SIZE, S_Output_File.f_ptr) != NULL)
			{
				strcat (file_buffer, DESC_Line_Str);
			}

			fclose (S_Output_File.f_ptr);

			printf ("send file buffer %s\n", file_buffer);
			printf ("sep %d %d\n", separter[0], S_Output_File.c_ptr);

			free (file_buffer);
			sscanf (para_data1, "%d", &para_datai1);
			sscanf (para_data2, "%d", &para_datai2);
			printf ("sum of output %s, %s in send \n", para_data1, para_data2);
			printf ("sum of output %d, %d in send \n", para_datai1, para_datai2);

			key = (long) para_datai2;
			if ((msgid1 = msgget (MSGKEY1, 0)) < 0)
				printf ("can not get message queue \n");

			sprintf (User_Msg, "%s", para_data1);
			Output_Decision ();

			mesg.mesg_type = key;
			strcpy (mesg.mesg_data, para_data1);
			mesg.mesg_len = strlen (mesg.mesg_data);
			mesg_send (msgid1, &mesg);

			if (syn == 1)
			{
				sem_signal (client);
				printf ("afer send %s", para_data1);
			}

			if (return_flag)
			{
				retry_fputs (User_Msg, Output_File.f_ptr);
				Output_File.c_ptr = Output_File.c_ptr + strlen (User_Msg);
				if (concurrent)
				{
					Current_output->next = (struct data_node *) calloc (1, sizeof (struct data_node));
					Prev_output = Current_output;
					Current_output = Current_output->next;
					Current_output->data = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
					strcpy (Current_output->data, User_Msg);
					Current_output->next = NULL;
					Current_output->front = Prev_output;
					Output_data_c_ptr++;
				}
			}
			else
			{
				retry_fputs (User_Msg, W_Output_File.f_ptr);
				W_Output_File.c_ptr = W_Output_File.c_ptr + strlen (User_Msg);
				if (concurrent)
				{
					Current_wk->next = (struct data_node *) calloc (1, sizeof (struct data_node));
					Prev_wk = Current_wk;
					Current_wk = Current_wk->next;
					Current_wk->data = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
					strcpy (Current_wk->data, User_Msg);
					Current_wk->next = NULL;
					Current_wk->front = Prev_wk;
					W_Output_data_c_ptr++;
				}
			}	/* end else */

			if (return_flag)
			{
				Temp_Stack->end = Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->end = Output_data_c_ptr;
			}
			else
			{
				Temp_Stack->end = W_Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->end = W_Output_data_c_ptr;
			}
			Locate_Stack_Element ();

			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}



		/* adjust template node pointer to ancestor node */
			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			if (Activity == FAIL)
			{
				sprintf (User_Msg, " FAIL<< Back to Node %s\n", Current_Node->name);
				printf (" FAIL<< Back to Node \n");
				Output_Decision ();
			}
			else if (Activity == SUCCEED)
			{
				sprintf (User_Msg, " SUCCEED<< Back to Node %s\n", Current_Node->name);
				printf (" SUCCEED<< Back to Node \n");
				Output_Decision ();
			}


			break;

		case NEXT:
			sprintf (User_Msg, "__(SS_next) Send  %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

		/* free the stack */
			Temp_Stack = Current_Node->ttop_of_stack;
			Current_Stack = Current_Node->ttop_of_stack->backward_stack_ptr;
			Current_Stack->forward_stack_ptr = NULL;

		/* Adjust the template stack pointer */
			if (Current_Node->ttop_of_stack->prev_stack_element)
			/* more stack elements */
				Current_Node->ttop_of_stack = Current_Node->ttop_of_stack->prev_stack_element;
			else
				Current_Node->ttop_of_stack = NULL;

		/*
		 * Move backward to the previous position in output file
		 */
			if (return_flag)
			{
				Output_File.c_ptr = Temp_Stack->begin;
				fseek (Output_File.f_ptr, Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_output = seek_data (Current_output, Output_data_c_ptr - Temp_Stack->begin);
					Output_data_c_ptr = Temp_Stack->begin;
				}
			}
			else
			{
				W_Output_File.c_ptr = Temp_Stack->begin;
				fseek (W_Output_File.f_ptr, W_Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_wk = seek_data (Current_wk, W_Output_data_c_ptr - Temp_Stack->begin);
					W_Output_data_c_ptr = Temp_Stack->begin;
				}
			}	/* end else */
			sprintf (User_Msg, " <- Backward output buffer pointer at location %d\n",
				 Output_File.c_ptr);
			Output_Decision ();

			sprintf (User_Msg, " ** Free a stack element at Node %s; adjust stack & "
				 "output pointers.\n",
				 Current_Node->name);
			Output_Decision ();
			free (Temp_Stack);

			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			sprintf (User_Msg, " << Fail; Back to Node %s\n", Current_Node->name);
			Output_Decision ();

			client_blink_window ();
			Activity = FAIL;
			break;

		default:
			break;

	}			/* switch */
}				       /* end S_Send() */


static void     S_Primitives2 (void)
{
	struct link_list *cur_para,
	               *tmp_para;
	char           *file_buffer;
	int             separter[3];
	char            para_data1[80];
	char            para_data2[80];
	int             para_datai1;
	int             para_datai2;
	int             i;
	long            seconds;
	static int      rand;
	struct data_node *Prev_output;
	struct data_node *Prev_wk;

	if (Animate_Flag)
	{
		Inverse_Node_Edge (Current_Node, FORWARD);
		Inverse_Tree_Node (Current_Node);
	}

	switch (Activity)
	{
		case FIRST:
			sprintf (User_Msg, "__(SP_first) primitive  %s\n", Current_Node->name);
			Output_Decision ();
			Save_variables ();

		/*
		 * S_Output_File  for storing the results of parameters'
		 * matching
		 */
			S_Output_File.c_ptr = 0;
			S_Output_File.f_ptr = retry_fopen (S_Output_File.name, "w");
			setbuf (S_Output_File.f_ptr, NULL);	/* Do not buffer I/O */

		/* add   April  1992    */
			cur_para = Current_Node->para;	/* Linked list of parameters of Current_Node->name */
		/* while(cur_para)  */
			for (i = 0; i < 2; i++)
			{
				if (*(cur_para->name) == 39)	/* ESC character. */
				{
					sprintf (User_Msg, "");
					strncat (User_Msg, cur_para->name + 1, strlen (cur_para->name) - 2);
					User_Msg[strlen (cur_para->name) - 2] = '\0';
					retry_fputs (User_Msg, S_Output_File.f_ptr);
					printf ("pointer loc %d\n", S_Output_File.c_ptr);
					S_Output_File.c_ptr = S_Output_File.c_ptr + strlen (cur_para->name) - 2;
					printf ("pointer loc %d\n", S_Output_File.c_ptr);
					printf ("=====>para_data %s------ %s\n", User_Msg, cur_para->name);
					separter[i] = S_Output_File.c_ptr;
					cur_para = cur_para->next;
				}
				else
				{
					printf ("check parameteres \n");
					tmp_para = cur_para;
					Activity = FIRST;
					S_Direct_Product1 (tmp_para);
					separter[i] = S_Output_File.c_ptr;
					printf ("pointer loc %d\n", S_Output_File.c_ptr);
					if (Activity == SUCCEED)
					{
						cur_para = cur_para->next;
					}
					else
						break;

				}
			}

		/*
		 * Add   carriage return  to the output file of parameters.
		 * without it, analysis can not reach the end of file,
		 * analysis will fail
		 */
			add_carriage_return (S_Output_File.f_ptr);
			fclose (S_Output_File.f_ptr);

			Restore_variables ();
		/* push a stack element for template node */
			Temp_Stack = Stack_Allocation ();
			if (return_flag)
			{
				Temp_Stack->begin = Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS;
			}
			else
			{
				Temp_Stack->begin = W_Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = W_Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS1;
			}

		/* add April    1992   */
		/* restore input file      */
			S_Output_File.f_ptr = retry_fopen (S_Output_File.name, "r");
			setbuf (S_Output_File.f_ptr, NULL);	/* Do not buffer I/O */
			DESC_File_Stat = Get_File_Stat (S_Output_File.name);
			file_buffer = (char *) calloc (DESC_File_Stat.st_size + 1, sizeof (char));
			while (retry_fgets (DESC_Line_Str, MAX_LINE_SIZE, S_Output_File.f_ptr) != NULL)
			{
				strcat (file_buffer, DESC_Line_Str);
			}

			fclose (S_Output_File.f_ptr);
			printf ("sep %d %d %d\n", separter[0], S_Output_File.c_ptr, DESC_File_Stat.st_size);
			strcpy (para_data1, "");
			printf ("sum of  %s\n", para_data1);
			strncpy (para_data1, file_buffer, separter[0]);
			para_data1[separter[0]] = '\0';
			printf ("sum of  %s,%s\n", para_data1, file_buffer);
			printf ("sum of  %s,%s\n", para_data1, file_buffer);
			strcpy (para_data2, "");
			strncpy (para_data2, file_buffer + separter[0], S_Output_File.c_ptr - separter[0]);
			para_data2[S_Output_File.c_ptr - separter[0]] = '\0';	/* MALCOLM possible suspect change. */
			printf ("sum of output %s, %s\n", para_data1, para_data2);
			printf ("paramers %s", file_buffer);
			free (file_buffer);
		/* comparsion of two parameters */
			sscanf (para_data1, "%d", &para_datai1);
			sscanf (para_data2, "%d", &para_datai2);

			switch (Current_Node->type)
			{
				case PLUS:
					printf ("sum of output %s, %s\n", para_data1, para_data2);
					para_datai1 = para_datai1 + para_datai2;
					break;

				case MINUS:
					printf ("sum of output %s, %s\n", para_data1, para_data2);
					para_datai1 = para_datai1 - para_datai2;
					break;

				case TIMES:
					printf ("sum of output %s, %s\n", para_data1, para_data2);
					para_datai1 = para_datai1 * para_datai2;
					break;

				case DIVIDED_BY:
					printf ("sum of output %s, %s\n", para_data1, para_data2);
					para_datai1 = para_datai1 / para_datai2;
					break;

				case RANDOM:
					printf ("random of output %s, %s\n", para_data1, para_data2);
					time (&seconds);
					rand = 0x7fff & ((int) seconds + rand * 273) >> 4;
					para_datai1 = (rand % para_datai1);

					break;

				default:
					break;
			}

			printf ("sum of output %d %d\n", para_datai1, para_datai2);
			sprintf (User_Msg, "");
			sprintf (User_Msg, "%d", para_datai1);

			if (return_flag)
			{
				retry_fputs (User_Msg, Output_File.f_ptr);
				Output_File.c_ptr = Output_File.c_ptr + strlen (User_Msg);
				if (concurrent)
				{
					Current_output->next = (struct data_node *) calloc (1, sizeof (struct data_node));
					Prev_output = Current_output;
					Current_output = Current_output->next;
					Current_output->data = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
					strcpy (Current_output->data, User_Msg);
					Current_output->next = NULL;
					Current_output->front = Prev_output;
					Output_data_c_ptr++;
				}
			}
			else
			{
				retry_fputs (User_Msg, W_Output_File.f_ptr);
				W_Output_File.c_ptr = W_Output_File.c_ptr + strlen (User_Msg);
				if (concurrent)
				{
					Current_wk->next = (struct data_node *) calloc (1, sizeof (struct data_node));
					Prev_wk = Current_wk;
					Current_wk = Current_wk->next;
					Current_wk->data = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
					strcpy (Current_wk->data, User_Msg);
					Current_wk->next = NULL;
					Current_wk->front = Prev_wk;
					W_Output_data_c_ptr++;
				}
			}	/* end else */

			printf (" => Output a string l\n");
			if (return_flag)
			{
				Temp_Stack->end = Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->end = Output_data_c_ptr;
			}
			else
			{
				Temp_Stack->end = W_Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->end = W_Output_data_c_ptr;
			}
			Locate_Stack_Element ();

			printf (" => Output a string with Literal\n");
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}



		/* adjust template node pointer to ancestor node */
			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			if (Activity == FAIL)
			{
				sprintf (User_Msg, " FAIL<< Back to Node %s\n", Current_Node->name);
				printf (" FAIL<< Back to Node \n");
				Output_Decision ();
			}
			else if (Activity == SUCCEED)
			{
				sprintf (User_Msg, " SUCCEED<< Back to Node %s\n", Current_Node->name);
				printf (" SUCCEED<< Back to Node \n");
				Output_Decision ();
			}


			break;

		case NEXT:
			sprintf (User_Msg, "__(SM_next) Module %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

		/* free the stack */
			Temp_Stack = Current_Node->ttop_of_stack;
			Current_Stack = Current_Node->ttop_of_stack->backward_stack_ptr;
			Current_Stack->forward_stack_ptr = NULL;

		/* Adjust the template stack pointer */
			if (Current_Node->ttop_of_stack->prev_stack_element)
			/* more stack elements */
				Current_Node->ttop_of_stack = Current_Node->ttop_of_stack->prev_stack_element;
			else
				Current_Node->ttop_of_stack = NULL;

		/*
		 * Move backward to the previous position in output file
		 */
			if (return_flag)
			{
				Output_File.c_ptr = Temp_Stack->begin;
				fseek (Output_File.f_ptr, Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_output = seek_data (Current_output, Output_data_c_ptr - Temp_Stack->begin);
					Output_data_c_ptr = Temp_Stack->begin;
				}
			}
			else
			{
				W_Output_File.c_ptr = Temp_Stack->begin;
				fseek (W_Output_File.f_ptr, W_Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_wk = seek_data (Current_wk, W_Output_data_c_ptr - Temp_Stack->begin);
					W_Output_data_c_ptr = Temp_Stack->begin;
				}
			}	/* end else */
			sprintf (User_Msg, " <- Backward output buffer pointer at location %d\n",
				 Output_File.c_ptr);
			Output_Decision ();

			sprintf (User_Msg, " ** Free a stack element at Node %s; adjust stack & "
				 "output pointers.\n",
				 Current_Node->name);
			Output_Decision ();
			free (Temp_Stack);

			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			sprintf (User_Msg, " << Fail; Back to Node %s\n", Current_Node->name);
			Output_Decision ();

			client_blink_window ();
			Activity = FAIL;
			break;

		default:
			break;

	}			/* switch */
}



static void     S_Literal (void)
{
	struct data_node *Prev_output;
	struct data_node *Prev_wk;

	if (Animate_Flag)
	{
		Inverse_Node_Edge (Current_Node, FORWARD);
		Inverse_Tree_Node (Current_Node);
	}

	switch (Activity)
	{
		case FIRST:
			sprintf (User_Msg, "__(SL_first) Literal %s\n", Current_Node->name);
			Output_Decision ();

			sprintf (User_Msg, "");
			strncat (User_Msg, Current_Node->name + 1, strlen (Current_Node->name) - 2);
			User_Msg[strlen (Current_Node->name) - 2] = '\0';

			if (return_flag)
			{
				retry_fputs (User_Msg, Output_File.f_ptr);
				if (concurrent)
				{
					Current_output->next = (struct data_node *) calloc (1, sizeof (struct data_node));
					Prev_output = Current_output;
					Current_output = Current_output->next;
					Current_output->data = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
					strcpy (Current_output->data, User_Msg);
					Current_output->next = NULL;
					Current_output->front = Prev_output;
				}
			}
			else
			{
				retry_fputs (User_Msg, W_Output_File.f_ptr);
				if (concurrent)
				{
					Current_wk->next = (struct data_node *) calloc (1, sizeof (struct data_node));
					Prev_wk = Current_wk;
					Current_wk = Current_wk->next;
					Current_wk->data = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
					strcpy (Current_wk->data, User_Msg);
					Current_wk->next = NULL;
					Current_wk->front = Prev_wk;
				}
			}	/* end else */

		/* push a stack element for template node */
			Temp_Stack = Stack_Allocation ();
			if (return_flag)
			{
				Temp_Stack->begin = Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS;
			}
			else
			{
				Temp_Stack->begin = W_Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = W_Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS1;
			}

			if (return_flag)
			{
				Output_File.c_ptr += (strlen (Current_Node->name) - 2);
				Temp_Stack->end = Output_File.c_ptr;
				if (concurrent)
				{
					Output_data_c_ptr++;
					Temp_Stack->end = Output_data_c_ptr;
				}
			}
			else
			{
				W_Output_File.c_ptr += (strlen (Current_Node->name) - 2);
				Temp_Stack->end = W_Output_File.c_ptr;
				if (concurrent)
				{
					W_Output_data_c_ptr++;
					Temp_Stack->end = W_Output_data_c_ptr;
				}
			}	/* end else */
			Locate_Stack_Element ();

			sprintf (User_Msg, " => Output a string with Literal\n");
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

		/* adjust template node pointer to ancestor node */
			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			sprintf (User_Msg, " << Back to Node %s\n", Current_Node->name);
			Output_Decision ();
			Activity = SUCCEED;
			break;

		case NEXT:
			sprintf (User_Msg, "__(SL_next) Literal %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

		/* free the stack */
			Temp_Stack = Current_Node->ttop_of_stack;
			Current_Stack = Current_Node->ttop_of_stack->backward_stack_ptr;
			Current_Stack->forward_stack_ptr = NULL;

		/* Adjust the template stack pointer */
			if (Current_Node->ttop_of_stack->prev_stack_element)
			/* more stack elements */
				Current_Node->ttop_of_stack = Current_Node->ttop_of_stack->prev_stack_element;
			else
				Current_Node->ttop_of_stack = NULL;

		/*
		 * Move backward to the previous position in output file
		 */
			if (return_flag)
			{
				Output_File.c_ptr = Temp_Stack->begin;
				fseek (Output_File.f_ptr, Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_output = seek_data (Current_output, Output_data_c_ptr - Temp_Stack->begin);
					Output_data_c_ptr = Temp_Stack->begin;
				}
			}
			else
			{
				W_Output_File.c_ptr = Temp_Stack->begin;
				fseek (W_Output_File.f_ptr, W_Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_wk = seek_data (Current_wk, W_Output_data_c_ptr - Temp_Stack->begin);
					W_Output_data_c_ptr = Temp_Stack->begin;
				}
			}	/* end else */
			sprintf (User_Msg, " <- Backward output buffer pointer at location %d\n",
				 Output_File.c_ptr);
			Output_Decision ();

			sprintf (User_Msg, " ** Free a stack element at Node %s; adjust stack & "
				 "output pointers.\n",
				 Current_Node->name);
			Output_Decision ();
			free (Temp_Stack);

			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}
			sprintf (User_Msg, " << Fail; Back to Node %s\n", Current_Node->name);
			Output_Decision ();

			client_blink_window ();
			Activity = FAIL;
			break;

		default:
			break;

	}			/* switch */
}


static int      S_Module_Call (void)
{

	struct link_list *cur_para;
	short           T_Input_File_ptr;
	short           T_return_flag;
	short           T_Tree_Type;
	struct Template_Node *T_Hoare_Root_Dummy;
	struct Template_Node *W_Hoare_Root_Dummy;
	struct Stack_Node *T_Root_Stack;
	struct Stack_Node *T_Current_Stack;
	struct Stack_Node *T_Temp_Stack;
	struct Template_Node *T_Current_Node;
	char           *T_Input_Buffer;

	switch (Activity)
	{
		case FIRST:
			T_Input_File_ptr = Input_File.c_ptr;
			T_return_flag = return_flag;
			T_Tree_Type = Tree_Type;
			T_Hoare_Root_Dummy = Hoare_Root_Dummy;
			T_Root_Stack = Root_Stack;
			T_Current_Stack = Current_Stack;
			T_Temp_Stack = Temp_Stack;
			T_Current_Node = Current_Node;
			T_Input_Buffer = (char *) calloc (strlen (Input_File.buffer) + 1, sizeof (char));

			strcpy (T_Input_Buffer, Input_File.buffer);
			printf ("BEFORE in file %s\n", T_Input_Buffer);

			sprintf (User_Msg, "__(SM_first) module %s\n", Current_Node->name);
			Output_Decision ();

			printf ("BEFORE in file %s\n", T_Input_Buffer);
			if (!recursion)

			/*
			 * Get_Parameters();
			 */
				printf ("BEFORE in file %s\n", T_Input_Buffer);
			if ((W_Hoare_Root_Dummy = Search_Module_Root (Current_Node)) == NULL)
			{

				return (0);
			}

		/* Animate the node edge left to the node; from top to bottom */
		/* Whiten the node chars; blacken background */
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

		/*
		 * S_Output_File  for storing the results of parameters'
		 * matching
		 */
			S_Output_File.c_ptr = 0;
			S_Output_File.f_ptr = retry_fopen (S_Output_File.name, "w");
			setbuf (S_Output_File.f_ptr, NULL);	/* Do not buffer I/O */
		/* add   April  1992    */
			cur_para = Current_Node->para;	/* Linked list of parameters of Current_Node->name */
			while (cur_para)
			{
				printf ("check parameteres \n");
				Activity = FIRST;
				S_Direct_Product1 (cur_para);
				if (Activity == SUCCEED)
				{
					cur_para = cur_para->next;
				}
				else
					break;
			}

		/*
		 * Add   carriage return  to the output file of parameters.
		 * Without it, analysis can not reach the end of file,
		 * analysis will fail
		 */
			add_carriage_return (S_Output_File.f_ptr);
			fclose (S_Output_File.f_ptr);

			S_Output_File.f_ptr = retry_fopen (S_Output_File.name, "r");
			setbuf (S_Output_File.f_ptr, NULL);	/* Do not buffer I/O */
			strcpy (DESC_Line_Str, "");
			strcpy (Input_File.buffer, "");
			printf ("before in file %s-%d\n", Input_File.buffer, strlen (Input_File.buffer));
			while (retry_fgets (DESC_Line_Str, MAX_LINE_SIZE, S_Output_File.f_ptr) != NULL)
			{
				strcat (Input_File.buffer, DESC_Line_Str);
			}

			fclose (S_Output_File.f_ptr);
			printf ("after in file -%s %d\n", Input_File.buffer, strlen (Input_File.buffer));

		/* put data of parameters to file buffer      */
		/* add  April    1992   */
			printf (" before go to exec \n");
			if (strlen (Input_File.buffer) > 1)
			{
				Stack_Save ();
				printf (" IN EXECUTION !!!! \n");
				Input_File.c_ptr = 0;
			/* Hoare_Root_Dummy=Search_Module_Root(Current_Node);  */
				printf (" NAME*** %s %s\n", Hoare_Root_Dummy->level_point->module_name,
					W_Hoare_Root_Dummy->level_point->module_name);
				if (strcmp (Hoare_Root_Dummy->level_point->module_name,
					    W_Hoare_Root_Dummy->level_point->module_name) == 0)
				{
					recursion = YES;
				}

				Hoare_Root_Dummy = W_Hoare_Root_Dummy;
				printf (" IN EXECUTION run 2 !!!! \n");
				exec_run2 ();

				Root_Stack = T_Root_Stack;
				Stack_Restore ();
			}
			printf (" after  go to exec \n");
			Input_File.c_ptr = T_Input_File_ptr;
			return_flag = T_return_flag;
			Tree_Type = T_Tree_Type;
			Hoare_Root_Dummy = T_Hoare_Root_Dummy;
			Current_Stack = T_Current_Stack;
			Temp_Stack = T_Temp_Stack;
			Current_Node = T_Current_Node;

			strcpy (Input_File.buffer, T_Input_Buffer);
			free (T_Input_Buffer);
			printf ("OLD  in file -%s", Input_File.buffer);

			if (Activity == SUCCEED)
			{
				Locate_Stack_Element ();
				Output_Decision ();

				if (return_flag)
				{
					Temp_Stack->end = Output_File.c_ptr;
					if (concurrent)
						Temp_Stack->end = Output_data_c_ptr;
				}
				else
				{
					Temp_Stack->end = W_Output_File.c_ptr;
					if (concurrent)
						Temp_Stack->end = W_Output_data_c_ptr;
				}
			}

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			/* Inverse_Node_Edge(Current_Node, BACKWARD); */
			}

			if (Activity == SUCCEED)
			{
				sprintf (User_Msg, " SUCCEED11<< Back to Node %s\n", Current_Node->name);
				printf (" SUCCEED<< Back to Node \n");
				Output_Decision ();
				Activity = SUCCEED;

			}
			else
			{
				sprintf (User_Msg, " FAIL<< Back to Node %s\n", Current_Node->name);
				printf (" FAIL<< Back to Node \n");
				Output_Decision ();
				Activity = FAIL;
			}
			break;

		case NEXT:
			sprintf (User_Msg, "__(SM_next) Module %s\n", Current_Node->name);
			Output_Decision ();
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

		/* free the stack */
			Temp_Stack = Current_Node->ttop_of_stack;
			Current_Stack = Current_Node->ttop_of_stack->backward_stack_ptr;
			Current_Stack->forward_stack_ptr = NULL;

		/* Adjust the template stack pointer */
			if (Current_Node->ttop_of_stack->prev_stack_element)
			/* more stack elements */
				Current_Node->ttop_of_stack = Current_Node->ttop_of_stack->prev_stack_element;
			else
				Current_Node->ttop_of_stack = NULL;

		/*
		 * Move backward to the previous position in output file
		 */
			if (return_flag)
			{
				Output_File.c_ptr = Temp_Stack->begin;
				fseek (Output_File.f_ptr, Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_output = seek_data (Current_output, Output_data_c_ptr - Temp_Stack->begin);
					Output_data_c_ptr = Temp_Stack->begin;
				}
			}
			else
			{
				W_Output_File.c_ptr = Temp_Stack->begin;
				fseek (W_Output_File.f_ptr, W_Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_wk = seek_data (Current_wk, W_Output_data_c_ptr - Temp_Stack->begin);
					W_Output_data_c_ptr = Temp_Stack->begin;
				}
			}	/* end else */
			sprintf (User_Msg, " <- Backward output buffer pointer at location %d\n",
				 Output_File.c_ptr);
			Output_Decision ();

			sprintf (User_Msg, " ** Free a stack element at Node %s; adjust stack & "
				 "output pointers.\n",
				 Current_Node->name);
			Output_Decision ();
			free (Temp_Stack);

			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}


			sprintf (User_Msg, " << Fail; Back to Node %s\n", Current_Node->name);
			Output_Decision ();

			client_blink_window ();
			Activity = FAIL;
			break;

		default:
			break;

	}			/* switch */
	return (1);
}


/* NOTE: There also exists S_Find_Corr_Match1(), and S_Find_Corr_Match2() */
static int      S_Find_Corr_Match (void)
{
	short           i;
	struct Stack_Node *TOS,
	               *t1;
	struct data_node *Prev_output;
	struct data_node *Prev_wk;

/* ---  convert the reference node into the match node  --- */
	sprintf (User_Msg, "");
	strncat (User_Msg, Current_Node->name, strlen (Current_Node->name));
	User_Msg[strlen (Current_Node->name)] = '\0';
	for (i = 0; User_Msg[i]; i++)
		if (isupper (User_Msg[i]))
			User_Msg[i] = tolower (User_Msg[i]);

/* ****************************************  */
/* search for the corr. sequence match node  */
/* ****************************************  */
	Prev_Stack = Root_Stack->forward_stack_ptr;

	for (;;)
	{
		while ((strncmp (Prev_Stack->template_node_ptr->name, User_Msg,
				 strlen (User_Msg)) ||
	/* Make sure the next character of the node name except *,+,(     */
	/* add   April   1992   */
			(isalpha (*(Prev_Stack->template_node_ptr->name + strlen (User_Msg))))
			) && Prev_Stack->forward_stack_ptr)
		{
			Prev_Stack = Prev_Stack->forward_stack_ptr;
			printf ("initial search ->%s\n", Prev_Stack->template_node_ptr->name);
		}
	/* nothing found */
		if (!Prev_Stack->forward_stack_ptr)
			return (0);
	/* found the exactly same node name */
		if (Prev_Stack->template_node_ptr->ttop_of_stack == Prev_Stack)
		{
			break;
		}
		else
		{
			Prev_Stack = Prev_Stack->forward_stack_ptr;
			printf ("**There are some previous stack\n");
		}
	}			/* for */

	sprintf (User_Msg, "match node->%s %s\n", Prev_Stack->template_node_ptr->name, Current_Node->name);
	Output_Decision ();
/* process needs to start from the bottom of the stack; searching BOS  */
	TOS = Prev_Stack;
	while (Prev_Stack->prev_stack_element)
	{
		Prev_Stack = Prev_Stack->prev_stack_element;
	}

	for (;;)
	{

		sprintf (User_Msg, "match node->%s->\n", Prev_Stack->template_node_ptr->name);
		Output_Decision ();
		sprintf (User_Msg, "");

		if (Prev_Stack->from_tree_type == ANALYSIS)
		{		/* 1 if */
			printf ("match in analysis tree \n");
			strncat (User_Msg, Input_File.buffer + Prev_Stack->begin,
				 Prev_Stack->end - Prev_Stack->begin);
		}
		else
		{		/* 1 else */
			printf ("match in synthesis tree \n");
			if (Prev_Stack->from_tree_type == SYNTHESIS1)
			{	/* 2 if */
				if (!concurrent)
				{	/* 3 if */
					fseek (W_Output_File.f_ptr, Prev_Stack->begin, SEEK_SET);
					retry_fgets (User_Msg, Prev_Stack->end - Prev_Stack->begin + 1, W_Output_File.f_ptr);
					fseek (W_Output_File.f_ptr, 0, SEEK_END);
				}
				else
				{	/* 3 else */
					find_data (Wk_data, Prev_Stack->begin, Prev_Stack->end - Prev_Stack->begin + 1);
				}	/* end 3 else */
			}
			else
			{	/* 2 else */
				if (!concurrent)
				{	/* 4 if */
					fseek (Output_File.f_ptr, Prev_Stack->begin, SEEK_SET);
					retry_fgets (User_Msg, Prev_Stack->end - Prev_Stack->begin + 1, Output_File.f_ptr);
					fseek (Output_File.f_ptr, 0, SEEK_END);
				}
				else
				{	/* 4 else */
					find_data (Output_data, Prev_Stack->begin, Prev_Stack->end - Prev_Stack->begin + 1);
				}	/* end 4 else  */
			}	/* end 2 else */
		}		/* end 1 else */

		Output_Decision ();
		printf ("match with match value %s \n", User_Msg);
		if (return_flag == 1)
		{
			retry_fputs (User_Msg, Output_File.f_ptr);
			Output_File.c_ptr = Output_File.c_ptr + Prev_Stack->end - Prev_Stack->begin;
			if (concurrent)
			{
				Current_output->next = (struct data_node *) calloc (1, sizeof (struct data_node));
				Prev_output = Current_output;
				Current_output = Current_output->next;
				Current_output->data = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
				strcpy (Current_output->data, User_Msg);
				Current_output->next = NULL;
				Current_output->front = Prev_output;
				Output_data_c_ptr = Output_data_c_ptr + 1;
			}
		}
		else
		{
			retry_fputs (User_Msg, W_Output_File.f_ptr);
			W_Output_File.c_ptr = W_Output_File.c_ptr + Prev_Stack->end - Prev_Stack->begin;
			if (concurrent)
			{
				Current_wk->next = (struct data_node *) calloc (1, sizeof (struct data_node));
				Prev_wk = Current_wk;
				Current_wk = Current_wk->next;
				Current_wk->data = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
				strcpy (Current_wk->data, User_Msg);
				Current_wk->next = NULL;
				Current_wk->front = Prev_wk;
				W_Output_data_c_ptr = W_Output_data_c_ptr + 1;
			}
		}		/* end else */

		printf ("matched data-> %s\n", User_Msg);
		sprintf (User_Msg, "Input_File %d %d\n", Prev_Stack->begin, Prev_Stack->end);
		Output_Decision ();
	/* does reach the top of the stack */
		if (Prev_Stack == TOS)
			break;
		else
		{

			for (t1 = TOS; t1->prev_stack_element != Prev_Stack;)
			{
				t1 = t1->prev_stack_element;
			}

		/* move one stack element upward */
			Prev_Stack = t1;
		}		/* end else  */
	}			/* end for  */
	return (1);
}


/* NOTE: There also exists S_Find_Corr_Match1(), and S_Find_Corr_Match() */
static int      S_Find_Corr_Match2 (void)
{
	short           i;

	printf ("s find corr match \n");
/* ---  convert the reference node into the match node  --- */
	sprintf (User_Msg, "");
	strncat (User_Msg, Current_Node->name, strlen (Current_Node->name));
	User_Msg[strlen (Current_Node->name)] = '\0';
	for (i = 0; User_Msg[i]; i++)
		if (isupper (User_Msg[i]))
			User_Msg[i] = tolower (User_Msg[i]);

/* ****************************************  */
/* search for the corr. sequence match node  */
/* ****************************************  */
	Prev_Stack = Root_Stack->forward_stack_ptr;

	for (;;)
	{
		while ((strncmp (Prev_Stack->template_node_ptr->name, User_Msg,
				 strlen (User_Msg)) ||
	/* Make sure the next character of the node name except *,+,(     */
	/* add   April   1992   */
			(isalpha (*(Prev_Stack->template_node_ptr->name + strlen (User_Msg))))
			) && Prev_Stack->forward_stack_ptr)
		{

		/*
		 * printf("initial search ->%c\n",
		 * Prev_Stack->template_node_ptr->name+strlen(User_Msg));
		 */
			printf ("initial search ->%s\n", Prev_Stack->template_node_ptr->name);
			Prev_Stack = Prev_Stack->forward_stack_ptr;
		}
	/* nothing found */
		if (!Prev_Stack->forward_stack_ptr)
			return (0);
	/* found the exactly same node name */
		if (Prev_Stack->template_node_ptr->ttop_of_stack == Prev_Stack)
		{
			break;
		}
		else
		{
			Prev_Stack = Prev_Stack->forward_stack_ptr;
			printf ("----There are some previous stack\n");
		}
	}			/* for */

	printf ("match node->%s %s\n", Prev_Stack->template_node_ptr->name, Current_Node->name);
	sprintf (User_Msg, "match node->%s %s\n", Prev_Stack->template_node_ptr->name, Current_Node->name);
	Output_Decision ();
/* process needs to start from the bottom of the stack; searching BOS  */
	while (Prev_Stack->prev_stack_element)
	{
		Prev_Stack = Prev_Stack->prev_stack_element;
	}
	no_of_elements = Prev_Stack->no_of_elements;
	printf ("elements %d\n", no_of_elements);
	return (1);
}				       /* end S_Find_Corr_Match2() */


/* ....................................................  */

/*
 * NOTE: There exists a function with ALMOST the same name earlier on in this
 * file, namely, S_Direct_Product1 ()
 */
static void     S_Direct_Product (void)
{
	struct Stack_Node *S_Temp_Stack;


/* ---  terminal reference node treated as literal  ---  */

	if ((Current_Node->type & REFERENCE_NODE) &&
			!Current_Node->level_point)
	{
		sprintf (User_Msg, "(SDP)_Node %s\n", Current_Node->name);
		Output_Decision ();

		if (Animate_Flag)
		{
			Inverse_Node_Edge (Current_Node, FORWARD);
			Inverse_Tree_Node (Current_Node);
		}

		switch (Activity)
		{

			case FIRST:
				sprintf (User_Msg, "__(SDP_first)Node %s\n", Current_Node->name);
				Output_Decision ();

				Temp_Stack = Stack_Allocation ();
			/* set up the starting point of synthesis */
				if (return_flag)
				{
					Temp_Stack->begin = Output_File.c_ptr;
					if (concurrent)
						Temp_Stack->begin = Output_data_c_ptr;
					Temp_Stack->from_tree_type = SYNTHESIS;
				}
				else
				{
					Temp_Stack->begin = W_Output_File.c_ptr;
					if (concurrent)
						Temp_Stack->begin = W_Output_data_c_ptr;
					Temp_Stack->from_tree_type = SYNTHESIS1;
				}
				S_Temp_Stack = Temp_Stack;
				if (S_Check_Module ())
				{
					Locate_Stack_Element ();

					sprintf (User_Msg, " => Successfully matched at module call\n");
					Output_Decision ();

				/* set up the ending point of synthesis */
					if (return_flag)
					{
						Temp_Stack->end = Output_File.c_ptr;
						if (concurrent)
							Temp_Stack->end = Output_data_c_ptr;
					}
					else
					{
						Temp_Stack->end = W_Output_File.c_ptr;
						if (concurrent)
							Temp_Stack->end = W_Output_data_c_ptr;
					}
					clientXBell ();
					Activity = SUCCEED;
				}
				else
				{

					switch (S_Find_Corr_Match ())
					{

						case 0:	/* no corr. match node */
							if (!S_Module_Call ())
								Activity = FAIL;

							if (Activity != SUCCEED)
							{

								sprintf (User_Msg, " => It is non-defined reference node\n");
								printf (" => It is non-defined reference node\n");
								Output_Decision ();
								Temp_Stack = S_Temp_Stack;
								client_blink_window ();
								Activity = FAIL;
								printf (" => It is non-defined reference node %s\n",
									Current_Node->name);
							}
							else
							{
								printf ("sub module suceed\n");
							}
							break;

						case 1:	/* a corr. match node */
							Locate_Stack_Element ();

							sprintf (User_Msg, " => Found a corresponding match node\n");
							Output_Decision ();

						/*
						 * set up the ending point of
						 * synthesis
						 */
							if (return_flag)
							{
								Temp_Stack->end = Output_File.c_ptr;
								if (concurrent)
									Temp_Stack->end = Output_data_c_ptr;
							}
							else
							{
								Temp_Stack->end = W_Output_File.c_ptr;
								if (concurrent)
									Temp_Stack->end = W_Output_data_c_ptr;
							}

							clientXBell ();
							Activity = SUCCEED;
							break;

						default:
							break;
					}	/* switch */
				}	/* else */


				if (Animate_Flag)
				{
					Inverse_Tree_Node (Current_Node);
					Inverse_Node_Edge (Current_Node, BACKWARD);
				}

			/* adjust template node pointers  */
				Prev_Node = Current_Node;
				Current_Node = Current_Node->ancestor;
				if (Animate_Flag)
				{
					Inverse_Tree_Node (Current_Node);
				}

			/* BACK TO ANCESTOR & INVERSE THE NODE WITH NODE EDGE */
				sprintf (User_Msg, " << Back to Node %s\n", Current_Node->name);
				Output_Decision ();
				printf (" << Back to Node %s\n", Current_Node->name);
				return;

			case NEXT:
				sprintf (User_Msg, "__(SDP_next)Node %s\n", Current_Node->name);
				Output_Decision ();

				if (Animate_Flag)
				{
					Inverse_Tree_Node (Current_Node);
					Inverse_Node_Edge (Current_Node, BACKWARD);
				}

				Temp_Stack = Current_Node->ttop_of_stack;
				Current_Stack = Current_Node->ttop_of_stack->backward_stack_ptr;
				Current_Stack->forward_stack_ptr = NULL;

			/* Adjust the template stack pointer */
				if (Current_Node->ttop_of_stack->prev_stack_element)
				/* more stack elements */
					Current_Node->ttop_of_stack = Current_Node->ttop_of_stack->prev_stack_element;
				else
					Current_Node->ttop_of_stack = NULL;

			/*
			 * Move backward to the previous position in
			 */
				if (return_flag)
				{
					Output_File.c_ptr = Temp_Stack->begin;
					fseek (Output_File.f_ptr, Output_File.c_ptr, SEEK_SET);
					if (concurrent)
					{
						Current_output = seek_data (Current_output, Output_data_c_ptr - Temp_Stack->begin);
						Output_data_c_ptr = Temp_Stack->begin;
					}
				}
				else
				{
					W_Output_File.c_ptr = Temp_Stack->begin;
					fseek (W_Output_File.f_ptr, W_Output_File.c_ptr, SEEK_SET);
					if (concurrent)
					{
						Current_wk = seek_data (Current_wk, W_Output_data_c_ptr - Temp_Stack->begin);
						W_Output_data_c_ptr = Temp_Stack->begin;
					}
				}	/* end else */
				sprintf (User_Msg, " <- Backward output buffer pointer at location %d\n",
					 Output_File.c_ptr);
				Output_Decision ();

				sprintf (User_Msg, " ** Free a stack element at Node %s; adjust stack & "
					 "output pointers.\n",
					 Current_Node->name);
				Output_Decision ();
			/* free the stack */
				free (Temp_Stack);

				Prev_Node = Current_Node;
				Current_Node = Current_Node->ancestor;

				if (Animate_Flag)
				{
					Inverse_Tree_Node (Current_Node);
				}

				sprintf (User_Msg, " << Fail; Back to Node %s\n", Current_Node->name);
				Output_Decision ();

				client_blink_window ();
				Activity = FAIL;
				return;

			default:
				break;

		}		/* switch */

	}			/* if */

/* ....................................................  */
/* other match nodes & intermediate reference nodes    */
/* ....................................................  */

	switch (Activity)
	{
		case FIRST:
			sprintf (User_Msg, "__(sDP_first) Direct Product %s\n", Current_Node->name);
			Output_Decision ();
			printf ("__(sDP_first) Direct Product %s\n", Current_Node->name);

			if (Current_Node->type & REFERENCE_NODE)
				if (!S_Find_Corr_Match2 ())
				{
					Activity = FAIL;
					Prev_Node = Current_Node;
					Current_Node = Current_Node->ancestor;
					printf ("Activity=FAIL\n");
					break;
				}


			if (Animate_Flag)
			{
				Inverse_Node_Edge (Current_Node, FORWARD);
				Inverse_Tree_Node (Current_Node);
			}

			Temp_Stack = Stack_Allocation ();
		/* set up the starting point of synthesis */
			if (return_flag)
			{
				Temp_Stack->begin = Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS;
			}
			else
			{
				Temp_Stack->begin = W_Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = W_Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS1;
			}

			Locate_Stack_Element ();
			printf ("sDP -%d %d \n", Temp_Stack->from_tree_type, SYNTHESIS);
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

		/* point to the first immediate sibling */
			Current_Node = Current_Node->level_point;
			sprintf (User_Msg, " >> Go to Node %s\n", Current_Node->name);
			Output_Decision ();
			break;

		case NEXT:
			sprintf (User_Msg, "__(sDP_next) Direct Product %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Node_Edge (Current_Node, FORWARD);
				Inverse_Tree_Node (Current_Node);
			}

		/*
		 * Get the last processed template node which is the last
		 * sibling; but Discriminated Union is different from this
		 */

		/*
		 * Method 1: indirectly get the last processed template node
		 * Temp_Node = Current_Node->level_point; while (
		 * Temp_Node->front )  { Temp_Node = Temp_Node->front; }
		 */
		/* Method 2: directly get the last processed template node */
			Temp_Node = Current_Node->ttop_of_stack->tcp_save->template_node_ptr;

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			sprintf (User_Msg, " >> Go to the last sibling %s under node %s\n",
				 Temp_Node->name, Current_Node->name);
			Output_Decision ();
			Current_Node = Temp_Node;
			break;

		case SUCCEED:
			sprintf (User_Msg, "__(sDP_succeed) Direct Product %s\n", Current_Node->name);
			Output_Decision ();
			printf ("__(sDP_succeed) Direct Product %s\n", Current_Node->name);
		/* set up the ending point of synthesis */
			if (return_flag)
			{
				Current_Node->ttop_of_stack->end = Output_File.c_ptr;
				if (concurrent)
					Current_Node->ttop_of_stack->end = Output_data_c_ptr;
			}
			else
			{
				Current_Node->ttop_of_stack->end = W_Output_File.c_ptr;
				if (concurrent)
					Current_Node->ttop_of_stack->end = W_Output_data_c_ptr;
			}	/* end else */

		/*
		 * store the pointer which points to the last processed
		 * template node
		 */
			Current_Node->ttop_of_stack->tcp_save = Prev_Node->ttop_of_stack;

			printf ("sDP w output file ptr %d\n", W_Output_File.c_ptr);
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			if (Prev_Node->front)
			{	/* more subnodes to process */
			/* point to the next immediate sibling */
				Current_Node = Prev_Node->front;
				Activity = FIRST;

				sprintf (User_Msg, " >> Succeed; Go to Node %s\n", Current_Node->name);
				Output_Decision ();

			}	/* if */
			else
			{	/* back to a ancestor node */
				if (Animate_Flag)
				{
					Inverse_Node_Edge (Current_Node, BACKWARD);
				}

				Prev_Node = Current_Node;
				Current_Node = Current_Node->ancestor;

				sprintf (User_Msg, " << Succeed; Back to Node %s\n", Current_Node->name);
				Output_Decision ();

				if (Animate_Flag)
				{
					Inverse_Tree_Node (Current_Node);
				}

			}	/* else */
			printf ("end w output file ptr %d\n", W_Output_File.c_ptr);
			break;

		case FAIL:
			sprintf (User_Msg, "__(sDP_fail) Direct Product %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

		/* if the node is NOT the first immediate son  */
			if (Prev_Node != Prev_Node->ancestor->level_point)
			{

				Current_Node = Prev_Node->back;	/* !!!  */
				Activity = NEXT;

				sprintf (User_Msg, " ?? Try to check node %s\n", Current_Node->name);
				Output_Decision ();

			}	/* if */
			else
			{

				sprintf (User_Msg, " // All subnodes are tried; all of them failed\n");
				Output_Decision ();

				if (Animate_Flag)
				{
					Inverse_Node_Edge (Current_Node, BACKWARD);
				}

			/* free the stack */
				Temp_Stack = Current_Node->ttop_of_stack;
				Current_Stack = Current_Node->ttop_of_stack->backward_stack_ptr;
				Current_Stack->forward_stack_ptr = NULL;

			/* Adjust the template stack pointer */
				if (Current_Node->ttop_of_stack->prev_stack_element)
				/* more stack elements */
					Current_Node->ttop_of_stack = Current_Node->ttop_of_stack->prev_stack_element;
				else
					Current_Node->ttop_of_stack = NULL;

			/*
			 * Move backward to the previous position in
			 */
				if (return_flag)
				{
					Output_File.c_ptr = Temp_Stack->begin;
					fseek (Output_File.f_ptr, Output_File.c_ptr, SEEK_SET);
					if (concurrent)
					{
						Current_output = seek_data (Current_output, Output_data_c_ptr - Temp_Stack->begin);
						Output_data_c_ptr = Temp_Stack->begin;
					}
				}
				else
				{
					W_Output_File.c_ptr = Temp_Stack->begin;
					fseek (W_Output_File.f_ptr, W_Output_File.c_ptr, SEEK_SET);
					if (concurrent)
					{
						Current_wk = seek_data (Current_wk, W_Output_data_c_ptr - Temp_Stack->begin);
						W_Output_data_c_ptr = Temp_Stack->begin;
					}
				}	/* end else */
				sprintf (User_Msg, " <- Backward output buffer pointer at location %d\n",
					 Output_File.c_ptr);
				Output_Decision ();

				sprintf (User_Msg, " ** Free a stack element at Node %s; adjust stack & "
					 "output pointers.\n",
					 Current_Node->name);
				Output_Decision ();
				free (Temp_Stack);

				Prev_Node = Current_Node;
				Current_Node = Current_Node->ancestor;

				sprintf (User_Msg, " << Back to Node %s\n", Current_Node->name);
				Output_Decision ();

				if (Animate_Flag)
				{
					Inverse_Tree_Node (Current_Node);
				}

			}	/* else */
			break;

		default:
			break;

	}			/* switch */
}




static void     S_Discriminated_Union (void)
{

	switch (Activity)
	{
			case FIRST:
			sprintf (User_Msg, "__(SDU_first) Discriminated Union %s\n",
				 Current_Node->name);
			printf ("__(SDU_first) Discriminated Union %s\n", Current_Node->name);
			Output_Decision ();

		/*
		 * no match with corresponding matched node, go back to
		 * ancestor
		 */
			if (isupper (*Current_Node->name))
				if (!S_Find_Corr_Match2 ())
				{
					Activity = FAIL;
					Prev_Node = Current_Node;
					Current_Node = Current_Node->ancestor;
					break;
				}

			if (Animate_Flag)
			{
				Inverse_Node_Edge (Current_Node, FORWARD);
				Inverse_Tree_Node (Current_Node);
				Inverse_Tree_Node (Current_Node);
			}

			Temp_Stack = Stack_Allocation ();
			if (return_flag)
			{
				Temp_Stack->begin = Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS;
			}
			else
			{
				Temp_Stack->begin = W_Output_File.c_ptr;
				if (concurrent)
					Temp_Stack->begin = W_Output_data_c_ptr;
				Temp_Stack->from_tree_type = SYNTHESIS1;
			}
			Locate_Stack_Element ();

		/* point to the first immediate sibling */
			Current_Node = Current_Node->level_point;

			sprintf (User_Msg, " >> Go to Node %s\n", Current_Node->name);
			Output_Decision ();
			break;

		case NEXT:
			sprintf (User_Msg, "__(SDU_next) Discriminated Union %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Node_Edge (Current_Node, FORWARD);
				Inverse_Tree_Node (Current_Node);
				Inverse_Tree_Node (Current_Node);
			}

		/* get the last processed template node */
			Temp_Node = Current_Node->ttop_of_stack->tcp_save->template_node_ptr;

			sprintf (User_Msg, " >> Go to the last sibling %s under node %s\n",
				 Temp_Node->name, Current_Node->name);
			Output_Decision ();
			Current_Node = Temp_Node;
			break;

		case SUCCEED:
			sprintf (User_Msg, "__(SDU_succeed) Discriminated Union %s\n", Current_Node->name);
			Output_Decision ();
		/* set up the ending point of the synthesis */
			if (return_flag)
			{
				Current_Node->ttop_of_stack->end = Output_File.c_ptr;
				if (concurrent)
					Current_Node->ttop_of_stack->end = Output_data_c_ptr;
			}
			else
			{
				Current_Node->ttop_of_stack->end = W_Output_File.c_ptr;
				if (concurrent)
					Current_Node->ttop_of_stack->end = W_Output_data_c_ptr;
			}

		/*
		 * store the pointer which points to the last processed
		 * template node
		 */
			Current_Node->ttop_of_stack->tcp_save = Prev_Node->ttop_of_stack;

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

		/* back to a ancestor node */
			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;

			sprintf (User_Msg, " << Succeed; Back to Node %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}
			break;

		case FAIL:
			sprintf (User_Msg, "__(SDU_fail) Discriminated Union %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			if (Prev_Node->front)
			{	/* need to try to check another sibling subnode */
			/* point to the next immediate sibling */
				Current_Node = Prev_Node->front;
				Activity = FIRST;

				sprintf (User_Msg, " ?? Try to check node %s\n", Current_Node->name);
				Output_Decision ();
			}	/* if */
			else
			{

				sprintf (User_Msg, " // All subnodes are tried; none of them found\n");
				Output_Decision ();

				if (Animate_Flag)
				{
					Inverse_Node_Edge (Current_Node, BACKWARD);
				}

			/* free the stack */
				Temp_Stack = Current_Node->ttop_of_stack;
				Current_Stack = Current_Node->ttop_of_stack->backward_stack_ptr;
				Current_Stack->forward_stack_ptr = NULL;

			/* Adjust the template stack pointer */
				if (Current_Node->ttop_of_stack->prev_stack_element)
				/* more stack elements */
					Current_Node->ttop_of_stack = Current_Node->ttop_of_stack->prev_stack_element;
				else
					Current_Node->ttop_of_stack = NULL;

			/*
			 * Move backward to the previous position in output
			 * file.
			 */
				if (return_flag)
				{
					Output_File.c_ptr = Temp_Stack->begin;
					fseek (Output_File.f_ptr, Output_File.c_ptr, SEEK_SET);
					if (concurrent)
					{
						Current_output = seek_data (Current_output, Output_data_c_ptr - Temp_Stack->begin);
						Output_data_c_ptr = Temp_Stack->begin;
					}
				}
				else
				{
					W_Output_File.c_ptr = Temp_Stack->begin;
					fseek (W_Output_File.f_ptr, W_Output_File.c_ptr, SEEK_SET);
					if (concurrent)
					{
						Current_wk = seek_data (Current_wk, W_Output_data_c_ptr - Temp_Stack->begin);
						W_Output_data_c_ptr = Temp_Stack->begin;
					}
				}	/* end else */
				sprintf (User_Msg, " <- Backward output buffer pointer at location %d\n",
					 Output_File.c_ptr);
				Output_Decision ();

				sprintf (User_Msg, " ** Free a stack element at Node %s; adjust stack & "
					 "output pointers.\n",
					 Current_Node->name);
				Output_Decision ();
				free (Temp_Stack);

				Prev_Node = Current_Node;
				Current_Node = Current_Node->ancestor;

				if (Animate_Flag)
				{
					Inverse_Tree_Node (Current_Node);
				}

				sprintf (User_Msg, " << Back to Node %s\n", Current_Node->name);
				Output_Decision ();

			}	/* else */
			break;

		default:
			break;

	}			/* switch */
}



/* range (digit..digit)            */
static void     S_Successful_Element (void)
{

	if (Current_Node->ttop_of_stack->no_of_elements < Current_Node->lower)
	{
	/* point to the first immediate sibling */
		Current_Node->ttop_of_stack->no_of_elements++;
		Current_Node = Current_Node->level_point;
		Activity = FIRST;

		sprintf (User_Msg, " >>(Suc_1) Go to node %s\n", Current_Node->name);
		printf (" >>(Suc_1) Go to node %s\n", Current_Node->name);
		Output_Decision ();

	/*
	 * need some more work to check Dummy Node (future work)
	 * A_Sequence_Dummy();
	 */
	}
	else if (Current_Node->ttop_of_stack->no_of_elements == Current_Node->lower)
	{
		if (Animate_Flag)
		{
			Inverse_Node_Edge (Current_Node, BACKWARD);
		}
		Current_Node->ttop_of_stack->tcp_save = NULL;	/* !!!  temporary */

	/* set up the ending point of the matching */
		if (return_flag)
		{
			Current_Node->ttop_of_stack->end = Output_File.c_ptr;
			if (concurrent)
				Current_Node->ttop_of_stack->end = Output_data_c_ptr;
		}
		else
		{
			Current_Node->ttop_of_stack->end = Output_File.c_ptr;
			if (concurrent)
				Current_Node->ttop_of_stack->end = W_Output_data_c_ptr;
		}
		sprintf (User_Msg, "A sequecne pointer%d %d\n", Current_Node->ttop_of_stack->end, Input_File.c_ptr);
		Output_Decision ();
		sprintf (User_Msg, "Input_File %d %d\n", Current_Node->ttop_of_stack->begin, Current_Node->ttop_of_stack->end);
		Output_Decision ();
		printf ("begin \n");
		if ((Current_Node->ttop_of_stack->no_of_elements == 0) && (no_of_elements != 0))
		{
			printf ("contine \n");
			Activity = FIRST;
			Current_Node->ttop_of_stack->no_of_elements++;
			Current_Node = Current_Node->level_point;
		}
		else
		{
		/* back to ancestor node */
			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;
			Activity = SUCCEED;
		}

		if (Animate_Flag)
		{
			Inverse_Tree_Node (Current_Node);
		}

		printf (" <<(Suc_2) Succeed; Back to node %s\n", Current_Node->name);
		sprintf (User_Msg, " <<(Suc_2) Succeed; Back to node %s\n", Current_Node->name);
		Output_Decision ();
	}
	else if ((Current_Node->ttop_of_stack->no_of_elements > Current_Node->lower)
			&& (Current_Node->ttop_of_stack->end == Output_File.c_ptr))
	{
		Current_Node = Current_Node->level_point;

		sprintf (User_Msg, " >>(Suc_3) Go to node %s\n", Current_Node->name);
		printf (" >>(Suc_3) Go to node %s\n", Current_Node->name);
		Output_Decision ();
		Activity = NEXT;
	}
	else if ((Current_Node->ttop_of_stack->no_of_elements > Current_Node->lower)
			&&
			(Current_Node->ttop_of_stack->end < Output_File.c_ptr))
	{
	/* set up the ending point of the matching */
		Current_Node->ttop_of_stack->end = Output_File.c_ptr;
		sprintf (User_Msg, "A sequecne pointer%d %d\n", Current_Node->ttop_of_stack->end, Output_File.c_ptr);
		Output_Decision ();

		sprintf (User_Msg, "Input_File %d %d\n", Current_Node->ttop_of_stack->begin, Current_Node->ttop_of_stack->end);
		Output_Decision ();
		Output_Decision ();

	/* store the pointer which points to the last processed template node */
		Current_Node->ttop_of_stack->tcp_save = Prev_Node->ttop_of_stack;

		if (Animate_Flag)
		{
			Inverse_Node_Edge (Current_Node, BACKWARD);
		}

		Prev_Node = Current_Node;
		Current_Node = Current_Node->ancestor;

		if (Animate_Flag)
		{
			Inverse_Tree_Node (Current_Node);
		}

		sprintf (User_Msg, " <<(Suc_4) Succeed; Back to node %s\n",
			 Current_Node->name);
		printf (" <<(Suc_4) Succeed; Back to node %s\n",
			Current_Node->name);
		Output_Decision ();
		Activity = SUCCEED;
	}
	else
	{
	/* no_of_element > lower && attempted match string > buffer string */
		Current_Node = Current_Node->level_point;

		sprintf (User_Msg, " >>(Suc_5) Go to node %s\n", Current_Node->name);
		printf (" >>(Suc_5) Go to node %s\n", Current_Node->name);
		Output_Decision ();
		Activity = NEXT;
	}			/* else */
}



static void     S_Failed_Element (void)
{

/* determine the next activity when element fails */
	if (Current_Node->ttop_of_stack->no_of_elements > 1)
	{
		Current_Node->ttop_of_stack->no_of_elements--;
		Current_Node = Current_Node->level_point;

		sprintf (User_Msg, " >>(Fail_1) Go to node %s\n", Current_Node->name);
		Output_Decision ();
		Activity = NEXT;
	}
	else
	{			/* no_of_elements == 1 */
		Adjust_Stack_and_Output_Ptrs ();

		if (Animate_Flag)
		{
			Inverse_Node_Edge (Current_Node, BACKWARD);
		}

		Prev_Node = Current_Node;
		Current_Node = Current_Node->ancestor;

		if (Animate_Flag)
		{
			Inverse_Tree_Node (Current_Node);
		}

		sprintf (User_Msg, " <<(Fail_2) Back to Node %s\n", Current_Node->name);
		Output_Decision ();
		Activity = FAIL;
	}
}



static void     S_Sequence (void)
{

	switch (Activity)
	{
			case FIRST:
			sprintf (User_Msg, "__(SS_first) Sequence Node %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Node_Edge (Current_Node, FORWARD);
				Inverse_Tree_Node (Current_Node);
				Inverse_Tree_Node (Current_Node);
			}

		/*
		 * no match with corresponding matched node, go back to
		 * ancestor
		 */
			if (isupper (*Current_Node->name))
				if (!S_Find_Corr_Match2 ())
				{
					Activity = FAIL;
					Prev_Node = Current_Node;
					Current_Node = Current_Node->ancestor;
					break;
				}


			Temp_Stack = Stack_Allocation ();
		/* set up the starting & ending points of the matching */
			if (return_flag)
			{
				Temp_Stack->begin = Output_File.c_ptr;
				Temp_Stack->end = Output_File.c_ptr;
				if (concurrent)
				{
					Temp_Stack->begin = Output_data_c_ptr;
					Temp_Stack->end = Output_data_c_ptr;
				}
				Temp_Stack->from_tree_type = SYNTHESIS;
			}
			else
			{
				Temp_Stack->begin = W_Output_File.c_ptr;
				Temp_Stack->end = W_Output_File.c_ptr;
				if (concurrent)
				{
					Temp_Stack->begin = W_Output_data_c_ptr;
					Temp_Stack->end = W_Output_data_c_ptr;
				}
				Temp_Stack->from_tree_type = SYNTHESIS1;
			}

		/* initialize the number of elements (occurrence) */
			Temp_Stack->no_of_elements = 0;

			Locate_Stack_Element ();

		/* determine activity when element is successful */
			S_Successful_Element ();
			break;

		case NEXT:
			sprintf (User_Msg, "__(SS_next) Sequence Node %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Node_Edge (Current_Node, FORWARD);
				Inverse_Tree_Node (Current_Node);
				Inverse_Tree_Node (Current_Node);
			}

			if (Current_Node->ttop_of_stack->no_of_elements < Current_Node->upper)
			{
				Current_Node->ttop_of_stack->no_of_elements++;
				Current_Node = Current_Node->level_point;

				sprintf (User_Msg, " >> (No. < upper) Go to node %s\n",
					 Current_Node->name);
				Output_Decision ();
				Activity = FIRST;
			}
			else if (Current_Node->ttop_of_stack->no_of_elements == Current_Node->upper)
			{
				sprintf (User_Msg, " .. (No. = upper)\n");
				Output_Decision ();
				Current_Node->ttop_of_stack->no_of_elements++;
				S_Failed_Element ();
			}

			break;

		case SUCCEED:
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			sprintf (User_Msg, "__(SS_succeed) Sequence Node %s\n", Current_Node->name);
			Output_Decision ();
			sprintf (User_Msg, "B sequecne pointer%d %d\n", Current_Node->ttop_of_stack->end, Output_File.c_ptr);
			Output_Decision ();
			printf ("__(SS_succeed) Sequence Node %s\n", Current_Node->name);
			S_Successful_Element ();

			sprintf (User_Msg, "A sequecne pointer%d %d\n", Current_Node->ttop_of_stack->end, Output_File.c_ptr);
			Output_Decision ();
			break;

		case FAIL:
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			sprintf (User_Msg, "__(SS_fail) Sequence Node %s\n", Current_Node->name);
			Output_Decision ();
			S_Failed_Element ();

			break;

		default:
			break;

	}			/* switch */
}



static void     S_Sequence_No (void)
{
	struct data_node *Prev_output;
	struct data_node *Prev_wk;
	short           i;

	switch (Activity)
	{
		case FIRST:
			sprintf (User_Msg, "__(SSN_first) Squence No. %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Node_Edge (Current_Node, FORWARD);
				Inverse_Tree_Node (Current_Node);
			}

			sprintf (User_Msg, "");
			strncat (User_Msg, Current_Node->name, strlen (Current_Node->name) - 1);
			 /* MALCOLM WHY the "-1"? */ User_Msg[strlen (Current_Node->name) - 1] = '\0';
			for (i = 0; User_Msg[i]; i++)
				if (isupper (User_Msg[i]))
					User_Msg[i] = tolower (User_Msg[i]);

		/* ****************************************  */
		/* search for the corr. sequence match node  */
		/* ****************************************  */
			Temp_Stack = Root_Stack->forward_stack_ptr;

			while (strncmp (Temp_Stack->template_node_ptr->name, User_Msg,
					strlen (User_Msg))
					&& Temp_Stack->forward_stack_ptr)

			/*
			 * consider checking the node type; diff. type but
			 * same name
			 */
			{
				Temp_Stack = Temp_Stack->forward_stack_ptr;
			}

		/* Check nothing found  */
			if (!Temp_Stack->forward_stack_ptr)
			{
				sprintf (User_Msg, " => There is no corresponding match node found.\n");
				Output_Decision ();

				client_blink_window ();
				Activity = FAIL;
			}
			else
			{

				sprintf (User_Msg, "%d", Temp_Stack->no_of_elements);
				if (return_flag)
				{	/* 1 if */
					retry_fputs (User_Msg, Output_File.f_ptr);
					if (concurrent)
					{	/* 2 if */
						Current_output->next = (struct data_node *) calloc (1, sizeof (struct data_node));
						Prev_output = Current_output;
						Current_output = Current_output->next;
						Current_output->data = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
						strcpy (Current_output->data, User_Msg);
						Current_output->next = NULL;
						Current_output->front = Prev_output;
					}	/* end 2 if */
				}
				else
				{
					retry_fputs (User_Msg, W_Output_File.f_ptr);
					if (concurrent)
					{
						Current_wk->next = (struct data_node *) calloc (1, sizeof (struct data_node));
						Prev_wk = Current_wk;
						Current_wk = Current_wk->next;
						Current_wk->data = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
						strcpy (Current_wk->data, User_Msg);
						Current_wk->next = NULL;
						Current_wk->front = Prev_wk;
					}
				}	/* end else */
			/* push a stack element for template node */
				Temp_Stack = Stack_Allocation ();
				if (return_flag)
				{
					Temp_Stack->begin = Output_File.c_ptr;
					if (concurrent)
						Temp_Stack->begin = Output_data_c_ptr;
					Temp_Stack->from_tree_type = SYNTHESIS;
				}
				else
				{
					Temp_Stack->begin = W_Output_File.c_ptr;
					if (concurrent)
						Temp_Stack->begin = W_Output_data_c_ptr;
					Temp_Stack->from_tree_type = SYNTHESIS1;
				}

				if (return_flag)
				{
					Output_File.c_ptr += strlen (User_Msg);
					Temp_Stack->end = Output_File.c_ptr;
					if (concurrent)
					{
						Output_data_c_ptr++;
						Temp_Stack->end = Output_data_c_ptr;
					}
				}
				else
				{
					W_Output_File.c_ptr += strlen (User_Msg);
					Temp_Stack->end = W_Output_File.c_ptr;
					if (concurrent)
					{
						W_Output_data_c_ptr++;
						Temp_Stack->end = W_Output_data_c_ptr;
					}
				}	/* end else */

				Locate_Stack_Element ();

				sprintf (User_Msg, " => Output a string with Sequence No\n");
				Output_Decision ();
				clientXBell ();
				Activity = SUCCEED;
			}	/* else */

		/* <<<<  continue the rest of processing  >>>>  */
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

		/* adjust template node pointer to ancestor node */
			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

		/* Note: back to its ancestor */
			sprintf (User_Msg, " << Back to Node %s\n", Current_Node->name);
			Output_Decision ();
			break;

		case NEXT:
			sprintf (User_Msg, "__(SSN_next) Squence No. %s\n", Current_Node->name);
			Output_Decision ();

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
				Inverse_Node_Edge (Current_Node, BACKWARD);
			}

		/* free the stack */
			Temp_Stack = Current_Node->ttop_of_stack;
			Current_Stack = Current_Node->ttop_of_stack->backward_stack_ptr;
			Current_Stack->forward_stack_ptr = NULL;

		/* Adjust the template stack pointer */
			if (Current_Node->ttop_of_stack->prev_stack_element)
			/* more stack elements */
				Current_Node->ttop_of_stack = Current_Node->ttop_of_stack->prev_stack_element;
			else
				Current_Node->ttop_of_stack = NULL;

		/*
		 * Move backward to the previous position in output file
		 */
			if (return_flag)
			{
				Output_File.c_ptr = Temp_Stack->begin;
				fseek (Output_File.f_ptr, Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_output = seek_data (Current_output, Output_data_c_ptr - Temp_Stack->begin);
					Output_data_c_ptr = Temp_Stack->begin;
				}
			}
			else
			{
				W_Output_File.c_ptr = Temp_Stack->begin;
				fseek (W_Output_File.f_ptr, W_Output_File.c_ptr, SEEK_SET);
				if (concurrent)
				{
					Current_wk = seek_data (Current_wk, W_Output_data_c_ptr - Temp_Stack->begin);
					W_Output_data_c_ptr = Temp_Stack->begin;
				}
			}	/* end else */
			sprintf (User_Msg, " <- Backward output buffer pointer at location %d\n",
				 Output_File.c_ptr);
			Output_Decision ();

			sprintf (User_Msg, " ** Free a stack element at Node %s; adjust stack & "
				 "output pointers.\n",
				 Current_Node->name);
			Output_Decision ();
			free (Temp_Stack);

			Prev_Node = Current_Node;
			Current_Node = Current_Node->ancestor;

			if (Animate_Flag)
			{
				Inverse_Tree_Node (Current_Node);
			}

			sprintf (User_Msg, " << Fail; Back to Node %s\n", Current_Node->name);
			Output_Decision ();
			Activity = FAIL;
			break;

		default:
			break;

	}			/* switch */
}

static void     S_Unimplemented_feature (void)
{
	sprintf (User_Msg, "\n*---- Unimplemented language feature ----*\n"
		 "\tUsed in node %s.\n", Current_Node->name);
	Output_Decision ();

	Prev_Node = Current_Node;
	Current_Node = Current_Node->ancestor;

	sprintf (User_Msg, " FAIL<< Back to Node %s\n", Current_Node->name);
	printf (" FAIL<< Back to Node \n");
	Output_Decision ();

	if (Animate_Flag)
	{
		Inverse_Tree_Node (Current_Node);
	}
	Activity = FAIL;
	client_blink_window ();
}

/*
 * ....................................................... Synthesis
 * Processing .......................................................
 */

static void     S_Node_Type_Check (void)
{
	switch (Current_Node->type)
	{
			case LITERAL:
			S_Literal ();
			break;

		case MATCH_DIRECT_PRODUCT:
		case REFERENCE_DIRECT_PRODUCT:
			S_Direct_Product ();
			break;

		case MATCH_DISCRIMINATED_UNION:
		case REFERENCE_DISCRIMINATED_UNION:
			S_Discriminated_Union ();
			break;

		case MATCH_SEQUENCE:
		case MATCH_SEQUENCE_UNION:
		case MATCH_SEQUENCE_RANGE:
		case REFERENCE_SEQUENCE:
		case REFERENCE_SEQUENCE_UNION:
		case REFERENCE_SEQUENCE_RANGE:
			S_Sequence ();
			break;

		case REFERENCE_SEQUENCE_NO:
			S_Sequence_No ();
			break;

		case MODULE_CALL:
			printf ("module call\n");
			break;

		case PLUS:
		case MINUS:
		case TIMES:
		case DIVIDED_BY:
		case RANDOM:
			S_Primitives2 ();
			break;

		case ISEQUAL:
		case NOT_EQUAL:
		case GREATER_THAN:
		case GREATER_THAN_OR_EQUAL:
		case LESS_THAN:
		case LESS_THAN_OR_EQUAL:
			S_Primitives ();
			break;

		case PARALLELS:
			S_Parallel ();
			break;

		case TIMER:
			S_Timer ();
			break;

		case GET_TIME:
			S_GTimer ();
			break;

		case SEND_TO:
			S_Send (1);
			break;

		case RECEIVE_FROM:
			S_Receive (1);
			break;

		case ASEND_TO:
			S_Send (0);
			break;

		case ARECEIVE_FROM:
			S_Receive (0);
			break;

		case DELAYS:
			S_Delay ();
			break;

		default:
			S_Unimplemented_feature ();
			break;
	}			/* switch */
}


void            execution_proc (struct Template_Node * cur_node)
{
	Current_Node = cur_node;

	while (Current_Node->level_no != 0)	/* back to root node */
	{
		if (Current_Node->level_no == 1)
		{
			if (Current_Node->type & REFERENCE_NODE)
			{
				Tree_Type = ANALYSIS;
			}
			else if (!strncmp (Current_Node->name, "return", 6))
			{
				Tree_Type = SYNTHESIS;
				return_flag = 1;
			}
			else
			{
				Tree_Type = SYNTHESIS;
				return_flag = 0;
			}
		}
		Show_Node_Type ();	/* for internal testing only */

		if (Tree_Type == ANALYSIS)
		{
			A_Node_Type_Check ();
		}
		else
			S_Node_Type_Check ();

	}			/* while */
}

static int      itisempty (TOP t)
{
	return (t == NULL);

}

static DATA     vtop (TOP t)
{
	return (t->d);

}

static void     pop (TOP * t, DATA * x)
{
	TOP             t1 = *t;

	if (!itisempty (t1))
	{
		*x = t1->d;
		*t = t1->next;
		free (t1);
	}
	else
		printf ("empty  stack ! \n");
}

static void     push (TOP * t, DATA x)
{
	TOP             t1;

	printf ("x=%c", x);
	t1 = (struct stack *) calloc (1, sizeof (struct stack));
	t1->d = x;
	t1->next = *t;
	*t = t1;
}

/* Used by build_hoare_tree.c */

/*
 * MALCOLM MALCOLM can you tell if the following code will null terminate its
 * results ?
 */
void            Get_Parameters (void)
{
	TOP             p = NULL;
	int             i = 0,
	                j;
	char            ch,
	                ch1;
	char            name1[MAX_NODE_NAME_LEN + 1],
	                name2[MAX_NODE_NAME_LEN + 1];
	struct link_list *pre_para;
	struct link_list *tmp_para;

	strcpy (name1, "");
	strcpy (name2, "");
	while (*(Current_Node->name + i) != '\0')
	{
		if (strncmp ((Current_Node->name + i), "(", 1))
		{
			strncat (name1, Current_Node->name + i, 1);
			i++;
		}
		else
		{
			strcpy (name2, "");
			ch = '(';
			push (&p, ch);
			i++;
			j = i;
			while (!itisempty (p))
			{
				if (*(Current_Node->name + i) == ')')
				{
					ch1 = vtop (p);
					while (vtop (p) != '(')
					{
						ch1 = vtop (p);
						pop (&p, &ch1);
					}
					pop (&p, &ch1);
				}
				else if (*(Current_Node->name + i) == '(')
					push (&p, ch);

				strncat (name2, Current_Node->name + i, 1);
				i++;
			}	/* end while */
			j = i - j;
			strcpy (name2 + j - 1, "");

			tmp_para = (struct link_list *) calloc (1, sizeof (struct link_list));
			tmp_para->name = (char *) calloc (strlen (name2) + 1, sizeof (char));
			strcpy (tmp_para->name, name2);
			printf ("name2 %s\n", name2);

			if (Current_Node->para == NULL)
			{
				Current_Node->para = tmp_para;
				tmp_para->next = NULL;
				pre_para = tmp_para;
			}
			else
			{
				tmp_para->next = pre_para->next;
				pre_para->next = tmp_para;
				pre_para = tmp_para;
				printf ("name2 %s\n", Current_Node->para->name);
			}

		}		/* end else */
	}			/* end while   */
	Current_Node->module_name = (char *) calloc (strlen (name1) + 1, sizeof (char));
	strcpy (Current_Node->module_name, name1);
	printf ("name1 %s\n", Current_Node->module_name);
}
