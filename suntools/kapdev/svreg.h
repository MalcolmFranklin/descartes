/* @(#) svreg.h 1.2@(#) Solbourne id 9/28/93 19:34:53 */
/*
 * Copyright 1991-1993 Solbourne Computer, Inc.
 */

/* Interphase V/SCSI 4110/4220 SCSI host adaptor: hardware interface */

/*
 * The interface to this controller is a window in short io space.
 * NOTE: host access to this shortio memory must be with 8 or 16bit operations.
 */
#define	SV_SHORTIO_SIZE	2048

/*
 * A number of structures use a short value to encode VMEbus address
 * information (AINFO: memory type, transfer type, address modifier):
 */
#define	AINFO_AMOD	0x00FF	/* VMEbus address modifier */
#define AINFO_XT	0x0C00	/* Transfer type*/
#define AINFO_XT_NORMAL	0x0000	/*   Normal VMEbus transfer */
#define AINFO_XT_BLK	0x0400	/*   Block Mode transfer */
#define AINFO_XT_BLACK	0x0800	/*   Black Hole transfer */
#define AINFO_XT_BLK64	0x0C00	/*   VME D64 block mode transfer */
#define AINFO_MT	0x0300	/* Memory Type */
#define	AINFO_MT_16BIT	0x0100	/*   16 Bit Memory type */
#define	AINFO_MT_32BIT	0x0200	/*   32 Bit Memory type */
#define	AINFO_MT_SHIO	0x0300	/*   Short I/O Memory type (G/S ONLY) */
#define AINFO_LINK	0x8000	/* for gather/scatter */

/*
 * A number of structures use a short value to encode SCSI
 * Unit Address information (UA: bus, id, lun):
 */
#define	UA_ID_MSK	0x0007	/* SCSI device id */
#define	UA_LUN_MSK	0x0038	/* SCSI logical unit number */
#define	UA_LUN_SFT	3
#define	UA_BUS		0x0040	/* SCSI bus */
#define	UA_BUS_PRI	0x0000	/* Primary scsi bus */
#define	UA_BUS_SEC	0x0040	/* Secondary scsi bus */
#define	UA_X		0x0080	/* Extended LUN (4220 only) */
#define	UA_X_ID_MSK	0x000F	/* Extended SCSI device id */
#define	UA_X_LUN_MSK	0x3F00
#define	UA_X_LUN_SFT	8

/*
 * Commands are passed to the controller as IO Parameter Blocks.
 * These can be in host memory, or in the host usable portion of shortio.
 */
