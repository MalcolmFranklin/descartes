/* @(#) saio.h 1.1@(#) Solbourne id 9/22/93 00:07:33 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

#ifndef _SAIO_
#define _SAIO_

#include <sys/ioccom.h>
#include <dev/scsi.h>

/*
 * Structures and definitions for scsi user io control commands
 */

/*
 * Structures used as data by ioctl calls.
 */

/*
 * Used to bind an unit to a scsi target
 */
#define	SA_IO_BIND	_IOW(u, 0, struct sa_bind)	/* Bind to device */
struct sa_bind {
	u_char	sa_bind_target;		/* scsi target id to bind */
	u_char	sa_bind_lun;		/* lun of target to bind */
	int	sa_bind_flags;
#define		  SA_BIND_FLAGS_SILENT	0x01	/* no error messages */
#define		  SA_BIND_FLAGS_DISCON	0x02	/* allow disconnect */
#define		  SA_BIND_FLAGS_SYNCH	0x04	/* allow synchronous */
#define		  SA_BIND_FLAGS_PARITY	0x08	/* allow parity */
#define		  SA_BIND_FLAGS_NON_MUX	0x10	/* non-multiplexed device */
#define		  SA_BIND_FLAGS_MSG_CC	0x20	/* only supports cmd complete */
	int	sa_bind_blksize;
};

/*
 * Used for commands
 */
#define	SA_IO_CMD	_IOWR(u, 1, struct sa_cmd)	/* issue cmd */
struct sa_cmd {
	union scsi_cdb	*sa_cmd_cdb;		/* scsi command block */
	caddr_t		sa_cmd_bufaddr;		/* user's buffer address */
	u_int		sa_cmd_buflen;		/* size of user's buffer */
	short		sa_cmd_ctlb_flags;	/* command flags for */
						/* non-standard commands. */
						/* see scsi.h ctlb_flags...*/
	short		sa_cmd_timeout;		/* time for completion */
	int		sa_cmd_error_class;	/* see scsi_var.h */
	int		sa_cmd_error_code;	/* host adaptor specific */
	union scsi_scb	*sa_cmd_scb;		/* execution status */
};
#endif !_SAIO_

