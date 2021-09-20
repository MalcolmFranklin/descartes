/* @(#) multicpu.h 1.2@(#) Solbourne id 11/29/93 19:20:12 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

#ifndef _kap_multicpu_h
#define	_kap_multicpu_h
#include <sys/rwlock.h>

/*
 * header file for multi CPU specific defines and data structures
 * by convention the master CPU will be cpu 0.
 */

#ifndef LOCORE
#include <sys/time.h>

struct percpu { /* per cpu specific information and state */
/*  0*/	u_int	pad_head[32];	/* Pad front 128 bytes (mxcc) */
/* 80*/	struct	proc *idlep;	/* idle process for this cpu */
/* 84*/	u_char	slot;		/* slot this cpu is in */
/* 85*/	u_char	enabled;	/* set if this cpu is enabled */
/* 86*/	u_char	running;	/* set if this cpu is running */
/* 87*/	u_char	idle;		/* set if this cpu is idle */
/* 88*/	u_int	tick_count;	/* number of clock ticks to this cpu */
/* 8c*/	struct	ctx *sctx;	/* slave context pointer */
/* 90*/	u_int	command;	/* cmd to slave from master, sent via intr */
/* 94*/	u_int	arg1;		/* command argument */
/* 98*/	u_int	arg2;		/* command argument */
/* 9c*/	u_int	missed_ticks_u;	/* count of unrelayed clock ticks */
/* a0*/	u_char	usermode;	/* set if this cpu is in user mode */
/* a1*/	u_char	nocharge;	/* don't charge for clock tick (unused) */
/* a2*/	u_char	dotraceback;	/* perform a traceback (see halt_cpu()) */
/* a4*/	u_int	nmi_regs;	/* pointer to nmi reg structure */
#if NCPUS > 1
/* a8*/	struct	simple_lock *locklist; /* locks held by this cpu */
#else
/* a8*/	int	*unused;	/* satisfy feed compler for idt */
#endif
/* ac*/	struct	proc *exitproc;	/* exiting process on this cpu */
/* b0*/	u_int	missed_ticks_s;	/* count of unrelayed clock ticks */

			/* Floating point on traps */
/* b4*/	struct regs *fptraprp;	/* floating point trap reg pointer [syncfpu] */
/* b8*/	u_int	fsrholder;	/* holding spot for fsr [syncfpu] */
/* bc*/	u_int	fsrsave;	/* save the fsr for later [sys_rtt] */
/* c0*/	u_int	f0save;		/* save spot for %f0 [sys_rtt] */
/* c4*/	u_int	fzero;		/* copy of 0.0 [sys_rtt] */

			/* Statistics gathering */
/* c8*/	u_int	swtch_cnt;	/* context switches [vmmeter] */
/* cc*/	u_int	trap_cnt;	/* calls to trap [vmmeter] */
/* d0*/	u_int	syscall_cnt;	/* syscall count [vmmeter] */
/* d4*/	u_int	intr_cnt;	/* device interrupts [vmmeter] */
/* d8*/	u_int	pgin_cnt;	/* pageins [vmmeter] */
/* dc*/	u_int	pgout_cnt;	/* pageouts [vmmeter] */
/* e0*/	u_int	pgpgin_cnt;	/* pages paged in [vmmeter] */
/* e4*/	u_int	pgpgout_cnt;	/* pages paged out [vmmeter] */
/* e8*/	u_int	intrans_cnt;	/* in-transit blocking page faults [vmmeter] */
/* ec*/	u_int	pgrec_cnt;	/* total page reclaims [vmmeter] */
/* f0*/	u_int	xsfrec_cnt;	/* reclaimed freelist not swapdev [vmmeter] */
/* f4*/	u_int	xifrec_cnt;	/* reclaimed freelist not filesys [vmmeter] */
/* f8*/	u_int	zfod_cnt;	/* pages zero filled on demand [vmmeter] */
/* fc*/	u_int	pgfrec_cnt;	/* page reclaims from free list [vmmeter] */
/*100*/	u_int	faults_cnt;	/* total page faults taken [vmmeter] */
/*104*/	u_int	scan_cnt;	/* page examinations in pageout [vmmeter] */
/*108*/	u_int	rev_cnt;	/* revolutions of pageout hand [vmmeter] */
/*10c*/	u_int	dfree_cnt;	/* pages freed by pageout [vmmeter] */
/*110*/	u_int	swtch_phit_cnt;	/* hits [vmmeter] */
/*114*/	u_int	swtch_pmiss_cnt;/* misses [vmmeter] */
/*118*/	u_int	reffaults_cnt;	/* page faults to set ref bit [vmmeter] */
/*11c*/	u_int	modfaults_cnt;	/* page faults to set mod bit [vmmeter] */
/*120*/	u_int	iswtch_cnt;	/* idle switches per cpu [vmmeter] */
/*124*/	u_int	fswtch_cnt;	/* fast context switches [vmmeter] */

