#undef _POSIX_SOURCE		       /* parse() uses a SysV message queue to get requests from a child process. */
/*******************************************************************************
 * MODULE:	WID1.C
 *
 * AUTHOR:	Believed to be Lih-Shiun Timothy Lee, of Arizona State
 *		University.
 *******************************************************************************
 * $Date: 1994/06/11 17:46:13 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/wid1.c,v $
 *
 **-M**************************************************************************/

#if 0
/******************************************************************************
 *
$Log: wid1.c,v $
 * Revision 1.44  1994/06/11  17:46:13  franklin
 * Remove variables and functions that are no longer referenced.
 *
 * Revision 1.43  1994/06/11  16:19:11  franklin
 * Move the control of global "Trace_Flag" to main.c.
 *
 * Revision 1.42  1994/06/11  05:38:19  franklin
 * Move the scale widget that controlls execution speed from this
 * file to main.c.  Delete the "Animation" radio buttons.  Their
 * functionality has been moved to main.c as well.
 *
 * Revision 1.41  1994/06/09  23:08:37  franklin
 * Add dismiss_display_standalone_text(); this displays a stand-alone shell
 * widget that can display any ascii text.  Right now we use it to view
 * ASCII files.
 *
 * Revision 1.40  1994/06/09  01:32:20  franklin
 * 1. Delete functions and global variables that are no longer used (most
 *    the deleted code has been replaced with a new user interface in main.c).
 * 2. Update the parameter list of Build_Proc().  It is no longer a
 *    callback function.
 *
 * Revision 1.39  1994/06/08  18:57:18  franklin
 * Move text from the message window to the history window
 *
 * Revision 1.38  1994/06/08  03:36:37  franklin
 * 1. Drive file_cb and Build_Proc callbacks from main.c
 *    instead of the old user interface.
 * 2. Display new messages in message_text widget, and move
 *    the old message to msghistory_text widget.
 *
 * Revision 1.37  1994/06/08  01:51:43  franklin
 * Display the hoare tree file when the user selects "Display Tree..." from
 * the "view" pulldown menu in main.c.  It used to be done in this file.
 *
 * Revision 1.36  1994/06/07  21:51:40  franklin
 * 1. Remove all references to the global text widget Rd_text_w
 * 2. Have read_file() put ASCII files into its own shell
 *    widget, instead of passing it an existing text widget
 *    to write to.
 * 3. Delete the code to pull up the old "ok to quit" dialog bos
 *    for the old user interface.
 *
 * Revision 1.34  1994/06/01  22:32:46  franklin
 * The user interface looks much better when the Motif system picks the
 * colors/shades on both Color and Black & White X terminals.  Delete the
 * custom widget pixmaps.
 *
 * Revision 1.33  1994/06/01  22:14:36  franklin
 * Try using the default colors instead of using custom XmNbackgroundPixmaps
 * for widgets.
 *
 * Revision 1.32  1994/05/25  22:35:46  franklin
 * command_line.c no longer requires you to call initialize_custom_resources()
 * to set up its internal data structures.
 *
 * Revision 1.31  1994/05/25  02:52:29  franklin
 * Fetch the custom applications resources defined in command_line.c
 *
 * Revision 1.30  1994/05/24  18:39:34  franklin
 * When a function is passed a global variable as a parameter
 * , reference the global variable via the parameter.  Maybe
 * we can "un-global" some stuff.
 *
 * Revision 1.29  1994/05/24  01:26:30  franklin
 * Undefile _POSIX_SOURCE for this file (for now) because parse()
 * uses a SysV message queue to get requests from a child process.
 *
 * Revision 1.28  1994/05/21  21:01:19  franklin
 * Do not print the message header when you display text to a text widget.
 * Added some comments.
 *
 * Revision 1.27  1994/05/20  21:49:12  franklin
 * Get rid of stupid debug variables.
 *
 * Revision 1.26  1994/05/20  21:42:50  franklin
 * Clean up the parse() function:
 * 1. Replace "if..then..else" ladder with switch() statement.
 * 2. Replace while(1){...break;} with do{...}while();
 * 3. Remove useless variable "i".
 *
 * Revision 1.25  1994/05/20  20:16:30  franklin
 * If you fail to receive a message (mesg_recv()), then set the message buffer
 * to be a zero length string.
 *
 * Revision 1.24  1994/05/20  17:25:04  franklin
 * 1. Copy the name of the program (argv[0]) into a new storage location
 *    because XtVaAppInitialize will actually change the argv array, and
 *    may even move it.  Saving a pointer to it is not sufficient.
 * 2. Pass text to the dialog box that verifies that you want to quit
 *    the application entirely (quit_msg()).  Use the default button text
 *    of "Ok" and "Cancel".  Change the title (XmNtitle) from
 *    "Real-time Descartes" to "Descartes Language Processor".  This
 *    language processor does not support the run-time additions.
 *
 * Revision 1.23  1994/05/16  21:17:42  franklin
 * Use the new version of sem_create(), which needs no parameters, and performs
 * its own exception handling.
 *
 * Revision 1.22  1994/05/13  13:50:56  franklin
 * Put brackets around "if" clause actions.
 *
 * Revision 1.21  1994/05/03  23:19:38  franklin
 * 1. Quit trying to allocat a gazillion-pixel pixmap for the drawing area!
 *    I reduced the dimensions drawing_a in create_exec() from
 *    3000x5000 (x Depth of frame buffer!) to 1280x2000 FOR NOW.
 *    Later, I'll compute the required width & height from the width of the
 *    widest module tree, and the combined height of all module trees in
 *    the specification.
 * 2. Change the input file selection widget, to default to showing only files
 *    whose names end in ".des".
 *
 * Revision 1.20  1994/05/03  17:40:50  franklin
 * 1. Removed static function redraw1(); it was never used.
 * 2. Initialized "ptr" in extract_filename() in case loop iterates 0 times.
 * 3. Deleted or commented out unused variables.
 * 4. Deleted a bunch of seemingly useless commented out code.
 *
 * Revision 1.19  1994/05/03  16:42:09  franklin
 * We have to pass the -Xa (K&R C compatibility switch) to clcc
 * in order to compile the system header files.  But when we
 * do this, CenterLines preprocessor #defines __STDC__ to 0;
 * when this happens, we dont see the vararg prototypes for
 * X functions -- and get warning messages for calling them with
 * different numbers of arguments.  Workaround:  When compiling
 * with clcc, #define __STDC__ to 1 AFTER #including the
 * system file.s.  I rearranged the #includes in the following
 * order:
 * 1. C language includes
 * 2. Operating system includes
 * 3. X includes
 * 4. User written includes.
 *
 * Revision 1.18  1994/05/02  05:02:05  franklin
 * Use semops.h instead of sem.c
 *
 * Revision 1.17  1994/04/12  13:06:15  franklin
 * Clarify some diagnostic messages.
 *
 * Revision 1.16  1994/04/12  10:33:54  franklin
 * Shut up Purify diagnostic about uninitialized memory read.
 *
 * Revision 1.15  1994/04/11  21:41:03  franklin
 * Used mixed-case in button widget labels.
 *
 * Revision 1.14  1994/04/11  19:52:14  franklin
 * Re-run through SunOS 4.1.3 "indent" utility.
 *
 * Revision 1.13  1994/04/11  16:11:30  franklin
 * Converted wid1.c to ANSI/ISO Standard C.
 *
 * Revision 1.11  1994/04/10  23:06:13  franklin
 * Use share_rtn.h and exec_rtn1.h for declarations of functions and globals
 * used from those modules.  Move declarations for this modules external
 * globals in to wid1.h.
 *
 * Revision 1.10  1994/04/09  23:49:02  franklin
 * Get the declaration of struct pro_table, pcb, and p_cnt from
 * analysis1.h.
 *
 * Revision 1.9  1994/04/09  22:33:45  franklin
 * wid1.h requires the definition of type Mesg in mesg.h.
 *
 * Revision 1.8  1994/04/09  20:29:23  franklin
 * Read the declaration of Print_Hoare_Tree() from build_rtn.h
 *
 * Revision 1.7  1994/04/09  19:39:20  franklin
 * Remove declaration of Read_Spec_And_Build_Tree().  It is no-longer called
 * from this module.
 *
 * Revision 1.6  1994/04/08  04:58:33  franklin
 * Read wid1.h to ensure declarations are consistent with definitions.
 *
 * Revision 1.5  1994/04/08  04:46:05  franklin
 * Syncronize function return value with wid1.h
 *
 * Revision 1.4  1994/04/08  04:20:32  franklin
 * #include build_rtn.h for the declarations of globals in build_rtn.h
 *
 * Revision 1.3  1994/03/30  05:13:36  franklin
 * Deleted function "create_file()"; it was never called from anywhere.
 *
 * Revision 1.2  1994/03/30  04:53:05  franklin
 * Run through SunOS "indent" program to get consistent indentation sytle.
 * Add a module header w/ RCS tokens.  NO OTHER changes were made
 * in this file version.
 *
 ******************************************************************************/
