/* @(#) srvar.h 1.1@(#) Solbourne id 9/22/93 00:08:27 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/* SCSI CDROM disk controller specific stuff. */

#define FIVETWELVE
#define SECSIZE			512		/* Bytes/sector */
#define SECDIV			9		/* log2 (SECSIZE) */
#define SECSIZE_2048		2048		/* Bytes/sector */
#define SECDIV_2048		11		/* log2 (SECSIZE) */

/* CDROM device driver structure. */
struct scsi_rcd {
	struct sr_tp		*sr_tp;		/* disk device info */
	u_short			sr_open_0;
	u_short			sr_open_1;
	u_int			sr_flags;
#define				  SR_FLAGS_OPEN		0x0001
#define				  SR_FLAGS_EXOPENED	0x0002
	int			sr_state;	/* disk driver state */
#define				  SR_STATE_BEGIN	0
#define				  SR_STATE_SENSE	1
#define				  SR_STATE_RETRY	2
#define				  SR_STATE_REZERO	3
#define				  SR_STATE_TREADY	4
#define				  SR_STATE_PREVENT	5
#define				  SR_STATE_CAP		6
#define				  SR_STATE_END		7
#define		  		  SR_STATE_ASCII	\
					{"BEGIN", "SENSE", "RETRY", "REZERO", \
					"TREADY", "PREVENT", "CAP", "END", 0 }
	struct dk_map		sr_map[NDKMAP];	/* logical partitions */
	int 			sr_sblk[NDKMAP];/* start block of partitions */
	struct dk_geom		sr_g;		/* disk geometry */
	u_int			sr_cyl_size;	/* blocks (sectors) per cyl */
	u_short			sr_retries;	/* retry count */
	u_short			sr_restores;	/* restore count */
	struct dk_diag		sr_diag;	/* error information */
	u_int			sr_capacity;
	u_int			sr_bs;
	struct scsi_rcap 	*sr_rcap;	/* drive capacity */
	struct scsi_rcap 	*sr_rcap_dma;	/* dma address */
};

/* Defines for type of supported CDROM drives */
struct sr_tp {
	char	*tp_vendor;		/* Vendor/model name */
	short	tp_vlen;		/* Vendor/model name length */
	char	**tp_error;		/* device specific sense code msgs */
};

extern char *sr_state_ascii[];

/* Additional SCSI commands for CD-ROM */

/*	Group 2 Commands */
#define	SCMD_READ_TOC		0x43		/* optional SCSI command */
#define	SCMD_PLAYAUDIO_MSF	0x47		/* optional SCSI command */
#define	SCMD_PLAYAUDIO_TI	0x48		/* optional SCSI command */
#define	SCMD_PAUSE_RESUME	0x4B		/* optional SCSI command */
#define	SCMD_READ_SUBCHANNEL	0x42		/* optional SCSI command */
#define	SCMD_PLAYAUDIO10	0x45		/* optional SCSI command */
#define	SCMD_PLAYTRACK_REL10	0x49		/* optional SCSI command */
#define	SCMD_READ_HEADER	0x44		/* optional SCSI command */

/*	Group 5 Commands */
#define	SCMD_PLAYAUDIO12	0xA5		/* optional SCSI command */
#define	SCMD_PLAYTRACK_REL12	0xA9		/* optional SCSI command */

/*	Group 6 Commands */
#define	SCMD_CD_PLAYBACK_CONTROL 0xC9		/* SONY unique SCSI command */
#define	SCMD_CD_PLAYBACK_STATUS 0xC4		/* SONY unique SCSI command */

/*
 * CDROM io controls type definitions
 */
struct cdrom_msf {
	unsigned char	cdmsf_min0;	/* starting minute */
	unsigned char	cdmsf_sec0;	/* starting second */
	unsigned char	cdmsf_frame0;	/* starting frame  */
	unsigned char	cdmsf_min1;	/* ending minute   */
	unsigned char	cdmsf_sec1;	/* ending second   */
	unsigned char	cdmsf_frame1;	/* ending frame	   */
};

struct cdrom_ti {
	unsigned char	cdti_trk0;	/* starting track */
	unsigned char	cdti_ind0;	/* starting index */
	unsigned char	cdti_trk1;	/* ending track */
	unsigned char	cdti_ind1;	/* ending index */
};

struct cdrom_tochdr {
	unsigned char	cdth_trk0;	/* starting track */
	unsigned char	cdth_trk1;	/* ending track */
};

