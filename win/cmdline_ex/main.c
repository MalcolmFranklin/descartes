#undef _POSIX_SOURCE		       /* parse() uses a SysV message queue to get requests from a child process. */
/*******************************************************************************
 *          Copyright (c) 1994,  Motorola Inc.,  Chandler, Arizona 85224
 *
 * MODULE:	MAIN.C
 *
 * PURPOSE:	Initialize the user interface, and register callbacks to
 *		the functions that implement the language processor.
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 * $Author: franklin $
 *******************************************************************************
 * $Date: 1994/08/05 18:22:11 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/cmdline_ex/RCS/main.c,v $
 *
 ******************************************************************************/



#if 0
/******************************************************************************
 *
$Log: main.c,v $
 * Revision 1.30  1994/08/05  18:22:11  franklin
 * exec_rtn1.h now requires hash.h and fifo.h to get the type definition
 * for the parameter to exec_run().
 *
 * Revision 1.29  1994/08/04  18:00:29  franklin
 * Add #includes for cchk_missing_<standard include>.h in order
 * to get prototypes that CodeCheck doesnt think are there.
 *
 * Revision 1.28  1994/08/04  16:35:06  franklin
 * 1. Moved include of string.h above stdlib.h and stdio.h, to eliminate
 *    CodeCheck warning about the prefix "str" being used before string.h
 *    had been read.
 * 2. Changed toolbar_mgr -> ttoolbar_mgr; the "to" prefix is reserved
 *    by ctype.h.
 *
 * Revision 1.27  1994/08/03  18:06:11  franklin
 * Change EXIT_IDX -> XEXIT_IDX, because "E" prefix is reserved by errno.h.
 * Change toplevel -> ttoplevel, because "to" prefix is reserved by ctype.h
 *
 * Revision 1.26  1994/08/01  23:53:34  franklin
 * Suffix "_t" is reserved by POSIX.1.
 *
 * Revision 1.25  1994/07/21  13:50:41  franklin
 * Use courier instead of prestige as the default text-widget
 * font (fixed width font).  The prestige font wasnt on any
 * of the systems I tested at ASU; courier seems to be more
 * common.
 *
 * Revision 1.24  1994/07/06  04:58:50  franklin
 * 1. Added callbacks to set output file names.
 * 2. Disable/re-enable buttons that should not be accessible until something
 *    else happens (like successfuly reading in a Descartes spec.).
 * 3. Set the default values for all global filenames in this file.
 *    (set_global_filenames()).
 * 4. Add a default resource to contol the height of the animation viewingw
 *
 * Revision 1.23  1994/07/02  19:48:01  franklin
 * Add an italic font to the default fontlist.
 *
 * Revision 1.22  1994/07/02  17:11:35  franklin
 * Bring up dialog box with the names of researchers who have
 * worked on the definition of the language and/or on this
 * language processor.
 *
 * Revision 1.21  1994/06/29  03:00:17  franklin
 * Add support for the X11 "editres" program.
 *
 * Revision 1.20  1994/06/15  20:34:49  franklin
 * Execute the spec immediately if the user passes "-batch True"
 * on the command line. Exit immediately after execution if
 * the user pasess "-batch True -iconic True" on the command line.
 *
 * Revision 1.19  1994/06/15  18:35:11  franklin
 * 1. If the user specifies an input specification on the command line
 *    (-infile fname.des), then load the spec immediately.
 * 2. If the user passes "-iconic True" on the command line, then bring
 *    up the application in the iconified state.
 *
 * Revision 1.18  1994/06/15  17:19:07  franklin
 * Fix bug in stripping of leading path components from filename.
 *
 * Revision 1.17  1994/06/15  15:45:50  franklin
 * Add function reset_descartes_specname().
 *
 * Revision 1.16  1994/06/14  20:21:38  franklin
 * Install the most commonly used functions in the toolbar of the mainwindow.
 * Extablish callbacks for all of the pushbuttons under the "File->Open..."
 * menu (added read log, read input, and read output).
 * "Options->Show Default Resource Values" now lets you view the fallback
 * resources in a stand-alone mainwindow.
 * Re-arranged the widgets in the tool bar.
 *
 * Revision 1.15  1994/06/14  15:28:06  franklin
 * Add callbacks to view files listed under the "File->Open->Read XXX"
 * pulldown menu selections.
 * Add pushbutons in the toolbar area to 1. Load a Descartes
 * spec; 2. Run the spec; and 3. Exit the language processor.
 *
 * Revision 1.14  1994/06/12  04:42:04  franklin
 * Tidy up text widget sizes
 *
 * Revision 1.13  1994/06/11  16:28:59  franklin
 * Trace_Flag controls the amount of execution trace information
 * provided, not  the generation of the log file.  Change the
 * names of identifiers related to Trace_Flag so they reflect
 * this fact.
 *
 * Revision 1.12  1994/06/11  16:17:21  franklin
 * Control the global "Trace_Flag from main.c instead of wid1.c.  Set/unset the
 * flag with an XmToggleButton widget.
 *
 * Revision 1.11  1994/06/11  05:36:04  franklin
 * Move the scale widget which controls execution speed from wid1.c to main.c.
 *
 * Revision 1.10  1994/06/10  17:22:42  franklin
 * Change "View Somefile" to "Read Somefile" under the "File->Open" submenu.
 * Move the command to read the tree file from the "View" menu to the
 *   "File->Open" submenu.
 * Remove the option to change the Descartes spec name from the
 *   "Options->Set Filenames" menu.  We try to read the new spec
 *   as soon as we know its name.
 *
 * Revision 1.9  1994/06/10  16:32:14  franklin
 * Moved the "Set Filenames" submenu under the "Options" menu.  This makes it
 * more evident that the "Set Filenames" feature is optional -- the language
 * processor derives default names for input and output files from the name
 * of the Descartes specification you load.
 *
 * Revision 1.8  1994/06/10  12:54:26  franklin
 * Install sub-menus "File->Open->load_spec,view_otherfiles"
 * and "File->Set Filenames->descartes_spec,other_filenames".
 *
 * Revision 1.7  1994/06/09  23:03:15  franklin
 * 1. Use tight bindings for all fallback resources.
 * 2. Add fallback resources for the shell widget used to view files and any
 *    other text.
 *
 * Revision 1.6  1994/06/09  00:49:28  franklin
 * Use different default fonts.
 *
 * Revision 1.5  1994/06/08  03:34:50  franklin
 * 1. Get text widgets message_text and msghistory_text from
 *    wid1.c, since that module writes to them.
 * 2. The "Open" selection from the "File" menu now opens
 *    and processes a Descartes specification file directly.
 *
 * Revision 1.4  1994/06/08  01:50:14  franklin
 * Display the hoare tree file when the user selects "Display Tree..." from
 * the "view" pulldown menu.
 *
 * Revision 1.3  1994/06/07  21:58:38  franklin
 * 1. Added a paned window, which will eventually contain the message history
 *    text widget, and the drawing window (where the animation will be
 *    displayed).
 *
 * Revision 1.2  1994/06/07  19:12:05  franklin
 * Install callbacks for "Run" and "Open" selections under
 * the "File" pulldown menu.
 *
 * Revision 1.1  1994/06/07  15:39:12  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif

static char    *rcsid = "$Id: main.c,v 1.30, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4 1994/08/05 18:22:11 franklin Exp $";
static char    *sccsid = "@(#) Real-Time Descartes Language Processor";

#include <string.h>
#include <stdlib.h>
#include "cchk_missing_stdlib.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include "cchk_missing_unistd.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <sys/stat.h>		       /* Required by desc_struct.h */
#include <sys/ipc.h>		       /* NON POSIX.1 */
#include <sys/msg.h>		       /* NON POSIX.1 */

