/*******************************************************************************
 *
 * PURPOSE:     Provide atomic wait() and signal() primitives to provide
 *              mutual exclusion among processes trying to access a shared
 *              resource.
 *
 * FUNCTIONS:
 *      EXTERNAL:       sem_create()
 *                      sem_wait()
 *                      sem_signal()
 *
 * IMPLEMENTATION:
 *              This module implements binary semaphores by placing locks on
 *              single bytes within a temporary file.  This is not terribly
 *              slower than the use of SysV semaphore operations, and unlike
 *              SysV semaphores, the file locks conform to POSIX.1-1990.
 ******************************************************************************/

#include  <stdio.h>
#include  <unistd.h>
#include  <fcntl.h>

void            error_condition (void)
{
    perror ("error_condition()");
}
static int      semaphore_count = 0;
static int      tempfile_descriptor;
static char     tempfile_name[L_tmpnam];

int             sem_create (void)
{
    int             new_sem_id;

    if (semaphore_count == 0) { /* First time called. */
        tmpnam (tempfile_name);

    /* Force creation of a new file, open for read/write.
     * Give the owner read and write privileges. see the
     * manpages for open() and stat() (in chanpter 2  i.e.
     * "man 2 open") for the definitions of the bitmask
     * values I have bitwise-OR-ed together.  */
        if ((tempfile_descriptor = open (tempfile_name,
                 O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) == -1) {
            error_condition ();
        }

    /* NOTE: With the "unlink()" call, we are ensuring that
     * the tempfile gets deleted on process termination.
     * The operating system will not actually delete the
     * file until the "unlink()"ed file is closed. The OS
     * automatically closes all files when a process
     * terminates. */
        if (unlink (tempfile_name) == -1) {
            error_condition ();
        }
    }

/* Offset of the new character is the new semaphore ID */
    new_sem_id = semaphore_count;
    ++semaphore_count;
    return (new_sem_id);
}

void            sem_wait (int id)
{
    struct flock    setlock;

    setlock.l_type = F_WRLCK;   /* Exclusive lock. */
    setlock.l_start = id * sizeof (char); /* Offset to be locked. */
    setlock.l_whence = SEEK_SET;/* Offset relative to beginning */
    setlock.l_len = sizeof (char);      /* Lock 1 byte. */

    if (fcntl (tempfile_descriptor, F_SETLKW, &setlock) < 0) {
        error_condition ();
    }
}

void            sem_signal (int id)
{
    struct flock    freelock;

    freelock.l_type = F_UNLCK;  /* Remove a lock. */
    freelock.l_start = id * sizeof (char); /* Offset to be locked. */
    freelock.l_whence = SEEK_SET; /* Offset relative to beginning */
    freelock.l_len = sizeof (char); /* Unlock 1 byte. */

    if (fcntl (tempfile_descriptor, F_SETLK, &freelock) == -1) {
        error_condition ();
    }
}

int             main (void)
{
    int             pid;
    int             semid;

    semid = sem_create ();
    printf ("tempfile_name = %s\n", tempfile_name);
    fflush (stdout);

    if ((pid = fork ()) == 0) {
        sem_wait (semid);
        printf ("Child got semaphore\n");
        fflush (stdout);
        sleep (3);
        printf ("Child releasing semaphore\n");
        fflush (stdout);
        sem_signal (semid);
	exit(0);
    }
    else {
        sem_wait (semid);
        printf ("Parent got semaphore\n");
        fflush (stdout);
        sleep (3);
        printf ("Parent releasing semaphore\n");
        fflush (stdout);
        sem_signal (semid);
    }
    return (0);
}
