/*
 * Copyright 1990 Solbourne Computer, Inc.
 * All rights reserved.
 */

#ifndef SGAREG_DEFINED
#define SGAREG_DEFINED

#include <sys/param.h>

/*
 * CG+ register and frame buffer hardware definitions
 * @(#)sgareg.h	1.6 9/1/90 10:54:51
 */


/*
 * Physical frame buffer and color map address offsets
 */

#define SGA_ADDR_IDROM		0x000000	/* ID ROM */
#define SGA_ADDR_SREG		0x010000	/* Kernel only registers */
#define SGA_ADDR_UREG		0x012000	/* mmapable registers */
#define SGA_ADDR_PIXEL_FB		0x200000	/* Pixel mode frame buffer */
#define SGA_ADDR_PLANAR_FB		0x400000	/* Planar mode frame buffer */
#define SGA_ADDR_SUNCOMP_FB		0x600000	/* Sun compatible frame buffer */
#define SGA_ADDR_OVERLAY		0x700000	/* Fake overlay plane */
#define SGA_ADDR_WRITEHADDR		0x800000	/* Fake host write buffer page */
#define SGA_ADDR_BUFFHADDR		0x802000	/* Fake host command buffer page */

/*
 * Additional register offsets within mmapable user register page
 */

#define SGA_DSP1_OFFSET	0x0400
#define SGA_DSP2_OFFSET	0x0800
#define SGA_GPU_OFFSET	0x0c00
#define SGA_GDP_OFFSET	(SGA_GPU_OFFSET+0x110)
#define SGA_CMAP_OFFSET	0x1000

/*
 * Sizes in bytes
 */

#define SGA_IDROM_SZ		(8*8192)
#define SGA_SREG_SZ		8192
#define SGA_UREG_SZ		8192
#define SGA_WRITEHADDR_SZ	8192
#define SGA_BUFFHADDR_SZ	8192
#define SGA_FB_SZ		(2*1024*1024)
#define SGA_SUNFB_SZ		(1*1024*1024)

#define SGA_SUN4C_SZ		(256*8192)

/*
 * Virtual (mmap) offsets and addresses
 */

#define SGA_VBASE			0x70000000
#define SGA_VADDR(x)			(SGA_VBASE+(x*8192))

#define SGA_VADDR_UREG		SGA_VADDR(0)
#define SGA_VADDR_PIXEL_FB		(SGA_VADDR_UREG + SGA_UREG_SZ)
#define SGA_VADDR_PLANAR_FB		(SGA_VADDR_PIXEL_FB + SGA_FB_SZ)
#define SGA_VADDR_WRITEHADDR		(SGA_VADDR_PLANAR_FB + SGA_FB_SZ)
#define SGA_VADDR_BUFFHADDR		(SGA_VADDR_WRITEHADDR + SGA_WRITEHADDR_SZ)
#define SGA_VADDR_IDROM		(SGA_VADDR_BUFFHADDR + SGA_BUFFHADDR_SZ)
#define SGA_VADDR_SREG		(SGA_VADDR_IDROM + SGA_IDROM_SZ)
#define SGA_VADDR_SUNCOMP_FB		0

#define SGA_VADDR_SUN4C		(SGA_VADDR_SREG + SGA_SREG_SZ)
#define SGA_VBASE_SUN4C		SGA_VADDR_SUN4C

/*
 * Use MMAPSIZE for length and SGA_VBASE for offset to
 * map one consecutive virtual region containing everything
 * from UREG to IDROM.
 */

#define MMAPSIZE (SGA_VADDR_SREG - SGA_VBASE)

/*
 * Macros to convert from mmap virtual addresses returned by
 * pr_makefromfd to CG+ register set.
 *
 * NOTE:  For the PIXEL_FB, PLANAR_FB, WRITEHADDR, BUFFHADDR,
 *	and IDROM macros to work correctly, everything must
 *	have been mapped in as one consecutive region using
 *	MMAPSIZE.  If these areas were mmapped in individually,
 *	then the return address can be used directly.
 */