#ifdef __CLCC__

#ifdef __STDC__
#undef __STDC__
#endif

#define __STDC__ 1
#endif

#include <X11/Intrinsic.h>
#include <Xm/MainW.h>
#include <Xm/RowColumn.h>
#include <Xm/CascadeBG.h>
#include <Xm/PushBG.h>
#include <Xm/ToggleBG.h>
#include <Xm/MessageB.h>
#include <Xm/PanedW.h>
#include <Xm/Text.h>
#include <Xm/Scale.h>
#include <Xm/Form.h>
#include <Xm/LabelG.h>

#ifdef WORK_WITH_EDITRES
#include <X11/Xmu/Editres.h>	       /* Allows a user to modify application resources via the "edires" program included in the
				        * standard MIT X11R4 and X11R5 distribution.  This is a convenience only, if Editres.h
				        * and libXmu are not available, then turn this option off. */
#endif

#include "some_utils.h"
#include "command_line.h"	       /* Non-Xwindow command line switches.  Known as "custom application resources" in X
				        * documentation. */
#include "build_rtn.h"		       /* Show_Hoare_Tree() */
#include "mesg.h"		       /* wid1.h requires the definition of type "Mesg". */
#include "desc_struct.h"	       /* DESC_New_File_Name */
#include "hash.h"		       /* required by exec_rtn1.h */
#include "fifo.h"		       /* required by exec_rtn1.h */
#include "exec_rtn1.h"		       /* Animate_Flag */
#define INCLUDED_FROM_MAIN	1      /* Some functions in wid1.c are only referenced from this file.  Make the declarations of
				        * these functions visible. */
#include "wid1.h"
#include "main.h"


/*******************************************************************************
 * TYPEDEFS:	MAIN_PULLDOWN_IDX, FILE_MENU_IDX, VIEW_MENU_IDX,
 *		OPTIONS_MENU_IDX, and HELP_MENU_IDX
 *
 * Array indices for accessing pulldown menus on the main menu, and accessing
 * the selections under each menu.
 *
 * CRITICAL NOTE:	The order in which these indices appear MUST MATCH the
 *	order in which the instance names appear in the following arrays
 *	defined in main():
 *
 *		pulldown_instname_pfx[], file_pbutton_instname[],
 *		options_pbutton_instname[], view_pbutton_instname[],
 *		and help_pbutton_instname[].
 *
 *	Also note that pulldown_instname_pfx[] is used to generate instance
 *	names for the main menu pulldown menu widgets, and the main menu
 *	cascade button widgets.  This is a result of how Motif main menus are
 *	implemented.
 ******************************************************************************/

typedef enum
{
	FILE_IDX, VIEW_IDX, OPTIONS_IDX, HELP_IDX, MAIN_PULLDOWN_COUNT
}               main_pulldown_idx;
typedef enum
{
	OPEN_IDX, RUN_IDX, XEXIT_IDX, FILE_MENU_COUNT
}               file_menu_idx;
typedef enum
{
	ANIMATE_IDX, TOOLBAR_IDX, VIEW_MENU_COUNT
}               view_menu_idx;
typedef enum
{
	SET_FILENAMES_IDX, SET_TRACE_IDX, DEFAULT_X_RESOURCE_VALUES_IDX, OPTIONS_MENU_COUNT
}               options_menu_idx;
typedef enum
{
	OVERVIEW_IDX, PRODUCT_INFORMATION_IDX, HELP_MENU_COUNT
}               help_menu_idx;
typedef enum
{
	LOAD_DESCARTES_SPEC_IDX, READ_TREE_FILE_IDX, READ_LOG_FILE, READ_INPUT_FILE_IDX, READ_OUTPUT_FILE_IDX, FILE_OPEN_MENU_COUNT
}               file_open_menu_idx;
typedef enum
{
	LOG_FILE_IDX, INPUT_FILE_IDX, OUTPUT_FILE_IDX, OPTIONS_SET_FILENAMES_MENU_COUNT
}               options_set_filenames_menu_idx;

/*******************************************************************************
 * GLOBALS
 ******************************************************************************/
Widget          ttoplevel;	       /* The WMShellWidget parent of the Main Window */
XtAppContext    app;		       /* Xt application context.  See manpage of XtAppInitialize() */
char            p_name[128];
char            titlebar_text[256] = "Descartes Language Processor";	/* Update the title bar with the name of the current
									 * input specification file.  (Motif 1.2 Style Guide
									 * 6.2.5.1 File Menu Contents, pg 6-18. */
int             show_toolbar = True;   /* True if you want to see the scale widget for speeding up/slowing down execution. */
static Widget   ttoolbar_mgr;	       /* Manager widget of the XmScale that controls execution speed. */

/*
 * options_pbutton[], and file_pbtn[] file_open_pbtn[] are defined here,
 * instead of inside main(), because one of their members have to be
 * enabled/disabled when the user selects a new input specification.
 * (file_pbtn[RUN_IDX], file_open_pbtn[LOAD_DESCARTES_SPEC_IDX], and
 * options_pbutton[SET_FILENAMES_IDX])
 */
static Widget   options_pbutton[OPTIONS_MENU_COUNT];
static Widget   file_pbtn[FILE_MENU_COUNT];
static Widget   file_open_pbtn[FILE_OPEN_MENU_COUNT];
static Widget   run_btn;	       /* run_btn duplicates the function of file_pbtn[RUN_IDX].  It is declared globally,
				        * because it has to be disabled until a good specification has been loaded. */

/*******************************************************************************
 * DEFAULT X RESOURCE VALUES:
 *	These resources my be overridden by the user via the Xt resource
 *	mechanism (xrdb, .Xdefaults, XAPPLRESDIR) without changing this
 *	source code.  All the gory details of X resources are described in
 *	chapter 9 of "X Toolkit Intrinsics - C Language Interface, X Window
 *	System, X version 11, Release 5", which is included in the X11R5
 *	distribution available from ftp.x.org.
 ******************************************************************************/
