/* @(#) sodreg.h 1.1@(#) Solbourne id 9/22/93 00:08:17 */
/* @(#)sodreg.h	1.1 87/02/24	*/
#include <kapdev/sodio.h>

/*
 */

/*
 * SCSI optical disk controller specific stuff.
 */

#define SODNLPART 8

struct scsi_odisk {
        struct  sod_par sod_par[SODNLPART];        /* base block number in use */
        char    sod_loaded;             /* disk is locked in */
        char    sod_lp_open;            /* low 8 bits set for open partition*/
        char    sod_lp_open_cnt[SODNLPART];/* opens on partition since close */
        char    sod_d_open_cnt;         /* opens on disk since last close*/
        caddr_t sod_extra;              /* extra data space*/
        struct scsi_sense *sod_sense;   /* data space for request sense */
	int	sod_type;		/* type of drive */
	int	sod_class;		/* class of drive */
	int	sod_sec_size;		/* size of physical sector */
	int	sod_nsec;		/* number of sectors */
	int	sod_retries;		/* number of retries */
	int	sod_rdonly;		/* read only flag */
	int	sod_autoload;		/* auto load flag */
	int	sod_autoloaddev;	/* auto load device */
#ifdef i386
	short	saved_cmd; 		/* saved cmd */
	struct	scsi_cdb saved_cdb; 	/* saved cdb */
	struct	scsi_scb saved_scb; 	/* saved scb */
	int	saved_resid;		/* saved amt untransferred */
	int	saved_dma_addr;		
	u_short	saved_dma_count;
#endif
        };
#define UNKOWN		0
#define GD1001		1
#define RXT800		2
#define LMSCD210	3
#define HICD1553	4
#define LD1200		5
#define SONYCD		6
#define LD510		7
#define PIDDS5001	8
#define MW5D1		9

#define WORM	1
#define CDROM	2
