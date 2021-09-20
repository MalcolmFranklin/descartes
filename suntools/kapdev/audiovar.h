/* @(#) audiovar.h 1.1@(#) Solbourne id 9/22/93 00:05:08 */
/*
 * Copyright 1991 Solbourne Computer, Inc.
 * All rights reserved.
 */
/*	@(#)audiovar.h 1.2 90/12/05 SMI	*/
/* Copyright (c) 1989 by Sun Microsystems, Inc. */

#ifndef _sbusdev_audiovar_h
#define	_sbusdev_audiovar_h

#include <sys/stream.h>
#ifdef	solbourne
#include <mfg/audioio.h>
#else	solbourne
#include <sun/audioio.h>
#endif	solbourne

/*
 * The audio driver is divided into generic (device-independent)
 * and device-specific modules.  The generic routines handle most
 * STREAMS protocol issues, communicating with the device-specific
 * code via function callouts and a chained control block structure.
 *
 * Separate control block lists are maintained for reading (record)
 * and writing (play).  These control blocks simulate a chained-DMA
 * structure, in that each block controls the transfer of data between
 * the device and a single contiguous memory segment.
 *
 * The command block contains buffer start and stop addresses,
 * a link address to the next block in the chain, a 'done' flag,
 * a 'skip' flag (indicating that this command block contains no
 * data), and a pointer to the STREAMS data block structure which
 * is private to the generic driver.
 *
 * The device-specific audio driver code is expected to honor the
 * 'skip' flag and set the 'done' flag when it has completed
 * processing the command block (i.e., the data transfer, if any,
 * is complete).  For record command blocks, it is also expected
 * to add to the 'data' pointer the number of bytes successfully
 * read from the device.
 *
 *
 * The device-specific driver module must initialize the static STREAMS
 * control structures and must provide an identify routine (sbus-only),
 * an attach routine, and an open routine.  The open routine verifies
 * the device unit number and calls the generic open routine with
 * the address of the audio_state structure for that unit.
 *
 *
 * The generic audio driver makes calls to the device-specific code
 * through an ops-vector table.  The following routines must be provided:
 *
 * The 'close' routine is called after either the play or record stream
 * is closed.  It may perform device-specific cleanup and initialization.
 *
 * void dev_close(v, which)
 *	aud_state_t	*v;		| Pointer to audio device state
 *	enum aud_which	which;		| AUD_PLAY || AUD_REC
 *
 *
 * The 'ioctl' routine is called from the STREAMS write put procedure when
 * a non-generic ioctl is encountered (AUDIO_SETINFO, AUDIO_GETINFO, and
 * AUDIO_DRAIN are the generic ioctls).  Any required data mblk_t is
 * allocated; its address is given by mp->b_cont (if this is a read/write
 * ioctl, the user-supplied buffer at mp->b_cont is reused).  If data is
 * successfully returned, the iocp->ioc_count field should be set with
 * the number of bytes returned.  If an error occurs, the 'ioctl' routine
 * should set iocp->ioc_error to the appropriate error code.  Otherwise,
 * the returned value should be TRUE if a device state change occurred
 * (in which case a signal is sent to the control device, if any) and
 * FALSE if no signal should be sent.
 *
 * int dev_ioctl(v, q, mp, iocp)
 *	aud_state_t	*v;		| Pointer to audio device state
 *	queue_t		*q;		| STREAMS queue pointer
 *	mblk_t		*mp;		| ioctl STREAMS message block
 *	struct iocblk	*iocp;		| M_IOCTL message data
 *
 *
 * The 'start' routine is called to start i/o.  Ordinarily, it is called
 * from the device-specific 'queuecmd' routine, but it is also called
 * when paused output is resumed.
 *
 * void dev_start(v, which)
 *	aud_state_t	*v;		| Pointer to audio device state
 *	enum aud_which	which;		| AUD_PLAY || AUD_REC
 *
 *
 * The 'stop' routine is called to stop i/o.  It is called when i/o is
 * paused, flushed, or the device is closed.  Note that currently queued
 * command blocks should not be flushed by this routine, since i/o may
 * be resumed from the current point.
 *
 * void dev_stop(v, which)
 *	aud_state_t	*v;		| Pointer to audio device state
 *	enum aud_which	which;		| AUD_PLAY || AUD_REC
 *
 *
 * The 'setflag' routine is called to get a single device-specific
 * flag.  The flag argument is either AUD_ACTIVE (return the active flag)
 * or AUD_ERRORRESET (zero the error flag, returning its previous value).
 * (The val argument is currently ignored.)
 *
 * void dev_setflag(v, which, flag, val)
 *	aud_state_t	*v;		| Pointer to audio device state
 *	enum aud_which	which;		| AUD_PLAY || AUD_REC
 *	enum aud_opflag	flag;		| AUD_ACTIVE || AUD_ERRORESET
 *
 *
 * The 'setinfo' routine is called to get or set device-specific fields
 * in the audio state structure.  If ip is NULL, the sample counters and
 * active flags should be set in v.  If ip is not NULL, is points to the
 * audio_info_t structure supplied in an AUDIO_SETINFO ioctl.  All
 * device-specific fields (gains, ports, sample counts) in both v
 * and the device itself should be updated, as long as the corresponding
 * field in ip is not set to AUD_INIT_VALUE.  When the sample counters
 * are set, the value returned in v should be the previous value.
 *
 * void dev_setinfo(v, ip)
 *	aud_state_t	*v;		| Pointer to audio device state
 *	aud_info_t	*ip;		| user info structure or NULL
 *
 *
 * The 'queuecmd' routine is called whenever a new command block is
 * linked into the chained command list.  The device-specific code
 * must ensure that the command is enqueued to the device and that
 * i/o, if not currently active, is started.
 *
 * void dev_queuecmd(v, which, cmdp)
 *	aud_state_t	*v;		| Pointer to audio device state
 *	enum aud_which	which;		| AUD_PLAY || AUD_REC
 *	struct aud_cmd	*cmdp;		| new command block to queue
 *
 *
 * The 'flushcmd' routine is called whenever the chained command list
 * is flushed.  It is only called after i/o has been stopped (via the
 * 'stop' routine) and after the command list in the audio state structure
 * has been cleared.  The device-specific code should flush the device's
 * queued command list.
 *
 * void dev_flushcmd(v, which)
 *	aud_state_t	*v;		| Pointer to audio device state
 *	enum aud_which	which;		| AUD_PLAY || AUD_REC
 */