static String   fallbacks[] = {
	"! Use a proportional width font for menus, buttons & stuff.",
	"Descartes*fontList:		*helvetica-bold-r-normal-*-*-140-*=master1,"
	"*helvetica-bold-r-normal--14-*=master2,"
	"*helvetica-medium-o-normal-*-*-140-*=small_italic,"
	"*helvetica-medium-r-normal-*-*-140-*=unbold",
	"! Use a fixed-width font for messages, and viewing file contents, so that columns"
	"! line up between lines of text.",
	"Descartes*XmText*fontList:	*courier-bold-r-normal-*-14-*=text",
	"! The following font is prettier.  If you have it on your system, then put"
	"! the next line in your .Xdefaults file."
	"!Descartes*XmText*fontList:	*prestige-medium-r-normal-*-*-128-*=text",
	"!",
	"! Main window pulldown menus",
	"Descartes.mainwindow.menubar.file_cbtn.labelString:	File",
	"Descartes.mainwindow.menubar.file_cbtn.mnemonic:	F",
	"Descartes.mainwindow.menubar.view_cbtn.labelString:	View",
	"Descartes.mainwindow.menubar.view_cbtn.mnemonic:	V",
	"Descartes.mainwindow.menubar.options_cbtn.labelString:	Options",
	"Descartes.mainwindow.menubar.options_cbtn.mnemonic:	O",
	"Descartes.mainwindow.menubar.help_cbtn.labelString:	Help",
	"Descartes.mainwindow.menubar.help_cbtn.mnemonic:	H",
	"!",
	"! Message hisory window below the drawing area",
	"Descartes.mainwindow.pane*history_text.rows:		6",
	"Descartes.mainwindow.pane*history_text.columns:	80",
	"!",
	"! Message window at the bottom of the Motif main window",
	"Descartes.mainwindow.message_text.columns:		80",
	"! We have to use class-names to access children of any menu widgets",
	"! created by the XmCreatePulldonwMenu() (or any other XmCreate[]Menu() call)",
	"! because the Motif library assigns an instance name for the XmMenuShell(),",
	"! not the programmer.  There is no way to determine this instance name",
	"! before runtime.",
	"!",
	"! File menu choices:",
	"Descartes.mainwindow.menubar.XmMenuShell.file_pmnu.open_pbtn.labelString:		Open...",
	"Descartes.mainwindow.menubar.XmMenuShell.file_pmnu.open_pbtn.mnemonic:			O",
	"Descartes.mainwindow.menubar.XmMenuShell.file_pmnu.run_pbtn.labelString:		Run",
	"Descartes.mainwindow.menubar.XmMenuShell.file_pmnu.run_pbtn.mnemonic:			R",
	"Descartes.mainwindow.menubar.XmMenuShell.file_pmnu.exit_pbtn.labelString:		Exit",
	"Descartes.mainwindow.menubar.XmMenuShell.file_pmnu.exit_pbtn.mnemonic:			x",
	"!",
	"! File->Open submenu choices",
	"Descartes.mainwindow.menubar.XmMenuShell.XmMenuShell.file_open_pulldown.load_descartes_spec.labelString:	"
	"Load Descartes Spec...",
	"Descartes.mainwindow.menubar.XmMenuShell.XmMenuShell.file_open_pulldown.load_descartes_spec.mnemonic: D",
	"Descartes.mainwindow.menubar.XmMenuShell.XmMenuShell.file_open_pulldown.read_tree_file.labelString:   Read Tree File...",
	"Descartes.mainwindow.menubar.XmMenuShell.XmMenuShell.file_open_pulldown.read_tree_file.mnemonic:      T",
	"Descartes.mainwindow.menubar.XmMenuShell.XmMenuShell.file_open_pulldown.read_log_file.labelString:    Read Log File...",
	"Descartes.mainwindow.menubar.XmMenuShell.XmMenuShell.file_open_pulldown.read_log_file.mnemonic:       L",
	"Descartes.mainwindow.menubar.XmMenuShell.XmMenuShell.file_open_pulldown.read_input_file.labelString:  Read Input File...",
	"Descartes.mainwindow.menubar.XmMenuShell.XmMenuShell.file_open_pulldown.read_input_file.mnemonic:     I",
	"Descartes.mainwindow.menubar.XmMenuShell.XmMenuShell.file_open_pulldown.read_output_file.labelString: Read Output File...",
	"Descartes.mainwindow.menubar.XmMenuShell.XmMenuShell.file_open_pulldown.read_output_file.mnemonic:    O",
	"!",
	"! View menu choices:  (Note: the Animate button is really an XmToggleButton)",
	"Descartes.mainwindow.menubar.XmMenuShell.view_pmnu.animate_pbtn.labelString:		Animation",
	"Descartes.mainwindow.menubar.XmMenuShell.view_pmnu.animate_pbtn.mnemonic:		A",
	"Descartes.mainwindow.menubar.XmMenuShell.view_pmnu.animate_pbtn.set:			True",
	"Descartes.mainwindow.menubar.XmMenuShell.view_pmnu.animate_pbtn.visibleWhenOff:	True",
	"Descartes.mainwindow.menubar.XmMenuShell.view_pmnu.toolbar_pbtn.labelString:		Tool Bar",
	"Descartes.mainwindow.menubar.XmMenuShell.view_pmnu.toolbar_pbtn.mnemonic:		T",
	"Descartes.mainwindow.menubar.XmMenuShell.view_pmnu.toolbar_pbtn.visibleWhenOff:		True",
	"Descartes.mainwindow.menubar.XmMenuShell.view_pmnu.toolbar_pbtn.set:			True",
	"!",
	"! Options menu choices:",
	"Descartes.mainwindow.menubar.XmMenuShell.options_pmnu.set_filenames_pbtn.labelString:	Set Filenames...",
	"Descartes.mainwindow.menubar.XmMenuShell.options_pmnu.set_filenames_pbtn.mnemonic:	n",
	"Descartes.mainwindow.menubar.XmMenuShell.options_pmnu.set_trace.labelString:		Trace Messages",
	"Descartes.mainwindow.menubar.XmMenuShell.options_pmnu.set_trace.mnemonic:		T",
	"Descartes.mainwindow.menubar.XmMenuShell.options_pmnu.set_trace.visibleWhenOff:	True",
	"Descartes.mainwindow.menubar.XmMenuShell.options_pmnu.set_trace.set:		True",
	"Descartes.mainwindow.menubar.XmMenuShell.options_pmnu.default_x_resource_values_pbtn.labelString:	"
	"Show Default X Resource Values...",
	"Descartes.mainwindow.menubar.XmMenuShell.options_pmnu.default_x_resource_values_pbtn.mnemonic:	D",
	"!",
	"! Options->Set Filenames submenu choices:",
	"Descartes.mainwindow.menubar.XmMenuShell.XmMenuShell.options_set_filenames_pmnu.log_file.labelString: Log File...",
	"Descartes.mainwindow.menubar.XmMenuShell.XmMenuShell.options_set_filenames_pmnu.log_file.mnemonic: L",
	"Descartes.mainwindow.menubar.XmMenuShell.XmMenuShell.options_set_filenames_pmnu.input_file.labelString: Input File...",
	"Descartes.mainwindow.menubar.XmMenuShell.XmMenuShell.options_set_filenames_pmnu.input_file.mnemonic: I",
	"Descartes.mainwindow.menubar.XmMenuShell.XmMenuShell.options_set_filenames_pmnu.output_file.labelString: Output File...",
	"Descartes.mainwindow.menubar.XmMenuShell.XmMenuShell.options_set_filenames_pmnu.output_file.mnemonic: O",
	"!",
	"! Help menu choices:",
	"Descartes.mainwindow.menubar.XmMenuShell.help_pmnu.overview_pbtn.labelString:			Overview",
	"Descartes.mainwindow.menubar.XmMenuShell.help_pmnu.overview_pbtn.mnemonic:			O",
	"Descartes.mainwindow.menubar.XmMenuShell.help_pmnu.product_information_pbtn.labelString:	Product Information",
	"Descartes.mainwindow.menubar.XmMenuShell.help_pmnu.product_information_pbtn.mnemonic:		P",
	"!",
	"! The toolbar has a scale for controlling execution speed, and pushbuttons to",
	"! access the most commonly used selections from the pulldown menus at the top",
	"! of the mainwindow.",
	"! Pushbuttons for quick access to the most common functions.",
	"Descartes.mainwindow.pane.ttoolbar_mgr.load_btn.labelString:	Load",
	"Descartes.mainwindow.pane.ttoolbar_mgr.load_btn.leftOffset:	3",
	"Descartes.mainwindow.pane.ttoolbar_mgr.run_btn.labelString:	Run",
	"Descartes.mainwindow.pane.ttoolbar_mgr.run_btn.leftOffset:	3",
	"Descartes.mainwindow.pane.ttoolbar_mgr.exit_btn.labelString:	Exit",
	"Descartes.mainwindow.pane.ttoolbar_mgr.exit_btn.leftOffset:	3",
	"!  Scale widget for controlling execution speed.",
	"Descartes.mainwindow.pane.ttoolbar_mgr.delay_scale.titleString:	Execution Speed",
	"!  Increase the following number if you need to slow down execution still further.",
	"Descartes.mainwindow.pane.ttoolbar_mgr.delay_scale.maximum:		50",
	"Descartes.mainwindow.pane.ttoolbar_mgr.delay_scale.minimum:		0",
	"Descartes.mainwindow.pane.ttoolbar_mgr.delay_scale.value:		0",
	"Descartes.mainwindow.pane.ttoolbar_mgr.delay_scale.processingDirection:	max_on_left",
	"Descartes.mainwindow.pane.ttoolbar_mgr.delay_scale.scaleWidth:	200",
	"Descartes.mainwindow.pane.ttoolbar_mgr.delay_scale.showValue:	False",
	"Descartes.mainwindow.pane.ttoolbar_mgr.slowlbl.labelString:	Slow",
	"Descartes.mainwindow.pane.ttoolbar_mgr.slowlbl.leftOffset:	10",
	"Descartes.mainwindow.pane.ttoolbar_mgr.slowlbl.rightMargin:	2",
	"Descartes.mainwindow.pane.ttoolbar_mgr.fastlbl.labelString:	Fast",
	"!",
	"! Height of the animation viewing window.",
	"Descartes.mainwindow.pane.scrollwin.height: 300",
	"!",
	"! Resources for secondary TopLevelShell used to display text in a standalone window:",
	"Descartes.display_text_shell.mainwindow.menubar.file_cbtn.labelString:				File",
	"Descartes.display_text_shell.mainwindow.menubar.file_cbtn.mnemonic:				F",
	"Descartes.display_text_shell.mainwindow.menubar.XmMenuShell.file_pmnu.exit_pbtn.labelString:	Exit",
	"Descartes.display_text_shell.mainwindow.menubar.XmMenuShell.file_pmnu.exit_pbtn.mnemonic:	x",
	"Descartes.display_text_shell.mainwindow.XmScrolledWindow.text_scrolled_window.rows:		24",
	"Descartes.display_text_shell.mainwindow.XmScrolledWindow.text_scrolled_window.columns:		80",

	NULL			       /* Mark the end of the list. */
};

