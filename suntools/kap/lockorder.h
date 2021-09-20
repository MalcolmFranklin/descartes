/* @(#) lockorder.h 1.3@(#) Solbourne id 11/29/93 19:19:56 */

#ifndef lockorder_h
#define	lockorder_h

/*
 * This file defines the lock ordering in the kernel
 * Each lock has an order number field, which should be
 * set by calling init_lock with the proper order number for the lock
 * and the name of the lock.
 * When a lock is taken, the lock acquisition code will check the
 * lock to ensure that the order number has been set.  It will
 * also check that no locks have already been taken on this
 * CPU with an equal or higher order number.  If they have, the kernel
 * will panic.
 * The ordering below is derived from a partial ordering of the
 * kernel locks.  Any lock that may not be acquired if a specific other
 * lock is held must have a lower order number than the other lock.
 * If two locks have no order relationship then they may share
 * an order number, if they have the same relationship to all 
 * lower order numbered locks.  In fact they should share the
 * order number because if a CPU then tries to take both locks
 * The kernel will detect that they do in fact have an order
 * relationship and panic.
 * NOTE: The partial ordering must generate a valid lock ordering.
 * If you end up with conflicting lock orders your code is wrong.
 * GENERAL RULE: If you know an order dependency for a lock then
 * assign it to the next higher available order number.  If a lock
 * has several order dependencies make order number higher than the
 * highest dependent lock.
 */

#ifdef	SMP_TEST
/*
 * USER_SYNC lock (user_sync_locks[]) dependencies:
 */
#define	USER_SYNC_LOCK_ORDER		100
#endif	SMP_TEST

/*
 * SEMAPHORE lock (sem_lock) dependencies:
 * < VM_CONTEXT
 * > RMAP_LOCK_ORDER
 */
#define SEM_LOCK_ORDER			500

/*
 * Socket lock (socket->so_lock) dependencies:
 * < VM_CONTEXT (Taken during syscalls)
 */
#define	SOCKET_LOCK_ORDER		600
#define	SOCKET_LOCK_ORDER_CLIENT	600
#define	SOCKET_LOCK_ORDER_SERVER	601
#define	SOCKET_LOCK_ORDER_ACCEPTOR 	602
#define	SOCKET_LOCK_ORDER_NEW	 	603

/*
 * Network Domain lock (domain_lock) dependencies:
 * < VM_CONTEXT (Taken during syscalls)
 * We make it just higher than socket locks because we can interupt them,
 * but they cannot interupt us.
 */
#define	DOMAIN_LOCK_ORDER		900

/*
 * VM context lock (vm_context_lock) dependencies:
 */
#define	VM_CONTEXT_LOCK_ORDER		1000

#ifdef	SMP_TEST
/*
 * PAM MODE lock (pam_mode_lock) dependencies:
 */
#define	PAM_MODE_LOCK_ORDER		1002
#endif	SMP_TEST

/*
 * VFORK lock (vfork_lock) dependencies:
 * > VM_CONTEXT (taken for fork)
 * < PROCESS_LOCK (taken during sleep)
 * < SLEEP_LOCK (taken during sleep)
 */
#define	VFORK_LOCK_ORDER		1200

/*
 * CREDENTIALS lock (cred_lock) dependencies:
 * > VM_CONTEXT (Taken during syscalls)
 */
#define	CRED_LOCK_ORDER			2500

/*
 * CWD lock (cwd_lock) dependencies:
 * > VM_CONTEXT taken from interrrups
 */
#define	CWD_LOCK_ORDER			2500

/*
 * FILE table (file_table_lock) lock dependencies: 
 * > VM_CONTEXT (Taken during syscalls)
 * > SOCKET (unp_gc)
 */
#define	FILE_TABLE_LOCK_ORDER		2600

#ifdef LKSTAT
/*
 * LKSTAT_LOCK_ORDER lock (lkstat_hashq_lock) dependencies:
 * Since it is called from simple_lock_init it is assumed that 
 * VM_CONTEXT_LOCK is held
 * > SOCKET (held while initialising another socket lock).
 */
#define LKSTAT_LOCK_ORDER          	2700
#define LKDRV_LOCK_ORDER           	2800
#endif

/*
 * PACKAGE lock (scsi, ipi controllers) dependencies:
 */
#define	PACKAGE_LOCK_ORDER		3700

/*
 * PHYSIO lock (physio_lock) dependencies:
 * > PACKAGE (Taken during syscall threads)
 */
#define	PHYSIO_LOCK_ORDER		3800

/*
 * Event count and sequencer lock (evcnt_lock, sequencer lock) dependencies:
 * > VM_CONTEXT (taken during syscalls)
 * > PACKAGE (taken during disk intrs)
 * < PROCESS_LOCK (taken during sleep)
 * < SLEEP_LOCK (taken during sleep)
 */
