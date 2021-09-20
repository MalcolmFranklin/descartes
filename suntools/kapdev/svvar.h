/* @(#) svvar.h 1.2@(#) Solbourne id 11/10/93 18:36:26 */
/*
 * Copyright 1991-1993 Solbourne Computer, Inc.
 */

/* Interphase V/SCSI 4110/4220 SCSI host adaptor: driver data structures */

#ifndef	_SVVAR_
#define	_SVVAR_
#include <sys/osmp_lock.h>

extern int	sv_reset_report_time;	/* delay posting of reset (sec)*/
extern int	sv_reset_panic;		/* kernel panics if bus reset needed */
extern int	sv_reinit_panic;	/* kernel panics if ctlr reset needed */
extern int	sv_reinit_loop;		/* kernel loops if ctlr reset needed */
extern int	sv_reinit_delay;	/* kernel delay before ctlr reset */
extern int	sv_dload_debug;		/* debug enable for fw download */
extern int	sv_thaw_debug;		/* debug enable for freeze/thaw */
extern int	sv_multireap;		/* process multiple CRB's per intr */
extern int	sv_reset_retry;		/* retry bus reset before ctlr reset */
extern int	sv_resume_timeout;	/* delay for restart of CQA */
extern int	sv_cqe_wait_delay;	/* wait for CQE before CQA */
extern int	sv_cqa_inorder;		/* keep commands in order if CQA */
extern int	sv_iqar_ctl;		/* how to interrupt on CQA */
extern int	sv_burst;		/* vmebus burst cib value */
extern int	sv_ntags_max_c;		/* for small memory controllers */
extern int	sv_ntags_max_d;		/* for small memory controllers */

struct svs_dstat {		/* driver statistics */
    int		dstat_intr;		/* number of interrupts */
    int		dstat_crb;		/* number of crb's */
    int		dstat_cactive;		/* # of commands on the board */
    int		dstat_cpass;		/* # of pass commands issued */
    int		dstat_cpass_crb;	/* # of pass crb's processed */
    int		dstat_cqa_pend;		/* # CQA pending XXX NOT USED */
    int		dstat_cqa;		/* number of CQA */
    int		dstat_init;		/* number of inits */
    int		dstat_block;		/* number of commands block mode */
    int		dstat_nblock;		/* number of commands non-block mode */
    int		dstat_panics;		/* number of sv panics */
    int		dstat_hung;		/* number of sv hung */
    int		dstat_thaw;		/* number of sv thaws */
    int		dstat_thawl;		/* number of sv thaws loops */
    int		dstat_resync;		/* number of commands with resync */
    int		dstat_reset[2];		/* number of scsibus resets */
    int		dstat_qcount[16];	/* # of commands per workq */
    int		dstat_rcount[16];	/* # of read commands per workq */
    int		dstat_wcount[16];	/* # of write commands per workq */
#define		  SVS_STAT_CRB_BINS	16
    int		dstat_ncrb_intr[SVS_STAT_CRB_BINS]; /* histogram crb's/intr*/
};

struct svs_p {			/* configuration parameters */
    u_int	p_verbose;
    u_int	p_verbose_reset;
    u_int	p_verbose_crsw;
    u_int	p_blockmode;
    u_int	p_selto;
    u_int	p_cqe_offb;
    u_int	p_crb_offb;
    u_int	p_disable[2];
    u_int	p_hostid[2];
    u_int	p_sync[2];
    u_int	p_nsperxfer[2];
    u_int	p_offset[2];
    u_int	p_parity[2];
    u_int	p_boot_reset[2];
    u_int	p_mid[2];		/* reserved machine id's */
};

struct svs_svs {		/* controller info */
    struct sv_device	*svs_sv;	/* controller registers */
    struct svs_dstat	*svs_dstat;	/* pointer to driver stats */
    int			svs_ctype;	/* controller type */
#define			  SVS_CTYPE_4210	1
#define			  SVS_CTYPE_4220	2
#define			  SVS_CTYPE_ASCII	\
			  {"UNKNOWN", "V/SCSI", "V/SCSI2" }
    int			svs_btype[2];	/* bus type */
#define			  SVS_BTYPE_SINGLE	0x00
#define			  SVS_BTYPE_DIFF	0x01
#define			  SVS_BTYPE_WIDTH	0x02
#define			  SVS_BTYPE_8_BIT	0x00
#define			  SVS_BTYPE_16_BIT	0x02
#define			  SVS_BTYPE_ASCII	\
			  {"8sngl", "8diff", "16sngl",	\
			  "16diff"}
    u_int		svs_flags;	/* controller flags */
#define			  SVS_FLAGS_PRESENT	0x01
#define			  SVS_FLAGS_INIT	0x02
#define			  SVS_FLAGS_INTR	0x04
#define			  SVS_FLAGS_NO_CHECK	0x08
#define			  SVS_FLAGS_CQE_OFFB	0x10	/* useing offbrd CQE */
#define			  SVS_FLAGS_CRB_OFFB	0x20	/* useing offbrd CRB */
    u_char		svs_vec;	/* normal interrupt vector */
    u_char		svs_ilev;	/* interrupt level */
    struct scsi_unit	*svs_cqa_un;	/* unit that was tripped by no CQE */

    int			svs_cqeiopb_i;	/* index to next cqe/iopb pair */
    u_int		svs_businit;	/* bus init, bit per bus */
    u_int		svs_wqinit;	/* bit per scsi id workq initialized */
    struct svs_p	svs_p;		/* configuration parameters */
    char		svs_lock_name[16];/* name of lock */
    slock		svs_lock;	/* access to this controller */
    char		svs_reset_pend[2];/* recieve reset is pending */	
    char		svs_reset_issued[2];
    int			svs_cqa_pend;	/* # CQAs pending */
    u_int 		svs_dma_crb;
    int			svs_workq_alloc;
    char		svs_workq_trans[32];
    struct sv_crb	*svs_kbus_crb;
    struct sv_off_cqe	*svs_off_cqe[SV_NCQE_OFF];
};

/* Structure pointed to by DKIOCCFWUPD controller firmware download ioctl */
struct	sv_fw {
    int	fw_magic;
#define	FW_MAGIC	0xFECEFACE
    int	fw_nseg;
    struct	fw_seg {
	int	seg_len;
	char	*seg_addr;
    }	fw_seg[10];
} sv_fw;
#endif	_SVVAR_
