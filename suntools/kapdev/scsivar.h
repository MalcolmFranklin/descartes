/* @(#) scsivar.h 1.2@(#) Solbourne id 10/18/93 17:38:55 */
/*
 * Copyright 1988-1993 Solbourne Computer, Inc.
 * All rights reserved.
 */

#ifndef	_SCSIVAR_
#define	_SCSIVAR_

#ifdef	TRACE
#undef	TRACE_LOCK_ALL
#define	TRACE_LOCK_ALL		/* XXX DEBUG trace the scsi locks */
#endif	TRACE
#include <dev/scsi.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/vnode.h>
#include <sys/osmp_lock.h>

extern int	scsi_verbose, scsi_verbose_watchdog_decay;
extern int	scsi_hur_discon;
extern int	scsi_timeout_debug;
extern int	scsi_reset_delay;
extern int	scsi_congestion_recovery;
extern int	scsi_congested_debug;
extern int	scsi_alloc_resume;
extern int	scsi_ntags_max_c, scsi_ntags_max_d;
extern int	scsi_fair;
extern int	scsi_qbp;

/* Switch for controller (host adaptor) routines called from units (devices). */
struct	scsi_ctlr_sw {
    char		*scs_cname;		/* name of ctlr */
    int			scs_nc;			/* number of ctlrs */
    struct scsi_ctlr	*scs_c;			/* array of scsi_ctlr structs */
    int			(*scs_cmd)();		/* execute a command */
    int			(*scs_ecal)();		/* end contingent allegience */
    int			(*scs_flush)();		/* flush pendig state */
    int			(*scs_reset)();		/* reset scsi bus */
    int			(*scs_perror)();	/* print ctlr error */
    int			scs_ctype;		/* type of ctlr */
    int			scs_flags;
#define		SCS_FLAGS_PARITY	0x0001	/* ctlr does synch */
#define		SCS_FLAGS_DISCON	0x0002	/* ctlr does discon */
#define		SCS_FLAGS_SYNC		0x0004	/* ctlr does synch */
#define		SCS_FLAGS_RRESET	0x0008	/* ctlr receives resets sent */
#define		SCS_FLAGS_XPAD		0x0010	/* ctlr does transfer pad */
#define		SCS_ALLOC_TIMEOUT	0x0020	/* ctlr wants alloc timeout */
#define		SCS_FLAGS_QTAG_C	0x0040	/* ctlr does tags */
#define		SCS_FLAGS_QTAG_D	0x0080	/* ctlr does tags to drive */
#define		SCS_FLAGS_INTEL		0x0100	/* ctlr is "inteligent" */
#define		SCS_FLAGS_BITS		\
"\20\11INTEL\10QTAG_D\7QTAG_C\6TIMEOUT\5XPAD\4RRESET\3SYNC\2DISC\1PARITY"
    int			(*scs_dreset)();	/* send dev reset message */
    int			(*scs_abort)();		/* send abort message */
};
extern struct scsi_ctlr_sw	scsi_ctlr_sw[];
struct scsi_ctlr_sw		*scsi_find_ctlr_sw();

/* Controller (host adaptor (scsibus)) control block. */
struct scsi_ctlr {
	struct scsi_ctlr_sw	*c_scs;		/* scsi ctlr subroutines */
	struct mb_ctlr		*c_mc;		/* mb controller */
	struct scsi_ctlr	*c_ctlrs;	/* chain all ctlrs */
	int			c_flags;	/* misc flags */
#define		C_FLAGS_PRESENT		0x00000001/* scsi bus is alive */
#define		C_FLAGS_ACTIVE		0x00000002/* scsi bus is active */
#define		C_FLAGS_RESET		0x00000004/* scsi bus was reset */
#define		C_FLAGS_SRESET		0x00000008/* servicing scsi bus reset */
#define		C_FLAGS_IDLE		0x00000010/* idleing scsi bus */
#define		C_FLAGS_SUSP		0x00000020/* suspend scsi bus */
#define		C_FLAGS_NODVMA		0x00000040/* out of DVMA */
#define		C_FLAGS_CTLR_1		0x40000000/* controller specific flag */
#define		C_FLAGS_CTLR_0		0x80000000/* controller specific flag */
#define		C_FLAGS_BITS		\
"\20\40CTLR_0\37CTLR_1\7NODVMA\6SUSP\5IDLE\4SRESET\3RESET\2ACTIVE\1PRESENT"
	struct scsi_unit	*c_units;	/* chain all units */
	struct scsi_unit	*c_un;		/* scsi unit now using ctlr */
	struct scsi_unit	*c_unf;		/* chain pending units */
	struct scsi_unit	*c_unl;		/* end chain pending units */
	struct scsi_unit	*c_dunf;	/* chain disconnect units */
	struct scsi_unit	*c_dunl;	/* end chain disconnect units */
	struct scsi_unit	*c_runf;	/* chain reset units */
	struct scsi_unit	*c_runl;	/* end chain reset units */

