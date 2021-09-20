/* @(#) sqz.h 1.1@(#) Solbourne id 9/22/93 00:04:06 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*	@(#)sqz.h 1.4 89/08/31 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

#ifndef _sun_sqz_h
#define	_sun_sqz_h

#include <sys/ioccom.h>

struct sqz_status {
	int count;
	int total;
};

#define	SQZSET	_IOW(q, 1, int)
#define	SQZGET	_IOR(q, 2, struct sqz_status)

#endif /*!_sun_sqz_h*/
