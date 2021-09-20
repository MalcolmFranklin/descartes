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
 * $Date: 1994/04/14 22:48:45 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/wid1.h,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: wid1.h,v $
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

static char    *wid1_h_rcsid = "@(#) $Id: wid1.h,v 1.8 1994/04/14 22:48:45 franklin Exp $";

/******************************************************************************
 * GLOBALS
 ******************************************************************************/
extern GC       gc;
extern GC       inv_gc;		       /* for inverse */
extern Dimension width;
extern Dimension height;
extern Widget   drawing_a;
extern Widget   rd_spec_text_w;
extern Widget   Rd_text_w;
extern Pixmap   Current_pix;
extern Widget   ex_button[5];
extern Dimension win_width;
extern Dimension win_height;
extern Mesg     mesg_d;
extern int      msgid;
extern int      Delay_Time;	       /* Set by new_value(), used by Delay_Checking() in exec_rtn1.c */

/******************************************************************************
 ******************************************************************************/
void            Display_Build_User_Msg (Widget text, char *msg);

extern void     read_file (Widget text_w, char *filename);

extern void     parse (void);

#endif				       /* WID1_H (end if this file has already been #included */