#endif

static char    *rcsid = "@(#) $Id: wid1.c,v 1.44 1994/06/11 17:46:13 franklin Exp $";

/* Udpate Nov 30 1992   */
/* pp.   346      */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>		       /* NON POSIX.1 */
#include <sys/msg.h>		       /* NON POSIX.1 */
#include <sys/stat.h>		       /* This is allowed under POSIX.1-1990 */

#ifdef __CLCC__

#ifdef __STDC__
#undef __STDC__
#endif

#define __STDC__ 1
#endif

#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Xlib.h>
#include  <Xm/MainW.h>
#include <Xm/DrawingA.h>
#include <Xm/Label.h>
#include <Xm/LabelG.h>
#include <Xm/MessageB.h>
#include <Xm/FileSB.h>
#include <Xm/PushBG.h>
#include <Xm/ScrolledW.h>
#include <Xm/ScrollBar.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <Xm/PushBG.h>
#include <Xm/CascadeBG.h>
#include <Xm/DialogS.h>
#include <Xm/PanedW.h>
#include <Xm/Text.h>
#include <Xm/ToggleBG.h>
#include <Xm/Frame.h>

#include <Xm/MessageB.h>
#include <Xm/Scale.h>
#include <Xm/DialogS.h>

#include "desc_struct.h"
#include "build_rtn.h"		       /* Build_Proc(), Show_Hoare_Tree() and Print_Hoare_Tree() callback functions; Also the
				        * global flag File_Modified */