struct sv_iopb {
    u_short	iopb_cmd;		/* Command Code for the IOPB */
#define		  CMD_SCSI_PASS	0x20	/*   SCSI Pass Through commands */
#define		  CMD_SCSI_RST	0x22	/*   SCSI Reset bus */
#define		  CMD_DIAG	0x40	/*   Perform Diagnostics */
#define		  CMD_CINIT	0x41	/*   Initialize Controller */
#define		  CMD_WQINIT	0x42	/*   Initialize workq */
#define		  CMD_CINIT_D	0x43	/*   Dump Initialization Parameters */
#define		  CMD_WQINIT_D	0x44	/*   Dump workq Parameters */
#define		  CMD_BUS_STAT	0x45	/*   Bus Status Inquiry */
#define		  CMD_CMD_STAT	0x46	/*   Command Status Inquiry */
#define		  CMD_TAG_CAN	0x48	/*   Cancel Command Tag */
#define		  CMD_FLUSH_WQ	0x49	/*   Flush workq */
#define		  CMD_C_RESTART	0x4b	/*   Restart Controller */
#define		  CMD_DEV_INIT	0x4c	/*   Device Reinitialize */
#define		  CMD_DEV_RESET	0x4d	/*   Issue Bus Device Reset */
#define		  CMD_DEV_ABORT	0x4e	/*   Issue Abort Message */
#define		  CMD_DWN_LOAD	0x4f	/*   Download Firmware Command */
#define		  CMD_SET_BCN	0x52	/*   Set Board Serial Number */
#define		iopb_ce		iopb_cmd/* Controller Error Code(CRSW_CE_ERR) */
#define		  CE_PANIC	0xff	/*   Firmware Paniced */
#define		  CE_NR_SCSI	0x86	/*   Non-recoverable scsi */
    u_short	iopb_copt;		/* Command options for the IOPB */
#define		  COPT_IE	0x0001	/*   Interrupt Enable */
#define		  COPT_POLLED	0x0000	/*   Polled Mode Command */
#define		  COPT_SCAT_GAT	0x0002	/*   Scatter Gather Enable */
#define		  COPT_NONSYNC	0x0004	/*   Suppress Synchronous Transfers */
#define		  COPT_FAST_SG	0x0008	/*   TODO KLUDGE: NO DOCUMENTATION */
#define		  COPT_NOTO	0x0040	/*   Suppress IOPB Timeout */
#define		  COPT_DIR	0x0100	/*   Transfer Direction */
#define		  COPT_DIR_WM	0x0000	/*     Write VMEbus Memory */
#define		  COPT_DIR_RM	0x0100	/*     Read VMEbus Memory */
#define		  COPT_FLSH_RPT	0x0100	/*   Reprot Flushed Commands */
#define		  COPT_FLSH_RIP	0x0100	/*   Reset In Progress NOT DOC */
#define		  COPT_WIDE	0x0800	/*   Communicate in WIDE mode */
#define		  COPT_QTAG_NO	0x0000	/*   No Queue Tag sent to Target */
#define		  COPT_QTAG_SMP	0x1000	/*   Simple Queue Tag sent to Target */
#define		  COPT_QTAG_ORD	0x2000	/*   Ordered Queue Tag sent to Target */
#define		  COPT_QTAG_HD	0x3000	/*   Head Queue Tag sent to Target */
#define		  COPT_DL_DEBUG	0x8000	/*   Enable debug console prints */
#define		  COPT_DL_ID	0x0010	/*   Download - Initialize Download */
#define		  COPT_DL_TP	0x0020	/*   Download - Transfer Packet */
#define		  COPT_DL_PF	0x0040	/*   Download - Program Flash */
#define		  COPT_DL_PM	0x0080	/*   Download - Program Memory */
/* XXX new RFC with more bits here for flash ... */
#define		  COPT_DL_S3	0x1000	/*   Download - 4byte srecord format */
#define		  COPT_SN_SN	0x0002	/*   Set BCN - Secondary Serial # */
#define		  COPT_SN_FS	0x8000	/*   Set BCN - Factory Serial # */
#define		iopb_panic_msg	iopb_copt
#define		iopb_nr_code	iopb_copt
    u_short	iopb_scbec;		/* SCSI status completion byte */
#define		  SCBEC_SCB_MSK	0xFF00	/*   see scsi.h... */
#define		  SCBEC_SCB_SFT	8
#define		  SCBEC_EC_MSK	0x00FF	/* Controller error codes */
#define		  EC_OK		0x00
#define		  EC_BUS_RESET	0x15
#define		  EC_NO_PORT	0x12
#define		  EC_SELTO	0x30
#define		  EC_XFERCNT	0x34
#define		  EC_XFER_EX	0x83
#define		  EC_VMEERR_MIN	0x20	/* range for VME bus errors */
#define		  EC_VMEERR_MAX	0x2F

#define		  EC_STRINGS	{					\
		/* 0x00    */ "\000OK",					\
		/* 0x01    */ "\001workq full",				\
		/* 0x02    */ "\002workq not initialized",		\
		/* 0x03    */ "\003first command not initialize",	\
		/* 0x04    */ "\004invalid command",			\
		/* 0x05    */ "\005invalid workq number",		\
		/* 0x06    */ "\006workq already init",			\
		/* 0x07    */ "\007reinit of a workq failed",		\
		/* 0x08    */ "\010SQM before init",			\
		/* 0x09    */ "\011command type not implemented",	\
		/* 0x0a    */ "\012invalid priority",			\
		/* 0x0b    */ "\013invalid burst count",		\
		/* 0x10    */ "\020reserved field not zero",		\
		/* 0x11    */ "\021issued SCSIbus reset",		\
		/* 0x12    */ "\022no secondary bus",			\
		/* 0x13    */ "\023SCSI id is our own",			\
		/* 0X14    */ "\024SCSIBus held in reset",		\
		/* 0x15    */ "\025aborted by SCSIbus reset",		\
		/* 0x16    */ "\026invalid page size in CIB",		\
		/* 0x17    */ "\027command tag search == 0",		\
		/* 0x18    */ "\030command on bus",			\
		/* 0x20    */ "\040DMA VMEbusError",			\
		/* 0x21    */ "\041DMA VMEbusTimeout",			\
		/* 0x23    */ "\043DMA invalid address",		\
		/* 0x24    */ "\044illegal memory type",		\
		/* 0x25    */ "\045bad transfer count",			\
		/* 0x26    */ "\046iopb VMEbusError",			\
		/* 0x27    */ "\047iopb VMEbusTimeout",			\
		/* 0x28    */ "\050iopb post VMEbusError",		\
		/* 0x29    */ "\051iopb post VMEbusTimeout",		\
		/* 0x2a    */ "\052iopb illegal address",		\
		/* 0x2b    */ "\053iopb post illegal address",		\
		/* 0x2c    */ "\054s/g VMEbusError",			\
		/* 0x2d    */ "\055s/g VMEbusTimeout",			\
		/* 0x2e    */ "\056s/g Invalid # elements",		\
		/* 0x30    */ "\060selection timeout ",			\
		/* 0x31    */ "\061reselect timeout",			\
		/* 0x32    */ "\062operation failed",			\
		/* 0x33    */ "\063invalid disconnect",			\
		/* 0x34    */ "\064transfer count mismatch",		\
		/* 0x35    */ "\065parity error",			\
		/* 0x40    */ "\100s/g odd count",			\
		/* 0x41    */ "\101s/g illegal memory type",		\
		/* 0x42    */ "\102s/g illegal address",		\
		/* 0x43    */ "\103s/g element count mismatch",		\
		/* 0x50    */ "\120buffer count too large",		\
		/* 0x51    */ "\121can't execute: ExCRB",		\
		/* 0x80    */ "\200command flushed on error",		\
		/* 0x81    */ "\201flush cancelled",			\
		/* 0x82 CE */ "\202unknown re-selection",		\
		/* 0x83    */ "\203transfer count exhausted",		\
		/* 0x84 CE */ "\204direction error",			\
		/* 0x86    */ "\206non-recoverable scsi error",		\
		/* 0x90    */ "\220incorrect hardware",			\
		/* 0x91    */ "\221invalid record format",		\
		/* 0x92    */ "\222illegal iopb value",			\
		/* 0x94    */ "\224invalid download op",		\
		/* 0x95    */ "\225bad seqn",				\
		/* 0x96    */ "\226bad CRC",				\
		/* 0x97    */ "\227translation error",			\
		/* 0x99    */ "\231bad packet count",			\
		/* 0x9a    */ "\232bad transfer count",			\
		/* 0x9b    */ "\233bad EPROM checksum",			\
		/* 0x9c    */ "\234illegal image",			\
		/* 0x9d    */ "\235bad EPROM load",			\
		/* 0xc0 CE */ "\300iopb type error",			\
		/* 0xc1 CE */ "\301iopb timeout",			\
		/* 0xff CE */ "\377controller panic",			\
		0}
    u_short	iopb_nr_scsi_code;
