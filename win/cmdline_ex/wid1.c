/*******************************************************************************
 * MODULE:	WID1.C
 *
 * AUTHOR:	Believed to be Lih-Shiun Timothy Lee, of Arizona State
 *		University.
 *******************************************************************************
 * $Date: 1994/08/13 18:58:18 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/cmdline_ex/RCS/wid1.c,v $
 *
 **-M**************************************************************************/

#if 0
/******************************************************************************
 *
$Log: wid1.c,v $
 * Revision 1.74  1994/08/13  18:58:18  franklin
 * Remove some debugging printf()s
 *
 * Revision 1.73  1994/08/10  19:13:03  franklin
 * Add server commands SRV_PRINT (utility), and SRV_TIMEOUT (message should
 * only come from the timeout() signal handler).
 *
 * Revision 1.72  1994/08/07  23:23:27  franklin
 * No more messages are passed via SysV queue, having the
 * key value (MSGKEY + 1).
 * This queue had been accessed via the message queue ID value stored
 * in the global "msgid".
 *
 * Revision 1.71  1994/08/06  22:24:40  franklin
 * Delete SRV_NO_OP.  It was not needed.
 *
 * Revision 1.70  1994/08/06  21:59:11  franklin
 * Renamed childproc_popup_error_dialog() to client_popup_error_dialog()
 * in exec_rtn1.c
 *
 * Revision 1.69  1994/08/06  18:29:19  franklin
 * Replace SysV message queue used by parse() with calls to the fifo.c package.
 * Replace sigle character server-command values, with values from the
 * enumverated type "server_command_tt", which has values such as SRV_BELL.
 * This module is now POSIX.1 compliant.
 *
 * Revision 1.68  1994/08/05  18:23:15  franklin
 * Die when you get bogus messages, so you can tell
 * where they came from.
 *
 * Revision 1.67  1994/08/05  18:12:45  franklin
 * exec_rtn1.h now requires hash.h and fifo.h to get the definition
 * for parent2child and child2parent.
 *
 * Revision 1.66  1994/08/04  22:38:43  franklin
 * workaround CodeCheck inability to handle ANSI variable argument lists.
 *
 * Revision 1.65  1994/08/04  18:07:11  franklin
 * 1. Remove unused function response3()
 * 2. Add #includes for cchk_missing_<standard include>.h in order
 * to get prototypes that CodeCheck doesnt think are there.
 *
 * Revision 1.64  1994/08/04  16:51:35  franklin
 * Changed str_len -> len; "str" prefix is reserved by string.h
 *
 * Revision 1.63  1994/08/03  21:50:46  franklin
 * Changed "str" to "pstr"; prefix "str" is reserved by string.h
 *
 * Revision 1.62  1994/08/03  18:03:29  franklin
 * Change toplevel -> ttoplevel, Exec_Run -> exec_run; "E" prefix is reserved
 * by errno.h
 *
 * Revision 1.61  1994/08/01  23:48:06  franklin
 * Suffix "_t" is reserved by POSIX.1
 *
 * Revision 1.60  1994/07/21  14:32:53  franklin
 * The bitmap for the Icon and the Help->Product Information
 * screen, had to be declared as type "unsigned char".  Cast
 * oops "unsigned char *", cast them back to "char *".
 *
 * Revision 1.59  1994/07/21  13:54:06  franklin
 * Fix the height and width of the draw_frame widget, where
 * the picure of Rene is displayed.  This is required by
 * the Motif 1.1 libraries at ASU.
 *
 * Revision 1.58  1994/07/08  00:08:19  franklin
 * Provide a new service in parse().  When a child sends a message of
 * type 'e' (by calling childproc_popup_error_dialog()),  popup
 * and application modal dialog box.
 *
 * Revision 1.57  1994/07/06  05:04:25  franklin
 * 1. Add filename pointer to to the file selection callback widget parameter
 *    (title_filter_subcallback_t) so that the selection widget can be used
 *    to change default filename settings.
 * 2. Add "set_filename_cb()" as a subcallback to set filenames (rather than
 *    just picking a file).
 * 3. Add popup_error_dialog(), utility for displaying a modal error dialog.
 * 4. Add install_shell_widgets_icon() -- Use Descartes face for the
 *    progams icon.
 * 5. Add print_normal_shell_xwd_command() and print_override_shell_xwd_command()
 *    to print window IDs.  Use with the "xwd" program to get bitmaps of
 *    the applications windows -- for writeups.
 *
 * Revision 1.56  1994/07/02  19:49:06  franklin
 * Add a frame around the picture of Descartes.  Print heading text
 * above the list of researchers.
 *
 * Revision 1.55  1994/07/02  17:10:01  franklin
 * Add dialog box with a picture of Rene Descartes, and the names
 * of the researchers who have worked on the language definition
 * and implementation.
 *
 * Revision 1.54  1994/06/29  03:01:08  franklin
 * Add support for the X11 "editres" program.
 *
 * Revision 1.53  1994/06/15  18:40:42  franklin
 * 1. In clear_drawing_area(), do not try to clear the drawing area if
 *    it has not been created yet.  This happens when the user specifies
 *    an input specification on the command line.
 * 2. Move the call to Build_Proc() from load_pixmap() to reset_descartes_specname
 *    in main.c
 *
 * Revision 1.52  1994/06/15  16:45:12  franklin
 * Greatly simplified load_pixmap().  Deleted extract_filename(); this
 *
 * Revision 1.51  1994/06/15  16:19:28  franklin
 * Remove File_Modified and Build_Flag_4_Old_File flags.
 *
 * Revision 1.50  1994/06/15  15:47:49  franklin
 * Remove references to the unused global DESC_Old_File_Name.
 * Add call to reset_descartes_specname() to update the main window
 * titlebar text and to enable menu selections for output files.
 *
 * Revision 1.49  1994/06/14  23:49:11  franklin
 * Add a function to clear the drawing area.  Call it
 * before you draw a specifications Hoare tree.
 *
 * Revision 1.48  1994/06/14  20:31:37  franklin
 * 1. Initialize static values x and y on the first invocation of "draw()".
 * 2. Remove pushbuttons from the drawing area manager widget.  Move the usable
 *    ones to the toolbar in main.c.
 *
 * Revision 1.47  1994/06/14  15:32:06  franklin
 * Use file_cb as the main callback function to read either a Descartes
 * spec, or an existing ASCII file into a text widget in a stand-alone
 * mainwindow.  file_cb accepts a pointer to a struct containing 1. The
 * title to display at the top of a FileSelectionDialog; 2. A regular expression
 * pattern to shorten the list of possible selections; and 3. A callback
 * function to execute when the user presses the OK button in the FileSelection
 * Dialog box.
 *
 * Revision 1.47  1994/06/14  15:32:06  franklin
 * Use file_cb as the main callback function to read either a Descartes
 * spec, or an existing ASCII file into a text widget in a stand-alone
 * mainwindow.  file_cb accepts a pointer to a struct containing 1. The
 * title to display at the top of a FileSelectionDialog; 2. A regular expression
 * pattern to shorten the list of possible selections; and 3. A callback
 * function to execute when the user presses the OK button in the FileSelection
 * Dialog box.
 *
 * Revision 1.46  1994/06/13  00:32:32  franklin
 * Delete calls that set global variables, just before another call overwrote
 * the value (nobody was using the first retrieved value).
 * Comment the meaning of several global variables.
 *
 * Revision 1.45  1994/06/12  04:48:15  franklin
 * Get the values for global variables win_width and win_height from the
 * new parent widget of the drawing area.
 *
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

static char    *rcsid = "@(#) $Id: wid1.c,v 1.74, h4_3_8 1994/08/13 18:58:18 franklin Exp $";

/* Udpate Nov 30 1992   */
/* pp.   346      */
#include <stdlib.h>
#include "cchk_missing_stdlib.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <stdarg.h>
#include "cchk_missing_stdarg.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>		       /* File/FIFO opening modes (Ex: O_RDONLY == open for read-only) */
#include "cchk_missing_unistd.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
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