#include "share_rtn.h"		       /* Get_File_Stat() */

#define MAX_PROC  4

#include "semops.h"
#include "mesg.h"
#include "analysis1.h"
#include "exec_rtn1.h"		       /* Trace_Flag, Animate_Flag Exec_Draw(), Exec_Proc() */
#include "some_utils.h"		       /* util_abort() */
#include "command_line.h"	       /* non-Xwindow command line switches. */
#include "main.h"		       /* Globals toplevel and app */
#include "wid1.h"		       /* Ensure consistency with the .h file for this .c file. */


/*******************************************************************************
 * GLOBALS
 ******************************************************************************/
Widget          message_text;	       /* Message text widget at the bottom of the MainWindow widget. */
Widget          msghistory_text;       /* Scrolling text window containing old messages. */

GC              gc;
GC              inv_gc;		       /* for inverse */
int             Delay_Time;	       /* Used by Delay_Checking() in exec_rtn.c  */

static GC       rev_gc;

Dimension       width;
Dimension       height;

Widget          drawing_a;

typedef struct
{
	XFontStruct    *font;
	int             fontheight;
	int             fontwidth;
}               text_data, *text_data_ptr;

static Widget   vsb;		       /* scrollbar widget   */
static Widget   hsb;		       /* scrollbar widget   */

static char    *base_buttons[] = {"Read Spec & Build Tree", "Execute Spec", "Help",
"Quit", "Test Driver", "Visual Editor"};

Widget          rd_spec_text_w;
static Widget   Show_text_w;
Pixmap          Current_pix = 0;       /* Drawable to display the animation. */
Widget          ex_button[5];
Dimension       win_width;
Dimension       win_height;

Mesg            mesg_d;
int             msgid;

/*******************************************************************************
 * FUNCTION:	CALL_XTUNMANAGECHILD_CB
 ******************************************************************************/

static void     call_XtUnmanageChild_cb (Widget wid, void *dummyptr1, XmPushButtonCallbackStruct * dummyptr2)
{
	XtUnmanageChild (wid);
}

/*******************************************************************************
 * FUNCTION:	EXTRACT_FILENAME
 ******************************************************************************/

static void     extract_filename (char *des_name, char *scr_name)
{
	int             i,
	                ptr;

	ptr = 0;
	for (i = 0; i <= strlen (scr_name); i++)
	{
		if (!strncmp (scr_name + i, "/", 1))
		{
			ptr = i;
		}
	}
	strcpy (des_name, scr_name + ptr + 1);
}

/*******************************************************************************
 * FUNCTION:	LOAD_PIXMAP
 ******************************************************************************/

