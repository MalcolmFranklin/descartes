/* @(#) stvar.h 1.1@(#) Solbourne id 9/22/93 00:08:37 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*
 * Defines for SCSI tape drives.
 */

#define MAX_ST_DEV_SIZE		65534   /* 64KB-2 for variable length I/O */

struct scsi_tape {
	struct st_tp	*st_tp;		/* tape device info */
	u_int	st_flags;		/* tape flags */
#define		  ST_FLAGS_INUSE	0x0001	/* tape is opened ... */
#define		  ST_FLAGS_WPROT	0x0002	/* write protected ... */
#define		  ST_FLAGS_HAD_RESET	0x0004	/* reset occured */
#define		  ST_FLAGS_VAR		0x0008	/* variable length records */
#define		  ST_FLAGS_LASTIOW	0x0010	/* last io was write */
#define		  ST_FLAGS_AT_EOM	0x0020	/* just got eom */
#define		  ST_FLAGS_PAST_EOM	0x0040	/* went past eom */
#define		  ST_FLAGS_TAPE_CHANGE	0x0080	/* tape changed */
#define		  ST_FLAGS_RWCLOSE	0x0100	/* tape rewinding on close */
#define		  ST_FLAGS_PEOF		0x0200	/* pending/past eof */
#define		  ST_FLAGS_BITS		\
"\20\12PEOF\11RWC\10TCH\7PEOM\6AEOM\5LW\4VAR\3RST\2WP\1U"
	u_char	st_state;		/* tape open state */
#define		  ST_STATE_BEGIN	0
#define		  ST_STATE_POSITION	1
#define		  ST_STATE_SENSE	2
#define		  ST_STATE_RETRY	3
#define		  ST_STATE_APPENDCHECK	4
#define		  ST_STATE_AUTODEN_REW	5
#define		  ST_STATE_AUTODEN_MSEL	6
#define		  ST_STATE_END		7
#define		  ST_STATE_ASCII	{ "BEGIN", "POSITION", "SENSE",	\
			"RETRY", "APCHECK", "ADEN_REW", "ADEN_MSEL", "END", }
	u_char	st_density;		/* current tape density/format */
	u_char	st_open_density;	/* open tape density/format */
#define		  ST_DENSITY_LO		0
#define		  ST_DENSITY_MLO	1
#define		  ST_DENSITY_MHI	2
#define		  ST_DENSITY_HI		3
#define		  ST_NDENSITY		4
	u_char	st_speed;		/* current tape speed */
#define		  ST_SPEED_LO	0
#define		  ST_SPEED_HI	1
#define		  ST_NSPEED	2
	u_char	st_bufmode;		/* current buffer mode */
	int	st_bufcnt;		/* number of buffers in use */
	int	st_fileno;		/* current file number on tape */
	int	st_blkno;		/* next record on tape */
	int	st_blkno_eof;		/* eof record on tape */
	int	st_bsize;		/* device unit block size (bytes) */
	struct scsi_blklim st_blklim;
	struct scsi_msen st_msen;
	struct mtget	st_mtget;
};

/* Defines for supported tape devices */
struct st_tp {
	char	*tp_vendor;		/* Vendor/model name */
	short	tp_vlen;		/* Vendor/model name length */
	char	*tp_type_str;		/* Drive type (mfg) string */
	char	tp_mt_type;		/* Drive type (mfg) code */
					/* see ../sys/mtio.h MT_IS constants */
	char	tp_media;		/* Drive media */
#define		  TP_MEDIA_UNKNOWN	0	/* ???? */
#define		  TP_MEDIA_QIC		1	/* 1/4" QIC cartrage */
#define		  TP_MEDIA_REEL		2	/* 1/2-inch reel tape */
#define		  TP_MEDIA_LCM		3	/* 1/2-inch cartrage tape */
#define		  TP_MEDIA_RDAT		4	/* RDAT video tape */
	short	tp_flags;		/* Drive options */
#define		  TP_FLAGS_FIXED	0x0001	/* fixed block size */
#define		  TP_FLAGS_BSF		0x0002	/* Supports backspace file */
#define		  TP_FLAGS_BSR		0x0004	/* Supports backspace record */
#define		  TP_FLAGS_RETEN	0x0010	/* Supports Retention */
#define		  TP_FLAGS_RETLD	0x0020	/* Retention on load */
#define		  TP_FLAGS_DEN_SENSE	0x0040	/* use mode sense density */
#define		  TP_FLAGS_PREVENT	0x0080	/* prevent removal off bot */
#define		  TP_FLAGS_BIG_REC	0x0100	/* allow big records */
#define		  TP_FLAGS_REW_IMM	0x0200	/* use IMM bit for rewinds */
#define		  TP_FLAGS_NOAUTO	0x0400	/* drive dosnt autodensity */
	u_int	tp_dump_density;	/* density for kernel dump */
	u_int	tp_nfm;			/* file marks to write at LEOT */
	u_int	tp_max_retries;		/* max retries on tape done by drive */
	u_int	tp_bsize[ST_NDENSITY];	/* block size of fixed */
	u_char	tp_den_rd[ST_NDENSITY];	/* read  density codes */
	u_char	tp_den_wr[ST_NDENSITY];	/* write density codes */
	u_char	tp_speed[ST_NSPEED];	/* speed code */
	short	tp_rewind_time;		/* max time to rewind tape (mins) */
	short	tp_seek_time;		/* max time to seek on tape (mins) */
	short	tp_erase_time;		/* max time to erase tape (mins) */
	u_int	tp_max_rec_size;	/* if BIG_REC used by minphys */
	char	**tp_error;		/* device specific sense code msgs */
};

/* structure for MTIOCGET - obsolete version */
#define	STIOCGET	_IOR(m, 2, struct st_mtget)
struct	st_mtget {
	short	mt_type;	/* type of magtape device */
	short	mt_dsreg;	/* drive status register */
	short	mt_erreg;	/* error register */
	short	mt_resid;	/* residual count */
	daddr_t	mt_fileno;	/* file number of current position */
	daddr_t	mt_blkno;	/* block number of current position */
};