#define SGAVA_TO_UREG(base) \
	((struct gsbi_ureg *) (((char *)base) + (SGA_VADDR_UREG-SGA_VBASE)))
#define SGAVA_TO_DSP1_PORT(base) \
	((DSP_T *) (((char *)base) + (SGA_VADDR_UREG-SGA_VBASE+SGA_DSP1_OFFSET)))
#define SGAVA_TO_DSP2_PORT(base) \
	((DSP_T *) (((char *)base) + (SGA_VADDR_UREG-SGA_VBASE+SGA_DSP2_OFFSET)))
#define SGAVA_TO_GPU_REG(base) \
	((struct gpu_reg *) (((char *)base) + (SGA_VADDR_UREG-SGA_VBASE+SGA_GPU_OFFSET)))
#define SGAVA_TO_GDP_REG(base) \
	((struct gdp_reg *) (((char *)base) + (SGA_VADDR_UREG-SGA_VBASE+SGA_GDP_OFFSET)))
#define SGAVA_TO_CMAP(base) \
	((struct cmap_reg *) (((char *)base) + (SGA_VADDR_UREG-SGA_VBASE+SGA_CMAP_OFFSET)))
#define SGAVA_TO_PIXEL_FB(base) \
	((u_char *) (((char *)base) + (SGA_VADDR_PIXEL_FB-SGA_VBASE)))
#define SGAVA_TO_PLANAR_FB(base) \
	((u_char *) (((char *)base) + (SGA_VADDR_PLANAR_FB-SGA_VBASE)))
#define SGAVA_TO_WRITEHADDR(base) \
	((char *) (((char *)base) + (SGA_VADDR_WRITEHADDR-SGA_VBASE)))
#define SGAVA_TO_BUFFHADDR(base) \
	((char *) (((char *)base) + (SGA_VADDR_BUFFHADDR-SGA_VBASE)))
#define SGAVA_TO_IDROM(base) \
	((u_char *) (((char *)base) + (SGA_VADDR_IDROM-SGA_VBASE)))
#define SGAVA_TO_SREG(base) \
	((struct gsbi_sreg *) (((char *)base) + (SGA_VADDR_SREG-SGA_VBASE)))
#define SGAVA_TO_SUNCOMP_FB(base) \
	((u_char *) base)


/*
 * SGA gSBI kernel only registers
 */

struct gsbi_sreg {
	u_short csr, pad1;	/* Control Status Register */
#define	GSBI_CSR_REVISION		0x3000
#define GSBI_CSR_DSPBUSY		0x0800
#define GSBI_CSR_RESET			0x0400
#define GSBI_CSR_CTSELECT		0x0200
#define GSBI_CSR_DSPIENABLE		0x0100
#define GSBI_CSR_ENBREAD		0x0080
#define GSBI_CSR_ENBWRITE		0x0040
#define GSBI_CSR_ENABLEALL		(GSBI_CSR_DSPIENABLE|GSBI_CSR_ENBREAD|GSBI_CSR_ENBWRITE)
#define GSBI_CSR_CLEAR			0x0020
#define GSBI_CSR_CMDSIZE		0x0010
#define GSBI_CSR_ZBUFSENSE		0x0008
#define GSBI_CSR_CMDPENDING		0x0004
#define GSBI_CSR_READPENDING		0x0002
#define GSBI_CSR_WRITEPENDING		0x0001
	u_long	writehaddr;		/* Write Host Address */
	u_long	icr;			/* Interrupt Cause Register */
#define GSBI_ICR_ACCESS			0x02000000
#define GSBI_ICR_DSPORIG		0x01000000
#define GSBI_ICR_DSPTOKEN		0x00ffffff
	u_long fcr;			/* Fault Cause Register */
#define GSBI_FCR_CYCLE			0x04000000
#define GSBI_FCR_MEMORY			0x02000000
#define GSBI_FCR_INVENTRY		0x01000000
#define GSBI_FCR_INVTAG			0x00800000
#define GSBI_FCR_BUFPTR			0x00400000
#define GSBI_FCR_READREG		0x00100000
#define GSBI_FCR_WRITEREG		0x00080000
#define GSBI_FCR_HIGHVADDR		0x0007ffff
	u_long	buffhaddr;		/* Buffer Host Address */
	u_short	tlbptr, pad2;		/* TLB pointer */
#define GSBI_TLB_NENTRIES		512
	u_long	tlbdata;		/* TLB data */
#define GSBI_TLB_SOFTMASK		0xf0000000
#define GSBI_TLB_SOFT_IO		0x10000000
#define GSBI_TLB_REF			0x08000000
#define GSBI_TLB_VALID			0x04000000
#define GSBI_TLB_TAG			0x03ff0000
#define GSBI_TLB_VTAGMASK		0xffc00000
#define GSBI_TLB_VTAGSHIFT		6
#if defined(Series4) || defined(Series5)
#define GSBI_TLB_PFNMASK		0x0000ffff
#else
#define GSBI_TLB_PFNMASK		0x00007fff
#endif	Series4 || Series5
	u_short	asi, pad3;		/* Address Space Indicator */
};

