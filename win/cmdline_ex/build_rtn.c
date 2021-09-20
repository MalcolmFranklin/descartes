/*******************************************************************************
 * Program Name:	build_rtn.c
 * Written Date:	Jul. 15, 1990
 * Modified Date:	Nov. 01, 1990
 * Designer:		Lih-shiun Timothy Lee at ASU
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: build_rtn.c,v $
 * Revision 1.36  1994/08/04  17:56:56  franklin
 * Add #includes for cchk_missing_<standard include>.h in order
 * to get prototypes that CodeCheck doesnt think are there.
 *
 * Revision 1.35  1994/08/03  17:09:24  franklin
 * Downcase "Error_Counter"; "E" prefix is reserved by errno.h
 *
 * Revision 1.34  1994/08/02  00:40:47  franklin
 * prefix E is reserved by ANSI.
 *
 * Revision 1.33  1994/07/06  04:42:35  franklin
 * Eliminated global flags Extension_Added and Tree_Show_Flag.
 * Removed function Extension_Check(), it served no useful purpose.
 * Set the Hoare tree file name in main.c instead of this file.
 *
 * Revision 1.32  1994/07/05  02:27:08  franklin
 * Allow a user to set input/output file names other than the default names
 * generated from the Descartes specification name.
 *
 * Revision 1.31  1994/06/30  23:24:19  franklin
 * Reset yylineno to 1 each time you read a new Descartes specification
 * Clarify the wording of some diagnostic messages.
 *
 * Revision 1.30  1994/06/15  18:37:10  franklin
 * Remove the global flag Build_Flag_4_New_File.
 * Change "File %s was modified" message to "Opening %s.".
 *
 * Revision 1.29  1994/06/15  16:17:13  franklin
 * Remove File_Modified and Build_Flag_4_Old_File.
 *
 * Revision 1.28  1994/06/15  15:43:19  franklin
 * Move the definition of Hoare_Table_Name[] to desc_struct.c
 *
 * Revision 1.27  1994/06/14  23:44:56  franklin
 * Clear the drawing area before loading another specification.
 *
 * Revision 1.26  1994/06/14  20:20:55  franklin
 * Corrections to comments.
 *
 * Revision 1.25  1994/06/09  01:30:29  franklin
 * Build_Proc() is no-longer a callback function.  It is invoked as
 * soon as the user provides a pathname to a readable Descartes
 * specification.
 *
 * Revision 1.24  1994/06/07  21:14:35  franklin
 * Only pass a filename to read_file().  read_file used to dump the file
 * contents into a text widget that was passed as a paremeter, now it
 * dumps the text into an independent shell widget.
 *
 * Revision 1.23  1994/06/02  17:23:21  franklin
 * Enable stricter type checking when running the CenterLine "clcc" in
 * K&R compatibility mode (-Xa switch) by re-defining __STDC__ after processing
 * the non-ansi SunOS system include files.
 *
 * Revision 1.22  1994/06/01  16:38:50  franklin
 * Remove unused auto variables in Read_Spec_And_Build_Tree().
 *
 * Revision 1.21  1994/05/24  02:02:57  franklin
 * ObjectCenter 2.0.2 detected that auto variable "percentage"
 * was initialized, but never used (when loading C source code
 * rather than object code).
 *
 * Revision 1.20  1994/05/13  02:47:52  franklin
 * Include need_before_ytab.h to get the definition of type NODE.
 *
 * Revision 1.19  1994/05/02  17:32:44  franklin
 * 1. This file DOES need to #include <sys/stat.h>.  This file
 *    is in the POSIX standard.
 *
 * Revision 1.18  1994/04/23  21:28:31  franklin
 * Remove the following CenterLine clcc warning messages:
 *    line 179: warning: yyparse: Function called but not declared.
 *    line 281: warning: system: Function called but not declared.
 *    line 121: warning: Variable "counter" is never referenced.
 *
 * Revision 1.17  1994/04/14  22:18:38  franklin
 * Remove #include alert_dcl.h.  The information once there is now in
 * share_rtn.h and share_rtn.c
 *
 * Revision 1.16  1994/04/10  21:56:17  franklin
 * Change the parameter list of Build_Proc() to match the actual parameters it
 * will be passed when invoked as a callback from an XmPushButton widget.
 * Move it's declaration to build_rtn.h (Called by wid1.c).
 *
 * Revision 1.15  1994/04/09  22:26:21  franklin
 * wid1.h requires the definition of type Mesg in mesg.h.  As of this writing,
 * that is the only reason this file #includes mesg.h
 *
 * Revision 1.14  1994/04/09  20:25:40  franklin
 * Change the definitions of Show_Hoare_Tree() and Print_Hoare_Tree() to
 * match the parameters that they will be passed by the XmPushButton widget
 * that invokes them.  Note that as of this writing, these functions do not
 * use the data passed to them.
 * Remove the parameter to Read_Spec_And_Build_Tree().  It is not passed
 * any parameters when invoked.
 *
 * Revision 1.13  1994/04/09  19:47:15  franklin
 * Removed #defines that were no longer needed.  Added "static" qualifier to
 * global variables and functions that are not used outside of this module.
 * Changed the command to print Hoare table file.  Old commands:
 *     #define       QUEUE_CMD  "lzpr -h ./%s -g %s"
 *     sprintf (User_Msg, QUEUE_CMD, Hoare_Table_Name, Hoare_Table_Name);
 *
 * Revision 1.12  1994/04/09  19:34:24  franklin
 * Added some comments.  Made function comment headers more consistent.
 * Re-ran through SunOS 4.1.3 "indent".
 *
 * Revision 1.11  1994/04/09  19:22:08  franklin
 * Remove declarations, defines, and function definitions that are not used
 * anywhere at all.
 *
 * Revision 1.10  1994/04/09  18:52:51  franklin
 * Remove declarations and macros that are no longer used in this file.
 *
 * Revision 1.9  1994/04/09  18:46:20  franklin
 * Change "short"s to "int"s to prevent conflicts when linking between
 * ANSI/ISO Standard C and K&R C modules and libraries.
 *
 * Revision 1.8  1994/04/09  18:34:04  franklin
 * Remove declarations now read from build_hoare_tree.h
 *
 * Revision 1.7  1994/04/09  18:31:18  franklin
 * Remove declarations of functions now declared in share_rtn.h.
 *
 * Revision 1.6  1994/04/09  18:29:08  franklin
 * Remove references to old sunview utilities that used to be
 * defined in share_var.c
 *
 * Revision 1.5  1994/04/09  18:25:46  franklin
 * (I forgot to list Display_Build_User_Msg() in the
 *  previous checkin comment).
 *
 * Revision 1.4  1994/04/09  18:23:22  franklin
 * Remove external declaration of Screen_Col.  It was not used
 *    in this file.
 * Remove external declarations of functions declared in wid1.h
 *     read_file(), rd_spec_text_w(), Rd_text_w
 *
 * Revision 1.4  1994/04/09  18:23:22  franklin
 * Remove external declaration of Screen_Col.  It was not used
 *    in this file.
 * Remove external declarations of functions declared in wid1.h
 *     read_file(), rd_spec_text_w(), Rd_text_w
 *
 * Revision 1.3  1994/04/09  18:19:41  franklin
 * Add RCS tokens.
 *
 ******************************************************************************/
