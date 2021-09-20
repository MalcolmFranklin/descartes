/* @(#) solkbd.h 1.1@(#) Solbourne id 9/22/93 00:08:21 */
/*
 * Copyright 1990 Solbourne Computer, Inc.
 * All rights reserved.
 */

/*
 * Header file for Solbourne Computer keyboard routines
 *
 * On Solbourne keyboards, the keycodes are transmitted on a serial line
 * at ~9600 baud.
 */

/*
 * special characters that might show up on port from a PC AT style keyboard
 */
#define	KB_KEYBREAK	0xF0	/* Next byte will indicate a key released */
#define	KB_CMDACK	0xFA	/* Acknowledge for a command from host */
#define	KB_DIAGFAIL	0xFC	/* Power on diagnostics failed */
#define	KB_RESETFAIL	0xFD	/* Reset diagnostics failed */
#define	KB_RESEND	0xFE	/* Keyboard received unrecognizable command */
#define	KB_TESTOK	0xAA	/* Keyboard passed self test */
#define	KB_OVERRUN	0x00	/* Keyboard buffer full or keyboard error */

/*
 * Keyboard ID bytes for PC AT compatible keyboards,
 * and Solbourne custom keyboards
 */
#define	KB_AT101PFX	0xAB	/* First byte of PC AT protocol keyboard ID */
#define	KB_AT101	0x83	/* Second byte of PC AT 101 key keyboard ID */
#define	KB_SKB1		0x9E	/* Second byte of Solbourne-1 keyboard ID */
#define	KB_SKB2		0xA8	/* Second byte of Solbourne-2 keyboard ID */

/*
 * layout bytes for Solbourne keyboards
 */
#define	KBD_US_LAYOUT	0x00	/* Standard Solbourne-2 keyboard layout */

/*
 * Commands to the PC AT keyboard 
 * A command to the AT keyboard always gets an ACK byte in response 
 * except for ECHO, RESEND, INVAL1 and INVAL2 commands.
 */
#define	KBD_CMD_LEDS		0xED	/* Next byte sent will control LEDs */
#define	KBD_CMD_ECHO		0xEE	/* Echo this byte back from keyboard */
#define	KBD_CMD_INVAL1		0xEF	/* Keyboard responds with a RESEND */
#define	KBD_CMD_SELMODE		0xF0	/* Next byte sent will select keycode mode */
#define	KBD_CMD_INVAL2		0xF1	/* Keyboard responds with a RESEND */
#define	KBD_CMD_READID		0xF2	/* Keyboard will send 2 byte ID code */
#define	KBD_CMD_SETRATE		0xF3	/* Next byte sent will set repeat rate/delay */
#define	KBD_CMD_ENABLE		0xF4	/* Enable the keyboard */
#define	KBD_CMD_DISABLE		0xF5	/* Disable the keyboard */
#define	KBD_CMD_DEFAULT		0xF6	/* Set keyboard to power on default state */
#define	KBD_CMD_SAMREP		0xF7	/* Set all keys send make, repeat */
#define	KBD_CMD_SAMB		0xF8	/* Set all keys send make/break, no repeat */
#define	KBD_CMD_SAM		0xF9	/* Set all keys send make, no repeat */
#define	KBD_CMD_SAMBREP		0xFA	/* Set all keys send make/break, repeat */
#define	KBD_CMD_SOMREP		0xFB	/* Set one key send make, repeat (next byte sent is key) */
#define	KBD_CMD_SOMB		0xFC	/* Set one key send make/break, no repeat */
#define	KBD_CMD_SOM		0xFD	/* Set one key send make, no repeat */
#define	KBD_CMD_RESEND		0xFE	/* Keyboard will resend last byte sent */
#define	KBD_CMD_ATRESET		0xFF	/* Keyboard will do power up reset and self test */

/*
 * commands to the Solbourne-1 keyboard, it also accepts all PC AT
 * keyboard commands
 */
#define	KBD_CMD_CLICKON		0xEA	/* turn keyclick on */
#define	KBD_CMD_CLICKOFF 	0xEB	/* turn keyclick off */
#define	KBD_CMD_RBELL		0xEC	/* sound the bell tone */

/*
 * LED bits for PC AT keyboard, if bit set => led is on
 */
#define	AT_LED_SCROLL	0x01	/* Scroll Lock */
#define	AT_LED_NUM	0x02	/* Num Lock led */
#define	AT_LED_CAPS	0x04	/* Caps Lock led */
#define	AT_LED_COMPOSE	0x08	/* Compose led */

/*
 * leds on a Solbourne-1 keyboard
 */
#define	SKB1_LEDS	(AT_LED_SCROLL|AT_LED_NUM|AT_LED_CAPS)

/*
 * leds on a Solbourne-2 keyboard
 */
#define	SKB2_LEDS	(AT_LED_SCROLL|AT_LED_NUM|AT_LED_CAPS|AT_LED_COMPOSE)

/*
 * Keyboard mode codes for PC AT keyboard
 */
#define	MODE_XT		0x01	/* Run keyboard in XT mode */
#define	MODE_AT		0x02	/* Run keyboard in AT mode */
#define	MODE_HN		0x03	/* Run keyboard in HN mode */
#define	MODE_INQUIRY	0x00	/* Ask keyboard to send mode currently in use */

#define	MAX_KEYS_DOWN	32	/* max # of keyboard keys pressed at same time */

struct kbdstate {
	u_char	id;		/* keyboard id */
	u_char	cmd;		/* current command going to keyboard */
	u_char	flags;		/* misc keyboard state flags */
	u_char	zsflags;	/* misc keyboard state zs level flags */
	u_char	charstate;	/* character xmit state */
	u_char	numdown;	/* number of keys down */
	u_char	xtrachar;	/* if soltosunkbd returns 2, this is 2nd char */
	u_char	resendcnt;	/* count of num of resends kbd has requested */
	u_char	kbd_keysdown[MAX_KEYS_DOWN];
};

/*
 * keyboard state flags
 */
#define	KBD_EXTRAKEYS	0x01	/* enable solbourne type 3 kbd extra keys */
#define	KBD_LEDSNEXT	0x02	/* next sun command byte is led state */
#define	KBD_PASSTHRU	0x10	/* pass next command byte thru to kbd */
#define	KBD_IDNEXT	0x40	/* next byte is keyboard id */

/*
 * keyboard zs state flags, must protect with splzs and zs_lock
 */
#define	ZS_KBD_2BYTECMD		0x01	/* 1st byte of a 2 byte cmd has been sent */
#define	ZS_KBD_CMDWAIT		0x20	/* wait for command completion */
#define	ZS_KBD_BREAKSEEN	0x04	/* last byte from kbd was key break prefix */

#define	KBD_CLEARFLAGS (KBD_LEDSNEXT|KBD_PASSTHRU|KBD_IDNEXT)

/*
 * misc keyboard defines
 */
#define	KBD_QEND	0	/* put command at end of queue */
#define	KBD_QFRONT	1	/* put command at front of queue */
#define	KBD_MAX_RESEND	16	/* max no. of resends to allow */
#define	MAX_KBDS	64	/* max # of keyboard ids supported */

/*
 * States of keyboard character transmitter
 */
#define	ZS_KBD_IDLE		0	/* keyboard xmit state machine idle */
#define	ZS_KBD_SENDCHAR		1	/* requesting the keyboard interface */
#define	ZS_KBD_CTSWAIT		2	/* waiting for CTS */
#define	ZS_KBD_CHAROUT		4	/* character xmit in progress */
#define	ZS_KBD_ACKWAIT		8	/* character sent, waiting for ack */

