#ifndef CCHK_MISSING_STDLIB_H
#define CCHK_MISSING_STDLIB_H	1
/*******************************************************************************
 * MODULE:	CCHK_MISSING_STDLIB_H
 *
 * PURPOSE:	Provide function prototypes that CodeCheck doesn't see for
 *		some unknown reason.
 *
 * FUNCTIONS DECLARED
 *	EXTERNAL:	abort()
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 * $Author: franklin $
 *******************************************************************************
 * $Date: 1994/08/04 18:18:27 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/cchk_missing_stdlib.h,v $
 *
 ******************************************************************************/



#if 0
/******************************************************************************
 *
$Log: cchk_missing_stdlib.h,v $
 * Revision 1.2  1994/08/04  18:18:27  franklin
 * Shorten the RCS id variable name.
 *
 * Revision 1.1  1994/08/04  17:40:01  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif

static char    *cchk_missing_stdlib_h_rcsid = "$Id: cchk_missing_stdlib.h,v 1.2, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3 1994/08/04 18:18:27 franklin Exp $";

#ifdef CODECHECK
void            abort (void);

#endif

#endif				       /* CCHK_MISSING_STDLIB_H */