#endif
static char    *rcsid = "@(#) $Id: build_rtn.c,v 1.36, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3 1994/08/04 17:56:56 franklin Exp $";

#include <stdlib.h>		       /* system() */
#include "cchk_missing_stdlib.h"        /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <stdio.h>
#include <string.h>
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

#include <Xm/Text.h>

#include "desc_struct.h"
#include "need_before_ytab.h"
#include "y.tab.h"
#include "mesg.h"		       /* Required by wid1.h */
#include "wid1.h"
#include "share_rtn.h"
#include "build_hoare_tree.h"
#include "some_utils.h"
#include "build_rtn.h"

/* Note: the following should have been declared in y.tab.h. */
int             yyparse (void);

/*******************************************************************************
 * GLOBALS
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION:	READ_SPEC_AND_BUILD_TREE
 ******************************************************************************/

static void     Read_Spec_And_Build_Tree (void)
{
	int             file_size;

	sprintf (User_Msg, "Opening %s.\n", DESC_New_File_Name);
	Display_Build_User_Msg (rd_spec_text_w, User_Msg);
	Free_Hoare_Tree (Hoare_Root_Dummy);

	if ((DESC_File_Ptr = freopen (DESC_New_File_Name, "r", stdin)) == NULL)
	{
		Continue_Msg (OPENING_FILE_FAILED);
		return;
	}

	DESC_File_Stat = Get_File_Stat (DESC_New_File_Name);
	file_size = DESC_File_Stat.st_size;

	sprintf (User_Msg, "Length of file %s is %d bytes.\n",
		 DESC_New_File_Name, file_size);
	Display_Build_User_Msg (rd_spec_text_w, User_Msg);

	sprintf (User_Msg, "Parsing %s.\n", DESC_New_File_Name);
	Display_Build_User_Msg (rd_spec_text_w, User_Msg);

/* initializtio=ns for the tree building; see the following function */
	Hoare_Root_Dummy = Allocate_Hoare_Root_Dummy ();
	pre_root = Hoare_Root_Dummy;
	Screen_Row = 80;
	yylineno = 1;		/* Reset to 1 before EACH call to yyparse() so that the correct line numbers are reported in
				 * error messages from yyerror(). */
	yyparse ();

	fclose (DESC_File_Ptr);
/* Hoare_Root of first module    */
	Hoare_Root_Dummy = Hoare_Root_Dummy->front;
	F_Hoare_Root_Dummy = Hoare_Root_Dummy;

	sprintf (User_Msg, "File %s is closed\n", DESC_New_File_Name);
	Display_Build_User_Msg (rd_spec_text_w, User_Msg);

	if (!error_counter)
	{
		Scan_Tree_For_Seq (Hoare_Root_Dummy->level_point);
		sprintf (User_Msg, "No syntax error(s).\n");
	}
	else
		sprintf (User_Msg, "%d syntax error(s) detected.\n", error_counter);

	Display_Build_User_Msg (rd_spec_text_w, User_Msg);
}

