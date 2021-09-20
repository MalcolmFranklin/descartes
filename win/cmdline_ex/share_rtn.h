#ifndef SHARE_RTN_H
#define SHARE_RTN_H	1
/*******************************************************************************
 * HEADER:	SHARE_RTN.H
 *
 * PURPOSE:	Contains declarations of external functions defined in
 *		share_rtn.c
 *
 * CREATED:	4/7/1994
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 *
 * NOTE:	This header file requires the definition of struct stat
 *		located in <unistd.h>
 *******************************************************************************
 * $Date: 1994/08/02 00:35:55 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/cmdline_ex/RCS/share_rtn.h,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: share_rtn.h,v $
 * Revision 1.10  1994/08/02  00:35:55  franklin
 * Change ERROR_EXISTED to XERROR_EXISTED.
 * Prefix E is reserved by ANSI.
 *
 * Revision 1.9  1994/08/02  00:32:59  franklin
 * Change continue_msg_t to continue_msg_tt.  Suffix "_t" is reserved by POSIX.1
 *
 * Revision 1.8  1994/07/05  02:09:58  franklin
 * Prettyprinter.
 *
 * Revision 1.7  1994/05/20  19:43:11  franklin
 * Remove NO_CORR_INPUT_ARGUMENT and its corresponding error message.
 * It would have been displayed only after this program performed
 * a nonsensical test.
 *
 * Revision 1.6  1994/04/23  16:52:48  franklin
 * Get the definition of struct stat from the POSIX standard "unistd.h"
 * instead of from "sys/stat.h":w
 *
 * Revision 1.5  1994/04/14  22:41:42  franklin
 * Move the definition of the diagnostic condition codes from alert_dcl.h
 * into this file, because they are used by Continue_Msg(), and Continue_Msg()
 * is defined in share_rtn.c.
 * Also: convert the codes from #defined macros to values of an enumerated tyype.
 * That way we can ensure that the definitions of the codes, and the messages
 * in the static array Alert_Msg[] (in share_rtn.c) are in the correct order.
 *
 * Revision 1.4  1994/04/14  22:09:35  franklin
 * You cannot suppress the warning about "share_rtn_h_rcsid" not used, without
 * turning off all such warnings in a module which #includes this file.
 * Live with the message.
 *
 * Revision 1.3  1994/04/14  18:26:33  franklin
 * Suppress ObjectCenter warnings about "static variable rcsid unused".
 *
 * Revision 1.2  1994/04/12  07:34:05  franklin
 * Remove #ifdef __STDC__.  All the code is now ANSI compliant.
 *
 * Revision 1.1  1994/04/08  06:49:32  franklin
 * Initial revision
 *
 * Revision 1.1  1994/04/08  04:56:01  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif

static char    *share_rtn_h_rcsid = "@(#) $Id: share_rtn.h,v 1.10, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3 1994/08/02 00:35:55 franklin Exp $";


int             Check_File (char *file_name);

struct stat     Get_File_Stat (char *file_name);

/******************************************************************************
 * FUNCTION:	Continue_Msg
 *	Pass an element from the type continue_msg_tt to Continue_Msg() to
 *	display a diagnostic message to the user.  The messages themselves
 *	are in a static array called Alert_Msg[] in share_rtn.c.
 *
 *	NOTE: the elements of type continue_msg_tt used to be #defined macros,
 *	      and they used to be in alert_dcl.h.  There is nothing else useful
 *	      in alert_dcl.h, so it is being removed from the build.
 *
 *	These changes were made on 4/14/1994 by Malcolm L. Franklin of ASU.
 ******************************************************************************/

/*
 * Values of type continue_msg_tt are passed to Continue_Msg() in order to
 * display an appropriate diagnostic message.
 */

typedef enum
{
	FILE_NAME_NEEDED,
	FILE_NOT_EXISTED,
	FILE_MODIFIED,
	BUILT_NOT_YET,
	BUILT_ALREADY,
	XERROR_EXISTED,
	OPENING_FILE_FAILED,
	HELP_NOT_EXISTED,
	INVALID_EXTENSION,
	INPUT_FILE_NOT_EXISTED,
	HOARE_TABLE_NOT_EXISTED,
	LOG_FILE_NOT_EXISTED
}               continue_msg_tt;

extern void     Continue_Msg (continue_msg_tt msg_no);

#endif				       /* SHARE_RTN_H (end if this file has already been #included) */
