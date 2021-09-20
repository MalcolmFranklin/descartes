/* @(#) zscom.h 1.1@(#) Solbourne id 9/22/93 00:10:24 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */
/*    @(#)zscom.h 1.15 89/06/28 SMI      */

/*
 * Copyright (c) 1984 by Sun Microsystems, Inc.
 */

/*
 * Support common to all users of Z8530 devices
 */

#ifndef _sundev_zscom_h
#define _sundev_zscom_h

/*
 * Interrupt vectors - per protocol
 */
struct zsops {
	int	(*zsop_attach)();	/* attach protocol */
	int	(*zsop_txint)();	/* xmit buffer empty */
	int	(*zsop_xsint)();	/* external/status */
	int	(*zsop_rxint)();	/* receive char available */
	int	(*zsop_srint)();	/* special receive condition */
	int	(*zsop_softint)();	/* process software interrupt */
};

/*
 * Common data
 */
struct zscom {
	int	(*zs_vec[4])();		/* vector routines - must be first */
	struct zscc_device *zs_addr;	/* address of half of chip  - second */
	short	zs_unit;		/* which channel (0:NZSLINE) */
	caddr_t	zs_priv;		/* protocol private data */
	struct zsops *zs_ops;		/* intr op vector */
	u_char	zs_wreg[16];		/* shadow of write registers */
	char	zs_flags;		/* random flags */
};
/* flags */
#define	ZS_NEEDSOFT	1
#ifdef	solbourne
#define	ZS_SERVICING	2		/* this controller being serviced */
#endif	solbourne

int zssoftpend;				/* level 3 interrupt pending */
#define	ZSSETSOFT(zs)	{		\
	zs->zs_flags |= ZS_NEEDSOFT;	\
	if (!zssoftpend) {		\
		zssoftpend = 1;		\
		setzssoft();		\
	}				\
}
#ifdef	sun4c
#define	ZSDELAY(x)
#else
#define	ZSDELAY(x)	DELAY(x)
#endif

/* 
 * Macros to access a port
 */
#define	ZREAD(n)	zszread(zs->zs_addr, n)
#define	ZWRITE(n,v)	zszwrite(zs->zs_addr, n, (int)(zs->zs_wreg[n] = (v)))
#define	ZBIS(n,v)	zszwrite(zs->zs_addr, n, (int)(zs->zs_wreg[n] |= (v)))
#define	ZBIC(n,v)	zszwrite(zs->zs_addr, n, (int)(zs->zs_wreg[n] &=~ (v)))
/*
 * If debugging via the Stimulus board, call routines to do the real thing
 */

#ifdef STIMULUS
#define	ZREAD0()	zszread(zs->zs_addr, 0)
#define	ZWRITE0(v)	{ zszwrite(zs->zs_addr, 0, (v)); }
#define	ZREADDATA()	zszread(zs->zs_addr, 8)
#define	ZWRITEDATA(v)	{ zszwrite(zs->zs_addr, (v)); }
#else
#define	ZREAD0()	zs->zs_addr->zscc_control
#define	ZWRITE0(v)	{ zs->zs_addr->zscc_control = (v); ZSDELAY(2); }
#define	ZREADDATA()	zs->zs_addr->zscc_data
#define	ZWRITEDATA(v)	{ zs->zs_addr->zscc_data = (v); ZSDELAY(2); }
#endif	/* STIMULUS */

extern struct zsops *zs_proto[];

#ifdef KERNEL
#include <smpdefs.h>
#endif
#endif /*!_sundev_zscom_h*/
