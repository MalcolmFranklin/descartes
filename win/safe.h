#ifndef SAFE_H
#define SAFE_H
/*******************************************************************************
 * HEADER:	SAFE.H
 *
 * PURPOSE:	Declarations of signal handlers, and utilities that are safe
 *		to call from within a signal handler (No writes to static
 *		storage, no side effects).
 *
 * AUTHOR:	Malcolm L. Franklin
 * $Author: franklin $
 *******************************************************************************
 * $Date: 1994/08/10 18:58:44 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/safe.h,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: safe.h,v $
 * Revision 1.3  1994/08/10  18:58:44  franklin
 * add sigpipe_handler().
 *
 * Revision 1.2  1994/08/10  18:09:23  franklin
 * 1. Add sigchild_handler() used in exec_rtn1.c
 * 2. indent.
 *
 * Revision 1.1  1994/08/10  17:22:33  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif

static char    *safe_h_rcsid = "$Id: safe.h,v 1.3, h4_3_8, h4_3_7 1994/08/10 18:58:44 franklin Exp $";

extern void     safe_int2string (int val, char buf[]);
extern void     safe_int2string_rj (int val, char buf[], int fieldwidth);
extern int      safe_strlen (const char buf[]);
extern int      safe_strcpy (char dest[], const char src[]);
extern void     timeout (int signo);
extern void     sigchild_handler (int signo);
extern void     sigpipe_handler (int signo);

#endif				       /* SAFE_H */
