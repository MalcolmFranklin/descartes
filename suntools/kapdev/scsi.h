/* @(#) scsi.h 1.2@(#) Solbourne id 11/17/93 09:24:01 */
/*
 * Copyright 1988-1993 Solbourne Computer, Inc.
 * All rights reserved.
 */

/* GENERIC SCSI DEFINITIONS */
#ifndef	_SCSI_H
#define	_SCSI_H

/* SCSI Bus Phase Definitions */
#define	SCSI_BUS_MSG		0x04	/* Message Bit */
#define	SCSI_BUS_CMD		0x02	/* Command/Data Bit */
#define	SCSI_BUS_IN		0x01	/* I/O Bit (relative to target) */
#define SCSI_PHASE_DATAOUT	(           0|           0|          0)
#define SCSI_PHASE_DATAIN	(           0|           0|SCSI_BUS_IN)
#define SCSI_PHASE_COMMAND	(           0|SCSI_BUS_CMD|          0)
#define SCSI_PHASE_STATUS	(           0|SCSI_BUS_CMD|SCSI_BUS_IN)
#define SCSI_PHASE_MSGOUT	(SCSI_BUS_MSG|SCSI_BUS_CMD|          0)
#define SCSI_PHASE_MSGIN	(SCSI_BUS_MSG|SCSI_BUS_CMD|SCSI_BUS_IN)
#define	SCSI_PHASE_NASCII	8
#define	SCSI_PHASE_ASCII	{ "DATA OUT", "DATA IN", "COMMAND", "STATUS", \
				  "-?-", "-??-", "MSG OUT", "MSG IN", }

struct scsi_ctlb {		/* SCSI command table */
	char	*ctlb_name;			/* name of command */
	int	ctlb_flags;			/* misc info about command */
#define		  CTLB_FLAGS_NODATA	0x0000	/*   no data transfered */
#define		  CTLB_FLAGS_DATA_OUT	0x0001	/*   data to target */
#define		  CTLB_FLAGS_DATA_IN	0x0002	/*   data from target */
#define		  CTLB_FLAGS_DATA_MSK	0x0003
#define		  CTLB_FLAGS_IOCTL_OK	0x0004	/*   command OK from ioctl */
	int	ctlb_cnt;			/* number of times cmd issues */
};
extern struct scsi_ctlb	scsi_ctlb[];
#define	SCSI_CTLB {							\
	{"testready",	CTLB_FLAGS_NODATA},		/* 0x00 */	\
	{"rezero",	CTLB_FLAGS_NODATA},		/* 0x01 */	\
	{NULL},								\
	{"sense",	CTLB_FLAGS_DATA_IN},		/* 0x03 */	\
	{"format",	CTLB_FLAGS_DATA_OUT},		/* 0x04 */	\
	{"blklim",	CTLB_FLAGS_DATA_IN},		/* 0x05 */	\
	{NULL},								\
	{"reassign",	CTLB_FLAGS_DATA_OUT},		/* 0x07 */	\
	{"read",	CTLB_FLAGS_DATA_IN},		/* 0x08 */	\
	{NULL},								\
	{"write",	CTLB_FLAGS_DATA_OUT},		/* 0x0A */	\
	{"seek",	CTLB_FLAGS_NODATA},		/* 0x0B */	\
	{"seekblk",	CTLB_FLAGS_NODATA},		/* 0x0C */	\
	{NULL}, {NULL},							\
	{"translate",	CTLB_FLAGS_DATA_IN},		/* 0x0F */	\
	{"filemark",	CTLB_FLAGS_NODATA},		/* 0x10 */	\
	{"space",	CTLB_FLAGS_NODATA},		/* 0x11 */	\
	{"inquiry",	CTLB_FLAGS_DATA_IN},		/* 0x12 */	\
	{NULL}, {NULL},							\
	{"mselect",	CTLB_FLAGS_DATA_OUT},		/* 0x15 */	\
	{"reserve",	CTLB_FLAGS_NODATA},		/* 0x16 */	\
	{"release",	CTLB_FLAGS_NODATA},		/* 0x17 */	\
	{"copy",	CTLB_FLAGS_DATA_OUT},		/* 0x18 */	\
	{"erase",	CTLB_FLAGS_NODATA},		/* 0x19 */	\
	{"msense",	CTLB_FLAGS_DATA_IN},		/* 0x1A */	\
	{"start",	CTLB_FLAGS_NODATA},		/* 0x1B */	\
	{"rdiag",	CTLB_FLAGS_DATA_IN},		/* 0x1C */	\
	{"sdiag",	CTLB_FLAGS_DATA_OUT},		/* 0x1D */	\
	{"prevent",	CTLB_FLAGS_NODATA},		/* 0x1E */	\
	{"readlog",	CTLB_FLAGS_DATA_IN},		/* 0x1F */	\
	{NULL}, {NULL}, {NULL}, {NULL}, {NULL},				\
	{"rcapac",	CTLB_FLAGS_DATA_IN},		/* 0x25 */	\
	{NULL}, {NULL},							\
	{"readx",	CTLB_FLAGS_DATA_IN},		/* 0x28 */	\
	{NULL},								\
	{"writex",	CTLB_FLAGS_DATA_OUT},		/* 0x2A */	\
	{"seekx",	CTLB_FLAGS_NODATA},		/* 0x2B */	\
	{NULL}, {NULL},							\
	{"writeverify",	CTLB_FLAGS_DATA_OUT},		/* 0x2E */	\
	{"verify",	CTLB_FLAGS_NODATA},		/* 0x2F */	\
	{NULL}, {NULL}, {NULL}, {NULL},					\
	{"prefetch",	CTLB_FLAGS_NODATA},		/* 0x34 */	\
	{"flush",	CTLB_FLAGS_NODATA},		/* 0x35 */	\
	{"cachelk",	CTLB_FLAGS_NODATA},		/* 0x36 */	\
	{"rdefect",	CTLB_FLAGS_DATA_IN},		/* 0x37 */	\
	{NULL}, {NULL}, {NULL},						\
	{"wbuffer",	CTLB_FLAGS_DATA_OUT},		/* 0x3B */	\
	{"rbuffer",	CTLB_FLAGS_DATA_IN},		/* 0x3C */	\
	{NULL}, {NULL}, {NULL},						\
	{NULL}, {NULL}, {NULL},	{NULL}, {NULL}, {NULL},	{NULL}, {NULL},	\
	{NULL}, {NULL}, {NULL},	{NULL}, {NULL}, {NULL},	{NULL}, {NULL},	\
	{NULL}, {NULL}, {NULL},	{NULL}, {NULL}, 			\
	{"mselectx",	CTLB_FLAGS_DATA_OUT},		/* 0x55 */	\
	{NULL}, {NULL}, {NULL},	{NULL}, 				\
	{"msensex",	CTLB_FLAGS_DATA_IN},		/* 0x5A */	\
	}