/* Various generic audio driver constants */
#define	AUD_INITVALUE	(~0)
#define	Modify(X)	((unsigned)(X) != AUD_INITVALUE)
#define	Modifyc(X)	((X) != (unsigned char)AUD_INITVALUE)

#define	SLEEPPRI	((PZERO + 1) | PCATCH)

#ifndef TRUE
#define	TRUE		1
#define	FALSE		0
#endif /*!TRUE*/


/* XXX - for compiling with 4.0.3 releases */
#ifndef _IOC_OUT
#define	_IOC_OUT	IOC_OUT
#define	_IOCPARM_MASK	IOCPARM_MASK
#define	new_kmem_zalloc(size, x)	kmem_zalloc(size)
#endif


/* Define the virtual chained-DMA control structure */
struct aud_cmd {
	unsigned char		*data;	/* address of next transfer */
	unsigned char		*enddata; /* address+1 of last transfer */
	struct aud_cmd		*next;	/* pointer to next or NULL */
	char			skip;	/* if TRUE, no xfers on this buffer */
	char			done;	/* if TRUE, buffer processed */
	caddr_t			private; /* pointer to private data */
};

/* Define the list-head for queued control structures */
struct aud_cmdlist {
	struct aud_cmd		*head;	/* First queued command block */
	struct aud_cmd		*tail;	/* Last queued command block */
	struct aud_cmd		*free;	/* Head of free list */
};

