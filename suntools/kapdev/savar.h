/* @(#) savar.h 1.1@(#) Solbourne id 9/22/93 00:07:35 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

#ifndef _SAVAR_
#define _SAVAR_

#include	<dev/saio.h>

/*
 * Defines for SCSI user devices.
 */
struct scsi_user {
	u_int		sa_flags;	
#define			  SA_FLAGS_BOUND	0x0001
	struct sa_bind	sa_bind;
	u_int		sa_error_class;
};
#endif	_SAVAR_