#define EVCNT_LOCK_ORDER		3900
#define SEQUENCER_LOCK_ORDER		3950

/*
 * INT_LEVEL_3 lock (zs_soft_lock, eg_lock, ei_lock, ex_lock) dependencies:
 */
#define	INT_LEVEL_3_LOCK_ORDER		5000

/*
 * KBD lock (kbd_lock) dependencies:
 * > INT_LEVEL_3 (Taken during zs softint interrupt threads)
 */
#define	KBD_LOCK_ORDER			5100

/*
 * IF lock (if_lock) dependencies:
 * > INT_LEVEL_3 (Taken during network interrupt threads)
 */
#define	IF_LOCK_ORDER			5100

/*
 * Arp lock (arp_lock) dependencies:
 * > VM_CONTEXT_LOCK (Taken from STREAMS calls and during init)
 * > DOMAIN_LOCK (Taken during socket operations)
 * > INT_LEVEL_3 (Taken during interrupt threads)
 * Used to protect all arp table operations
 */
#define	ARP_LOCK_ORDER			5100

/*
 * IF chain lock (ifchain_lock) dependencies:
 * > VM_CONTEXT_LOCK (Taken from STREAMS calls and during init)
 * > DOMAIN_LOCK (Taken during socket operations)
 * > ARP_LOCK (taken during arp operations)
 * Used in net/if.c for those operations which run down the interface
 * chain.
 */
#define	IFCHAIN_LOCK_ORDER		5150

/*
 * MBUF lock (mbuf_lock) dependencies:
 * > IF (Taken during ip packet processing)
 * > SOCKET sbdrop()
 */
#define	MBUF_LOCK_ORDER			5200

/*
 * CKU_BUF lock (cku_buf_lock) dependencies:
 * > MBUF (Taken during mbuf frees with mbuf lock held)
 */
#define	CKU_BUF_LOCK_ORDER		5300

/*
 * UDP_DATA lock (udp_data_lock) dependencies:
 * > MBUF (Taken during network interrupt threads)
 */
#define	UDP_DATA_LOCK_ORDER		5300

/*
 * NFS RROKINFO lock (rrokinfo_lock) dependencies:
 * used by nfs
 */
#define NFS_RROKINFO_LOCK_ORDER		5300

/*
 * kudp dup cache lock (ku_dup_lock) dependencies:
 * < HEAP_LOCK (can do kmem_alloc)
 * used by nfs
 */
#define KU_DUP_LOCK_ORDER		5300

/*
 * RFS GET lock (rfsget_lock) dependencies:
 * < HEAP_LOCK (can do kmem_alloc)
 * used by nfs
 */
#define RFSGET_LOCK_ORDER		5300

/*
 * rfs export lock (rfs_export_lock) dependencies:
 * > VM_CONTEXT (Taken during syscalls)
 * < PROCESS LOCK (calls wakeup)
 * < sleep lock (calls wakeup)
 * used by nfs
 */
#define RFS_EXPORT_LOCK_ORDER		5300

/*
 * INT_LEVEL_4 lock (mbq_lock, cg4_lock, cg2_lock) dependencies:
 * > INT_LEVEL_3 (Taken during higher interrupt threads)
 */
#define	INT_LEVEL_4_LOCK_ORDER		6000

/*
 * INT_LEVEL_5 lock (zs_lock) dependencies:
 * > INT_LEVEL_4 (Taken during higher interrupt threads)
 */
#define	INT_LEVEL_5_LOCK_ORDER		7000

/*
 * ALLPROC lock (allproc_lock) dependencies:
 * > INT_LEVEL_5 (Taken during interrupt threads)
 * > SOCKET (sbwakeup)
 */
#define	ALLPROC_LOCK_ORDER		7500

/*
 * POLL lock (poll_lock) dependencies:
 * < SELECT (strwakeup)
 */
#define	POLL_LOCK_ORDER			7600

/*
 * SELECT lock (select_lock) dependencies:
 * > VM_CONTEXT potentially held
 * > Interrupt potentially held
 * > will acquire process lock
 * > SOCKET (sbwakeup)
 * > POLL (strwakeup)
 */
#define SELECT_LOCK_ORDER		7700

/*
 * VM_CONTEXT_QUEUE lock (vm_context_queue) ddependencies:
 * > VM_CONTEXT (Taken during drop vm_context)
 * > all device generated interrupts (may grab/drop vm_context in these)
 */
#define	VM_CONTEXT_QUEUE_LOCK_ORDER	7800