/* Define the ops-vector table for device-specific callouts */
struct aud_ops {
	void			(*close)();	/* device close routine */
	int			(*ioctl)();	/* device ioctl routine */
	void			(*start)();	/* device start routine */
	void			(*stop)();	/* device stop routine */
	unsigned		(*setflag)();	/* read/alter state value */
	int			(*setinfo)();	/* update/alter device info */
	void			(*queuecmd)();	/* add a chained cmd */
	void			(*flushcmd)();	/* flush chained cmd block */
};

/* Define pseudo-routine names for the device-specific callouts */
#define	AUD_CLOSE(V, W)		(*(V)->ops->close)(V, W)
#define	AUD_IOCTL(V, Q, M, I)	(*(V)->ops->ioctl)(V, Q, M, I)
#define	AUD_START(V, W)		(*(V)->ops->start)(V, W)
#define	AUD_STOP(V, W)		(*(V)->ops->stop)(V, W)
#define	AUD_SETFLAG(V, W, F, X)	(*(V)->ops->setflag)(V, W, F, X)
#define	AUD_GETFLAG(V, W, F)	(*(V)->ops->setflag)(V, W, F, AUD_INITVALUE)
#define	AUD_SETINFO(V, I)	(*(V)->ops->setinfo)(V, I)
#define	AUD_GETINFO(V)		(void) (*(V)->ops->setinfo)(V, NULL)
#define	AUD_QUEUECMD(V, W, C)	(*(V)->ops->queuecmd)(V, W, C)
#define	AUD_FLUSHCMD(V, W)	(*(V)->ops->flushcmd)(V, W)

/*
 * Define legal values for the 'which' argument to device-specific callouts.
 * Note that AUD_REC is sometimes tested as a bitfield.
 */
enum aud_which {
	AUD_NONE = 0,
	AUD_REC = 1,
	AUD_PLAY = 2,
	AUD_PLAYREC = 3,	/* AUD_PLAY | AUD_REC */
	AUD_CTL = 4
};

/* Define legal values for the 'flag' argument to the 'setflag' callout */
enum aud_opflag {
	AUD_ACTIVE,		/* active flag */
	AUD_ERRORRESET,		/* error flag (reset after read) */
};



/* This structure describes the state of the audio device and queues */
typedef struct aud_state {
	caddr_t			devdata;	/* device-specific data ptr */
	int			input_size;	/* private record buffer size */
	int			draining;	/* TRUE if output draining */
	audio_info_t		info;		/* state info (see audioio.h) */
	struct aud_ops		*ops;		/* audio ops vector */

	/*
	 * STREAMS routines pass the address of a 'struct audstream' when
	 * calling put and service procedures.  This structure points to
	 * the STREAMS queues and back to the containing 'struct aud_state'.
	 */
	struct aud_stream {
	    enum aud_which	type;	/* which stream is this? */
	    struct aud_state	*v;	/* used when q_ptr is passed */
	    queue_t		*readq;	/* STREAMS read queue */
	    queue_t		*writeq; /* STREAMS write queue */
	}			play,		/* play stream */
				rec,		/* record stream */
				ctl;		/* control stream */

	/* Virtual DMA command support */
	struct aud_cmdlist	playlist;	/* Play command chain */
	struct aud_cmdlist	reclist;	/* Record command chain */
} aud_state_t;


/* Global routines defined in audio.c for use by device-dependent modules */
extern void	audio_flush_cmdlist(/* aud_state_t *v,
	enum aud_which which */);
extern int	audio_open(/* aud_state_t *v, queue_t *q, dev_t dev, flag,
	sflag */);
extern		audio_close(/* queue_t *q, flag */);
extern int	audio_do_setinfo(/* aud_state_t *v, audio_info_t *ip */);
extern		audio_wput(/* queue_t *q, mblk_t *mp */);
extern		audio_wsrv(/* queue_t *q */);
extern void	audio_process_play(/* aud_state_t *v */);
extern		audio_rput(/* queue_t *q, mblk_t *mp */);
extern		audio_rsrv(/* queue_t *q */);
extern void	audio_process_record(/* aud_state_t *v */);
extern void	audio_pause_record(/* aud_state_t *v */);
extern void	audio_pause_play(/* aud_state_t *v */);
extern void	audio_resume_record(/* aud_state_t *v */);
extern void	audio_resume_play(/* aud_state_t *v */);