#define		  NR_SCSI_CODE_BUS_PRI	0x1000
#define		  NR_SCSI_CODE_BUS_SEC	0x2000
#define		  NR_SCSI_CODE_KNOWN	0x0800
#define		  NR_SCSI_STRINGS	{				\
		/* 0x00    */ "\000illegal fatal scsi error",		\
		/* 0x01    */ "\001bad sync msg",			\
		/* 0x02    */ "\002bad wide msg",			\
		/* 0x03    */ "\003unknown msg reject",			\
		/* 0x04    */ "\004msg reject in cmd",			\
		/* 0x05    */ "\005msg reject not in msg out",		\
		/* 0x06    */ "\006unimplemented msg",			\
		/* 0x20    */ "\040resel, no identify",			\
		/* 0x21    */ "\041reserved phase selected",		\
		/* 0x40    */ "\100Invalid msg out",			\
		/* 0x41    */ "\101reserved phase",			\
		/* 0x42    */ "\102phase glitch in non-data phase",	\
		/* 0x43    */ "\103Invalid timeout",			\
		0}
    u_char	iopb_vec_ok;		/* Normal Completion Vector */
    u_char	iopb_vec_err;		/* Error Completion Vector */
    u_short	iopb_ilev;		/* Interrupt Level */
    union	iopbcmd {
    struct	cmd_scsi {	/* CMD_SCSI_PASS: SCSI Pass Thru IOPB */
	u_short	_rsv_1;
	u_short	scsi_ainfo;		/* Address type and modifer */
	u_int	scsi_address;		/* Buffer Address */
	u_int	scsi_length;		/* Max-Transfer Length */
	u_short	_rsv_2[3];
	u_short	scsi_ua;		/* Unit address on SCSI bus */
	union scsi_cdb scsi_cdb;	/* SCSI Command Descriptor Block */
    }		cmd_scsi;
    struct	cmd_scsi_rst {	/* CMD_SCSI_RST: SCSI Bus Reset */
	u_short	scsi_rst_reserved[8];
	u_short	scsi_rst_bus;		/* SCSI Bus Number */
#define		  RST_BUS_PRI	0x0000	/*   Reset the Primary Bus */
#define		  RST_BUS_SEC	0x8000	/*   Reset the Secondary Bus */
    }		cmd_scsi_rst;
    struct	cmd_diag {	/* CMD_DIAG: Diagnostics Command */
	u_short	diag_reserved[8];
#define		DIAG_OK		0xFFFF	/* Test completed successfully */
	u_short	diag_rom;		/* ROM Test Results */
	u_short	diag_bufram;		/* Buffer RAM results */
	u_short	diag_event_ram;		/* Event Ram test Results */
	u_short	diag_scsi_port[2];	/* SCSI Port Register test */
    }		cmd_diag;
    struct	cmd_cinit {	/* CMD_CINIT: Initialize Controller */
				/* CMD_CINIT_D: Dump Init Parameters */
	u_short	_rsv_1;
	u_short	cinit_ainfo;		/* Address type and modifer */
					/*   Must be AINFO_MT_SHIO */
	u_int	cinit_offset;		/* Offset to  struct sv_cib */
	u_int	cinit_length;		/* sizeof(struct sv_cib) */
    }		cmd_cinit;
    struct	cmd_wqinit {	/* CMD_WQINIT: Initialize workq */
				/* CMD_WQINIT_D: Dump workq Parameters */
	u_short	wqinit_reserved[8];
	u_short	wqinit_workq;		/* workq Number */
	u_short	wqinit_wopt;		/* workq Options */
#define		  WOPT_IWQ	0x8000	/*   Initialize workq */
#define		  WOPT_RF	0x0020	/*   Report Frozen (RFC18) */
#define		  WOPT_AS	0x0010	/*   ??? */
#define		  WOPT_PE	0x0008	/*   Parity Enable */
#define		  WOPT_FE	0x0004	/*   Freeze on Error */
#define		  WOPT_TM	0x0002	/*   XXXX  */
#define		  WOPT_AE	0x0001	/*   Abort Enable  */
	u_short	wqinit_slots;		/* # of slots in the workq */
	u_short	wqinit_priority;	/* XXXX Priority Level */
#define	wqinit_ua	wqinit_priority
	u_short	wqinit_cmd_to;		/* max time cmd should take (265msec) */
#define		  CMD_TO_INF	0x0000	/*   Forever */
    }		cmd_wqinit;
    struct	cmd_bstat {	/* CMD_BUS_STAT: Bus Status Inquiry */
	u_int	bstat_tag_active;	/*   Driver Tag currently on SCSI bus */
	u_int	bstat_tag_busy[7];
#define		  BSTAT_SETUA(bstat, bus)	\
		  ((u_short *)(bstat))[0xf] = ((bus) ? UA_BUS_PRI : UA_BUS_SEC)
    }		cmd_bstat;
    struct	cmd_cstat {	/* CMD_CMD_STAT: Command Status Inquiry */
	u_short	cstat_reserved[0xA];
	u_int	cstat_tag;		/* Address type and modifer */
					/*   Must be AINFO_MT_SHIO */
	u_short	cstat_scode;
#define		  SCODE_NOT_FOUND	1
#define		  SCODE_NOT_INWQ	2
#define		  SCODE_ACTIVE		3
#define		  SCODE_BUSY		4
#define		  SCODE_DONEQ		5
#define		  SCODE_CMDQ		6
	u_short	cstat_last_cmd_issues;
	u_short	cstat_phase_sense;
    }		cmd_cstat;
    struct	cmd_tcan {	/* CMD_TAG_CAN: Cancel Command Tag */
	u_short	tcan_reserved[0xA];
	u_int	tcan_tag;
    }		cmd_tcan;
    struct	cmd_fwq {	/* CMD_FLUSH_WQ: Flush workq */
	u_short	fwq_reserved[8];
	u_short	fwq_wqn;
	u_short	fwq_info;
#define		  FWQ_INFO_NCMD_MSK	0x3fff
#define		  FWQ_INPROG_PRI	0x4000
#define		  FWQ_INPROG_SEC	0x8000
    }		cmd_fwq;
    struct	cmd_restart {	/* CMD_C_RESTART: Restart Controller */
	u_short	restart_reserved[9];
    }		cmd_restart;
    struct	cmd_devinit {	/* CMD_DEV_INIT: Device Reinitialize */
	u_short	devinit_reserved[9];
	u_short	devinit_ua;
    }		cmd_devinit;
    struct	cmd_devreset {	/* CMD_DEV_RESET: Issue Bus Device Reset */
	u_short	devreset_reserved[9];
	u_short	devreset_ua;
    }		cmd_devreset;
    struct	cmd_devabort {	/* CMD_DEV_ABORT: Issue Abort Message */
	u_short	devabort_reserved[9];
	u_short	devabort_ua;
    }		cmd_devabort;
    struct	cmd_dload {	/* CMD_DWN_LOAD: Download Firmware */
	u_short	_rsv_1;
	u_short	dload_ainfo;		/* Address type and modifer */
	u_int	dload_address;		/* Buffer Address */
	u_int	dload_length;		/* Max-Transfer Length */
	u_int	dload_csum;
	u_short	_rsv_2;
	u_short	dload_seqn;
    }		cmd_dload;
    struct	cmd_sbcn {	/* CMD_SET_BCN: Set Board Serial # */
	u_short	_rsv_1;
	u_short	_rsv_2;
	u_short	sbcn_cn[3];		/* Serial number */
    }		cmd_sbcn;
    }		cmd;			/* end command of union */
};

