#ifndef CCHK_MISSING_STDARG_H
#define CCHK_MISSING_STDARG_H	1
/*******************************************************************************
 * MODULE:	CCHK_MISSING_STDARG_H
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
 * $Date: 1994/08/04 21:57:28 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/cchk_missing_stdarg.h,v $
 *
 ******************************************************************************/



#if 0
/******************************************************************************
 *
$Log: cchk_missing_stdarg.h,v $
 * Revision 1.1  1994/08/04  21:57:28  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif

static char    *cchk_missing_stdarg_h_rcsid = "$Id: cchk_missing_stdarg.h,v 1.1, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3 1994/08/04 21:57:28 franklin Exp $";

#ifdef CODECHECK
#define va_arg(ap,type) (*(type*) NULL)
#define va_end(ap) ({;})
typedef struct
{
	unsigned int    bogus;
}               va_list;

#define va_start(ap,T) ({;})
#endif				       /* CODECHECK */

#endif				       /* CCHK_MISSING_STDARG_H */