/*******************************************************************************
 * FUNCTION:    SET_GLOBAL_FILENAMES
 *      Set new filenames based upon the name of the new input specification.
 *      Take something like /all/me/fred.des and generate:
 *       /all/me/fred.input /all/me/fred.output  ... and so on.
 ******************************************************************************/
static void     set_global_filenames (void)
{
	const char     *source_ptr;    /* Points into the pathname of the Descartes spec file. */
	const char     *base_fname;    /* Descartes file name without any directory name information. */
	int             extension_len; /* Length of any filename extension (including the period). */
	int             index_of_period;	/* Where to put the period of the filename extensions. */

	if ((DESC_New_File_Name == NULL) || (*DESC_New_File_Name == '\0'))
	{
		util_abort (__LINE__, __FILE__, "The name of the Descartes specification file must be set before calling\n"
			    "set_global_filenames().  DESC_New_File_Name = \"%s\"\n",
			    DESC_New_File_Name ? DESC_New_File_Name : "(NULL)");
	}

	strcpy (Input_File.name, DESC_New_File_Name);
	strcpy (Output_File.name, DESC_New_File_Name);
	strcpy (S_Output_File.name, DESC_New_File_Name);
	strcpy (W_Output_File.name, DESC_New_File_Name);
	strcpy (Log_File.name, DESC_New_File_Name);
	strcpy (Hoare_Table_Name, DESC_New_File_Name);

/*
 * Point to the end of the Descartes spec file name and work backwards; a
 * filename may contain more than 1 period.
 */
	extension_len = 0;
	base_fname = get_base_filename (DESC_New_File_Name);
	base_fname = get_base_filename (DESC_New_File_Name);
	source_ptr = base_fname + strlen (base_fname) - 1;	/* Character preceding the null terminator. */
	while ((*source_ptr != '.') && (source_ptr != base_fname))
	{
		++extension_len;
		--source_ptr;
	}
	if (source_ptr == base_fname)	/* Either there was no extension, or the specification was named "." */
		extension_len = 0;

	index_of_period = strlen (DESC_New_File_Name) - extension_len - 1;

	Input_File.name[index_of_period] = '\0';	/* Null terminate, so strcat() appends data where you think it will. */
	Output_File.name[index_of_period] = '\0';
	S_Output_File.name[index_of_period] = '\0';
	W_Output_File.name[index_of_period] = '\0';
	Log_File.name[index_of_period] = '\0';
	Hoare_Table_Name[index_of_period] = '\0';

	strcat (Input_File.name, INPUT_EXTENSION);
	strcat (Output_File.name, OUTPUT_EXTENSION);
	strcat (S_Output_File.name, S_OUTPUT_EXTENSION);
	strcat (W_Output_File.name, W_OUTPUT_EXTENSION);
	strcat (Log_File.name, LOG_EXTENSION);
	strcat (Hoare_Table_Name, TREE_EXTENSION);

	sprintf (User_Msg, "Input file:  \"%s\"\n", Input_File.name);
	Display_Build_User_Msg (NULL, User_Msg);
	sprintf (User_Msg, "Output file: \"%s\"\n", Output_File.name);
	Display_Build_User_Msg (NULL, User_Msg);
	sprintf (User_Msg, "Log file:    \"%s\"\n", Log_File.name);
	Display_Build_User_Msg (NULL, User_Msg);
}

/*******************************************************************************
 * FUNCTION:    RESET_DESCARTES_SPECNAME
 *	1. Copy new_spec_name into the global string DESC_New_File_Name.
 *	2. Strip off all leading pathname components from new_spec_name, and
 *	   append the resulting file name to the main window title bar text.
 *	3. Enable menu selections for reading input files.
 *	4. Enable "File->Open->Read Tree File" button, and the
 *	   "Options->Set Filenames" button.
 ******************************************************************************/
