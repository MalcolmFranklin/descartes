/* @(#) simuartreg.h 1.1@(#) Solbourne id 9/22/93 00:08:06 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*
 * simulated uart defines
 */
#ifdef S4000
# define STATUS_REG	0
# define XMIT_BUF	8
# define RECV_BUF	8
#define	XMIT_BUFFER_EMPTY	0x01
#define	RECV_BUFFER_FULL	0x02
#define	XBE_INTEN		0x04
#define	RBF_INTEN		0x08
#else
#define	UART_IO_BASE	0x17012000
# define XMIT_BUF	0x00
# define RECV_BUF	0x08
# define STATUS_REG	0x10
# define ENABLE_REG	0x18

#define	XMIT_BUFFER_EMPTY	0x01
#define	RECV_BUFFER_FULL	0x02
#define	XBE_INTEN		0x01
#define	RBF_INTEN		0x02
#endif S4000

#ifndef LOCORE
#ifdef S4000
struct succ_device {
	unsigned char	su_cmd;
	unsigned char	su_fill1[7];
	unsigned char	su_dta;
	unsigned char	su_fill2[7];
};
#define su_xmitbuf	su_dta	/* transmitter buffer */
#define su_recvbuf	su_dta	/* receiver buffer */
#define su_status	su_cmd	/* status register */
#define su_enablereg	su_cmd	/* interrupt enable register */
#else
struct succ_device {
	unsigned char	su_xmitbuf;	/* transmitter buffer */
	unsigned char	su_fill1[7];
	unsigned char	su_recvbuf;	/* receiver buffer */
	unsigned char	su_fill2[7];
	unsigned char	su_status;	/* status register */
	unsigned char	su_fill3[7];
	unsigned char	su_enablereg;	/* interrupt enable register */
};
#endif S4000

extern struct succ_device *su_struct_va;
#endif !LOCORE
