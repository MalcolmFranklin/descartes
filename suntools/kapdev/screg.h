/* @(#) screg.h 1.1@(#) Solbourne id 9/22/93 00:07:39 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*
 *	The Rimfire 3200/3400/3500 is seen as a 512 byte area in the 16 bit
 *	address space.  There are four registers in this space,
 *	each on an 8 byte boundary.  The registers are defined below.
 *		3200 - SMD,	3400 - ESDI,	3500 - SCSI
 */

/* 3200/2400/3500: hardware ports */
struct scdevice {	
	u_short	scd_abp;		/* Address Buffer Port (write only)*/
#define	scd_abp_ctlam	scd_abp		    /* 1st write (control, addr mod)*/
#define		SCD_ABP_CTLAM_V		0x8000	/* apply controls to command */
#define		SCD_ABP_CTLAM_WID	0x0400	/* data width, 0=16, 1=32 bit */
#define		SCD_ABP_CTLAM_WSW	0x0200	/* word swp, 0=no swp, 1=swp */
#define		SCD_ABP_CTLAM_BSW	0x0100	/* byte swp, 0=no swp, 1=swp */
					    /* addr modifiers in "vme_am.h" */
#define	scd_abp_pb_msb	scd_abp		    /* 2nd write (address of pb) */
#define	scd_abp_pb_lsb	scd_abp		    /* 3rd write (address of pb) */
	u_char	scd_pad_0[6];
	u_short	scd_atn;		/* Channel Attention Port (write only)*/
#define		SCD_ATN_TYPE0	0
#define		SCD_ATN_TYPE1	1
	u_char	scd_pad_1[6];
	u_short	scd_status;		/* Board Status Port (read only) */
#define		SCD_STATUS_BSY		0x0001	/* board is busy... */
#define		SCD_STATUS_RDY		0x0002	/* board is ready/initialized */
#define		SCD_STATUS_MERR		0x0010	/* parameter blk memory error */
#define		SCD_STATUS_MERR_MSK	0x00E0	/* attention port with error */
#define		SCD_STATUS_EMASK	0x00FC	/* mask for diag error field */
#define		SCD_STATUS_ESHFT	2	/* shift for diag error field */
#define		SCD_STATUS_EBITS		\
		    "\20\10CATTN\7CHAN\6FIFO\5DSEQ\4SRAM\3DRAM\2CSUM\1PROCESSOR"
#define		SCD_STATUS_BMASK	0xFF00	/* board id mask */
#define		SCD_STATUS_B3200	0x0000	/* 3200 SMD  Controller */
#define		SCD_STATUS_B3400	0x0100	/* 3400 ESDI Controller */
#define		SCD_STATUS_B3500	0x0200	/* 3500 SCSI Controller */
	u_char	scd_pad_2[6];
	u_short	scd_reset;		/* Controller Reset Port (write only) */
	u_char	scd_pad_3[6];
#define		SCD_RESET		1
	u_char	scd_pad_4[512 - 4*(2+6)];
};

