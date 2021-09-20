#ifndef SUNOS4_MISSING_H
#define SUNOS4_MISSING_H 1
/*******************************************************************************
 * HEADER:	SUNOS4_MISSING.H
 *
 * PURPOSE:	Declarations of functions and globals that SHOULD have been
 *		in the SunOS 4.x standard #include files, but were NOT!
 *
 * CREATED:	5/1/1994
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 *******************************************************************************
 * $Date: 1994/06/01 16:42:44 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/cmdline_ex/RCS/sunos4_missing.h,v $
 *
 **-M**************************************************************************/

#if 0
/******************************************************************************
 *
$Log: sunos4_missing.h,v $
 * Revision 1.4  1994/06/01  16:42:44  franklin
 * SunOS 4.x does NOT have the declaration of "time()" in <time.h>.
 *
 * Revision 1.3  1994/05/16  22:46:21  franklin
 * The declaration of "errno" was causeing CDE 1.1b to abort when running
 * with ObjectCenter 2.0.2.
 *
 * Revision 1.2  1994/05/16  21:04:31  franklin
 * Remove obsolete comments about sys/sem.h
 *
 * Revision 1.1  1994/05/02  06:00:08  franklin
 * Initial revision
 *
 *
 ******************************************************************************/
#endif
static char    *sunos4_missing_h_rcsid = "@(#) $Id: sunos4_missing.h,v 1.4, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3, h4_3_2, h4_3_1, h4_3_0, h4_2_7, h4_2_6, h4_2_5, h4_2_4 1994/06/01 16:42:44 franklin Exp $";

#ifdef sun			       /* Value of the PLATSPEC macro in makefile */

/******************************************************************************
 * On POSIX-compliant systems, errno and perror() are declared in errno.h
 ******************************************************************************/
/* extern int      errno; declaring "errno" causes the IdE CDE tool to bomb. */
extern void     perror (const char *s);

/******************************************************************************
 * ANSI/ISO C requires the prototype of "time()" to be in <time.h>
 ******************************************************************************/
extern time_t time (time_t *tod);

#endif /* This is a SunOS 4.x compilation. */


#endif				       /* SUNOS4_MISSING_H */
