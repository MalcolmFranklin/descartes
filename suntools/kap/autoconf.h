/* @(#) autoconf.h 1.1@(#) Solbourne id 9/22/93 00:02:58 */
/*
 * Copyright 1988-1991 Solbourne Computer, Inc.
 * All rights reserved.
 */

/* @(#)autoconf.h 1.3 90/12/05 SMI */

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

#ifndef _sun_autoconf_h
#define	_sun_autoconf_h

#ifdef	solbourne
/* VMEbus address modifier values: composed of a size, privilege, and a space */
#define	VME_AM_AMSK		0x38		/* size */
#define	VME_AM_A16		0x28
#define	VME_AM_A24		0x38
#define	VME_AM_A32		0x08
#define	VME_AM_PMSK		0x04		/* privilege */
#define	VME_AM_SUPERVISORY	0x04
#define	VME_AM_NON_PRIVILEGED	0x00
#define	VME_AM_SMSK		0x03		/* space */
#define	VME_AM_BLOCK_TRANSFER	0x03
#define	VME_AM_PROGRAM_ACCESS	0x02
#define	VME_AM_DATA_ACCESS	0x01

#define	VME_AM(size, priv, space)	\
	(VME_AM_/**/size|VME_AM_/**/priv|VME_AM_/**/space)
/* EXAMPLE: VME_AM(STANDARD,NON_PRIVILEDGED,BLOCK_TRANSFER) */
#endif	solbourne

/*
 * Defines for bus types.  These are magic cookies passed between config
 * and the kernel to tell what bus each device is on.
 */
#define	SP_BUSMASK	0x0000FFFF	/* mask for bus type */
#ifdef	solbourne
#define SP_VIRTUAL	0x8000		/* virtual address */
/*#define	SP_OB		0x4000	/* FIXME ... onboard address */
#define SP_SBUS		0x4000		/* SBUS address */
#define	SP_OB		SP_KB		/* KLUDGE for now ...onboard address */
#define	SP_KB		0x2000		/* kbus address */
#define	SP_VME		0x1000		/* vme address */
#define	SP_MB		0x0800		/* multibus address */
#define SP_MEMMASK	0xF800		/* mask for memory type only */
#define SP_OBMEM	(SP_OB|0x0001)	/* on board memory */
#define SP_OBIO		(SP_OB|0x0002)	/* on board i/o */
#define SP_KBMEM	(SP_KB|0x0001)	/* kbus memory */
#define SP_KBIO		(SP_KB|0x0002)	/* kbus i/o */
#define SP_KBSLOT	(SP_KB|0x0003)	/* kbus i/o (id region) */
#define	SP_VME_A16	VME_AM(A16,SUPERVISORY,DATA_ACCESS)
#define	SP_VME_A24	VME_AM(A24,SUPERVISORY,DATA_ACCESS)
#define	SP_VME_A32	VME_AM(A32,SUPERVISORY,DATA_ACCESS)
#define	SP_VME_A16_BLK	VME_AM(A16,SUPERVISORY,BLOCK_TRANSFER)
#define	SP_VME_A24_BLK	VME_AM(A24,SUPERVISORY,BLOCK_TRANSFER)
#define	SP_VME_A32_BLK	VME_AM(A32,SUPERVISORY,BLOCK_TRANSFER)
#define	SP_VME_AMMSK	0x003F		/* address modifier mask */
#define SP_VME_D8	0x0000		/* vme data width */
#define SP_VME_D16	0x0100
#define SP_VME_D32	0x0200
#define SP_VME_DMSK	0x0300
#define SP_VME16D16	(SP_VME|SP_VME_A16|SP_VME_D16)
#define SP_VME24D16	(SP_VME|SP_VME_A24|SP_VME_D16)
#define SP_VME32D16	(SP_VME|SP_VME_A32|SP_VME_D16)
#define SP_VME16D32	(SP_VME|SP_VME_A16|SP_VME_D32)
#define SP_VME24D32	(SP_VME|SP_VME_A24|SP_VME_D32)
#define SP_VME32D32	(SP_VME|SP_VME_A32|SP_VME_D32)
#define SP_VME16D16_BLK	(SP_VME|SP_VME_A16_BLK|SP_VME_D16)
#define SP_VME24D16_BLK	(SP_VME|SP_VME_A24_BLK|SP_VME_D16)
#define SP_VME32D16_BLK	(SP_VME|SP_VME_A32_BLK|SP_VME_D16)
#define SP_VME16D32_BLK	(SP_VME|SP_VME_A16_BLK|SP_VME_D32)
#define SP_VME24D32_BLK	(SP_VME|SP_VME_A24_BLK|SP_VME_D32)
#define SP_VME32D32_BLK	(SP_VME|SP_VME_A32_BLK|SP_VME_D32)
#define SP_MBMEM	(SP_OB|0x0001)	/* (history) on board memory */
#define SP_MBIO		(SP_OB|0x0002)	/* (history) on board i/o */
#else	!solbourne
#define	SP_VIRTUAL	0x0001		/* virtual address */
#define	SP_OBMEM	0x0002		/* on board memory */
#define	SP_OBIO		0x0004		/* on board i/o */
#define	SP_MBMEM	0x0010		/* multibus memory (sun2 only) */
#define	SP_MBIO		0x0020		/* multibus i/o (sun2 only) */
#define	SP_ATMEM	0x0040		/* atbus memory (sun386 only) */
#define	SP_ATIO		0x0080		/* atbus i/o (sun386 only) */
#define	SP_VME16D16	0x0100		/* vme 16/16 */
#define	SP_VME24D16	0x0200		/* vme 24/16 */
#define	SP_VME32D16	0x0400		/* vme 32/16 (sun3 only) */
#define	SP_VME16D32	0x1000		/* vme 16/32 (sun3 only) */
#define	SP_VME24D32	0x2000		/* vme 24/32 (sun3 only) */
#define	SP_VME32D32	0x4000		/* vme 32/32 (sun3 only) */
#define	SP_IPI		0x8000		/* IPI channel address */
#endif	!solbourne

