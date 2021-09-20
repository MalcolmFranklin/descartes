#ifndef WID1_H
#define WID1_H	1
/*******************************************************************************
 * HEADER:	WID1.H
 *
 * PURPOSE:	Contains declarations of external functions defined in wid1.c
 *
 * CREATED:	4/7/1994
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 *
 * NOTE:	Type "Widget" is defined in <X11/Intrinsic.h>
 *		Type "Mesg" is defined in "mesg.h"
 *******************************************************************************
 * $Date: 1994/08/07 23:24:36 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/wid1.h,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: wid1.h,v $
 * Revision 1.24  1994/08/07  23:24:36  franklin
 * No more messages are passed via SysV queue, having the
 * key value (MSGKEY + 1).
 * This queue had been accessed via the message queue ID value stored
 * in the global "msgid".
 *
 * Revision 1.23  1994/08/06  19:30:49  franklin
 * Allow const pointers to message text, to be passed to
 * Display_Build_User_Msg().
 *
 * Revision 1.22  1994/08/05  18:23:53  franklin
 * Add parent2child parameter to parse().
 *
 * Revision 1.21  1994/08/04  00:06:13  franklin
 * Shut up a CodeCheck warning.  See commnents on #undef in analysis1.c for
 * details.
 *
 * Revision 1.20  1994/08/01  23:46:11  franklin
 * Suffix "_t" is reserved by POSIX.1
 *
 * Revision 1.19  1994/07/06  04:52:48  franklin
 * Add callbacks to set output file names.  Add the address of the global
 * filename to the struct passed (by reference) to the file selection box
 * callback.
 * Add utilities to print window IDs so you can grab bitmap images of the
 * applications menus.
 * Delete ex_button[].  No longer used.
 *
 * Revision 1.18  1994/07/02  19:48:20  franklin
 * Add protoytpe for rene_descartes(), a callback to post a dialog box
 * when th user presses Help->Product Information.
 *
 * Revision 1.17  1994/06/14  23:50:15  franklin
 * Add a function to clear the drawing area before
 * you load another specification.
 *
 * Revision 1.16  1994/06/14  21:21:29  franklin
 * Remove embedded non-printable character.
 *
 * Revision 1.15  1994/06/14  20:28:39  franklin
 * indent.
 *
 * Revision 1.13  1994/06/13  00:34:43  franklin
 * Delete the declaration of create_exec(); it has been replaced by
 * create_drawing_area().
 *
 * Revision 1.12  1994/06/09  23:07:11  franklin
 * Make dismiss_display_standalone_text_cb() visible to main.c.
 * Make create_drawing_area() visible to main.c -- we will use it later to
 * have main.c put the drawing area in the main window.
 *
 * Revision 1.11  1994/06/09  01:35:03  franklin
 * Delete create_rd_spec().  Its functionality has been replaced by code in
 * main.c.
 *
 * Revision 1.10  1994/06/08  03:38:50  franklin
 * Get text widgets message_text and msghistory_text from
 * wid1.c, instead of main.c, since the writes to the text
 * widgets are handled in wid1.c
 *
 * Revision 1.9  1994/06/07  21:54:13  franklin
 * 1. Register callback functions create_rd_spec() and
 *    create_exec() in main.c.
 * 2. Remove all references to global text widget Rd_text_w.
 *    This is the widget that used to be used for displaying
 *    the hoare tree table file.
 * 3. Put an "extern" keyword in front of the declaration of
 *    Display_Build_User_Msg().  it should have been there all along.
 *
 * Revision 1.8  1994/04/14  22:48:45  franklin
 * You cannot suppress the warning about "share_rtn_h_rcsid" not used, without
 * turning off all such warnings in a module which #includes this file.
 * Live with the message.
 *
 * Revision 1.7  1994/04/14  18:26:57  franklin
 * Suppress ObjectCenter warnings about "static variable rcsid unused".
 *
 * Revision 1.6  1994/04/12  07:42:48  franklin
 * Remove #ifdef __STDC__.  All the code is now ANSI compliant.
 * /
 *
 * Revision 1.5  1994/04/11  18:29:48  franklin
 * Remove declaration of create_para().  It was never called.
 *
 * Revision 1.4  1994/04/10  23:08:25  franklin
 * Move declarations for this modules external globals in to wid1.h.
 *
 * Revision 1.3  1994/04/09  22:34:19  franklin
 * Add declarations for the global data in wid1.c that is used in analysis1.c
 *
 * Revision 1.2  1994/04/08  06:25:32  franklin
 * Add prototype for parse().
 *
 * Revision 1.1  1994/04/08  04:56:01  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif

static char    *wid1_h_rcsid = "@(#) $Id: wid1.h,v 1.24, h4_3_8, h4_3_7, h4_3_6 1994/08/07 23:24:36 franklin Exp $";

/******************************************************************************
 * GLOBALS
 ******************************************************************************/