/* 3200/3400/3500: Parameter Block */
struct sc_pb {
    u_int		pb_id;		/* unique command identifier */
#ifdef	SC_3500
    union pb {				/* 3500: */
	struct pb_scsi {		/* SCSI Command: TID != TID_SC */
	    u_char	scsi_pad0;
	    u_char	scsi_flags;
#define		SCSI_FLAGS_SGO		0x01	/*   Scatter/gather operation */
#define		SCSI_FLAGS_DIR_TOTARG	0x02	/*   xfer to the target */
#define		SCSI_FLAGS_DIR_FROMTARG	0x00	/*   xfer from the target */
#define		SCSI_FLAGS_DAT		0x04	/*   Data xfer in this op */
#define		SCSI_FLAGS_IRS		0x08	/*   Inhibit request sense */
#define		SCSI_FLAGS_DBV		0x80	/*   Data Bits Valid */
	    u_char	scsi_addrmod;		/* AM to VME memory */
	    u_char	scsi_tid;		/* SCSI targid id */
#define		SCSI_TID_SC		0xFF	/*   Targid ID for controller */
#define		SCSI_TID_FLOPPY		0xFE	/*   Targid ID for floppy */
    	    u_int	scsi_vmeaddr;		/* VME address */
	    u_int	scsi_xfrcnt;		/* transfer count */
	    union scsi_cdb scsi_cdb;		/* SCSI command block */
	}		pb_scsi;
	struct pb_setup {		/* 0x01: Setup Command */
	    u_char	setup_pad_0[2];
	    u_char	setup_addrmod;		/* AM to VME memory */
	    u_char	setup_tid;		/* targid id (0xFF) */
	    struct sc_clst *setup_clst;		/* command list start address */
	    u_char	setup_pad_1[2];
	    u_short	setup_dint;		/* done interrupt */
	    u_char	setup_cmd;		
#define		SETUP_CMD		0x01	/* setup command list */
	}		pb_setup;
	struct pb_stop {		/* 0x02: Stop Command */
	    u_char	stop_pad_0[3];
	    u_char	stop_tid;		/* targid id (0xFF) */
	    u_char	stop_pad_1[8];
	    u_char	stop_cmd;
#define		STOP_CMD		0x02	/* stop command list */
	}		pb_stop;
	struct pb_ident {		/* 0x05: Identify Command */
	    u_char	ident_pad_0[3];
	    u_char	ident_tid;		/* targid id (0xFF) */
	    u_char	ident_pad_1[8];
	    u_char	ident_cmd;
#define		IDENT_CMD		0x05
	}		pb_ident;
	struct pb_stat {		/* 0x06: Board Statistics */
	    u_char	stats_pad_0[2];
	    u_char	stats_addrmod;		/* AM to VME memory */
	    u_char	stats_tid;		/* targid id (0xFF) */
	    struct sc_stats *stat_stats;	/* where to put stat data */
	    u_char	stats_pad_1[8];
	    u_char	stats_cmd;
#define		STATS_CMD		0x06
	}		pb_stat;
	struct pb_gopt {		/* 0x07: General Options */
	    u_char	gopt_flags;
#define		GOPT_FLAG_BMT		0x04	/* Block Mode Transfers */
#define		GOPT_FLAG_PAR		0x02	/* Use Parity */
#define		GOPT_FLAG_DIS		0x01	/* Allow Disconnect/Reconnect */
	    u_char	gopt_throttle;
#define		GOPT_THROTTLE		8	/* 32 bytes- size of bus fifo */
	    u_char	gopt_iid;		/* initiator id */
#define		GOPT_IID		0x07
	    u_char	gopt_tid;		/* targid id (0xFF) */
	    u_char	gopt_pad_0[8];
	    u_char	gopt_cmd;
#define		GOPT_CMD		0x07	/* general options */
	}		pb_gopt;
	struct pb_uopt {
	    u_short	uopt_dtimeo;		/* disconnect timeout .1 sec */
	    u_char	uopt_uid;		/* unit id */
	    u_char	uopt_tid;		/* targid id (0xFF) */
	    u_short	uopt_stimeo;		/* select timeout millisec */
	    u_char	uopt_rtryctl;		/* retry controll */
#define		UOPT_RTRYCTL_RBE	0x10	/*   bus errors */
#define		UOPT_RTRYCTL_RCE	0x08	/*   command errors */
#define		UOPT_RTRYCTL_RPE	0x04	/*   parity errors */
#define		UOPT_RTRYCTL_ISB	0x02	/*   status block for retry */
#define		UOPT_RTRYCTL_INT	0x01	/*   interrupt for retry */
	    u_char	uopt_retrylim;		/* number of retries */
	    u_char	uopt_pad_0[3];
	    u_char	uopt_flags;
#define		UOPT_FLAG_IAT		0x04	/*   Inhibit ATN signal */
#define		UOPT_FLAG_SYN		0x02	/*   Synchronous transfers */
#define		UOPT_FLAG_IDI		0x01	/*   Inhibit Disconnect */
	    u_char	uopt_cmd;
#define		UOPT_CMD		0x08	/* unit options */
	}		pb_uopt;
    }	pb_pb;
#else	!SC_3500
					/* 3200/3400: */
    u_char		pb_addrmod;		/* AM to VME memory */
    u_char		pb_unit;		/* unit */
#define		PB_UNIT_NODISK		0x00	/*   Non-disk command */
#define		PB_UNIT(x)		((x&0x7)+1)
    u_char		pb_control;		/* I/O control group */
#define		PB_CONTROL_IOCG_MASK	0x0f
#define		PB_CONTROL_IOCG_0	0
#define		PB_CONTROL_IOCG_1	1
    u_char		pb_command;		/* command to execute */
						/* 33 Support    */
 						/* 24            */
 						/* 00            */
 						/* 00 DEFINITION */
#define	PB_COMMAND_SETUPCL		0x01	/* xx setup command list */
#define	PB_COMMAND_STOPCL		0x02	/* xx stop command list */
#define	PB_COMMAND_IDENT		0x05	/* xx identify */
#define	PB_COMMAND_STATS		0x06	/* xx board statistics */
#define	PB_COMMAND_GOPT			0x07	/* xx general options */
#define	PB_COMMAND_SETIOCG		0x08	/* xx init IO control group */
#define	PB_COMMAND_DIAG			0x09	/* xx board selftest */
#define	PB_COMMAND_SETCONF		0x10	/* xx configure disk */
#define	PB_COMMAND_SETDPARAM		0x11	/* xx define disk params */
#define	PB_COMMAND_GETCONFIG		0x12	/* xx return disk config */
#define	PB_COMMAND_INTERROGATE		0x13	/* x  interrogate SMD disk */
#define	PB_COMMAND_GESDICONF		0x13	/*  x return ESDI config */
#define	PB_COMMAND_TAGSTATUS		0x14	/* x  do tag/return status */
#define	PB_COMMAND_VSTATUS		0x14	/*  x return vendor status */
#define	PB_COMMAND_SERIALCMD		0x17	/*  x issue ESDI serial */
#define	PB_COMMAND_READ			0x18	/* xx read */
#define	PB_COMMAND_WRITE		0x19	/* xx write */
#define	PB_COMMAND_SREAD		0x1A	/* xx scatter read */
#define	PB_COMMAND_GWRITE		0x1B	/* xx gather write */
#define	PB_COMMAND_FORMAT		0x20	/* xx format tracks */
#define	PB_COMMAND_VERIFY		0x21	/* xx verify */
#define	PB_COMMAND_SLIPSEC		0x22	/* xx slip sector */
#define	PB_COMMAND_MAPSEC		0x23	/* xx map sector */
#define	PB_COMMAND_MAPTRACK		0x24	/* xx map track */
#define	PB_COMMAND_RDEFECT		0x25	/* xx read defect data */
#define	PB_COMMAND_IGNOREID		0x28	/* x  ignore id read data */
#define	PB_COMMAND_READLONG		0x29	/* xx read long */
#define	PB_COMMAND_WRITELONG		0x2A	/* xx write long */
#define	PB_COMMAND_READID		0x2B	/* xx read a single id */
#define	PB_COMMAND_READTID		0x2C	/* xx read a track of id's */
#define	PB_COMMAND_REZERO		0x2D	/* xx rezero */
#define	PB_COMMAND_SEEK			0x2E	/* xx perform a seek */
#define	PB_COMMAND_START		0x30	/*  x start spindle motor */
#define	PB_COMMAND_STOP			0x31	/*  x stop spindle motor */
#define	PB_COMMAND_WRITEMAP		0x38	/* xx write defect map */
#define	PB_COMMAND_READMAP		0x39	/* xx read defect map */
#define	PB_SET(pb, command, unit, control, id)			{\
		bzero((caddr_t)(pb), sizeof(struct sc_pb));	\
		(pb)->pb_command	= command;		\
		(pb)->pb_control	= control;		\
		(pb)->pb_unit		= unit;			\
		(pb)->pb_id		= id;			}
    union pb {
	struct pb_std {			/* Standard Command */
	    u_int	std_daddr;		/* starting sector # */
	    u_int	std_vmeaddr;		/* VME address to read/write */
	    u_char	std_pad_0[2];
	    u_short	std_blkcnt;		/* # of blocks to read/write */
	}		pb_std;
	struct pb_setup {		/* 0x01: Setup Command */
	    u_char	setup_pad_0[2];
	    u_short	setup_dint;		/* done interrupt */
	    struct sc_clst *setup_clst;		/* command list start address */
	    u_char	setup_pad_1[3];
	    u_char	setup_list;		/* command list # (1-7) */
	}		pb_setup;
	struct pb_stop {		/* 0x02: Stop Command */
	    u_char	stop_pad_0[11];
	    u_char	stop_list;		/* command list # (1-7) */
	}		pb_stop;
	struct pb_stat {		/* 0x06: Board Statistics */
	    u_char	stat_pad_0[4];
	    struct sc_stats *stat_stats;	/* where to put stat data */
	    u_char	stat_pad_1[3];
	    u_char	stat_clear;		/* clear statistics != 0 */
	}		pb_stat;
	struct pb_gopt {		/* 0x07: General Options */
#define	    gopt_throttle	pb_addrmod	/* KLUDGE */
#define		GOPT_THROTTLE	8		/* 32 bytes- size of bus fifo */
	    u_short	gopt_sbintr;		/* status block interrupts */
#define		GOPT_SB_WDL	0x01		/*   3200: Write Data Loaded */
#define		GOPT_SB_DTE	0x02		/*   Retries and Corrections */
#define		GOPT_SB_IDE	0x04		/*   ID/interface errors */
#define		GOPT_SB_VST	0x10		/*   3400: vendor status */
	    u_short	gopt_sbenable;		/* status block enables */
	    u_char	gopt_pad_0[8];
	}		pb_gopt;
	struct pb_iocg {		/* 0x08: Initialize IOCG */
	    u_short	iocg_cache;		/* cache control */
#define		IOCG_CACHE_SEA		0x0001	/*   search cache */
#define		IOCG_CACHE_CRD		0x0002	/*   save read data in cache */
#define		IOCG_CACHE_RAP		0x0004	/*   read ahead priority */
#define		IOCG_CACHE_CWT		0x0008	/*   save write data in cache */
#define		IOCG_CACHE_SRD		0x0010	/*   sort reads */
#define		IOCG_CACHE_SWT		0x0020	/*   sort writes */
#define		IOCG_CACHE_ZLI		0x0080	/*   inhibit zero latency */
#define		IOCG_CACHE_XHD		0x0100	/*   read ahead across head */
#define		IOCG_CACHE_XCY		0x0200	/*   read ahead across cyl */
#define		IOCG_CACHE_BITS 	\
			"\20\12XCY\11XHD\10ZLI\6SWT\5SRD\4CWT\3RAP\2CRD\1SEA"
	    u_char	iocg_rahead;		/* read ahead */
	    u_char	iocg_rcvry;		/* recovery */
#define		IOCG_RCVRY_IGE		0x01	/*   ignore ECC */
#define		IOCG_RCVRY_COR		0x02	/*   disable error correction */
#define		IOCG_RCVRY_EXT		0x04	/*   apply trk/data separator */
#define		IOCG_RCVRY_BITS		"\20\3EXT\2COR\1IGE"
	    u_char	iocg_pad_0[2];
	    u_char	iocg_dretry;		/* maximum data retries */
	    u_char	iocg_ndretry;		/* maximum non-data retries */
	    u_char	iocg_pad_1[4];
	}		pb_iocg;
	struct pb_confd {		/* 0x10: Configure Disk */
	    u_short	confd_nbps;		/* bytes per sector */
	    u_short	confd_ncyl;		/* cylinders per disk */
	    u_char	confd_nspares;		/* # of spare sectors per trk */
	    u_char	confd_nspt;		/* sectors per track */
	    u_char	confd_nhead;		/* heads per cylinder */
	    u_char	confd_shead;		/* 3200: 1st head for volume */
	    u_char	confd_pad_0[3];		/* reserved */
	    u_char	confd_flags;		/* 3200: drive info */
#define		CONFD_FLAGS_SSP		0x01	/*   short sector present */
#define		CONFD_FLAGS_EAD		0x02	/*   1 => SMD-E interface */
#define		CONFD_FLAGS_MSK		0x03
#define		CONFD_FLAGS_BITS	"\20\2SMDE\1SSP"
	}		pb_confd;
	struct pb_dparam {		/* 0x11: Define Disk Parameters */
	    u_char	dparam_intlv;		/* interleave factor to use */
	    u_char	dparam_hdskew;		/* head skew to use */
	    u_char	dparam_cyskew;		/* cylinder skew to use */
	    u_char	dparam_hgskew;		/* 3400: Head group skew */
	    u_short	dparam_rcvry;		/* 3200: data recovery */
#define		DPARAM_RCVRY_DBV	0x03ff	/*   Data bus value */
#define		DPARAM_RCVRY_TAG	(4<<12)	/*   tag # (1 to 6) */
	    u_char	dparam_gap1;		/* 3200: ID preamble length */
	    u_char	dparam_gap2;		/* 3200: data preamble length */
	    u_char	dparam_pad_0[4];
	}		pb_dparam;
	struct pb_itrs {		/* 0x14: Tag/Return Status (3200) */
	    u_char	itrs_pad_0[2];
	    u_short	itrs_data;		/* data to send */
	    u_char	itrs_pad_1[2];
	    u_short	itrs_tag;		/* tag # */
	    u_char	itrs_pad_2[4];
	}		pb_itrs;
	struct pb_fmtv {		/* 0x20,0x21: Format and Verify */
	    u_int	fmtv_sector;		/* starting sector # */
	    u_char	fmtv_pad_0[4];
	    u_int	fmtv_nsector;		/* # of blocks */
	}		pb_fmtv;
	struct pb_smap {		/* 0x22-0x24: Slip/Map Sector/Trk */
	    u_int	smap_baditem;		/* bad track or sector */
	    u_int	smap_alternate;		/* alternate track or sector */
	    u_char	smap_pad_0[2];		/* reserved */
	    u_short	smap_rcvry;		/* recover data in error? */
#define		SMAP_RECOVER_NO		0x00	/*   no */
#define		SMAP_RECOVER_NOTERR	0x01	/*   if no error */
#define		SMAP_RECOVER_ONERR	0x01	/*   with error */
	}		pb_smap;
    }	pb;
