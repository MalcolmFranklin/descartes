/* @(#) cg4reg.h 1.1@(#) Solbourne id 9/22/93 00:05:22 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/* @(#)cg4reg.h 1.2 89/08/03 SMI */

/*
 * Copyright 1986 by Sun Microsystems, Inc.
 */

#ifndef	cg4reg_DEFINED
#define	cg4reg_DEFINED

/*
 * Prism frame buffer hardware definitions.
 *
 * The cg4 device has an overlay plane, enable plane and eight planes
 * of color/grayscale pixel read/write memory.  There are no rasterop chips 
 * or planes register.  All memory is on board memory.
 *
 * There are two flavors of cg4.  The A type has AMD DACS in the I/O space
 * and a status register.  The B type has a Brooktree BT458 DAC in the
 * memory space.
 */

/* number of colormap entries */
#define CG4_CMAP_ENTRIES	256

#ifdef sun3

/* number of known cg4 types */
#define	CG4_NTYPES		2

/* A type (AMD DAC) definitions */
#define	CG4A			0

/* frame buffer and color map addresses */
#ifdef S4000
/* XXX */
#else
#define CG4A_ADDR_OVERLAY	0xFF000000
#define CG4A_ADDR_ENABLE	0xFE400000
#define CG4A_ADDR_COLOR		0xFE800000
#define CG4A_ADDR_CMAP		0x000E0000
#endif S4000

/* frame buffer and color map address spaces */
#define CG4A_PGT_FB		PGT_OBMEM
#define CG4A_PGT_CMAP		PGT_OBIO

/* colormap/status register structure */
struct cg4a_cmap {
	u_char red[CG4_CMAP_ENTRIES];
	u_char green[CG4_CMAP_ENTRIES];
	u_char blue[CG4_CMAP_ENTRIES];
	u_char status;
#define CG4A_STATUS_FIRSTHALF	0x80
#define CG4A_STATUS_TOOLATE	0x40
};

/* B type (Brooktree DAC) definitions */

/* frame buffer and color map addresses */
#define CG4B_ADDR_OVERLAY	0xFF400000
#define CG4B_ADDR_ENABLE	0xFF600000
#define CG4B_ADDR_COLOR		0xFF800000
#define CG4B_ADDR_CMAP		0xFF200000

/* frame buffer and color map address spaces */
#define CG4B_PGT_FB		PGT_OBMEM
#define CG4B_PGT_CMAP		PGT_OBMEM

#endif sun3
#ifdef sun4

/* number of known cg4 types */
#define	CG4_NTYPES		1

/* B type (Brooktree DAC) definitions */

/* frame buffer and color map address spaces */
#define CG4B_PGT_FB		PGT_OBIO
#define CG4B_PGT_CMAP		PGT_OBIO

#endif sun4
#ifdef sun3x

/* number of known cg4 types */
#define	CG4_NTYPES		1

/* B type (Brooktree DAC) definitions */

/* frame buffer and color map addresses */
#define CG4B_ADDR_OVERLAY	0x50400000
#define CG4B_ADDR_ENABLE	0x50600000
#define CG4B_ADDR_COLOR		0x50800000
#define CG4B_ADDR_CMAP		0x50200000

/* frame buffer and color map address spaces -- not used on sun3x */
#define CG4B_PGT_FB		0
#define CG4B_PGT_CMAP		0

#endif sun3x

#ifdef S4000
/* colormap structure */
struct cg4b_cmap {
	u_char	addr;		/* address register */
	char	fill0[3];
	u_char	ctrl;		/* control register */
	char	fill1[3];
	u_char	cmap;		/* color map data register */
	char	fill2[3];
	u_char	omap;		/* overlay map data register */
	char	fill3[3];
};
#else
/* colormap structure */
struct cg4b_cmap {
	u_char	addr;		/* address register */
	char	fill0[7];
	u_char	cmap;		/* color map data register */
	char	fill1[7];
	u_char	ctrl;		/* control register */
	char	fill2[7];
	u_char	omap;		/* overlay map data register */
	char	fill3[7];
};
#endif S4000

#define CG4_LED		0x80	/* led			*/
#define CG4_RESET	0x08	/* 0 == reset */
#define CG4_INTENABLE	0x04	/* Interrupt enable	*/
#define CG4_VIDEOBLANK	0x02	/* video blank		*/
#define CG4_VIDEOENABLE	0x01	/* video enable		*/

#define CG4_OVERLAY_SIZE	0x20000
#define CG4_IMAGE_SIZE		0x100000