/*
 * The following structure is pointed to by the Controller Initialize Command
 * and the Dump Initialization Parameters Command
 */
struct	sv_cib	{		/* Controller Initialization Block */
    u_short	cib_ncqe;		/* Number of Command Queue Entries */
    u_short	cib_burst;		/* VMEbus DMA Burst count */
#define		  BURST_BM	0x8000	/*   4220: new burst mode format */
#define		  BURST_BM_FAIR	0x4000	/*   4220: FAIR */
#define		  BURST_BM_TOFF	0x0070
#define		  BURST_BM_TOFF_SHFT	4
#define		  BURST_BM_TON	0x0007
#define		  BURST_BM_TON_16	0	/* 16usec */
#define		  BURST_BM_TON_32	1	/* 32usec */
#define		  BURST_BM_TON_64	2	/* 64usec */
#define		  BURST_BM_TON_128	3	/* 128usec */
#define		  BURST_BM_TON_256	4	/* 256usec */
#define		  BURST_BM_TON_512	5	/* 512usec */
#define		  BURST_BM_TON_1024	6	/* 1024usec */
#define		  BURST_BM_TON_DONE	7	/* until done */
    u_short	cib_lvec_ok;		/* Normal Completion Level/Vector */
					/*   for Flush of workq */
    u_short	cib_lvec_cerr;		/* Controller Error Level/Vector */
#define		  LVEC_VEC_MSK	0x00ff
#define		  LVEC_LEV_MSK	0x0300
#define		  LVEC_LEV_SFT	8
    u_short	cib_hostid[2];		/* SCSI Bus ID */
#define		  HOSTID_MSK	0x07	/*   Mask for scsi bus id */
#define		  HOSTID_DFLT	0x40	/*   Use the default id */
    u_short	cib_crb_offset;		/* Command Response Block Offset */
    u_short	cib_sel_h;		/* Selection timeout in milli_second */
    u_short	cib_sel_l;
    u_short	cib_rsel_h;
    u_short	cib_rsel_l;
    u_short	cib_vmeto_h;		/* VME Time out in 32 milli-second */
    u_short	cib_vmeto_l;
    u_short	_rsv_1[2];
    u_short	cib_crb_ainfo;		/* struct sv_crb address information */
    u_short	cib_crb_adr_h;		/* struct sv_crb address/offset */
    u_short	cib_crb_adr_l;
    u_short	cib_erflags;		/* Error Recovery Flags */
#define		  CIB_ERFLAGS_FZ_RST	0x01 /* Freeze on Scsi Reset */
#define		  CIB_ERFLAGS_IDL_RST	0x02 /* Interrupt on idle Scsi Reset */
#define		  CIB_ERFLAGS_RNRSERR	0x04 /* Report NonRecover Scsi Errs */
#define		  CIB_ERFLAGS_FZ_ALL	0x08 /* Freeze all workq's on error */
    u_short	_rsv_2;
    u_short	cib_lvec_tmode;		/* Target Mode Level/Vector */
    u_short	cib_lvec_reset;		/* SCSIbus Reset Level/Vector */
    u_short	cib_sync[2];		/* per bus synchronous control info */
#define		  SYNC_OFF_MSK	0xFF00	/* max REQ/ACK offset for synchronous */
#define		  SYNC_OFF_SFT	8
#define		  SYNC_NEG_MSK	0x00FF	/* min xfer period (ns/4) */
};