#endif	!SC_3500
};

/* 3200/3400/3500: Status Block */
union sc_sb {
#ifdef	SC_3500
    struct sb {			/* 3500: */
	u_int	sb_id;			/* command identifier */
	u_char	sb_xxx;			/* reserved */
	u_char	sb_scsi_status;		/* scsi status completion byte */
	u_char	sb_error;		/* errr/retry/status condition code */
	u_char	sb_flag;		/* type of status block and results */
#define		SB_FLAG_CC	0x80	/*   Command complete, last block */
#define		SB_FLAG_ERR	0x40	/*   Error, check error code */
#define		SB_FLAG_RTY	0x20	/*   Retry required */
#define		SB_FLAG_DTT	0x10	/*   Data Transfer Truncated */
#define		SB_FLAG_CON	0x04	/*   Continued status block */
#define		SB_FLAG_SOFT	0x02	/*   Soft Error */
#define		SB_FLAG_BITS	"\20\10CC\7ERR\6RETRY\5DTT"
	u_char	sb_scsi_class;
	u_char	sb_scsi_seg;
	u_char	sb_scsi_flag;
	u_char	sb_scsi_info3;
	u_char	sb_scsi_info4;
	u_char	sb_scsi_info5;
	u_char	sb_scsi_info6;
	u_char	sb_scsi_xlen;
    }		sb_sb;
#else	SC_3500
    struct sb {			/* 3200/3400: */
	u_int	sb_id;			/* command identifier */
	u_short	sb_dstatus;		/* drive error information */
#define		SB_DSTATUS_BITS_3200	\
"\20\20SEC\17IND\16ADM\15WRP\14DSR\13SER\12ONC\11RDY\5WRP\4FLT\3SER\2ONC\1RDY"
#define		SB_DSTATUS_BITS_3400	\
"\20\17RMNP\16RMWP\15WPFM\12STOPED\11PRESET\10CPARITY\7IFAULT\6CFAULT\5SFAULT\4WGATE\3VUSTAT\2WFAULT\1CMEDIA"
	u_char	sb_error;		/* errr/retry/status condition code */
	u_char	sb_flag;		/* type of status block and results */
#define		SB_FLAG_CC	0x80	/*   Command complete, last block */
#define		SB_FLAG_ERR	0x40	/*   Error, check error code */
#define		SB_FLAG_RTY	0x20	/*   Retry required */
#define		SB_FLAG_COR	0x10	/*   3200/3400: Correction required */
#define		SB_FLAG_CON	0x04	/*   3400: Continuation status block */
#define		SB_FLAG_BITS	"\20\10CC\7ERR\6RETRY\5CORR\3CON"
	u_int	sb_daddr;		/* disk address of errr/retry/status */
#define		SB_ERRDATA_UNDEF -1	/*   undefined */
    }		sb_sb;
#endif	SC_3500
    struct sb_ident { 		/* 0x05: Identify */
	u_int	ident_id;		/* identifier */
	u_char	ident_fwrev;		/* firmware revision level */
	u_char	ident_engrev;		/* Engineering revision level */
	u_char	ident_error;		/* error code */
	u_char	ident_flag;		/* status */
	u_char	ident_oflag;		/* configuration of board */
#define 	IDENT_OFLAG_ND	0x01	/*   3200: 1 = 4-drive , 0 = 2-drive */
/* 3400 ??? */
#define 	IDENT_OFLAG_FPY	0x01	/*   3500: 1 = have floppy */
	u_char	ident_day;		/* day the firmware was generated */
	u_char	ident_month;		/* month the firmware was generated */
	u_char	ident_year;		/* year the firmware was generated */
    }		sb_ident;
    struct sb_itrs {
	u_int	itrs_id;		/* identifier */
	u_char	itrs_pad_0[2];
	u_char	itrs_error;		/* error code */
	u_char	itrs_flag;		/* status */
	u_char	itrs_pad_1[3];
	u_char	itrs_data;		/* drive data */
    }		sb_itrs;
};