/*
 * SGA gSBI user mmapable registers
 */

struct gsbi_ureg {
	u_short	buffwrite, pad1;	/* Primary command buffer write pointer */
	u_short buffread, pad2;		/* Primary command buffer read pointer */
	u_short mcr, pad3;		/* Master control register */
#define GSBI_MCR_AUXOUTPUT		0x100
#define GSBI_MCR_DSPRUN			0x080
#define GSBI_MCR_DSPINTERRUPT		0x040
#define GSBI_MCR_ENBPCB			0x020
#define	GSBI_MCR_PCBPTREQUAL		0x010
#define GSBI_MCR_BUSREQ2		0x008
#define GSBI_MCR_BUSGRANT2		0x004
#define GSBI_MCR_BUSREQ1		0x002
#define GSBI_MCR_BUSGRANT1		0x001
};

/*
 * SGA DSP parallel port interface definitions
 */

struct dspm0regs {
	unsigned char pad80;
	unsigned char parl;
	unsigned short pad81;
	unsigned char pad82;
	unsigned char parh;
	unsigned short pad83;
	unsigned char pad84;
	unsigned char pdrl;
	unsigned short pad85;
	unsigned char pad86;
	unsigned char pdrh;
	unsigned short pad87;
	unsigned char pad88;
	unsigned char emrl;
	unsigned short pad89;
	unsigned char pad90;
	unsigned char emrh;
	unsigned short pad91;
	unsigned char pad92;
	unsigned char esr;
	unsigned short pad93;
	unsigned char pad94;
	unsigned char pcrl;
	unsigned short pad95;
	unsigned char pad96;
	unsigned char pirh;
	unsigned short pad97;
};

struct dspm1regs {
	unsigned char pad80;
	unsigned char parl;
	unsigned short pad81;
	unsigned char pad82;
	unsigned char parh;
	unsigned short pad83;
	unsigned char pad84;
	unsigned char pdrl;
	unsigned short pad85;
	unsigned char pad86;
	unsigned char pdrh;
	unsigned short pad87;
	unsigned char pad88;
	unsigned char emrl;
	unsigned short pad89;
	unsigned char pad90;
	unsigned char emrh;
	unsigned short pad91;
	unsigned char pad92;
	unsigned char esr;
	unsigned short pad93;
	unsigned char pad94;
	unsigned char pcrl;
	unsigned short pad95;
	unsigned char pad96;
	unsigned char pirl;
	unsigned short pad97;
	unsigned char pad98;
	unsigned char pirh;
	unsigned short pad99;
	unsigned char pad100;
	unsigned char pcrh;
	unsigned short pad101;
	unsigned char pad102;
	unsigned char pare;
	unsigned short pad103;
	unsigned char pad104;
	unsigned char pdr2l;
	unsigned short pad105;
	unsigned char pad106;
	unsigned char pdr2h;
	unsigned short pad107;
};