extern int		nscsi_ctlb;
#define	NSCSI_CTLB	(sizeof(scsi_ctlb)/sizeof(struct scsi_ctlb))

/* scsi command codes, used to index into scsi_cmd table */
#define SC_TESTREADY	0x00			/* 0 test unit ready */
#define SC_REZERO	0x01			/* 0 rezero unit */
#define SC_REWIND	SC_REZERO		/* 0 rewind unit */
#define SC_BLKADR	0x02			/* 0 request block address */
#define SC_SENSE	0x03			/* 0 request sense */
#define SC_FORMAT	0x04			/* 0 format unit */
#define SC_BLKLIM	0x05			/* 0 read block limits */
#define SC_FORMAT_TRACK	0x06			/* 0 format single track */
#define SC_REASSIGN	0x07			/* 0 re-assign blocks */
#define SC_READ 	0x08			/* 0 read data */
#define SC_WRITE	0x0A			/* 0 write data */
#define SC_SEEK 	0x0B			/* 0 seek */
#define SC_SEEKBLK 	0x0C			/* 0 seek block */
#define SC_TRANSLATE 	0x0F			/* 0 translate block */
#define SC_FILEMARK 	0x10			/* 0 write file mark(s) */
#define SC_SPACE 	0x11			/* 0 space */
#define SC_INQUIRY	0x12			/* 0 inquiry */
#define SC_MODE_SELECT	0x15			/* 0 mode select */
#define SC_RESERVE	0x16			/* 0 reserve */
#define SC_RELEASE	0x17			/* 0 release */
#define SC_COPY		0x18			/* 0 copy */
#define SC_ERASE	0x19			/* 0 erase tape */
#define SC_MODE_SENSE	0x1A			/* 0 mode sense */
#define SC_STARTSTOP	0x1B			/* 0 start/stop unit */
#define SC_LOAD		SC_STARTSTOP		/* 0 load/unload unit */
#define SC_R_DIAG	0x1C			/* 0 receive diagnostic rslt */
#define SC_S_DIAG	0x1D			/* 0 send diagnostic */
#define SC_PREVENT	0x1E			/* 0 prevent medium release */
#define SC_READ_LOG	0x1F			/* 0 VU: read log */
#define SC_RCAPAC	0x25			/* 1 read capacity */
#define SC_READX	0x28			/* 1 extended read data */
#define SC_WRITEX	0x2A			/* 1 extended write data */
#define SC_SEEKX	0x2B			/* 1 extended seek */
#define SC_WRITE_VERIFY	0x2E			/* 1 write and verify */
#define SC_VERIFY	0x2F			/* 1 verify data */
#define SC_PREFETCH	0x34			/* 1 prefetch into cache */
#define SC_FLUSH	0x35			/* 1 flush cache */
#define SC_CACHELK	0x36			/* 1 lock/unlock cache */
#define SC_RDEFECT	0x37			/* 1 read defect list */
#define SC_WBUFFER	0x3B			/* 1 write buffer */
#define SC_RBUFFER	0x3C			/* 1 read buffer */
#define SC_MODE_SELECTX	0x55			/* 1 mode select */
#define SC_MODE_SENSEX	0x5A			/* 1 mode sense */