/* 3200/3400/3500: Extended (type-0 channel attention) Parameter Block */
struct sc_xpb {
	struct sc_pb	xpb_pb;		/* standard parameter block */
	u_char		xpb_pad_0[2];
	u_short		xpb_dint;	/* done interrupt */
#define	DINT_LEV_SHFT		8
#define	DINT_SID_MSK		0x00FF
	u_char		xpb_pad_1[4];
	union sc_sb	xpb_sb;		/* status block */
};

/* 3200/3400/3500: Command list (type-1 channel attention) Parameter Blocks */
struct sc_clst {
	u_int		clst_pbin;	/* parameter block in index */
	u_int		clst_pbout;	/* parameter block out index */
	u_int		clst_sbin;	/* status block in index */
	u_int		clst_sbout;	/* status block out index */
	u_int		clst_pbsize;	/* paramter block area size */
	u_int		clst_sbsize;	/* status block area size */
	u_int		clst_resv1;
	u_int		clst_resv2;
#define	SCNPB		0x40		/* Max. # of parameter blocks */
#define SCNPBMSK	0x3f		/* mask for valid sc_pb block index */
	struct sc_pb	clst_pb[SCNPB]; /* parameter blocks */
#define	SCNSB		0x80		/* Max. # of status blocks */
#define	SCNSBMSK	0x7f		/* mask for valid sc_sb index */
	union sc_sb	clst_sb[SCNSB]; /* status blocks */
};

