#ifndef XDESC3_H
#define XDESC3_H	1
/*******************************************************************************
 * HEADER:	XDESC3.H
 *
 * PURPOSE:	Declare external functions defined in xdesc3.h
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 * $Author: franklin $
 *******************************************************************************
 * $Date: 1994/06/01 15:50:48 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/editor/RCS/xdesc3.h,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: xdesc3.h,v $
 * Revision 1.1  1994/06/01  15:50:48  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif

static char    *xdesc3_h_rcsid = "$Id: xdesc3.h,v 1.1 1994/06/01 15:50:48 franklin Exp $";

extern void     semantic_display (Widget w, XtPointer client_data, XmListCallbackStruct * cbs);
extern void     remove_semantic_listing (void);
extern void     semantic_analysis (Widget w, caddr_t client_data, XEvent * event_info);

#endif				       /* XDESC3_H; End if this file has not already been #included */