#ifdef WORK_WITH_EDITRES
#include <X11/Xmu/Editres.h>	       /* Allows a user to modify application resources via the "edires" program included in the
				        * standard MIT X11R4 and X11R5 distribution.  This is a convenience only, if Editres.h
				        * and libXmu are not available, then turn this option off. */
#endif

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
#include <Xm/Form.h>

#include <Xm/MessageB.h>
#include <Xm/Scale.h>
#include <Xm/DialogS.h>

#include "desc_struct.h"
#include "build_rtn.h"		       /* Build_Proc(), and Print_Hoare_Tree() callback functions. */
#include "share_rtn.h"		       /* Get_File_Stat() */

#define MAX_PROC  4

#include "semops.h"
#include "mesg.h"
#include "analysis1.h"
#include "some_utils.h"		       /* util_abort() */
#include "hash.h"
#include "fifo.h"
#include "exec_rtn1.h"		       /* Log_File, Input_File, Output_File */
#include "command_line.h"	       /* non-Xwindow command line switches. */
#include "rene_descartes.h"	       /* Bitmap image of Franz Hals portrait of Rene Descartes */
#include "main.h"		       /* Globals ttoplevel and app */
#define	INCLUDED_FROM_MAIN	1      /* Check the declarations used externally only by main.c, against the definitions in this
				        * file. */
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


typedef struct
{
	XFontStruct    *font;
	int             fontheight;
	int             fontwidth;
}               text_data, *text_data_ptr;

static char    *base_buttons[] = {"Read Spec & Build Tree", "Execute Spec", "Help",
"Quit", "Test Driver", "Visual Editor"};

Widget          rd_spec_text_w;

Widget          drawing_a;	       /* The XmDrawingAreaWidget that the animation is drawn on. */
Pixmap          Current_pix = 0;       /* Drawable to display the animation. */
Dimension       win_width;	       /* Width of the viewable drawing area. */
Dimension       win_height;	       /* Height of the viewable drawing area. */
Dimension       width;		       /* Height of the virtual drawing area. */
Dimension       height;		       /* Width of the virtual drawing area. */
static Widget   vsb;		       /* Vertical scrollbar widget.  Scrolls teh viewable animation area across a larger virtual
				        * drawing area */
static Widget   hsb;		       /* Horizontal scrollbar widget. Horizontal scrolling across virtual animation area. */

Mesg            mesg_d;

/*
 * Pass the address of these structures as the client_data to file_cb().
 * These structures contain the XmNdialogTitle and XmNpattern resources for
 * the file selection dialog box.
 */
static void     load_pixmap (Widget dialog, void *dummyptr, XmFileSelectionBoxCallbackStruct * cbs);	/* Callback to load a
													 * spec. */
title_filter_subcallback_tt descartes_spec_file_selection_params = {
	"Descartes Specification File",
	"*" SPEC_EXTENSION,	       /* ANSI/ISO C string concatenation resolves this to "*.des" */
	DESC_New_File_Name,
	(XtCallbackProc) load_pixmap   /* XmNokCallback to invoke when/if the user selects a file. */
};
static void     read_text_file_cb (Widget dialog, void *dummyptr, XmFileSelectionBoxCallbackStruct * cbs);