/* 3200/3400/3500: Structure for the scatter/gather descriptor entry */
struct sc_scat {
    struct sc_scat	*scat_next;
    struct scat_desc {
	u_char		desc_addrmod;
	u_char		desc_lenh;
	u_short		desc_len;
	u_int		desc_vmeaddr;
    }			scat_desc[8];
};

/* 3200/2400/2500: Statistics Data Block */
struct sc_stats {
	u_int	stats_commands;		/* total # of commands */
#ifdef	SC_3500
	u_int	stats_command_id[8];	/* # of commands to id #*/
	u_int	stats_scsi_chk;		/* total # of commands */
	u_int	stats_commands_fl;	/* # of commands to floppy */
	struct	stats_fl {		/* floppy info */
	    u_int	fl_commands;	/* number of commands */
	    u_int	fl_sec;		/* number of sectors xfered */
	    u_short	fl_soft;	/* number of soft errors */
	    u_short	fl_hard;	/* number of hard errors */
	}	stats_fl[4];
#else	SC_3500
	u_int	stats_reads;		/* # of disk reads */
	u_int	stats_diskrd;		/* sectors read from disk */
	u_int	stats_cacherd;		/* sectors read from cache */
	u_int	stats_writes;		/* # of disk writes */
	u_int	stats_diskwr;		/* sectors written to disk */
	struct 	sc_stats_d {		/* per drive stats */
	    u_short	d_seek;		/* drive n: # seek errors */
	    u_short	d_iferr;	/* drive n: # interface errors */
	    u_short	d_ecccor;	/* drive n: # ecc corrections */
	    u_short	d_nonecc;	/* drive n: # non-ecc data errors */
	    u_short	d_altseek;	/* drive n: # alternate seeks */
	    u_short	d_corfail;	/* drive n: # ecc correction failures */
	}	stats_d[4];
#endif	SC_3500
};

