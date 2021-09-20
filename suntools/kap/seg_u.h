/* @(#) seg_u.h 1.1@(#) Solbourne id 9/22/93 00:03:58 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*	@(#)seg_u.h	1.1 88/03/29 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

/*
 * VM - U-area segment management
 *
 * This file contains definitions related to the u-area segment type.
 *
 * This segment type is not yet implemented.  The intent is that the
 * things defined here evolve into the seg_u implementation.
 */

#ifndef	_kap_seg_u_h
#define	_kap_seg_u_h

/*
 * The number of pages covered by a single seg_u slot.
 *
 * This value is the number of (software) pages in the u-area
 * (including the stack in the u-area) plus an additional page
 * for a stack red zone.  If the seg_u implementation is ever
 * generalized to allow variable-size stack allocation, this
 * define will have to change.
 */
#define	SEGU_PAGES	(UPAGES/CLSIZE)

/*
 * Private segment information for seg_u.
 *
 * At this stage of the implementation, we record only things that
 * formerly were part of the proc structure.
 *
 * XXX:	The parallel su_uaddr and su_swaddr arrays should perhaps
 * 	be combined into a single array of structures, but doing
 *	so requires more changes to genassym.c et al.
 *
 * N.B.: UPAGES is expressed in units of mmu pages.
 *
 * Note: since the struct user is separate from the kernel stack, the 
 * 	first entry in each of these arrays is for the struct user page
 *	and the rest of the entries are for the kernel stack pages.
 */
struct segu_data {
	long	su_uaddr[UPAGES];	/* XXX - really struct pte for
						   u area */
	struct	anon *su_swaddr[SEGU_PAGES];	/* disk address of u area when
						   swapped */
};

#ifdef	KERNEL
extern struct seg	segu;
extern struct segu_data	*segudata;

u_int	segu_swapout(/* sup */);
u_int	segu_swapin(/* sup */);
#endif	KERNEL

#endif	_kap_seg_u_h