struct dsp16regs {
	unsigned short par;
	unsigned short pad0;
	unsigned pad1;
	unsigned short pdr;
	unsigned short pad3;
	unsigned pad4;
	unsigned short emr;
	unsigned short pad5;
	unsigned pad6;
	unsigned short esr;
	unsigned short pad7;
	unsigned short pcr;
	unsigned short pad8;
	unsigned short pir;
	unsigned short pad9;
	unsigned pada[2];
	unsigned short pare;
	unsigned short padb;
	unsigned short pdr2;
	unsigned short padc;
};



/*
   The DSP parallel interface will be used in 16 bit mode.  The following
   defines assume this mode.
*/

#define	MODE8		0
#define	MODE16		1

#define	PCRRUN		0x001
#define	REGMAP		0x002
#define	ENPIF		0x004
#define	PCRDMA		0x008
#define	PCRAUTO		0x010
#define	PCRPDF		0x020
#define	PCRPIF		0x040
#define	PCRDMA32	0x100
#define	PCRPIO16	0x200
#define	PCRFLG		0x400

typedef union {
	struct dspm0regs map0;
	struct dspm1regs map1;
	struct dsp16regs regs16;
} DSP_T;

/*
 * The following definitions are used for the DSP interface to/from the
 * SPU user programs
 */

#ifndef KERNEL
#define	DSP1	0
#define	DSP2	1
#define	DSP3	2

/*
   The state of each DSP
*/

struct cb {
	unsigned short command;
	unsigned short cfill;
	unsigned parms[3];		/* Parameters */
	};

struct sb {
	unsigned short sfill;
	unsigned short status;
	unsigned sd[9];			/* Returned data, if used */
	};

struct dspstat {
	unsigned mode : 1;		/* 0 = 8 bit, 1 = 16 bit */
	unsigned running : 1;		/* The DSP is running */
	unsigned inop : 1;		/* DSP is unusable */
	unsigned heldoff : 1;		/* DSP is held off */
	unsigned holdexp : 1;		/* DSP hold off is expected */
	unsigned suspended : 1;		/* The DSP is suspended */
	unsigned idle : 1;
	unsigned monld : 1;		/* DSP command monitor is loaded */
	unsigned testld : 1;		/* Flag if test is loaded in DSP mem */
	struct cb cb;
	struct sb sb;
	unsigned tsa;			/* Test start address */
	char testname[15];		/* The test file */
	DSP_T  *r;			/* Pointer to DSP registers */
};

extern struct dspstat ds[];		/* The status array */

/* The DSP monitor program image */
#define	DSPMON		"dspmon"

/* Flags for the program loader */
#define	NO_MON		1	/* No monitor is required, ok to overwrite */

/* The DSP monitor is loaded for RAM2, the starting address is 0 */
#define	DSPMON_LDADDR	0

/* Offsets for the variables in DSP memory */
#define	OFF_DSPNUM	0x08
#define	OFF_HALTFLAG	0x0A
#define	OFF_CONTFLAG	0x0C
#define	OFF_QUIETFLAG	0x0E
#define	OFF_LOOPFLAG	0x10
#define	OFF_COMMAND	0x20

#endif !KERNEL

/*
 * SGA gPU Graphics Controller registers
 */