title_filter_subcallback_tt view_log_file_selection_params = {
	"Log File",
	"*" LOG_EXTENSION,
	Log_File.name,
	(XtCallbackProc) read_text_file_cb
};

title_filter_subcallback_tt view_input_file_selection_params = {
	"Input File",
	"*" INPUT_EXTENSION,
	Input_File.name,
	(XtCallbackProc) read_text_file_cb
};
title_filter_subcallback_tt view_output_file_selection_params = {
	"Output File",
	"*" OUTPUT_EXTENSION,
	Output_File.name,
	(XtCallbackProc) read_text_file_cb
};

/*
 * Have the language processor write these files to some name other than
 * <specname>.[input|output|log]
 */
title_filter_subcallback_tt set_log_file_name_params = {
	"Set Log File Name",
	"*" LOG_EXTENSION,
	Log_File.name,
	(XtCallbackProc) set_filename_cb
};
title_filter_subcallback_tt set_input_file_name_params = {
	"Set Input File Name",
	"*" INPUT_EXTENSION,
	Input_File.name,
	(XtCallbackProc) set_filename_cb
};
title_filter_subcallback_tt set_output_file_name_params = {
	"Set Output File Name",
	"*" OUTPUT_EXTENSION,
	Output_File.name,
	(XtCallbackProc) set_filename_cb
};

/*******************************************************************************
 * FUNCTION:	CALL_XTUNMANAGECHILD_CB
 ******************************************************************************/

static void     call_XtUnmanageChild_cb (Widget wid, void *dummyptr1, XmPushButtonCallbackStruct * dummyptr2)
{
	XtUnmanageChild (wid);
}

/*******************************************************************************
 * FUNCTION:	CLEAR_DRAWING_AREA
 *	Erase the drawing area, if it has been created.
 ******************************************************************************/
void            clear_drawing_area (void)
{
	if (Current_pix)
		XFillRectangle (XtDisplay (drawing_a), Current_pix, rev_gc, 0, 0, width, height);
}

/*******************************************************************************
 * FUNCTION:	LOAD_PIXMAP
 ******************************************************************************/

/* pp  178    */
static void     load_pixmap (Widget dialog, void *dummyptr, XmFileSelectionBoxCallbackStruct * cbs)
{
	char           *filename = NULL;
	Boolean         got_a_filename;

	if (cbs)
	{

#ifdef MOTIF_1_2_AND_LATER
		got_a_filename = XmStringGetLtoR (cbs->value, XmFONTLIST_DEFAULT_TAG, &filename);
#else
		got_a_filename = XmStringGetLtoR (cbs->value, XmSTRING_DEFAULT_CHARSET, &filename);
#endif

		if (got_a_filename)
		{
			XtUnmanageChild (dialog);

		/* Load the input file into internal data structures. */
			reset_descartes_specname (filename);
			XtFree (filename);
		}
	}
}

/*******************************************************************************
 * FUNCTION:	READ_FILE
 *
 *	Read an ASCII text file into a standalone main window widget.  The user
 *	can destroy the standalone widget, by selecting "File->Exit" from the
 *	meunu bar of this standalone main window.
 *
 *	This function USED to dump the file contents into a text widget that
 *	was passed as a parameter.
 *
 *	This function is called directly from Build_Hoare_Tree in build_rtn.c
 *	to view the tree file, and also called from callback function
 *	read_text_file_cb(), *	below, to read a file that should already exist.
 ******************************************************************************/
void            read_file (char *filename)
{

	FILE           *fpr;
	struct stat     statb;
	char           *text;
	growbuf_tt     *msg_gbuf;      /* Arbitrary-length string to compose messages in */
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
}				       /* end read_file() */

/*******************************************************************************
 * FUNCTION	READ_TEXT_FILE_CB
 *	Called if the user presses the OK button in a file selection dialog box.
 *	cbs->value is the name of the file that the user selected.
 ******************************************************************************/
static void     read_text_file_cb (Widget dialog, void *dummyptr, XmFileSelectionBoxCallbackStruct * cbs)
{
	char           *filename = NULL;
	Boolean         got_a_filename;


	if (cbs)
	{

#ifdef MOTIF_1_2_AND_LATER
		got_a_filename = XmStringGetLtoR (cbs->value, XmFONTLIST_DEFAULT_TAG, &filename);
#else
		got_a_filename = XmStringGetLtoR (cbs->value, XmSTRING_DEFAULT_CHARSET, &filename);
#endif

		if (got_a_filename)
		{
			XtUnmanageChild (dialog);
			if (!(filename && *filename))	/* Make sure filename is not NULL, and points to a nonzero length string. */
			{
				XtFree (filename);
				return;
			}
			read_file (filename);
			XtFree (filename);
		}
	}
}

/*******************************************************************************
 * FUNCTION:	SET_FILENAME_CB
 *	Set the name of the *.input, *.output, or *.log file.
 * NOTE:
 *	The second parameter to this function will be a pointer to allocated
 *	storage.  I used a separate "filename" pointer, so I could free the
 *	heap space allocated by XmStringGetLtoR().  When I wrote this
 *	function, outfile_nameptr was always pointing to a statically
 *	declared character array.
 ******************************************************************************/
void            set_filename_cb (Widget dialog, char *outfile_nameptr, XmFileSelectionBoxCallbackStruct * cbs)
{
	char           *filename = NULL;
	Boolean         got_a_filename;


	if (cbs)
	{

#ifdef MOTIF_1_2_AND_LATER
		got_a_filename = XmStringGetLtoR (cbs->value, XmFONTLIST_DEFAULT_TAG, &filename);
#else
		got_a_filename = XmStringGetLtoR (cbs->value, XmSTRING_DEFAULT_CHARSET, &filename);
#endif

		if (got_a_filename)
		{
			XtUnmanageChild (dialog);
			if (filename && *filename)
			{
				strcpy (outfile_nameptr, filename);
				XtFree (filename);
			}
		}
	}
}

