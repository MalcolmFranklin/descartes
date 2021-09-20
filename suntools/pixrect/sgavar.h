/*
 * Copyright 1990 Solbourne Computer, Inc.
 * All rights reserved
 */

/*
 * sgavar.h - describes the private data of the pixrect
 * @(#)sgavar.h	1.2 9/1/90 10:58:22
 */

#ifndef	SGAVAR_DEFINED
#define	SGAVAR_DEFINED

#define PIX_SUCCESS		0	/* common constant */

#define SGA_LSIZE_X		1152	/* low resolution screen coordinates */
#define SGA_LSIZE_Y		900

#define SGA_HSIZE_X		1280	/* high resolution screen coordinates */
#define SGA_HSIZE_Y		1024

#define SGA_HWSIZE_X		2048	/* hardware bounds */
#define SGA_HWSIZE_Y		1024

#define SGA_REG_SPACE_SIZE	0x33ff	/* used for mmaping space */
#define SGA_FB_SIZE		((SGA_HWSIZE_X * SGA_HWSIZE_Y) / 8)

#define SGA_PSEUDO_COLOR	8
#define SGA_TRUE_COLOR		24

#define SGA_BUSYWAIT_TIMEOUT	100000	/* constant used in looping */

/* FBIOSATTR device specific array indices */
#define FB_ATTR_SGA_SETOWNER_CMD         0
#define FB_ATTR_SGA_SETOWNER_PID         1


/* private data structure for sga driver */
struct sgapr {
    u_char *fb;			/* mmapped color frame buffer */
    struct gpu_reg *gpu;	/* mmapped gPU registers */
    struct gdp_reg *gdp;	/* mmapped gDP registers */
    struct cmap_reg *cmap;	/* mmapped cmap registers */
    int fd;			/* file descriptor */
    int flags;
#define SGA_LOW_RES		0x0	/* low or high resolution */
#define SGA_HIGH_RES		0x1
#define SGA_PLANE8		0x0	/* 8 or 24 planes */
#define SGA_PLANE24		0x2
#define SGA_PRIMARY		0x0	/* primary or secondary pixrect */
#define SGA_SECONDARY		0x4
    int mask;			/* to enable access to specific bitplanes */
    struct pr_pos offset;	/* x and y coordinates of upper left */
};

#define sga_d(pr)		((struct sgapr *) (pr)->pr_data)

#define sga_waitidle(dpr)	while (READ_SHORT((dpr)->gpu->csr & GPU_CSR_BUSY)) ;

#define	sga_linebytes(dpr)	(SGA_HWSIZE_X / 8)

#define sga_depth(dpr)		(((dpr->flags) & SGA_PLANE24) ? \
				    SGA_PSEUDO_COLOR : SGA_TRUE_COLOR)
#define sga_disable_clipping(dpr) \
				WRITE_SHORT((dpr->gpu)->xmin,0); \
				WRITE_SHORT((dpr->gpu)->ymin,0); \
				WRITE_SHORT((dpr->gpu)->xmax,SGA_HWSIZE_X-1); \
				WRITE_SHORT((dpr->gpu)->ymax,SGA_HWSIZE_Y-1)

#define sga_enable_clipping(dpr,min_x,min_y,max_x,max_y) \
				WRITE_SHORT((dpr->gpu)->xmin,min_x); \
				WRITE_SHORT((dpr->gpu)->ymin,min_y); \
				WRITE_SHORT((dpr->gpu)->xmax,max_x); \
				WRITE_SHORT((dpr->gpu)->ymax,max_y); \
				WRITE_SHORT((dpr->gpu)->csr,GPU_CSR_RCLIP)

				/* equivalent to (yval * SGA_HW_SIZE) + xval */
#define sga_product(yval,xval)	(yval << 11) + xval


int     sga_rop();
int     sga_putcolormap();
int     sga_putattributes();

#ifndef KERNEL
extern struct pixrectops sga_ops;
int     sga_stencil();
int     sga_batchrop();
Pixrect *sga_make();
int     sga_destroy();
int     sga_get();
int     sga_put();
int     sga_vector();
Pixrect *sga_region();
int     sga_getcolormap();
int     sga_getattributes();
#endif !KERNEL

#endif	!SGAVAR_DEFINED
