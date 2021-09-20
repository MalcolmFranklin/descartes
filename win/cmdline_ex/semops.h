#ifndef SEMOPS_H
#define SEMOPS_H 1
/*******************************************************************************
 * HEADER:	SEMOPS.H
 *
 * PURPOSE:	Contains declarations of external functions defined in
 *		semops.c.
 *
 * CREATED:	5/1/1994 (under construction for a couple of weeks prior).
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 *
 * NOTE:	semops.c was called sem.c in Lih-Shiun Timothy Lee s
 *		Descartes language processor.
 *******************************************************************************
 * $Date: 1994/05/16 20:02:55 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/cmdline_ex/RCS/semops.h,v $
 *
 **-M**************************************************************************/

#if 0
/******************************************************************************
 *
$Log: semops.h,v $
 * Revision 1.5  1994/05/16  20:02:55  franklin
 * Use advisory record locks, which are POSIX.1 compliant, to
 * implement binary semaphores.
 *
 * Revision 1.4  1994/05/13  15:39:32  franklin
 * sem_rm() and sem_op() are ONLY called from withing semops.c.  Remove
 * their declarations from this header file.
 *
 * Revision 1.3  1994/05/03  18:03:49  franklin
 * Added comma before "..." in the function signature of semctl().
 *
 * Revision 1.2  1994/05/02  05:58:27  franklin
 * Dont nest includes within this file.
 * Move declaration of errno and perror() to sunos4_missing.h.
 *
 * Revision 1.1  1994/05/02  05:20:20  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif
static char    *semops_h_rcsid = "@(#) $Id: semops.h,v 1.5, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3, h4_3_2, h4_3_1, h4_3_0, h4_2_7, h4_2_6, h4_2_5, h4_2_4, h4_2_3 1994/05/16 20:02:55 franklin Exp $";

extern int      sem_create (void);
extern void     sem_wait (int id);
extern void     sem_signal (int id);
extern void     sem_delete (int id);

#endif				       /* You have not already #included semops.h */
