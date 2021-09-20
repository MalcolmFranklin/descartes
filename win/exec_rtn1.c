#undef _POSIX_SOURCE		       /* Shared memory, and SysV message queues are not compliant with POSIX.1-1990 */
/*******************************************************************************
 * MODULE:	exec_rtn1.c
 *
 *	Exec_Run() is executed as a sub-process of the main startup process.
 *	Spec execution is done in this child process; the child passes
 *	messages to the main startup process to display messages and draw
 *	in the Hoare tree animation window.
 *
 *	This child process will spawn other subrpcess when the specification
 *	calls for "PARALLEL" processes (one of the real-time extensions of
 *	Descartes).  these sub-children are spawned in analysis1.c.
 *
 *******************************************************************************
 * $Date: 1994/08/10 19:07:50 $
 * $State: Exp $
 * $Locker: franklin $
 * $Source: /all/franklin/thesis/descartes/win/RCS/exec_rtn1.c,v $
 *
 **-M**************************************************************************/

#if 0
/******************************************************************************
 *
$Log: exec_rtn1.c,v $
 * Revision 1.67  1994/08/10  19:07:50  franklin
 * Add a signal handler to let you know when SIGCHILD events are received.
 *
 * Revision 1.66  1994/08/07  23:22:56  franklin
 * No more messages are passed via SysV queue, having the
 * key value (MSGKEY + 1).
 *
 * Revision 1.65  1994/08/06  22:04:59  franklin
 * Delete client_no_op().
 * Add static qualifiers to server-interface functions that are not needed
 * outside of this file.
 * Rename childproc_popup_error_dialog() to client_popup_error_dialog().
 *
 * Revision 1.64  1994/08/06  21:26:26  franklin
 * indent.  Remove test messages.
 *
 * Revision 1.63  1994/08/06  21:16:33  franklin
 * Delete commented-out code that used to either send a message
 * to the animation server via a SysV message queue, or that
 * made direct Xwindow drawing calls.
 *
 * Revision 1.62  1994/08/06  20:45:42  franklin
 * Replace message queue communication to the server (in function
 * parse() at wid1.c) with FIFOs.  Leave the replaced code in, just
 * commented out.
 *
 * Revision 1.61  1994/08/06  18:54:25  franklin
 * Remove calls to sem_close(); it is not needed by the new
 * semaphore implementation.
 *
 * Revision 1.60  1994/08/06  18:43:28  franklin
 * Removed Search_Module(); it was only called from exec_run1(),
 * which was never called by anybody.
 *
 * Revision 1.58  1994/08/06  18:37:46  franklin
 * The old 's' command (which I mapped to "SRV_NO_OP") turned out to
 * be a SCROLLING command, that ended up not being used in Chengs
 * version of the Descartes language processor.  I deleted messages
 * that sent an 's' command to the server.
 *
 * Revision 1.57  1994/08/06  18:11:21  franklin
 * Add functions to construct messages and pass them to the server;
 * this allows calls to the server to be abstracted out of the
 * client source code.
 *
 * Revision 1.56  1994/08/05  18:19:58  franklin
 * use INCLUDED_FROM_EXEC_RTN1 to tell wid1.h to show you the prototype for
 * parse()
 *
 * Revision 1.55  1994/08/05  17:49:05  franklin
 * 1. Add parent2child and child2parent globals.
 * 2. Remove calls to sem_open(), it is a dummy function that
 *    is not needed by the semops.c semaphore routines.
 * 3. Delete commented-out code and extra blank lines.
 * 4. Add parent2child parameter to exec_run() and parse().
 *
 * Revision 1.54  1994/08/04  22:35:06  franklin
 * workaround CodeCheck inability to handle ANSI variable argument lists.
 *
 * Revision 1.53  1994/08/04  17:56:22  franklin
 * Add #includes for cchk_missing_<standard include>.h in order
 * to get prototypes that CodeCheck doesnt think are there.
 *
 * Revision 1.52  1994/08/04  16:20:03  franklin
 * Draw_Tree_Node() local variable str_len -> len;  The "str" prefix
 * is reserved by string.h
 *
 * Revision 1.51  1994/08/03  16:42:04  franklin
 * Changed all identifiers with the prefix "E" to lower case "e",
 * changed identifiers such as "Exec_Proc" to "exec_proc", because
 * "E" prefix is reserved by errno.h.
 *
 * Revision 1.50  1994/08/02  13:36:51  franklin
 * ERROR_EXISTED -> XERROR_EXISTED (E prefix is reserved by ANSI)
 *
 * Revision 1.49  1994/08/02  00:32:01  franklin
 * Change top_of_stack to ttop_of_stack, because prefix "to" is reserved by
 * ctype.h
 *
 * Revision 1.48  1994/08/01  23:39:09  franklin
 * The suffix "_t" is reserved by POSIX.1
 *
 * Revision 1.47  1994/07/21  14:23:43  franklin
 * The Solaris 2.3 "/opt/SUNWspro/bin/cc" compiler requires
 * a cast from type size_t (returned by strlen()) to type
 * int in order to do comparisons w/ogenerating a warning.
 *
 * Revision 1.46  1994/07/17  20:40:38  franklin
 * Get the height and width of the animation window AFTER it is up on the
 * screen.  The parent of the drawing_a widget is an Xlib "window" object;
 * therefore, you cannot get its height and width until it is actually
 * realized.
 *
 * Suppress "branch not taken" warnings for if(1) ... else ... statements.
 * the "else" clauses serve as good comments.
 *
 * Revision 1.45  1994/07/08  02:47:02  franklin
 * Eliminate the use of the non POSIX.1 ftime() call.  It was used
 * to induce delays of a few milliseconds in order to control
 * the speed of the animation.  I replaced it with a call to a couple
 * of slow (order of a millisecond or two) system calls, calloc() and
 * free().
 *
 * Revision 1.44  1994/07/08  00:06:31  franklin
 * Added childproc_popup_error_dialog(), a function allowing child proceses
 * to have the server popup an application-modal error dialog box.
 *
 * Revision 1.43  1994/07/06  04:45:37  franklin
 * Added print_to_user_and_maybe_logfile() to eliminate some redundant code
 * Print more messages to the history log widget in the main window.
 * Clarify some diagnostic messages.  Move Set_Global_Filenames() to main.c,
 * and change its name to "set_global_filenames()".
 *
 * Revision 1.42  1994/07/01  18:00:18  franklin
 * If Output_File, S_Output_File, and/or W_Output_File cannot be opened, then
 * set them to stdout.
 * CRITICAL NOTE: If you set any of these files to stdout then DONT CLOSE
 *     THE FILE.  Closing stdout is bad -- if you dont believe me, just try it.
 *
 * Revision 1.41  1994/06/15  18:39:14  franklin
 * Remove the global flag Build_Flag_4_New_File.
 *
 * Revision 1.40  1994/06/14  23:46:22  franklin
 * Clean up some output messages.
 *
 * Revision 1.39  1994/06/14  15:39:33  franklin
 * Move #define constants for the expected file name suffixes, to exec_rtn1.h.
 * wid1.c needs these extensions so it can shorten the list of files in
 * a FileSelectionDialog box.
 *
 * Revision 1.38  1994/06/11  19:28:25  franklin
 * Define global variables only used by this file, as static:
 *
 * Revision 1.36  1994/06/09  00:52:01  franklin
 * Dont escape newline characters in order to split long string constants across
 * multiple lines of text.  Use ANSI/ISO Standard C string concatenation
 * instead.
 *
 * Revision 1.35  1994/06/06  23:08:30  franklin
 * Use a variable named "msgid" when referencing queue MSGKEY, and
 * use msgid1 when referencing MSGKEY1.  MSGKEY handles graphics,
 * and MSGKEY1 handles communications between parallel Descartes
 * sub-processes.
 *
 * Revision 1.34  1994/06/02  17:45:54  franklin
 * Enable stricter type checking when running the CenterLine "clcc" in
 * K&R compatibility mode (-Xa switch) by re-defining __STDC__ after processing
 * the non-ansi SunOS system include files.
 *
 * Revision 1.33  1994/05/24  18:44:39  franklin
 * Do not assume that there is a period in the
 * input file name.
 *
 * Revision 1.32  1994/05/24  15:05:32  franklin
 * Used ANSI/ISO "time()" function to report the time of day to the log file.
 * The language processor still needs the old UNIX system 7 "ftime()" command
 * in order to get time resolution of 1 millisecond on SunOS 4.1.x machines.
 *
 * Exec_Canvas_Setup(), and Canvas_Scrolling() were writing directly to
 * global "drawing_a", even though they were passed "drawing_a" by the
 * calling routine.  I changed the name of the input parameter form "canvas"
 * to "drawing_a" so they COULD draw to a different drawing area widget if
 * they had to.
 *
 * Re-arranged the if-then-else ladder which spawns the child process to
 * execute Exec_Run().
 *
 * Converted a hacked "for" loop to a more-appropriage "while" loop.:w
 *
 * Revision 1.31  1994/05/20  19:44:54  franklin
 * Remove nonsensical test to see if the input file name matches the
 * name of the first parameter to the top-most module in a specification.
 * Remove the useless TEST_NON_DIRECT_PRODUCT macro as well.
 *
 * Revision 1.30  1994/05/16  21:16:39  franklin
 * Use the new version of sem_create(), which needs no parameters, and performs
 * its own exception handling.
 *
 * Revision 1.29  1994/05/03  19:53:28  franklin
 * Replace printf() with a call to perror() if fork() fails to create a
 * child process.
 *
 * Revision 1.28  1994/05/03  00:53:00  franklin
 * #include stdlib.h for calloc() and free(); #include ctype.h for isupper();
 * delete references to variables that were never used.
 * re-run through "indent".
 *
 * Revision 1.27  1994/05/02  17:38:53  franklin
 * Remove nested includes in desc_struct.h.  Include unistd.h
 * and sys/stat.h here instead.
 *
 * Revision 1.26  1994/05/02  05:12:18  franklin
 * Include semops.h for declarations of semaphore operations.
 * Include unistd.h instead of sys/types.h
 *
 * Revision 1.25  1994/04/23  21:32:57  franklin
 * Remove slash-star sequence inside a comment to kill clcc warning.
 *
 * Revision 1.24  1994/04/14  22:19:22  franklin
 * Remove #include alert_dcl.h.  The information once there is now in
 * share_rtn.h and share_rtn.c
 *
 * Revision 1.23  1994/04/12  13:05:34  franklin
 * Clearly identify the input, output, and log file names.
 *
 * Revision 1.22  1994/04/12  11:23:14  franklin
 * Clarify messages.
 *
 * Revision 1.21  1994/04/12  09:42:19  franklin
 * Mark free()d pointers NULL, so you dont try to free() them again.
 *
 * Revision 1.20  1994/04/12  09:11:28  franklin
 * Allocate enough storage for strings AND their null terminator.
 *
 * Revision 1.19  1994/04/11  22:05:44  franklin
 * Re-run through the SunOS 4.1.3 "indent" utility.
 *
 * Revision 1.18  1994/04/11  22:04:14  franklin
 * Added a "static" qualifier to the definitions of all functions used
 * only within this file.
 *
 * Revision 1.17  1994/04/11  21:14:51  franklin
 * ANSIfy function signatures.
 *
 * Revision 1.16  1994/04/11  20:46:03  franklin
 * Remove unused global "Exec_Msg_Row", and unused #defines EXEC_FRAME_LABEL
 * and PIX_INV
 *
 * Revision 1.15  1994/04/11  20:37:14  franklin
 * Removed functions that were never called from anywhere:
 * Create_Exec_Popup	Create_Exec_Base_Panel	Create_Exec_Canvas
 * Create_Exec_Msg_Panel create_Exec_Preview_Textsw
 * DESC_Input_Done	Exec_Help_Done	Exec_Done
 *
 * Revision 1.14  1994/04/11  20:19:53  franklin
 * Clarify some of the messages.
 *
 * Revision 1.13  1994/04/10  23:11:54  franklin
 * Dont #include analysis1.h twice.
 *
 * Revision 1.12  1994/04/10  23:01:02  franklin
 * Get the declarations of globals used from wid1.c, by including wid1.h.
 *
 * Revision 1.11  1994/04/10  22:14:43  franklin
 * Change the parameter lists of Exec_Draw() and Exec_Proc() to match the
 * parameters that they will be passed when they are invoked as callbacks
 * from an XmPushButtonwidget.
 *
 * Revision 1.10  1994/04/09  23:54:14  franklin
 * analysis1.h needs the definition of type Pixmap from <X11/X.h>
 *
 * Revision 1.9  1994/04/09  21:49:50  franklin
 * Moved declarations needed by analysis1.c into header file exec_rtn1.h.
 * Changed "short"s to "int"s to prevent problems linking modules built with
 * ANSI/ISO Standard C and K&R C.
 * Changed Activity from a short to processing_situation_t (enumerated type).
 * Changed Tree_Type from a short to tree_t (enumerated type).
 *
 * Revision 1.8  1994/04/08  06:40:35  franklin
 * Get the definition of BACKWARD and FORWARD, as well as the declaration for
 * Execution_Proc() from analysis1.h.
 * Get the declaration of parse() from wid1.h.
 *
 * Revision 1.7  1994/04/08  06:19:59  franklin
 * Remove declarations of functions no-longer called from this file.
 *
 * Revision 1.6  1994/04/08  06:13:01  franklin
 * Remove declarations of functions no-longer called from share_var.c
 *
 * Revision 1.5  1994/04/08  05:45:44  franklin
 * Get the declaration of Get_File_Stat() from share_rtn.h
 * Delete references to functions from share_rtn.c that were
 * never called from anywhere.
 *
 * Revision 1.4  1994/04/08  05:22:36  franklin
 * Remove declarations of functions that were never used anywhere.
 *
 * Revision 1.3  1994/04/08  00:32:01  franklin
 * Dump the unmatched input data to stdout on failure.
 *
 * Revision 1.2  1994/03/30  05:45:53  franklin
 * Run through SunOS "indent" program to get consistent indentation sytle.
 * Add a module header w/ RCS tokens.  NO OTHER changes were made
 * in this file version.
 *
 ******************************************************************************/
