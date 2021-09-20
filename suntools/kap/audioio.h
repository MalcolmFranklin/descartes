/* @(#) audioio.h 1.1@(#) Solbourne id 9/22/93 00:02:56 */
/*
 * Copyright 1991 Solbourne Computer, Inc.
 * All rights reserved.
 */
/*	@(#)audioio.h 1.2 90/12/05 SMI	*/
/* Copyright (c) 1989 by Sun Microsystems, Inc. */

/*
 * These are the ioctl calls for generic audio devices, including
 * the SPARCstation 1 audio device.
 *
 * You are encouraged to design your code in a modular fashion so that
 * future changes to the interface can be incorporated with little trouble.
 */

#ifndef _sun_audioio_h
#define	_sun_audioio_h


/*
 * This structure contains state information for play or record streams.
 */
typedef struct audio_prinfo {
	/*
	 * The following values describe the audio data encoding.
	 * They are read-only for SPARCstation audio, but may be
	 * dynamically configurable for other audio devices.
	 */
	unsigned	sample_rate;	/* sample frames per second */
	unsigned	channels;	/* number of interleaved channels */
	unsigned	precision;	/* bits per sample */
	unsigned	encoding;	/* data encoding method */

	/* The following values control audio device configuration */
	unsigned	gain;		/* gain level: 0 - 255 */
	unsigned	port;		/* selected I/O port (see below) */
	unsigned	_xxx[4];	/* Reserved for future use */

	/* The following values describe driver state */
	unsigned	samples;	/* number of samples converted */
	unsigned	eof;		/* number of EOF records (play only) */
	unsigned char	pause;		/* TRUE to pause, FALSE to resume */
	unsigned char	error;		/* TRUE if overflow/underflow */
	unsigned char	waiting;	/* TRUE if a process wants access */
	unsigned char	_ccc[3];	/* Reserved for future use */

	/* The following values are read-only state flags */
	unsigned char	open;		/* TRUE if access requested at open */
	unsigned char	active;		/* TRUE if HW I/O active */
} audio_prinfo_t;

/*
 * This structure describes the current state of the audio device.
 */
typedef struct audio_info {
	audio_prinfo_t	play;		/* output status information */
	audio_prinfo_t	record;		/* input status information */
	unsigned	monitor_gain;	/* input to output mix: 0 - 255 */
	unsigned	_yyy[4];	/* Reserved for future use */
} audio_info_t;


/* Audio encoding types */
#define	AUDIO_ENCODING_ULAW	(1)	/* u-law encoding */
#define	AUDIO_ENCODING_ALAW	(2)	/* A-law encoding (not supported yet) */

/* These ranges apply to record, play, and monitor gain values */
#define	AUDIO_MIN_GAIN	(0)		/* minimum gain value */
#define	AUDIO_MAX_GAIN	(255)		/* maximum gain value */

/* Define some possible 'port' values */
#define	AUDIO_PORT_A	(1)		/* define generic port names */
#define	AUDIO_PORT_B	(2)
#define	AUDIO_PORT_C	(3)
#define	AUDIO_PORT_D	(4)

/* Define some convenient names for SPARCstation audio ports */
#define	AUDIO_SPEAKER	AUDIO_PORT_A	/* output to built-in speaker */
#define	AUDIO_HEADPHONE	AUDIO_PORT_B	/* output to headphone jack */
#define	AUDIO_MICROPHONE AUDIO_PORT_A	/* input from microphone */

/*
 * This macro initializes an audio_info structure to 'harmless' values.
 * Note that (~0) might not be a harmless value for a flag that was signed int.
 */
#define	AUDIO_INITINFO(i)	{					\
	unsigned	*__x__;						\
	for (__x__ = (unsigned *)(i);					\
	    (char *) __x__ < (((char *)(i)) + sizeof (audio_info_t));	\
	    *__x__++ = ~0);						\
}


/*
 * Ioctl calls for the audio device.
 */

/*
 * AUDIO_GETINFO retrieves the current state of the audio device.
 *
 * AUDIO_SETINFO copies all fields of the audio_info structure whose values
 * are not set to the initialized value (-1) to the device state.  It performs
 * an implicit AUDIO_GETINFO to return the new state of the device.  Note that
 * the record.samples and play.samples fields are set to the last value before
 * the AUDIO_SETINFO took effect.  This allows an application to reset the
 * counters while atomically retrieving the last value.
 *
 * AUDIO_DRAIN suspends the calling process until the write buffers are empty.
 */
#define	AUDIO_GETINFO		_IOR(A, 1, audio_info_t)
#define	AUDIO_SETINFO		_IOWR(A, 2, audio_info_t)
#define	AUDIO_DRAIN		_IO(A, 3)


/*
 * XXX - The following are defined for binary compatibility with Release 4.0.3c.
 *	 They will not be supported in future releases.
 */
#ifdef AUDIO_4_0_3_COMPAT
/*
 * READSTART tells the device driver to start reading sound.  This is
 * useful for starting recordings when you don't want to call read()
 * until later.  STOP stops all i/o and clears the buffers, while
 * PAUSE stops i/o without clearing the buffers.  RESUME resumes i/o
 * after a PAUSE.  These ioctl's don't transfer any data.
 */
#define	AUDIOREADSTART		_IO(1, 3)
#define	AUDIOSTOP		_IO(1, 4)
#define	AUDIOPAUSE		_IO(1, 5)
#define	AUDIORESUME		_IO(1, 6)

/*
 * READQ is the number of bytes that have been read but not passed to
 * the application.  WRITEQ is the number of bytes passed into
 * the driver but not written to the device.  QSIZE is the number of bytes
 * in the queue.
 */
#define	AUDIOREADQ		_IOR(1, 7, int)
#define	AUDIOWRITEQ		_IOR(1, 8, int)
#define	AUDIOGETQSIZE		_IOR(1, 9, int)
#define	AUDIOSETQSIZE		_IOW(1, 10, int)

#endif /*AUDIO_4_0_3_COMPAT*/

#endif /*!_sun_audioio_h*/
