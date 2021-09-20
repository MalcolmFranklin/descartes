/*******************************************************************************
 *
 * MODULE:	SEMOPS.C
 *
 * PURPOSE:	Provide atomic wait() and signal() primitives to provide
 *		mutual exclusion among processes trying to access a shared
 *		resource.
 *
 * FUNCTIONS:
 *	EXTERNAL:	sem_create()
 *			sem_wait()
 *			sem_signal()
 *			sem_delete()
 *
 * IMPLEMENTATION:
 *		This module implements binary semaphores by placing locks on
 *		single bytes within a temporary file.  This is not terribly
 *		slower than the use of SysV semaphore operations, and unlike
 *		SysV semaphores, the file locks conform to POSIX.1-1990.
 *
 * AUTHOR:	This is a rewrite of the sem.c module.  The original author is
 *		unknown.  The rewrite was by Malcolm L. Franklin, Arizona State
 *		University.
 *******************************************************************************
 * $Date: 1994/08/06 18:51:27 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/cmdline_ex/RCS/semops.c,v $
 *
 **-M**************************************************************************/

#if 0
/******************************************************************************
$Log: semops.c,v $
 * Revision 1.11  1994/08/06  18:51:27  franklin
 * sem_open() and sem_close() are not needed by the new
 * semaphore implementation.  Delete them and all calls to
 * them.
 *
 * Revision 1.10  1994/08/04  18:01:40  franklin
 * Add #includes for cchk_missing_<standard include>.h in order
 * to get prototypes that CodeCheck doesnt think are there.
 *
 * Revision 1.9  1994/07/25  00:16:05  franklin
 * Allow for OSs (like Solaris 2.x) that dont #define S_IRUSR and S_IWUSR
 * bitmask values.
 *
 * Revision 1.8  1994/06/15  19:04:36  franklin
 * Remove debugging printf() statements.
 *
 * Revision 1.7  1994/06/02  17:24:01  franklin
 * Enable stricter type checking when running the CenterLine "clcc" in
 * K&R compatibility mode (-Xa switch) by re-defining __STDC__ after processing
 * the non-ansi SunOS system include files.
 *
 * Revision 1.6  1994/05/20  20:36:36  franklin
 * The last couple of characters of the file were chopped off.
 *
 * Revision 1.5  1994/05/20  20:28:20  franklin
 * Return a dummy value from the dummy functions, for now.
 *
 * Revision 1.4  1994/05/16  20:02:27  franklin
 * Use advisory record locks, which are POSIX.1 compliant, to
 * implement binary semaphores.
 *
 ******************************************************************************
 * Log of this file while the semaphore operations were based on UNIX SYSV
 * semaphore primitives:
 *
 * Revision 1.3  1994/05/13  15:40:17  franklin
 *  sem_rm() and sem_op() are ONLY called from withing semops.c.  Define
 * them to be "static" functions (not available for linkage with functions
 * outside of this file.).
 *
 * Revision 1.2  1994/05/02  05:39:41  franklin
 * Get the declaration of errno and perror() from sunos4_missing.h
 *
 * Revision 1.1  1994/05/02  05:20:47  franklin
 * Initial revision
 *
 *
 ******************************************************************************
 * Log of this file while it was called sem.c:
 *
 * Revision 1.5  1994/05/01  23:42:50  franklin
 * Last version of this file before it was renamed
 * semops.c
 *
 * Revision 1.4  1994/04/12  13:03:01  franklin
 * 1. Convert to ANSI function signatures.
 * 2. Call "perror()" to find out why system calls no worky.
 *
 * Revision 1.3  1994/04/08  04:45:20  franklin
 * Fix compiler warnings
 *
 * Revision 1.2  1994/04/08  01:08:22  franklin
 * Run through SunOS 4.1.3 "indent" program.
 *
 ******************************************************************************/
#endif
static char    *semops_c_rcsid = "@(#) $Id: semops.c,v 1.11, h4_3_8, h4_3_7, h4_3_6, h4_3_5 1994/08/06 18:51:27 franklin Exp $";

#include  <stdlib.h>
#include "cchk_missing_stdlib.h"        /* Workaround for Spurious CodeCheck diagnostic messages. */

#include  <stdio.h>
#include  <stdarg.h>
#include  <string.h>
#include  <unistd.h>
#include "cchk_missing_unistd.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */

#include  <fcntl.h>
/******************************************************************************
 * NOTE TO FUTURE MAINTAINERS USING CenterLine "clcc" COMPILER:
 *
 * Nearly all the SunOS 4.x Operating System include files (<sys/xxx.h>)
 * cause compilation errors under a strict ANSI/ISO compiler running in anal-
 * retentive mode such as CenterLine "clcc".  In order to get these to compile,
 * with clcc, you have to pass the  -Xa (K&R C compatibility switch) to the
 * compiler.  BUT (get this) when we do this, the CenterLine preprocessor
 * #defines __STDC__ to 0 (zero); when this happens, we dont see the vararg
 * prototypes for the X functions -- and get warning messages for calling them
 * with different numbers of arguments.  On top of all this noise, we DONT GET
 * all the ANSI/ISO C type checking that we could have.
 *
 * WORKAROUND:
 *      When compiling with clcc, #define __STDC__ to 1 AFTER #including the
 * system header files you need (<sys/xxx.h>), and hopefully before #including
 * any of the header files you (or I, or Yu-Kuh, or someone else) wrote.
 * Here is the code:
 ******************************************************************************/
#ifdef __CLCC__
#ifdef __STDC__
#undef __STDC__
#endif
#define __STDC__ 1
#endif

#include "sunos4_missing.h"
#include "some_utils.h"		       /* util_abort() */
#include "semops.h"

/*******************************************************************************
 * GLOBALS
 ******************************************************************************/
static int      semaphore_count = 0;   /* Used to issue semaphore ID's.  This also happens to be the length of the tempfile.
				        * Semaphore ID's are essentially the offset of the byte in the tempfile that is either
				        * locked or unlocked, depending upon whether or not the resource it protects is in use. */
static int      semaphores_in_use;     /* Count of the number of semaphores in use in the current tempfile.  If this is
				        * decremented back to 0 by sem_delete(), then there are no more semaphores in use; so
				        * delete the tempfile. */
static int      tempfile_descriptor;   /* We are using POSIX.1 file operations, instead of ANSI/ISO C operations.  This requires
				        * the use of file descriptors rather than FILE pointers. */
static char     tempfile_name[L_tmpnam];	/* Unique file name obtained from tmpnam().  Note: L_tmpnam is defined in stdio.h */


/*******************************************************************************
 * FUNCTION:	SEM_CREATE
 *
 * PUROSE:	Create a new binary semaphore, initialized to  TRUE.  Here I
 *		mean that an unlocked byte in the tempfile == a semaphore that
 *		will allow the next requestor to have access to the resource.
 *
 * RETURN:	The "id" of the new semaphore.  In this implementation, it
 *		equals the offset of a byte in the tempfile that is either
 *		locked or unlocked.
 * USE:
 *		int new_semaphore_id;
 *
 *		new_semaphore_id = sem_create();
 ******************************************************************************/
int             sem_create (void)
{
	int             new_sem_id;    /* Return valiue */
	const static char *blank_ptr = " ";	/* Points to the byte written to the tempfile whenever a new semaphore is
						 * created. */
	mode_t          tempfile_privileges;

	if (semaphore_count == 0)	/* If this is the first time this function has been called. */
	{
		tmpnam (tempfile_name);
	/*
	 * Force creation of a new file, open for read/write.  Give the owner
	 * read and write privileges. see the manpages for open() and stat()
	 * (in chanpter 2  i.e. "man 2 open") for the definitions of the
	 * bitmask values I have bitwise-OR-ed together.
	 */
#ifndef SOLARIS2
		tempfile_privileges = S_IRUSR | S_IWUSR;
#else
		tempfile_privileges = 0600;
#endif

	
		if ((tempfile_descriptor = open (tempfile_name, O_CREAT | O_RDWR, tempfile_privileges)) == -1)
		{
			perror ("open() failed in sem_create()");
			util_abort (__LINE__, __FILE__, "Couldn't create a new file.  File name == \"%s\"; Descriptor = %d\n",
				    tempfile_name, tempfile_descriptor);
		}

	/*
	 * NOTE: With the "unlink()" call, we are ensuring that the tempfile
	 * gets deleted on process termination. The operating system will not
	 * actually delete the file until the "unlink()"ed file is closed.
	 * The OS automatically closes all files when a process terminates,
	 * so this will be taken care of even if we forget to close() it
	 * ourselves.
	 */
		if (unlink (tempfile_name) == -1)
		{
			perror ("sem_delete() could not unlink() the tempfile");
		}
	}

/*
 * Append 1 byte to the end of the tempfile and leave it unlocked (semapore
 * initialized to TRUE).  Note that you can lock byte n of a file, without the 
 * file being n bytes long.  I did this so I could tell how many semaphores
 * had been created, by getting a directory listing of the tempfile (ls -l).
 */
	if (lseek (tempfile_descriptor, semaphore_count * sizeof (char), SEEK_SET) < 0)
	{
		util_abort (__LINE__, __FILE__, "lseek() failed seeking to offset %d in file \"%s\", in sem_create().\n",
			    semaphore_count, tempfile_name);
	}
	if (write (tempfile_descriptor, blank_ptr, sizeof (char)) < 0)
	{
		util_abort (__LINE__, __FILE__, "write() to file \"%s\" failed in sem_create().  semaphore_count == %d.\n",
			    tempfile_name, semaphore_count);
	}

/*
 * Return the offset of the character you just wrote, as the ID of the new
 * semaphore.
 */
	new_sem_id = semaphore_count;
	++semaphore_count;
	++semaphores_in_use;
	return (new_sem_id);
}


