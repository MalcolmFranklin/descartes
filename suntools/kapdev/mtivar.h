/* @(#) mtivar.h 1.1@(#) Solbourne id 9/22/93 00:07:13 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*	@(#)mtivar.h 1.1 88/03/29 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

/*
 * Systech MTI-800/1600 Multiple Terminal Interface driver
 */

/*
 * Per-board data structures.
 */
struct	mti_softc {
	int	msc_have;	/* number of response chars accumulated */
	u_char	msc_rbuf[8];	/* buffer for responses */
	struct	clist msc_cmdq;	/* queue of commands if cmd fifo is busy */
};

#define	SILOSIZE	32	/* size of software input silo */

/*
 * Per-line data structures.
 */
struct mtiline {
	int	mt_flags;		/* random flags */
	int	mt_unit;		/* unit number */
	tty_common_t mt_ttycommon;	/* data common to all tty drivers */
	u_char	mt_wbits;		/* copy of writable modem control bits */
	u_char	mt_rbits;		/* copy of readable modem control bits */
	char	*mt_buf;		/* pointer to DMA buffer */
	int	mt_dmaoffs;		/* offset into DMA buffer to start */
	int	mt_dmacount;		/* number of bytes to transmit */
	u_char	mt_flowc;		/* startc or stopc to transmit */
	u_char	mt_isilo[SILOSIZE];	/* input silo */
	u_char	*mt_iptr;		/* producing ptr for input */
	u_char	*mt_sptr;		/* consuming ptr for input */
	short	mt_silocnt;		/* number of characters in silo */
};

#define	MTS_WOPEN	0x00000001	/* waiting for open to complete */
#define	MTS_ISOPEN	0x00000002	/* open is complete */
#define	MTS_OUT		0x00000004	/* line being used for dialout */
#define	MTS_CARR_ON	0x00000008	/* carrier on last time we looked */
#define	MTS_XCLUDE	0x00000010	/* device is open for exclusive use */
#define	MTS_STOPPED	0x00000020	/* output is stopped */
#define	MTS_DELAY	0x00000040	/* waiting for delay to finish */
#define	MTS_BREAK	0x00000080	/* waiting for break to finish */
#define	MTS_BUSY	0x00000100	/* waiting for transmission to finish */
#define	MTS_FCXMIT	0x00000200	/* waiting for flow control char transmission to finish */
#define	MTS_DRAINING	0x00000400	/* waiting for output to drain */
#define	MTS_FLUSH	0x00000800	/* flushing output being transmitted */