/* 3200/3400: seek to specific head/cylinder */
struct sc_look {
	u_short	look_cyl;
	u_char	look_head;
	u_char	look_sec;
};

/* 3200/3400: Return Drive Configuration Data Block */
struct sc_dconf {
	u_short	dconf_bytsec;		/* bytes per sector */
	u_short	dconf_cyldsk;		/* cylinders per disk */
	u_char	dconf_nspares;		/* # of spare sectors per track */
	u_char	dconf_sectrk;		/* sectors per track */
	u_char	dconf_headcyl;		/* heads per cylinder */
	u_char	dconf_bhead;		/* head offset for this volume */
	u_char	dconf_zero1[3];		/* zeros */
	u_char	dconf_flags;		/* 3200: as in configure */
	u_int	dconf_secdsk;		/* # of logical sectors per disk */
	u_char	dconf_intlv;		/* interleave factor */
	u_char	dconf_hdskew;		/* head skew factor */
	u_char	dconf_cyskew;		/* cylinder skew factor */
	u_char	dconf_hgskew;		/* 3400: Head group skew */
	u_short	dconf_rcvry;		/* 3200: data recovery */
	u_char	dconf_idpre;		/* 3200: id preamble length */
	u_char	dconf_datapre;		/* 3200 data preamble length */
	u_int	dconf_zero3;		/* zero */
	u_int	dconf_zero4;		/* zero */
};

