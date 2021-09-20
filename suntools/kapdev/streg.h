/* @(#) streg.h 1.1@(#) Solbourne id 9/22/93 00:08:34 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/* @(#)streg.h       1.2 88/05/28 Copyr 1987 Sun Micro */

/*
 * Defines for SCSI tape drives.
 */
#define ST_SYSGEN   			/* Enable Sysgen controller support */
#define ST_AUTOPOSITION  		/* Enable seek support */
#define ST_TIMEOUT			/* Enable command timeouts */

#define MAX_ST_DEV_SIZE		65535	/* 64KB limit for variable length I/O */
#define MAX_AUTOLOAD_DELAY	60	/* 120 Sec. Auto-load maximum delay */
#define ST_AUTODEN_LIMIT	1	/* Auto density file limit */

#ifdef  lint
#define ST_SYSGEN   			/* Enable Sysgen controller support */
#define ST_AUTOPOSITION  		/* Enable seek support */
#define ST_TIMEOUT			/* Enable command timeouts */
/*#define sun2				/* Enable sun2 support */
/*#define CPU_SUN2_120		2	/*   "     "     "     */
#endif  lint

/*
 * Driver state machine codes -- Do not change order!
 * Opening states:
 *	closed -> opening         ||   -> open  (no tape change, no error)
 *		  opening_sysgen
 *
 *	closed -> opening         ||   -> open  (tape change, no error)
 *                opening_delay   ||
 *
 *	closed -> opening         ||   -> opening_sysgen  -> open  (sysgen)
 *                opening_delay   ||
 *
 *	closed -> opening         ||   -> open_failed_loading ||  -> closed
 *                opening_delay	          open_failed_tape    ||     (error)
 *			     	          open_failed
 *
 * Closing states:
 *	open   -> closing -> closed
 *
 * Open states:
 *	open   -> open (passed command)
 *
 *	open   -> sensing -> open (failed command)
 *
 *	open   -> sensing -> append_testing -> open  (failed write append)
 *
 *	open   -> sensing -> density_change -> open  (failed write append)
 *
 *	open   -> sensing -> append_testing -> retrying_cmd -> open
 *					       (passed write append)
 *
 *	open   -> sensing -> density_change -> retrying_cmd -> open
 *					       (passed write append)
 */
#define CLOSED			 0
#define CLOSING			 1
#define OPEN_FAILED_LOADING	 2
#define OPEN_FAILED_TAPE	 3
#define OPEN_FAILED		 4
#define OPENING_SYSGEN		 5
#define OPENING_DELAY		 6
#define OPENING			 7
#define APPEND_TESTING		 8
#define DENSITY_CHANGING	 9
#define RETRYING_CMD		10
#define SENSING			11
#define OPEN			12

/*
 * Eof codes.
 */
#define ST_NO_EOF		0x00
#define ST_EOF			0x01
#define ST_EOF_PENDING		0x02
#define ST_EOT			ST_EOF

/*
 * Operation codes.
 */
#define SC_REWIND		0x01
#define SC_QIC02		0x0D
#define SC_READ_XSTATUS_CIPHER	0xe0		/* Sun-2, Cipher tape only */
#define SC_SPACE_REC		0x11
#define SC_ERASE_TAPE		0x19
#define SC_LOAD			0x1B
#define SC_UNLOAD		0x80		/* phony - for int use only */
#define SC_BSPACE_FILE		0x81		/* phony - for int use only */
#define SC_SPACE_FILE		0x82		/* phony - for int use only */
#define SC_RETENSION		0x83		/* phony - for int use only */
#define SC_DEN1600		0x84		/* phony - for int use only */
#define SC_DEN6250		0x85		/* phony - for int use only */
#define SC_READ_APPEND		0x86		/* phony - for int use only */

/*
 * Supported tape device types plus default type for opening.
 * Types 10 - 13, are special (ancient too) drives.
 * Types 14 - 1f, are 1/4-inch cartridge drives.
 * Types 20 - 28, are 1/2-inch cartridge or reel drives.
 * Types 28+, are rdat (vcr) drives.
 */
#define ST_TYPE_INVALID		0x00
#define ST_TYPE_SYSGEN1		0x10	/* Sysgen with QIC-11 only */
#define ST_TYPE_SYSGEN		0x11	/* Sysgen with QIC-24 and QIC-11 */
#define ST_TYPE_DEFAULT		0x12	/* Who knows ? */
#define ST_TYPE_ADAPTEC		0x13	/* Adaptec */

