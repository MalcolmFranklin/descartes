/* @(#)cg2reg.h 1.2 91/11/23 SMI */

/*
 * Copyright 1983, 1987 by Sun Microsystems, Inc.
 */

#ifndef	cg2reg_DEFINED
#define	cg2reg_DEFINED

/*
 * cg2 -- color frame buffers with rasterop chips
 *
 * The frame buffer address space looks like this:
 *
 * 0x000000	plane mode memory
 * 0x100000	pixel mode memory
 * 0x200000	rop mode memory
 * 0x300000	control registers
 * 0x310000	color map
 *
 * The Solbourne board also provides some "id space" registers.  These
 * start at the page after the color map:
 *
 * 0x312000	id space registers
 *
 * NOTE: the mappable part of the id space is not contiguous with the
 *       compatibility space.  map them in separately using
 *       CG2ID_MAPPED_OFFSET and CG2ID_MAPPED_SIZE.
 *
 * To save on virtual address space, we don't map the plane or pixel mode
 * memory (first two megabytes).  However, when calling mmap the user has
 * to add 2M to the desired offset anyway (goofy, huh?).
 *
 * The following does not apply to Solbourne:
 * The board can also be jumpered so the plane and pixel mode memory are
 * not accessible at all, and the rop mode memory and control registers
 * are decoded starting at address offset 0.
 */

/* offset to and size of mapped part of frame buffer */
#define	CG2_MAPPED_OFFSET	(sizeof (struct cg2memfb))
#define	CG2_MAPPED_SIZE		(sizeof (struct cg2fb))

/* offset to and size of Solbourne specific (id space) part of frame buffer */
#define	CG2ID_MAPPED_OFFSET\
	(roundup(sizeof(struct cg2memfb) + sizeof(struct cg2fb), PAGESIZE) +\
	roundup(sizeof(struct cg2id_kernel), PAGESIZE))
#define	CG2ID_MAPPED_SIZE	(sizeof(struct cg2id))

/* size of idspace csr register (bytes) */
#define CG2_SIZE_CSR		1

/* offset of colormap address register (id space) */
#define CG2ID_CMADDR_OFFSET	0x70000
#define CG2CMREG_COMMAND	6
#define CG2CMREG_COMMAND_REN	0x40
#define CG2CMREG_BLINK		5
#define CG2CMREG_RMASK		4

/* XXX change space to be dynamically allocated */
#define CG2_SPACE		0xd
#define CG2_SPACE_MASK		0x7

/* interrupt priority */
#define	CG2_INT_PRI	4
#define CG2IR_DI	0x40
#define CG2IR_DDID	0x3f

/* frame buffer resolution constants */
#define CG2_WIDTH	1152
#define CG2_HEIGHT	900
#define CG2_SQUARE	1024
#define CG2_DEPTH	8

/* 
 * Structure describing plane and pixel mode memory -- pretty useless
 * since we don't map that part of the frame buffer.
 */
struct	cg2memfb {
	union bitplane {			/* word mode memory */
		short word[CG2_HEIGHT][CG2_WIDTH/(8*sizeof(short))];
		short sword[CG2_SQUARE][CG2_SQUARE/(8*sizeof(short))];
	} memplane[8];
	union byteplane {			/* pixel mode memory */
		u_char pixel[CG2_HEIGHT][CG2_WIDTH];
		u_char spixel[CG2_SQUARE][CG2_SQUARE];
	} pixplane;
};

/* control/status register */
struct cg2statusreg {
	u_int unused : 2;	/* reserved for future use */
	u_int fastread : 1;	/* has fast read feature */
	u_int id : 1;		/* has ID, extended status registers */
	u_int resolution : 4;	/* screen resolution */
#define	CG2_SCR_1152X900	0
#define	CG2_SCR_1024X1024	1
#define	CG2_SCR_1600X1280	2
#define	CG2_SCR_1440X1440	3
	unsigned retrace : 1;	/* rdonly: monitor in retrace */
	unsigned inpend  : 1;	/* rdonly: interrupt pending */
	unsigned ropmode : 3;	/* Rasterop mode */
	unsigned inten   : 1;	/* enab interrupt at end of retrace */
	unsigned update_cmap : 1;
			/* copy TTL cmap to ECL cmap next vert retrace*/
			/* silently disables writing to TTL cmap */
	unsigned video_enab  : 1;	/* enab video DACs */
};

/* extended status register */
struct cg2_status2 {
	u_int gpintreq : 1;	/* GP interrupt request */
	u_int gpintdis : 1;	/* GP interrupt disable */
	u_int unused : 13;	/* reserved for future use */
	u_int gpbus : 1;	/* GP bus enabled (read only) */
};

