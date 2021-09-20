#ifndef DESC_TABLE_H
#define DESC_TABLE_H 1
/********************************************************************************
 * Program Name:	desc_table.h
 * Written Date:	Aug. 18, 1990
 * Modified Date:	Nov. 15, 1990
 * Designer:		Lih-shiun Timothy Lee  at ASU
 *
 * $Date: 1994/08/03 17:00:32 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/cmdline_ex/RCS/desc_table.h,v $
 *
 *******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: desc_table.h,v $
 * Revision 1.6  1994/08/03  17:00:32  franklin
 * Downcase "Error_Supplement" and "Error_Code", because the "E" prefix is
 * reserved by errno.h
 *
 * Revision 1.5  1994/05/23  18:27:04  franklin
 * Remove transition tables and message tables that are no longer used
 * anywhere.
 *
 * Revision 1.4  1994/04/22  04:57:08  franklin
 * The Gnu C compiler would not allow Tt_Array[][] to be defined
 * without first assigning a name to the structure/type of
 * its elements.  I added the name Tt_Array_t (and for grins, I
 * added a name for the struct -- Tt_Array_struct.
 *
 * Revision 1.3  1994/04/14  22:40:26  franklin
 * You cannot suppress the warning about "share_rtn_h_rcsid" not used, without
 * turning off all such warnings in a module which #includes this file.
 * Live with the message.
 *
 * Revision 1.2  1994/04/14  18:25:45  franklin
 * 1. Add RCS tokens.
 * 2. Add #defines to make sure this file is never #included more than once.
 *
 ******************************************************************************/
#endif
static char    *desc_table_h_rcsid = "@(#) $Id: desc_table.h,v 1.6, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3 1994/08/03 17:00:32 franklin Exp $";


/*
 * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 * The following information is joined as part of error codes to give the
 * complete meaning
 * 
 */

static char    *error_supplement[]
= {
	 /* 0 */ "Control Character",
	 /* 1 */ "Special Character",
	 /* 2 */ "Digit Number",
	 /* 3 */ "Upper-case Letter",
	 /* 4 */ "Lower-case Letter",
	 /* 5 */ "Carriage Return",
	 /* 6 */ "Blank",
	 /* 7 */ "Single Quote",
	 /* 8 */ "Underscore",
	 /* 9 */ "Left Parenthesis",
	 /* 10 */ "Right Parenthesis",
	 /* 11 */ "Period",
	 /* 12 */ "Asterisk",
	 /* 13 */ "Plus",
	 /* 14 */ "Pound Sign"
};

/*
 * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 * The following error codes are used to help the Descartes designer
 * understand what the error is and give the brief idea for the error; for
 * more details about the correction please refer to the action of error.
 * 
 */

static char    *error_code[] = {
	 /* 0 */ "",		       /* no error at all */
	 /* 1 */ "%s used is not part of reference node (or module title)",
	 /* 2 */ "invalid %s used for either reference or match node",
	 /* 3 */ "invalid %s used in literal node",
	 /* 4 */ "missing %s at the end of literal node",
	 /* 5 */ "an invalid %s occurred in literal node",
	 /* 6 */ "an invalid %s occurred in match node",
	 /* 7 */ "an invalid %s occurred in match node (direct product)",
	 /* 8 */ "an invalid %s occurred in match node (discriminated union)",
	 /* 9 */ "an invalid %s occurred in match node (sequence)",
	 /* 10 */ "an invalid %s occurred in match node (sequence union)",
	 /* 11 */ "an invalid %s occurred in match node (sequence range)",
	 /* 12 */ "illegal indentation occurred; must be a multiple of 5",
	 /* 13 */ "illegal format for sequence range; use either (1..100) or \
(1..) as example",
	 /* 14 */ "illegal lower bound; lower bound must be > 0",
	 /* 15 */ "illegal lower bound because lower bound > upper bound",
	 /* 16 */ "incomplete reference node",
	 /* 17 */ "an invalid %s occurred in reference node",
	"NOT  YET"
};

#endif				       /* DESC_TABLE_H; end if this file hasn't already been #included */