void            reset_descartes_specname (char *new_spec_name)
{
	char           *end_of_title;
	char           *find_tail;
	Arg             args[2];
	Cardinal        nargs;

/*
 * Assume that the language processor will not be able to build the hoare
 * tree, unless proven otherwise.
 */
	XtSetSensitive (file_open_pbtn[READ_TREE_FILE_IDX], False);
	XtSetSensitive (options_pbutton[SET_FILENAMES_IDX], False);
	XtSetSensitive (file_pbtn[RUN_IDX], False);
	XtSetSensitive (run_btn, False);

	if (new_spec_name && *new_spec_name)
	{
	/* Copy the new spec name to the global variable DESC_New_File_Name. */
		strcpy (DESC_New_File_Name, new_spec_name);

	/* Strip leading path components */
		find_tail = new_spec_name + strlen (new_spec_name);	/* Point to null terminator. */
		do
		{
			--find_tail;
		} while ((find_tail >= new_spec_name) && (*find_tail != '/'));
		if (find_tail < new_spec_name)
			find_tail = new_spec_name;
		if ((*find_tail == '/') && (*(find_tail + 1) != '\0'))
			++find_tail;

	/*
	 * Search for a colon at the end of the titlebar text, then append a
	 * space, followed by the new file name.
	 */
		end_of_title = titlebar_text + strlen (titlebar_text) - 1;
		while ((end_of_title >= titlebar_text) && (*end_of_title != ':'))
			--end_of_title;
		if (end_of_title < titlebar_text)
			end_of_title = titlebar_text;

		if (*end_of_title != ':')	/* If no colon, then this is the first call to this function.  Add a colon to the
						 * end. */
		{
			end_of_title = titlebar_text + strlen (titlebar_text);
			*end_of_title = ':';
		}
		++end_of_title;
		*end_of_title = ' ';
		++end_of_title;
		strcpy (end_of_title, find_tail);

	/*
	 * Load the spec into internal data structures.
	 */
		XtSetSensitive (file_open_pbtn[READ_TREE_FILE_IDX], False);
		XtSetSensitive (options_pbutton[SET_FILENAMES_IDX], False);
		XtSetSensitive (file_pbtn[RUN_IDX], False);
		XtSetSensitive (run_btn, False);
		if (Build_Proc ())
		{

			set_global_filenames ();	/* Builds default names from the name of the input specification. */

		/*
		 * If it was read in OK, then enable the "File->Open->Read
		 * Tree File" menu selection
		 */
			XtSetSensitive (file_open_pbtn[READ_TREE_FILE_IDX], True);
			XtSetSensitive (options_pbutton[SET_FILENAMES_IDX], True);
			XtSetSensitive (file_pbtn[RUN_IDX], True);
			XtSetSensitive (run_btn, True);
		/* Update the main windows titlebar */
		}
	}
	nargs = 0;
	XtSetArg (args[nargs], XmNtitle, titlebar_text);
	nargs++;
	XtSetValues (ttoplevel, args, nargs);
}

/*******************************************************************************
 * FUNCTION:	verify_exit_dialog_buttonpress_cb
 *	If the user presses the "OK" button on the verify exit dialog box, then
 *	terminate, and return a normal exit status to the operating system.
 ******************************************************************************/
static void     verify_exit_dialog_buttonpress_cb (Widget dummywidget, void *dummyptr1, XmPushButtonCallbackStruct * cbs)
{
	if (cbs->reason == XmCR_OK)
		exit (0);
}

/*******************************************************************************
 * FUNCTION:	verify_exit_dialog_cb
 *	According to the Motif style guide, you must have the user verify
 *	exiting the application.
 ******************************************************************************/
static void     verify_exit_dialog_cb (Widget dummywidget, void *dummyptr1, XmPushButtonCallbackStruct * dummyptr2)
{
	static Widget   quit_dialog = NULL;
	static char    *question_text = "Exit the Descartes Language Processor?";
	XmString        question;
	Arg             args[10];
	Cardinal        nargs;

/*
 * Create the dialog box on the first call to this function.  Re-use it on
 * subsequent calls.
 */
	if (quit_dialog == NULL)
	{

#ifdef MOTIF_1_2_AND_LATER
		question = XmStringCreateLocalized (question_text);
#else
		question = XmStringCreateLtoR (question_text, XmSTRING_DEFAULT_CHARSET);
#endif

		nargs = 0;
		XtSetArg (args[nargs], XmNtitle, titlebar_text);
		nargs++;
		XtSetArg (args[nargs], XmNmessageString, question);
		nargs++;
		XtSetArg (args[nargs], XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL);
		nargs++;
		quit_dialog = XmCreateQuestionDialog (ttoplevel, "dialog", args, nargs);
		XmStringFree (question);

	/* We do not need the "Help" button. */
		XtUnmanageChild (XmMessageBoxGetChild (quit_dialog, XmDIALOG_HELP_BUTTON));
		XtAddCallback (quit_dialog, XmNokCallback, (XtCallbackProc) verify_exit_dialog_buttonpress_cb, NULL);
	}


/* Display the dialog box. */
	XtManageChild (quit_dialog);
}

/*******************************************************************************
 * FUNCTION:	create_tool_bar
 *	Contains a scale widget to adjust execution speed, and push-buttons to
 *	heavily used function that are also accessible from the pulldown menus.
 *
 *	NOTE: As the value of Delay_Time increases, execution speed decreases.
 ******************************************************************************/