/* double buffering control register */
struct dblbufreg {
	u_int display_b : 1;	/* Display memory set B or A. */
			/* Synchronized to start of vertical retrace. */
	u_int read_b : 1;	/* Read memory set B or A. */
	u_int nowrite_b : 1;	/* Do not update memory set B on writes. */
	u_int nowrite_a : 1;	/* Do not update memory set A on writes. */
	u_int read_ecmap : 1;/* ECL to TTL cmap transfer direction. */
			/* Synchronized to start of Vertical retrace. */
	u_int fast_read : 1; /* Return invalid data but fast Dtack on read */
	u_int wait : 1;	/* Write a '1' to set.  Bit will remain */
			/* high until a full vertical retrace period has */
			/* elapsed.  The bit clears itself. */
	u_int update_ecmap : 1;
	u_int reserved : 8;
};

/* zoom/pan registers; Sun-2 color board only */
struct cg2_zoom {
	union {				/*----- word pan register */
		unsigned short reg;		/* hi 16 of 20 bit pix addr */
						/* pix addr = CG2_WIDTH*y+x */
		char pad[4096];
	} wordpan;
	union {				/*----- zoom and line offset register */
		struct {
		    unsigned unused  : 8;
		    unsigned lineoff : 4;	/* y offset into zoomed pixel */
		    unsigned pixzoom : 4;	/* zoomed pixel size - 1 */
		} reg;
		short word;
		char pad[4096];
	} zoom;
	union {				/*----- pixel pan register */
		struct {
		    unsigned unused   : 8;
		    unsigned lorigin  : 4;	/* lo 4 bits of pix addr   */
		    unsigned pixeloff : 4;	/* zoomed pixel x offset/4 */
		} reg;
		short word;
		char pad[4096];
	} pixpan;
	union {				/*----- variable zoom register */
						/* reset zoom after line no */
		unsigned short reg;		/* line number 0..1024/4  */
		char pad[4096];
	} varzoom;
};

/* misc. control registers; Sun-3 color board etc. */
struct cg2_nozoom {
	union {				/*----- double buffering register */
		struct dblbufreg reg;
		short word;
		char pad[4096];
	} dblbuf;
	union {				/*----- dma window origin register */
		unsigned short reg;
		char pad [4096];
	} dmabase;
	union {				/*----- dma window width register */
		unsigned short reg;		/* reg * 16 specifies width */
		char pad [4096];		/* of dma window.  8 bit. */
	} dmawidth;
	union {				/*----- frame count register */
		unsigned short reg;		/* 8 bit. Read-only. */
			/* Returns frame number mod 256. */
		char pad[4096];
	} framecnt;
};

/* structure describing mapped part of frame buffer */
struct cg2fb {
	union {					/* ROP mode memory */
		union bitplane ropplane[8];	/* word mode memory with ROP */
		union byteplane roppixel;	/* pixel mode memory with ROP */
	} ropio;
	union {					/* rasterop unit control */
		struct memropc ropregs;		/* normal register access */
		struct {
			char pad[2048];		/* for pixmode src reg prime */
			struct memropc ropregs;	/* byte xfer loads alternate */
		} prime;			/* src register bits */
		char pad[4096];
	} ropcontrol[9];
	union {				/*----- status register */
		struct cg2statusreg reg;
		short word;
		char pad[4096];
	} status;
	union {				/*----- per plane mask register */
		unsigned short reg;		/* 8 bits 1bit -> wr to plane*/
		char pad[4096];
	} ppmask;
	union {
		struct cg2_zoom zoom;
		struct cg2_nozoom nozoom;
	} misc;
	union {				/*----- interrupt vector register */
		unsigned short reg;		/* line number 0..1024/4  */
		char pad[32];
	} intrptvec;
	union {				/* board ID */
		u_short reg;
		char pad[16];
	} id;
	union {				/* extended status */
		struct cg2_status2 reg;
		u_short word;
		char pad[16];
	} status2;
	union {				/* auxiliary ropmode register */
		u_short reg;
		char pad[4032];
	} ropmode;
	u_short redmap[256];			/* shadow color maps */
	u_short greenmap[256];
	u_short bluemap[256];
};

/*
 *	structures describing Solbourne specific part of frame buffer
 *	("id" space).  this is broken in two structs, the part unmappable
 *	by the user (used only by the kernel) and the part that is mappable
 *	by the user (used to set up the hardware cursor).
 */