struct cdrom_tocentry {
	unsigned char	cdte_track;
	unsigned char	cdte_adr	:4;
	unsigned char	cdte_ctrl	:4;
	unsigned char	cdte_format;
	union {
		struct {
			unsigned char	minute;
			unsigned char	second;
			unsigned char	frame;
		} msf;
		int	lba;
	} cdte_addr;
	unsigned char	cdte_datamode;
};

/*
 * CDROM address format definition, for use with struct cdrom_tocentry
 */
#define	CDROM_LBA	0x01
#define	CDROM_MSF	0x02

/*
 * Bitmask for CD-ROM data track in the cdte_ctrl field
 * A track is either data or audio.
 */
#define	CDROM_DATA_TRACK	0x04

/*
 * For CDROMREADTOCENTRY, set the cdte_track to CDROM_LEADOUT to get
 * the information for the leadout track.
 */
#define	CDROM_LEADOUT	0xAA

struct cdrom_subchnl {
	unsigned char	cdsc_format;
	unsigned char	cdsc_audiostatus;
	unsigned char	cdsc_adr:	4;
	unsigned char	cdsc_ctrl:	4;
	unsigned char	cdsc_trk;
	unsigned char	cdsc_ind;
	union {
		struct {
			unsigned char	minute;
			unsigned char	second;
			unsigned char	frame;
		} msf;
		int	lba;
	} cdsc_absaddr;
	union {
		struct {
			unsigned char	minute;
			unsigned char	second;
			unsigned char	frame;
		} msf;
		int	lba;
	} cdsc_reladdr;
};

/*
 * Definition for audio status returned from Read Sub-channel
 */
#define	CDROM_AUDIO_INVALID	0x00	/* audio status not supported */
#define	CDROM_AUDIO_PLAY	0x11	/* audio play operation in progress */
#define	CDROM_AUDIO_PAUSED	0x12	/* audio play operation paused */
#define	CDROM_AUDIO_COMPLETED	0x13	/* audio play successfully completed */
#define	CDROM_AUDIO_ERROR	0x14	/* audio play stopped due to error */
#define	CDROM_AUDIO_NO_STATUS	0x15	/* no current audio status to return */

/* definition of audio volume control structure */
struct cdrom_volctrl {
	unsigned char	channel0;
	unsigned char	channel1;
	unsigned char	channel2;
	unsigned char	channel3;
};

struct cdrom_read {
	int	cdread_lba;
	caddr_t	cdread_bufaddr;
	int	cdread_buflen;
};

#ifdef FIVETWELVE
#define	CDROM_MODE1_SIZE	512
#else
#define	CDROM_MODE1_SIZE	2048
#endif FIVETWELVE
#define	CDROM_MODE2_SIZE	2336

/*
 * CDROM io control commands
 */
#define	CDROMPAUSE	_IO(c, 10)	/* Pause Audio Operation */

#define	CDROMRESUME	_IO(c, 11)	/* Resume paused Audio Operation */

#define	CDROMPLAYMSF	_IOW(c, 12, struct cdrom_msf)	/* Play Audio MSF */
#define	CDROMPLAYTRKIND	_IOW(c, 13, struct cdrom_ti)	/*
							 * Play Audio
`							 * Track/index
							 */
#define	CDROMREADTOCHDR	\
		_IOR(c, 103, struct cdrom_tochdr)	/* Read TOC header */
#define	CDROMREADTOCENTRY	\
	_IOWR(c, 104, struct cdrom_tocentry)		/* Read a TOC entry */

#define	CDROMSTOP	_IO(c, 105)	/* Stop the cdrom drive */

#define	CDROMSTART	_IO(c, 106)	/* Start the cdrom drive */

#define	CDROMEJECT	_IO(c, 107)	/* Ejects the cdrom caddy */

#define	CDROMVOLCTRL	\
	_IOW(c, 14, struct cdrom_volctrl)	/* control output volume */

#define	CDROMSUBCHNL	\
	_IOWR(c, 108, struct cdrom_subchnl)	/* read the subchannel data */

#define	CDROMREADMODE2	\
	_IOW(c, 110, struct cdrom_read)		/* read CDROM mode 2 data */

#define	CDROMREADMODE1	\
	_IOW(c, 111, struct cdrom_read)		/* read CDROM mode 1 data */
