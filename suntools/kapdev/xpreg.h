/* @(#) xpreg.h 1.1@(#) Solbourne id 9/22/93 00:09:43 */
/*
 * Copyright 1989 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*
 * Xylogics 781 driver
 */

/* lines per board */
#define XP_NLPB		16
#define XP_NLPBSHIFT	4

/* registers */
struct xpreg {
	u_char	xp_pad0;
	u_char	xp_read0;
	u_char	xp_pad1;
	u_char	xp_read1;
	u_char	xp_pad2;
	u_char	xp_write0;
	u_char	xp_pad3;
	u_char	xp_write1;
	u_char	xp_pad4;
	u_char	xp_cmd;
	u_char	xp_pad5;
	u_char	xp_ctl;
	u_char	xp_pad6;
	u_char	xp_line;
	u_char	xp_pad7;
	u_char	xp_pad8;
};

/* alias for registers */
#define xp_idb0		xp_read0
#define xp_idb1		xp_read1
#define xp_idb2		xp_write0
#define xp_idb3		xp_write1
#define xp_addrmod	xp_cmd
#define xp_rpt		xp_cmd
#define xp_stat		xp_ctl
#define xp_ferr		xp_line

/* alias for registers after power-on */
#define xp_fwmaj	xp_read0
#define xp_fwmin_h	xp_read1
#define xp_fwmin_l	xp_write0
#define xp_hwconf	xp_write1
#define xp_oem		xp_cmd

/* csr bits */
#define XP_CTL_MRST	0x40	/* module reset */
#define XP_CTL_EMM	0x20	/* enter maint. mode */
#define XP_CTL_ARC	0x04	/* add register control */
#define XP_CTL_CRS	0x02	/* clear register status */
#define XP_STAT_RSTA	0x40	/* reset active */
#define XP_STAT_MMA	0x10	/* maint. mode active */
#define XP_STAT_ARCP	0x04	/* add register control pending */
#define XP_STAT_RSP	0x02	/* register status pending */
#define XP_STAT_FERR	0x01	/* fatal error */

/* command register bits */
/* read-write commands */
#define XP_CMD_SYNC	0x04
#define XP_CMD_WR	0x02
#define XP_CMD_RD	0x01

/* non read-write commands */
#define XP_CMD_MASK		0xf0
#define XP_CMD_UARTINIT		0x10
#define XP_CMD_FLUSHBUF		0x20
#define XP_CMD_RESETPORT	0x30
#define XP_CMD_SETMDM		0x40
#define XP_CMD_GETMDM		0x50
#define XP_CMD_SENDBRK		0x60
#define XP_CMD_GETERRLOG	0x70
#define XP_CMD_RESETPORT_FLOW	0x80	/* new firmware only */
#define XP_CMD_HOSTXON		0x90
#define XP_CMD_HOSTXOFF		0xA0
#define XP_CMD_SBRK		0xB0
#define XP_CMD_CBRK		0xC0
#define XP_CMD_HOSTXON_OVERRIDE	0xD0	/* new firmware only */
#define XP_CMD_UARTINIT_NOFLUSH	0xE0	/* new firmware only */

/* report codes */
#define XP_RPT_PARERR		0x10
#define XP_RPT_FRAMERR		0x20
#define XP_RPT_MDMCHANGE	0x30
#define XP_RPT_OVERRUN		0x40
#define XP_RPT_CMDERR		0x50
#define XP_RPT_BUSERR		0x60
#define XP_RPT_TIMEOUT		0x70
#define XP_RPT_OVERFLOW		0x80
#define XP_RPT_QUEUEOF		0x90

/* fatal error register code */
#define XP_FERR_EPROM		0x10
#define XP_FERR_SRAM		0x20
#define XP_FERR_REGCEL		0x31
#define XP_FERR_OCTART_CMDREG	0x40
#define XP_FERR_OCTART_MODEREG	0x50
#define XP_FERR_OCTART_INLOOP	0x80
#define XP_FERR_OCTART_EXTLOOP	0x90

/* hwconf bits */
#define	XP_HWCONF_BTLB		0x01

/* uart parameters */
struct xp_uart {
	u_short	u_scc;
	u_short	u_baud;
	u_short	u_modem_state;
	u_short	u_modem_mask;
	u_short	u_input_timeout;
	u_short	u_input_min;
	u_char	u_xon;
	u_char	u_xoff;
	u_short	u_lowtide;
	u_short	u_breaktime;
	u_short	u_res1;
	u_short	u_res2;
	u_short	u_parerr;
	u_short	u_frmerr;
	u_short	u_ovflerr;
	u_short	u_res3;
	u_short u_res4;
};

/* definition for SCC bits */
#define U_SCC_1STOPB	0x40
#define U_SCC_1_5STOPB	0x80
#define U_SCC_2STOPB	0xc0

#define U_SCC_PARNO	0x00
#define U_SCC_PARODD	0x10
#define U_SCC_PAREVEN	0x30

#define U_SCC_CS5	0x00
#define U_SCC_CS6	0x04
#define U_SCC_CS7	0x08
#define U_SCC_CS8	0x0c

#define U_SCC_NO_FLCTL	0x00
#define U_SCC_HDW_FLCTL	0x01
#define U_SCC_SW_FLCTL	0x02
#define U_SCC_ALL_FLCTL	0x03

/* modem line signals */
#define U_MDM_DSR	0x80
#define U_MDM_CTS	0x40
#define U_MDM_DCD	0x20
#define U_MDM_DTR	0x02
#define U_MDM_RTS	0x01
#define U_MDM_UNI	0x10
#define U_MDM_IXANY	0x08	/* new firmware only */
#define U_MDM_MCU	0x02

/* receiver enable bit */
#define U_MDM_RCV_ENBL	0x01

/* IDB (Initialization Descriptor Block) */
struct xp_idb {
	u_short	idb_ibaddr[2];	/* input buffer */
	u_short idb_iblen;
	u_short idb_obaddr[2];	/* output buffer */
	u_short idb_oblen;
	u_short idb_addrmod;	/* buffer address modifier */
	u_short idb_invec;	/* input interrupt */
	u_short idb_inlev;
	u_short idb_outvec;	/* output interrupt */
	u_short idb_outlev;
	u_short idb_statvec;	/* status interrupt */
	u_short idb_statlev;
	struct xp_uart idb_uart[XP_NLPB];	/* uart parameters all line */
};

/* input/output buffer */

#define XP_IBUFSIZE 512
#define XP_OBUFSIZE 512		/* greater or equal 64 and power of 2 */

struct xp_ibuf {
	u_short	xi_count;
	u_char	xi_data[XP_IBUFSIZE];
};

struct xp_obuf {
	u_short	xo_get;
	u_short	xo_put;
	u_char	xo_data[XP_OBUFSIZE];
};
