/* @(#) xdvar.h 1.1@(#) Solbourne id 9/22/93 00:09:36 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*	@(#)xdvar.h 1.2 89/08/03 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */
#ifndef _sundev_xdvar_h
#define	_sundev_xdvar_h


/*
 * Structure definitions for Xylogics 7053 disk driver.
 */
#include <dev/xdcreg.h>
#include <dev/xdreg.h>
#include <dev/xycom.h>

/*
 * Structure needed to execute a command.  Contains controller & iopb ptrs
 * and some error recovery information.  The link is used to identify
 * chained iopbs.
 */
struct xdcmdblock {
	struct	xdctlr *c;		/* ptr to controller */
	struct	xdunit *un;		/* ptr to unit */
	struct	xdiopb *iopb;		/* ptr to IOPB */
	struct	xdcmdblock *next;	/* next iopb in queue */
	struct	buf *breq;		/* */
	caddr_t	mbaddr;			/* */
	u_char	retries;		/* retry count */
	u_char	restores;		/* restore count */
	u_char	resets;			/* reset count */
	u_char  slave;			/* current drive no. */
	u_short	cmd;			/* current command */
	int	flags;			/* state information */
	caddr_t	baddr;			/* physical buffer address */
	daddr_t	blkno;			/* current block */
	daddr_t	altblkno;		/* alternate block (forwarding) */
	u_short	nsect;			/* sector count active */
	short	device;			/* current minor device */
	u_char	failed;			/* command failure */
	u_char	forwarded:	1,	/* did this xfer have a mapped block */
		nverifies:	7;	/* number of verify actions */
	daddr_t	vblk;			/* (for verify of forwarded blocks) */
};

/*
 * Data per unit
 */
struct xdunit {
	struct	xdctlr *c;		/* controller */
	struct	dk_map *un_map;		/* logical partitions */
	struct	dk_geom *un_g;		/* disk geometry */
	int	un_active;		/* #command committed for this unit */
	int	un_ltick;		/* last time active */
	struct	mb_device *un_md;	/* generic unit */
	struct	mb_ctlr *un_mc;		/* generic controller */
	struct	dkbad *un_bad;		/* bad sector info */
	int	un_errsect;		/* sector in error */
	u_char	un_errno;		/* error number */
	u_char	un_errsevere;		/* error severity */
	u_short	un_errcmd;		/* command in error */
	u_char	un_flags;		/* state information */
	u_char	un_wchkmap;		/* partition map for write check ops */
};

/*
 * Data per controller
 */

struct xdctlr {
	struct	xdunit *c_units[XDUNPERC];	/* units on controller */
	u_char	c_u2cu[XDUNPERC];		/* unit to channel xlate vec */
	struct	xddevice *c_io;			/* ptr to I/O space data */
	struct	xdcmdblock *actvcmdq; 		/* current command queue */
	struct	xdcmdblock *actvcmdq_l;		/* last current command queue */
	struct	xdiopb *rdyiopbq;		/* ready iopbs */
	struct	xdiopb *lrdy;			/* last ready iopb */
	int	c_wantint;			/* controller is busy */
	int	c_intpri;			/* interrupt priority */
	int	c_intvec;			/* interrupt vector */
	u_char	c_flags;			/* state information */
	u_char	c_ectype;			/* type of controller SMD/IPI */
	struct	xdcmdblock *c_free;		/* free cmdblock/iopbs */
	struct	xdcmdblock *c_err_retry;	/* free cmdblock for error */
	int	c_freewait;			/* flag for c_free wait */
	struct	buf *c_waitbufq;		/* head of waiting bufs */
	struct	buf *c_lbq;			/* tail of waiting bufs */
	int	c_maxsecsize;			/* max secsizes to try */
	u_int	c_fwrev;			/* firmware rev of the board */
	slock 	c_lock;				/* access to this controller */
};

/* firmware 2.2.18 == XS_FWREV(2, 2, 18) == 0x02020012 */
#define	XD_FWREV(a, b, c)	(((a) << 24) | ((b) << 16) | (c))

/*
 * after RIO is found to be set, this is the number of
 * seconds to wait for the interrupt handler to get invoked
 * before timing out and invoking xdintr via the
 * watch-dog handler.  This value was originally set to
 * 1, but this resulted in recovery messages being printed
 * out constantly under conditions of heavy I/O.  This value must
 * be less that the min watch dog timeout value next_timeout for
 * this mechanism to work.
 */
#define	MAX_RIO_TICKS 6
				

struct xd_w_info {
	u_int curr_timeout;     /* remaining ticks in interval */
	u_int next_timeout;     /* ticks for next interval */
	u_int got_interrupt;    /* got an interrupt in interval */
	u_int got_rio;		/* number of seconds XD_RIO */
				/* has been set, but not serviced */
};

/*
 * The tuning parameter for each cpu architecture is held in this structure.
 * Currently the structure has to be ifdef'd for sun3 & sun4s
 * A cpu type of zero should be the last entry in the list.  This is the
 * default value and will be used if there weren't any matches
 *
 * Note: a delay value of 0 is really 2 msec. Otherwise the delay is in
 *	 256usecs increments.
 */

struct xd_ctlrpar2 {
	int   cpu;	/* the cpu type that will match this entry */
	short delay;	/* the delay sent to the controller */
};

#define	XD_MAXDELAYS	20  /* max number of entries in xd_ctlrpar2 struct */
#endif	/*!_sundev_xdvar_h*/