struct cg2id_kernel {
	u_char idprom[16384 * 8];	/* 16384 idprom bytes, every 8th byte */
	union {
		u_char reg;
		char pad[65536];
	} ioloc;			/* io location register */
	union {
		struct {
			unsigned en:1;		/* (r/w) board enable */
			unsigned led:1;		/* (r/w) led indicator */
			unsigned vien:1;	/* (r/w) vertical int enable */
			unsigned sien:1;	/* (r/w) serial int enable */
			unsigned unused:1;
			unsigned res:1;		/* (r/o) resolution */
			unsigned h:1;		/* (r/o) horizontal blanking */
			unsigned v:1;		/* (r/o) vertical blanking */
		} reg;
		char pad[65536];
	} csr;				/* control/status register */
	union {
		u_short reg;
		char pad[65536];
	} rtint;			/* retrace interrupt register */
	union {
		u_short reg;
		char pad[65536];
	} zsint;			/* serial port interrupt register */
	union {
		struct {
			union {
				u_char reg;
				char pad[16];
			} kbdcsr;		/* keyboard command register */
			union {
				u_char reg;
				char pad[16];
			} kbddat;		/* keyboard data register */
			union {
				u_char reg;
				char pad[16];
			} mscsr;		/* mouse command register */
			union {
				u_char reg;
				char pad[16];
			} msdat;		/* mouse data register */
		} regs;
		char pad[65536];
	} kmregs;			/* keyboard/mouse registers */
};

struct cg2id {
	union {
		struct {
			union {
				u_char reg;
				char pad[4096];
			} cmaddr;		/* colormap address register */
			union {
				u_char reg;
				char pad[4096];
			} cmpal;		/* colormap palette data reg */
			union {
				u_char reg;
				char pad[4096];
			} cmctl;		/* colormap control data reg */
			union {
				u_char reg;
				char pad[4096];
			} cmovly;		/* colormap overlay data reg */
		} regs;
		char pad[65536];
	} cmregs;			/* colormap registers */
	union {
		struct {
			union {
				u_char reg;
				char pad[4096];
			} low;			/* address low register */
			union {
				u_char reg;
				char pad[4096];
			} high;			/* address high register */
			union {
				u_char reg;
				char pad[4096];
			} ram;			/* ram data register */
			union {
				u_char reg;
				char pad[4096];
			} control;		/* control data register */
		} regs;
		char pad[65536];
	} cursor[3];			/* cursor registers */
#define CG2ID_CUR1	0	/* index into cursor[] for cursor 1 */
#define CG2ID_CUR2	1	/* index into cursor[] for cursor 2 */
#define CG2ID_CURBOTH	2	/* index into cursor[] for both cursors */
};

/*
 *	ROPMODE		    PARALLEL	     LD_DST  LD_SRC   Description
 *					       ON      ON		*/
#define	PRWWRD	0	/* parallel 8 plane,  read    write,	wrdmode */
#define	SRWPIX	1	/* single     pixel,  read    write, 	pixmode */
#define	PWWWRD	2	/* parallel 8 plane,  write   write,	wrdmode */
#define	SWWPIX	3	/* single     pixel,  write   write,	pixmode */
#define	PRRWRD	4	/* parallel 8 plane,  read    read,	wrdmode */
#define	PRWPIX	5	/* parallel16 pixel,  read    write,	pixmode */
#define	PWRWRD	6	/* parallel 8 plane,  write   read,	wrdmode */
#define	PWWPIX	7	/* parallel16 pixel,  write   write,	pixmode */

/*
 * ROP control unit numbers
 */
#define CG2_ROP0	0	/* rasterop unit for bit plane 0 */
#define CG2_ROP1	1	/* rasterop unit for bit plane 1 */
#define CG2_ROP2	2
#define CG2_ROP3	3
#define CG2_ROP4	4
#define CG2_ROP5	5
#define CG2_ROP6	6
#define CG2_ROP7	7
#define CG2_ALLROP	8	/* writes to all units enabled by PPMASK */
				/* reads from plane zero */
				
#define	CG_SRC		0xCC
#define	CG_DEST		0xAA
#define	CG_MASK		0xf0
#define	CG_NOTMASK	0x0f
#define	CGOP_NEEDS_MASK(op)		( (((op)>>4)^(op)) & CG_NOTMASK)

/*
 *----------- Defines for accessing the rasterop units
 */
#define	cg2_setrsource(fb, ropunit, val)				\
		((fb)->ropcontrol[(ropunit)].ropregs.mrc_source1 = (val))
