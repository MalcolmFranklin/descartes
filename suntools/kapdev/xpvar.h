/* @(#) xpvar.h 1.1@(#) Solbourne id 9/22/93 00:09:46 */
/*
 * Copyright 1989 Solbourne Computer, Inc.
 * All rights reserved.
 */

/* Xylogics 781 driver */


/* per line data structure */
struct xpline {
    int		xp_flags;		/* random flags */
#define		  XPS_WOPEN	0x0001	/*   waiting for open to complete */
#define		  XPS_ISOPEN	0x0002	/*   open is complete */
#define		  XPS_OUT	0x0004	/*   line being used for dialout */
#define		  XPS_CARR_ON	0x0008	/*   carrier on last time we looked */
#define		  XPS_XCLUDE	0x0010	/*   open for exclusive use */
#define		  XPS_STOPPED	0x0020	/*   output is stopped */
#define		  XPS_SUSPD	0x0040	/*   output is suspended */
#define		  XPS_DELAY	0x0080	/*   wait for delay to finish */
#define		  XPS_BREAK	0x0100	/*   wait for break to finish */
#define		  XPS_BUSY	0x0200	/*   wait for sync xmit to finish */
#define		  XPS_DRAINPEND	0x0400	/*   wait for silo to be drained */
#define		  XPS_DRAINNOW	0x0800	/*   force  silo to be drained */
#define		  XPS_SYNC	0x1000	/*   last sent a SYNC for output */
#define		  XPS_SOFTC_ATN	0x2000	/*   softcar status has changed */
    int		xp_dev;			/* unit number */
    tty_common_t xp_ttycommon;		/* data common to all tty drivers */
    int		xp_wbufcid;		/* id of pendinf write-side bufcall */
    int		xp_dtrlow;		/* time dtr started low */
    int		xp_icnt;		/* number of chars in silo */
    int		xp_iptr;		/* silo input pointer */
    int		xp_sptr;		/* silo consumer pointer */
    u_char	xp_flowc;		/* startc or stopc to transmit */
#define		  XP_SILOSIZE 512
    u_char	xp_silo[XP_SILOSIZE];	/* input silo used when q is full */
};

/* per board data structure */
struct xp_softc {
    struct xp_idb	*xs_idb;	/* idb addr */
    struct xp_ibuf	*xs_ib;		/* input buffer addr */
    struct xp_obuf	*xs_ob;		/* output buffer addr */
    u_int		xs_idb_addr;	/* idb virtual address */
    int			xs_idb_cookie;	/* idb VMEbus address */
    int			xs_ib_cookie;	/* input buffer virtual address */
    u_int		xs_ib_addr;	/* input buffer VMEbus address */
    int			xs_ob_cookie;	/* output buffer virtural address */
    u_int		xs_ob_addr;	/* output buffer VMEbus address */
    int			xs_btlb;	/* baud rate table for board */
    u_int		xs_fwrev;	/* firmware rev of the board */
    u_int		xs_empty;	/* initial state of empty for writes */
    struct xpline	xs_line[XP_NLPB];
};

/* firmware 2.2.18 == XS_FWREV(2, 2, 18) == 0x02020012 */
#define	XS_FWREV(a, b, c)	(((a) << 24) | ((b) << 16) | (c))

/* performance statistics */

struct xp_lstats {
    int		xpl_noch;		/* characters output */
    int		xpl_nich;		/* characters input */
    int		xpl_sb_mdm;		/* modem changes */
    int		xpl_sb_pferr;		/* parity/framing errors */
    int		xpl_sb_err;		/* error status blocks */
    int		xpl_ring_cantput;	/* ring buffer overflows */
};

struct xp_cstats {
    int		xpc_intr;		/* interrupts */
    int		xpc_sb_wr;		/* write status blocks */
    int		xpc_sb_rd;		/* read status blocks */
    int		xpc_sb_sync;		/* synchronous write status blocks */
    int		xpc_maxsbperint;	/* max status blocks per interrupt */
    int		xpc_maxxpersb;		/* max transmit per status block */
    int		xpc_maxrpersb;		/* max recieve per status block */
    int		xpc_maxblcnt;		/* board max ARCP poll loop */
    int		xpc_maxllcntb;		/* line max ARCP poll loop (before) */
    int		xpc_maxllcntb_cmd;	/* cmd */
    int		xpc_maxllcntb_line;	/* line */
    int		xpc_maxllcnta;		/* line max ARCP poll loop (after) */
    int		xpc_maxllcnta_cmd;	/* cmd */
    int		xpc_maxllcnta_line;	/* line */
    int		xpc_maxloopcnt;		/* max ARCP polling loop count */
    int		xpc_starts_wr;		/* writes */
    int		xpc_starts_wr_async;	/* writes that produced command */
    int		xpc_starts_sync;	/* sync's initiated */
    int		xpc_noch;		/* total characters output */
    int		xpc_nich;		/* total characters input */
    int		xpc_ring_cantput;	/* total ring buffer overflows */
    struct xp_lstats xpc_lstats[XP_NLPB];/* per line stats */
    int		xpc_last_cmd;		/* last cmd */
    int		xpc_last_line;		/* last line */
    int		xpc_maxllcnta_who;	/* who */
    int		xpc_maxllcnta_arg;	/* arg */
    int		xpc_xpparam;		/* number of xpparams */
    int		xpc_xpparam_nop;	/* number of unneeded xpparams */
};