static void     update_delay (Widget scale_w, void *client_data, XmScaleCallbackStruct * cbs)
{
	Delay_Time = cbs->value;
	if (cbs->value)
		sprintf (User_Msg, "Delay at least %d milliseconds.\n", Delay_Time);
	else
		sprintf (User_Msg, "No delay.\n");
	Display_Build_User_Msg (NULL, User_Msg);
}
static void     create_tool_bar (Widget parent)
{
	Widget          delay_scale;
	Widget          slowlbl;
	Widget          fastlbl;
	Widget          load_btn,

/*
 * Note: run_btn is declared globally, because it has to be disabled until a
 * good specification has been loaded.
 */
	                exit_btn;
	Arg             args[8];
	Cardinal        nargs;

	ttoolbar_mgr = XmCreateForm (parent, "ttoolbar_mgr", NULL, 0);
	if (show_toolbar)
		XtManageChild (ttoolbar_mgr);

/*
 * This function is duplicated by file_open_pbtn[LOAD_DESCARTES_SPEC_IDX] in
 * main()
 */
	nargs = 0;
	XtSetArg (args[nargs], XmNtopAttachment, XmATTACH_FORM);
	nargs++;
	XtSetArg (args[nargs], XmNleftAttachment, XmATTACH_FORM);
	nargs++;
	load_btn = XmCreatePushButtonGadget (ttoolbar_mgr, "load_btn", args, nargs);
	XtAddCallback (load_btn, XmNactivateCallback, (XtCallbackProc) file_cb, &descartes_spec_file_selection_params);
	XtManageChild (load_btn);

/* This function is duplicated by file_pbtn[RUN_IDX] in main() */
	nargs = 0;
	XtSetArg (args[nargs], XmNleftWidget, load_btn);
	nargs++;
	XtSetArg (args[nargs], XmNleftAttachment, XmATTACH_WIDGET);
	nargs++;
	run_btn = XmCreatePushButtonGadget (ttoolbar_mgr, "run_btn", args, nargs);
	XtAddCallback (run_btn, XmNactivateCallback, (XtCallbackProc) exec_proc, NULL);
	XtManageChild (run_btn);
	XtSetSensitive (run_btn, False);	/* You cannot run a Descartes spec until you have successfully read one. */

/* This function is duplicated by file_pbtn[XEXIT_IDX] in main() */
	nargs = 0;
	XtSetArg (args[nargs], XmNleftWidget, run_btn);
	nargs++;
	XtSetArg (args[nargs], XmNleftAttachment, XmATTACH_WIDGET);
	nargs++;
	exit_btn = XmCreatePushButtonGadget (ttoolbar_mgr, "exit_btn", args, nargs);
	XtAddCallback (exit_btn, XmNactivateCallback, (XtCallbackProc) verify_exit_dialog_cb, NULL);
	XtManageChild (exit_btn);

/*
 * Put together the scale widget that controls execution speed, and its
 * labels.
 */
	nargs = 0;
	XtSetArg (args[nargs], XmNleftWidget, exit_btn);
	nargs++;
	XtSetArg (args[nargs], XmNleftAttachment, XmATTACH_WIDGET);
	nargs++;
	slowlbl = XmCreateLabelGadget (ttoolbar_mgr, "slowlbl", args, nargs);
	XtManageChild (slowlbl);

	nargs = 0;
	XtSetArg (args[nargs], XmNorientation, XmHORIZONTAL);
	nargs++;
	XtSetArg (args[nargs], XmNleftWidget, slowlbl);
	nargs++;
	XtSetArg (args[nargs], XmNleftAttachment, XmATTACH_WIDGET);
	nargs++;
	delay_scale = XmCreateScale (ttoolbar_mgr, "delay_scale", args, nargs);
	XtManageChild (delay_scale);

	XtAddCallback (delay_scale, XmNvalueChangedCallback, (XtCallbackProc) update_delay, NULL);

	nargs = 0;
	XtSetArg (args[nargs], XmNorientation, XmHORIZONTAL);
	nargs++;
	XtSetArg (args[nargs], XmNleftWidget, delay_scale);
	nargs++;
	XtSetArg (args[nargs], XmNleftAttachment, XmATTACH_WIDGET);
	nargs++;
	fastlbl = XmCreateLabelGadget (ttoolbar_mgr, "fastlbl", args, nargs);
	XtManageChild (fastlbl);

}

/*******************************************************************************
 * FUNCTION:	CONVERT_TO_INST_NAME
 ******************************************************************************/
char           *convert_to_inst_name (char *name, char *suffix)
{
	static char     instance_name_buf[128];
	char           *sp;	       /* Source pointer */
	char           *dp;	       /* Destination pointer */

/*
 * Use lower-case letters for widget instance names.  Only use alpha chars in
 * an instance name.
 */
	sp = name;
	dp = instance_name_buf;
	while (*sp)
	{
		if ((isalpha (*sp)) || (*sp == ' '))
		{
			if (*sp == ' ')
				*dp = '_';
			else
				*dp = tolower (*sp);
			++dp;
		}
		++sp;
	}
	*dp = '\0';
	strcat (instance_name_buf, suffix);
	return (instance_name_buf);
}

/*******************************************************************************
 * FUNCTION:	INSTALL_FILE_MENU_CALLBACKS
 ******************************************************************************/
static void     install_file_menu_callbacks (const Widget file_pbtn[FILE_MENU_COUNT],
					                     const Widget file_open_pbtn[FILE_OPEN_MENU_COUNT])
{

/*
 * file_pbtn[OPEN_IDX] references a sub-window which identifies which file to
 * open.
 */
	XtAddCallback (file_open_pbtn[LOAD_DESCARTES_SPEC_IDX], XmNactivateCallback, (XtCallbackProc) file_cb,
		       &descartes_spec_file_selection_params);
	XtAddCallback (file_open_pbtn[READ_TREE_FILE_IDX], XmNactivateCallback, (XtCallbackProc) Show_Hoare_Tree, NULL);
	XtAddCallback (file_open_pbtn[READ_LOG_FILE], XmNactivateCallback, (XtCallbackProc) file_cb,
		       &view_log_file_selection_params);
	XtAddCallback (file_open_pbtn[READ_INPUT_FILE_IDX], XmNactivateCallback, (XtCallbackProc) file_cb,
		       &view_input_file_selection_params);
	XtAddCallback (file_open_pbtn[READ_OUTPUT_FILE_IDX], XmNactivateCallback, (XtCallbackProc) file_cb,
		       &view_output_file_selection_params);

	XtAddCallback (file_pbtn[RUN_IDX], XmNactivateCallback, (XtCallbackProc) exec_proc, NULL);
	XtAddCallback (file_pbtn[XEXIT_IDX], XmNactivateCallback, (XtCallbackProc) verify_exit_dialog_cb, NULL);

}

/*******************************************************************************
 * FUNCTION:	INSTALL_VIEW_MENU_CALLBACKS
 ******************************************************************************/
static void     update_animate_flag (Widget widget, int *animate_flag, XmToggleButtonCallbackStruct * event)
{
	*animate_flag = event->set;    /* Update the global value "Animate_Flag" in exec_rtn1.c */
	if (drawing_a != NULL)
	{
		if (*animate_flag)
			XtManageChild (drawing_a);
		else
			XtUnmanageChild (drawing_a);
	}
}
static void     update_show_toolbar_mgr (Widget widget, int *show_toolbar, XmToggleButtonCallbackStruct * event)
{
	*show_toolbar = event->set;
	if (ttoolbar_mgr)
	{
		if (*show_toolbar)
			XtManageChild (ttoolbar_mgr);
		else
			XtUnmanageChild (ttoolbar_mgr);
	}
}
static void     install_view_menu_callbacks (const Widget view_pbutton[VIEW_MENU_COUNT])
{
	XtAddCallback (view_pbutton[ANIMATE_IDX], XmNvalueChangedCallback, (XtCallbackProc) update_animate_flag, &Animate_Flag);
	XtAddCallback (view_pbutton[TOOLBAR_IDX], XmNvalueChangedCallback,
		       (XtCallbackProc) update_show_toolbar_mgr, &show_toolbar);
}

/*******************************************************************************
 * FUNCTION:	INSTALL_OPTIONS_MENU_CALLBACKS
 ******************************************************************************/