#endif

static char    *rcsid = "@(#) $Id: exec_rtn1.c,v 1.67 1994/08/10 19:07:50 franklin Exp franklin $";

/*
 * Program Name:	exec_rtn.c Modified Date:	Nov. 6, 1929
 * 
 */

#include <stdlib.h>
#include "cchk_missing_stdlib.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <stdarg.h>
#include "cchk_missing_stdarg.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include "cchk_missing_unistd.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <sys/stat.h>

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

#include "desc_struct.h"
#include "share_rtn.h"

#include <X11/X.h>		       /* analysis1.h needs the definition of type "Pixmap" */
#include "analysis1.h"		       /* execution_proc(), para[], p_cnt */

#include <sys/ipc.h>
#include <sys/msg.h>

#include <fcntl.h>

#include "mesg.h"

#include <Xm/Text.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>

#include "some_utils.h"
#include "hash.h"
#include "fifo.h"
#define INCLUDED_FROM_EXEC_RTN1	1      /* Tell wid1.c that you want to see the prototype for parse(). */
#include "wid1.h"		       /* parse(), and several globals. */

#include "exec_rtn1.h"
#include "semops.h"

shared_fifodata_tt *parent2child;      /* Struct for FIFO read by the server process, and written to by all child processes. Note
				        * that each child gets a seperate copy of this variable when it is fork()ed.  Data fields
				        * which cannot be known before the child is created, must be initialized inside of each
				        * fork()ed process.  */
