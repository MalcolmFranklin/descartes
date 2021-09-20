/* @(#) ansiparse.h 1.1@(#) Solbourne id 9/22/93 00:04:53 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*
 * Copyright 1987 by Digital Equipment Corporation, Maynard, Massachusetts.
 *
 *                         All Rights Reserved
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and that
 * both that copyright notice and this permission notice appear in
 * supporting documentation, and that the name of Digital Equipment
 * Corporation not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior permission.
 *
 *
 * DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
 * DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
 * ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 */

/* @(#)VTparse.h	X10/6.6	11/6/86 */
#define	GROUND_STATE	0x00
#define	IGNORE		0x01
#define	BELL		0x07
#define	BS		0x08
#define	TAB		0x09
#define	LF		0x0a
#define	VT		0x0b
#define	FF		0x0c
#define	CR		0x0D
#define	SO		0x0e
#define	SI		0x0f
#define	ESC		0x1b
#define	ESC_DIGIT	0x1c
#define	ESC_SEMI	0x1d
#define	ICH		0x1e
#define	CUU		0x1f
#define	CUD		0x20
#define	CUF		0x21
#define	CUB		0x22
#define	CNL		0x23
#define	CUP		0x24
#define	ED		0x25
#define	EL		0x26
#define	IL		0x27
#define	DL		0x28
#define	DCH		0x29
#define	TBC		0x2a
#define	SET		0x2b
#define	RST		0x2c
#define	SGR		0x2d
#define	IND		0x2e
#define	NEL		0x2f
#define	HTS		0x30
#define	RI		0x31
#define	CSI_STATE	0x32
#define	PRINT		0x33
#define	SUNBOW		0x40
#define	SUNWOB		0x41
#define	SUNSCRL		0x42
#define	SUNRESET	0x43