union	scsi_cdb {		/* SCSI command block */
    u_char	cdb_byte[12];
    struct	cdb {		    /* COMMON PORTION */
	u_char	cdb_cmd;
#define		  CMD_GRP_SHIFT	5
#define		  CMD_CODE_MASK	0x1F
#define 	  CMD_GRP(cmd)	((cmd) >> CMD_GRP_SHIFT)
#define		  CMD_CODE(cmd)	((cmd) & CMD_CODE_MASK)
	u_char	cdb_lun:3;
	u_char	cdb_tag:5;
    }		cdb;
#define CDB_LEN(cmd)	((CMD_GRP(cmd)==0)?sizeof(struct cdb_0):sizeof(cdb_1))

    struct	cdb_0 {		    /* COMMAND GROUP 0 */
/* 0*/	u_char	cdb_0_cmd;		/* command code */
/* 1*/	u_char	cdb_0_lun	: 3;	/* logical unit number */
	u_char	cdb_0_lba_h	: 5;	/* high part of address */
/* 2*/	u_char	cdb_0_lba_m;		/* middle part of address */
/* 3*/	u_char	cdb_0_lba_l;		/* low part of address */
#define		  CDB_0_LBA_MAX	0x1FFFFF
/* 4*/	u_char	cdb_0_len;		/* block count */
/* 5*/	u_char			: 6;	/* reserved */
	u_char	cdb_0_fr	: 1;	/* flag request */
	u_char	cdb_0_link	: 1;	/* link */
    }		cdb_0;
#define	SET_CDB_0(cdb, cmd, lun, lba, len)			(	\
		bzero((caddr_t)&cdb, sizeof (struct cdb_0)),		\
		(cdb).cdb_0.cdb_0_cmd = (cmd),				\
		(cdb).cdb_0.cdb_0_lun = (lun),				\
		SCSI_HML_SET((cdb).cdb_0.cdb_0_lba, lba),		\
		(cdb).cdb_0.cdb_0_len = (len))

    struct	cdb_0_tape {	    /* COMMAND GROUP 0 - TAPE */
/* 0*/	u_char	cdb_0_tape_cmd;		/* command code */
/* 1*/	u_char	cdb_0_tape_lun	: 3;	/* logical unit number */
	u_char	cdb_0_tape_code	: 5;	/* command specific code */
#define		  TAPE_CODE_CMD_SPACE_BLOCKS	0
#define		  TAPE_CODE_CMD_SPACE_FILES	1
#define		  TAPE_CODE_CMD_SPACE_SFILES	2
#define		  TAPE_CODE_CMD_SPACE_EOR	3
#define		  TAPE_CODE_FIXED		1
#define		  TAPE_CODE_IMM			1
/* 2*/	u_char	cdb_0_tape_len_h;	/* high part of block count */
/* 3*/	u_char	cdb_0_tape_len_m;	/* middle part of block count */
/* 4*/	u_char	cdb_0_tape_len_l;	/* low part of block count */
/* 5*/	u_char			: 6;	/* reserved */
	u_char	cdb_0_tape_fr	: 1;	/* flag request */
	u_char	cdb_0_tape_link	: 1;	/* link */
    }		cdb_0_tape;
#define	SET_CDB_0_TAPE(cdb, cmd, lun, code, len)		(	\
		bzero((caddr_t)&cdb, sizeof (struct cdb_0_tape)),	\
		(cdb).cdb_0_tape.cdb_0_tape_cmd = (cmd),		\
		(cdb).cdb_0_tape.cdb_0_tape_lun = (lun),		\
		(cdb).cdb_0_tape.cdb_0_tape_code = (code),		\
		SCSI_HML_SET((cdb).cdb_0_tape.cdb_0_tape_len, len))

    struct	cdb_1 {		    /* COMMAND GROUP 1 */
/* 0*/	u_char	cdb_1_cmd;		/* command code */
/* 1*/	u_char	cdb_1_lun	: 3;	/* logical unit number */
	u_char			: 4;	/* reserved */
	u_char	cdb_1_reladr	: 1;	/* relative address */
/* 2*/	u_char	cdb_1_lba_h;		/* logical block address */
/* 3*/	u_char	cdb_1_lba_mh;		/* logical block address */
/* 4*/	u_char	cdb_1_lba_ml;		/* logical block address */
/* 5*/	u_char	cdb_1_lba_l;		/* logical block address */
/* 6*/	u_char			: 8;	/* reserved */
/* 7*/	u_char	cdb_1_len_h;		/* length (high) */
/* 8*/	u_char	cdb_1_len_l;		/* length (low) */
/* 9*/	u_char			: 6;	/* reserved */
	u_char	cdb_1_fr	: 1;	/* flag request */
	u_char	cdb_1_link	: 1;	/* link */
    }		cdb_1;