/*
 * FAST_HEAP lock (fast_heap_lock) dependencies:
 * > VM_CONTEXT (Taken during syscalls)
 * > INT_LEVEL_5 (Taken in zs interrupt threads)
 */
#define	FAST_HEAP_LOCK_ORDER		8000

/*
 * HEAP lock (heap_lock) dependencies:
 * > VM_CONTEXT (Taken during syscalls)
 * > INT_LEVEL_5 (Taken in zs interrupt threads)
 */
#define	HEAP_LOCK_ORDER			8000

/*
 * VME_IACK lock (vme_lock_array[]) dependencies:
 * > INT_LEVEL5	(Taken in VME interrupt threads)
 */
#define	VME_IACK_LOCK_ORDER		8000

/*
 * RW SIMPLE lock (lp->lock) dependencies:
 * This is lock which protects the fields within the 
 * READER_WRITER_LOCK
 */
#define RW_SIMPLE_LOCK_ORDER		8000

/*
 * RMAP lock (rmap_lock) dependencies:
 * > HEAP_LOCK_ORDER for RECORD_USAGE kmem_alloc
 * > VM_CONTEXT (Taken during interrupt threads)
 * > MBUF (Taken allocating more mbufs while mbuf lock held)
 */
#define	RMAP_LOCK_ORDER			8050

/*
 * PROCESS lock (process->p_lock) dependencies:
 * > VM_CONTEXT (Taken during kernel faults)
 * > PROCESS p - 1 (have range that allows 2000 processes)
 * > SOCKET (sowakeup)
 */
#define	PROCESS_LOCK_ORDER		8100
#define PROCESS_LOCK_ORDER_MAX	(SLEEP_LOCK_ORDER-1)

/*
 * THREAD SLEEP lock (th_sleep_lock) dependencies:
 */
#define	TH_SLEEP_LOCK_ORDER		10200

/*
 * SLEEP lock (sleep_locks[]) dependencies:
 * > VM_CONTEXT 	(Taken during interrupt threads while vm_context held)
 * > PACKAGE		(Taken in package interrupt threads)
 * > PROCESS		(Taken in wakeup while process lock held)
 * > SOCKET 		sbwait()
 * > TH_SLEEP_LOCK	(Taken in sleep_and_unlock after th_sleep_lock)
 */
#define	SLEEP_LOCK_ORDER		10300

/*
 * HAT lock (hat_lock) dependencies:
 * > VM_CONTEXT (Taken during kernel faults on almost any thread)
 * > HEAP	(Taken during kernel faults on almost any thread)
 * > INT_LEVEL_5 (Taken during kernel faults on interrupt threads)
 */
#define	HAT_LOCK_ORDER			11000

/*
 * RUNQ lock (runq_lock) dependencies:
 * > VM_CONTEXT (Taken during many threads while vm_context held)
 * > PACKAGE	(Taken in package interrupt threads)
 * > HEAP	(Taken during kernel heap growing code)
 */
#define	RUNQ_LOCK_ORDER			11000

/*
 * CALLOUT lock (callout_lock) dependencies:
 * > VM_CONTEXT (Taken during syscalls)
 * > PACKAGE	(Taken in package interrupt threads)
 * > CKU_BUF	(Taken in hardclock interrupt threads)
 * > HAT	(Taken in hardclock interrupt threads)
 */
#define	CALLOUT_LOCK_ORDER		11100

/*
 * SOFTCALL lock (softcall_lock) dependencies:
 * > INT_LEVEL5 (Taken during hardclock processing)
 * > all other locks (Taken during kernel printfs to streams)
 */
#define	SOFTCALL_LOCK_ORDER		11200

/*
 * UNIQ_TIME lock (uniqtime_lock) dependencies:
 * >taken at anytime with interrupts blocking all devices
 */
#define UNIQ_TIME_LOCK_ORDER		11400

/*
 * RW_HASH lock (rw_hlck) dependencies:
 * taken anytime any reader/writer locking function is called
 */
#define RW_HASH_LOCK_ORDER		11600

/*
 * IOM_DVMA lock (iom_dvma_lock) dependencies:
 * > almost everything. Held to synchronize hardware dvma map opperations
 */
#define	IOM_DVMA_LOCK_ORDER		11800

/*
 * LOCK SPIN lock (lock_spin_lock) dependencies:
 */
#define	LOCK_SPIN_LOCK_ORDER		11600

/*
 * SIMPLE_PRINT lock (simple_print_lock) dependencies:
 * > all other locks (May need to print at almost any time)
 */
#define	SIMPLE_PRINT_LOCK_ORDER		12000

/*
 * TRACE lock (trace_lock) dependencies:
 * > all other locks (May need to print at almost any time)
 */
#define	TRACE_LOCK_ORDER		20000

#endif lockorder_h
