/* @(#) xdreg.h 1.1@(#) Solbourne id 9/22/93 00:09:34 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*	@(#)xdreg.h 1.3 89/08/03 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

#ifndef _sundev_xdreg_h
#define	_sundev_xdreg_h

/*
 * Xylogics 7053 declarations
 */

/*
 * IOPB - in real memory so we can use bit fields
 */
struct xdiopb {
/* 0*/	u_char	xd_iserr	:1;	/* error indicator */
	u_char	xd_complete	:1;	/* completion code valid */
	u_char	xd_chain	:1;	/* command chaining */
	u_char	xd_sgm		:1;	/* scatter/gather mode */
	u_char	xd_cmd		:4;	/* command */
/* 1*/	u_char	xd_errno;		/* error number */
/* 2*/	u_char	xd_dstat;		/* drive status */
/* 3*/	u_char	xd_resvd;		/* reserved */
/* 4*/	u_char	xd_subfunc;		/* subfunction code */
/* 5*/	u_char	xd_fixd		:1;	/* fixed/removable media */
	u_char	xd_hdp		:1;	/* hold dual-port drive */
	u_char	xd_psel		:1;	/* priority select (dual-port) */
	u_char	xd_bht		:1;	/* black hole transfer */
	u_char	xd_unit		:4;	/* unit number */
/* 6*/	u_char	xd_llength	:5;	/* link length (scatter/gather) */
#define	xd_drparam xd_llength		/* used for set drive params */
#define	xd_interleave xd_llength	/* used for set format params */
	u_char	xd_intpri	:3;	/* interrupt priority */
/* 7*/	u_char	xd_intvec;		/* interrupt vector */
/* 8*/	u_short	xd_nsect;		/* sector count */
#define	xd_bdma_icnt xd_nsect
/* A*/	u_short	xd_cylinder;		/* cylinder number */
#define	xd_throttle xd_cylinder		/* used for write ctlr params */
#define	xd_bdma_ocnt xd_cylinder
/* C*/	u_char	xd_head;		/* head number */
#define	xd_promrel xd_head		/* used for controller params */
/* D*/	u_char	xd_sector;		/* sector number */
#define	xd_ectype xd_sector		/* used for read ctlr params */
#define		XD_ECTYPE_SMD		0x00
#define		XD_ECTYPE_IPI_68	0x68
#define		XD_ECTYPE_IPI_78	0x78
#define		XD_ECTYPE_IPI_MSK	0x08
/* E*/	u_char	xd_bufmod;		/* buffer address modifier */
#define	xd_hsect xd_bufmod		/* used for read drive status */
#define	xd_ctype xd_bufmod		/* used for read ctlr params */
#define	xd_bdma_imod xd_bufmod
/* F*/	u_char	xd_prio		:1;	/* high priority iopb */
	u_char			:1;
	u_char	xd_nxtmod 	:6;	/* next iopb addr modifier */
#define	xd_bdma_omod xd_nxtmod
/*10*/	u_int	xd_bufaddr;		/* buffer address */
#define	xd_promrev xd_bufaddr		/* used for read ctlr params */
#define	xd_bdma_ibufaddr xd_bufaddr
#define	XD_PROMREV_SOLBOURNE_SMD	0x2258
#define	XD_PROMREV_SOLBOURNE_IPI	0x2328
/*14*/	struct xdiopb *xd_nxtaddr;	/* next iopb address */
#define	xd_bdma_obufaddr xd_nxtaddr
/*18*/	u_short	xd_cksum;		/* iopb checksum */
/*1A*/	u_short	xd_eccpat;		/* ECC pattern */
/*1C*/	u_short	xd_eccaddr;		/* ECC address */
/*1E*/	u_short	xd_pad;			/* pad */
/*20*/
#define	XDIOPB_HWSIZE	0x20
};

/*
 * Commands -- the values are shifted by a byte so they can be folded
 * with the subcommands into a single variable.
 */
#define	XD_NOP		0x0000	/* nop */
#define	XD_WRITE	0x0100	/* write */
#define	XD_READ		0x0200	/* read */
#define	XD_SEEK		0x0300	/* seek */
#define	XD_RESTORE	0x0400	/* drive reset */
#define	XD_WPAR		0x0500	/* write params */
#define	XD_RPAR		0x0600	/* read params */
#define	XD_WEXT		0x0700	/* extended write */
#define	XD_REXT		0x0800	/* extended read */
#define	XD_DIAG		0x0900	/* diagnostics */
#define	XD_ABORT	0x0a00	/* abort */
#define	XD_IPI_PT	0x0a00	/* passthrough (IPI) */
#define	XD_PSEUDO	0xff00	/* driver: pseudo command... */

/*
 * Subcommands
 */
	/*
	 * seek
	 */
#define	XD_RCA		0x00	/* report current address */
#define	XD_SRCA		0x01	/* seek and report current address */
#define	XD_SSRCI	0x02	/* start seek and report completion */
	/*
	 * read and write parameters
	 */
#define	XD_CTLR		0x00	/* controller parameters */
#define	XD_DRIVE	0x80	/* drive parameters */
#define	XD_FORMAT	0x81	/* format parameters */
#define	XD_DSTAT	0xa0	/* drive status (read only) */
#define	XD_PERF		0xc0	/* performance params */
	/*
	 * extended read and write
	 */
