/* @(#) cg6reg.h 1.1@(#) Solbourne id 9/22/93 00:05:25 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/* @(#)cg6reg.h	1.2 89/08/03 SMI */

/*
 * Copyright 1983, 1987 by Sun Microsystems, Inc.
 */

#ifndef	cg6reg_DEFINED
#define	cg6reg_DEFINED

#include <sys/param.h>

/*
 * CG6 frame buffer hardware definitions.
 */


/* Physical frame buffer and color map addresses */
/*
 * The base address is defined in the configuration file, e.g. GENERIC.
 * These constants are the offset from that address.
 *
 * For sun3, the base address is 	0xFF000000
 * For sun4, it is			0xFB000000
 */

#ifdef sparc
#define CG6_P4BASE		0xFB000000
#else
#define CG6_P4BASE		0xFF000000
#endif

#define CG6_ADDR_CMAP		0x200000
#define CG6_ADDR_FBC		0x700000
#define	CG6_ADDR_TEC		0x701000
#define CG6_ADDR_P4REG		0x300000
#define CG6_ADDR_ROM		0x380000
#define CG6_ADDR_OVERLAY	0x400000	/* FAKE */
#define CG6_ADDR_FHC		0x300000
#define CG6_ADDR_THC		0x301000
#define CG6_ADDR_ENABLE		0x600000
#define CG6_ADDR_COLOR		0x800000

#define CG6_ADDR_FBCTEC		CG6_ADDR_FBC
#define CG6_ADDR_FHCTHC		CG6_ADDR_FHC	

#define CG6_CMAP_SZ		ctob(1)
#define CG6_FBCTEC_SZ		ctob(1)
#define CG6_FBC_SZ		ctob(1)		/* a relic of 1.0 CG6 */
#define CG6_TEC_SZ		ctob(1)		/* a relic of 1.0 CG6 */
#define CG6_FHCTHC_SZ		ctob(1)
#define CG6_FHC_SZ		ctob(1)		/* a relic of 1.0 CG6 */
#define CG6_THC_SZ		ctob(1)		/* a relic of 1.0 CG6 */
#define CG6_ROM_SZ		ctob(8)
#define CG6_FB_SZ		(1024*1024)

/*
 * Offsets of TEC/FHC into page
 */
#define CG6_TEC_POFF		0x1000
#define CG6_THC_POFF		0x1000

/*
 * Virtual (mmap offsets) addresses
 */ 
#define CG6_VBASE		0x70000000
#define CG6_VADDR(x)		(CG6_VBASE+ctob(x))

/*
 * CG6 Virtual object addresses
 */
#define CG6_VADDR_FBC		CG6_VADDR(0)
#define	CG6_VADDR_TEC		(CG6_VADDR_FBC + CG6_TEC_POFF)
#define CG6_VADDR_CMAP		CG6_VADDR(1)
#define CG6_VADDR_FHC		CG6_VADDR(2)
#define CG6_VADDR_THC		(CG6_VADDR_FHC + CG6_THC_POFF)
#define CG6_VADDR_ROM		CG6_VADDR(3)
#define CG6_VADDR_COLOR		CG6_VADDR(3+btoc(CG6_ROM_SZ))

#define CG6_VADDR_FBCTEC	CG6_VADDR_FBC
#define CG6_VADDR_FHCTHC	CG6_VADDR_FHC
/*
 * to map in all of lego, use mmapsize below, and offset CG6_VBASE
 */
#define MMAPSIZE(dfbsize)	(CG6_VADDR_COLOR-CG6_VBASE+dfbsize)

/*
 * convert from address returned by pr_makefromfd (eg. mmap) 
 * to CG6 register set.
 */
#define CG6VA_TO_FBC(base) \
	((struct fbc*)  (((char*)base)+(CG6_VADDR_FBC-CG6_VBASE)))
#define CG6VA_TO_TEC(base)  \
	((struct tec*)  (((char*)base)+(CG6_VADDR_TEC-CG6_VBASE)))
#define CG6VA_TO_FHC(base)  \
	((u_int*) 	(((char*)base)+(CG6_VADDR_FHC-CG6_VBASE)))
#define CG6VA_TO_THC(base)  \
	((struct thc*)  (((char*)base)+(CG6_VADDR_THC-CG6_VBASE)))
#define CG6VA_TO_DFB(base)  \
	((short*) 	(((char*)base)+(CG6_VADDR_COLOR-CG6_VBASE)))
#define CG6VA_TO_ROM(base)  \
	((u_int*)	(((char*)base)+(CG6_VADDR_ROM-CG6_VBASE)))
#define CG6VA_TO_CMAP(base) \
	((struct cg6_cmap*) (((char*)base)+(CG6_VADDR_CMAP-CG6_VBASE)))


/* (Brooktree DAC) definitions */

/* number of colormap entries */
#define CG6_CMAP_ENTRIES	256

struct cg6_cmap {
	u_int	addr;		/* address register */
	u_int	cmap;		/* color map data register */
	u_int	ctrl;		/* control register */
	u_int	omap;		/* overlay map data register */
};

#endif	!cg6reg_DEFINED
