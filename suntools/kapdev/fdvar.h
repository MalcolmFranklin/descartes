/* @(#) fdvar.h 1.1@(#) Solbourne id 9/22/93 00:06:23 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

#define	NFD_PER_FDC		4
#define	NFD_PER_FDC_SHFT	2

#define	PART(dev)	(dev & NDKMSK)
#define	UNIT(dev)	(minor(dev) >> NDKSHFT)
#define	CTLR(dev)	(minor(dev) >> (NDKSHFT + NFD_PER_FDC_SHFT))

/*
 * There an ioctl that alow you to turn on debug trace for the floppy.
 * At levels 0 (no tracing) and 1 (every but during an interrupt) we
 * can use the normal poll counts.  At level 2 we must use the higher
 * polling values basicly disables the fifo interrupt so that we can
 * print during the interrupt routine.
 */
#define FD_WOPT_COUNT_NORMAL	0x1000
#define FD_COUNT_NORMAL		0x100
#define FD_WOPT_COUNT_DEBUG	0x40000
#define FD_COUNT_DEBUG		0x1000

/* information related to controller */
struct fd_ctlr {
    char	*ctlr_name;
    struct fd_drive *ctlr_drive[NFD_PER_FDC];/* type of drive for each unit */
    u_char	ctlr_wopt;		/* do write optimization */
    u_int	ctlr_poll_count_wopt;	/* number of times to poll for wopt */
    u_int	ctlr_poll_count;	/* number of times to poll */
    u_char	ctlr_eis;		/* enable implied seeks */
    u_char	ctlr_max_sec;		/* max number of sectors at a time */
    u_char	ctlr_idle_moff;		/* seconds of idle till motor off */
    u_char	ctlr_close_eject;	/* seconds of close till disk eject */
};

/* information related to drive */
struct fd_drive {
    char	*drive_name;
    struct fd_disk	**drive_disks;	/* disks supported by drive */
    struct fd_disk	*drive_disk_hi;	/* default high density disk */
    struct fd_disk	*drive_disk_low;/* default low density disk */
    u_char	drive_step_rate;	/* maximum head step rate */
    u_char	drive_step_width;	/* minimum step pulse width */
    u_char	drive_head_load;	/* time to load heads */
    u_char	drive_head_unload;	/* time to unload heads */
    u_char	drive_motor_on;		/* time to spin drive */
    u_char	drive_motor_off;	/* time for disk to stop spinning */
    u_int	drive_rpm;		/* rotational speed of drive */
    u_char	drive_eject;		/* drive ejects disks */
};

/* information related to disks */
struct fd_disk {
    char	*disk_name;
    struct dk_allmap *disk_dk_map;	/* default partition info */
    u_char	disk_density;
    u_short	disk_drate;
    u_short	disk_tpi;		/* track density per inch */
    u_short	disk_ncyl;		/* number of cylinders */
    u_char	disk_nhead;		/* number of heads */
    u_char	disk_nspt;		/* number of sectors per track */
    u_short	disk_nbps;		/* number of bytes per sector */
    u_char	disk_dtl;		/* special nbps */
    u_char	disk_gap3_dt;		/* number of bytes in gap3 for io */
    u_char	disk_gap3_fmt;		/* number of bytes in gap3 for format */
    u_char	disk_fsec;		/* first sector number */
    u_char	disk_precomp;		/* precomp amount */
    u_short	disk_precomp_cyl;	/* cylinder to start precomp */
    u_char	disk_interleave;	/* format interleave factor */
    u_char	disk_fmt_data;		/* format data */
};


