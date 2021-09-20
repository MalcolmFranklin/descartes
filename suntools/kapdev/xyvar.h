/* @(#) xyvar.h 1.1@(#) Solbourne id 9/22/93 00:10:07 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*	@(#)xyvar.h 1.2 88/05/28 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */
#ifndef _XYVAR_
#define _XYVAR_

/*
 * Structure definitions for Xylogics 450 disk driver.
 */
#include <sundev/xycreg.h>
#include <sundev/xyreg.h>
#include <sundev/xycom.h>

/*
 * Structure needed to execute a command.  Contains controller & iopb ptrs
 * and some error recovery information.  The link is used to identify
 * chained iopbs.
 */
struct xycmdblock {
	struct	xyctlr *c;		/* ptr to controller */
	struct	xyiopb *iopb;		/* ptr to IOPB */
	struct	xycmdblock *next;	/* next iopb in ctlr chain */
	u_char	retries;		/* retry count */
	u_char	restores;		/* restore count */
	u_char	resets;			/* reset count */
	u_char	slave;			/* current drive no. */
	u_short	cmd;			/* current command */
	int	flags;			/* state information */
	caddr_t	baddr;			/* physical buffer address */
	daddr_t	blkno;			/* current block */
	daddr_t altblkno;		/* alternate block (forwarding) */
	u_short	nsect;			/* sector count active */
	short	device;			/* current minor device */
	u_char	failed;			/* command failure */
};

/*
 * Data per unit
 */
struct xyunit {
	struct	dk_map *un_map;		/* logical partitions */
	u_char	un_flags;		/* state information */
	u_char	un_drtype;		/* drive type */
	struct	dk_geom *un_g;		/* disk geometry */
	struct	buf *un_rtab;		/* for physio */
	int	un_ltick;		/* last time active */
	struct	mb_device *un_md;	/* generic unit */
	struct	mb_ctlr *un_mc;		/* generic controller */
	struct	dkbad *un_bad;		/* bad sector info */
	int	un_errsect;		/* sector in error */
	u_char	un_errno;		/* error number */
	u_char	un_errsevere;		/* error severity */
	u_short	un_errcmd;		/* command in error */
	long	un_residual;		/* bytes not transfered */
	struct	xycmdblock un_cmd;	/* current command info */
};

/*
 * Data per controller
 */
struct xyctlr {
	struct	xyunit *c_units[XYUNPERC];	/* units on controller */
	int	c_nextunit;			/* round-robin unit ptr */
	struct	xydevice *c_io;			/* ptr to I/O space data */
	struct	xycmdblock *c_chain;		/* ptr to iopb chain */
	u_char	c_flags;			/* state information */
	int	c_wantint;			/* controller is busy */
	struct	xycmdblock c_cmd;		/* used for special commands */
};

#endif _XYVAR_

