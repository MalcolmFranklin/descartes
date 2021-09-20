#ifndef XEXEC_RTN1_H
#define XEXEC_RTN1_H	1
/*******************************************************************************
 * HEADER:	EXEC_RTN1_H.H
 *
 * PURPOSE:	Contains declarations of external functions defined in
 *		exec_rtn1.c
 *
 * CREATED:	4/7/1994
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 *
 * NOTE:	Type "Widget" is defined in <X11/Intrinsic.h>
 *		Struct Template_Node is defined in "desc_struct.h"
 *		Enumerated types processing_situation_tt, and tree_tt are also
 *		defined in "desc_struct.h".
 *******************************************************************************
 * $Date: 1994/08/06 22:02:45 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/exec_rtn1.h,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: exec_rtn1.h,v $
 * Revision 1.21  1994/08/06  22:02:45  franklin
 * Rename childproc_popup_error_dialog() to client_popup_error_dialog().
 * Add clientXBell() and client_blink_window(), these will replace
 * Bell() and Blink_Window() in analysis1.c
 *
 * Revision 1.20  1994/08/05  18:21:07  franklin
 * Do not initialize child2parent in the declaration.  Only initialize it in
 * the definition in exec_rtn1.c
 *
 * Revision 1.19  1994/08/05  17:51:39  franklin
 * Add globals parent2child and child2parent.
 *
 * Revision 1.18  1994/08/03  18:29:22  franklin
 * Still trying to shut up CodeCheck diagnostics.  See #undefs in
 * analysis1.c for explaination.
 *
 * Revision 1.17  1994/08/03  16:43:37  franklin
 * Downcased function names beginning with "E", because the "E" prefix
 * is reserved by errno.h
 *
 * Revision 1.16  1994/08/03  16:07:41  franklin
 *  Shut up CodeCheck diagnostics.  See #undefs
 * in analysis1.c for explaination.
 *
 * Revision 1.15  1994/08/02  13:29:18  franklin
 * (E prefix is reserved by ANSI)
 *
 * Revision 1.14  1994/08/01  23:42:02  franklin
 * Suffix _t is reserved by POSIX.
 *
 * Revision 1.13  1994/07/08  00:07:23  franklin
 * Added childproc_popup_error_dialog(), a function allowing child proceses
 * to have the server popup an application-modal error dialog box.
 *
 * Revision 1.12  1994/07/06  04:49:11  franklin
 * Move definitions for filename extensions to wid1.h.
 * Moved Set_Global_Filenames() to main.c and named it "set_global_filenames()".
 * Use statically allocated arrays for filenames, so we can change filenames
 * without having to free & re-malloc storage.
 *
 * Revision 1.11  1994/07/01  17:59:38  franklin
 * Dont declare Output_File, S_Output_File, and W_Output_File twice.
 *
 * Revision 1.10  1994/06/14  15:41:41  franklin
 * Move #define constants for the expected file name suffixes from exec_rtn1.c
 * to exec_rtn1.h.  wid1.c needs these extensions so it can shorten the list
 * files presented in a FileSelectionDialog box.
 *
 * Revision 1.9  1994/06/11  18:23:46  franklin
 * 1. Abstract_Flag was never used.  Delete it.
 * 2. Draw_Flag and Preview_Flag are only referenced in
 *    exec_rtn1.c; do not declare them here
 *
 * Revision 1.8  1994/04/14  22:40:40  franklin
 * You cannot suppress the warning about "share_rtn_h_rcsid" not used, without
 * turning off all such warnings in a module which #includes this file.
 * Live with the message.
 *
 * Revision 1.7  1994/04/14  18:26:17  franklin
 * Suppress ObjectCenter warnings about "static variable rcsid unused".
 *
 * Revision 1.6  1994/04/12  07:32:19  franklin
 *  Remove #ifdef __STDC__.  All the code is now ANSI compliant.
 *
 * Revision 1.5  1994/04/11  22:06:46  franklin
 * Removed Canvas_Scrolling(); it was never used.
 * Added Stack_Save() and Stack_Restore() (used by analysis1.c)
 *
 * Revision 1.4  1994/04/11  20:46:59  franklin
 * Remove unused global Exec_Msg_Row
 *
 * Revision 1.3  1994/04/10  22:27:09  franklin
 * Fix syntax error.
 *
 * Revision 1.2  1994/04/10  22:16:10  franklin
 * Move the declarations for Exec_Draw() and Exec_Proc() here, so that
 * wid1.c can use them.
 *
 * Revision 1.1  1994/04/09  21:59:01  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif

static char    *exec_rtn1_h_rcsid = "@(#) $Id: exec_rtn1.h,v 1.21, h4_3_8, h4_3_7, h4_3_6 1994/08/06 22:02:45 franklin Exp $";

#undef Input_File		       /* Shut up CodeCheck diagnostics.  See #undefs in analysis1.c for explaination. */
#undef S_Input_File
#undef S_Input_File
#undef S_Output_File

/*******************************************************************************
 * TYPES & STRUCTS
 ******************************************************************************/

struct input_format
{
	char            name[1024];    /* input file name */
	char           *buffer;	       /* input buffer string */
	int             row,
	                col;	       /* used for moving input buffer string po inter */
	int             s_ptr;	       /* save the current pointer just in case of FAIL */
	int             c_ptr;	       /* indicator for pointing input buffer */
	FILE           *f_ptr;	       /* file pointer */
};

#undef S_Input_File
struct output_format
{
	char            name[1024];    /* output file name */
	int             c_ptr;
	FILE           *f_ptr;
};

#undef S_Output_File
struct log_format
{
	char            name[1024];
	FILE           *f_ptr;
};


/******************************************************************************
 * GLOBALS
 ******************************************************************************/

/*
 * FIFOs used to pass data from the execution subprocesses to the user
 * interface server process.
 */
extern shared_fifodata_tt *parent2child;
extern reply_fifodata_tt *child2parent;

/* Input_File for input string , S_Input_File for nothing */
extern struct input_format Input_File;
extern struct input_format S_Input_File;

/* S_Output_File for parameters, W_Output_File for non-return analysis trees */
extern struct output_format Output_File;
extern struct output_format S_Output_File;
extern struct output_format W_Output_File;

extern struct log_format Log_File;

extern int      Trace_Flag;
extern int      Animate_Flag;
extern int      Log_Flag;

/******************************************************************************
 * FUNCTIONS
 ******************************************************************************/
extern void     Display_Exec_Msg (char *msg);
extern void     client_popup_error_dialog (const char *printf_fmt_str,...);
extern void     clientXBell (void);
extern void     client_blink_window (void);

struct Stack_Node *Stack_Allocation (void);
extern void     Stack_Save (void);
extern void     Stack_Restore (void);
extern void     Inverse_Node_Edge (struct Template_Node * cur_node, int mode);
extern void     Inverse_Tree_Node (struct Template_Node * cur_node);
extern void     exec_run2 (void);
extern void     exec_draw (Widget dummywidget, void *dummyptr1, XmPushButtonCallbackStruct * dummyptr2);
extern void     exec_proc (Widget dummywidget, void *dummyptr1, XmPushButtonCallbackStruct * dummyptr2);

#endif				       /* XEXEC_RTN1_H (end if this file has already been #included) */
