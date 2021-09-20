/* @(#) vme.h 1.1@(#) Solbourne id 9/22/93 00:09:01 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/* VME Bus definitions */

/* VMEbus address modifier values: composed of a size, privilege, and a space */
#define	VME_AM_SIZE_MSK		0x38		/* size */
#define	VME_AM_SHORT		0x28
#define	VME_AM_STANDARD		0x38
#define	VME_AM_EXTENDED		0x08
#define	VME_AM_A32		VME_AM_EXTENDED
#define	VME_AM_A24		VME_AM_STANDARD
#define	VME_AM_A16		VME_AM_SHORT

#define	VME_AM_PRIV_MSK		0x04		/* privilege */
#define	VME_AM_SUPERVISORY	0x04
#define	VME_AM_NON_PRIVILEGED	0x00

#define	VME_AM_SPACE_MSK	0x03		/* space */
#define	VME_AM_BLOCK_TRANSFER	0x03
#define	VME_AM_PROGRAM_ACCESS	0x02
#define	VME_AM_DATA_ACCESS	0x01

#define	VME_AM(size, priv, space)	\
	(VME_AM_/**/size|VME_AM_/**/priv|VME_AM_/**/space)
/* EXAMPLE: VME_AM(STANDARD,NON_PRIVILEDGED,BLOCK_TRANSFER) */