static void     options_set_trace_flag_state (Widget widget, void *dummyptr, XmToggleButtonCallbackStruct * event)
{
	Trace_Flag = event->set;
}
static void     options_default_x_resource_values_cb (Widget widget, char *fallbacks[], XmPushButtonCallbackStruct * event)
{
	int             idx;
	growbuf_tt     *gbuf;
	char            newline_str[2];/* Use to append newlines to each character string in the array of fallback resource
				        * strings. */

	newline_str[0] = '\n';
	newline_str[1] = '\0';

	growbuf_init (&gbuf);
	growbuf_strcpy (gbuf, "");
	if (fallbacks)
	{
		idx = 0;
		while (fallbacks[idx])
		{
			growbuf_strcat (gbuf, fallbacks[idx]);
			growbuf_strcat (gbuf, newline_str);
			++idx;
		}
	}
	display_standalone_text ("Default Resources", growbuf_str (gbuf));
	growbuf_free (&gbuf);
}
static void     install_options_menu_callbacks (const Widget options_pbutton[OPTIONS_MENU_COUNT],
				                      const Widget options_set_filenames_pbtn[OPTIONS_SET_FILENAMES_MENU_COUNT])
{
	XtAddCallback (options_pbutton[SET_TRACE_IDX], XmNvalueChangedCallback,
		       (XtCallbackProc) options_set_trace_flag_state, NULL);
	XtAddCallback (options_pbutton[DEFAULT_X_RESOURCE_VALUES_IDX], XmNactivateCallback,
		       (XtCallbackProc) options_default_x_resource_values_cb, fallbacks);

/*
 * set_filename_cb() is the sub-callback that the file selection widget in
 * file_cb will invoke.
 */
	XtAddCallback (options_set_filenames_pbtn[LOG_FILE_IDX], XmNactivateCallback,
		       (XtCallbackProc) file_cb, &set_log_file_name_params);
	XtAddCallback (options_set_filenames_pbtn[INPUT_FILE_IDX], XmNactivateCallback,
		       (XtCallbackProc) file_cb, &set_input_file_name_params);
	XtAddCallback (options_set_filenames_pbtn[OUTPUT_FILE_IDX], XmNactivateCallback,
		       (XtCallbackProc) file_cb, &set_output_file_name_params);
}

/*******************************************************************************
 * FUNCTION:	INSTALL_HELP_MENU_CALLBACKS
 ******************************************************************************/
static void     install_help_menu_callbacks (const Widget options_pbutton[HELP_MENU_COUNT])
{
	XtAddCallback (options_pbutton[PRODUCT_INFORMATION_IDX], XmNactivateCallback,
		       (XtCallbackProc) rene_descartes, NULL);
}

/*******************************************************************************
 * FUNCTION:	MAIN
 *
 * NOTE:	Button label text is duplicated here AND in the resource
 *		settings in the global variable "fallbacks".  This allows the
 *		default settings to reside in the executable, and also
 *		allows the user to change resources via the X resource
 *		mechanism (XAPPLDEFAULTS, .Xinitrc, xrdb and so on).
 ******************************************************************************/