/* dynamic per-drive driver information */
struct fd_softc {		/* per-drive data */
    struct fdreg	*fs_fdreg;		/* pointer to controller hw */
#ifdef OPENPROMS
    struct dev_info	*fs_devinfo;		/* pointer to devinfo struct */
#else
    struct mb_device	*fs_md;			/* pointer to device struct */
#endif
#ifdef new_code
    struct buf		*fs_bpf;		/* first pointer to bp */
    struct buf		*fs_bpl;		/* last pointer to bp */
    int			fs_active;		/* command in progress */
#endif
    int			fs_flags;		/* flags */
#define		FS_FLAGS_OPEN		0x01	/* drive open */
#define		FS_FLAGS_OPEN_EXCL	0x02	/* opened exclusive */
#define		FS_FLAGS_MOTOR_ON	0x04	/* motor is on */
#define		FS_FLAGS_SPECBUSY	0x08	/* specail cmd busy */
#define		FS_FLAGS_WAIT		0x10	/* waiting for completion */
#define		FS_FLAGS_DONE		0x20	/* buf is done */
#define		FS_FLAGS_WANTSPEC	0x40	/* special cmd wanted */
#define		FS_FLAGS_RDONLY		0x80	/* Write protect bit is set */
#define		FS_FLAGS_NODISK		0x100	/* No disk in drive */
#define		FS_FLAGS_INIT		0x200	/* fd_init() has been called */
#define		FS_FLAGS_RESET		0x400	/* chip reset has been done */
#define		FS_FLAGS_MOTOR_TIMEOUT	0x800	/* a motor timeout has started */
    int			fs_state;		/* controller state */
    struct fd_ctlr	*fs_ctlr;		/* type of disk inserted */
    struct fd_drive	*fs_drive;		/* current drive */
    struct fd_disk	fs_disk;		/* type of disk inserted */
    struct dk_allmap	fs_dk_map;		/* current partition info */
    union fdc_cmd	fs_cmd;			/* current command buffer */
    union fdc_rsl	fs_rsl;			/* current result buffer */
    union fdc_cmd	fs_special_cmd;		/* special command buffer */
    union fdc_rsl	fs_special_rsl;		/* special result buffer */
#define	BUFSIZE	1024
    u_char		fs_buf[BUFSIZE];	/* fast access buffer... */
    u_int		fs_ignore_int;		/* ignore the next interrupt */
    short		fs_c;			/* current cylinder number */
    short		fs_h;			/* current head track number */
    int			fs_addr;		/* virtual addr of xfer */
    u_short		fs_bleft;		/* bytes left to transfer */
    u_short		fs_bpart;		/* bytes to transfer */
    u_short		fs_bpart_done;		/* bytes done transferring */
    u_short		fs_retry;
#define			  FS_RETRY_MAX	3	/* WAG */
    short		fs_try_results;
    short		fs_send_sense;
    short		fs_previous;		/* previous command - debug */
} fd_softc[];

/* driver ioctl() commands */
#define	V_FORMAT   _IOW(V, 5, union io_arg)	/* Format track(s) */
#define FDKIODEBUG _IOW(F, 1, int)	/* Turn tracing on/off */

union   io_arg {
    struct  {
	ushort		ncyl;		/* number of cylinders on drive */
	unsigned char	nhead;		/* number of heads/cyl */
	unsigned char	nsec;		/* number of sectors/track */
	ushort		secsiz;		/* number of bytes/sector */
    }			ia_cd;		/* used for Configure Drive cmd */
    struct  {
	ushort		flags;		/* flags (see below) */
	daddr_t		bad_sector;	/* absolute sector number */
	daddr_t		new_sector;	/* RETURNED alternate sect assigned */
    }			ia_abs;		/* used for Add Bad Sector cmd */
    struct  {
	ushort		start_trk;	/* first track # */
	ushort		num_trks;	/* number of tracks to format */
	ushort		intlv;		/* interleave factor */
    }			ia_fmt;		/* used for Format Tracks cmd */
};

struct fdexec {				/* controller command structure */
    u_char		fd_cmd[9];	/* user-supplied command bytes */
    u_char		fd_rsl[7];	/* controller-supplied result bytes */
    short		fd_cnum;	/* number of command bytes */
    short		fd_nbytes;	/* # bytes to transfer */
    char		*fd_addr;	/* where to transfer */
};

struct fdformid {
    char	fdf_cyl;
    char	fdf_head;
    char	fdf_sec;
    char	fdf_secsiz;
};