reply_fifodata_tt *child2parent = NULL;/* Struct for the replies written by the server process, and read by each individual child
				        * proces.  Note that each child has its own individual reply FIFO, for which it is the
				        * only reader. */

#define	XEOF_MARKER		0x1a

/*
 * Enumerated types processing_situation_t and tree_t are defined in
 * desc_struct.h
 */
processing_situation_tt Activity;      /* indicates the current processing during the Analysis/Synthesis; there are 4 situations-
				        * First, Next, Succeed, and Fail. */
tree_tt         Tree_Type;	       /* One of ANALYSIS, SYNTHESIS, or SYNTHESIS1 */

int             Trace_Flag = TRUE;
int             Animate_Flag;
int             Log_Flag;
static int      Draw_Flag;

/* Input_File for input string , S_Input_File for nothing */
struct input_format Input_File;
struct input_format S_Input_File;

/* S_Output_File for parameters, W_Output_File for non-return analysis trees */
struct output_format Output_File;
struct output_format S_Output_File;
struct output_format W_Output_File;

struct log_format Log_File;

/*
 * x_end - the position of bottom right in x axis (rectangle) y_end - the
 * position of bottom right in y axis c_start_x - the position of bottom left
 * in x axis for the 1st char in the string c_start_y - the position of
 * bottom left in y axis for the 1st char in the string
 */

static int      x_end,
                y_end,
                c_start_x,
                c_start_y;
static int      g_count;	       /* Global Counter */

static short   *C_Top,
               *C_Left,
               *C_Bottom,
               *C_Right;	       /* for exec_canvas use */

static int      semid_d;	       /* semaphore for drawing */
static int      shmid[4];


/*******************************************************************************
 * FUNCTION:    DISPLAY_EXEC_MSG
 *	Tell the server (parent) to write a message to the main window message
 *	area.  The server will invoke Display_Build_User_Msg().
 ******************************************************************************/
void            Display_Exec_Msg (char *msg)
{
	send2parent (parent2child, SRV_DISPLAY_EXEC_MSG, msg);
}

/*******************************************************************************
 * FUNCTION:    CLIENT_POPUP_ERROR_DIALOG
 *
 * PURPOSE:     Tell the server(parent) process to post an application-modal
 *              error dialog box.
 *
 * PARAMETERS:  Same parameter list as printf()
 ******************************************************************************/

void            client_popup_error_dialog (const char *printf_fmt_str,...)
{
	va_list         arguments;
	char            buf[4096];     /* Just make it "big" */

	va_start (arguments, printf_fmt_str);
	vsprintf (buf, printf_fmt_str, arguments);
	send2parent (parent2child, SRV_POPUP_ERROR_DIALOG, buf);
	va_end (arguments);
}

/*******************************************************************************
 * FUNCTION:	clientXDrawLine
 *
 *	Replaces the old message 'd'.  Take the 'd' and its trailing whitespace
 *	off of the front of the old message, in order to get the new message.
 * PARAMETERS:
 *	inverted -- if nonzero, then tell parent to draw the line with the
 *	         -- inverse graphic context (inv_gc).
 *	x1,y1,x2,y2 -- Endpoints of the line.
 ******************************************************************************/
static void     clientXDrawLine (int inverted, int x1, int y1, int x2, int y2)
{
	char            buf[INTLEN + 1 + INTLEN + 1 + INTLEN + 1 + INTLEN + 1 + INTLEN + 1];	/* 5 integers, plus separating
												 * blanks, and NULL terminator. */

	sprintf (buf, "%d %d %d %d %d", inverted, x1, y1, x2, y2);
	send2parent (parent2child, SRV_DRAW_LINE, buf);
}

/*******************************************************************************
 * FUNCTION:	clientXCopyArea
 *
 *	Replaces the old 'c' message.
 *	TRICKY: replace the first TWO whitespace delimited fields ('c' and an
 *		int.) the old first integer  was set to the "inverted" (gc_n)
 *		variable in the server, but it was never used.
 ******************************************************************************/
static void     clientXCopyArea (int src_x, int src_y, int width, int height, int dest_x, int dest_y)
{
	char            buf[INTLEN + 1 + INTLEN + 1 + INTLEN + 1 + INTLEN + 1 + INTLEN + 1 + INTLEN + 1];	/* 6 integers, plus
														 * separating blanks,
														 * and NULL terminator. */

	sprintf (buf, "%d %d %d %d %d %d", src_x, src_y, width, height, dest_x, dest_y);
	send2parent (parent2child, SRV_COPY_AREA, buf);
}

/*******************************************************************************
 *	clientXDrawString
 *
 *	Replaces the old 't' message.
 *	Delete the first TWO whitespace delimited fields ('t' and and int)
 *	NOTE:	This function sends TWO MESSAGES, the first message contains
 *		the integer parameters, wich will be parsed in the server by
 *		sscanf().
 *		The second message contains the string to be sent to the
 *		server.  The string MAY CONTAIN WHITESPACE which would goof
 *		up sscanf(); therefore it is sent in a separate message.
 ******************************************************************************/
static void     clientXDrawString (int x, int y, char *nodename, int length)
{
	char            buf[INTLEN + 1 + INTLEN + 1 + INTLEN + 1];	/* Three integers, and a null terminator. */

	sprintf (buf, "%d %d %d", x, y, length);
	fflush (stdout);
	send2parent (parent2child, SRV_DRAW_STRING, buf);
	send2parent (parent2child, SRV_DRAW_STRING, nodename);
}

/*******************************************************************************
 * FUNCTION:	clientXBell
 *	Replaces old 'b' command. No parameters.
 ******************************************************************************/
void            clientXBell (void)
{
	send2parent (parent2child, SRV_BELL, "");
}

/*******************************************************************************
 * FUNCTION:	CLIENT_BLINK_WINDOW
 *	Replaces old 'k' command. No parameters.
 ******************************************************************************/
void            client_blink_window (void)
{
	send2parent (parent2child, SRV_BLINK, "");
}


/*******************************************************************************
 * FUNCTION:    CLIENT_SHUTDOWN_SERVER
 *      Replaces old 'f' command. No parameters.
 ******************************************************************************/
static void     client_shutdown_server (void)
{
	send2parent (parent2child, SRV_SHUTDOWN, "");
}

struct Stack_Node *Stack_Allocation (void)
{
	if ((Temp_Stack = (struct Stack_Node *) calloc (1, sizeof (struct Stack_Node))) == NULL)
		util_abort (__LINE__, __FILE__, "calloc() failed.\n");

	return Temp_Stack;
}

void            Stack_Save (void)
{

/*
 * Dec. 6, 1990 modified for freeing the Root Stack and letting execution
 * repeat as many times as possible
 */
	if (Root_Stack->forward_stack_ptr)
	{
		Current_Stack = Root_Stack->forward_stack_ptr;
		printf ("save Root Stack\n");

	/*
	 * free(Root_Stack->template_node_ptr->ttop_of_stack);
	 * Root_Stack->template_node_ptr->ttop_of_stack = NULL;
		 */ printf ("save Root Stack\n");
		while (Current_Stack)
		{
			Temp_Stack = Current_Stack;
			Current_Stack = Current_Stack->forward_stack_ptr;
			if (Temp_Stack->template_node_ptr)
				printf ("save (stack) name ->%s\n", Temp_Stack->template_node_ptr->name);

			Temp_Stack->template_node_ptr->ttop_of_stack = NULL;

		}		/* while */
	}
	else if (Root_Stack)
	{
	/* printf("save Root Stack only\n"); */
		Root_Stack->template_node_ptr->ttop_of_stack = NULL;
		printf ("save Root Stack only\n");
	}
	else
	{
		printf ("Nothing save\n");
		return;
	}

}