/* pp  178    */
static void     load_pixmap (Widget dialog, void *dummyptr, XmFileSelectionBoxCallbackStruct * cbs)
{
	char           *filename = NULL;

	if (cbs)
	{
		if (!XmStringGetLtoR (cbs->value, XmSTRING_DEFAULT_CHARSET, &filename))
			return;
		XtUnmanageChild (dialog);
		File_Modified = YES;
		if (!*filename)
		{
			File_Modified = NO;
			XtFree (filename);
			return;
		}
		else if (!strlen (DESC_New_File_Name))
		{
			extract_filename (DESC_New_File_Name, filename);
			File_Modified = NO;
		}
		else if (Build_Flag_4_New_File)
		{
			if (strcmp (filename, DESC_New_File_Name))
			{
				strcpy (DESC_Old_File_Name, DESC_New_File_Name);
				extract_filename (DESC_New_File_Name, filename);
			}
			Build_Flag_4_New_File = NOT_YET;
			Build_Flag_4_Old_File = READY;
			File_Modified = NO;
		}
		else
		{
			strcpy (DESC_Old_File_Name, DESC_New_File_Name);
			extract_filename (DESC_New_File_Name, filename);
		}
	/* Load the input file into internal data structures. */
		Build_Proc ();

		XtFree (filename);
	}
}

/*******************************************************************************
 * FUNCTION:	FILE_CB
 *	Select a Descartes specification to process, and read it into internal
 *	data structures.
 ******************************************************************************/

void            file_cb (Widget dummywidget, void *dummyptr1, XmPushButtonCallbackStruct * dummyptr2)
{
	static Widget   dialog;
	Widget          button2deactivate;
	XmString        infile_suffix;
	Arg             wargs[10];
	Cardinal        n;

	if (!dialog)
	{
	/* Expects Descartes specification files to end in ".des". */
		infile_suffix = XmStringCreateLtoR ("*.des", XmSTRING_DEFAULT_CHARSET);
		n = 0;
		XtSetArg (wargs[n], XmNpattern, infile_suffix);
		n++;
		dialog = XmCreateFileSelectionDialog (toplevel, "file_sel", wargs, n);

		button2deactivate = XmFileSelectionBoxGetChild (dialog, XmDIALOG_HELP_BUTTON);
		XtUnmanageChild (button2deactivate);

		XtAddCallback (dialog, XmNokCallback, (XtCallbackProc) load_pixmap, NULL);
		XtAddCallback (dialog, XmNcancelCallback, (XtCallbackProc) call_XtUnmanageChild_cb, NULL);
		XmStringFree (infile_suffix);
	}
	XtManageChild (dialog);
	XtPopup (XtParent (dialog), XtGrabNone);
}

/*******************************************************************************
 * FUNCTION:	RESPONSE3
 ******************************************************************************/

static void     response3 (Widget dummywidget, Widget shell, XmPushButtonCallbackStruct * dummyptr)
{
/* pp.  212  */
/* XtDestroyWidget(shell); */
	XSetFunction (XtDisplay (drawing_a), rev_gc, GXclear);
	XCopyArea (XtDisplay (drawing_a), Current_pix, Current_pix, rev_gc,
		   0, 0, width, height, 0, 0);

	XClearArea (XtDisplay (drawing_a), XtWindow (drawing_a), 0, 0, width, height, TRUE);
	XtPopdown (shell);
	XmTextSetString (Show_text_w, NULL);
}

/*******************************************************************************
 * FUNCTION:	DRAW
 ******************************************************************************/

static void     draw (Widget widget, XButtonEvent * event, String * args, int *num_args)
{
	static Position x,
	                y;

	if (*num_args != 1)
		XtError ("Wrong number of args !");
	if (strcmp (args[0], "down"))
	{
		XDrawLine (event->display, event->window, gc, x, y, event->x, event->y);
		XDrawLine (event->display, Current_pix, gc, x, y, event->x, event->y);
	}
	x = event->x;
	y = event->y;

}

/*******************************************************************************
 * FUNCTION:	REDRAW
 ******************************************************************************/

static void     redraw (Widget drawing_a, void *dummyptr, XmDrawingAreaCallbackStruct * cbs)
{
	XCopyArea (cbs->event->xexpose.display, Current_pix, cbs->window, gc,
		   0, 0, width, height, 0, 0);
}

/*******************************************************************************
 * FUNCTION:	CREATE_EXEC
 *      Invoked as a Callback function from an XmPushButton widget in wid1.c
 *      This function does not use the parameters passed to it from the
 *      XmPushButton widget.
 ******************************************************************************/
