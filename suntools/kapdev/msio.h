/* @(#) msio.h 1.1@(#) Solbourne id 9/22/93 00:07:02 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*      @(#)msio.h 1.1 88/03/29 SMI      */

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

#ifndef _kapdev_msio_h
#define _kapdev_msio_h

/*
 * Mouse related ioctls
 */
#include <sys/ioccom.h>

typedef struct {
    int             jitter_thresh;
    int             speed_law;
    int             speed_limit;
}               Ms_parms;

#define	MSIOGETPARMS	_IOR(m, 2, Ms_parms) /*  get / set jitter, speed  */
#define	MSIOSETPARMS	_IOW(m, 3, Ms_parms) /*  law, or speed limit	   */

#endif _kapdev_msio_h
