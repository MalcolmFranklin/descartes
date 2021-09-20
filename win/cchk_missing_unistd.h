#ifndef CCHK_MISSING_UNISTD_H
#define CCHK_MISSING_UNISTD_H	1
/*******************************************************************************
 * MODULE:	CCHK_MISSING_UNISTD
 *
 * PURPOSE:	Provide function prototypes that CodeCheck doesn't see for
 *		some unknown reason.
 *
 * FUNCTIONS DECLARED
 *	EXTERNAL:	getpid()
 *			fork()
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 * $Author: franklin $
 *******************************************************************************
 * $Date: 1994/08/04 17:40:25 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/cchk_missing_unistd.h,v $
 *
 ******************************************************************************/



#if 0
/******************************************************************************
 *
$Log: cchk_missing_unistd.h,v $
 * Revision 1.1  1994/08/04  17:40:25  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif

static char    *cchk_missing_unistd_h_rcsid = "$Id: cchk_missing_unistd.h,v 1.1, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3 1994/08/04 17:40:25 franklin Exp $";

#ifdef CODECHECK
pid_t           getpid (void);
pid_t           fork (void);

#endif

#endif				       /* CCHK_MISSING_UNISTD_H	 */