struct gpu_reg {
	u_short	hperiod, pad1;		/* Horizontal period */
	u_short hblank, pad2;		/* Horizontal Blank period */
	u_short hstart, pad3;		/* Horizontal Sync start value */
	u_short hstop,  pad4;		/* Horizontal Sync stop value */
	u_short vperiod, pad5;		/* Vertical period */
	u_short vblank, pad6;		/* Vertical Blank period */
	u_short vstart, pad7;		/* Vertical Sync start value */
	u_short vstop,  pad8;		/* Vertical Sync stop value */
	u_short refcnt, pad9;		/* Refresh Count value */
	u_short sysconfig, pad10;	/* System Configuration Register */
#define GPU_SYS_REFRESHDETECT	0x400
#define GPU_SYS_SERIALDTADETECT	0x200
#define GPU_SYS_COUNTERTESTENB	0x100
#define GPU_SYS_PIXPERSCNLINE	0x0e0
#define GPU_SYS_ENBPAGEMODE	0x010
#define GPU_SYS_ENBVTIMING	0x008
#define GPU_SYS_ENBREFRESH	0x004
#define GPU_SYS_ZBUFPRESENT	0x002
#define GPU_SYS_PLANESELECT	0x001
	u_short	xmin,  pad11;		/* clipping upper left X coordinate */
	u_short ymin,  pad12;		/* clipping upper left Y coordinate */
	u_short xmax,  pad13;		/* clipping lower right X coordinate */
	u_short ymax,  pad14;		/* clipping lower right Y coordinate */
	u_short bread, pad15;		/* Bank read select */
#define GPU_BREAD_RED		0x0
#define GPU_BREAD_GREEN		0x1
#define GPU_BREAD_BLUE		0x2
#define GPU_BREAD_CONTROL	0x3
#define GPU_BREAD_ZBUFLOW	0x4
#define GPU_BREAD_ZBUFHIGH	0x5
	u_short bwrite, pad16;		/* Bank write select */
#define GPU_BWRITE_RED		0x01
#define GPU_BWRITE_GREEN	0x02
#define GPU_BWRITE_BLUE		0x04
#define GPU_BWRITE_CONTROL	0x08
#define GPU_BWRITE_ZBUFLOW	0x10
#define GPU_BWRITE_ZBUFHIGH	0x20
#define GPU_BWRITE_RGB		(GPU_BWRITE_RED | GPU_BWRITE_GREEN | GPU_BWRITE_BLUE)
	u_short	lptrnh, pad17;		/* line pattern high */
	u_short lptrnl, pad18;		/* line pattern low */
	u_short lptrnc, pad19;		/* line pattern control */
	u_short csr,  pad20;		/* Control Status register */
#define GPU_CSR_REVISION	0x3000
#define GPU_CSR_VBLANK		0x0020
#define GPU_CSR_HBLANK		0x0010
#define GPU_CSR_BUSY		0x0080
#define GPU_CSR_DCLIPPED	0x0040
#define GPU_CSR_RCLIPFB		0x0008
#define GPU_CSR_CCLIPFB		0x0004
#define GPU_CSR_RCLIPRP		0x0002
#define GPU_CSR_CCLIPRP		0x0001
#define GPU_CSR_RCLIP		(GPU_CSR_RCLIPFB | GPU_CSR_RCLIPRP)
	u_short	buffcntrl, pad21;	/* Buffer control */
#define GPU_BCNTRL_FLAG		0x0400
#define GPU_BCNTRL_BPTRMASK	0x03ff
	u_short buffer,  pad22;		/* Buffer data register */
	u_short command,   pad23;	/* Command trigger register */
#define GPU_CMD_POLYLINE	0xc000
#define GPU_CMD_POLYGON		0xe000
#define GPU_CMD_IBITBLT		0x8000
#define GPU_CMD_EBITBLT		0x9000
#define GPU_CMD_FRAF		0xa000
};

/*
 * SGA gPD Graphics Data Path registers
 */