/*
 * Structure of the controllers shortio space:
 */
struct	sv_device {
    struct	sv_mcsb	{	/* Master Control/Status Block */
	u_short	mcsb_msr;		/* Master Status Register */
#define		  MSR_CNA	0x0001	/*    Controller Not Available */
#define		  MSR_BOK	0x0002	/*    Board OK */
#define		  MSR_QFC	0x0004	/*    Queue Flush Complete */
	u_short	mcsb_mcr;		/* Master Control register */
#define		  MCR_SQM	0x0001	/*    Start Queue Mode */
#define		  MCR_FLQR	0x0004	/*    BROKEN. FLush Queue and Report */
#define		  MCR_FLQ	0x0800	/*    BROKEN. FLush Queue */
#define		  MCR_RESET	0x1000	/*    RESET controller */
#define		  MCR_SFEN	0x2000	/*    SysFail Enable */
	u_short	mcsb_iqar;		/* Interrupt on Queue Available Reg */
#define		  IQAR_IVEC_MSK	0x00FF	/*    Interrupt Vector */
#define		  IQAR_ILEV_MSK	0x0700	/*    Interrupt Level */
#define		  IQAR_ILEV_SFT	8
#define		  IQAR_IQEH	0x4000	/*    Interrupt on Queue Entry Half */
					/* 	problem with IQEH pre A16 */
#define		  IQAR_IQEA	0x8000	/*    Interrupt on Queue Entry Avail */
	u_short	mcsb_qhdp;		/* Queue head pointer */
	u_short	mcsb_thaw;		/* Thaw work Queue */
#define		  THAW_TWQ	0x0001	/*     Thaw workq */
#define		  THAW_TWQN_MSK	0x0f00	/*     Thaw workq Number */
#define		  THAW_TWQN_SFT	8
	u_short	_pad[3];
    }		sv_mcsb;
    struct	sv_cqe	{	/* Command Queue Entry */
	u_short	cqe_qecr;		/* Queue Entry Control Register */
#define		  QECR_GO	0x0001	/*    Go/Busy Bit */
#define		  QECR_BUSY	QECR_GO
#define		  QECR_AA	0x0002	/*    Abort Acknowledge */
#define		  QECR_HPC	0x0004	/*    High Priority Command */
#define		  QECR_FO	0x0010	/*    Fetch Offboard */
#define		  QECR_IOPB_MSK	0x0F00	/*    IOPB Type */
#define		  QECR_IOPB_SFT	8
	u_short	cqe_iopb_addr;		/* IOPB Address */
#define		cqe_ob_ainfo	cqe_iopb_addr	/* (offboard) addr info */
	u_int	cqe_tag;		/* Command Tag */
#define		cqe_ob_addr	cqe_tag		/* (offboard) address */
	u_char	cqe_iopb_length;	/* IOPB Length */
	u_char	cqe_workq;		/* workq Number */
	u_short	_pad;
    }		sv_mcqe;	/* Master Command Queue Entry */