#define	SET_CDB_1(cdb, cmd, lun, reladr, lba, len)		(	\
		bzero((caddr_t)&cdb, sizeof (struct cdb_1)),		\
		(cdb).cdb_1.cdb_1_cmd = (cmd),				\
		(cdb).cdb_1.cdb_1_lun = (lun),				\
		(cdb).cdb_1.cdb_1_reladr = (reladr),			\
		SCSI_HMML_SET((cdb).cdb_1.cdb_1_lba, lba),		\
		SCSI_HL_SET((cdb).cdb_1.cdb_1_len, len))
};

union	scsi_scb {		/* SCSI status completion byte/block */
    u_char	scb_status;	    /* Standard SCSI status */
#define		  SCB_STATUS_EXT	0x80	/* extended status format */
#define		  SCB_STATUS_QFULL	0x28	/* queue full */
#define		  SCB_STATUS_RCON	0x18	/* reservation conflict */
#define		  SCB_STATUS_INTER	0x10	/* intermediate/good */
#define		  SCB_STATUS_BUSY	0x08	/* device busy or reserved */
#define		  SCB_STATUS_CM		0x04	/* condition met */
#define		  SCB_STATUS_CHECK	0x02	/* sense data available */
#define		  SCB_STATUS_GOOD	0x00	/* good */
#define		  SCB_STATUS_MASK	0x3F	/* good */
#define		  SCB_STATUS_BITS	"\20\6QFULL\5INTER\4BUSY\3CM\2CHECK"
#define		  SCB_STATUS_NASCII	64
#define		  SCB_STATUS_ASCII 	{"ok","","check","","cm","","","", \
					"busy","","","","","","","",	\
					"int","","","","","","","",	\
					"rcon","","","","","","","",	\
					"","","","","","","","",	\
					"qfull","","","","","","","",	\
					"","","","","","","","",	\
					"","","","","","","",""}
    struct	scb_ext {	    /* Extended SCSI status */
/* 0*/	u_char	ext_status;		/* same as scb_status */
/* 1*/	u_char	ext_2		: 1;	/* extended status (next byte valid) */
	u_char	ext_resrv	: 6;	/* reserved */
	u_char	ext_ha_er	: 1;	/* host adapter detected error */
/* 2*/	u_char	ext_byte2;
    }		scb_ext;
};
extern char *scb_status_ascii[];

union	scsi_msg {		/* SCSI Messages. */
    u_char	msg_bytes[1];
    u_char	msg;		    /* Standard Messages: */
#define		  MSG_COMPLETE	0x00	/* I  command complete, check status */
#define		  MSG_EXTENDED	0x01	/* IO see below ... */
#define		  MSG_SAVE_P	0x02	/* I  save data pointers */
#define		  MSG_RESTORE_P	0x03	/* I  restore data pointers */
#define		  MSG_DISCON	0x04	/* I  disconnect */
#define		  MSG_I_ERR	0x05	/*  O initiator error */
#define		  MSG_ABORT	0x06	/*  O abort current operation */
#define		  MSG_REJECT	0x07	/* IO inappropriate message */
#define		  MSG_NO_OP	0x08	/*  O host has no valid message */
#define		  MSG_MSGPARITY	0x09	/*  O parity error on last message */
#define		  MSG_L_CMP	0x0A	/* I  linked command complete */
#define		  MSG_L_CMP_F	0x0B	/* I  linked command complete w flag */
#define		  MSG_DEV_RST	0x0C	/* IO soft reset */
#define		  MSG_IDENTIFY	0x80	/*  O identify no disc */
#define		  MSG_IDENTIFYD	0xC0	/*  O identify, allow disconnect */
    struct	msg_ext {	    /* Extended Message */
/* 0*/	u_char	ext_msg;		/* == MSG_EXTENDED */
/* 1*/	u_char	ext_len;		/* number of following bytes */
/* 2*/	u_char	ext_code;		/* code */
#define		  EXT_CODE_SDTR	0x01	/*   SYNCHRONOUS DATA XFER REQ */
    /* THERE ARE MORE EXTENDED MESSAGES.... */
/* 3*/	u_char	ext_xfer_period;	/* transfer period in 4ns units */
/* 4*/	u_char	ext_offset;		/* REQ/ACK offset */
    }		msg_ext;
};