void            Stack_Restore (void)
{

/*
 * Dec. 6, 1990 modified for freeing the Root Stack and letting execution
 * repeat as many times as possible
 */
	if (Root_Stack->forward_stack_ptr)
	{
		printf ("restore Root Stack\n");
		Current_Stack = Root_Stack->forward_stack_ptr;

	/*
	 * Root_Stack->template_node_ptr->ttop_of_stack = Root_Stack;
	 */
		while (Current_Stack)
		{
			Temp_Stack = Current_Stack;
			Current_Stack = Current_Stack->forward_stack_ptr;
			if (Temp_Stack->template_node_ptr)
				printf ("restore (stack) name->%s\n", Temp_Stack->template_node_ptr->name);

			Temp_Stack->template_node_ptr->ttop_of_stack = Temp_Stack;

		}		/* while */
	}
	else if (Root_Stack)
	{
		printf ("restore Root Stack only\n");
		Root_Stack->template_node_ptr->ttop_of_stack = NULL;
	}
	else
	{
		printf ("Nothing restore \n");
		return;
	}

}

static void     Template_Stack_Ptr_Free (struct Template_Node * cur_node)
{
	if (cur_node->level_point == NULL && cur_node->front == NULL)
	{
		if (cur_node->ttop_of_stack)
		{
			free (cur_node->ttop_of_stack);
			cur_node->ttop_of_stack = NULL;

		/*
		 * printf("clear (stack ptr) name ->%s\n", cur_node->name);
		 */
			if (cur_node->extra_front)
			{
				if (cur_node->extra_front->ttop_of_stack)
				{

				/*
				 * printf("(sequence) node ->%s\n",
				 * cur_node->name);
				 */
					free (cur_node->extra_front->ttop_of_stack);
					cur_node->extra_front->ttop_of_stack = NULL;
				}
			}
		}
		return;
	}

	if (cur_node != NULL)
	{
		if (cur_node->ttop_of_stack)
		{
			free (cur_node->ttop_of_stack);
			cur_node->ttop_of_stack = NULL;

		/*
		 * printf("clear (stack ptr) name ->%s\n", cur_node->name);
		 */
			if (cur_node->extra_front)
			{
				if (cur_node->extra_front->ttop_of_stack)
				{
					free (cur_node->extra_front->ttop_of_stack);
					cur_node->extra_front->ttop_of_stack = NULL;
				}
			}
		}
		if (cur_node->level_point != NULL)
			Template_Stack_Ptr_Free (cur_node->level_point);
	}

	if (cur_node->front != NULL)
	{
		Template_Stack_Ptr_Free (cur_node->front);
	}
	return;
}

static void     Stack_Free (void)
{

/*
 * Dec. 6, 1990 modified for freeing the Root Stack and letting execution
 * repeat as many times as possible
 */
	if (Root_Stack->forward_stack_ptr)
	{
	/* printf("free Root Stack\n"); */
		Current_Stack = Root_Stack->forward_stack_ptr;
		if (Root_Stack)
		{
			free (Root_Stack);
			Root_Stack = NULL;
		}

		while (Current_Stack)
		{
			Temp_Stack = Current_Stack;
			Current_Stack = Current_Stack->forward_stack_ptr;
			if (Temp_Stack->template_node_ptr)

				if (Temp_Stack)
				{
					free (Temp_Stack);
					Temp_Stack = NULL;
				}
		}		/* while */
	}
	else if (Root_Stack)
	{
		free (Root_Stack);
		Root_Stack = NULL;
	}
	else
	{
		printf ("Nothing freed\n");
		return;
	}

	Template_Stack_Ptr_Free (Hoare_Root_Dummy->level_point);
}

static void     exec_flags_setting (void)
{
	Log_Flag = ON;
}

static void     exec_canvas_setup (Widget drawing_a)
{
	shmid[0] = shmget (SHMKEY + 5, sizeof (short), 0777 | IPC_CREAT);
	if (shmid[0] == -1)
		printf ("can not create shared mem\n");
	C_Top = (short *) shmat (shmid[0], 0, 0);

	shmid[1] = shmget (SHMKEY + 6, sizeof (short), 0777 | IPC_CREAT);
	if (shmid[1] == -1)
		printf ("can not create shared mem\n");
	C_Bottom = (short *) shmat (shmid[1], 0, 0);

	shmid[2] = shmget (SHMKEY + 7, sizeof (short), 0777 | IPC_CREAT);
	if (shmid[2] == -1)
		printf ("can not create shared mem\n");
	C_Left = (short *) shmat (shmid[2], 0, 0);

	shmid[3] = shmget (SHMKEY + 8, sizeof (short), 0777 | IPC_CREAT);
	if (shmid[3] == -1)
		printf ("can not create shared mem\n");
	C_Right = (short *) shmat (shmid[3], 0, 0);
	*C_Top = 0;
	*C_Left = 0;

/*
 * The parent widget of drawing_a is an Xlib "window" object.  You can only
 * get the values from an Xlib window when it is being displayed, therefore
 * you cannot get its height and width when you create it.
 */
	XtVaGetValues (XtParent (drawing_a), XmNwidth, &win_width, XmNheight, &win_height, NULL);
	XtVaGetValues (XtParent (drawing_a), XmNwidth, C_Right, XmNheight, C_Bottom, NULL);
}

/*******************************************************************************
 * FUNCTION:	PRINT_SUCCESSFUL_EXECUTION_INFO
 *	If the Descartes specification accepts all of its input data, then:
 *
 *	1. Tell the user
 *	2. If the user enabled logging, write about the success to the log file
 *	3. If the output file was not sent to stdout (this happens when the
 *	   program cannot read the specified output file), then display the
 *	   output of the run to the user.
 *	4. If logging is enabled, and the output was not sent to stdout, then
 *	   copy the output of the run to the log file.
 *
 * NOTE:  The parameter "calledfrom" is simply a convenience hook, in case you
 *	  have to trace back a problem to one of the points where this
 *	  function is called from.
 ******************************************************************************/
static void     print_to_user_and_maybe_logfile (char *User_Msg)
{
	Display_Exec_Msg (User_Msg);
	if (Log_Flag)
		fputs (User_Msg, Log_File.f_ptr);
}
static void     print_successful_execution_info (const int calledfrom)
{
	char           *outfile_contents;
	int             outfile_len;

	outfile_contents = NULL;

	sprintf (User_Msg, "Your specificaton ran successfully.\n");
	print_to_user_and_maybe_logfile (User_Msg);

	if (Output_File.f_ptr != stdout)
	{
		outfile_contents = load_file_into_charbuf (Output_File.name, &outfile_len);
		if (outfile_contents)
		{
			sprintf (User_Msg, "Output file length = %d.  Contents:\n", outfile_len);
			print_to_user_and_maybe_logfile (User_Msg);

		/*
		 * The output file may contain a NULL character, which could
		 * mess up fputs().  Use fwrite() to copy output file to the
		 * Log file.
		 */
			Display_Exec_Msg (outfile_contents);
			sprintf (User_Msg, "\n");
			Display_Exec_Msg (User_Msg);
		}
	}
	if (Log_Flag && (Output_File.f_ptr != stdout) && outfile_contents)
	{
		fwrite (outfile_contents, 1, outfile_len, Log_File.f_ptr);
		fwrite ("\n", 1, strlen ("\n"), Log_File.f_ptr);
		fflush (Log_File.f_ptr);
	}
	if (outfile_contents)
		free (outfile_contents);
}

/*******************************************************************************
 * FUNCTION:	EXEC_RUN
 *
 * PURPOSE:	This function is the top-level child of all subchild processes.
 *	This function establishes the communication link with the user-
 *	interface server parse() in wid1.c.
 ******************************************************************************/