	int			c_cspec[4];	/* controller specific info */
	slock			c_lock;		/* access to this scsibus */
	char			c_lock_name[12];/* name of lock */
	struct scsi_unit	*c_lst_un;	/* last scsi unit using ctlr */
	int			c_suspend_loop;
	int			c_start_depth;		/* DEBUG ONLY */
	int			c_start_depth_max;	/* DEBUG ONLY */
	int			c_ntags_max_c;	/* max tags to controller */
	int			c_ntags_max_d;	/* max tags to drive */
	char			c_unit_name_buf[16];
};
extern struct scsi_ctlr		*scsi_ctlrs;		/* chain all ctlrs */
extern struct scsi_ctlr_sw	scsi_ctlr_sw[];
/* controller specific information is a pointer to the scsi_ctlr structure */
#define	mc_c	mc_spec

/* Switch for unit (device) routines called from controllers (host adaptors). */
struct	scsi_unit_sw {
	char			*sus_uname;	/* name of device */
	int			sus_nun;	/* number of units */
	struct scsi_unit	*sus_un;	/* array of scsi_unit structs */
	int			(*sus_attach)();/* attach a device */
	int			(*sus_strat)();	/* queue command for device */
	int			(*sus_start)();	/* start a command */
	int			(*sus_intr)();	/* process an interrupt */
	int			(*sus_perror)();/* print extended sense code */
	int			sus_retries;	/* number of retries */
	int			sus_restores;	/* number of restores */
	int			sus_fails;	/* number of fails */
	int			sus_busyretry;	/* number of busy retries */
	int			sus_busydelay;	/* sec's delay between retry */
	int			sus_retry_disc_to;/* retry disconnect to's */
	int			(*sus_disc)();	/* save tagged command state */
	int			(*sus_recon)();	/* restore tag command state */
};
extern struct scsi_unit_sw	scsi_unit_sw[];
struct scsi_unit_sw		*scsi_find_unit_sw();