union	scsi_sns {		/* data returned by request sense (SC_SENSE) */
    struct	sns {		    /* Non-Extended Sense data format */
/* 0*/	u_char	sns_valid	: 1;	/* logical block is valid */
	u_char	sns_class	: 3;	/* error class (0-6): 7, see below */
#define		  SNS_CLASS_EXT		7
	u_char	sns_code	: 4;	/* error code */
/* 1*/	u_char	sns_lba_h;		/* high logical block address */
/* 2*/	u_char	sns_lba_m;		/* middle logical block address */
/* 3*/	u_char	sns_lba_l;		/* low logical block address */
    }		sns;
    struct	sns_ext {	    /* Extended Sense data format */
/* 0*/	u_char	sns_ext_valid	: 1;	/* sense data is valid */
	u_char	sns_ext_class	: 3;	/* error class (== 7) */
	u_char	 		: 4;	/* not used */
/* 1*/	u_char	sns_ext_seg_num;	/* segment number */
/* 2*/	u_char	sns_ext_fil_mk	: 1;	/* file mark on device */
	u_char	sns_ext_eom	: 1;	/* end of media */
	u_char	sns_ext_ili	: 1;	/* incorrect length indicator */
	u_char		 	: 1;	/* reserved */
	u_char	sns_ext_key	: 4;	/* sense key */
#define		  SNS_EXT_KEY_NO_SENSE		0x0	/* DEVICE CODES ... */
#define		  SNS_EXT_KEY_RECOVERED		0x1
#define		  SNS_EXT_KEY_NOT_READY		0x2
#define		  SNS_EXT_KEY_MEDIUM_ERR	0x3
#define		  SNS_EXT_KEY_HW_ERROR		0x4
#define		  SNS_EXT_KEY_ILL_REQUEST	0x5
#define		  SNS_EXT_KEY_UNIT_ATTN		0x6
#define		  SNS_EXT_KEY_DATA_PROT		0x7
#define		  SNS_EXT_KEY_BLANK_CHECK	0x8
#define		  SNS_EXT_KEY_VU		0x9
#define		  SNS_EXT_KEY_COPY_ABORT	0xA
#define		  SNS_EXT_KEY_ABORT_CMD		0xB
#define		  SNS_EXT_KEY_EQUAL		0xC
#define		  SNS_EXT_KEY_VOL_OF		0xD
#define		  SNS_EXT_KEY_MISCOMPARE	0xE
#define		  SNS_EXT_KEY_RESERVED		0xF
							/* DRIVER CODES... */
#define		  SNS_EXT_KEY_DRVR_FATAL	0x10	/* handshake failure */
#define		  SNS_EXT_KEY_DRVR_TIMEOUT	0x11	/* command timeout */
#define		  SNS_EXT_KEY_DRVR_EOF		0x12	/* eof hit */
#define		  SNS_EXT_KEY_DRVR_EOT		0x13	/* eot hit */
#define		  SNS_EXT_KEY_DRVR_LENGTH	0x14	/* length error */
#define		  SNS_EXT_KEY_DRVR_BOT		0x15	/* bot hit */
#define		  SNS_EXT_KEY_DRVR_MEDIA	0x16	/* wrong media */
#define		  SNS_EXT_KEY_DRVR_RESIDUE	0x17	/* dma residue error */
#define		  SNS_EXT_KEY_DRVR_BUSY		0x18	/* device busy error */
#define		  SNS_EXT_KEY_DRVR_RESERVATION	0x19	/* reservation error */
#define		  SNS_EXT_KEY_DRVR_INTERRUPTED	0x1a	/* user interrupted */
#define		  SNS_EXT_KEY_NASCII		27
#define		  SNS_EXT_KEY_ASCII					\
		    { "no sense", "soft error", "not ready", "media error", \
		    "hardware error", "illegal request", "unit attention", \
		    "write protected", "blank check", "vendor unique", \
		    "copy aborted", "aborted command", "equal error", \
		    "volume overflow", "miscompare error", "reserved", \
		    "fatal", "timeout", "EOF", "EOT", "length error", \
		    "BOT", "wrong tape media", "dma residue", "busy", \
		    "reservation", "user interrupted", 0 }
#define		  SENSE_KEY_INFO	SNS_EXT_KEY_ASCII
/* 3*/	u_char	sns_ext_info_h;		/* information */
/* 4*/	u_char	sns_ext_info_mh;	/* information */
/* 5*/	u_char	sns_ext_info_ml;	/* information */
/* 6*/	u_char	sns_ext_info_l;		/* information */
/* 7*/	u_char	sns_ext_add_len;	/* number of additional bytes */
/* 8*/	u_char	sns_ext_vu_8;		/* vendor unique sense codes */
/* 9*/	u_char	sns_ext_vu_9;		/* vendor unique sense codes */
/*10*/	u_char	sns_ext_vu_10;		/* vendor unique sense codes */
/*11*/	u_char	sns_ext_vu_11;		/* vendor unique sense codes */
/*12*/	u_char	sns_ext_code;		/* extended sense error codes */
/*13*/	u_char	sns_ext_vu_13;		/* vendor unique sense codes */
/*14*/	u_char	sns_ext_vu_14;		/* vendor unique sense codes */
/*15*/	u_char	sns_ext_vu_15;		/* vendor unique sense codes */
/*16*/	u_char	sns_ext_vu_16;		/* vendor unique sense codes */
/*17*/	u_char	sns_ext_vu_17;		/* vendor unique sense codes */
/*18*/	u_char	sns_ext_vu_18;		/* vendor unique sense codes */
/*19*/	u_char	sns_ext_vu_19;		/* vendor unique sense codes */
/*20*/	u_char	sns_ext_vu_20;		/* vendor unique sense codes */
/*21*/	u_char	sns_ext_vu_21;		/* vendor unique sense codes */
/*22*/	u_char	sns_ext_vu_22;		/* vendor unique sense codes */
/*23*/	u_char	sns_ext_vu_23;		/* vendor unique sense codes */
/*24*/	u_char	sns_ext_vu_24;		/* vendor unique sense codes */
/*25*/	u_char	sns_ext_vu_25;		/* vendor unique sense codes */
/*26*/	u_char	sns_ext_vu_26;		/* vendor unique sense codes */
/*27*/	u_char	sns_ext_vu_27;		/* vendor unique sense codes */
/*28*/
    }		sns_ext;
};
extern char *sns_ext_key_ascii[];