			/* Scheduling & Miscellaneous */
/*128*/	int	curpri;		/* current priority */
/*12c*/	u_int	runrun;		/* flag to get a resched */
/*130*/	u_int	softint;	/* flag saying this cpu is running softints */
/*134*/	u_int	noproc;		/* flag saying there's no process on this cpu */
/*138*/	u_int	whichqs;	/* flags saying qs have runnable procs */
/*13c*/	u_int	kidipr;		/* shadow copy of the IPR board register */
/*140*/	u_int	cachecount;	/* counter of when to merge cache info */
/*144*/	u_int	usingcaddr2;	/* used in paging code to detect problems */
/*148*/	u_int	wantcaddr2;	/* used in paging code to signal desire */

			/* led information (dont re-order) */
/*14c*/	u_short	leds;		/* led value */
/*14e*/	u_char	led_ptr;	/* clock tick led pattern pointer */
/*14f*/	u_char	led_ticks;	/* clock tick ticks */

/*150*/	u_int	pam_affinity_balance;

/*154*/	struct timeval	last;	/* used by uniqtime */

			/* Future expansion (pad to even pow of 2) */
/*15c*/	u_int	extras[137];
/*380*/	u_int	pad_tail[32];	/* Pad end 128 bytes (mxcc) */
};
extern struct	percpu cpu_specific[];
#ifndef S4000
extern int	slottocpu[];	/* converts slot number to CPU number */
extern int	slaves_started;	/* slaves started flag */
extern int	slot_number();	/* returns slot number of this CPU */
extern u_char	read_dg_ram();	/* read a byte from dg ram */
#endif
extern int	ncpus;		/* number of good cpus */

#ifdef notdef
extern int	cpu_number();	/* returns number of this CPU */
#endif notdef
#endif LOCORE

#if	defined(Series6) || defined(Series7)
#define	CPUNUM_DG_LOC	0	/* address in DG RAM of cpu number */
#endif Series6 || Series7
#ifdef Series5
#define	CPUNUM_DG_LOC	4	/* address in DG RAM of cpu number */
#endif Series5
#ifdef Series4
#define	CPUNUM_DG_LOC	8	/* address in DG RAM of cpu number */
#endif Series4

#define	NO_CPU		255	/* no cpu has this number */
#define	MASTER_CPU	0	/* number of master CPU */

#define	RELEASE_SLEEP_LOCK	0x01	/* multi_swtch should release sleep lock */

/*
 * commands sent between cpus
 *
 * source cpu places a command in the command field of the percpu 
 *	structure of the destination cpu
 * source cpu sends a directed interrupt to the destination cpu
 * destination cpu receives interrupt 
 * destination cpu performs the specified function
 * destination cpu clears the command field of its percpu structure
 * source cpu can wait for an acknowledgement from the destination cpu
 *	by waiting for the command field to clear
 */
#define MSCMD_TLBINVAL	1
#define MSCMD_SCHED	2
#define MSCMD_SHOOTCTX	3

#ifndef LOCORE
/*
 * lock structure that allows the same cpu to lock multiple times
 * but prevents other cpus from accessing when a different cpu is 
 * holding the lock.
 */
struct rlock { /* lock that can be recursively locked */
	u_char	interlock;	/* interlock on lock structure */
	u_char	holder;		/* current cpu holding lock */
	u_short	holdcount;	/* count of recursive locks */
};
#endif LOCORE

#if !defined(LOCORE) && !defined(S4000)
extern void	simple_lock_init(/* slock_t, int, char * */); /* init a lock */
#endif LOCORE

#ifdef LOCORE
/*
 * Define assembly language macro to get current cpu number
 *
 * We use u_area value where possible for efficiency
 *
 * NOTE: CPU_NUMBER macro is called in branch delay slots,
 * 	so it must not be more than one instruction
 * NOTE: CPU_NUMBER_ macro uses DG RAM to return the cpu number.
 *	it can be called when there is not a valid uarea.
 */

#if NCPUS > 1
#define	CPU_NUMBER(reg)				\
	ld	[_u+U_CPUNUM],reg
#if	defined(Series4) || defined(Series5)
#define	CPU_NUMBER_(reg)			\
	set	CPUNUM_DG_LOC,reg;		\
	lduba	[reg]ASI_DIAG_RAM,reg
#endif	Series4 || Series5
#if	defined(Series6) || defined(Series7)
#define	CPU_NUMBER_(reg)			\
	set	KID_DGRAM+CPUNUM_DG_LOC,reg;	\
	lda	[reg]ASI_KBUS_ID,reg
#endif	Series6 || Series7
#else NCPUS > 1
#define	CPU_NUMBER(reg)				\
	mov	%g0,reg
#define	CPU_NUMBER_(reg)			\
	mov	%g0,reg
#endif NCPUS > 1
/*
 * since our old sun assemblers don't know the stbar instruction
 * we define it by hand here
 */
#define	STBAR	.word	0x8143c000
#endif LOCORE
#endif _kap_multicpu_h
