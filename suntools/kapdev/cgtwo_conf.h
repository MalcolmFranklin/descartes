/* @(#) cgtwo_conf.h 1.1@(#) Solbourne id 9/22/93 00:05:48 */
/*
 * Copyright 1989 Solbourne Computer, Inc.
 * All rights reserved
 */


extern int ncgtwo;

/* driver per-unit data */
struct cg2_softc {
	int flags;		/* misc. flags; bits defined in cg2var.h */
				/* (struct cg2pr, flags member) */
	struct cg2memfb *memfb;	/* virtual address of plane/pixel mode stuff */
	struct cg2fb *fb;	/* virtual address of rop mode stuff */
	struct cg2id_kernel *id_kernel;	/* kernel only id space */
	struct cg2id *id;	/* virtual address of mappable id space */
	time_t rtwait;		/* time when when started waiting for retrace */
	int w, h;		/* resolution */
#if NWIN > 0
	Pixrect pr;		/* kernel pixrect and private data */
	struct cg2pr prd;
#endif NWIN > 0
	struct tinfo *tp;	/* terminal emulator pointer */
};