/*******************************************************************************
 * FUNCTION:    SHOW_HOARE_TREE
 *      Write the hoare tree file to disk, then load the file into a stand-
 *      alone mainwindow widget, by calling read_file() in wid1.c.
 ******************************************************************************/
void            Show_Hoare_Tree (Widget dummywidget, void *dummyptr1, XmPushButtonCallbackStruct * dummyptr2)
{
	struct Template_Node *Root_Dummy;

	if (error_counter)
	{
		Continue_Msg (XERROR_EXISTED);
		return;
	}

/**window_set(Build_Tree_Textsw, TEXTSW_READ_ONLY, FALSE, 0);**/
	Generate_String_Format (Max_Name_Size);

	Write_Hoare_Tree (Hoare_Root_Dummy->level_point);	/* from 1st node */
	Root_Dummy = Hoare_Root_Dummy->front;
	while (Root_Dummy)
	{
		Write_Hoare_Tree (Root_Dummy->level_point);	/* from 1st node */
		Root_Dummy = Root_Dummy->front;
	}

	Free_String_Format ();

	read_file (Hoare_Table_Name);
}

/*******************************************************************************
 * FUNCTION:
 *	Invoked as a Callback function from an XmPushButton widget in wid1.c
 *	This function does not use the parameters passed to it from the
 *	XmPushButton widget.
 ******************************************************************************/

void            Print_Hoare_Tree (Widget dummywidget, void *dummyptr1, XmPushButtonCallbackStruct * dummyptr2)
{
#define	QUEUE_CMD  "enscript -rG %s "  /* ASU custom-made printing utility */

	if (error_counter)
	{
		Continue_Msg (XERROR_EXISTED);
		return;
	}

	if (!Check_File (Hoare_Table_Name))
	{
		Continue_Msg (HOARE_TABLE_NOT_EXISTED);
		return;
	}

	sprintf (User_Msg, "queue a file to a local printer; please wait ..\n");
	Display_Build_User_Msg (rd_spec_text_w, User_Msg);
	sprintf (User_Msg, QUEUE_CMD, Hoare_Table_Name);
	Display_Build_User_Msg (rd_spec_text_w, User_Msg);
	system (User_Msg);
	sprintf (User_Msg, "\nPlease check the printout at your local printer.\n");
	Display_Build_User_Msg (rd_spec_text_w, User_Msg);
}

/*******************************************************************************
 * FUNCTION:	Build_Proc
 *
 * PURPOSE:	Load an input Descartes specification file into internal
 *		data structures.
 * SIDE EFFECTS:
 *              1. Clears the drawing area of any previously displayed Hoare
 *                 tree.
 *              2. If you did not specify an input spec on the command line,
 *                 then any menu choices for reading/viewing an output file
 *                 are disabled until you call this function at least once.
 *
 * RETURNS:     Nonzero (TRUE) if the spec was read without errors by yyparse()
 *
 * NOTE:	This function was originally invoked as a push-button callback.
 *		The language processor now immediately loads the input
 *		specification after it has verified that it can read the file.
 ******************************************************************************/

int             Build_Proc (void)
{
	int             good_fname;
	const char     *base_desc_filename;	/* Points to the base filename within a full pathname. */

	good_fname = TRUE;
	clear_drawing_area ();
	if (!DESC_New_File_Name || !strlen (DESC_New_File_Name))	/* no file name at all */
	{
		popup_error_dialog ("No filename provided.\nPlease select an input specification.");
		good_fname = FALSE;
	}
	else
	{
		base_desc_filename = get_base_filename (DESC_New_File_Name);

		if (!Check_File (DESC_New_File_Name))
		{
			popup_error_dialog ("Could not find a file named:\n\"%s\"\nPlease chose another file.",
					    base_desc_filename ? base_desc_filename : "(NULL)");
			good_fname = FALSE;
		}

		if (good_fname)
		{
			Read_Spec_And_Build_Tree ();
		}
	}
	return (good_fname && (!error_counter));
}