/* If AUDIOTRACE is defined, include debugging trace definitions */
#ifdef AUDIOTRACE

#define	NAUDIOTRACE 256
struct audiotrace {
	int	count;
	int	function;	/* address of function */
	enum trace_action {
		ATR_APPEND	= 'appC',
		ATR_BEGINCLOSE	= 'cloz',
		ATR_BUSY	= 'busy',
		ATR_CLOSEPLAY	= 'Pclz',
		ATR_CLOSEREC	= 'Rclz',
		ATR_CLOSED	= 'clzd',
		ATR_CLOSEDRAIN	= 'cldr',
		ATR_CMDALLOC	= 'allC',
		ATR_CMDFREE	= 'freC',
		ATR_DELCMD	= 'delC',
		ATR_DONEPLAY	= 'Pfin',
		ATR_DONEREC	= 'Rfin',
		ATR_DRAIN	= 'drai',
		ATR_EOF		= 'eof ',
		ATR_EXITCLOSE	= 'exit',
		ATR_FIRSTPLAY	= 'P1st',
		ATR_FIRSTREC	= 'R1st',
		ATR_FLOWPLAY	= 'P-ER',
		ATR_FLOWREC	= 'R-ER',
		ATR_FLUSH	= 'flsh',
		ATR_IOCTL	= 'ioct',
		ATR_MARK	= 'mark',
		ATR_NEVER	= '!!!!',
		ATR_NEWR	= 'newr',
		ATR_NONE	= '    ',
		ATR_NOTBUSY	= '!bsy',
		ATR_OPENPLAY	= 'Popn',
		ATR_OPENREC	= 'Ropn',
		ATR_OPENED	= 'opnd',
		ATR_OPENFLAG	= 'open',
		ATR_PLAYINTR	= 'pint',
		ATR_PUTRECBUF	= 'putr',
		ATR_RQ		= 'rque',
		ATR_WQ		= 'wque',
		ATR_RECORDINTR	= 'rint',
		ATR_SIGCTL	= 'sigC',
		ATR_SKIPPLAY	= 'P-SK',
		ATR_SKIPREC	= 'R-SK',
		ATR_STARTPLAY	= 'Pgo ',
		ATR_STARTREC	= 'Rgo ',
		ATR_STOP	= 'STOP',
		ATR_STOPPLAY	= 'Pstp',
		ATR_STOPREC	= 'Rstp',
		ATR_WHY		= 'why?',
	}	action;
	int	object;		/* object operated on */
};

struct audiotrace	audiotrace_buffer[NAUDIOTRACE+1];
struct audiotrace	*audiotrace_ptr;
int			audiotrace_count;

#define	ATRACEINIT() {						\
	if (audiotrace_ptr == NULL)				\
		audiotrace_ptr = audiotrace_buffer;		\
	}

#define	ATRACE(func, act, obj) {				\
	int __s = splaudio();					\
	audiotrace_ptr->function = (int)(func);			\
	audiotrace_ptr->object = (int)(obj);			\
	audiotrace_ptr->action = (act);				\
	audiotrace_ptr->count = ++audiotrace_count;		\
	if (audiotrace_ptr >= &audiotrace_buffer[NAUDIOTRACE-1])\
		audiotrace_ptr = audiotrace_buffer;		\
	else							\
		++audiotrace_ptr;				\
	(void) splx(__s);					\
	}

#define	ATRACEPRINT(str)	(void) printf(str)

#else	/*!AUDIOTRACE*/

/* If no tracing, define no-ops */
#define	ATRACEINIT()
#define	ATRACE(a, b, c)
#define	ATRACEPRINT(str)

#endif	/*!AUDIOTRACE*/

#endif /*!_sbusdev_audiovar_h*/