/* Unit (device) block. */
struct scsi_unit {
	struct scsi_unit_sw	*un_sus;	/* scsi unit subroutines */
	char			un_target;	/* scsi bus address of unit */
#define				  TARGET(slave)	((slave) & 0x0F)
	char			un_lun;		/* scsi lun of unit */
#define				  LUN(slave)	(((slave) >> 4) & 0xFF)
	short			un_unit;	/* real unit number of device */
	int			un_flags;	/* misc flags */
#define		UN_FLAGS_PRESENT	0x00000001/* device is online */
#define		UN_FLAGS_SPECBUSY	0x00000002/* special resources used */
#define		UN_FLAGS_WANTSPEC	0x00000004/* waiting for special */
#define		UN_FLAGS_PARITY		0x00000008/* enable parity */
#define		UN_FLAGS_DISCON		0x00000010/* allow disconnect */
#define		UN_FLAGS_SYNC		0x00000020/* negotiate sync */
#define		UN_FLAGS_SYNC_NEGO	0x00000040/* sync negotation done */
#define		UN_FLAGS_PREEMPT	0x00000080/* preempted by recon */
#define		UN_FLAGS_RESET		0x00000100/* device was reset */
#define		UN_FLAGS_CMD_TO		0x00000200/* command timed out */
#define		UN_FLAGS_HUR_DISCON	0x00000400/* huristic for discon */
#define		UN_FLAGS_DELAYED	0x00000800/* start delayed for unit */
#define		UN_FLAGS_MULTI_LUN	0x00001000/* multi cmds diff luns */
#define		UN_FLAGS_MSG_JUST_CC	0x00002000/* only cmd complete msg */
#define		UN_FLAGS_CONGESTED	0x00004000/* command congested */
#define		UN_FLAGS_OPTIMIZING	0x00008000/* optimize operations */
#define		UN_FLAGS_RDELAY		0x00010000/* restart delayed */
#define		UN_FLAGS_SYNC_NEGOMSG	0x00020000/* sync message produced */
#define		UN_FLAGS_DISCON_TO	0x00040000/* disconnect timeout */
#define		UN_FLAGS_ABORT	 	0x00080000/* sending abort message */
/*#define		UN_FLAGS_NODVMA	 	0x00100000/*   ran out of DVMA */
#define		UN_FLAGS_HIPRI	 	0x00200000/* high priority command */
#define 	UN_FLAGS_QTAG_C		0x00400000/* queue tag to ctlr */
#define 	UN_FLAGS_QTAG_D		0x00800000/* queue tag to drive */
#define 	UN_FLAGS_QTAG		0x00C00000/* queue tag to ctlr|drive */
#define 	UN_FLAGS_NOSTART	0x01000000/* dont start commands */
#define		UN_FLAGS_ONSTART	0x02000000/* on c_unf start list */
#define		UN_FLAGS_CAL		0x04000000/* contingent allegiance */
#define		UN_FLAGS_NO_WIDE	0x08000000/* no wide transfers */
#define		UN_FLAGS_CTLR_1		0x40000000/* controller specific flag */
#define		UN_FLAGS_CTLR_0		0x80000000/* controller specific flag */
#define		UN_FLAGS_BITS		\
"\20\40CTLR_0\37CTLR_1\34NOWIDE\33CAL\32ONSTART\31NOSTART\30QD\
\27QC\26HIPRI\25NDVMA\24ABORT\23DISCTO\22SYNCM\21RDELAY\20OPTIM\
\17CONGEST\16MSGCC\15MLUN\14DELAY\13HURD\12CMDTO\11RESET\10PREEMPT\
\7SYNCN\6SYNC\5DISC\4PARITY\3WSPEC\2SBUSY\1PRESENT"
	int			un_sync_param;	/* sync off/transfer period */
	struct scsi_ctlr	*un_c;		/* scsi ctlr */
	struct mb_device	*un_md;		/* mb device */
	struct scsi_unit	*un_units;	/* chain all units */
	struct scsi_unit	*un_forw;	/* c_unf forward pointer */
	struct scsi_unit	*un_dforw;	/* c_dunf forward pointer */
	struct scsi_unit	*un_rforw;	/* c_runf forward pointer */
	struct buf 		un_sbuf;	/* buffer for special cmds */
	struct buf 		un_rbuf;	/* buffer for raw i/o */
	struct vnode		*un_ttyvp;	/* tty for exclusive device */
	struct un_cmd	{			/* command information */
	    union scsi_cdb	cmd_cdb;	/*   scsi command block */
	    int			cmd_dma_saddr;	/*   start address for data */
	    int			cmd_dma_scnt;	/*   total count for data */
	    int			cmd_dma_addr;	/*   current address for data */
	    int			cmd_dma_cnt;	/*   current count for data */
#define		CMD_DMA_RESID(cmd)		/*   data left to transfer */ \
			(cmd->cmd_dma_saddr + cmd->cmd_dma_scnt) - \
			(cmd->cmd_dma_addr + cmd->cmd_dma_cnt)
	    int			cmd_dma_tcr;	/*   current transfer counter */
	    struct buf		*cmd_bp;	/*   buf associated with cmd */
	    struct buf		*cmd_bp0;	/*   initial buf for cmd */
	    int			cmd_timeout;	/*   timeout time (in sec) */
	    int			cmd_timer;	/*   time until timeout */
	    int			cmd_ctlb_flags;	/*   command table flags */
	    int			cmd_flags;	/*   misc flags */
#define		CMD_FLAGS_SILENT	0x0001	/*     don't print messages */
#define		CMD_FLAGS_NORETRY	0x0002	/*     don't retry errors */
#define		CMD_FLAGS_UDMA		0x0004	/*     user space dma */
#define		CMD_FLAGS_NODISCON	0x0008  /*     prohibit disconnect */
#define		CMD_FLAGS_CONTROL_BITS	0x00FF	/*     upper lev control bits */
#define		CMD_FLAGS_SCBV		0x0100	/*     scsi status valid */
#define		CMD_FLAGS_ECV		0x0200	/*     error code valid */
#define		CMD_FLAGS_SENSEV	0x0400	/*     sense info is valid */
#define		CMD_FLAGS_STATUS_BITS	0xFF00	/*     low level status bits */
	    union scsi_scb	cmd_scb;	/*   scsi status */
	    int			cmd_error_code;	/*   ctlr specific error code */