static void     exec_run (shared_fifodata_tt * parent2child)
{
	struct Template_Node *Root_Node;
	int             msgid1;
	void           *dummyptr1;
	XmPushButtonCallbackStruct *dummyptr2;
	time_t          timeofday;
	const char     *base_fname;
	char            child_pidstr[INTLEN];
	size_t          reply_len;
	char           *message;
	const char     *reply_ptr;

	dummyptr1 = NULL;	/* Shut up warning messages about dummy parameters not being set before they are passed to a
				 * function.. */
	dummyptr2 = NULL;
	semid_d = sem_create ();
	concurrent = 0;		/* initialize concurrent flag */

/* Establish communication with the user-interface server process. */
	sprintf (child_pidstr, "%d", getpid ());
	connect_to_parent (parent2child, child_pidstr, &child2parent);
	if ((message = malloc (shared_fifo_bufsiz (parent2child))) == NULL)
	{
		util_abort (__LINE__, __FILE__, "malloc() failed.\n");
	}
/* Test connection. */
	sprintf (message, "echomeback echomeback echomeback");
	send2parent (parent2child, SRV_ECHO, message);
	receive_fm_parent (child2parent, &reply_len);
	reply_ptr = reply_fifo_data (child2parent);

	client_blink_window ();

	if ((msgid1 = msgget (MSGKEY1, 0666 | IPC_CREAT)) < 0)
		printf ("can not get message queue\n");

/*
 * Set up Analysis Buffer String and analysis pointer; Allocate a stack
 * element associated with the module title
 */
	if (!Check_File (Input_File.name))
	{
		Continue_Msg (INPUT_FILE_NOT_EXISTED);
		base_fname = get_base_filename (Input_File.name);
		printf ("Input file:\n\"%s\"\ndoes not exist.", base_fname ? base_fname : "(NULL)");
		fflush (stdout);
		client_popup_error_dialog ("Input file:\n\"%s\"\ndoes not exist.", base_fname ? base_fname : "(NULL)");

		client_shutdown_server ();
		destroy_child2parent (child2parent);
		free (child2parent);
		free (message);
		exit (0);
	}

	if ((Input_File.f_ptr = fopen (Input_File.name, "r")) == NULL)
	{
		Continue_Msg (OPENING_FILE_FAILED);
		base_fname = get_base_filename (Input_File.name);
		printf ("Cannot open file:\n\"%s\".", base_fname ? base_fname : "(NULL)");
		fflush (stdout);
		client_popup_error_dialog ("Cannot open file:\n\"%s\".", base_fname ? base_fname : "(NULL)");

		client_shutdown_server ();
		destroy_child2parent (child2parent);
		free (child2parent);
		free (message);
		exit (0);
	}

	exec_canvas_setup (drawing_a);

	DESC_File_Stat = Get_File_Stat (Input_File.name);
/* printf("input file size - %d\n", DESC_File_Stat.st_size); */

	Input_File.buffer = (char *) calloc (DESC_File_Stat.st_size + 1, sizeof (char));

	while (fgets (DESC_Line_Str, MAX_LINE_SIZE, Input_File.f_ptr) != NULL)
	{
		strcat (Input_File.buffer, DESC_Line_Str);
	}

	fclose (Input_File.f_ptr);

	sprintf (User_Msg, "Length of input stream: %d\n", strlen (Input_File.buffer));
	Display_Exec_Msg (User_Msg);
	Display_Exec_Msg ("Input stream contents:\n");
	Display_Exec_Msg (Input_File.buffer);
	Display_Exec_Msg ("\n");

/* initialize analysis input pointers */
	Input_File.s_ptr = 0;
	Input_File.c_ptr = 0;

	exec_flags_setting ();	/* flags for TRACE & ANIMATE; Delay Time */

	if ((!Draw_Flag) && (Animate_Flag))
	{
		printf ("drawing diagram \n");
		exec_draw (drawing_a, dummyptr1, dummyptr2);
	}

	if (Animate_Flag)
	{
		Inverse_Tree_Node (Hoare_Root_Dummy->level_point);
	}

	Root_Stack = Stack_Allocation ();	/* root dummy */
	Current_Stack = Stack_Allocation ();	/* module title */

/* thread connection */
	Root_Stack->forward_stack_ptr = Current_Stack;
	Current_Stack->backward_stack_ptr = Root_Stack;

	Current_Stack->template_node_ptr = Hoare_Root_Dummy->level_point;
	Hoare_Root_Dummy->level_point->ttop_of_stack = Current_Stack;

	if (Animate_Flag)
	{
		Inverse_Tree_Node (Hoare_Root_Dummy->level_point);
	}

	sprintf (User_Msg, "Execute specification.\n");
	Display_Exec_Msg (User_Msg);

	if (Log_Flag)
	{
		time (&timeofday);
		Log_File.f_ptr = fopen (Log_File.name, "w");
		if (Log_File.f_ptr == NULL)
		{
			Log_File.f_ptr = stdout;
			sprintf (User_Msg, "Could not open log file for writing:\n");
			Display_Exec_Msg (User_Msg);
			sprintf (User_Msg, "\t%s\n", Log_File.name ? Log_File.name : "(NULL)");
			Display_Exec_Msg (User_Msg);
			sprintf (User_Msg, "Will write log to stdout instead.\n");
			Display_Exec_Msg (User_Msg);
		}
		sprintf (User_Msg, "Descartes' Trace Log  Ver 1.0   Time: %s",
			 ctime (&timeofday));
		fputs (User_Msg, Log_File.f_ptr);
		sprintf (User_Msg, "--------------------------------------------------------------");
		fputs (User_Msg, Log_File.f_ptr);
		sprintf (User_Msg, "\n\n  #####   Beginning   #####\n\n\n");
		fputs (User_Msg, Log_File.f_ptr);
		sprintf (User_Msg, "Descartes specification file: \"%s.\n",
			 DESC_New_File_Name);
		fputs (User_Msg, Log_File.f_ptr);
		sprintf (User_Msg, "Log file:                     \"%s.\n\n", Log_File.name);
		fputs (User_Msg, Log_File.f_ptr);
		sprintf (User_Msg, "Contents of the Descartes specification file:\n");
		fputs (User_Msg, Log_File.f_ptr);
		fputs (Input_File.buffer, Log_File.f_ptr);
		sprintf (User_Msg, "\n\n");
		fputs (User_Msg, Log_File.f_ptr);
	}

/* Begin to write the tracing messages on the window and disk file  */
	sprintf (User_Msg, "Module Title %s\n", Hoare_Root_Dummy->level_point->name);
	if (Trace_Flag)
	{
		Display_Exec_Msg (User_Msg);
	}
	if (Log_Flag)
	{
		fputs (User_Msg, Log_File.f_ptr);
	}

/* proceed the INPUT argument */
	Root_Node = Hoare_Root_Dummy->level_point->level_point;
	while (Root_Node && isupper (*Root_Node->name))
	{
		Activity = FIRST;

		execution_proc (Root_Node);
		if (Animate_Flag)
		{
			Inverse_Tree_Node (Hoare_Root_Dummy->level_point);
		}
		Root_Node = Root_Node->front;
	}

/* there are something wrong somewhere */
/* the matching of input is not complete yet */
	if (Tree_Type == ANALYSIS)
	{
		if (Input_File.c_ptr < (int) strlen (Input_File.buffer))
		{
			sprintf (User_Msg, "==> It doesnot reach the end of the file; check "
				 "either specification or input.\n");
			Display_Exec_Msg (User_Msg);
			fflush (stderr);
			fflush (stdout);
			sprintf (User_Msg, "Failed %d bytes from the beginning of the input stream.\n"
				 "Contents of the rest of the input buffer:\n\t\"%s\"\n",
				 (int) Input_File.c_ptr, (Input_File.buffer + Input_File.c_ptr));
			Display_Exec_Msg (User_Msg);
			if (Log_Flag)
			{
				fputs (User_Msg, Log_File.f_ptr);
			}
			Activity = FAIL;
		}
	}

	if (Activity == SUCCEED)
	{
		sprintf (User_Msg, "The analysis procedure was successful.\n");
		Display_Exec_Msg (User_Msg);
		if (Log_Flag)
		{
			fputs (User_Msg, Log_File.f_ptr);
		}

	/*
	 * if ( Animate_Flag )  {
	 * Inverse_Tree_Node(Hoare_Root_Dummy->level_point); }
	 */
		sprintf (User_Msg, "Continue synthesis procedure.\n");
		Display_Exec_Msg (User_Msg);
		if (Log_Flag)
		{
			fputs (User_Msg, Log_File.f_ptr);
		}

	/* proceed "return" for output segment */

		Output_File.c_ptr = 0;
		Output_File.f_ptr = fopen (Output_File.name, "w+");
		if (Output_File.f_ptr == NULL)
		{
			Output_File.f_ptr = stdout;
			sprintf (User_Msg, "Could not open output file for writing:\n");
			Display_Exec_Msg (User_Msg);
			sprintf (User_Msg, "     %s\n", Output_File.name ? Output_File.name : "(NULL)");
			Display_Exec_Msg (User_Msg);
			sprintf (User_Msg, "Will write output to stdout instead.\n");
			Display_Exec_Msg (User_Msg);
		}

		W_Output_File.c_ptr = 0;
		W_Output_File.f_ptr = fopen (W_Output_File.name, "w+");
		if (W_Output_File.f_ptr == NULL)
		{
			W_Output_File.f_ptr = stdout;
			sprintf (User_Msg, "Could not open W_Output_File file for writing:\n");
			Display_Exec_Msg (User_Msg);
			sprintf (User_Msg, "     %s\n", W_Output_File.name ? W_Output_File.name : "(NULL)");
			Display_Exec_Msg (User_Msg);
			sprintf (User_Msg, "Will write W_Output_File to stdout instead.\n");
			Display_Exec_Msg (User_Msg);
		}

		while (Root_Node)
		{
			Activity = FIRST;
			execution_proc (Root_Node);
			if (Animate_Flag)
			{
				Inverse_Tree_Node (Hoare_Root_Dummy->level_point);
			}
			Root_Node = Root_Node->front;
		}

		printf ("end of execution proc \n");
		printf ("\n####final file length %d %d\n", Output_File.c_ptr, W_Output_File.c_ptr);
	/* <<  Explicitly-written EOF marker into the file by program  >> */
	/* fputc (XEOF_MARKER, Output_File.f_ptr); */
		fflush (Output_File.f_ptr);

	/* <<  Explicitly-written EOF marker into the file by program  >> */
		fputc (XEOF_MARKER, W_Output_File.f_ptr);	/* This line probably should be commented out. */
		fflush (W_Output_File.f_ptr);
		if (W_Output_File.f_ptr != stdout)	/* If you were able to open the W_Output_File */
			fclose (W_Output_File.f_ptr);
		if (Output_File.f_ptr != stdout)	/* If you were able to open the Output_File */
			fclose (Output_File.f_ptr);

		if (Activity == SUCCEED)
		{
			print_successful_execution_info (__LINE__);
		}
		else
		{
			sprintf (User_Msg, "The synthesis procedure failed.\n");
			Display_Exec_Msg (User_Msg);
			if (Log_Flag)
			{
				fputs (User_Msg, Log_File.f_ptr);
			}
			goto NO_OUTPUT;
		}
	}			/* if2  */
	else
	{			/* if 1 */

		sprintf (User_Msg, "The analysis procedure failed.\n");
		Display_Exec_Msg (User_Msg);
		if (Log_Flag)
		{
			fputs (User_Msg, Log_File.f_ptr);
		}

NO_OUTPUT:
		sprintf (User_Msg, "No output is produced at this execution.\n");
		Display_Exec_Msg (User_Msg);
		if (Log_Flag)
		{
			fputs (User_Msg, Log_File.f_ptr);
		}
	}			/* else */
/* after execution, free an input file name & all stack elements */
/* free input buffer string */
	if (Input_File.buffer)
	{
		free (Input_File.buffer);
		Input_File.buffer = NULL;
	}

	if (Log_Flag)
	{
		sprintf (User_Msg, "#####   THE  END   #####\n");
		fputs (User_Msg, Log_File.f_ptr);
		if (Log_File.f_ptr != stdout)	/* If you were able to open the output file. */
			fclose (Log_File.f_ptr);
	}
	Stack_Free ();
	sprintf (User_Msg, "Free all stacks.\n");
	Display_Exec_Msg (User_Msg);

	sprintf (User_Msg, " #####   THE  END   #####\n");

	if (msgctl (msgid1, IPC_RMID, (struct msqid_ds *) 0) < 0)
		printf ("can not remove message queue\n");

	if (shmctl (shmid[0], IPC_RMID, 0) < 0)
		printf ("can not remove share memory\n");

	if (shmctl (shmid[1], IPC_RMID, 0) < 0)
		printf ("can not remove share memory\n");

	if (shmctl (shmid[2], IPC_RMID, 0) < 0)
		printf ("can not remove share memory\n");

	if (shmctl (shmid[3], IPC_RMID, 0) < 0)
		printf ("can not remove share memory\n");

	printf ("Shutting down the server line %d of %s\n", __LINE__, __FILE__);
	client_shutdown_server ();
	destroy_child2parent (child2parent);
	free (child2parent);
	free (message);
	exit (0);
}