/* 3400: Return Configuration of ESDI drive Data Block */
struct sc_esdiconf {
	u_short	esdiconf_gc;		/* general configuration */
#define		ESDICONF_GC_TAPE	0x8000	/* Tape drive */
#define 	ESDICONF_GC_TOLGAP	0x4000	/* Format speed gap req */
#define 	ESDICONF_GC_TRKOFF	0x2000	/* Track offset option avail */
#define 	ESDICONF_GC_DATAOFF	0x1000	/* Data strobe offset avail */
#define 	ESDICONF_GC_SPEEDTOL	0x0800	/* RPM speed tolerance > 0.5% */
#define 	ESDICONF_GC_XFER10	0x0400	/* Transfer > 10MHz */
#define 	ESDICONF_GC_XFER510	0x0200	/* Transfer > 5MHz, <= 10MHz */
#define 	ESDICONF_GC_XFER5	0x0100	/* Transfer <= 5MHz */
#define 	ESDICONF_GC_REMOV	0x0080	/* Removable cartridge drive */
#define 	ESDICONF_GC_FIXED	0x0040	/* Fixed drive */
#define 	ESDICONF_GC_MOTORCTL	0x0020	/* Spindle motor control ok */
#define 	ESDICONF_GC_HDSWLONG	0x0010	/* Head switch time > 15 uS */
#define 	ESDICONF_GC_RLL		0x0008	/* RLL encoded (not MFM) */
#define 	ESDICONF_GC_CTLSOFT	0x0004	/* Controller soft-sectored */
#define 	ESDICONF_GC_DRVHARD	0x0002	/* Drive hard-sectored */
#define 	ESDICONF_GC_CTLHARD	0x0001	/* Controller hard-sectored */
	u_short	esdiconf_fixcyl; 	/* # of fixed cylinders */
	u_short	esdiconf_remcyl;	/* # of removable cylinders */
	u_char	esdiconf_remhead;	/* # of removable heads */
	u_char	esdiconf_fixhead;	/* # of fixed heads */
	u_short	esdiconf_minbytrk;	/* min unformatted bytes per track */
	u_short	esdiconf_bytesec;	/* unformatted bytes per sector */
	u_char	esdiconf_resv0;		/* reserved */
	u_char	esdiconf_sectrk;	/* sectors per track */
	u_char	esdiconf_isgbyte;	/* isg bytes after index */
	u_char 	esdiconf_minisg;	/* minimum isg bytes */
	u_char	esdiconf_spare;		/* spare */
	u_char	esdiconf_plosync;	/* bytes in plo sync */
	u_short	esdiconf_nwords;	/* # of words of vendor-unique status */
	u_short	esdiconf_resv[5];	/* reserved */
	u_char	esdiconf_vendid;	/* vendor id */
	u_char	esdiconf_vendmodel;	/* vendor model */
	u_short	esdiconf_statbits;	/* general drive status bits */
#define		ESDICONF_DS_NOREMOV	0x4000	/* non-removable media */
#define 	ESDICONF_DS_WPREM	0x2000	/* Write prot, removable */
#define 	ESDICONF_DS_WPFIX	0x1000	/* Write prot, fixed */
#define 	ESDICONF_DS_SPINDWN	0x0200	/* Spindle motor stopped */
#define 	ESDICONF_DS_POR		0x0100	/* Power on reset exist */
#define 	ESDICONF_DS_CMDPARITY	0x0080	/* Command data parity fault */
#define 	ESDICONF_DS_INTFLT	0x0040	/* Interface fault */
#define 	ESDICONF_DS_INVCMD	0x0020	/* Invalid/unimp cmd fault */
#define 	ESDICONF_DS_SEEKFLT	0x0010	/* Seek fault */
#define 	ESDICONF_DS_TOFLT	0x0008	/* Write gate fault */
#define 	ESDICONF_DS_STATAVAIL	0x0004	/* Vendor-unique status avail */
#define 	ESDICONF_DS_WRTFLT	0x0002	/* Write fault */
#define 	ESDICONF_DS_MEDIACHG	0x0001	/* Removable media changed */
	u_short	esdiconf_resv1;		/* reserved */
};

/* 3200: SMD disk manfacturer defect structure */
struct sc_smd_defect {
	u_char	smd_defect_zero1;	/* zero */
	u_char	smd_defect_x19;		/* Constant (0x19) */
	u_short	smd_defect_cylinder;	/* cylinder # */
	u_char	smd_defect_head;	/* head # */
	u_char	smd_defect_zero2;	/* zero */
	u_short	smd_defect_pos1;	/* position 1 */
	u_short	smd_defect_len1;	/* length 1 */
	u_short	smd_defect_pos2;	/* position 2 */
	u_short	smd_defect_len2;	/* length 2 */
	u_short	smd_defect_pos3;	/* position 3 */
	u_short	smd_defect_len3;	/* length 3 */
	u_short	smd_defect_pos4;	/* position 4 */
	u_short	smd_defect_len4;	/* length 4 */
	u_char	smd_defect_zero3;	/* zero */
	u_char	smd_defect_xf0;		/* Constant (0xf0) */
};

/* 3200: track of id's */
struct sc_trkid {
	u_short	trkid_cyl;
	u_char	trkid_sec;
#define	TRKID_SEC_SHORT		0xFD
#define	TRKID_SEC_SPARE		0xFE
#define	TRKID_SEC_SLIP		0xFF
        u_char	trkid_head;
	u_char	trkid_alt;
#define	TRKID_ALT_NORMAL	0xFF
	u_char	trkid_flag;
#define	TRKID_FLAG_NORMAL	0xAA
#define	TRKID_FLAG_DEF_TRK	0xC3
#define	TRKID_FLAG_ALT_TRK	0x3C
#define	TRKID_FLAG_BAD_TRK	0x33
#define	TRKID_FLAG_DEF_SEC	0x5A
#define	TRKID_FLAG_ALT_SEC	0xA5
#define	TRKID_FLAG_BAD_SEC	0x35
};