	    int			cmd_uspec[4];	/*   unit specific cmd info */
	}			un_cmd;		/* active command */
	struct un_cmd		un_save_cmd;	/* saved command during retry */
	struct un_cmd		un_special_cmd;	/* pending special command */
	union scsi_sns		*un_sns;	/* request sense data */
	union scsi_sns		*un_sns_dma;	/* request sense dma address */
	int			un_sns_cookie;	/* request sense dma cookie */
	int			un_busy;	/* busy retry count */

	struct	un_tag	{			/* tagged command info */
	    struct scsi_unit	*tag_un;	/*   link back to scsi_unit */
	    struct un_tag	*tag_forw;	/*   link for tagged commands */
	    int			tag_n;		/*   command tag #(and index) */
	    struct un_cmd	tag_cmd;	/*   command */
	    struct un_cmd	tag_save_cmd;	/*   saved command */
	    int			tag_mbinfo;	/* Mainbus allocation info */
#define	NUM_TAG_CMDS		32	
	}			un_tag[NUM_TAG_CMDS];
	struct	un_tag		un_tag_poll;	/* tag for polled mode cmds */
	int			un_ntags;	/* maximum number of tags */
	int			un_tag_nactive;	/* number of active tags */
	int			un_tag_wretire;	/* waiting for retirement */
	struct un_tag		*un_tag_retire;	/* retired tag list */
	struct un_tag		*un_tag_free;	/* tag free list */
	struct un_tag		*un_tag_active;	/* ptr to active cmd tag */
	struct un_tag		*un_tagf;	/* head of pending tags */
	struct un_tag		*un_tagl;	/* tail of pending tags */
	struct un_tag		*un_dtagf;	/* head of disc tag commands */
	struct un_tag		*un_dtagl;	/* tail of disc tag commands */
	struct un_tag		*un_rtagf;	/* head of reset disc tags */
	struct un_tag		*un_rtagl;	/* tail of reset disc tags */

	int			un_qbp;		/* number of queued bp's */
	int			un_cspec[4];	/* controller specific info */
};
/* device specific information is a pointer to the scsi_unit structure */
#define	md_un	md_spec
extern char	*scsi_unit_name();

/*
 * Error class passed to device routines. The value refers to general errors, 
 * not to controller specific errors.  Controller specific errors are 
 * communicated in error_code, and printed with scs_perror(error_code).
 * The distinction between retryable and fatal is somewhat ad hoc.
 */
#define ERROR_CLASS_OK		0	/* no error */
#define ERROR_CLASS_NONE	ERROR_CLASS_OK
#define ERROR_CLASS_RECOVERED	1	/* recoverable error occured */
#define ERROR_CLASS_RETRY	2	/* failed, but can be retried */
#define ERROR_CLASS_RESET	3	/* processing scsi reset */
#define ERROR_CLASS_SEL_TO	4	/* selection timed out */
#define ERROR_CLASS_FATAL	5	/* fatal error */
#define ERROR_CLASS_CMD_TO	6	/* command timed out */
#define ERROR_CLASS_SCSI_RESET	7	/* got scsi reset */
#define ERROR_CLASS_ALLOC	8	/* failed resource allocation */
#define	ERROR_CLASS_ASCII	{"OK", "RECOVERED", "RETRY", "RESET",	\
				"SEL_TO", "FATAL", "CMD_TO",		\
				"SCSI_RESET", "ALLOC" }
extern char	*scsi_error_class_ascii[];

/*
 * Intr values are returned from the upper level interrupt routines and
 * control the dequeing to be done by the common code. The values indicate
 * that the operation is complete (done), the operation should be retried
 * (retry), that the interrupt routine wants to try a recovery (recovery), 
 * and that the interrupt routine wants its start routine called again for 
 * the operation (restart).
 */
#define	INTR_DONE		0	/* operation completed (maybe error) */
#define	INTR_RETRY		1	/* operation should be retried */
#define	INTR_RECOVERY		2	/* recovery operation set up */
#define	INTR_RESTART		3	/* operation should restart, new dma */
#define	INTR_DELAY_BIT		0x4	/* delay further operation a while */
#define	INTR_ASCII		{"DONE", "RETRY", "RECOVERY", "RESTART", \
				"DELAYDONE", "DELAYRETRY", "DELAYRECOVERY", \
				"DELAYRESTART"}
extern char	*scsi_intr_ascii[];

/* bp flag definition for parallel optimization of raw io */
#define B_PHYS_PARALLEL B_BAD	/* XXX - B_BAD not used at this time */
#endif	_SCSIVAR_