void            exec_run2 (void)
{
	struct Template_Node *Root_Node;
	void           *dummyptr1;
	XmPushButtonCallbackStruct *dummyptr2;

	dummyptr1 = NULL;
	dummyptr2 = NULL;

	sprintf (User_Msg, "File %s is opened\n", Input_File.name);
	Display_Exec_Msg (User_Msg);

	printf ("exection in file -%s<=", Input_File.buffer);
	if ((!Draw_Flag) && (Animate_Flag))
	{
		printf ("exection in file -%s<=", Input_File.buffer);
		exec_draw (drawing_a, dummyptr1, dummyptr2);

	}

	if (Animate_Flag)
	{
		Inverse_Tree_Node (Hoare_Root_Dummy->level_point);
	}
	Root_Stack = Stack_Allocation ();	/* root dummy */
	Current_Stack = Stack_Allocation ();	/* module title */

/* thread connection */
	Root_Stack->forward_stack_ptr = Current_Stack;
	Current_Stack->backward_stack_ptr = Root_Stack;

	Current_Stack->template_node_ptr = Hoare_Root_Dummy->level_point;
	Hoare_Root_Dummy->level_point->ttop_of_stack = Current_Stack;

	if (Animate_Flag)
	{
		Inverse_Tree_Node (Hoare_Root_Dummy->level_point);
	}

	printf ("\n\n  ##### THE BEGINNING SUB MODULE #####\n\n\n");
	sprintf (User_Msg, "Begin to execute specification.\n");
	Display_Exec_Msg (User_Msg);

	printf ("Begin to execute specification.\n");
	printf ("Module Title %s\n", Hoare_Root_Dummy->level_point->name);
	printf ("Begin to execute specification.\n");
	sprintf (User_Msg, "\n\n  ##### THE BEGINNING SUB MODULE #####\n\n\n");
	fputs (User_Msg, Log_File.f_ptr);

	printf ("Module Title %s\n", Hoare_Root_Dummy->level_point->name);
	sprintf (User_Msg, "The name of the Descartes specification is [%s].\n\n",
		 DESC_New_File_Name);
	fputs (User_Msg, Log_File.f_ptr);

	printf ("Module Title %s\n", Hoare_Root_Dummy->level_point->name);
/* Begin to write the tracing messages on the window and disk file  */
	sprintf (User_Msg, "Module Title %s\n", Hoare_Root_Dummy->level_point->name);
	if (Trace_Flag)
	{
		Display_Exec_Msg (User_Msg);
	}
	if (Log_Flag)
	{
		fputs (User_Msg, Log_File.f_ptr);
	}

/* proceed the INPUT argument */
	Root_Node = Hoare_Root_Dummy->level_point->level_point;
	while (Root_Node && isupper (*Root_Node->name))
	{
		Activity = FIRST;
		printf ("GO TO ANALYSIS \n");
		execution_proc (Root_Node);
		if (Animate_Flag)
			Inverse_Tree_Node (Hoare_Root_Dummy->level_point);
		Root_Node = Root_Node->front;
	}

	printf ("\n\n  ##### THE BEGINNING SUB MODULE \n\n\n");

/* there are something wrong somewhere */
/* the matching of input is not complete yet */
	if (Tree_Type == ANALYSIS)
	{
		if (Input_File.c_ptr < (int) strlen (Input_File.buffer))
		{
			sprintf (User_Msg, "==> It doesnot reach the end of the file; check "
				 "either specification or input.\n");
			Display_Exec_Msg (User_Msg);
			sprintf (User_Msg, "Failed %d bytes from the beginning of the input stream.\n", (int) Input_File.c_ptr);
			Display_Exec_Msg (User_Msg);
			sprintf (User_Msg, "Contents of the rest of the input buffer:\n\t\"");
			Display_Exec_Msg (User_Msg);
			sprintf (User_Msg, "%s\"\n", (Input_File.buffer + Input_File.c_ptr));
			Display_Exec_Msg (User_Msg);
			if (Log_Flag)
			{
				fputs (User_Msg, Log_File.f_ptr);
				fflush (Log_File.f_ptr);
			}
			Activity = FAIL;
		}
	}

	if (Activity == SUCCEED)
	{
		sprintf (User_Msg, "The analysis procedure was successful.\n");
		Display_Exec_Msg (User_Msg);
		if (Log_Flag)
		{
			fputs (User_Msg, Log_File.f_ptr);
		}

		sprintf (User_Msg, "Continue synthesis procedure.\n");
		Display_Exec_Msg (User_Msg);
		if (Log_Flag)
		{
			fputs (User_Msg, Log_File.f_ptr);
		}

	/* proceed "return" for output segment */
		while (Root_Node)
		{
			Activity = FIRST;
			execution_proc (Root_Node);
			if (Animate_Flag)
				Inverse_Tree_Node (Hoare_Root_Dummy->level_point);
			Root_Node = Root_Node->front;
		}

		if (Activity == SUCCEED)
		{
			print_successful_execution_info (__LINE__);
		}
		else
		{
			sprintf (User_Msg, "The synthesis procedure failed.\n");
			Display_Exec_Msg (User_Msg);
			if (Log_Flag)
			{
				fputs (User_Msg, Log_File.f_ptr);
			}
			goto NO_OUTPUT;
		}
	}			/* if  */
	else
	{

		sprintf (User_Msg, "The analysis procedure failed.\n");
		Display_Exec_Msg (User_Msg);
		if (Log_Flag)
		{
			fputs (User_Msg, Log_File.f_ptr);
		}
NO_OUTPUT:
		sprintf (User_Msg, "No output is produced at this execution.\n");
		Display_Exec_Msg (User_Msg);
		if (Log_Flag)
		{
			fputs (User_Msg, Log_File.f_ptr);
		}
	}			/* else */

/* after execution, free an input file name & all stack elements */
	Display_Exec_Msg (User_Msg);

/* it is necessary to free stack but ........  */
	Stack_Free ();

	sprintf (User_Msg, "\n\n  #####   THE  END OF SUB MODULE  #####\n");
	if (Log_Flag)
	{
		fputs (User_Msg, Log_File.f_ptr);
	}
}