#define ST_TYPE_EMULEX		0x14	/* Emulex MT-02 */
#define ST_TYPE_ARCHIVE		0x15	/* Archive QIC-150 */
#define ST_TYPE_WANGTEK		0x16	/* Wangtek QIC-150 */
#define ST_TYPE_ADSI		0x17	/* ADSI */

#define ST_TYPE_CDC		0x20	/* CDC */
#define ST_TYPE_FUJI		0x21	/* Fujitsu */
#define ST_TYPE_KENNEDY		0x22	/* Kennedy */
#define ST_TYPE_HP		0x23	/* HP */

#define ST_TYPE_EXABYTE		0x28	/* Exabyte */


/* Defines for supported drive options */
#define ST_VARIABLE		0x001	/* supports variable length I/O */
#define ST_QIC			0x002	/* QIC tape drive */
#define ST_REEL			0x004	/* 1/2-inch reel tape drive */
#define ST_BSF			0x008	/* Supports backspace file */
#define ST_BSR			0x010	/* Supports backspace record */
#define ST_LONG_ERASE		0x020	/* Long Erase tape timeout required */
#define ST_NODISCON		0x040	/* No disconnect/reconnect support */
#define ST_NO_QIC24		0x080	/* No QIC-24 (for Sysgen) */
#define ST_AUTODEN_OVERRIDE	0x100	/* Auto-Density override flag */


struct st_drive_table {
	char	name[8];		/* Name, for debug */
	char	length;			/* Length of vendor id */
	char	vid[8];			/* Vendor id */
	char	type;			/* Drive type for driver */
	short	bsize;			/* Block size */
	u_char	lo_density;		/* Low  density code */
	u_char	hi_density;		/* High density code */
	u_char	lo_speed;		/* Low speed code */
	u_char	hi_speed;		/* High speed code */
	int	options;		/* Drive options */
};
struct st_drive_table st_drivetab1[] = {
/* Emulex MT-02 controller for 1/4" cartridge */
	"Emulex",
	2, "\000\000", ST_TYPE_EMULEX,
	512, 0x84, 0x00, 0, 0, ST_QIC,
/* Wangtek QIC-150 1/4" cartridge */
	"Wangtek",
	7, "WANGTEK", ST_TYPE_WANGTEK,
	512, 0x00, 0x00, 0, 0, ST_QIC,
/* Archive QIC-150 1/4" cartridge */
	"Archive",
	7, "ARCHIVE", ST_TYPE_ARCHIVE,
	512, 0x00, 0x00, 0, 0, ST_QIC,
/* ADSI T-100 controller for 1/4" cartridge */
	"Adsi",
	4, "ADSI", ST_TYPE_ADSI,
	512, 0x00, 0x00, 0, 0, ST_QIC,

/* CDC 1/2" cartridge */
	"CDC",
	3, "LMS", ST_TYPE_CDC,
	1024, 0x00, 0x00, 0, 0,
	(ST_QIC | ST_VARIABLE | ST_BSF | ST_LONG_ERASE),
/* Fujitsu 1/2" cartridge */
	"Fujitsu",
	2, "\076\000", ST_TYPE_FUJI,
	1024, 0x00, 0x00, 0, 0,
	(ST_QIC | ST_VARIABLE | ST_BSF | ST_BSR | ST_LONG_ERASE),
/* Exabyte 8mm cartridge */
	"Exabyte",
	7, "EXABYTE", ST_TYPE_EXABYTE,
	1024, 0x00, 0x00, 0, 0, (ST_QIC | ST_VARIABLE | ST_LONG_ERASE),

/* Kennedy 1/2" reel */
	"Kennedy",
	4, "KENNEDY", ST_TYPE_KENNEDY,
	10240, 0x02, 0x03, 0, 0, (ST_REEL | ST_VARIABLE | ST_BSF | ST_BSR),
/* HP 1/2" reel */
	"HP",
	2, "HP", ST_TYPE_HP,
	10240, 0x02, 0x03, 0, 0, (ST_REEL | ST_VARIABLE | ST_BSF | ST_BSR),
};
#define MAX_TAPE_DEVICES \
	(sizeof(st_drivetab1)/sizeof(st_drivetab1[0]))

/*
 * Exceptions to the above drive table.  These drives/controllers
 * require special processing.  Note, do not change to order of
 * this table!
 */
