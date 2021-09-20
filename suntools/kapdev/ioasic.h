/* @(#) ioasic.h 1.1@(#) Solbourne id 9/22/93 00:06:27 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/* asic control registers */

struct ioasic_reg {
	int	ioasic_ir;		/* 0x00 ioasic interrupt register */
#define		  IOASIC_IR_VMEPANIC	0x1	/* VMEbus panic condition */
#define		  IOASIC_IR_SI_PO	0x2	/* scsi page overflow */
#define		  IOASIC_IR_SI_ECC_TO	0x4	/* scsi ECC/timeout error */
	int	ioasic_ei_rar;		/* 0x04 ioasic enet recieve addr register */
#define		  IOASIC_EI_RAR_SHIFT	15	/* right shift addr */
	int	ioasic_ei_tar1;		/* 0x08 ioasic enet xmit addr register 1 */
	int	ioasic_ei_tar2;		/* 0x0C ioasic enet xmit addr register 2 */
#define		  IOASIC_EI_TAR_SHIFT	13	/* right shift addr */
	int	ioasic_si_sar;		/* 0x10 ioasic scsi addr register */
#define		  IOASIC_SI_SAR_SHIFT	13	/* right shift addr */
#define		  IOASIC_SI_SAR_MASK	0x0007FFFF
	int	ioasic_si_ctl;		/* 0x14 ioasic scsi control register */
#define		  IOASIC_SI_CTL_READ	0x0	/* read from scsi bus */
#define		  IOASIC_SI_CTL_WRITE	0x1	/* write to scsi bus */
#define		  IOASIC_SI_CTL_PRE	0x2	/* prefetch */
#define		  IOASIC_SI_CTL_SHIFT	2	/* left shift addr */
#define		  IOASIC_SI_CTL_MASK	0x0007FFF
#define		  IOASIC_SI_CTL_AMASK	0x0007FFC
#define		  IOASIC_SI_CTL_BITS	"\20\2PREFETCH\1WRITE"
	int	ioasic_pad[6];		/* 0x18 */
	int	ioasic_si_sar_pre;	/* 0x30 prefetech ioasic scsi addr reg */
};