void            create_drawing_area (Widget parent)
{
}
static char    *exec_buttons[] = {"Run", "Draw", "Print Log", "Done", "Help"};
void            create_exec (Widget dummywidget, void *dummyptr1, XmPushButtonCallbackStruct * dummyptr2)
{
	Widget          main_w,
	                pane;
	Widget          rowcol_b;
	static Widget   exec_dialog;
	XGCValues       gcv;
	XGCValues       gcv1;
	XtActionsRec    actions;
	Arg             wargs[10];
	Cardinal        n;
	int             value = 0;
	int             max = 0,
	                ssize = 0;
	int             i;
	static int      yes_constant = YES;	/* Pass the address of these constants to the t_toggled() callback function. */
	static int      no_constant = NO;

	String          translations =
	"<Btn1Down>: draw(down) ManagerGadgetArm()  \n\
   <Btn1Up>: draw(up) ManagerGadgetActivate()  \n\
   <Btn1Motion>: draw(motion) ManagerGadgetButtonMotion()";


	if (exec_dialog)
	{
		XtPopup (exec_dialog, XtGrabNone);
		return;
	}

	exec_dialog = XtVaCreatePopupShell ("dialog",
					    xmDialogShellWidgetClass, toplevel, XmNtitle, "Execution Viewport",
					    NULL);


	pane = XtVaCreateWidget ("pane", xmPanedWindowWidgetClass, exec_dialog,
/* pp.   208   */
				 XmNsashWidth, 1,
				 XmNsashHeight, 1,
				 XmNspacing, 2,
				 NULL);


/* pp.   268   */
	rowcol_b = XtVaCreateManagedWidget ("rowcol", xmRowColumnWidgetClass, pane,
					    XmNpacking, XmPACK_COLUMN,
					    XmNentryAlignment, XmALIGNMENT_CENTER,
					    XmNorientation, XmHORIZONTAL, NULL);
	for (i = 0; i < XtNumber (exec_buttons); i++)
		ex_button[i] = XtVaCreateManagedWidget (exec_buttons[i], xmPushButtonWidgetClass, rowcol_b, NULL);

	XtAddCallback (ex_button[0], XmNactivateCallback, (XtCallbackProc) Exec_Proc, NULL);
	XtAddCallback (ex_button[1], XmNactivateCallback, (XtCallbackProc) Exec_Draw, NULL);

	XtAddCallback (ex_button[3], XmNactivateCallback, (XtCallbackProc) response3, exec_dialog);


/* pp.  411   */
	main_w = XtVaCreateManagedWidget ("main", xmMainWindowWidgetClass, pane,
					  XmNscrollBarDisplayPolicy, XmAS_NEEDED,
					  XmNscrollingPolicy, XmAUTOMATIC, XmNheight, 500, NULL);

/* pp.  308   */
/* text  window   */
	n = 0;
	XtSetArg (wargs[n], XmNrows, 5);
	n++;
	XtSetArg (wargs[n], XmNcolumns, 80);
	n++;
	XtSetArg (wargs[n], XmNeditMode, XmMULTI_LINE_EDIT);
	n++;
	XtSetArg (wargs[n], XmNwordWrap, True);
	n++;
	XtSetArg (wargs[n], XmNblinkRate, 0);
	n++;
	XtSetArg (wargs[n], XmNautoShowCursorPosition, True);
	n++;

	Show_text_w = XmCreateScrolledText (pane, "text_w", wargs, n);
	XtManageChild (Show_text_w);

	XtManageChild (pane);
	XtPopup (exec_dialog, XtGrabNone);

/* Handle   scrollbar     */
	XtVaGetValues (main_w, XmNverticalScrollBar, &vsb, XmNvalue, &value, NULL);
	XtVaGetValues (vsb, XmNmaximum, &max, XmNvalue, &value, XmNsliderSize, &ssize, NULL);

	XtVaGetValues (main_w, XmNhorizontalScrollBar, &hsb, XmNvalue, &value, NULL);
	XtVaGetValues (hsb, XmNmaximum, &max, XmNvalue, &value, XmNsliderSize, &ssize, NULL);

	actions.string = "draw";
	actions.proc = (XtActionProc) draw;
	XtAppAddActions (app, &actions, 1);
	drawing_a = XtVaCreateManagedWidget ("drawing_a",
					     xmDrawingAreaWidgetClass, main_w,
					     XmNtranslations, XtParseTranslationTable (translations),
					     XmNwidth, 1280,
					     XmNheight, 2000,
					     XmNresizePolicy, XmNONE,
					     NULL);

	XtAddCallback (drawing_a, XmNexposeCallback, (XtCallbackProc) redraw, NULL);
	XtVaSetValues (drawing_a, XmNunitType, XmPIXELS, NULL);
	XtVaGetValues (drawing_a, XmNwidth, &width, XmNheight, &height, NULL);

	if (Current_pix)
		XFreePixmap (XtDisplay (drawing_a), Current_pix);
	Current_pix = XCreatePixmap (XtDisplay (drawing_a),
				     RootWindowOfScreen (XtScreen (drawing_a)), width, height,
				     DefaultDepthOfScreen (XtScreen (drawing_a)));

	gcv.foreground = WhitePixelOfScreen (XtScreen (drawing_a));

	gc = XCreateGC (XtDisplay (drawing_a), RootWindowOfScreen (XtScreen (drawing_a)),
			GCForeground, &gcv);
	rev_gc = XCreateGC (XtDisplay (drawing_a), RootWindowOfScreen (XtScreen (drawing_a)),
			    GCForeground, &gcv);

	XFillRectangle (XtDisplay (drawing_a), Current_pix, gc, 0, 0, width, height);

	XSetForeground (XtDisplay (drawing_a), gc,
			BlackPixelOfScreen (XtScreen (drawing_a)));

	gcv1.foreground = WhitePixelOfScreen (XtScreen (drawing_a));
	inv_gc = XCreateGC (XtDisplay (drawing_a), RootWindowOfScreen (XtScreen (drawing_a)),
			    GCForeground, &gcv1);

/* scrollbar   handling   */
	XtVaGetValues (drawing_a, XmNwidth, &width, XmNheight, &height, NULL);
	value = 200;

/* set  scroll bar values    */
	XtVaSetValues (vsb, XmNsliderSize, 100, XmNvalue, 200, NULL);
	XtVaSetValues (hsb, XmNsliderSize, 100, XmNvalue, 200, NULL);

	XtVaGetValues (vsb, XmNmaximum, &max, XmNvalue, &value, XmNsliderSize, &ssize, NULL);

	XtVaGetValues (XtParent (drawing_a), XmNwidth, &win_width, XmNheight, &win_height, NULL);
	XtVaGetValues (XtParent (drawing_a), XmNwidth, &win_width, XmNheight, &win_height, NULL);
}


