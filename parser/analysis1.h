#ifndef ANALYSIS1_H
#define ANALYSIS1_H	1
/*******************************************************************************
 * HEADER:	ANALYSIS1.H
 *
 * PURPOSE:	Contains declarations of external functions defined in
 *		analysis1.c
 *
 * CREATED:	4/7/1994
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 *
 * NOTE:	Type "Widget" is defined in <X11/Intrinsic.h>
 *		Type "Pixmap" is defined in <X11/X.h>
 *		Struct Template_Node is defined in "desc_struct.h"
 *******************************************************************************
 * $Date: 1994/04/14 22:39:17 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/analysis1.h,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: analysis1.h,v $
 * Revision 1.6  1994/04/14  22:39:17  franklin
 * You cannot suppress the warning about "share_rtn_h_rcsid" not used, without
 * turning off all such warnings in a module which #includes this file.
 * Live with the message.
 *
 * Revision 1.5  1994/04/14  18:24:04  franklin
 * Suppress ObjectCenter warnings about "static variable rcsid unused".
 *
 * Revision 1.4  1994/04/12  07:19:48  franklin
 * Remove #ifdef __STDC__.  All the code is now ANSI compliant.
 *
 * Revision 1.3  1994/04/09  23:52:53  franklin
 * Move declarations of globals defined in analysis1.c, and used
 * by wid1.c to analysis1.h
 *
 * Revision 1.2  1994/04/09  23:00:45  franklin
 * The declaration of Get_Parameters() is needed by build_hoare_tree.c
 *
 * Revision 1.1  1994/04/08  06:48:18  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif

static char    *analysis1_h_rcsid = "@(#) $Id: analysis1.h,v 1.6 1994/04/14 22:39:17 franklin Exp $";

/*******************************************************************************
 * TYPES & STRUCTS
 ******************************************************************************/
struct pro_table
{
	char           *root_node;
	char           *Input_buffer;
	int             pid;
};

/******************************************************************************
 * GLOBALS
 ******************************************************************************/

extern struct pro_table pcb[5];	       /* Used by reset () in wid1.c */
extern int      p_cnt;		       /* process number.  Used in exec_rtn1.c and wid1.c  */
extern Pixmap   para[5];	       /* Used by des2.y, exec_rtn1.c, and wid1.c */


/******************************************************************************
 * DEFINES
 ******************************************************************************/
#define BACKWARD                0      /* backward drawing node edge */
#define FORWARD                 1      /* forward drawing node edge  */


/******************************************************************************
 ******************************************************************************/
extern void     Execution_Proc (struct Template_Node * cur_node);

/******************************************************************************
 ******************************************************************************/
extern void     Get_Parameters (void);

#endif				       /* ANALYSIS1_H (end if this file has already been #included) */