#define IS_DEFAULT(dsi)		(dsi->un_ctype == ST_TYPE_DEFAULT)
#define IS_SYSGEN(dsi)		(dsi->un_ctype == ST_TYPE_SYSGEN)
#define IS_EXABYTE(dsi)		(dsi->un_ctype == ST_TYPE_EXABYTE)

struct st_drive_table st_drivetab2[] = {
/* Adaptec ACB-3530A controller for 1/4" cartridge */
	"Adaptec",
	5, "ADAPTEC", ST_TYPE_ADAPTEC,
	512, 0x04, 0x00, 0, 0, ST_QIC,
/* Default values for unknown tape drive/controller */
	"Unknown",
	0, " ", ST_TYPE_DEFAULT,
	512, 0x00, 0x00, 0, 0, (ST_QIC | ST_LONG_ERASE),

/* Sysgen controller for 1/4" cartridge (QIC-24 and QIC-11) */
	"Sysgen",
	0, "\000", ST_TYPE_SYSGEN,
	512, 0x26, 0x27, 0, 0, (ST_QIC | ST_NODISCON),
/* Sysgen controller for 1/4" cartridge (QIC-11 only) */
	"Sysgen11",
	0, "\000", ST_TYPE_SYSGEN,
	512, 0x00, 0x00, 0, 0, (ST_QIC | ST_NODISCON | ST_NO_QIC24),
};

/*
 * defines for SCSI tape CDB.
 */
#undef	t_code
#undef	high_count
#undef	mid_count
#undef	low_count
struct	scsi_cdb6 {		/* scsi command description block */
	u_char	cmd;		/* command code */
	u_char	lun	: 3;	/* logical unit number */
	u_char	t_code	: 5;	/* high part of address */
	u_char	high_count;	/* middle part of address */
	u_char	mid_count;	/* low part of address */
	u_char	low_count;	/* block count */
	u_char	vu_57	: 1;	/* vendor unique (byte 5 bit 7) */
	u_char	vu_56	: 1;	/* vendor unique (byte 5 bit 6) */
	u_char		: 4;	/* reserved */
	u_char	fr	: 1;	/* flag request (interrupt at completion) */
	u_char	link	: 1;	/* link (another command follows) */
};


/*
 * Parameter list for the MODE_SELECT and MODE_SENSE commands.
 * The parameter list contains a header, followed by zero or more
 * block descriptors, followed by vendor unique parameters, if any.
 * Note, only one 8-byte block descriptor is used for 1/2-inch SCSI
 * tape devices (e.g. CDC HI/TC, HP SCSI-2, and Kennedy).
 */
#define MS_BD_LEN	8
struct st_ms_mspl {
	u_char	reserved1;	/* reserved, sense data length */
	u_char	reserved2;	/* reserved, medium type */
	u_char	wp	:1;	/* write protected */
	u_char	bufm	:3;	/* buffered mode */
	u_char	speed	:4;	/* speed */
	u_char	bd_len;		/* block length in bytes */
	u_char	density;	/* density code */
	u_char	high_nb;	/* number of logical blocks on the medium */
	u_char	mid_nb;		/* that are to be formatted with the density */
	u_char	low_nb;		/* code and block length in block descriptor */
	u_char	reserved;	/* reserved */
	u_char	high_bl;	/* block length */
	u_char	mid_bl;		/*   "      "   */
	u_char	low_bl;		/*   "      "   */
};
struct st_ms_exabyte {
	u_char	reserved1;	/* reserved, sense data length */
	u_char	reserved2;	/* reserved, medium type */
	u_char	wp	:1;	/* write protected */
	u_char	bufm	:3;	/* buffered mode */
	u_char	speed	:4;	/* speed */
	u_char	bd_len;		/* block length in bytes */
	u_char	density;	/* density code */
	u_char	high_nb;	/* number of logical blocks on the medium */
	u_char	mid_nb;		/* that are to be formatted with the density */
	u_char	low_nb;		/* code and block length in block descriptor */
	u_char	reserved;	/* reserved */
	u_char	high_bl;	/* block length */
	u_char	mid_bl;		/*   "      "   */
	u_char	low_bl;		/*   "      "   */
	u_char	optional1;	/* optional vendor unique byte */
};


/*
 * SCSI tape REQUEST SENSE parameter block.  Note,
 * this structure should have an even number of bytes to
 * eliminate any byte packing problems with our host adapters.
 */
