/* @(#) save.vtoc.h 1.1@(#) Solbourne id 9/22/93 00:03:50 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ident	"@(#)kern-port:sys/vtoc.h	10.1"
/*
 * VTOC.H
 * A VTOC resides at the beginning of all disk media and contains physical 
 * geometry and logical partitioning information.
 */

/*
 * misc defines
 */
#define VTOC_SANE	0x600DDEEE	/* indicates a sane VTOC */
#define V_NUMPAR 	16		/* maximum number of partitions */
#define V_VERSION	0x01		/* vtoc layout version number */
#define V_MAXNAME	16		/* maximum chars in volume name */
#define V_FULLDISK	15		/* partition for whole disk */

/*
 * The partition information describes the logical partitioning of the
 * physical device.
 */
struct partition {
	u_short		p_tag;		/* ID tag of partition */
	u_short		p_flag;		/* permission flags */
	int		p_fstype;	/* file system type */
	daddr_t		p_start;	/* start sector num of partition */
	long		p_size;		/* num of sectors in partition */
};

/* 
 * Partition identification tags, indicates use of the partition.
 */
#define V_UNUSED	0x00		/* unused partition */
#define V_BOOT		0x01		/* Boot partition */
#define V_ROOT		0x02		/* Root filesystem */
#define V_SWAP		0x03		/* Swap filesystem */
#define V_USR		0x04		/* Usr filesystem */
#define V_OVERLAP	0x05		/* overlaps other partitions */
#define V_TRACKFORWARD	0x06		/* For track forwarding */
#define V_SECTORFORWARD	0x07		/* For sector forwarding */

/* 
 * partition permission flags 
 */
#define V_UNMNT		0x01		/* Unmountable partition */
#define V_RONLY		0x10		/* Read only */

/*
 * partition filesystem type flags 
 * NOTE: also used as indices into file system switch
 */
#define V_FSTYPE_CKVTOC	-1		/* get fstype from vtoc */
#define	V_FSTYPE_NONE	0		/* no file system */
#define	V_FSTYPE_BSD	1		/* BSD file system */
#define	V_FSTYPE_SYSV	2		/* system V file system */
#define	V_FSTYPE_BOOT	3		/* boot file system */
#define V_FSTYPE_NET	4		/* network file system */
#define V_FSTYPE_TTY	5		/* serial line file system */
#define	V_FSTYPE_MAX	5		/* maximum valid filesystem type */


#define PD_SERIAL	16		/* maximum chars in a pd serial # */

/*
 * This structure defines the physical description (geometry) of the device.
 */
struct pdinfo {
	char		pd_serial[PD_SERIAL];	
					/* serial number of the device */
	u_short		pd_devtype;	/* identifies the device type */
	u_short		pd_apc;		/* anternates per cyl (SCSI only) */
	u_char		pd_skew;	/* spiral skew, cylinder skew */
	u_char		pd_gap1;	/* words of 0 before header */
	u_char		pd_gap2;	/* words of 0 between hdr and data */
	u_char		pd_interleave;	/* sector interleave */
	u_short		pd_cyls;	/* number of cylinders per drive */
	u_short		pd_tracks;	/* number tracks per cylinder */
	u_short		pd_sectors;	/* number sectors per track */
	u_short		pd_bytes;	/* number of bytes per sector */
	u_short		pd_dcyls;	/* number of data cylinders */
	u_short		pd_acyls;	/* number of alternate cylinders */
	u_short		pd_rpm;		/* revolutions per minute */
	u_short		pd_flags;	/* device specific characteristics */
};

/*
 * physical description flags indicating device specific characteristics
 */
#define PD_SEC_SLIP	0x0001		/* slip defective sectors */
#define PD_SEC_FORWARD	0x0002		/* forward defective sector */
#define PD_TRK_FORWARD	0x0004		/* forward defective track */

/*
 * This structure defines the volume table of contents. A VTOC resides at
 * the beginning of all disk media and contains physical geometry and 
 * logical partitioning information.
 */
struct vtoc {
	u_long		v_sanity;	/* to verify vtoc sanity */
	u_long		v_version;	/* layout version */
	char		v_volume[V_MAXNAME]; /* volume name */
	struct pdinfo	v_pdinfo;	/* physical device geometry */
	struct partition v_part[V_NUMPAR]; /* partition headers */
	char		v_pad[512 - (2*sizeof(u_long) + V_MAXNAME*sizeof(char)
				+ sizeof(struct pdinfo) + 
				V_NUMPAR*sizeof(struct partition))- sizeof(short)];
	short		v_cksum;	/* vtoc checksum */
};

/* 
 * vtoc ioctls
 */
#define	VIOCGVTOCLOC	_IOR(V, 1, long)		/* Get VTOC location */
#define	VIOCGPINFO	_IOR(V, 2, struct partition)	/* Get part params */
#define VIOCVTOCRD	_IO(V, 3)			/* Force read of VTOC */
#define VIOCGETPDINFO	_IOR(V, 4, struct pdinfo)	/* Get device info */
#define	VIOCSPINFO	_IOW(V, 5, struct partition)	/* Set part params */
