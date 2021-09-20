/* @(#) divar.h 1.1@(#) Solbourne id 9/22/93 00:06:06 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*	@(#)xyvar.h 1.12 87/04/18 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */
#ifndef _DIVAR_
#define _DIVAR_

/*
 * Structure definitions for simulated disk driver
 */
#include <dev/dicom.h>

/*
 * Structure needed to execute a command.  Contains controller & iopb ptrs
 * and some error recovery information.  The link is used to identify
 * chained iopbs.
 */
struct dicmdblock {
	struct	dictlr *c;		/* ptr to controller */
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
struct diunit {
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
	struct	dicmdblock un_cmd;	/* current command info */
};

/*
 * Data per controller
 */
struct dictlr {
	struct	diunit *c_units[DIUNPERC];	/* units on controller */
	int	c_nextunit;			/* round-robin unit ptr */
	struct	didevice *c_io;			/* ptr to I/O space data */
	u_char	c_flags;			/* state information */
	int	c_wantint;			/* controller is busy */
	struct	dicmdblock c_cmd;		/* used for all commands */
};

#endif _DIVAR_

