/* @(#) bw2reg.h 1.1@(#) Solbourne id 9/22/93 00:05:17 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/* @(#)bw2reg.h 1.11 87/09/02 SMI */

/*
 * Copyright 1985, 1987 by Sun Microsystems, Inc.
 */

#ifndef	bw2reg_DEFINED
#define	bw2reg_DEFINED

/*
 * Monochrome memory frame buffer hardware definitions
 */

#define	BW2_LORES	1	/* 1152 x 900 pixel frame buffer */
#define	BW2_HIRES	2	/* 1600 x 1280 pixel frame buffer */
#define	BW2_FBSIZE		(256*1024)	/* size of frame buffer */
#define	BW2_FBSIZE_HIRES	(256*1024)	/* hi-res frame buffer size */

/*
 * The video lives in I/O memory space at zero in the adddress space specified
 */
#define	BW2MB_SPACE	0xa		/* address space for frame buffer */

#ifndef LOCORE
/*
 * The video control register is arranged as shown below.
 */
struct	bw2cr {
#ifdef S4000
	unsigned short vc_ins:1;	/* INS -- Int not serviced - r/o */
	unsigned short vc_hblank:1;	/* HBL -- Horizontal blanking - r/o */
	unsigned short vc_vblank:1;	/* VBL -- Vertical blanking - r/o */
	unsigned short vc_res:1;	/* MODE -- Resolution mode */
	unsigned short vc_video_rst:1;	/* RST -- Video reset */
	unsigned short vc_int_en:1;	/* IEN -- Interrupt enable */
	unsigned short vc_video_en:1;	/* DEN -- Video enable */
	unsigned short vc_fb_en:1;	/* FEN -- Frame buffer enable */
#else
	unsigned vc_fb_en:1;		/* Frame buffer enable */
	unsigned vc_video_en:1;		/* Video enable */
	unsigned vc_int_en:1;		/* Interrupt enable */
	unsigned vc_res:1;		/* Resolution mode */
	unsigned vc_space:3;		/* Address space */
	unsigned vc_vblank:1;		/* Vertical blanking - r/o */
#endif S4000
};

/* the Sun-2 bwtwo device, as mapped in the kernel */
struct	bw2dev {
	u_char	image[BW2_FBSIZE];
};
#endif

#ifdef S4000
#define BW2_INS			0x80	/* Interrupt not serviced */
#define BW2_HBLANK		0x40	/* Horizontal blanking */
#define BW2_VBLANK		0x20	/* Vertical blanking */
#define	BW2_HIGHRESMODE		0x10	/* Set high resolution mode */
#define BW2_RESET		0x08	/* Video reset */
#define BW2_INTENABLE		0x04	/* Interrupt enable */
#define BW2_VIDEOENABLE		0x02	/* Video enable */
#define BW2_FRAMEENABLE		0x01	/* Frame buffer enable */
#else
#define BW2_FRAMEENABLE		0x80	/* Frame buffer enable */
#define BW2_VIDEOENABLE		0x40	/* Video enable */
#define BW2_INTENABLE		0x20	/* Interrupt enable */
#define	BW2_HIGHRESMODE		0x10	/* Set high resolution mode */
#define	BW2_ADDRESSSPMASK	0x0e	/* Address Space mask */
#define BW2_INTACTIVE		0x01	/* Vertical blanking */
#define BW2_SPACE(x)  (((x)-8)<<1)	/* set Space Address bits for frame buffer */
#endif S4000

struct bw2_softc {
	caddr_t	image;	/* pointer to frame buffer */
	int w, h;	/* resolution */
	int size;	/* size of frame buffer, bytes */
	int type;	/* type of monitor to drive */
#ifdef S4000
	short *csreg;	/* control/status register */
#else  !S4000
	char *csreg;	/* control/status register */
#endif S4000
	struct tinfo *tp; /* terminal emulator pointer */
	int space;
#if NWIN > 0
	Pixrect pr;
	struct mpr_data prd;
#endif
};

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
#define	BW_BLACK		0x1
#define	BW_WHITE		0x0

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

#endif bw2reg_DEFINED
