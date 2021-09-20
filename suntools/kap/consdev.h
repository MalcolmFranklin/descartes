/* @(#) consdev.h 1.1@(#) Solbourne id 9/22/93 00:03:05 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*	@(#)consdev.h 5.8 89/08/31 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

#ifndef _sun_consdev_h
#define	_sun_consdev_h

/*
 * Support for multiple workstation consoles added by
 * Solbourne Computer, Inc.
 */

#ifndef NWSCONS
#define	NWSCONS		4
#endif

int	nconsoles;		/* number of wscons, including serial port */
int	consowner[NWSCONS];	/* current owner of device for TIOCCONS */
dev_t	consdev[NWSCONS];	/* user retargettable console */
struct vnode *consvp[NWSCONS];	/* pointer to vnode for that device */
dev_t	rconsdev[NWSCONS];	/* real console - 0 if not retargetted */
struct vnode *rconsvp[NWSCONS];	/* pointer to vnode for that device */
dev_t	mousedev[NWSCONS];	/* default mouse device */
dev_t	kbddev[NWSCONS];	/* default keyboard device */
int	kbddevopen;		/* keyboard open flag */
dev_t	fbdev[NWSCONS];		/* default framebuffer device */
int	fbisconout;		/* frame buffer is console output */
int	(*fb_mayput[NWSCONS])(); /* put a character if you can */
void	(*fb_fwritestr[NWSCONS])(); /* put a string to frame buffer */

#endif /*!_sun_consdev_h*/
