/* @(#) cg8reg.h 1.1@(#) Solbourne id 9/22/93 00:05:27 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*  @(#)cg8reg.h	1.2 of 8/3/89, SMI */

/* Board layout of Ibis 24-bit frame buffer */

#ifndef CG8REG_INCLUDED
#define CG8REG_INCLUDED

#ifdef CG8REG_DEBUG
#include <sys/types.h>
#include <stdio.h>
#include <pixrect/pixrect.h>
#define P4BASE	    0xfb000000	       /* not for 3/60 */
#endif	CG8REG_DEBUG

#include <machine/param.h>
#include <dev/p4reg.h>
#include <dev/ramdac.h>

/*
 * These are the physical offset from the beginning of the P4.
 */
#define P4IDREG	    0x300000
/* constants define in p4reg.h */
#define DACBASE	    (P4IDREG + P4_COLOR_OFF_LUT)
#define OVLBASE	    (P4IDREG + P4_COLOR_OFF_OVERLAY)
#define ENABASE	    (P4IDREG + P4_COLOR_OFF_ENABLE)
#define FBMEMBASE   (P4IDREG + P4_COLOR_OFF_COLOR)
#define PROMBASE    (P4IDREG + 0x8000)

/*
 * The device as presented by the "mmap" system call.  It seems to the mmap
 * user that the board begins, at its 0 offset, with the overlay plane,
 * followed by the enable plane and the color framebuffer.  At 8MB, there
 * is the ramdac followed by the p4 register and the boot prom.
 */
#define CG8_VADDR_FB	0
#define CG8_VADDR_DAC	0x800000
#define CG8_VADDR_P4REG	(CG8_VADDR_DAC + ctob(1))
#define CG8_VADDR_PROM	(CG8_VADDR_P4REG + ctob(1))
#define PROMSIZE	0x40000

/*
 * Some sizes constants for reference only.  No one actually use them.
 */
#define CG8_WIDTH   1152	       /* default width */
#define CG8_HEIGHT  900		/* default height */
#define PIXEL_SIZE  4		       /* # of bytes per pixel in frame
				        * buffer */
#define BITPERBYTE  8
#define FBSCAN_SIZE (CG8_WIDTH * PIXEL_SIZE)
#define OVLSCAN_SIZE (CG8_WIDTH / BITPERBYTE)

/* screen size in bytes */
#define FBMEM_SIZE  (FBSCAN_SIZE * CG8_HEIGHT)
#define OVL_SIZE    (OVLSCAN_SIZE * CG8_HEIGHT)
#define CG8_RAMDAC_OMAPSIZE		4
#define CG8_RAMDAC_CMAPSIZE		256

/*
 * Constants from <sundev/ramdac.h> which define the structure of 3
 * Brooktree 458 ramdac packed into one 32-bit register.
*/
#define CG8_RAMDAC_READMASK		RAMDAC_READMASK
#define CG8_RAMDAC_BLINKMASK		RAMDAC_BLINKMASK
#define CG8_RAMDAC_COMMAND		RAMDAC_COMMAND
#define CG8_RAMDAC_CTRLTEST		RAMDAC_CTRLTEST

/*
 * The following sessions describe the physical device.  No software
 * actually uses this model which for initial board bring-up and debugging
 * only.  Since the definitions of the structure take no space, we leave
 * them here for future references.
 */
union ovlplane {
    u_short         pixel[OVLSCAN_SIZE / sizeof (u_short)][CG8_HEIGHT];
    u_short         bitplane[OVL_SIZE / sizeof (u_short)];
};


struct overlay {
    union ovlplane  color;
    u_char          pad[ENABASE - OVLBASE - OVL_SIZE];
    union ovlplane  enable;
};


/* The whole board.  We defined fb to be linearly addressable, instead of a
two dimensional array.  Maybe we should use union? */
struct cg8_board {
    struct ramdac   lut;	       /* start at P4BASE + DACBASE */
    u_char          pad1[P4IDREG - DACBASE - sizeof (struct ramdac)];
    u_int           p4reg;	       /* p4 bus register */
    u_char          pad2[OVLBASE - P4IDREG - sizeof (u_int)];
    struct overlay  ovl;	       /* overlay planes */
    u_char          pad3[FBMEMBASE - OVLBASE - sizeof (struct overlay)];
    union fbunit    fb[FBMEM_SIZE / sizeof (union fbunit)];
};



/*
 * Some codes to verify if the definition is really working.  These codes
 * are mostly obsolete.
 */
#ifdef CG8REG_DEBUG

/* ln -s cg8reg.h cg8reg.c; cc -o cg8reg cg8reg.c */
#define PADDR(which) printf("%-15s = 0x%06x\n", \
    "which", (caddr_t) &dummy.which - base + DACBASE)
#define PARRAY_ADDR(which) printf("%-15s = 0x%06x\n", \
    "which", (caddr_t) dummy.which - base + DACBASE)
#define PSIZE(which) printf("\tsize = 0x%06x\n", sizeof(dummy.which))

main ()
{
    static struct cg8_board dummy;
    caddr_t         base;

    base = (caddr_t) & dummy;
    PADDR (lut);
    PADDR (lut.addr_reg);
    PADDR (lut.lut_data);
    PADDR (lut.command);
    PADDR (lut.overlay);
    PADDR (p4reg);
    PADDR (ovl);
    PARRAY_ADDR (ovl.color.bitplane);
    PSIZE (ovl.color);
    PARRAY_ADDR (ovl.enable.bitplane);
    PSIZE (ovl.enable);
    PARRAY_ADDR (fb);
    PSIZE (fb);
}

#endif	CG8REG_DEBUG
#endif	CG8REG_INCLUDED
