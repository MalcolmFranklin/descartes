/* @(#) vm_hat.h 1.1@(#) Solbourne id 9/22/93 00:04:35 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*	@(#)vm_hat.h  1.2 90/12/05 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

#ifndef _sun_vm_hat_h
#define	_sun_vm_hat_h

#include <machine/pte.h>
#include <machine/mmu.h>
#include <sys/osmp_lock.h>

/*
 * VM - Hardware Address Translation management.
 *
 * This file describes the contents of the machine specific
 * hat data structures and the machine specific hat procedures.
 * The machine independent interface is described in <vm/hat.h>.
 */

struct ctx {
#ifdef solbourne
	u_short	c_lock: 1;	/* lock bit */
	u_short	c_clean: 1;	/* this ctx has no lines in cache */
	u_short	c_ctx_flush: 1;	/* this ctx must be flushed */
	u_short	: 13;
	u_short	c_ref;		/* vfork ref count */
#else
	u_int	c_lock: 1;	/* lock bit */
	u_int	c_clean: 1;	/* this ctx has no lines in cache */
	u_int	: 30;		/* unused */
#endif /* solbourne */
	struct	ctx *c_next;	/* link when on free list */
#ifndef	refmmu
	struct	pde *c_pdep;	/* ptr to pde array for this context */
#else
	struct	l1pt *c_l1ptp;	/* ptr to level 1 page table for this context */
	int	c_ctxnum;	/* context number for this context */
#endif	refmmu
	struct	as *c_as;	/* back pointer to address space */
};

#ifdef	refmmu
/*
 * Context table definition
 */
struct ctx_table {
	union {
		struct ptp ptp;
		struct pte pte;
	} ptppte[NPTPPERCTXTBL];
};

/*
 * level 1 page table definition
 */
struct l1pt {
	union {
		struct ptp ptp;
		struct pte pte;
	} ptppte[NPTPPERL1PT];
};

/*
 * to facilitate page table allocation/deallocation from the
 * system memory pool, we cluster L2/L3 page tables in PAGESIZE/2
 * chunks.
 */
#define	NPTPERL3CHUNK	((PAGESIZE/2)/PT_L3_SIZE)
#define	NPTEPERL3CHUNK	(NPTPERL3CHUNK*NPTEPERL3PT)
#define	L3_CHUNK_SIZE	(NPTPERL3CHUNK*L3_SEGSIZE)
#define	L3_CHUNK_MASK	(~(L3_CHUNK_SIZE - 1))
#define L3_CINDEX_MASK	0x003ff000	/* mask for Level 3 chunk index */
#define	CHUNKSHIFT	4	/* log2(NPTPERL2CHUNK) */
#define	L3_CHUNK_SHIFT	(L3_INDEX_SHIFT)

/*
 * macros for getting from a virtual address to the proper entry
 * in any level page table cluster
 */
#define L3_CHUNKINDEX(addr) \
	(((unsigned)addr & L3_CINDEX_MASK) >> L3_CHUNK_SHIFT)
#define L3_CHUNKOFFSET(addr)	(L3_CHUNKINDEX(addr) << PTE_SIZE_SHIFT)


/*
 * level 2 page table definition
 */
struct l2pt {
	union {
		struct ptp ptp;
		struct pte pte;
	} ptppte[NPTPPERL2PT];
};

/*
 * level 3 page table definition
 */
struct l3pt {
	struct pte pte[NPTEPERL3CHUNK];
};

#define	L1_PAGE_TABLE	1	/* flag for L1 page table */
#define	L2_PAGE_TABLE	2	/* flag for L2 page table */
#define	L3_PAGE_TABLE	3	/* flag for L3 page table */

#define	TLB_UPAGE_INDEX	0	/* tlb index for wired in upage pte */

#endif	refmmu
/*
 * each page directory entry is associated with a page table.
 * a pde contains the virtual address of the beginning of the hardware 
 * pte array within a page table as well as the pte for mapping this 
 * virtual address.
 *
 * NOTE: a page directory array must begin on a 8192 byte boundary.
 * on Series4 and Series5
 */
#ifdef S4000
struct pde {
	addr_t	pde_pa;			/* pa of beginning of pte array */
	addr_t	pde_va;			/* va of beginning of pte array */
};
#endif S4000
#if	defined(Series4) || defined(Series5)
struct pde {
	addr_t	pde_va;			/* va of beginning of pte array */
	struct	pte pde_pte;		/* pte for mapping previous va */
};
#endif	/* Series4 || Series5 */

/*
 * page table header structure 
 */