static void     Draw_Tree_Node (struct Template_Node * cur_node)
{
	int             len;

	if (cur_node->back)	/* has a prev. sibling */
	{
		printf ("(back)node->%s\n", cur_node->name);

	/* Vertical  Line  */
		clientXDrawLine (FALSE, cur_node->col - 18, cur_node->back->row + 9, cur_node->col - 18, cur_node->row + 9);
	/* Horizontal  Line  */
		clientXDrawLine (FALSE, cur_node->col - 18, cur_node->row + 9, cur_node->col, cur_node->row + 9);
	}
	else if (cur_node->level_no)
	/* this means it is a immediate son except module title */
	{
		printf ("(level_no)node->%s\n", cur_node->name);

	/* Horizontal  Line  */
		clientXDrawLine (FALSE, cur_node->col - 36, cur_node->row - 15, cur_node->col - 18, cur_node->row - 15);
	/* Vertical  Line  */
		clientXDrawLine (FALSE, cur_node->col - 18, cur_node->row - 15, cur_node->col - 18, cur_node->row + 9);
	/* Horizontal  Line  */
		clientXDrawLine (FALSE, cur_node->col - 18, cur_node->row + 9, cur_node->col, cur_node->row + 9);
	}

	x_end = cur_node->col + 2 + (8 * (strlen (cur_node->name))) + 2;
	y_end = cur_node->row + 18;
	c_start_x = cur_node->col + 2;
	c_start_y = cur_node->row + 12;

	clientXDrawLine (FALSE, cur_node->col, cur_node->row,
			 cur_node->col, y_end);
	clientXDrawLine (FALSE, cur_node->col, y_end, x_end, y_end);
	clientXDrawLine (FALSE, x_end, y_end, x_end, cur_node->row);
	clientXDrawLine (FALSE, x_end, cur_node->row,
			 cur_node->col, cur_node->row);
	len = strlen (cur_node->name);
	clientXDrawString (c_start_x, c_start_y, cur_node->name, len);
}

static void     Draw_Hoare_Tree (struct Template_Node * cur_node)
{
/* Terminal  Node  */
	if (cur_node->level_point == NULL && cur_node->front == NULL)
	{
		Draw_Tree_Node (cur_node);
		return;
	}

	if (cur_node != NULL)
	{
		Draw_Tree_Node (cur_node);
		if (cur_node->level_point != NULL)
			Draw_Hoare_Tree (cur_node->level_point);
	}

	if (cur_node->front != NULL)
	{
		Draw_Hoare_Tree (cur_node->front);
	}
	return;
}


/*******************************************************************************
 * FUNCTION:	EXEC_DRAW
 * 	Show hoare tree with the visualization
 *      Invoked as a Callback function from an XmPushButton widget in wid1.c
 *      This function does not use the parameters passed to it from the
 *      XmPushButton widget.
 ******************************************************************************/

void            exec_draw (Widget dummywidget, void *dummyptr1, XmPushButtonCallbackStruct * dummyptr2)
{
	struct Template_Node *Root_Dummy;

	printf ("*---- In exec_draw() Draw_Flag = %d; Hoare_Root_Dummy->level_point = %d ----*\n",
		Draw_Flag, Hoare_Root_Dummy->level_point);
	fflush (stdout);

/*
 * Each char has 8 pixels wide and 14 pixels high There is no need for
 * drawing Root Dummy.  Draw the actual entire Hoare Tree.
 */
	if (!Draw_Flag && (Hoare_Root_Dummy->level_point))
	{
		sprintf (User_Msg, "Drawing the Hoare tree structure in block diagram.\n");
		Display_Exec_Msg (User_Msg);
		printf ("Drawing the Hoare tree structure in block diagram.");
		Draw_Hoare_Tree (Hoare_Root_Dummy->level_point);
		Draw_Flag = YES;
	}

	Root_Dummy = Hoare_Root_Dummy->front;
	while (Root_Dummy)
	{
		if (Draw_Flag && (Hoare_Root_Dummy->front->level_point))
		{
			sprintf (User_Msg, "Drawing the Hoare tree structure in block diagram.\n");
			Display_Exec_Msg (User_Msg);
			Draw_Hoare_Tree (Root_Dummy->level_point);
			Root_Dummy = Root_Dummy->front;
			Draw_Flag = YES;
		}
	}
	clientXCopyArea (0, 0, width, height, 0, 0);
}

