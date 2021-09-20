/* @(#) dicom.h 1.1@(#) Solbourne id 9/22/93 00:06:01 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*	@(#)xycom.h 1.8 87/04/18 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */
#ifndef _DICOM_
#define _DICOM_

/*
 * Common definitions for Xylogics disk drivers.  Names are prefixed
 * with 'xy', but these definitions also apply to the xd driver.
 */

/*
 * States for the command block flags
 */
#define DI_FBSY		0x0001		/* cmdblock in use */
#define DI_FRDY		0x0002		/* cmdblock ready for execution */
#define DI_DONE		0x0004		/* operation completed */
#define	DI_FAILED	0x0008		/* command failed */
#define DI_WANTED	0x0010		/* process waiting for iopb */
#define DI_WAIT		0x0020		/* process waiting for completion */
#define DI_INFRD	0x0040		/* in bad block forwarding */
#define DI_INRST	0x0080		/* in a restore */
#define	DI_FNLRST	0x0100		/* in final restore (cmd failed) */
#define DI_NOMSG	0x0200		/* suppress error messages */
#define	DI_DIAG		0x0400		/* diagnostic mode */
#define	DI_NOCHN	0x0800		/* don't chain this command */
#define	DI_PAGEIO	0x1000		/* pageio operation being performed */

/*
 * States for the ctlr structure flags
 */
#define	DI_C_PRESENT	0x01		/* ctlr exists */
#define	DI_C_NOCHN	0x04		/* no chaining of iopbs */

/*
 * States for the unit structure flags
 */
#define	DI_UN_PRESENT	0x01		/* unit is online */
#define	DI_UN_ATTACHED	0x02		/* unit has been attached */

/*
 * Modes to execute a command
 */
#define DI_SYNCH	0		/* synchronous */
#define DI_ASYNCH	1		/* interrupt, no wait on iopb */
#define DI_ASYNCHWAIT	2		/* interrupt, wait on iopb */

/*
 * Error message control -- if a given bit is set, those errors are
 * printed. All others are suppressed.
 */
#define EL_FORWARD	0x0001		/* block forwarding message */
#define EL_FIXED	0x0002		/* fixed error message */
#define EL_RETRY	0x0004		/* retry message */
#define EL_RESTR	0x0008		/* restore message */
#define EL_RESET	0x0010		/* reset message */
#define EL_FAIL		0x0020		/* failure message */

/*
 * Miscellaneous defines.
 */
#define b_cylin b_resid			/* used for disksort */
#define DINUNIT		2		/* max # of units on system */
#define	DINLPART	NDKMAP		/* # of logical partitions (8) */
#define	UNIT(dev)	((dev>>4) & 0xf)
#define	LPART(dev)	(dev & 0xf)
#define NOLPART		(-1)		/* used for 'non-partition commands */
#define	SECSIZE		512
#define DIWATCHTIMO	20		/* seconds till disk check */
#define DILOSTINTTIMO	4		/* seconds till lost interrupt */
#define	DI_IN		0		/* command reads data */
#define	DI_OUT		1		/* command writes data */
#define	DI_READ		2		/* read command */
#define	DI_WRITE	1		/* write command */
#define	DIUNPERC	4		/* units per controller */
#define	DI_SIMINTINTVL	1		/* clock ticks till disk interrupt */

/*
 * Structure definition and macros for manufacturer's list.
 */
#define	DI_MANDEFSIZE	24

struct didefinfo {
	u_char	info[DI_MANDEFSIZE];
};

#define	DI_MAN_SYNC(x)		(x[0])
#define	DI_MAN_CYL(x)		(((x[1] & 0x7f) << 8) + x[2])
#define	DI_MAN_HEAD(x)		(x[3])
#define	DI_MAN_BFI(x,y)		((x[5 + 4 * y] << 8) + x[6 + 4 * y])
#define	DI_MAN_LEN(x,y)		((x[7 + 4 * y] << 8) + x[8 + 4 * y])
#define	DI_MAN_LAST(x)		(x[21])

#define	DI_SYNCBYTE		0x19
#define	DI_LASTBYTE		0xf0

/*
 * Macros for sector headers that don't hold data.
 */
#define	DI_HDR_SPARE	0xdddddddd		/* header for spare sector */
#define	DI_HDR_RUNT	0xeeeeeeee		/* header for runt sector */
#define	DI_HDR_SLIP	0xfefefefe		/* header for slipped sector */
#define	DI_HDR_ZAP	0xffffffff		/* header for zapped sector */

#endif _DICOM_
