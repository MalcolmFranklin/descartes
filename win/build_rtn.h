#ifndef BUILD_RTN_H
#define BUILD_RTN_H	1
/*******************************************************************************
 * HEADER:	BUILD_RTN.H
 *
 * PURPOSE:	Contains declarations of external functions defined in
 *		build_rtn.c
 *
 * CREATED:	4/7/1994
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 *******************************************************************************
 * $Date: 1994/07/05 02:28:10 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/build_rtn.h,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: build_rtn.h,v $
 * Revision 1.11  1994/07/05  02:28:10  franklin
 * Build_Proc now returns TRUE if it was able to process the input spec.
 *
 * Revision 1.10  1994/06/15  16:18:10  franklin
 * Remove File_Modified flag.
 *
 * Revision 1.9  1994/06/15  15:44:16  franklin
 * Move Hoare_Table_Name to desc_struct.[hc]
 *
 * Revision 1.8  1994/06/09  01:31:49  franklin
 * Build_Proc() is no-longer a callback function.  It is invoked as
 * soon as the user provides a pathname to a readable Descartes
 * specification.
 *
 * Revision 1.7  1994/04/14  22:48:03  franklin
 * You cannot suppress the warning about "share_rtn_h_rcsid" not used, without
 * turning off all such warnings in a module which #includes this file.
 * Live with the message.
 *
 * Revision 1.6  1994/04/14  18:24:28  franklin
 * Suppress ObjectCenter warnings about "static variable rcsid unused".
 *
 * Revision 1.5  1994/04/12  07:24:53  franklin
 * Remove #ifdef __STDC__.  All the code is now ANSI compliant.
 *
 * Revision 1.4  1994/04/11  16:12:01  franklin
 * Add "extern" keyword to the declaration of Build_Proc().
 *
 * Revision 1.3  1994/04/10  21:57:48  franklin
 * Declare Build_Proc().  It is registered as a callback of an XmPushButton
 * widget.
 *
 * Revision 1.2  1994/04/09  20:28:10  franklin
 * Change the definitions of Show_Hoare_Tree() and Print_Hoare_Tree() to
 * match the parameters that they will be passed by the XmPushButton widget
 * that invokes them.  Note that as of this writing, these functions do not
 * use the data passed to them.
 *
 * Revision 1.1  1994/04/08  04:59:47  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif

static char    *build_rtn_h_rcsid = "@(#) $Id: build_rtn.h,v 1.11, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3, h4_3_2 1994/07/05 02:28:10 franklin Exp $";

extern void     Show_Hoare_Tree (Widget dummywidget, void *dummyptr1, XmPushButtonCallbackStruct * dummyptr2);

extern void     Print_Hoare_Tree (Widget dummywidget, void *dummyptr1, XmPushButtonCallbackStruct * dummyptr2);

extern int      Build_Proc (void);

#endif				       /* BUILD_RTN_H (end if this file has already been #included */