/******************************************************************************
 * UTILITY FUNCTIONS CALLED BY OTHER MODULES:
 *	Display_Build_User_Msg()
 *	read_file()
 *	parse()
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION:	DISPLAY_BUILD_USER_MSG
 *	Used by build_hoare_tree.c, build_rtn.c, des2.y
 *	Display new messages in the message window at the bottom of the
 *	applications MainWindow widget, then move them to the msghistory_text
 *	when a new message comes along.
 ******************************************************************************/

void            Display_Build_User_Msg (Widget unused, char *msg)
{
	XmTextPosition  last_position;
	static growbuf_t *last_msg_gbuf = NULL;

	if (last_msg_gbuf == NULL)	/* First call to this function */
	{
		growbuf_init (&last_msg_gbuf);
	}
	else
	{
	/* Move text to history window. */
		last_position = XmTextGetLastPosition (msghistory_text);
		XmTextInsert (msghistory_text, last_position, growbuf_str (last_msg_gbuf));
		last_position = XmTextGetLastPosition (msghistory_text);
		XmTextSetCursorPosition (msghistory_text, last_position);
	}
	growbuf_strcpy (last_msg_gbuf, msg);	/* Overwirte the last message in the message text window. */
	last_position = XmTextGetLastPosition (message_text);
	XmTextReplace (message_text, 0, last_position, msg);
}


static void     dismiss_display_standalone_text_cb (Widget dummywidget, Widget file_dialog, XmPushButtonCallbackStruct * cbs)
{
	XtUnmanageChild (file_dialog);
	XtDestroyWidget (file_dialog);
}