struct pt {
	struct	as *pt_as;		/* address space using this pagetable */
	addr_t	pt_base;		/* base virtaddr within address space */
	struct	pt *pt_next;		/* next page table for this as */
	struct	pte_info *pt_data;	/* ptr to pte info for this pt */
	char	pt_flags;		/* flags for this page table */
	char	pt_type;		/* type of pt pointed to */
	u_short	pt_index;		/* index of this pt */
	struct	pt *pt_lower;		/* lower level pg tbls for this dir */
};

/*
 * pt flag definitions
 */
#define	PT_FREE		0x01		/* this page table is free */
#define	PT_ALLOCATED	0x02		/* this page table exists */
#define	PT_LOCKED	0x04		/* this page table locked */

/*
 * one of these structures is linked to the page structure for
 * each valid mapping(pte) for the page.
 */
struct spte {
	u_int		pte_next:20;	/* index of next pt for this page */
	u_int		pte_ix:10;	/* index of next pte for this page */
	u_int		pte_nosync:1;	/* 1 => don't sync this mapping */
	u_int		pte_lock:1;	/* 1 => mapping is locked */
};

/*
 * page table entry information. The information associated with each page 
 * table entry is a hardware pte, and a software pte.
 * NOTE: a page table entry information structure must begin on a 
 * PAGESIZE boundary on Series4/Series5/Series6/Series7.
 *
 */
#ifdef	refmmu
struct pte_info {
	struct	l3pt ptei_pte; /* hardware ptes */
	struct	spte ptei_spte[NPTEPERL3CHUNK]; /* software ptes */
};
#else	!refmmu
struct pte_info {
	struct	pte ptei_pte[NPTEPERPT]; /* hardware ptes */
	struct	spte ptei_spte[NPTEPERPT]; /* software ptes */
};
#endif	refmmu

/*
 * The hat structure is the machine dependent hardware address translation
 * structure kept in the address space structure to show the translation.
 */
enum	hw_fault_info {
	FTYPE_UNKNOWN,		/* type of last fault on this as is unknown */
	FTYPE_INSTRUCTION,	/* last fault on this as was instruction access fault */
	FTYPE_DATA,		/* last fault on this as was data access fault */
};

struct hat {
	struct	ctx *hat_ctx;		/* hardware ctx info */
	struct	pt *hat_pt;		/* page tables belonging to this hat */
	enum	hw_fault_info hat_fi;	/* type of last fault on address space */
};

/*
 * flags to pass to hat_pteload() and segkmem_mapin()
 */
#define	PTELD_LOCK	0x01
#define PTELD_IO	0x02
#define	PTELD_NOSYNC	0x04
#define	PTELD_NOSHOOT	0x08

#ifdef KERNEL
/*
 * These routines are all MACHINE-SPECIFIC interfaces to the hat routines.
 * These routines are called from machine specific places to do the
 * dirty work for things like boot initialization, mapin/mapout and
 * first level fault handling.
 */

#ifdef notdef
/*
 * Boot time pt initialization routines
 */
void	hat_ptinit();

/*
 * Allocate a ctx for the specified as.
 * this includes allocating a page directory table.
 */
void	hat_getctx(/* as */);

/*
 * Called by UNIX during pagefault to insure a context is allocated
 * for this address space. 
 * Also used internally before all operations involving the translation
 * hardware if you need to be in the correct context for the operation.
 * Done inline for performance reasons.
 */
#define hat_setup(x)	{ register struct ctx *ctx = x->a_hat.hat_ctx; \
			  if (ctx->c_pdep == NULL) \
				hat_getpdep(x); \
			  if (ctx->c_pdep != mmu_getpdep()) \
				mmu_setpdep(ctx->c_pdep); \
			}
#endif notdef

/*
 * Load up a particular translation
 */
void	hat_pteload(/* seg, addr, pp, pte, lock */);

/*
 * Convert from mman protections to a protection value to be loaded in a pte
 */
u_int	hat_vtop_prot(/* vprot */);

/*
 * Construct a memory pte using the page pointer and mman protections specified
 */
void	hat_mempte(/* pp, vprot, ppte */);

/*
 * convert a physical address to a virtual address
 */
char *	hat_ptov(/* addr_t */);

#if	defined(Series4) || defined(Series5) || defined(S4000)
extern struct pte_info *pt_invalid;
#endif	Series4 || Series5 || S4000
#ifdef	refmmu
extern struct l3pt *pt_invalid;
#endif	refmmu
#endif KERNEL

#endif /*!_sun_vm_hat_h*/