/* 3200/3400/3500: Error codes (sb_error field) */
#define	SC_ERR_FIRMWARE		0x80

#ifdef	SC_3500
char	*sc_err_ascii[SC_ERR_FIRMWARE] = {
#else
char	*sc_err_ascii[SC_ERR_FIRMWARE] = {
#endif
	"\001Invalid command",				/* 0x01 */
	"\002Bad unit number",				/* 0x02 */
	"\003Bad unit type",				/* 0x03 */
	"\004Drive not configured",			/* 0x04 */
	"\005Transfer alignment",			/* 0x05 */
	"\006Bad logical sector",			/* 0x06 */
	"\007Bad number of sectors",			/* 0x07 */
	"\010Bad track starting sector",		/* 0x08 */
	"\011Bad number of sectors",			/* 0x09 */
	"\012Bad tag number",				/* 0x0a */
	"\013Reserved field not zero",			/* 0x0b */
	"\014Bad number of gather/scatter heads",	/* 0x0c */
	"\015Bad length of gather/scatter table",	/* 0x0d */
	"\016Command list stopped",			/* 0x0e */
	"\017Bad command list size",			/* 0x0f */
	"\020Bad command list number",			/* 0x10 */
	"\021State wrong for start/stop",		/* 0x11 */
#ifdef	SC_3500
	"\024VMEbus timeout",				/* 0x14 */
	"\025VMEbus error",				/* 0x15 */
	"\026Gather/scatter descriptor read error",	/* 0x16 */
	"\036SCSIbus select timeout",			/* 0x1e */
#define	SC_ERR_SCSISELTO	0x1E
	"\037SCSIbus disconnect timeout",		/* 0x1f */
	"\040SCSIbus parity error",			/* 0x20 */
	"\041Unexpected SCSIbus disconnect",		/* 0x21 */
	"\042Undefined or uninterpretable SCSI error",	/* 0x22 */
	"\043SCSI status",				/* 0x23 */
#define	SC_ERR_SCSISTATUS	0x23	
	"\044Unexpected SCSIbus phase",			/* 0x24 */
	"\045SCSI controller chip error",		/* 0x25 */
	"\046Synchronous negotiation error",		/* 0x26 */
	"\047SCSIbus reset during operation",		/* 0x27 */
#define	SC_ERR_SCSIRESET	0x27
	"\050Target Mode error",			/* 0x28 */
#else	SC_3500
/* TODO -- check 3400 accuracy */
	"\022VMEbus timeout",				/* 0x12 */
	"\023VMEbus error",				/* 0x13 */
	"\024Drive not present",			/* 0x14 */
	"\025Drive not ready",				/* 0x15 */
	"\034Seek error",				/* 0x1c */
	"\036Fault detected",				/* 0x1e */
	"\043Sector too short",				/* 0x23 */
	"\044Data ECC error",				/* 0x24 */
	"\045ID sync error",				/* 0x25 */
	"\046Header CRC error",				/* 0x26 */
	"\047Data sync error",				/* 0x27 */
	"\050Seek timeout",				/* 0x28 */
	"\051Data timeout",				/* 0x29 */
	"\052Misseek/bad format",			/* 0x2a */
	"\053Sector ID error",				/* 0x2b */
	"\054Direct access to bad sector/track",	/* 0x2c */
	"\055ECC correction performed",			/* 0x2d */
	"\056ECC correction failed",			/* 0x2e */
	"\057Incorrect sectors per track",		/* 0x2f */
	"\062Incorrect sectors per track",		/* 0x32 */
	"\063Incorrect bytes per sector",		/* 0x33 */
	"\064Preamble too long",			/* 0x34 */
	"\067Inconsistant config parameter",		/* 0x37 */
	"\071Attempt to init IOCG 0",			/* 0x39 */
	"\072Bad src in defect mapping",		/* 0x3a */
	"\073Bad dst in defect mapping",		/* 0x3b */
	"\074No spares left in track",			/* 0x3c */
#define	SC_ERR_ID(e)	 	\
		((e==0x25)|(e==0x26)|(e==0x29)|(e==0x2A)|(e==0x2B)|(e==0x2C))
#define	SC_ERR_SOFT(e)	\
		((e==0x24)|(e==0x2D))
#endif	SC_3500
	"\140Cache memory diagnostic error",		/* 0x60 */
	"\141Static ram error",				/* 0x61 */
	"\142PROM checksum error",			/* 0x62 */
	"\143Undefined diagnostic",			/* 0x63 */
};