struct	scsi_inq {		/* data returned by SC_INQUIRY */
/* 0*/	u_char	inq_pq		: 3;	/* Peripherial Qualifier */
#define		  INQ_PQ_CON	0x00	/*   Lun Device connected */
#define		  INQ_PQ_NCON	0x01	/*   Lun Device not connected */
#define		  INQ_PQ_NLUN	0x03	/*   No Device Supported on lun */
	u_char	inq_pdtype	: 5;	/* Peripheral Device Type */
#define		  INQ_PDT_DISK	0x00	/*   Direct-access device */
#define		  INQ_PDT_TAPE	0x01	/*   Sequential-access device */
#define		  INQ_PDT_PRINT	0x02	/*   Printer device */
#define		  INQ_PDT_PROC	0x03	/*   Processor device */
#define		  INQ_PDT_WORM	0x04	/*   Write-once read-multiple device */
#define		  INQ_PDT_RO	0x05	/*   Read only device */
#define		  INQ_PDT_SCAN	0x06	/*   Scanner device */
#define		  INQ_PDT_OMEM	0x07	/*   Optical memory device */
#define		  INQ_PDT_JBOX	0x08	/*   Media changer- Jukebox */
#define		  INQ_PDT_COMM	0x09	/*   Communications Device */
#define		  INQ_PDT_NOLUN	0x1f	/*   Logical unit not present */
#define		  INQ_PDT_NPDTYPE	10
#define		  INQ_PDT_NASCII	10
#define		  INQ_PDT_ASCII	{"disk", "tape", "printer", "processor", \
				"work", "ro", "scanner", "optmem", \
				"jukebox", "comdevice", 0 }
/* 1*/	u_char	inq_removable	: 1;	/* removable */
	u_char	inq_dtypeq	: 7;	/* device type qualifier */
/* 2*/	u_char	inq_isov	: 2;	/* ISO version */
	u_char	inq_emcav	: 3;	/* EMCA version */
	u_char	inq_ansiiv	: 3;	/* ANSII version */
#define		  INQ_ANSIIV_SCSI_1	1
#define		  INQ_ANSIIV_SCSI_2	2
/* 3*/	u_char	inq_aenc	: 1;	/* asynchronous event notification */
	u_char	inq_trmiop	: 1;	/* supports terminate io message */
	u_char	: 2;
	u_char	inq_rdf		: 4;	/* response data format */
#define		  INQ_RDF_CCS	0x01	/*   Common Command Set */
/* 4*/	u_char	inq_addlen;		/* additional length */
/* 5*/	u_char	inq_rsl;		/* max sense length (non standard) */
/* 6*/	u_char	inq_vu[1];		/* pad vender unique data */
/* 7*/	u_char	inq_reladr	: 1;	/* supports relative addresses */
	u_char	inq_wbus32	: 1;	/* supports 32-bit wide transfers */
	u_char	inq_wbus16	: 1;	/* supports 16-bit wide transfers */
	u_char	inq_sync	: 1;	/* supports synchronous transfers */
	u_char	inq_linked	: 1;	/* supports linked commands */
	u_char	: 1;
	u_char	inq_cmdque	: 1;	/* supports command queueing */
	u_char	inq_softrst	: 1;	/* supports soft reset */
/* 8*/	u_char	inq_vendor[8];		/* vendor name ASCII */
/*16*/	u_char	inq_product[16];	/* vendor product name ASCII */
/*32*/	u_char	inq_rev[4];		/* vendor product revision ASCII */
/*36*/	u_char	inq_vu_[148-36];
};
extern char *inq_pdt_ascii[];