struct gdp_reg {
	u_short	loc,  pad1;		/* Location register */
	u_short	dccr, pad2;		/* double buffering and clipping control */
	u_short color, pad3;		/* color data */
	u_short	gpwm, pad4[3];		/* Graphics plane write mask */
#define GDP_GPWM_ALL_PLANES	0x00ff
	u_short bblt, pad5;		/* BitBLT register */
	u_short fifo, pad6;		/* FIFO register */
	u_short frst, pad7;		/* FIFO reset register */
	u_short dar0, pad8;		/* Diagnostic address register 0 */
	u_short dar1, pad9;		/* Diagnostic address register 1 */
	u_long	pad10;
	u_short shcr, pad11;		/* Shading control register */
	u_short miri, pad12;		/* Main interpolation - integer part */
	u_short mire, pad13;		/* Main interpolation - error term */
	u_short midi, pad14;		/* Main interpolation - delta integer part */
	u_short midf1, pad15;		/* Main interpolation - delta fraction #1 */
	u_short midf2, pad16;		/* Main interpolation - delta fraction #2 */
	u_short siri, pad17;		/* Second interpolation - integer part */
	u_short sire, pad18;		/* Second interpolation - error term */
	u_short sidi, pad19;		/* Second interpolation - delta integer part */
	u_short sidf1, pad20;		/* Second interpolation - delta fraction #1 */
	u_short sidf2, pad21;		/* Second interpolation - delta fraction #2 */
	u_short tiri, pad22;		/* Third interpolation - integer part */
	u_short tire, pad23;		/* Third interpolation - error term */
	u_short tidi, pad24;		/* Third interpolation - delta integer part */
	u_short tidf1, pad25;		/* Third interpolation - delta fraction #1 */
	u_short tidf2, pad26;		/* Third interpolation - delta fraction #2 */
	u_short	pcent, pad27;		/* Pseudo color entry register */
	/*
	 * Plane replacement rule registers
	 */
	u_short	rr0, pad28;
	u_short rr1, pad29;
	u_short rr2, pad30;
	u_short rr3, pad31;
	u_short rr4, pad32;
	u_short rr5, pad33;
	u_short rr6, pad34;
	u_short rr7, pad35;
	u_short rrall, pad36;
#define GDP_RRALL_SOURCE	0x0003
	u_long	pad37[7];
	/*
	 * Diagnostic Data registers
	 */
	u_short ddr0, pad38;
	u_short ddr1, pad39;
	u_short ddr2, pad40;
	u_short ddr3, pad41;
	u_short ddr4, pad42;
	u_short ddr5, pad43;
	u_short ddr6, pad44;
	u_short ddr7, pad45;
	u_short ddrall, pad46;
};


/*
 * Brooktree colormap definitions
 */

#define SGA_CMAP_ENTRIES_PIX	256
#define SGA_CMAP_ENTRIES_MAX	256  /* Brooktree really has 512 entries */
#define SGA_BRK_RMASKLOW	0x204
#define SGA_BRK_RMASKHIGH	0x205
#define SGA_BRK_CURSORCMD	0x300

struct cmap_reg {
	u_char	addrlow,pad1,pad2,pad3;		/* address register low */
	u_char	addrhigh,pad4,pad5,pad6;	/* address register high */
	u_char	ctrldata,pad7,pad8,pad9;	/* control data */
	u_char	paldata,pad10,pad11,pad12s;	/* palette data */
};

/*
 * Brooktree Bt451/458 definitions
 */

#define SGA_B458_RMASK	0x4
#define SGA_B458_BLINK	0x5
#define SGA_B458_CMDREG	0x6

struct bt458_cmap_reg {
	u_char	addr,pad1,pad2,pad3;		/* address register */
	u_char	paldata,pad4,pad5,pad6;		/* palette data */
	u_char	ctrldata,pad7,pad8,pad9;	/* control data */
	u_char	ovlydata,pad10,pad11,pad12;	/* overlay data */
};

#ifdef SIM
extern u_char sim_read_byte();
extern u_short sim_read_short();
extern u_long sim_read_long();

