/* @(#) z8530reg.h 1.1@(#) Solbourne id 9/22/93 00:10:09 */
/*
 * Copyright 1988 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*
 * defines for Z8530 SCC registers
 */

#define	CH_A		0	/* channel A of 8530 */
#define	CH_B		1	/* channel B of 8530 */

#define	RR0		0	/* Read register 0 */
#define	RR1		1	/* Read register 1 */
#define	RR2		2	/* Read register 2 */
#define	RR3		3	/* Read register 3 */
#define	RR4		4	/* Read register 4 */
#define	RR5		5	/* Read register 5 */
#define	RR6		6	/* Read register 6 */
#define	RR7		7	/* Read register 7 */
#define	RR8		8	/* Read register 8 */
#define	RR9		9	/* Read register 9 */
#define	RR10		10	/* Read register 10 */
#define	RR11		11	/* Read register 11 */
#define	RR12		12	/* Read register 12 */
#define	RR13		13	/* Read register 13 */
#define	RR14		14	/* Read register 14 */
#define	RR15		15	/* Read register 15 */

#define	WR0		0	/* Write register 0 */
#define	WR1		1	/* Write register 1 */
#define	WR2		2	/* Write register 2 */
#define	WR3		3	/* Write register 3 */
#define	WR4		4	/* Write register 4 */
#define	WR5		5	/* Write register 5 */
#define	WR6		6	/* Write register 6 */
#define	WR7		7	/* Write register 7 */
#define	WR8		8	/* Write register 8 */
#define	WR9		9	/* Write register 9 */
#define	WR10		10	/* Write register 10 */
#define	WR11		11	/* Write register 11 */
#define	WR12		12	/* Write register 12 */
#define	WR13		13	/* Write register 13 */
#define	WR14		14	/* Write register 14 */
#define	WR15		15	/* Write register 15 */
#define	N8530WREGS	16	/* no. of write registers on 8530 */
/*
 * bits in RR0
 */
#define	SC_CTS		0x20	/* set if CTS pin is low */
#define	SC_RCA		0x01	/* set if character available in input silo */
#define	SC_TBE		0x04	/* set if transmit buffer is empty */
#define	SC_DCD		0x08	/* data carrier detect */
/*
 * bits in RR2 (channel B)
 */
#define	SC_CHANA	0x08	/* this bit set if channel A interrupt */
#define	SC_INTMSK	0x0e	/* mask to isolate interrupt status bits */
#define	SC_SRCINT	0x06	/* special receive condition interrupt */
#define	SC_TXEINT	0x00	/* transmit buffer empty interrupt */
#define	SC_RCAINT	0x04	/* receive character available interrupt */
/*
 * bits in RR1
 */
#define	SC_FE		0x40	/* framing error */
#define	SC_PE		0x10	/* parity error */
#define	SC_OV		0x20	/* overrun error */

/*
 * bits in WR0
 */
#define	SC_PTHI		0x08	/* point at high registers */
#define	SC_REXST	0x10	/* reset external/status interrupts */
#define	SC_ERRRST	0x30	/* error reset */
/*
 * bits in WR1
 */
#define	SC_EIEN		0x01	/* external status interrupt enable */
#define	SC_TIEN		0x02	/* transmitter empty interrupt enable */
#define	SC_RAIEN	0x10	/* interrupt on all received characters */
#define	SC_DMA		0xe0	/* enable DMA modes */
/*
 * bits in WR3
 */
#define	SC_RBITS8	0xc0	/* receive 8 bits per character */
#define	SC_RXEN		0x01	/* enable receiver */
/*
 * bits in WR4
 */
#define	SC_ONESB	0x04	/* one stop bit */
#define	SC_PEN		0x01	/* enable parity bit */
#define	SC_OPAR		0x00	/* select odd parity */
#define	SC_EPAR		0x02	/* select even parity */
/*
 * bits in WR5
 */
#define	SC_DTR		0x80	/* set DTR pin true */
#define	SC_TBITS8	0x60	/* transmit 8 bit characters */
#define	SC_TXEN		0x08	/* enable transmitter */
#define	SC_RTS		0x02	/* set RTS pin low */
/*
 * bits in WR9
 */
#define	SC_RESETA	0x80	/* reset channel A of SCC */
#define	SC_RESETB	0x40	/* reset channel B of SCC */
#define	SC_HWRESET	0xc0	/* force hardware reset */
#define	SC_MIEN		0x08	/* master interrupt enable */
/*
 * bits in WR11
 */
#define	SC_XTAL		0x80	/* expect external crystal oscillator */
#define	SC_RCRT		0x00	/* take receive clock from RTxC pin */
#define	SC_RCBR		0x40	/* take receive clock from baud rate generator */
#define	SC_XCRT		0x00	/* take transmit clock from RTxC pin */
#define	SC_XCBR		0x10	/* take transmit clock from baud rate generator */
/*
 * bits in WR14
 */
#define	SC_BRGE		0x01	/* enable baud rate generator */
