#ifndef CCHK_MISSING_SIGNAL_H
#define CCHK_MISSING_SIGNAL_H	1
/*******************************************************************************
 * MODULE:	CCHK_MISSING_SIGNAL_H
 *
 * PURPOSE:	Provide function prototypes that CodeCheck doesn't see for
 *		some unknown reason.
 *
 * FUNCTIONS DECLARED
 *	EXTERNAL:	signal()
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 * $Author: franklin $
 *******************************************************************************
 * $Date: 1994/08/04 17:39:19 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/cmdline_ex/RCS/cchk_missing_signal.h,v $
 *
 ******************************************************************************/



#if 0
/******************************************************************************
 *
$Log: cchk_missing_signal.h,v $
 * Revision 1.1  1994/08/04  17:39:19  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif

static char    *cchk_missing_signal_h_rcsid = "$Id: cchk_missing_signal.h,v 1.1, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3 1994/08/04 17:39:19 franklin Exp $";

#ifdef CODECHECK
void            (*signal (int sig, void (*action) (int))) (int);

#endif

#endif				       /* CCHK_MISSING_SIGNAL_H */