static void     Canvas_Scrolling (Widget drawing_a, int x1, int y1, int x2, int y2)
{
	short           tmp;

/* check for node edge under BACKWARD SITUATION */
	if (x1 > x2)
	{
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}

	if (y1 > y2)
	{
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	if (x1 <= *C_Left)
	{
		*C_Left = x1 - 2;
		*C_Right = *C_Left + (int) win_width;
		clientXCopyArea (*C_Left, *C_Top, width, height, 0, 0);
	}

	if (y1 <= *C_Top)
	{
		*C_Top = y1 - 2;
		*C_Bottom = *C_Top + (int) win_height;
		clientXCopyArea (*C_Left, *C_Top, width, height, 0, 0);
	}

	if (x2 >= *C_Right)
	{
		*C_Right = x2 + 2;
		*C_Left = *C_Right - (int) win_width;
		clientXCopyArea (*C_Left, *C_Top, width, height, 0, 0);
	}

	if (y2 >= *C_Bottom)
	{
		*C_Bottom = y2 + 2;
		*C_Top = *C_Bottom - (int) win_height;
		clientXCopyArea (*C_Left, *C_Top, width, height, 0, 0);

	/*
	 * MALCOLM MALCOLM NOTE The following two lines look funny; why
	 * perform the computations again?
	 */
		*C_Bottom = y2 + 2;
		*C_Top = *C_Bottom - (int) win_height;
	}
}

/*******************************************************************************
 * FUNCTION:	DELAY_CHECKING  (really more of a delay insertion.)
 *
 * PURPOSE:	Slow down animation when the user requests it.
 *
 * NOTE:	The user sets Delay_Time with the "Execution Speed" slider
 *		widget on the main window toolbar.
 *
 * ALGORITHM:	Waste a few milliseconds by calling a slow system function.
 *		This slows down execution without introducing a "busywait".
 *		This is roughly equivalent to the slowdown introduced by the
 *		"Dynamic Feedback Indicator" slider widget in the Lih-shiun Lee
 *		implementation of this language processor.
 ******************************************************************************/

static void     Delay_Checking (void)
{
	int             i;
	volatile char  *waste_time_buf;/* "volatile" keyword is used to keep a smart optimizer from deleting cals to calloc() and
				        * free(). */

	if (Delay_Time)		/* Nonzero delay time. */
	{
		for (i = 0; i < Delay_Time; i++)
		{
			waste_time_buf = (volatile char *) calloc (1024, sizeof (char));
			free ((char *) waste_time_buf);
		}
		clientXCopyArea (*C_Left, *C_Top, width, height, 0, 0);
	}
}

static void     Animate_Inversing (int x_1, int y_1, int x_2, int y_2)
{
	Canvas_Scrolling (drawing_a, x_1, y_1, x_2, y_2);
	clientXDrawLine (TRUE, x_1, y_1, x_2, y_2);
	clientXCopyArea (*C_Left, *C_Top, width, height, 0, 0);

	clientXDrawLine (TRUE, x_1, y_1, x_2, y_2);
	clientXCopyArea (*C_Left, *C_Top, width, height, 0, 0);
}

void            Inverse_Node_Edge (struct Template_Node * cur_node, int mode)
{
	short           x1,
	                x2,
	                x3,
	                y1,
	                y2;

	if (mode == FORWARD)
	{
		x1 = cur_node->col - 36;
		x2 = cur_node->col - 18;
		x3 = cur_node->col;
		y1 = cur_node->ancestor->row + 10;
		y2 = cur_node->row + 9;

		for (g_count = x1; g_count < (x2 - 2); g_count += 5)
		{
			Animate_Inversing (g_count, y1, g_count + 5, y1);
		}
		for (g_count = y1; g_count < (y2 - 2); g_count += 5)
		{
			Animate_Inversing (x2, g_count, x2, g_count + 5);
		}
		for (g_count = x2; g_count < (x3 - 2); g_count += 5)
		{
			Animate_Inversing (g_count, y2, g_count + 5, y2);
		}
	}
	else
	{
		x1 = cur_node->col;
		x2 = cur_node->col - 18;
		x3 = cur_node->col - 36;
		y1 = cur_node->row + 9;
		y2 = cur_node->ancestor->row + 10;
		for (g_count = x1; g_count > (x2 + 2); g_count -= 5)
		{
			Animate_Inversing (g_count, y1, g_count - 5, y1);
		}
		for (g_count = y1; g_count > (y2 + 2); g_count -= 5)
		{
			Animate_Inversing (x2, g_count, x2, g_count - 5);
		}
		for (g_count = x2; g_count > (x3 + 2); g_count -= 5)
		{
			Animate_Inversing (g_count, y2, g_count - 5, y2);
		}
	}
/* printf("2process id in canvas %d\n",getpid()); */
}


void            Inverse_Tree_Node (struct Template_Node * cur_node)
{
	sem_wait (semid_d);

	x_end = cur_node->col + 2 + (8 * (strlen (cur_node->name))) + 2;
	y_end = cur_node->row + 18;

	Canvas_Scrolling (drawing_a, cur_node->col, cur_node->row, x_end, y_end);

	for (g_count = cur_node->col + 1; g_count < x_end; g_count++)
	{
		clientXDrawLine (TRUE, g_count, cur_node->row + 1, g_count, y_end - 1);
		Delay_Checking ();
	}
	clientXCopyArea (*C_Left, *C_Top, width, height, 0, 0);

	sem_signal (semid_d);
}

/*******************************************************************************
 * FUNCTION	EXEC_PRINT_LOG
 *	Not used in Malcolm Franklins version of the language processor.  I
 *	left in in the code in case someone else wanted it in the future.
 ******************************************************************************/
void            exec_print_log (void)
{
#define	QUEUE_CMD  "lzpr -h ./%s -g %s"/* ASU custom-made printing utility */

	if (!Check_File (Log_File.name))
	{
		Continue_Msg (LOG_FILE_NOT_EXISTED);
		return;
	}

	sprintf (User_Msg, "queue a file to a local printer; please wait ..\n");
	Display_Exec_Msg (User_Msg);
	sprintf (User_Msg, QUEUE_CMD, Log_File.name, Log_File.name);
	Display_Exec_Msg (User_Msg);
	system (User_Msg);
	sprintf (User_Msg, "Please check the printout at your local printer.\n");
	Display_Exec_Msg (User_Msg);
}

/*******************************************************************************
 * FUNCTION:	EXEC_PROC
 *
 *	Spawns the execution subprocess.  The parent process acts as a
 *	server to process requests for updates to the user interface, and
 *	for setting/retrieving values for shared variables.  The execution
 *	subprocess spawns its own children, in order to implement the
 *	"PARALLEL" real time extension to Descartes.
 *
 *      Invoked as a Callback function from an XmPushButton widget in wid1.c
 *      This function does not use the parameters passed to it from the
 *      XmPushButton widget.
 ******************************************************************************/
void            exec_proc (Widget dummywidget, void *dummyptr1, XmPushButtonCallbackStruct * dummyptr2)
{
	pid_t           pid;
	char            parent_pidstr[INTLEN];	/* String representation of the parent process ID. */


	sprintf (parent_pidstr, "%d", (int) getpid ());
	parent2child = init_parent2child_fifo (parent_pidstr);	/* Create the FIFO object in the file system. */

	if (!strlen (DESC_New_File_Name))
	{
		Continue_Msg (FILE_NAME_NEEDED);
		return;
	}
	if (!Check_File (DESC_New_File_Name))
	{
		Continue_Msg (FILE_NOT_EXISTED);
		return;
	}

/* Incomplete Tree Building  */
	if (error_counter)
	{
		Continue_Msg (XERROR_EXISTED);
		return;
	}

	Draw_Flag = NO;
	Animate_Flag = YES;

	if ((pid = fork ()) == -1)
	{
		perror ("can not fork() in exec_proc()");
	}
	else if (pid == 0)
	{
		printf ("Child process forked() successfully.  Child will execute exec_run() now.\n");
		exec_run (parent2child);
		exit (0);
	}
	else
	{

	/*
	 * Parent process processes requests form child to draw and display
	 * messages.
	 */
		parse (parent2child);
	}
}