/* frame buffer offsets */
#ifdef S4000
#define CG4_ADDR_OVERLAY	0x040000
#define CG4_ADDR_ENABLE		0x060000
#define CG4_ADDR_COLOR		0x100000
#else
#define CG4_ADDR_OVERLAY	0x000000
#define CG4_ADDR_ENABLE		0x020000
#define CG4_ADDR_COLOR		0x100000
#endif S4000

/* cg4 register offsets */
#ifdef S4000
#define CG4_ADDR_CSR		0x081000
#define CG4_ADDR_CMAP		0x081100
#define CG4_INT_CLR		0x081400
#else
#define CG4_ADDR_PROM		0x000000
#define CG4_ADDR_CSR		0x010000
#define CG4_ADDR_SPACE		0x020000
#define CG4_ADDR_VIDEO		0x030000
#define CG4_ADDR_CMAP		0x040000
#define CG4_ADDR_IIR		0x050000
#define CG4_ADDR_IVR		0x060000
#endif S4000

/* cg4 regsister sizes */
#define CG4_SIZE_PROM		0x10000
#define CG4_SIZE_CSR		0x1
#define CG4_SIZE_SPACE		0x1
#define CG4_SIZE_VIDEO		0x61
#define CG4_SIZE_CMAP		0x19
#define CG4_SIZE_IIR		0x1
#define CG4_SIZE_IVR		0x1
#define CG4_SPACE		0xc

/* interrupt register values */
#define CG4_IVEC		0x85


/***********************************************************
Copyright 1987 by Digital Equipment Corporation, Maynard, Massachusetts,
and the Massachusetts Institute of Technology, Cambridge, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Digital or MIT not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*****************************************************************
 * GRAPHICS DEFINITIONS
 *****************************************************************/

#define	GXclear			0x0		/* 0 */
#define GXand			0x1		/* src AND dst */
#define GXandReverse		0x2		/* src AND NOT dst */
#define GXcopy			0x3		/* src */
#define GXandInverted		0x4		/* NOT src AND dst */
#define	GXnoop			0x5		/* dst */
#define GXxor			0x6		/* src XOR dst */
#define GXor			0x7		/* src OR dst */
#define GXnor			0x8		/* NOT src AND NOT dst */
#define GXequiv			0x9		/* NOT src XOR dst */
#define GXinvert		0xa		/* NOT dst */
#define GXorReverse		0xb		/* src OR NOT dst */
#define GXcopyInverted		0xc		/* NOT src */
#define GXorInverted		0xd		/* NOT src OR dst */
#define GXnand			0xe		/* NOT src OR NOT dst */
#define GXset			0xf		/* 1 */

/* Colors */
#define	CG4_BLACK		0x1
#define	CG4_WHITE		0x0

/* Byte order  used in imageByteOrder and bitmapBitOrder */

#define LSBFirst                0
#define MSBFirst                1

#define IMAGE_BYTE_ORDER        MSBFirst        /* Values for the SUN only */
#define BITMAP_BIT_ORDER        MSBFirst
#define GLYPHPADBYTES           4
#define GETLEFTBITS_ALIGNMENT   4

/* Binary search to figure out what to do for the raster op.  It may
 * do 5 comparisons, but at least it does no function calls
 * Special cases copy because it's so frequent
 */
#define DoRop(alu, src, dst) \
( ((alu) == GXcopy) ? (src) : \
    (((alu) >= GXnor) ? \
     (((alu) >= GXcopyInverted) ? \
       (((alu) >= GXnand) ? \
         (((alu) == GXnand) ? ~((src) & (dst)) : ~0) : \
         (((alu) == GXcopyInverted) ? ~(src) : (~(src) | (dst)))) : \
       (((alu) >= GXinvert) ? \
         (((alu) == GXinvert) ? ~(dst) : ((src) | ~(dst))) : \
         (((alu) == GXnor) ? ~((src) | (dst)) : (~(src) ^ (dst)))) ) : \
     (((alu) >= GXandInverted) ? \
       (((alu) >= GXxor) ? \
         (((alu) == GXxor) ? ((src) ^ (dst)) : ((src) | (dst))) : \
         (((alu) == GXnoop) ? (dst) : (~(src) & (dst)))) : \
       (((alu) >= GXandReverse) ? \
         (((alu) == GXandReverse) ? ((src) & ~(dst)) : (src)) : \
         (((alu) == GXand) ? ((src) & (dst)) : 0)))  ) )

#endif	!cg4reg_DEFINED