/*******************************************************************************
 * FUNCTION:	SEM_WAIT
 *
 * PURPOSE:	If nobody is using the resource protected by semaphore # "id",
 *		then lock the resource, and give the caller access.  If another
 *		process is using the resource, then block the calling process
 *		until the resource is available again.
 *
 * PARAMETER:
 *	INPUT:	int id -- A semaphore id returned from sem_create().
 ******************************************************************************/
void            sem_wait (int id)
{
	struct flock    setlock;

	setlock.l_type = F_WRLCK;	/* Obtain an exclusive lock. */
	setlock.l_start = id * sizeof (char);	/* Offset of the record to lock. */
	setlock.l_whence = SEEK_SET;	/* Offset is relative to the beginning of the file. */
	setlock.l_len = sizeof (char);	/* Lock 1 byte. */

	if (fcntl (tempfile_descriptor, F_SETLKW, &setlock) < 0)
	{
		perror ("fcntl() failed in sem_wait()");
		util_abort (__LINE__, __FILE__, "Failed to get a lock for semaphore id == %d\n", id);
	}
}

/*******************************************************************************
 * FUNCTION:	SEM_SIGNAL
 *
 * PURPOSE:	Free a resource so it may be used by another process.
 *
 * PARAMETER:
 *	INPUT:	int id -- A semaphore id returned from sem_create().
 ******************************************************************************/
void            sem_signal (int id)
{
	struct flock    freelock;

	freelock.l_type = F_UNLCK;	/* Remove a lock. */
	freelock.l_start = id * sizeof (char);	/* Offset of the record to unlock. */
	freelock.l_whence = SEEK_SET;	/* Offset is relative to the beginning of the file. */
	freelock.l_len = sizeof (char);	/* Unlock 1 byte. */

	if (fcntl (tempfile_descriptor, F_SETLK, &freelock) == -1)
	{
		perror ("fcntl () failure in sem_signal()");
		util_abort (__LINE__, __FILE__, "Failed to release a lock for semaphore id == %d\n", id);
	}
}

/*******************************************************************************
 * FUNCTION:	SEM_DELETE
 *
 * PURPOSE:	Tell this module that you are done using a particular semaphore.
 *
 * PARAMETER:
 *	INPUT:	int id -- A semaphore id returned from sem_create().
 *
 * ALGORITHM:
 *	Doesn't actually care about WHICH semaphore you have deleted, but once
 *	you have deleted all that are in use, it deletes the tempfile.
 *
 * NOTE:
 *	If you don't delete semaphores when you are done with them, then this
 *	module will leave its tempfile after the program finishes.
 ******************************************************************************/
void            sem_delete (int id)
{
printf ("Called sem_delete (%d)\n", id); fflush (stdout);

	--semaphores_in_use;
	if (semaphores_in_use == 0)
	{

	/*
	 * This close will probably fail if someone still has a lock on the
	 * file.  NOTE: we "unlink()"ed the file immediately after creating
	 * it. The operating system will not actually delete the file until
	 * the file is closed.
	 */
		if (close (tempfile_descriptor) == -1)
		{
			perror ("sem_delete() could not close() the tempfile");
		}
	}
}