    /* definition for onboard and offboard layout of CQE's and iopb's (hus) */
    union	sv_onoff {
#define		  SV_ONOFF_SPC		0x6d8
	u_char	onoff_spc[SV_ONOFF_SPC];
	struct sv_on {		/* structure of memory for onboard iopb's */
#define		  SV_NCQE_MAX_ON	31	/* max number of CQE's */
#define		  SV_NCQE_ON		SV_NCQE_MAX_ON
	    struct	sv_cqe	on_cqe[SV_NCQE_ON];	/* Cmd Queue Entry */
#if	SV_NCQE_ON < SV_NCQE_MAX_ON
	    struct	sv_cqe	on_cqe_pad[SV_NCQE_MAX_ON-SV_NCQE_ON];
#endif	SV_NCQE_ON < SV_NCQE_MAX_ON
	    struct	sv_iopb	on_iopb[SV_NCQE_ON];	/* onboard iopb's */
	}		on;
	struct sv_off {		/* structure of memory for offboard iopb's */
#define		  SV_NCQE_MAX_OFF	146
#define		  SV_NCQE_OFF		64
	    struct	sv_cqe	off_cqe[SV_NCQE_OFF]; /* Cmd Queue Entry */
#if	SV_NCQE_OFF < SV_NCQE_MAX_OFF
	    struct	sv_cqe	off_cqe_pad[SV_NCQE_MAX_OFF-SV_NCQE_OFF];
#endif	SV_NCQE_OFF < SV_NCQE_MAX_OFF
	}		off;
    }		sv_onoff;