void            display_standalone_text (char *title, char *text)
{
	Widget          display_text_shell;	/* TopLevelShell widget.  This will be a standalone window. */
	Widget          mainwindow;
	Widget          text_scrolled_window;
	Widget          menubar;
	String          pulldown_instname_pfx[] = {"file"};
	Widget          pulldown_menu[XtNumber (pulldown_instname_pfx)];
	Widget          pulldown_cbtn[XtNumber (pulldown_instname_pfx)];	/* XmCascadeButtons */
	String          file_pbutton_instname[] = {"exit_pbtn"};
	Widget          file_pbutton[XtNumber (file_pbutton_instname)];
	Arg             args[15];
	Cardinal        nargs;
	int             idx;	       /* Loop control */

	nargs = 0;
	XtSetArg (args[nargs], XmNtitle, title);
	nargs++;
	XtSetArg (args[nargs], XmNiconName, title);
	nargs++;
	display_text_shell = XtCreatePopupShell ("display_text_shell", topLevelShellWidgetClass, toplevel, args, nargs);

	mainwindow = XmCreateMainWindow (display_text_shell, "mainwindow", NULL, 0);
	XtManageChild (mainwindow);

	menubar = XmCreateMenuBar (mainwindow, "menubar", NULL, 0);
	XtManageChild (menubar);
	for (idx = 0; idx < XtNumber (pulldown_instname_pfx); idx++)
	{
	/* NOTE: You do NOT manage the pulldown menu widgets. */
		pulldown_menu[idx] = XmCreatePulldownMenu (menubar, convert_to_inst_name (pulldown_instname_pfx[idx], "_pmnu"),
							   NULL, 0);
		nargs = 0;
		XtSetArg (args[nargs], XmNsubMenuId, pulldown_menu[idx]);
		nargs++;
		pulldown_cbtn[idx] = XmCreateCascadeButtonGadget (menubar, convert_to_inst_name (pulldown_instname_pfx[idx],
												 "_cbtn"), args, nargs);
		XtManageChild (pulldown_cbtn[idx]);
	}
/* Install selections for the "File" pulldown menu. */
	for (idx = 0; idx < XtNumber (file_pbutton_instname); idx++)
	{
		file_pbutton[idx] = XmCreatePushButtonGadget (pulldown_menu[0], file_pbutton_instname[idx], NULL, 0);
		XtManageChild (file_pbutton[idx]);
	}

/* Install the text viewing window. */
	nargs = 0;
	XtSetArg (args[nargs], XmNeditMode, XmMULTI_LINE_EDIT);
	nargs++;
	XtSetArg (args[nargs], XmNscrollingPolicy, XmAUTOMATIC);
	nargs++;
	XtSetArg (args[nargs], XmNeditable, False);
	nargs++;
	text_scrolled_window = XmCreateScrolledText (mainwindow, "text_scrolled_window", args, nargs);
	XtManageChild (text_scrolled_window);

	XmTextSetString (text_scrolled_window, text);
	XtFree (text);

/*
 * Set the ScrolledWindow parent of the text_scrolled_window as the work
 * region widget, otherwise, the scroll bars wont work properly.
 */
	XmMainWindowSetAreas (mainwindow, menubar, NULL, NULL, NULL, XtParent (text_scrolled_window));
	XtAddCallback (file_pbutton[0], XmNactivateCallback, (XtCallbackProc) dismiss_display_standalone_text_cb, display_text_shell);
/* Use XtRealizeWidget()? */
	XtPopup (display_text_shell, XtGrabNone);
}

/*******************************************************************************
 * FUNCTION:	READ_FILE
 *
 *	Read an ASCII text file into a text dialog box with a "Dismiss"button.
 *
 *	This function USED to dump the file contents into a text widget that
 *	was passed as a parameter.
 *	Used by build_rtn.c
 ******************************************************************************/
void            read_file (char *filename)
{

	FILE           *fpr;
	struct stat     statb;
	char           *text;
	growbuf_t      *msg_gbuf;      /* Arbitrary-length string to compose messages in */
	char            int2string[11];/* Buffer for converting integer to character string. */

	growbuf_init (&msg_gbuf);
	if (filename == NULL)
	{
		growbuf_strcpy (msg_gbuf, "Unable to open file; no filename specified.\n");
		Display_Build_User_Msg (NULL, growbuf_str (msg_gbuf));
		return;		/* User must first select and read a Descartes specification. */
	}
	if ((fpr = fopen (filename, "r")) == NULL)
	{
		growbuf_strcpy (msg_gbuf, "Unable to open file \"");
		growbuf_strcat (msg_gbuf, filename);
		growbuf_strcat (msg_gbuf, "\".\n");
		Display_Build_User_Msg (NULL, growbuf_str (msg_gbuf));
	}
	stat (filename, &statb);
	growbuf_strcpy (msg_gbuf, "Reading \"");
	growbuf_strcat (msg_gbuf, filename);
	growbuf_strcat (msg_gbuf, "\"; size = ");
	sprintf (int2string, "%d", statb.st_size);
	growbuf_strcat (msg_gbuf, int2string);
	growbuf_strcat (msg_gbuf, ".\n");
	Display_Build_User_Msg (NULL, growbuf_str (msg_gbuf));

	text = XtMalloc ((unsigned) (statb.st_size + 1));
	if (text == NULL)
	{
		fprintf (stderr, "Cannot allocate enough spece for filename.");
		growbuf_strcpy (msg_gbuf, "Cannot allocate a buffer big enough to hold\"");
		growbuf_strcat (msg_gbuf, filename);
		growbuf_strcat (msg_gbuf, "\".\n");
		Display_Build_User_Msg (NULL, growbuf_str (msg_gbuf));
		fclose (fpr);
		return;
	}

	if (!fread (text, sizeof (char), statb.st_size + 1, fpr))
	{
		growbuf_strcpy (msg_gbuf, "Failed to read all of \"");
		growbuf_strcat (msg_gbuf, filename);
		growbuf_strcat (msg_gbuf, "\".\n");
		Display_Build_User_Msg (NULL, growbuf_str (msg_gbuf));
	}

	text[statb.st_size] = '\0';	/* Null terminate the text read from the file. */

	display_standalone_text (filename, text);

	fclose (fpr);
	growbuf_free (&msg_gbuf);
}