/*
 * Defines for encoding the machine type in the space field of
 * each device.
 */
#define	SP_MACHMASK	0xFFFF0000	/* space mask for machine type */
#define	MAKE_MACH(m)	((m)<<16)
#define	SP_MACH_ALL	MAKE_MACH(0)	/* 0 implies all machines */

#ifdef OPENPROMS

/*
 * OPENPROM autoconfiguration goodies
 * These structures are NOT exported to the world!
 * They are defined here ONLY as a service to device driver writers
 * who would prefer to create (at least some of) the
 * PROM internal structures in C.
 */

/*
 * As far as the external world (clients of the ROMvec) is concerned,
 * device nodes are "magic cookies" of type "int".  We assume here that
 * an int is capable of representing an opaque pointer.
 */
typedef struct dev_element {
	struct dev_element *next;
	struct dev_element *slaves;
	struct property *props;
} devnode_t;

struct property {
	char *name;
	int size;
	caddr_t value;
};

#define	SPO_VIRTUAL	-1	/* virtual address (not used?) */

/*
 * Other legal values are OBMEM and OBIO from machine/pte.h, because
 * the space identifier is identical to the "type" bits from the MMU.
 * The space identifier should be thought of as simply some extra
 * physical address bits.
 */

/*
 * These are service routines in openprom_util.c
 */
struct dev_info *path_to_devi(/* char *path */);
int get_part_from_path(/* char *path */);
u_int atou(/* char *s */);
int (*path_getdecodefunc(/* struct devinfo *dip */))();
char *(*path_getencodefunc(/* struct devinfo *dip */))();
int (*path_getmatchfunc(/* struct devinfo *dip */))();

/*
 * Structures and service routines from machine/openprom_xxx.c.
 */
struct dev_path_ops {
	char *devp_name;		/* driver name */
	int (*devp_decode_regprop)();	/* decode reg property to reg struct */
	char *(*devp_encode_reg)();	/* encode reg struct to address */
	int (*devp_match_addr)();	/* does this node match this address? */
};

extern struct dev_path_ops dev_path_opstab[];
int obio_decode_regprop(/* struct dev_info *dip, int nodeid */);
char *obio_encode_reg(/* struct dev_info *dip, char *addrspec */);
int obio_match(/* struct dev_info *dip, char *addrspec */);

#endif OPENPROMS

#ifdef i386

/* maximum number of interrupt request channels (irq's) */
#ifdef SUN386
#define	NVECT	24
#else  SUN386
#define	NVECT	72
#endif SUN386

#else  i386

/* maximum number of autovectored interrupts at a given priority */
#define	NVECT	10

#endif i386

#ifdef solbourne
#ifndef LOCORE
extern addr_t mapioaddr( /* addr, space, nbytes */ );
#endif !LOCORE
#endif solbourne

/*
 * An array of these structures will replace the three "levelN_*" arrays
 * used by older architectures.
 */
struct autovec {
	int (*av_vector)();	/* interrupt handler */
	int av_intcnt;		/* interrupt counter */
	char *av_name;		/* pointer to driver name */
	int av_devcnt;		/* number of devices driver handles */
};

#if	defined(sun4c) || defined(twin)
#if defined(KERNEL)
/*
 * These are service routines in autoconf.c that device drivers
 * can call.
 */

addr_t map_regs(/* (addr_t)addr, (u_int)size, (int)space */);
void unmap_regs(/* (addr_t)addr, (u_int)size */);
int walk_devs(/* (struct dev_info *)dev_info, (int (*)())f, (caddr_t)arg */);
void report_dev(/* (struct dev_info) dev */);

#endif kernel
#endif /*defined(sun4c) || defined(twin)*/

#endif /*!_sun_autoconf_h*/