struct	blk_desc {		/* block descriptor: SC_MODE_{SELECT,SENSE} */
/* 0*/	u_char	bd_density;		/* block descriptor density */
/* 1*/	u_char	bd_nb_h;		/* high number of blocks */
/* 2*/	u_char	bd_nb_m;		/* mid number of blocks */
/* 3*/	u_char	bd_nb_l;		/* low number of blocks */
/* 4*/	u_char	: 8;			/* reserved */
/* 5*/	u_char	bd_bl_h;		/* high block length */
/* 6*/	u_char	bd_bl_m;		/* mid block length */
/* 7*/	u_char	bd_bl_l;		/* low block length */
};

struct	pag_desc {		/* page descriptor: SC_MODE_{SELECT,SENSE} */
    u_char	pd_save		: 1;	/* parameter savable */
    u_char			: 1;	/* reserved */
    u_char	pd_code		: 6;	/* page code */
#define		  PD_ERROR	0x01	/*	Error Recovery Parameters */
#define		  PD_DISRE	0x02	/*	Disconnect Reconnect Params */
#define		  PD_FORMAT	0x03	/*	Format Parameters Parameters */
#define		  PD_GEOMETRY	0x04	/*	Drive Geometry Parameters */
#define		  PD_CACHE	0x38	/*	Cache Parameters */
#define		  PD_ALL	0x3F	/*	All Pages */
    u_char	pd_len;			/* page length */
    union	pd_pg {
	struct pg_err {			/*   ERROR PAGE */
	    u_char err_awre	: 1;		/* auto write reallocation */
	    u_char err_arre	: 1;		/* auto read reallocation */
	    u_char err_tb	: 1;		/* transfer block on error */
	    u_char err_rc	: 1;		/* read continuous */
	    u_char err_ecc	: 1;		/* enable early correction */
	    u_char err_per	: 1;		/* post errors (report soft)*/  
	    u_char err_dte	: 1;		/* disable transfer on error */
	    u_char err_dcr	: 1;		/* disable correction */
	    u_char err_retries;			/* retry count */
	    u_char err_cspan;			/* correction span */
	    u_char err_hoffset;			/* head offset */
	    u_char err_dsoffset;		/* data strobe offset */
	    u_char err_tlimit;			/* recovery time limit */
	}	pg_err;
	struct pg_dis {			/*   DISCONNECT RECONNECT PAGE */
	    u_char	dis_bfr;		/* buffer full ratio */
	    u_char	dis_ber;		/* buffer empty ratio */
	    u_short	dis_bil;		/* bus inactivity limit */
	    u_short	dis_distime;		/* disconnect time limit */
	    u_short	dis_retime;		/* reconnect time limit */
	    u_short	dis_xxx;		/* reserved */
	}	pg_dis;
	struct pg_fmt {			/*   FORMAT PAGE */
	    u_short	fmt_tpz;		/* tracks/zone */
	    u_short	fmt_alt_spz;		/* alternate sectors/zone */
	    u_short	fmt_alt_tpz;		/* alternate tracks/zone */
	    u_short	fmt_alt_tpv;		/* alternate tracks/volume */
	    u_short	fmt_spt;		/* sectors/track */
	    u_char	fmt_dbps;		/* data bytes/sector */
	    u_char	fmt_interleave;		/* interleave factor */
	    u_char	fmt_t_skew;		/* track skew factor */
	    u_char	fmt_c_skew;		/* cylinder skew factor */
	    u_char	fmt_ssec	: 1;	/* soft sector formatting */
	    u_char	fmt_hsec	: 1;	/* hard sector formatting */
	    u_char	fmt_rmb		: 1;	/* removable */
	    u_char	fmt_surf	: 1;	/* surface lba allocation */
	    u_char	fmt_ins		: 1;	/* inhibit save */
	    u_char			: 3;
	    u_char	fmt_rsvd[3];
	}	pg_fmt;
	struct	pd_geo {		/*   GEOMETRY PAGE */
	    u_char	geo_cyl_h;		/* number of cylinders */
	    u_char	geo_cyl_m;
	    u_char	geo_cyl_l;
	    u_char	geo_heads;		/* number of heads */
	    u_char	geo_cyl_wp_h;		/* start write precomp cyl */
	    u_char	geo_cyl_wp_m;
	    u_char	geo_cyl_wp_l;
	    u_char	geo_cyl_rw_h;		/* start reduced write cyl */
	    u_char	geo_cyl_rw_m;
	    u_char	geo_cyl_rw_l;
	    u_short	geo_step_rate;		/* step rate */
	    u_char	geo_cyl_ld_h;		/* landing zone cylinder */
	    u_char	geo_cyl_ld_m;
	    u_char	geo_cyl_ld_l;
	    u_char	geo_rsvd[3];
	}	pg_geo;
	struct	pd_cac {		/*   CACHE PAGE */
	    u_char	cac_mode;		/* Cache control and size */
	    u_char	cac_threshold;		/* Prefetch threshold */
	    u_char	cac_max_prefetch;	/* Max. prefetch */
	    u_char	cac_max_multiplier;	/* Max. prefetch multiplier */
	    u_char	cac_min_prefetch;	/* Min. prefetch */
	    u_char	cac_min_multiplier;	/* Min. prefetch multiplier */
	    u_char	cac_rsvd2[8];
	}	pg_cac;
    }	pd_pg;
};