extern GC       gc;
extern GC       inv_gc;		       /* for inverse */
extern Dimension width;
extern Dimension height;
extern Widget   drawing_a;
extern Widget   rd_spec_text_w;
extern Pixmap   Current_pix;
extern Dimension win_width;
extern Dimension win_height;
extern Mesg     mesg_d;
extern int      Delay_Time;	       /* Set by new_value(), used by Delay_Checking() in exec_rtn1.c */

/******************************************************************************
 ******************************************************************************/
extern void     Display_Build_User_Msg (Widget text, const char *msg);
extern void     popup_error_dialog (const char *printf_fmt_str,...);
extern void     read_file (char *filename);
extern void     clear_drawing_area (void);	/* Erase the drawing area before drawing the next tree. */
extern void     install_shell_widgets_icon (Widget shellwidget);

#ifdef INCLUDED_FROM_EXEC_RTN1
extern void     parse (shared_fifodata_tt * parent2child);

#endif

/*
 * The following information is referenced in main().  Not all users of this
 * file have read the declaration of type XmPushButtonCallbackStruct
 */

#ifdef INCLUDED_FROM_MAIN
/* Default file name suffixes */
#define SPEC_EXTENSION          ".des" /* Descartes specification file. */
#define INPUT_EXTENSION         ".input"	/* Contains data to be processed by the Descartes specification. */
#define OUTPUT_EXTENSION        ".output"	/* Output generated by executing the Descartes specification. */
#undef S_OUTPUT_EXTENSION	       /* Shut up a CodeCheck warning. */
#define S_OUTPUT_EXTENSION      ".tmp" /* Workarea - not useful to the end-user. */
#define W_OUTPUT_EXTENSION      ".wk"  /* Workarea - not useful to the end-user. */
#define LOG_EXTENSION           ".log" /* A Descartes execution trace of a specification against an input file. */
#define TREE_EXTENSION           ".table"	/* A tablular description of the structure of the Hoare tree for a Descartes
						 * specification. */

typedef struct title_filter_subcallback_struct
{
	char           *file_dialog_title;	/* Titlebar text for XmFileSelectionDialog */
	char           *file_filter;   /* XmNpattern resource for the XmFileSelectionDialog.  ex, use "*.des" when looking for a
				        * Descartes specification. "*.log" when looking for a log file. */
	char           *filename_array;
	XtCallbackProc  ok_callback;   /* The XmNokCallback that the XmFileSelectionDialog box must call when/if the user selects
				        * a file. */
}               title_filter_subcallback_tt;

/* Load/Read these files */
extern title_filter_subcallback_tt descartes_spec_file_selection_params;
extern title_filter_subcallback_tt view_log_file_selection_params;
extern title_filter_subcallback_tt view_input_file_selection_params;
extern title_filter_subcallback_tt view_output_file_selection_params;

/*
 * Tell the language processor what names to write these files to (in case
 * you dont like the default name derived from the name of the Descartes
 * specification file).
 */
extern title_filter_subcallback_tt set_log_file_name_params;
extern title_filter_subcallback_tt set_input_file_name_params;
extern title_filter_subcallback_tt set_output_file_name_params;

extern Widget   message_text;	       /* Message text widget at the bottom of the MainWindow widget. */
extern Widget   msghistory_text;       /* Scrolling text window containing old messages. */
extern void     file_cb (Widget dummywidget, title_filter_subcallback_tt * title_and_filter, XmPushButtonCallbackStruct * dummyptr2);
extern void     set_filename_cb (Widget dialog, char *outfile_namptr, XmFileSelectionBoxCallbackStruct * cbs);
extern void     create_drawing_area (Widget parent);
extern void     display_standalone_text (char *title, char *text);
extern void     rene_descartes (Widget dummywidget, void *dummyptr1, XmPushButtonCallbackStruct * dummyptr2);
extern void     print_normal_shell_xwd_command (Widget wmshellwidget, char *base_fname, XmAnyCallbackStruct * dummyptr);
extern void     print_override_shell_xwd_command (Widget overrideshellwidget, char *base_fname, XmAnyCallbackStruct * dummyptr);

#endif				       /* INCLUDED_FROM_MAIN */

#endif				       /* WID1_H (end if this file has already been #included) */
