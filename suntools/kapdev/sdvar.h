/* @(#) sdvar.h 1.1@(#) Solbourne id 9/22/93 00:07:54 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/* SCSI CCS disk controller specific stuff. */

#define SECSIZE			512		/* Bytes/sector */
#define SECDIV			9		/* log2 (SECSIZE) */
#define	SDNBAD			16		/* number of reassign blocks */

/* SCSI disk device driver structure. */
struct scsi_disk {
	struct sd_tp		*sd_tp;		/* disk device info */
	int			sd_pdtype;	/* type of scsi device */
	int			sd_flags;	
#define				  SD_FLAGS_REMOVABLE	1
	int			sd_state;	/* disk driver state */
#define				  SD_STATE_BEGIN	0
#define				  SD_STATE_SENSE	1
#define				  SD_STATE_RETRY	2
#define				  SD_STATE_REZERO	3
#define				  SD_STATE_REASSIGN	4
#define				  SD_STATE_RESPIN	5
#define				  SD_STATE_END		6
#define		  		  SD_STATE_ASCII	\
					{"BEGIN", "SENSE", "RETRY", "REZERO", \
					"REASSIGN", "RESPIN", "END", 0 }
	struct dk_map		sd_map[NDKMAP];	/* logical partitions */
	int 			sd_sblk[NDKMAP];/* start block of partitions */
	struct dk_geom		sd_g;		/* disk geometry */
	struct sd_bad {				/* dynamic reassign table */
		daddr_t	block;			/* marginal block */
		short	retries;		/* # of failures */
	}			sd_bad[SDNBAD];
	u_int			sd_cyl_size;	/* blocks (sectors) per cyl */
	struct scsi_reassign 	*sd_reassign;	/* defect list address */
	struct scsi_reassign 	*sd_reassign_dma;/* dma address */
	u_short			sd_retries;	/* retry count */
	u_short			sd_restores;	/* restore count */
	struct dk_diag		sd_diag;	/* error information */
};

/* Defines for type of supported disks */
struct sd_tp {
	char	*tp_vendor;		/* Vendor/model name */
	short	tp_vlen;		/* Vendor/model name length */
	char	tp_maxtags;		/* number of tags to use */
	char	**tp_error;		/* device specific sense code msgs */
};

extern char *sd_state_ascii[];
