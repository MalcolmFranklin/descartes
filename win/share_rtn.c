/*******************************************************************************
 *  Program Name:	share_rtn.c
 *  Written Date:	Jul. 11, 1990
 *  Modified Date:	Oct. 29, 1990
 *  Designer:		Lih-shiun Timothy Lee   at ASU
 *
 * $Date: 1994/08/02 00:36:29 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/share_rtn.c,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: share_rtn.c,v $
 * Revision 1.13  1994/08/02  00:36:29  franklin
 * Change ERROR_EXISTED to XERROR_EXISTED.
 * Prefix E is reserved by ANSI.
 *
 * Revision 1.12  1994/08/02  00:33:32  franklin
 * Change continue_msg_t to continue_msg_tt.  Suffix "_t" is reserved by POSIX.1.
 *
 * Revision 1.11  1994/07/05  02:10:15  franklin
 * Prettyprinter.
 *
 * Revision 1.10  1994/06/02  17:24:10  franklin
 * Enable stricter type checking when running the CenterLine "clcc" in
 * K&R compatibility mode (-Xa switch) by re-defining __STDC__ after processing
 * the non-ansi SunOS system include files.
 *
 * Revision 1.9  1994/05/20  19:44:22  franklin
 * Remove NO_CORR_INPUT_ARGUMENT and its corresponding error message.
 * It would have been displayed only after this program performed
 * a nonsensical test.
 * e
 *
 * Revision 1.8  1994/05/02  17:28:12  franklin
 * 1. Remove nested includes in desc_struct.h,  include unistd.h
 *    and sys/stat.h here.
 * 2. Re-run through SunOS "indent" utility.
 *
 * Revision 1.7  1994/04/23  16:54:30  franklin
 * Get the declarations of UNIX system calls (like access()) from the POSIX
 * standard unistd.h.  Delete #includes of <sys/types.h>, <sys/stat.h>, and
 * <sys/file.h>.
 *
 * Revision 1.6  1994/04/23  16:35:28  franklin
 * The declaration of access() is in unistd.h, not sys/file.h
 *
 * Revision 1.5  1994/04/14  22:44:48  franklin
 * Move the definition of the static array Alert_Msg[] from
 * alert_dcl.h in to this file (there is no good reason to store a static
 * data structure in a file #included by several other files.
 * Also: convert the array Alert_Msg[] from an array of strings, into an array
 * of structs, so that we can verify that the diagnostic messages appear
 * in the same order that the diagnostic codes are defined in.
 *
 * Revision 1.4  1994/04/11  22:24:19  franklin
 * ANSIfy function signatures.
 *
 * Revision 1.3  1994/04/08  05:57:01  franklin
 * Run through SunOS 4.1.3 "indent" program.
 *
 * Revision 1.2  1994/04/08  05:55:49  franklin
 * Remove code that is no longer used anywhere.
 *
 ******************************************************************************/
#endif
static char    *rcsid = "@(#) $Id: share_rtn.c,v 1.13, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3 1994/08/02 00:36:29 franklin Exp $";

#include <stdio.h>
#include <string.h>
#include <unistd.h>		       /* Declaration of access() */
#include <sys/stat.h>		       /* Required by desc_struct.h */
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

/*******************************************************************************
 * FUNCTION:	CHECK_FILE
 ******************************************************************************/
int             Check_File (char *file_name)
{

/* F_OK means that only existence of file will be checked */

	if (access (file_name, F_OK))  /* system returns -1 if not existed */
	{
		return 0;
	}
	else			/* system returns 0 if existed */
		return 1;
}

/*******************************************************************************
 * FUNCTION:	GET_FILE_STAT
 ******************************************************************************/
struct stat     Get_File_Stat (char *file_name)
{
	struct stat     statbuf;

	stat (file_name, &statbuf);	/* get the file status */
	return statbuf;
}

/*******************************************************************************
 * FUNCTION:	CONTINUE_MSG
 *	Seems to have been used at one time to popup a dialog box with an
 *	informational message.  When I took over this code in the Spring of
 *	1994, the function was called, but did nothing.  The comments in
 *	alert_dcl.h tipped me off as to what the original purpose of this
 *	function was.
 ******************************************************************************/

/*
 * Static array "Alert_Msg" contains the diagnostic messages displayed by
 * function Continue_Msg()
 */

struct alert_msg_struct
{
	continue_msg_tt offset;	       /* Verify that elements in array Alert_Msg[] are in the same order that type
				        * continue_msg_tt values appear in the type definition (typedef enum { ... }
				        * continue_msg_tt). */
	char           *msg_part1;     /* The messages for each diagnostic code in continue_msg_tt come in two parts. */
	char           *msg_part2;
};

static struct alert_msg_struct Alert_Msg[] = {
	FILE_NAME_NEEDED, "There is no file name given currently.",
	"Please return to <File> Button for a new file.",

	FILE_NOT_EXISTED, "File name does not exist in the current directory.",
	"Please confirm a file name with <File> button.",

	FILE_MODIFIED, "The file has been modified already just now.",
	"Please save or discard it before exit this window.",

	BUILT_NOT_YET, "The tree construction for the file has not built yet.",
	"Please do the tree building before proceed this button.",

	BUILT_ALREADY, "The tree construction for the file has built already.",
	"Please proceed other buttons except the one you click.",

	XERROR_EXISTED, "There is/are error(s) occurred at this moment.",
	"Please fix error(s) FIRST before proceed this button.",

	OPENING_FILE_FAILED, "The file failed in opening.",
	"Please check the file attribute and disk storage",

	HELP_NOT_EXISTED, "HELP file does not exist in the current directory.",
	"Please consult with the designer.",

	INVALID_EXTENSION, "The extension name for the file is invalid.",
	"Please check the extension name \".des\".",

	INPUT_FILE_NOT_EXISTED, "There is no corresponding input file for an input argument.",
	"Please check a file with an argument name & extension \".input\".",

	HOARE_TABLE_NOT_EXISTED, "There is no Hoare table file for the Hoare tree structure.",
	"Please proceed \"Show Hoare Tree\" before this button.",

	LOG_FILE_NOT_EXISTED, "There is no log file existed currently.",
	"Please set \"Create Log:\" to ON and do \"Run\" option."
};				       /* end static struct alert_msg_struct Alert_Msg[] */

void            Continue_Msg (continue_msg_tt msg_no)
{

/*
 * Verify that the Alert_Msg[] array and the definition of continue_msg_tt
 * are in the same order.
 */
	fflush (stderr);
	if (Alert_Msg[msg_no].offset != msg_no)
		printf ("INTERNAL ERROR: line %d file %s.\n\tThe definition of type continue_msg_tt and the order of\n"
			"messages in Alert_Msg[] are not in the correct order.\n"
			"The next message you see will probably not make sense.\n\n", __LINE__, __FILE__);
	puts (Alert_Msg[msg_no].msg_part1);
	puts (Alert_Msg[msg_no].msg_part2);
	fflush (stdout);
}