int             main (int argc, char *argv[])
{
	Widget          mainwindow;
	Widget          menubar;
	String          pulldown_instname_pfx[] = {"file", "view", "options", "help"};
	Widget          pulldown_menu[MAIN_PULLDOWN_COUNT];
	Widget          pulldown_cbtn[MAIN_PULLDOWN_COUNT];	/* XmCascadeButtons for each of the pulldown menus */
	String          file_pbutton_instname[] = {"open_pbtn", "run_pbtn", "exit_pbtn"};
	String          view_pbutton_instname[] = {"animate_pbtn", "toolbar_pbtn"};
	Widget          view_pbutton[VIEW_MENU_COUNT];
	String          options_pbutton_instname[] = {"set_filenames_pbtn", "set_trace", "default_x_resource_values_pbtn"};

/*
 * NOTE: options_pbutton[], file_pbtn[], and file_open_pbtn[] are defined
 * earlier in this file, because one of their members has to be
 * enabled/disabled when the user selects a new input specification.
 */
	String          help_pbutton_instname[] = {"overview_pbtn", "product_information_pbtn"};
	Widget          help_pbutton[HELP_MENU_COUNT];
	Widget          file_open_pulldown;	/* Submenu off of "File->" "Open".  Selects which file to open. */
	String          file_open_pbtn_instname[] = {"load_descartes_spec", "read_tree_file", "read_log_file", "read_input_file",
	"read_output_file"};
	Widget          options_set_filenames_pulldown;	/* Submenu off of "File->" "Set Filenames". Selects which filename to
							 * set. */
	String          options_set_filenames_instname[] = {"log_file", "input_file", "output_file"};
	Widget          options_set_filenames_pbtn[OPTIONS_SET_FILENAMES_MENU_COUNT];
	Widget          pane;	       /* Paned window holding the history text and the drawing area. */
	Arg             args[128];
	Cardinal        nargs;
	int             idx;	       /* Loop control */
	int             subidx;	       /* Nested subloop control */


	strcpy (p_name, argv[0]);	/* Save the program name. */
	ttoplevel = XtVaAppInitialize (&app, "Descartes", fetch_command_line_args_struct (),
				       fetch_num_commandline_args (),
				       &argc, argv, fallbacks, NULL);
	get_commandline_values (ttoplevel);
	install_shell_widgets_icon (ttoplevel);


#ifdef WORK_WITH_EDITRES
	XtAddEventHandler (ttoplevel, (EventMask) 0, True, _XEditResCheckMessages, NULL);
#endif

	mainwindow = XmCreateMainWindow (ttoplevel, "mainwindow", NULL, 0);
	XtManageChild (mainwindow);

	menubar = XmCreateMenuBar (mainwindow, "menubar", NULL, 0);
	XtManageChild (menubar);

	for (idx = 0; idx < MAIN_PULLDOWN_COUNT; idx++)
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

/*
 * See the comments for print_normal_shell_xwd_command() in wid1.c for a
 * description of what this does. All pulldown menus off of a menu bar will
 * share the same MenuShell widget, so you will not get a seperate widget id
 * for the MenuShells of the pulldown menus.  That is why I put the following
 * statement AFTER the FOR loop, instead of IN the FOR loop.
 */
	XtAddCallback (XtParent (pulldown_menu[0]), XmNpopupCallback, (XtCallbackProc) print_override_shell_xwd_command,
		       "mainmenupulldown");

/*
 * Tell the menu bar which one of the cascade buttons activates the "Help"
 * menu.
 */
	nargs = 0;
	XtSetArg (args[nargs], XmNmenuHelpWidget, pulldown_cbtn[HELP_IDX]);
	nargs++;
	XtSetValues (menubar, args, nargs);

/* Install selections for the "File" pulldown menu. */
	for (idx = 0; idx < FILE_MENU_COUNT; idx++)
	{
		if (idx == OPEN_IDX)	/* Install submenu for selecting wich file to open */
		{
		/* Do NOT manage the pulldown widget. */
			file_open_pulldown = XmCreatePulldownMenu (pulldown_menu[FILE_IDX], "file_open_pulldown", NULL, 0);

		/*
		 * See the comments for print_normal_shell_xwd_command() in
		 * wid1.c for a description of what this does.
		 */
			XtAddCallback (XtParent (file_open_pulldown), XmNpopupCallback,
				       (XtCallbackProc) print_override_shell_xwd_command, "file_open_pulldown");
			nargs = 0;
			XtSetArg (args[nargs], XmNsubMenuId, file_open_pulldown);
			nargs++;
			file_pbtn[idx] = XmCreateCascadeButtonGadget (pulldown_menu[FILE_IDX],
								      file_pbutton_instname[idx], args, nargs);
			XtManageChild (file_pbtn[idx]);
			for (subidx = 0; subidx < FILE_OPEN_MENU_COUNT; subidx++)
			{
				file_open_pbtn[subidx] = XmCreatePushButtonGadget (file_open_pulldown,
										   file_open_pbtn_instname[subidx], NULL, 0);
				XtManageChild (file_open_pbtn[subidx]);
			}

		/*
		 * Dont let anyone try to read a tree file until we
		 * succsessfully read an input specification.
		 */

			XtSetSensitive (file_open_pbtn[READ_TREE_FILE_IDX], False);
		}
		else
		{
			file_pbtn[idx] = XmCreatePushButtonGadget (pulldown_menu[FILE_IDX], file_pbutton_instname[idx], NULL, 0);
			XtManageChild (file_pbtn[idx]);
		}

	}

/*
 * Dont let anyone try to run a specification until we have read one first!
 */
	XtSetSensitive (file_pbtn[RUN_IDX], False);

/*
 * "View" menu selections.  The first and second buttons in the view menu,
 * are toggle buttons to enable/disable viewing the animation of the
 * execution of the Descartes specification, and the slider bar for slowing
 * down the animation. The rest of the buttons on the View menu, are regular
 * push buttons.
 */
	view_pbutton[ANIMATE_IDX] = XmCreateToggleButtonGadget (pulldown_menu[VIEW_IDX],
								view_pbutton_instname[ANIMATE_IDX], NULL, 0);
	XtManageChild (view_pbutton[ANIMATE_IDX]);
	view_pbutton[TOOLBAR_IDX] = XmCreateToggleButtonGadget (pulldown_menu[VIEW_IDX],
								view_pbutton_instname[TOOLBAR_IDX], NULL, 0);
	XtManageChild (view_pbutton[TOOLBAR_IDX]);
	for (idx = VIEW_MENU_COUNT; idx < VIEW_MENU_COUNT; idx++)
	{
		view_pbutton[idx] = XmCreatePushButtonGadget (pulldown_menu[VIEW_IDX], view_pbutton_instname[idx], NULL, 0);
		XtManageChild (view_pbutton[idx]);
	}
/* "Options" menu selections. */
	for (idx = 0; idx < OPTIONS_MENU_COUNT; idx++)
	{
		if (idx == SET_FILENAMES_IDX)
		{
		/* Do NOT manage the pulldown widget. */
			options_set_filenames_pulldown = XmCreatePulldownMenu (pulldown_menu[OPTIONS_IDX],
									       "options_set_filenames_pmnu", NULL, 0);

		/*
		 * See the comments for print_normal_shell_xwd_command() in
		 * wid1.c for a description of what this does.
		 */
			XtAddCallback (XtParent (options_set_filenames_pulldown), XmNpopupCallback,
				       (XtCallbackProc) print_override_shell_xwd_command, "options_set_filenames_pmnu");
			nargs = 0;
			XtSetArg (args[nargs], XmNsubMenuId, options_set_filenames_pulldown);
			nargs++;
			options_pbutton[idx] = XmCreateCascadeButtonGadget (pulldown_menu[OPTIONS_IDX],
									    options_pbutton_instname[idx], args, nargs);
			XtManageChild (options_pbutton[idx]);

		/*
		 * Dont bother setting output filenames until you have a good
		 * spec read; The default ouput names are overwritten
		 * whenever you read in a new spec.
		 */
			XtSetSensitive (options_pbutton[SET_FILENAMES_IDX], False);
			for (subidx = 0; subidx < OPTIONS_SET_FILENAMES_MENU_COUNT; subidx++)
			{
				options_set_filenames_pbtn[subidx] = XmCreatePushButtonGadget (options_set_filenames_pulldown,
									       options_set_filenames_instname[subidx], NULL, 0);
				XtManageChild (options_set_filenames_pbtn[subidx]);
			}
		}
		else if (idx == SET_TRACE_IDX)
		{

		/*
		 * Toggle button to determine whether or not to write a log
		 * file.
		 */
			options_pbutton[idx] = XmCreateToggleButtonGadget (pulldown_menu[OPTIONS_IDX],
									   options_pbutton_instname[idx], NULL, 0);
			XtManageChild (options_pbutton[idx]);
		}
		else
		{
			options_pbutton[idx] = XmCreatePushButtonGadget (pulldown_menu[OPTIONS_IDX],
									 options_pbutton_instname[idx], NULL, 0);
			XtManageChild (options_pbutton[idx]);
		}
	}
/* "Help" menu selections. */
	for (idx = 0; idx < HELP_MENU_COUNT; idx++)
	{
		help_pbutton[idx] = XmCreatePushButtonGadget (pulldown_menu[HELP_IDX], help_pbutton_instname[idx], NULL, 0);
		XtManageChild (help_pbutton[idx]);
	}

	nargs = 0;
	XtSetArg (args[nargs], XmNeditable, False);
	nargs++;
	XtSetArg (args[nargs], XmNeditMode, XmSINGLE_LINE_EDIT);
	nargs++;
	message_text = XmCreateText (mainwindow, "message_text", args, nargs);	/* Message window at bottom of MainMenu. */
	XtManageChild (message_text);

	pane = XtCreateWidget ("pane", xmPanedWindowWidgetClass, mainwindow, NULL, 0);
	XtManageChild (pane);

	create_tool_bar (pane);
	create_drawing_area (pane);

	nargs = 0;
	XtSetArg (args[nargs], XmNeditMode, XmMULTI_LINE_EDIT);
	nargs++;
	XtSetArg (args[nargs], XmNwordWrap, True);
	nargs++;
	XtSetArg (args[nargs], XmNblinkRate, 0);
	nargs++;
	XtSetArg (args[nargs], XmNautoShowCursorPosition, True);
	nargs++;
	XtSetArg (args[nargs], XmNcursorPositionVisible, True);
	nargs++;		/* Originally set to False */
	XtSetArg (args[nargs], XmNeditable, False);
	nargs++;
	msghistory_text = XmCreateScrolledText (pane, "history_text", args, nargs);
	XtManageChild (msghistory_text);

	XmMainWindowSetAreas (mainwindow, menubar, NULL, NULL, NULL, pane);
	nargs = 0;
	XtSetArg (args[nargs], XmNmessageWindow, message_text);
	nargs++;
	XtSetValues (mainwindow, args, nargs);

	install_file_menu_callbacks (file_pbtn, file_open_pbtn);
	install_view_menu_callbacks (view_pbutton);
	install_options_menu_callbacks (options_pbutton, options_set_filenames_pbtn);
	install_help_menu_callbacks (help_pbutton);

	reset_descartes_specname (fetch_infile_name ());
	if (fetch_iconic_switch ())
	{
		nargs = 0;
		XtSetArg (args[nargs], XmNinitialState, IconicState);
		nargs++;
		XtSetValues (ttoplevel, args, nargs);
	}

	XtRealizeWidget (ttoplevel);
/* The main window must be realized befor you can get a window ID for it. */
	print_normal_shell_xwd_command (ttoplevel, "mainwin", NULL);

	if (fetch_batch_switch ())
	{
	/* Try to execute the spec immediately. */
		exec_proc (NULL, NULL, NULL);	/* Usually invoked as a callback from a PushButton. */
		if (fetch_iconic_switch ())	/* If brought up as an icon, then just exit.  Otherwise, let the user have access
						 * to the interface. */
		{
			return (0);
		}
	}
	XtAppMainLoop (app);
	return (0);		/* Never executed, but this statement makes the compiler happy. */
}				       /* end main() */
