/* @(#) kfont.h 1.1@(#) Solbourne id 9/22/93 00:06:46 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*	@(#)kfont.h 1.6 88/02/07 SMI; from UCB 4.1 83/05/03	*/

/*
 * The structures header and dispatch define the format of a kernel internal
 * font it is a minor variation of the vfont format, mostly with
 * alignment fixups for faster use by kernel bitblt routines.
 *
 * A font contains one struct 'header', an array of KNUM_DISPATCH struct
 * 'dispatch'es, then an array of bytes containing bit maps.
 *
 * See vfont(5) for more details.
 */
struct kheader {
	short		magic;		/* Magic number VFONT_MAGIC */
	unsigned short	size;		/* Total # bytes of bitmaps */
	short		maxx;		/* Maximum horizontal glyph size */
	short		maxy;		/* Maximum vertical   glyph size */
	short		xtend;		/* (unused?) */
	short		fill;		/* unused (aligns struct to long) */
}; 
#define	VFONT_MAGIC	0436

struct kdispatch {
	unsigned short	addr;		/* &(glyph) - &(start of bitmaps) */
	short		nbytes;		/* # bytes of glyphs (0 if no glyph) */
	char		up, down, left, right;	/* Widths from baseline point */
	short		width;		/* Logical width, used by troff */
	short		fill;		/* unused (aligns struct to long) */
};

#define	KNUM_DISPATCH	256

/*
 * the glyphs follow the above structures, all should be aligned on
 * long boundaries so the glyphs consist of a long for each
 * line of the glyph and fonts with > 32 bit wide characters are not 
 * supported.
 */

/*
 * the following is to support the font blits and terminal emulator
 */
#define NullCharInfo ((CharInfoPtr)0)
#define NullFontInfo ((FontInfoPtr)0)
#define LeftToRight 0
#define RightToLeft 1
#define BottomToTop 2
#define TopToBottom 3

#define	GLWIDTHPIXELS(pci) ((pci)->right - (pci)->left)
#define	GLHEIGHTPIXELS(pci) ((pci)->up + (pci)->down)

typedef struct kdispatch CharInfoRec;
typedef struct kheader FontInfoRec;
typedef struct kdispatch *CharInfoPtr;
typedef struct kheader *FontInfoPtr;
typedef unsigned int DrawDirection;

/*
 * the following macro definitions describe a font file image in memory
 */
#define ADDRCharInfoRec(pfi)	((CharInfoRec *) &(pfi)[1])
#define ADDRCHARGLYPHS(pfi)	(((char *) &(pfi)[1]) + BYTESOFCHARINFO(pfi))
#define	BYTESOFFONTINFO(pfi)	(sizeof(FontInfoRec))
#define BYTESOFCHARINFO(pfi)	(sizeof(CharInfoRec) * KNUM_DISPATCH)
#define	BYTESOFGLYPHINFO(pfi)	(((pfi)->size+3) & ~0x3)
#define	GLYPHWIDTHBYTES(pci)	(((GLYPHWIDTHPIXELS(pci))+7) >> 3)
#define	GLYPHHEIGHTPIXELS(pci)	(pci->up + pci->down)
#define	GLYPHWIDTHPIXELS(pci)	(pci->right - pci->left)
#define	GLYPHWIDTHBYTESPADDED(pci)	((GLYPHWIDTHBYTES(pci)+3) & ~0x3)

