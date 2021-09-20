/* @(#) ansiterm.h 1.1@(#) Solbourne id 9/22/93 00:04:57 */
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

/* ptyx.h */
/* @(#)ptyx.h	X10/6.6	11/10/86 */

#ifdef	CODE_EUC
#include <dev/ekfont.h>
#endif	CODE_EUC

#define Max(i, j)       ((i) > (j) ? (i) : (j))

#define MAX_COLS	200
#define MAX_ROWS	128

/*
 * The origin of a screen is 0, 0.  Therefore, the number of rows
 * on a screen is screen->max_row + 1, and similarly for columns.
 */

typedef char **ScrnBuf;

/*
 * ANSI emulation.
 */
#define	CSI	0x9B

#define	NBOX	5			/* Number of Points in box	*/
#define	NPARAM	10			/* Max. parameters		*/

#define	MINHILITE	32

typedef struct {
	unsigned char	a_type;
	unsigned char	a_pintro;
	unsigned char	a_final;
	unsigned char	a_inters;
	char	a_nparam;		/* # of parameters		*/
	char	a_dflt[NPARAM];		/* Default value flags		*/
	short	a_param[NPARAM];	/* Parameters			*/
	char	a_nastyf;		/* Error flag			*/
} ANSI;

typedef struct {
	int		row;
	int		col;
	unsigned	flags;	/* Vt100 saves graphics rendition. Ugh! */
} SavedCursor;

typedef struct {
	char		*fbaddr;	/* address of frame buffer */
	int		fbwidth;	/* pixel width of frame buffer */
	int		fbheight;	/* pixel height of frame buffer */
	int		fbx;		/* x offset for raster ops */
	int		fby;		/* y offset for raster ops */
} Display;

typedef struct {
/*
 * values filled in by the driver that will use the ansi terminal emulator
 */
	/* Drawing functions */
	void		(*FillRectangle)();
	void		(*CopyArea)();
	void		(*InvertArea)();
	void		(*DrawImageString)();
	void		(*ClearEntireScreen)();
	Display		fb;		/* frame buffer descriptor */
	int		white;		/* value for white color */
	int		black;		/* value for black color */
	/*  window parameters */
	struct {
		int	width;		/* width of screen		*/
		int	height;		/* height of screen		*/
		int	f_width;	/* width of font in pixels	*/
		int	f_height;	/* height of font in pixels	*/
	} fullVwin;
	/* Terminal font */
#ifndef	CODE_EUC
	FontInfoRec	*fnt_norm;	/* normal font of terminal	*/
#else	CODE_EUC
	EucFontInfoRec	*fnt_norm;	/* normal font of terminal	*/
#endif	CODE_EUC
	int		max_col;	/* rightmost column		*/
	int		max_row;	/* bottom row			*/
/*
 * values filled in by the terminal emulator
 */
	unsigned char 	*parsestate;	/* ansi parse state */
	int		nparam;		/* current no. of parameters */
	int		param[NPARAM];	/* current parameters */
	int		foreground;	/* current foreground color */
	int		background;	/* current background color */
	int		cursor_state;	/* ON or OFF			*/
	int		cursor_set;	/* requested state		*/
	int		cursor_col;	/* previous cursor column	*/
	int		cursor_row;	/* previous cursor row		*/
	int		cur_col;	/* current cursor column	*/
	int		cur_row;	/* current cursor row		*/
	int		top_marg;	/* top line of scrolling region */
	int		bot_marg;	/* bottom line of  "	    "	*/
	ScrnBuf		buf;		/* screen buffer (main)		*/
	unsigned short	do_wrap;	/* true if cursor in last column
					   and character just output    */
	char		curses;		/* kludge-ups for more and vi	*/
	char	 	multiscroll;	/* true if multi-scroll		*/
	int		scrolls;	/* outstanding scroll count	*/
	int		scroll_amt;	/* amount to scroll		*/
	int		refresh_amt;	/* amount to refresh		*/
	char		jumpscroll;	/* whether we should jumpscroll */
} TScreen;

#define N_MARGINBELL	10
#define MAX_TABS	320
#define TAB_ARRAY_SIZE	10	/* number of ints to provide MAX_TABS bits */

typedef unsigned Tabs [TAB_ARRAY_SIZE];

#define BUF_SIZE 4096

struct tinfo {
	TScreen		screen;
	unsigned	flags;
	Tabs		tabs;
};

/* masks for terminal flags */

#define INVERSE		0x01	/* invert the characters to be output */
#define UNDERLINE	0x02	/* true if underlining */
#define BOLD		0x04
#define WRAPAROUND	0x08
#define REVERSE_VIDEO	0x10	/* true if screen white on black */
#define ORIGIN		0x20	/* true if in origin mode */
#define INSERT		0x40	/* true if in insert mode */
#define SMOOTHSCROLL	0x80	/* true if in smooth scroll mode */
#define AUTOREPEAT	0x100	/* true if in autorepeat mode */
#define IN132COLUMNS	0x200	/* true if in 132 column mode */
#define LINEFEED	0x400
#define	REVERSEWRAP	0x800	/* true if reverse wraparound mode */

#define	ATTRIBUTES	0x07	/* attributes mask */
#define CHAR		0177

#define Width(screen)		(screen->fullVwin.width)
#define Height(screen)		(screen->fullVwin.height)
#define FontWidth(screen)	(screen->fullVwin.f_width)
#define FontHeight(screen)	(screen->fullVwin.f_height)

#define CursorX(screen,col) ((col) * FontWidth(screen))
#define CursorY(screen,row) ((row) * FontHeight(screen))

/* flags for cursors */
#define	OFF		0
#define	ON		1
#define	CLEAR		0
#define	TOGGLE		1