    /* decleration for the rest of host usable space */
    struct	sv_iopb	sv_miopb;	/* hus: Master Command Queue iopb */
    struct	sv_cib	sv_cib;		/* hus: Controller Initialization Blk */

    struct	sv_crb	{	/* Command Response Block */
	u_short	crb_crsw;		/* Command response status word */
#define		  CRSW_CRBV	0x0001	/*   Command Response Block Valid  */
#define		  CRSW_CC	0x0002	/*   Command Complete  */
#define		  CRSW_ER	0x0004	/*   Error */
#define		  CRSW_EX	0x0008	/*   Exception */
#define		  CRSW_AQ	0x0010	/*   Abort Queue  */
#define		  CRSW_QMS	0x0020	/*   Queue Mode Select  */
#define		  CRSW_CQA	0x0040	/*   Command Queue Entry Available  */
#define		  CRSW_SC	0x0080	/*   Status Change */
#define		  CRSW_TIOPB	0x0200	/*   Target Mode IOPB Request */
#define		  CRSW_SRESET	0x0400	/*   SCSIbus was reset */
#define		  CRSW_SERROR	0x0800	/*   SCSIbus error (iff RSRSERR 4220) */
#define		  CRSW_QF	0x1000	/*   Queue Frozen (RFC18) */
#define		  CRSW_CE_ERR	(CRSW_SC|CRSW_ER|CRSW_CRBV)	/* ctlr error */
#define		  CRSW_BITS	\
	    "\20\14SERROR\13SRESET\12TIOPB\10SC\7CQA\6QMODE\5ABORTQ\4EX\3ER\2CC\1CRBV"
	u_short	_rsv_1;
	u_int	crb_tag;		/* Command Tag */
	u_char	crb_iopb_length;	/* IOPB Length */
	u_char	crb_workq;		/* workq Number */
	u_short	_rsv_2;
	struct	sv_iopb	crb_iopb;	/* Returned iopb */
    }	sv_crb;
    struct	sv_csb	{	/* Configuration Status Block (0x788) */
	u_short	csb_id;
#define		  ID_4220	0x4220
	u_char	_rsv_2;
	u_char	csb_prod_code[3];
	u_short	_rsv_3;
	u_char	_rsv_4;
	u_char	csb_prod_var;
	u_short	_rsv_5;
	u_char	_rsv_6;
	u_char	csb_fw_rev[3];
	u_short	_rsv_7;
	u_char	csb_fw_date[8];
	u_short	csb_ramsize_k;			/* new */
	u_short	csb_bsize_k;
	u_short	_rsv_9;
	u_char	csb_fecid[2];			/* RFC34: Front End Channel */
#define		  FECID_NCR710_SE	0x00
#define		  FECID_NCR710_DIFF	0x01
#define		  FECID_NCR720_SE	0x02
#define		  FECID_NCR720_DIFF	0x03
#define		  FECID_PRINTER		0x07
#define		  FECID_NCR710_DIFF_RM	0x0E
	u_char	csb_hostid[2];
	u_char	csb_lst_dev[2];
	u_char	csb_phase_sense[2];
#define		  PHASE_SENSE_PHASE_MSK	0x07	/* SCSIbus phase (see scsi.h) */
#define		  PHASE_SENSE_4210_BUSY	0x08	/* SCSIbus BUSY asserted */
#define		  PHASE_SENSE_4210_SEL	0x10	/* SCSIbus SEL asserted */
#define		  PHASE_SENSE_4210_ATTN	0x20	/* SCSIbus ATTN asserted */
#define		  PHASE_SENSE_4210_ACK	0x40	/* SCSIbus ACK asserted */
#define		  PHASE_SENSE_4210_REQ	0x80	/* SCSIbus REQ asserted */
#define		  PHASE_SENSE_4210_BITS	\
		  "\20\10REQ\7ACK\6ATTN\5SEL\4BUSY\3MSG\2CMD\1IN"
#define		  PHASE_SENSE_4220_ATTN	0x08	/* SCSIbus ATTN asserted */
#define		  PHASE_SENSE_4220_SEL	0x10	/* SCSIbus SEL asserted */
#define		  PHASE_SENSE_4220_BUSY	0x20	/* SCSIbus BUSY asserted */
#define		  PHASE_SENSE_4220_ACK	0x40	/* SCSIbus ACK asserted */
#define		  PHASE_SENSE_4220_REQ	0x80	/* SCSIbus REQ asserted */
#define		  PHASE_SENSE_4220_BITS	\
		  "\20\10REQ\7ACK\6BUSY\5SEL\4ATTN\3MSG\2CMD\1IN"
#define	csb_printer_status	csb_phase_sense
	u_char	csb_daughter_et;
#define		  DAUGHTER_ET_UNKNOWN	0x00
#define		  DAUGHTER_ET_SINGLE	0x01
#define		  DAUGHTER_ET_DIFF	0x02
	u_char	csb_daughter;
#define		  DAUGHTER_MSK		0x07
#define		  DAUGHTER_NONE		0x07
#define		  DAUGHTER_SCSI		0x06
#define		  DAUGHTER_PRINTER	0x04

	u_char	_rsv_c;
	u_char	csb_soft_dip;
#define		  SOFT_DIP_RESET_POW	0x01	/* Reset SCSIbus on Power up */
#define		  SOFT_DIP_CLR_SYS_BT	0x02	/* Clear SYSFAIL before test */
/* TODO....DIP */
	u_char	csb_sync_rate[2];
#define		  SYNC_RATE(ns)		((ns)/4)
	u_short	csb_fwqr;			/* frozen workq register */

	u_short	_pad[0x18];			/* Unused area.... */

	u_short	csb_oem_sn_p[3];		/* OEM Serial # primary */
	u_short	csb_oem_sn_s[3];		/* OEM Serial # secondary */
	u_short	csb_mfr_sn_p[3];		/* MFR Serial # primary */
	u_short	csb_mfr_sn_s[3];		/* MFR Serial # secondary */
    }	sv_csb;
};

/*
 *	offboard structure for cqe and iopb
 */
struct sv_off_cqe {
	struct sv_cqe	off_cqe;
	struct sv_iopb  off_iopb;
};
