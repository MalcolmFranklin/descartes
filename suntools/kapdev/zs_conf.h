/* @(#) zs_conf.h 1.1@(#) Solbourne id 9/22/93 00:10:19 */
#ifdef notdef

>>>This module now obsolete <<<

/*
 * Copyright 1990 Solbourne Computer, Inc.
 * All rights reserved
 */

#include <sys/ttyflow.h>

extern int nzs;

#define	RINGBITS	8		/* # of bits in ring ptrs */
#define	RINGSIZE	(1<<RINGBITS)	/* size of ring */
#define	RINGMASK	(RINGSIZE-1)
#define	RINGFRAC	8		/* fraction of ring to force flush */

#define	RING_INIT(zap)	((zap)->za_rput = (zap)->za_rget = 0)
#define	RING_CNT(zap)	(((zap)->za_rput - (zap)->za_rget) & RINGMASK)
#define	RING_FRAC(zap)	(RING_CNT(zap) >= (RINGSIZE/RINGFRAC))
#define	RING_POK(zap,n)	(RING_CNT(zap) < (RINGSIZE-(n)))
#define	RING_PUT(zap,c)	((zap)->za_ring[(zap)->za_rput++ & RINGMASK] = (u_char)(c))
#define	RING_GOK(zap,n)	(RING_CNT(zap) >= (n))
#define	RING_GET(zap)	((zap)->za_ring[(zap)->za_rget++ & RINGMASK])
#define	RING_EAT(zap,n)	((zap)->za_rget += (n))
/*
 * Communication between H/W level 5 interrupts
 * and software interrupts
 */
struct zsaline {
	int	za_flags;		/* random flags */
	dev_t	za_dev;			/* major/minor for this device */
	mblk_t	*za_xmitblk;		/* block being transmitted from */
	struct zscom *za_common;	/* address of zs common data structure */
	tty_common_t za_ttycommon;	/* data common to all tty drivers */
	flow_t	za_flow;		/* bottom flow control info */
	time_t	za_dtrlow;		/* time dtr went low */
	short	za_needsoft;		/* need for software interrupt */
	short	za_break;		/* break occurred */
	union {
		struct {
			u_char	_hw;		/* overrun (hw) */
			u_char	_sw;		/* overrun (sw) */
		} _z;
		u_short uover_overrun;
	} za_uover;
#define za_overrun	za_uover.uover_overrun
#define za_hw_overrun	za_uover._z._hw
#define za_sw_overrun	za_uover._z._sw
	short	za_ext;			/* modem status change */
	short	za_work;		/* work to do */
	u_char	za_rput;		/* producing ptr for input */
	u_char	za_rget;		/* consuming ptr for input */
	u_char	*za_optr;		/* output ptr */	
	short	za_ocnt;		/* output count */	
	u_char	za_flowc;		/* startc or stopc to transmit */
	u_char	za_rr0;			/* for break detection */
	u_char	za_ring[RINGSIZE];	/* circular input buffer */
};

#define	ZAS_WOPEN	0x00000001	/* waiting for open to complete */
#define	ZAS_ISOPEN	0x00000002	/* open is complete */
#define	ZAS_OUT		0x00000004	/* line being used for dialout */
#define	ZAS_CARR_ON	0x00000008	/* carrier on last time we looked */
/* #define ZAS_STOPPED	0x00000010	   output is stopped OBSELETE */
#define	ZAS_DELAY	0x00000020	/* waiting for delay to finish */
#define	ZAS_BREAK	0x00000040	/* waiting for break to finish */
#define	ZAS_BUSY	0x00000080	/* waiting for transmission to finish */
#define	ZAS_DRAINING	0x00000100	/* waiting for output to drain from chip */
#define	ZAS_SERVICEIMM	0x00000200	/* queue soft interrupt as soon as receiver interrupt occurs */
#endif notdef