#define	XD_THEAD	0x80	/* track headers (SMD) */
#define	XD_THEAD_IPI	0xc0	/* track headers (IPI) */
#define	XD_FORMVER	0x81	/* format (write), verify (read) */
#define	XD_HDE		0x82	/* header, data and ecc (SMD) */
#define	XD_HDE_IPI	0xc1	/* header, data and ecc (IPI) */
#define	XD_DEFECT	0xa0	/* defect map (SMD) */
#define	XD_EXTDEF	0xa1	/* extended defect map (SMD) */
#define	XD_DEFECT_IPI	0xc4	/* defect map (IPI) */
	/*
	 * Diagnostic Commands
	 */
#define	XD_BDMA		0x01	/* buffer dma command (IPI) */
	/*
 	* Compound Compounds (for clarity of code)
 	*/
#define	XD_VERIFY	(XD_REXT|XD_FORMVER)
	/*
	 * IPI Passthrough commands defined in <dev/ipi_2.h>
	 */

/*
 * drive status bits
 */
#define	XD_READY	0x01
#define	XD_ONCYL	0x02
#define	XD_SKERR	0x04
#define	XD_DFAULT	0x08
#define	XD_WPROT	0x10
#define	XD_DPBUSY	0x80

/*
 * Miscellaneous defines.
 */
#define	XD_THROTTLE	32		/* 32 words/transfer */
#define	XDUNPERC	16		/* max # of units per controller */

/*
 * Structure definition and macros used for a sector header.
 */
#define	XD_HDRSIZE	4		/* bytes/sector header */
struct xdhdr {				/* smd header */
	u_char	xdh_cyl_lo;		/* Byte 0 */
	u_char	xdh_cyl_hi;		/* Byte 1 */
	u_char	xdh_head;		/* Byte 2 */
	u_char	xdh_sec;		/* Byte 3 */
};
#define	XD_CYL_LO(n)	((int)(n) & 0xff)
#define	XD_CYL_HI(n)	(((int)(n) & 0xff00) >> 8)
#define	XD_GET_CYL(h)	(((h)->xdh_cyl_hi << 8) | (h)->xdh_cyl_lo)

#define	XD_HDRSIZE_IPI	8		/* bytes/sector header */
struct xdhdr_ipi {
	u_short	xdh_ipi_empty;		/* Byte 0,1 */
	u_short	xdh_ipi_cyl;		/* Byte 0,1,2,3 */
	u_short	xdh_ipi_head;		/* Byte 4,5 only byte 5 used */
	u_short	xdh_ipi_sec;		/* Byte 6,7 */
};

/*
 * Bits that are to be used for setting controller parameters
 *
 * iopb bytes 0x8 and 0x9 are mushed together here as one short.
 *
 */
	/* iopb byte 0x8 */
#define	XD_AUD	0x8000	/* auto update mode. If false, update still */
			/* occurs on error                          */
#define	XD_LWRD	0x4000	/* 32bit xfer mode if on */
#define	XD_DACF	0x2000	/* disable VMEbus ACFAIL* recognition */
#define	XD_ICS	0x1000	/* IOPB checksum done by 7053 */
#define	XD_EDT	0x0800	/* Enable DMA timeout */
#define	XD_NPRM	0x0400	/* Non-privileged register access mode */
/*		0x0200	   Reserved */
/*		0x0100	   Reserved */
	/* iopb byte 0x9 */
#define	XD_TDTM	0x00c0	/* Mask for throttle dead time value - 2 bits */
#define	xd_tdtv(x)	(((x)&0x3)<<6)
#define	XT_BMT	0x0020	/* block mode transfer (IPI only) */
#define	XD_ROR	0x0010	/* enable VMEbus Release-On-Request */
#define	XT_BHT	0x0008	/* black hole transfers (IPI only) */
/*		0x0008	   Reserved */
/*		0x0004	   Reserved */
/*		0x0002	   Reserved */
#define	XD_DRA	0x0001	/* Disable Read-Ahead on 7053 */


	/* iopb byte 0xa */
#define	XD_OVS	0x80	/* Enable overlapped seeks */
#define	XD_ESWO	0x40	/* (undocumented feature) enable elevator seeks */
			/* and write optimization                       */
#define	XD_NOQD	0x20	/* if set disables queue delays */   
#define	XD_ASR	0x10	/* Automatic Seek Retry */
/*		0x08	   Reserved */
#define	XD_RBC	0x04	/* Retry Before Correction */
#define	XD_ECC2	0x02	/* ECC Mode 2 */
#define	XD_ECC1	0x01	/* ECC Mode 1 */	
#define	XD_ECC0	0x00	/* ECC Mode 0 */

/* scatter gather list element format */
struct xdsgl {
	u_short	xd_sgl_bcount;	/* byte count for this descriptor */
	u_char	xd_sgl_xcf;	/* extention count field... */
	u_char	xd_sgl_dam;	/* data address modifier */
	u_int	xd_sgl_da;	/* data address */
};
#endif /*!_sundev_xdreg_h*/