/*******************************************************************************
 * FUNCTION:	FILE_CB
 *	This callback creates a general-purpose file selection dialog box.  It
 *	is passed a pointer to a structure containing:
 *		1. A title for the file selection dialog.
 *		2. A regular expression to filter the list of candidate files.
 *		3. A callback function to invoke when and if the user selects
 *		   a file with the dialog box.
 *	At this writing, there were two callback functions passed via
 *	title_and_filter->ok_callback:
 *		1. load_pixmap(), which reads a Descartes specification into
 *		   internal data structures, and
 *		2. read_text_file_cb, which reads a text file into a stand-
 *		   alone main window widget, containing a text widget.  This
 *		   standalone main window can be iconified independently of
 *		   the main application window.
 ******************************************************************************/
void            file_cb (Widget dummywidget, title_filter_subcallback_tt * title_and_filter, XmPushButtonCallbackStruct * dummyptr2)
{
	static Widget   dialog = NULL; /* Create it once, then re-use it. */
	Widget          button2deactivate;
	XmString        dialog_title;
	XmString        file_suffix;
	Arg             wargs[10];
	Cardinal        n;
	static XtCallbackProc last_callback = NULL;	/* You must remove the XmNokCallback, AND ITS DATA, from the previous
							 * call to this function, or else you will end up calling multiple
							 * callbacks! */
	static char    *last_callback_data;

	if (!dialog)
	{

		dialog = XmCreateFileSelectionDialog (ttoplevel, "file_sel", NULL, 0);

		button2deactivate = XmFileSelectionBoxGetChild (dialog, XmDIALOG_HELP_BUTTON);
		XtUnmanageChild (button2deactivate);

		XtAddCallback (XtParent (dialog), XmNpopupCallback, (XtCallbackProc) print_normal_shell_xwd_command, "file_sel");
		XtAddCallback (dialog, XmNcancelCallback, (XtCallbackProc) call_XtUnmanageChild_cb, NULL);
	}


#ifdef MOTIF_1_2_AND_LATER
	dialog_title = XmStringCreateLocalized (title_and_filter->file_dialog_title);
	file_suffix = XmStringCreateLocalized (title_and_filter->file_filter);
#else
	dialog_title = XmStringCreateLtoR (title_and_filter->file_dialog_title, XmSTRING_DEFAULT_CHARSET);
	file_suffix = XmStringCreateLtoR (title_and_filter->file_filter, XmSTRING_DEFAULT_CHARSET);
#endif

	n = 0;
	XtSetArg (wargs[n], XmNdialogTitle, dialog_title);
	n++;
	XtSetArg (wargs[n], XmNpattern, file_suffix);
	n++;
	XtSetValues (dialog, wargs, n);

	XmStringFree (dialog_title);
	XmStringFree (file_suffix);

	if (last_callback)
	{
		XtRemoveCallback (dialog, XmNokCallback, last_callback, last_callback_data);
	}
	XtAddCallback (dialog, XmNokCallback, title_and_filter->ok_callback, title_and_filter->filename_array);
	last_callback = title_and_filter->ok_callback;
	last_callback_data = title_and_filter->filename_array;

	XtManageChild (dialog);
	XtPopup (XtParent (dialog), XtGrabNone);
}

/*******************************************************************************
 * FUNCTION:	DRAW
 *	Draws a line from the position of the last event, to the positon of
 *	the current event, and stores the new position for the next request.
 ******************************************************************************/