#define	cg2_setrsource_pix(fb, ropunit, val) \
		((fb)->ropcontrol[(ropunit)].prime.ropregs.mrc_source1 = (val))
#define	cg2_setlsource(fb, ropunit, val)				\
		((fb)->ropcontrol[(ropunit)].ropregs.mrc_source2 = (val))
#define	cg2_setlsource_pix(fb, ropunit, val) \
		((fb)->ropcontrol[(ropunit)].prime.ropregs.mrc_source2 = (val))
#define	cg2_setpattern(fb, ropunit, val)				\
		((fb)->ropcontrol[(ropunit)].ropregs.mrc_pattern = (val))
#define	cg2_setlmask(fb, ropunit, val) \
		((fb)->ropcontrol[(ropunit)].ropregs.mrc_mask1 = (val))
#define	cg2_setrmask(fb, ropunit, val) \
		((fb)->ropcontrol[(ropunit)].ropregs.mrc_mask2 = (val))
#define	cg2_setshift(fb, ropunit, shft, dir)				\
		((fb)->ropcontrol[(ropunit)].ropregs.mrc_shift =	\
		 (shft)|((dir)<<8)	)
#define	cg2_setfunction(fb, ropunit, val)				\
		((fb)->ropcontrol[(ropunit)].ropregs.mrc_op = (val))
#define	cg2_setwidth(fb, ropunit, w, count)				\
		((fb)->ropcontrol[(ropunit)].ropregs.mrc_width = (w));	\
		((fb)->ropcontrol[(ropunit)].ropregs.mrc_opcount = (count))

/*
 *----------- Defines for accessing the zoom and pan registers
 */
#define	cg2_setzoom(fb, pixsize)					\
		((fb)->misc.zoom.zoom.reg.pixzoom = (pixsize)-1)
#define	cg2_setpanoffset(fb, xoff, yoff)				\
		((fb)->misc.zoom.pixpan.reg.pixeloff = (xoff)>>2; \
		 (fb)->misc.zoom.zoom.reg.lineoff = (yoff))
#define	cg2_setpanorigin(fb, x, y)					\
		((y) = ((fb)->misc.zoom.status.reg.resolution == 1) ? \
			(y)*CG2_SQUARE+(x) : (y)*CG2_WIDTH+(x); \
		 (fb)->misc.zoom.pixpan.reg.lorigin = (y)&0xf; \
		 (fb)->misc.zoom.wordpan.reg = (y)>>4)
#define	cg2_setzoomstop(fb, y) \
		((fb)->misc.zoom.varzoom.reg = (y)>>2)

/*
 *      Defines that facilitate addressing the frame buffer
 */

#define	cg2_pixaddr(fb, x, y)						\
		(((fb)->status.reg.resolution) ?			\
			&(fb)->pixplane.spixel[(y)][(x)] :		\
			&(fb)->pixplane.pixel[(y)][(x)] )
#define	cg2_wordaddr(fb, plane, x, y)					\
		(((fb)->status.reg.resolution) ?			\
			&(fb)->memplane[(plane)].sword[(y)][(x)>>4] :	\
			&(fb)->memplane[(plane)].word[(y)][(x)>>4])
#define	cg2_roppixaddr(fb, x, y)					\
		(((fb)->status.reg.resolution) ?			\
			&(fb)->ropio.roppixel.spixel[(y)][(x)] :	\
			&(fb)->ropio.roppixel.pixel[(y)][(x)])
#define	cg2_ropwordaddr(fb, plane, x, y)				\
		(((fb)->status.reg.resolution) ?			\
			&(fb)->ropio.ropplane[(plane)].sword[(y)][(x)>>4]:\
			&(fb)->ropio.ropplane[(plane)].word[(y)][(x)>>4])
#define	cg2_width(fb )							\
		( ((fb)->status.reg.resolution)	? CG2_SQUARE : CG2_WIDTH )
#define	cg2_height(fb )							\
		( ((fb)->status.reg.resolution)	? CG2_SQUARE : CG2_HEIGHT )
#define	cg2_linebytes(fb, mode)						\
		( ((fb)->status.reg.resolution)				\
			? ( ((mode)&1)?CG2_SQUARE:CG2_SQUARE/8 )	\
			: ( ((mode)&1)?CG2_WIDTH:CG2_WIDTH/8   ))

#define	cg2_prskew(x)	((x) & 15)

#define	cg2_touch(a)	((a)=0)

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
#define	CG2_BLACK		0x1
#define	CG2_WHITE		0x0

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

#endif	cg2reg_DEFINED
