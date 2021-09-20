/* @(#) fault.h 1.1@(#) Solbourne id 9/22/93 00:03:19 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*	@(#)fault.h 1.3 90/12/05 SMI	*/

/*
 * Copyright (c) 1983 by Sun Microsystems, Inc.
 */

#ifndef _sun_fault_h
#define	_sun_fault_h

/*
 * Where to go on fault in kernel mode
 * Zero means fault was unexpected
 */
#ifdef	solbourne
label_t	*nofault[MAXNCPUS];	/* longjmp vector */
#else	solbourne
label_t	*nofault;	/* longjmp vector */
#endif	solbourne

/*
 * Additional stuff for handling expected async faults;
 * used to communicate between poke*() and asyncerror()/memerr().
 *  0 means fault unexpected;
 * -1 means fault expected;
 *  1 means fault occured.
 */
#ifdef	solbourne
int	pokefault[MAXNCPUS];
#else	solbourne
int	pokefault;
#endif	solbourne

#if	defined(sun4c) || defined(sun4m) || defined(sun4d) ||  \
		defined(Series5) || defined(Series6) || defined(Series7)
void flush_writebuffers_to(/* addr_t v */);
void flush_all_writebuffers();
void flush_poke_writebuffers();

#else /* sun4c || sun4m || sun4d  || Series5 || Series6 || Series7  */
/* Not a machine with write buffers */
#define flush_writebuffers_to(v)
#define flush_all_writebuffers()
#define flush_poke_writebuffers();

#endif /* sun4c || sun4m || sun4d  || Series5 || Series6 || Series7 */


#endif /*!_sun_fault_h*/
