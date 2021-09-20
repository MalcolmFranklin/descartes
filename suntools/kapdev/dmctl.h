/* @(#) dmctl.h 1.1@(#) Solbourne id 9/22/93 00:06:08 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*	@(#)dmctl.h 1.1 88/05/28 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

/*
 * Bits for use with TIOCM{GET,SET,BIS,BIC} ioctls
 * really bits in dm lsr, copied from dh.c
 */
#define	DML_DSR		0000400		/* data set ready, not a real DM bit */
#define	DML_RNG		0000200		/* ring */
#define	DML_CAR		0000100		/* carrier detect */
#define	DML_CTS		0000040		/* clear to send */
#define	DML_SR		0000020		/* secondary receive */
#define	DML_ST		0000010		/* secondary transmit */
#define	DML_RTS		0000004		/* request to send */
#define	DML_DTR		0000002		/* data terminal ready */
#define	DML_LE		0000001		/* line enable */