#define WRITE_BYTE(ADDR,DATA)	    sim_write_byte(&ADDR,DATA)
#define WRITE_SHORT(ADDR,DATA)	    sim_write_short(&ADDR,DATA)
#define WRITE_LONG(ADDR,DATA)	    sim_write_long(&ADDR,DATA)
#define READ_BYTE(ADDR)		    sim_read_byte(&ADDR)
#define READ_SHORT(ADDR)	    sim_read_short(&ADDR)
#define READ_LONG(ADDR)		    sim_read_long(&ADDR)

#else

#define WRITE_BYTE(ADDR,DATA)	    ADDR = DATA
#define WRITE_SHORT(ADDR,DATA)	    ADDR = DATA
#define WRITE_LONG(ADDR,DATA)	    ADDR = DATA
#define READ_BYTE(ADDR)		    ADDR
#define READ_SHORT(ADDR)	    ADDR
#define READ_LONG(ADDR)		    ADDR

#endif

/*
 * CG+ IDROM configuration data structure layout
 *
 *	The CG+ IDROM is organized as follows:
 *
 *
 *				-----------------
 *			0x0000  |     Forth     |
 *				|     Code	|
 *				|		|
 *				|      cg+ 	|
 *				| initialization|
 *				|     and       |
 *				|   self-tests	|
 *				|		|
 *				|		|
 *				-----------------
 *			0x3fdf	| Configuration |
 *				-----------------
 *		 	0x4000	| Compatability |
 *				|    Table I    |
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				-----------------
 *			0x8000  | Compatability |
 *				|    Table II   |
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *				|		|
 *			0xffff  |   		|
 *				-----------------
 *
 *
 * Multiple configuration data formats are supported.  The last byte
 * of the current structure defines the current type.  The byte before
 * the current structure indicates more data is available.  For now,
 * a data type value of "1" indicates the cg+ structure layout, and
 * the byte before it, at 0x3fdf has a "0", indicating no more data.
 */

struct sga_idrom_conf {
	u_char		board_type;		/* 8/24 planes, sga20/40/50, etc. */
	u_char		sysconfig;		/* data for sys config register */
	u_short		x_resolution;		/* 1152, 1280, etc */
	u_short		y_resolution;		/* 900, 1024, etc */
	u_short		x_cursor_off;		/* x cursor offset */
	u_short		y_cursor_off;		/* y cursor offset */
	u_short		hperiod;		/* horizontal period */
	u_short		hblank;			/* horizontal blanking period */
	u_short		hstart;			/* horizontal start */
	u_short		hstop;			/* horizontal stop */
	u_short		vperiod;		/* vertical period */
	u_short		vblank;			/* vertical blanking period */
	u_short		vstart;			/* vertical start */
	u_short		vstop;			/* vertical stop */
	u_short		reserved2;
	u_short		reserved3;
	u_char		reserved4;
	u_char		current_data_type;	/* configuration structure type: 1 for this structure */
};

#define SGA_IDROM_CONFBASE		(0x4000)	/* Configuration address +1 */
#define SGA_IDROM_CONFADDR		(SGA_IDROM_CONFBASE - sizeof(struct sga_idrom_conf))
#define SGA_IDROM_CONFNEXT		(SGA_IDROM_CONFADDR - sizeof(struct sga_idrom_conf))

#define SGA_IDROM_CONFNULL	0		/* no more data */
#define SGA_IDROM_CONFTYPE	1		/* sga_idrom_conf structure layout */

#define SGA_IDROM_SGA40	0x00		/* 8 plane SGA40 */
#define SGA_IDROM_SGA50	0x01		/* 24 plane SGA50 */
#define SGA_IDROM_SGA20	0x02		/* 8 plane SGA20 (no DSP) */




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
#define	SGA_BLACK		0x1
#define	SGA_WHITE		0x0

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

#endif !SGAREG_DEFINED