static void     draw (Widget widget, XButtonEvent * event, String * args, int *num_args)
{
	static int      first_call_to_this_function = True;
	static Position x,
	                y;

	if (first_call_to_this_function)
	{
		x = event->x;
		y = event->y;
		first_call_to_this_function = False;
	}
	if (*num_args != 1)
		XtError ("draw() invoked with the wrong number of arguments.");
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
 * FUNCTION:	CREATE_DRAWING_AREA
 *      Create the window for the execution animation graphics.  Store the
 *	global values that controll automatic scrolling.
 * NOTE:
 *	This function replaces much of what was done by the old "create_exec"
 *	callback function.  Earlier implementations of the language processor
 *	would only create the drawing area when it was time to begin execution.
 ******************************************************************************/
static char    *exec_buttons[] = {"Run", "Draw", "Print Log", "Done", "Help"};
void            create_drawing_area (Widget parent)
{
	Widget          scrollwin;
	XGCValues       gcv;
	XGCValues       gcv1;
	XtActionsRec    actions;
	int             value = 0;
	int             max = 0;

/*
 * The following translations are described on the manpage of the XmManager
 * widget class. The combination of these translations and the "draw"
 * function (in this file) let the user "scribble" in the animation window.
 * Not a terribly useful feature, but it is there if you want it.
 */
	String          translations = "<Btn1Down>: draw(down) ManagerGadgetArm()  \n"
	"<Btn1Up>: draw(up) ManagerGadgetActivate()  \n"
	"<Btn1Motion>: draw(motion) ManagerGadgetButtonMotion()";

/* Handle   scrollbar     */
	scrollwin = XtVaCreateManagedWidget ("scrollwin", /* xmScrolledWindowWidgetClass */ xmMainWindowWidgetClass, parent,
					     XmNscrollBarDisplayPolicy, XmAS_NEEDED,
					     XmNscrollingPolicy, XmAUTOMATIC, NULL);
	XtVaGetValues (scrollwin, XmNverticalScrollBar, &vsb, XmNvalue, &value, NULL);
	XtVaGetValues (vsb, XmNmaximum, &max, XmNvalue, &value, NULL);

	XtVaGetValues (scrollwin, XmNhorizontalScrollBar, &hsb, XmNvalue, &value, NULL);
	XtVaGetValues (hsb, XmNmaximum, &max, XmNvalue, &value, NULL);

	actions.string = "draw";
	actions.proc = (XtActionProc) draw;
	XtAppAddActions (app, &actions, 1);
	drawing_a = XtVaCreateManagedWidget ("drawing_a",
					     xmDrawingAreaWidgetClass, scrollwin,
					     XmNtranslations, XtParseTranslationTable (translations),
					     XmNwidth, 1280,
					     XmNheight, 1500,
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

/*
 * Set the global variables used to handle automatic scrolling during
 * execution.
 */
	XtVaGetValues (drawing_a, XmNwidth, &width, XmNheight, &height, NULL);
	XtVaGetValues (vsb, XmNmaximum, &max, XmNvalue, &value, NULL);
	fflush (stdout);
	XtVaSetValues (scrollwin, XmNunitType, XmPIXELS, NULL);
	XtVaGetValues (scrollwin, XmNwidth, &win_width, XmNheight, &win_height, NULL);
	fflush (stdout);

}				       /* end create_drawing_area() */

/******************************************************************************
 * UTILITY FUNCTIONS CALLED BY OTHER MODULES:
 *	Display_Build_User_Msg()
 *	popup_error_dialog()
 *	display_standalone_text()
 *	install_shell_widgets_icon()
 *	print_normal_shell_xwd_command()
 *	print_override_shell_xwd_command()
 *	parse()
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION:	DISPLAY_BUILD_USER_MSG
 *	Used by build_hoare_tree.c, build_rtn.c, des2.y
 *	Display new messages in the message window at the bottom of the
 *	applications MainWindow widget, then move them to the msghistory_text
 *	when a new message comes along.
 ******************************************************************************/

void            Display_Build_User_Msg (Widget dummy, const char *msg)
{
	XmTextPosition  last_position;
	static growbuf_tt *last_msg_gbuf = NULL;

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
	XmTextReplace (message_text, 0, last_position, growbuf_str (last_msg_gbuf));
}

/*******************************************************************************
 * FUNCTION:    POPUP_ERROR_DIALOG
 *
 * PURPOSE:     Display a error message inside a dialog box.  Stop all activity
 *              in this application until the user acknowledges the dialog
 *              box.
 *
 * USE:         Takes the same parameter list that "printf()" takes.
 *
 * NOTE:        This function must only be called from the server process.
 *              Subprocessees must use client_popup_error_dialog()
 ******************************************************************************/

void            popup_error_dialog (const char *printf_fmt_str,...)
{
	va_list         arguments;
	static Widget   err_dialog = NULL;
	char            buf[2048];
	Widget          subwidget;
	XmString        errmsg;
	Arg             args[10];
	Cardinal        nargs;

	va_start (arguments, printf_fmt_str);

	if (!err_dialog)
	{
		nargs = 0;
		XtSetArg (args[nargs], XmNtitle, "Error Message");
		nargs++;

	/*
	 * Error dialogs must be application modal to comply with the Motif
	 * 1.2 style guide.
	 */
		XtSetArg (args[nargs], XmNdialogStyle, XmDIALOG_APPLICATION_MODAL);
		nargs++;
		err_dialog = XmCreateErrorDialog (ttoplevel, "err_dialog", args, nargs);
		subwidget = XmMessageBoxGetChild (err_dialog, XmDIALOG_CANCEL_BUTTON);
		XtUnmanageChild (subwidget);
		subwidget = XmMessageBoxGetChild (err_dialog, XmDIALOG_HELP_BUTTON);
		XtUnmanageChild (subwidget);
	}
	vsprintf (buf, printf_fmt_str, arguments);
	errmsg = XmStringCreateLtoR (buf, "master1");

	nargs = 0;
	XtSetArg (args[nargs], XmNmessageString, errmsg);
	nargs++;
	XtSetValues (err_dialog, args, nargs);

	XmStringFree (errmsg);
	XtManageChild (err_dialog);
	va_end (arguments);
}

/*******************************************************************************
 * FUNCTION:	DISPLAY_STANDALONE_TEXT
 *
 *	Print a (probably long) string of ASCII text in a Motif MainWindow,
 *	and display it.  The user can iconify, and dismiss this window
 *	seperately from the application main window (ttoplevel), this window
 *	will be destroyed when the main application window is destroyted.
 *
 *	You will probably append a bunch of text, with embedded newline
 *	characters ("\n") to a growbuf object (some_utils.c) and pass the
 *	large grow buffers text to this function.
 ******************************************************************************/
static void     dismiss_display_standalone_text_cb (Widget dummywidget, Widget standalone_window, XmPushButtonCallbackStruct * cbs)
{
	XtUnmanageChild (standalone_window);
	XtDestroyWidget (standalone_window);
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
	display_text_shell = XtCreatePopupShell ("display_text_shell", topLevelShellWidgetClass, ttoplevel, args, nargs);
	install_shell_widgets_icon (display_text_shell);

#ifdef WORK_WITH_EDITRES
	XtAddEventHandler (display_text_shell, (EventMask) 0, True, _XEditResCheckMessages, NULL);
#endif

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

/*
 * Set the ScrolledWindow parent of the text_scrolled_window as the work
 * region widget, otherwise, the scroll bars wont work properly.
 */
	XmMainWindowSetAreas (mainwindow, menubar, NULL, NULL, NULL, XtParent (text_scrolled_window));
	XtAddCallback (file_pbutton[0], XmNactivateCallback,
		       (XtCallbackProc) dismiss_display_standalone_text_cb, display_text_shell);
	XtPopup (display_text_shell, XtGrabNone);
}

/*******************************************************************************
 * FUNCTION:	rene_descartes_heading
 *	Utility function invoked from rene_descartes(), to place a caption under
 *	Descartes picture, and to print heading text before the list of
 *	contributors
 ******************************************************************************/
static void     rene_descartes_heading (Widget parent)
{
	Widget          captiong;      /* Label gadget to hold the caption for the picture */
	Widget          headingg1_mgr; /* Use to center text in the headingg1 label gadget. */
	Widget          headingg1;
	Widget          headingg2;     /* This text is left-aligned. */
	XmString        captionstr;
	XmString        headingstr1;
	XmString        headingstr2;
	Arg             args[10];
	Cardinal        nargs;

	captionstr = XmStringCreateLtoR ("\"Descartes\", by Franz Hals.", "small_italic");
	nargs = 0;
	XtSetArg (args[nargs], XmNlabelString, captionstr);
	nargs++;
	captiong = XmCreateLabelGadget (parent, "captiong", args, nargs);
	XtManageChild (captiong);

	nargs = 0;
	XtSetArg (args[nargs], XmNentryAlignment, XmALIGNMENT_CENTER);
	nargs++;
	headingg1_mgr = XmCreateRowColumn (parent, "headingg1_mgr", args, nargs);
	XtManageChild (headingg1_mgr);

	headingstr1 = XmStringCreateLtoR ("Descartes Language Processor", "master1");
	nargs = 0;
	XtSetArg (args[nargs], XmNlabelString, headingstr1);
	nargs++;
	headingg1 = XmCreateLabelGadget (headingg1_mgr, "headingg1", args, nargs);
	nargs++;
	XtSetArg (args[nargs], XmNalignment, XmALIGNMENT_CENTER);
	nargs++;
	XtManageChild (headingg1);

	headingstr2 = XmStringCreateLtoR ("Contributors:", "master1");
	nargs = 0;
	XtSetArg (args[nargs], XmNlabelString, headingstr2);
	nargs++;
	headingg2 = XmCreateLabelGadget (parent, "headingg2", args, nargs);
	nargs++;
	XtManageChild (headingg2);

	XmStringFree (headingstr1);
	XmStringFree (headingstr2);
	XmStringFree (captionstr);
}

/*******************************************************************************
 * FUNCTION:	ADD_RESEARCHER
 *	Utility function invoked from rene_descartes(), to insert the names
 *	of the people who have worked on the language processor.
 ******************************************************************************/
static void     add_researcher (Widget parent, char *contributor, char *year)
{
	Widget          rowmgr;	       /* "Row" of text.  A contributor followed by the year(s) of contribution(s) */
	Widget          contrg;	       /* Label gadget to hold the name of a contributor. */
	Widget          yearg;	       /* Label gadget to hold researchers year. */
	XmString        contrstr;
	XmString        yearstr;
	static int      count = 0;     /* Used to generate instance names for the rowmgr widgets. */
	char            mgrname[128];
	Arg             args[10];
	Cardinal        nargs;

	++count;
	sprintf (mgrname, "contrib_%d", count);
	rowmgr = XmCreateForm (parent, mgrname, NULL, 0);
	XtManageChild (rowmgr);

	contrstr = XmStringCreateLtoR (contributor, "unbold");
	yearstr = XmStringCreateLtoR (year, "unbold");

	nargs = 0;
	XtSetArg (args[nargs], XmNleftAttachment, XmATTACH_FORM);
	nargs++;
	XtSetArg (args[nargs], XmNalignment, XmALIGNMENT_BEGINNING);
	nargs++;
	XtSetArg (args[nargs], XmNlabelString, contrstr);
	nargs++;
	contrg = XmCreateLabelGadget (rowmgr, "contrg", args, nargs);
	XtManageChild (contrg);

	nargs = 0;
	XtSetArg (args[nargs], XmNrightAttachment, XmATTACH_FORM);
	nargs++;
	XtSetArg (args[nargs], XmNrightAttachment, XmATTACH_FORM);
	nargs++;
	XtSetArg (args[nargs], XmNalignment, XmALIGNMENT_END);
	nargs++;
	XtSetArg (args[nargs], XmNlabelString, yearstr);
	nargs++;
	yearg = XmCreateLabelGadget (rowmgr, "yearg", args, nargs);
	XtManageChild (yearg);

	XmStringFree (contrstr);
	XmStringFree (yearstr);
}

/*******************************************************************************
 * FUNCTION:	RENE_DESCARTES
 *
 *	Popup a bitmap image of Franz Hals portrait of Rene Descartes, along
 *	with the names of researchers who have worked on this language
 *	processor.
 *
 *	I hacked "message dialog" a bit, by adding my own manager widget
 *	as its child.  That way I did not have to put together my own
 *	buttons and separator widgets to get a style-guide compliant
 *	dialog box.
 ******************************************************************************/
void            rene_descartes (Widget dummywidget, void *dummyptr1, XmPushButtonCallbackStruct * dummyptr2)
{
	Widget          rene_dialog;
	Widget          manager;
	Widget          draw_frame;
	Widget          draw_area;
	Widget          unwanted;
	Pixmap          rene_pmap;
	Display        *display;
	Screen         *screen;
	Drawable        root;
	Pixel           foreground;
	Pixel           background;
	int             depth;
	Arg             args[10];
	Cardinal        nargs;

	nargs = 0;
	XtSetArg (args[nargs], XmNtitle, "Descartes");
	nargs++;
	rene_dialog = XmCreateMessageDialog (ttoplevel, "rene_dialog", args, nargs);

	XtAddCallback (XtParent (rene_dialog), XmNpopupCallback, (XtCallbackProc) print_normal_shell_xwd_command, "rene_dialog");

#ifdef WORK_WITH_EDITRES
	XtAddEventHandler (XtParent (rene_dialog), (EventMask) 0, True, _XEditResCheckMessages, NULL);
#endif

/* Strip out the parts of the dialog box that you do not want. */
	unwanted = XmMessageBoxGetChild (rene_dialog, XmDIALOG_CANCEL_BUTTON);
	XtUnmanageChild (unwanted);
	unwanted = XmMessageBoxGetChild (rene_dialog, XmDIALOG_HELP_BUTTON);
	XtUnmanageChild (unwanted);
	unwanted = XmMessageBoxGetChild (rene_dialog, XmDIALOG_MESSAGE_LABEL);
	XtUnmanageChild (unwanted);
	unwanted = XmMessageBoxGetChild (rene_dialog, XmDIALOG_SYMBOL_LABEL);
	XtUnmanageChild (unwanted);

/* Insert your own manager widget into the dialog box. */
	manager = XmCreateRowColumn (rene_dialog, "manager", NULL, 0);
	XtManageChild (manager);

	draw_frame = XtVaCreateManagedWidget ("draw_frame", xmFrameWidgetClass, manager,
					      XmNmarginWidth, 1,
					      XmNmarginHeight, 1,
					      XmNwidth, descartes_width + 2,	/* This frame has a margin of 1 pixel. */
					      XmNheight, descartes_height + 2,	/* This frame has a margin of 1 pixel. */
					      NULL);

	display = XtDisplay (rene_dialog);
	screen = XtScreen (rene_dialog);
	root = RootWindowOfScreen (screen);
	foreground = WhitePixelOfScreen (screen);
	background = BlackPixelOfScreen (screen);

	depth = DefaultDepthOfScreen (screen);

	rene_pmap = XCreatePixmapFromBitmapData (display, root,
						 (char *) descartes_bits, descartes_width, descartes_height,
						 foreground, background, depth);

	draw_area = XtVaCreateManagedWidget ("draw_area", xmDrawingAreaWidgetClass, draw_frame,
					     XmNwidth, descartes_width,
					     XmNheight, descartes_height,
					     XmNresizePolicy, XmNONE,
					     XmNunitType, XmPIXELS,
					     XmNbackgroundPixmap, rene_pmap,
					     NULL);

	rene_descartes_heading (manager);
	add_researcher (manager, "J. E. Urban ", "1977, 1992");
	add_researcher (manager, "K. S. Tang", "1981");
	add_researcher (manager, "Y. C. Yu", "1984");
	add_researcher (manager, "M. S. Sun", "1984");
	add_researcher (manager, "L. Lee", "1991");
	add_researcher (manager, "H-C Cheng", "1992");
	add_researcher (manager, "K-Y  Sung", "1992");
	add_researcher (manager, "M. L.  Franklin", "1994");

	XtManageChild (rene_dialog);
}

/*******************************************************************************
 * FUNCTION:	INSTALL_SHELL_WIDGETS_ICON
 ******************************************************************************/
void            install_shell_widgets_icon (Widget shellwidget)
{
	static Pixmap   icon_pixmap;   /* Create it once and re-use it. */
	static int      first_time_called = TRUE;
	Arg             args[5];
	Cardinal        nargs;

	if (first_time_called)
	{
		first_time_called = FALSE;
		icon_pixmap = XCreateBitmapFromData (XtDisplay (ttoplevel), RootWindowOfScreen (XtScreen (ttoplevel)),
						     (char *) descartes_icon_bits, descartes_icon_width, descartes_icon_height);
	}

	nargs = 0;
	XtSetArg (args[nargs], XmNiconPixmap, icon_pixmap);
	nargs++;
	XtSetValues (shellwidget, args, nargs);
}

/*******************************************************************************
 * FUNCTION:	PRINT_NORMAL_SHELL_XWD_COMMAND
 *
 * PURPOSE:
 *	Print a command that will dump a shell widget's window to a file.
 *	This will let you convert the file into a format accepted by your word
 *	processor, so you can include pictures of windows in the writeup of
 *	your research.
 *
 *	The X11 utility program for dumping bitmap images of window contents,
 *	is called "xwd", there should be a manpage for it in your X11
 *	distribution.
 *
 *	There are two versions of this function; one for WMShell widgets, which
 *	are "decorated" by a window manager frame, and one for OverrideShell
 *	widgets, such as popup menus, which are NOT decorated by the window
 *	manager.  See the Motif programmers reference manual for more details
 *	about these shell widget types.
 *
 *	THIS FUNCTION DOES NOT INVOKE XWD.  It simply prints the command you
 *	need (which includes the WINDOW ID -- ONLY AVAILABLE AT RUNTIME) to
 *	stderr.  Execute the command printed by this function in a terminal
 *	window to generate the file.
 *
 *	The file format written by xwd is called "X window dump" format.
 *	Several people have written convertes from xwd format to formats such
 *	as GIF, TIFF, BMP, DXF and others.
 *
 *	A list of programs that can convert xwd files is given in the
 *	FAQ for the Usenet "comp.windows.x" newsgroup.  The converter I used
 *	(Malcolm Franklin, Summer 1994), was the "convert" program in the
 *	"ImageMagick" toolkit.  I got it from:
 *		ftp.x.org:contrib/ImageMagick-3.1.tar.Z
 *	I converted the xwd images to GIF format, and imported the pictures
 *	into Microsoft Word for Windows.
 ******************************************************************************/
void            print_normal_shell_xwd_command (Widget wmshellwidget, char *base_fname, XmAnyCallbackStruct * dummyptr)
{

#ifndef PRINT_SCREEN_DUMP_COMMANDS
	return;
#else
	fprintf (stderr, "xwd -frame -id %d -out %s.xwd\n", XtWindow (wmshellwidget), base_fname);
	fflush (stderr);
#endif
}

/*******************************************************************************
 * FUNCTION:	PRINT_OVERRIDE_SHELL_XWD_COMMAND
 *	See comments on print_normal_shell_xwd_command().
 ******************************************************************************/
void            print_override_shell_xwd_command (Widget overrideshellwidget, char *base_fname, XmAnyCallbackStruct * dummyptr)
{

#ifndef PRINT_SCREEN_DUMP_COMMANDS
	return;
#else
	printf ("\tFor shell widget instance %s:\n", base_fname);
	fprintf (stderr, "xwd -id %d -out %s.xwd\n", XtWindow (overrideshellwidget), base_fname);
	fflush (stderr);
#endif
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
 *	Accepts commands from the child process which is executing "exec_run()".
 *	exec_run() executes the spec, and passes messages to this function.
 *	The first character in the message indicates which function parse()
 *	is to call.
 ******************************************************************************/

void            parse (shared_fifodata_tt * parent2child)
{
	int             x1,
	                y1,
	                x2,
	                y2,
	                width,
	                height;
	int             len;
	Widget          unused_parameter = NULL;
	char            child_pidstr[INTLEN];
	server_command_tt command;
	const char     *dataptr;       /* Points at data in the parent2child internal structures; therefore it is declared as
				        * const. */
	size_t          datalen;

	open_parent2child_fifo (parent2child, O_RDONLY);

	do
	{			/* Do until you receive a SRV_SHUTDOWN command. */
		command = receive_fm_child (parent2child, child_pidstr, &datalen);
		dataptr = shared_fifo_data (parent2child);

		switch (command)
		{
			case SRV_CONNECT:	/* The SRV_CONNECT message is automatically sent by the client process when it
						 * calls connect_to_parent().  The source code for the client process should not
						 * send an SRV_CONNECT command directly, or else it will goof up the protocol. */
				parent_open_reply_fifo (parent2child, child_pidstr);
				break;

			case SRV_ECHO:	/* A test message you can send.  You should get your message echoed right back to you. */
				send2child (parent2child, child_pidstr, command, dataptr);
				break;

			case SRV_PRINT:	/* A test message you can send.  Just prints what you sent to stdout. */
				printf (dataptr);
				break;

			case SRV_TIMEOUT:	/* An interrupt handler is sending a message to a process waiting for an alarm
						 * message.  The PID of the interrupt handler, and of the blocked process, are
						 * the same. */
				send2child (parent2child, child_pidstr, command, dataptr);
				break;

			case (int) SRV_POPUP_ERROR_DIALOG:	/* Popup an error dialog.  Print all of message except type,
								 * value, and delimiting whitespace. */
				popup_error_dialog (dataptr);
				break;

			case (int) SRV_DRAW_LINE:	/* Draw either non-inverted or inverted. */
				{
					int             inverted;	/* Boolean, first parameter to clientXDrawLine() */

					sscanf (dataptr, "%d %d %d %d %d", &inverted, &x1, &y1, &x2, &y2);
					if (inverted)
					{
						XSetFunction (XtDisplay (drawing_a), inv_gc, GXinvert);
						XDrawLine (XtDisplay (drawing_a), Current_pix, inv_gc, x1, y1, x2, y2);
					}
					else
					{
						XDrawLine (XtDisplay (drawing_a), Current_pix, gc, x1, y1, x2, y2);
					}
				}
				break;

			case SRV_COPY_AREA:	/* 'c' */
				sscanf (dataptr, "%d %d %d %d %d %d", &x1, &y1, &width, &height, &x2, &y2);
				XCopyArea (XtDisplay (drawing_a), Current_pix, XtWindow (drawing_a),
					   gc, x1, y1, width, height, x2, y2);
				break;

			case SRV_DRAW_STRING:	/* 'd' */

			/*
			 * NOTE: this command comes in TWO PARTS, that is why
			 * it makes its own call to receive_fm_child (). The
			 * first message contains the integer coordinates and
			 * length  parameters to XDrawString(), the second
			 * message contains the actual string to be
			 * displayed.  The string may contain whitespace,
			 * which would goof up  sscanf(), therefore, the
			 * string is sent in a seperate message.
			 */
				sscanf (dataptr, "%d %d %d", &x1, &y1, &len);
				receive_fm_child (parent2child, child_pidstr, &datalen);
				dataptr = shared_fifo_data (parent2child);
				XDrawString (XtDisplay (drawing_a), Current_pix, gc, x1, y1, dataptr, len);
				break;

			case SRV_DISPLAY_EXEC_MSG:	/* Print a message to a text widget.  This command comes from
							 * Display_Exec_Msg(). */
				Display_Build_User_Msg (unused_parameter, dataptr);
				break;

			case SRV_BELL:	/* 'b' */
				XBell (XtDisplay (drawing_a), 0);
				break;

			case SRV_BLINK:
				blink_window (drawing_a);
				break;

			case SRV_SHUTDOWN:	/* Received the quit command.  Exit via the test at the bottom of this
						 * do...while() loop.  */
				break;

			default:
				util_abort (__LINE__, __FILE__, "parse() received a command that it did not know how to process.\n"
					    "command == '%c' == %d == 0x%X\n", command, command, command);
		}		/* end switch (command) */
	} while (command != SRV_SHUTDOWN);

	destroy_fifos (parent2child);
}