struct	st_sense {		/* scsi tape extended sense for error class 7 */
	/* byte 0 */
	u_char	adr_val	: 1;	/* sense data is valid */
	u_char		: 7;	/* fixed at binary 1110000 */
	/* byte 1 */
	u_char	seg_num;	/* segment number, applies to copy cmd only */
	/* byte 2 */
	u_char	fil_mk	: 1;	/* file mark on device */
	u_char	eom	: 1;	/* end of media */
	u_char	ili	: 1;	/* incorrect length indicator */
	u_char		: 1;	/* reserved */
	u_char	key	: 4;	/* sense key, see below */
	/* bytes 3 through 6 */
	u_char	info_0;		/* sense information byte 1 */
	u_char	info_1;		/* sense information byte 2 */
	u_char	info_2;		/* sense information byte 3 */
	u_char	info_3;		/* sense information byte 4 */
	/* bytes 7 through 13 */
	u_char	add_len;	/* number of additional bytes */
	u_char	optional_8;	/* search/copy src sense only */
	u_char	optional_9;	/* search/copy dst sense only */
	u_char	optional_10;	/* search/copy only */
	u_char	optional_11;	/* search/copy only */
	u_char	error;		/* error code */
	u_char	error1;		/* error code qualifier */
	/* bytes 14 through 15 */
	u_char	optional_14;	/* reserved */
	u_char	optional_15;	/* reserved */
};

#ifdef	ST_SYSGEN
/*
 * Sense info returned by sysgen controllers.  Note,
 * this structure should always be 16 bytes or the controller
 * will not clear it's error condition.  Also, you must
 * always follow an error condition with a request sense cmd.
 */
struct  sysgen_sense {
	/* Bytes 0 - 3  */
	u_char  disk_sense[4];		/* sense data from disk */
	/* byte 4 */
	u_char  valid4		:1;	/* some other bit set in this byte */
	u_char  no_cart		:1;	/* no cartrige, or removed */
	u_char  not_ready	:1;	/* drive not present */
	u_char  write_prot	:1;	/* write protected */
	u_char  eot		:1;	/* end of last track */
	u_char  data_err	:1;	/* unrecoverable data error */
	u_char  no_err		:1;	/* data transmitted not in error */
	u_char file_mark	:1;	/* file mark detected */
	/* byte 5 */
	u_char  valid5		:1;	/* some other bit set in this byte */
	u_char  illegal		:1;	/* illegal command */
	u_char  no_data		:1;	/* unable to find data */
	u_char  retries		:1;	/* 8 or more retries needed */
	u_char  bot		:1;	/* beginning of tape */
	u_char			:2;	/* reserved */
	u_char  reset		:1;	/* power-on or reset since last op */
	/* bytes 6 through 9 */
	short   retry_ct;		/* retry count */
	short   underruns;		/* number of underruns */
	/* bytes 10 through 15 */
	u_char   disk_xfer[3];		/* no. blks in last disk operation */
	u_char   tape_xfer[3];		/* no. blks in last tape operation */
};
#endif	ST_SYSGEN

/*
 * Macros for getting information from the sense data returned
 * by the various SCSI 1/2-inch tape controllers.  Note, this
 * use byte 2 of the extended sense descriptor block to mimimize
 * SCSI controller dependencies.
 */
#define ST_FILE_MARK(dsi, sense) \
	(dsi->un_ctype != 0  && \
	 (((struct st_sense *)sense)->fil_mk) ? 1 : 0)

#define ST_END_OF_TAPE(dsi, sense) \
	(dsi->un_ctype != 0  && \
	 (((struct st_sense *)sense)->eom) ? 1 : 0)

#define ST_LENGTH(dsi, sense) \
	(dsi->un_ctype != 0  && \
	 (((struct st_sense *)sense)->ili) ? 1 : 0)

#define ST_WRITE_PROT(dsi, sense) \
	(dsi->un_ctype != 0  && \
	 (((struct st_sense *)sense)->key == SC_WRITE_PROTECT))

#define ST_ILLEGAL(dsi, sense) \
	(dsi->un_ctype != 0  && \
	 (((struct st_sense *)sense)->key == SC_ILLEGAL_REQUEST))

#define ST_NO_CART(dsi, sense) \
	(dsi->un_ctype != 0  && \
	 (((struct st_sense *)sense)->key == SC_NOT_READY))

#define ST_RESET(dsi, sense) \
	(dsi->un_ctype != 0  && \
	 (((struct st_sense *)sense)->key == SC_UNIT_ATTENTION))

#define ST_CORRECTABLE(dsi, sense) \
	(dsi->un_ctype != 0  && \
	 (((struct st_sense *)sense)->key == SC_RECOVERABLE_ERROR))