struct	scsi_msen {		/* data returned by SC_MODE_SENSE */
	u_char	msen_len;		/* sense data length */
	u_char	msen_mtype;		/* medium type */
	u_char	msen_wprot	: 1;	/* write protected if 1 */
	u_char	msen_bufm	: 3;	/* buffer mode */
#define		  MSEN_BUFM_UNBUF	0
#define		  MSEN_BUFM_BUF		1
	u_char	msen_speed	: 4;	/* speed */
	u_char	msen_bdl;		/* block descriptor length */
	struct	blk_desc msen_bd;	/* block descriptor */
	struct	pag_desc msen_pd;	/* page descriptor */
};

struct	scsi_msel {		/* data sent by SC_MODE_SELECT */
	u_char	: 8;			/* reserved */
	u_char	msel_mtype;		/* medium type */
	u_char	msel_wprot	: 1;	/* write protected if 1 */
	u_char	msel_bufm	: 3;	/* buffer mode  */
#define		  MSEL_BUFM_UNBUF	0
#define		  MSEL_BUFM_BUF		1
	u_char	msel_speed	: 4;	/* speed */
	u_char	msel_bdl;		/* block descriptor length */
	struct	blk_desc msel_bd;	/* block descriptor */
	struct	pag_desc msel_pd;	/* page descriptor */
};

struct	scsi_rcap {		/* data returned by SC_RCAPAC */
	u_int	rcap_lba;		/* logical block address */
	u_int	rcap_bl;		/* block length */
};

struct	scsi_blklim {		/* data returned by SC_BLKLIM */
	u_int	blklim_max;		/* cheat on first byte */
	u_short	blklim_min;
};

union	defect {		/* defect list formats supported by scsi */
	int	defect_blk;		/* logical block format */
	struct defect_bfi {		/* byte from index format */
		char	bfi_cyl_h;
		char	bfi_cyl_m;
		char	bfi_cyl_l;
		char	bfi_head;
		int	bfi_bfi;
	}	defect_bfi;
	struct defect_ps {		/* physical sector format */
		char	ps_cyl_h;
		char	ps_cyl_m;
		char	ps_cyl_l;
		char	ps_head;
		int	ps_ps;
	}	defect_ps;
};

struct	scsi_format {		/* data sent by SC_FORMAT */
	u_char	: 8;			/* reserved */
	u_char	format_fov	: 1;	/* format options valid */
	u_char	format_dpry	: 1;	/* disable primary defect list */
	u_char	format_dcrt	: 1;	/* disable certivication */
	u_char	format_stpf	: 1;	/* stop format on error */
	u_char			: 4;	/* reserved */
	u_short	format_dll;		/* defect list length in bytes */
	/* union defect format_defects[] */
};

struct	scsi_rdefect {		/* data sent from SC_READDEFECT */
	u_char	: 8;			/* reserved */
	u_char	: 3;			/* reserved */
	u_char	rdefect_mdl	: 1;	/* mfg defect list */
	u_char	rdefect_gdl	: 1;	/* grown defect list */
	u_char	rdefect_fmt	: 3;	/* defect list format */
	u_short	rdefect_dll;		/* defect list length in bytes */
	/* union defect rdefect_defects[] */
};

struct	scsi_reassign {		/* data sent by SC_REASSIGN */
	u_char	: 8;			/* reserved */
	u_char	: 8;			/* reserved */
	u_short	reassign_len;		/* number of defects*4 that follow */
	u_long	reassign_lba;		/* logical block to reassign */
};

/* pick up (set) 2 byte "_h _l" field in (from) an int */
#define	SCSI_HL(x)		((x/**/_h<<8)|(x/**/_l))
#define	SCSI_HL_SET(x, v)	(x/**/_h=(v)>>8, x/**/_l=(v))

/* pick up (set) 3 byte "_h _m _l" field in (from) an int */
#define	SCSI_HML(x)		((x/**/_h<<16)|(x/**/_m<<8)|(x/**/_l))
#define	SCSI_HML_SET(x, v)	(x/**/_h=(v)>>16, x/**/_m=(v)>>8, x/**/_l=(v))

/* pick up (set) 4 byte "_h _mh _ml _l" field in (from) an int */
#define	SCSI_HMML(x)		\
	    ((x/**/_h<<24)|(x/**/_mh<<16)|(x/**/_ml<<8)|(x/**/_l))
#define	SCSI_HMML_SET(x, v)	\
	    (x/**/_h=(v)>>24, x/**/_mh=(v)>>16, x/**/_ml=(v)>>8, x/**/_l=(v))
#endif	_SCSI_H