/*******************************************************************************
 * FUNCTION:	BLINK_WINDOW
 ******************************************************************************/

static void     blink_window (Widget drawing_a)
{
	int             fg,
	                bg;
	int             i;

	XBell (XtDisplay (drawing_a), -90);
/* Shut up Purify diagnostic about uninitialized memory read. */
	fg = 0;
	bg = 0;
	XtVaGetValues (drawing_a, XmNbackground, &bg, XmNforeground, &fg, NULL);

	for (i = 0; i < 3; i++)
	{
		XtVaSetValues (drawing_a, XmNbackground, fg, NULL);
		XtVaSetValues (drawing_a, XmNbackground, bg, NULL);
	}
}

/*******************************************************************************
 * FUNCTION:	PARSE
 *	Accepts commands from the child process which is ececuting "Exec_Run()".
 *	Exec_Run() executes the spec, and passes messages to this function.
 *	The first character in the message indicates which function parse()
 *	is to call.
 ******************************************************************************/

void            parse ()
{
	char           *msg;	       /* A handy alias for the body of the message (mesg_d.mesg_data). */
	int             command;       /* The first character in the body of the message indicates the operation to perform. */
	int             n;
	char            type[1];
	int             gc_n;
	int             x1,
	                y1,
	                x2,
	                y2,
	                x3,
	                y3;
	int             value;
	char            str[132];
	int             str_len;
	char            scr_b[1];


	if ((msgid = msgget (MSGKEY + 1, 0)) < 0)
		printf ("can not get message queue \n");

	do
	{			/* Do until you receive a message beginning with 'f' */

		mesg_d.mesg_type = 0L;
		if ((n = mesg_recv (msgid, &mesg_d)) <= 0)
		{
			printf ("message read error \n");
			n = 0;
		}

		mesg_d.mesg_data[n] = '\0';
		msg = mesg_d.mesg_data;
		command = (int) msg[0];

		switch (command)
		{

			case (int) 'd':	/* Draw either non-inverted or inverted. */
				sscanf (msg, "%s %d %d %d %d %d", type, &gc_n, &x1, &y1, &x2, &y2);
				if (gc_n == 0)
					XDrawLine (XtDisplay (drawing_a), Current_pix, gc, x1, y1, x2, y2);
				else
				{
					XSetFunction (XtDisplay (drawing_a), inv_gc, GXinvert);
					XDrawLine (XtDisplay (drawing_a), Current_pix, inv_gc, x1, y1, x2, y2);
				}
				break;

			case (int) 'c':
				sscanf (msg, "%s %d %d %d %d %d %d %d", type, &gc_n, &x1, &y1, &x2, &y2, &x3, &y3);
				XCopyArea (XtDisplay (drawing_a), Current_pix, XtWindow (drawing_a),
					   gc, x1, y1, x2, y2, x3, y3);
				break;

			case (int) 't':
				sscanf (msg, "%s %d %d %d %s %d", type, &gc_n, &x1, &y1, str, &str_len);
				XDrawString (XtDisplay (drawing_a), Current_pix, gc, x1, y1, str, str_len);
				break;

			case (int) 's':	/* Basically a no-op.  Nobody uses "scr_b" or "value" */
				sscanf (msg, "%s %s %d", type, scr_b, &value);
				break;

			case (int) 'm':	/* Print a message to a text widget.  This command usually comes from
						 * Display_Exec_Msg(). */

			/*
			 * NOTE: in the following sscanf() statement, "str"
			 * only accepts the first whitespace delimited word
			 * following the "type" and "value" header.  None of
			 * the sscanf()-assigned values is used.
			 */
				sscanf (msg, "%s %d %s", type, &value, str);

			/*
			 * Display everything exept the "type", the "value",
			 * and the whitespace that delimeted them.
			 */
				Display_Build_User_Msg (Show_text_w, msg + 4);
				break;

			case (int) 'b':
				XBell (XtDisplay (drawing_a), 0);
				break;

			case (int) 'k':
				blink_window (drawing_a);
				break;

			case (int) 'f':

			/*
			 * Received the quit command.  Exit via the test at
			 * the bottom of this do...while() loop.
			 */
				break;

			default:
				util_abort (__LINE__, __FILE__, "parse() received a command that it did not know how to process.\n"
					    "command == '%c' == %d == 0x%X\n", command, command, command);
		}		/* end switch (command) */
	} while (command != (int) 'f');
}
