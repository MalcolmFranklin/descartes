#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>      /* perror() */
#include <unistd.h>
#include <fcntl.h>      /* O_RDONLY - file open mode */
#include <sys/wait.h>   /* wait(), waitpid() */
#include "semops.h"     /* Semaphore operations */
#include "some_utils.h" /* util_abort() */
#include "hash.h"       /* Needed by fifo.h */
#include "fifo.h"

void            flprintf (char *printf_fmt_str,...)
{
    va_list         arguments;

    va_start (arguments, printf_fmt_str);
    vfprintf (stdout, printf_fmt_str, arguments);
    fflush (stdout);
    va_end (arguments);
}
static void     sub_client (shared_fifodata_tt *parent2child,
                                            int mutex)
{
    char            child_pidstr[INTLEN];
    char            message[1024];
    reply_fifodata_tt *child2parent = NULL;
    const char     *reply_ptr;
    size_t          reply_len;
    server_command_tt command;
    int             shared;

    sprintf (child_pidstr, "%d", getpid ());
    flprintf ("Sub-Child created.  PID = %s\n", child_pidstr);
    connect_to_parent (parent2child, child_pidstr, &child2parent);
    message[0] = '\0';
/* Begin critical section. */
    sem_wait (mutex);
    send2parent (parent2child, SRV_GET_VAL, message);
    command = receive_fm_parent (child2parent, &reply_len);
    reply_ptr = reply_fifo_data (child2parent);
    shared = atoi (reply_ptr);
    ++shared;
    sprintf (message, "%d", shared);
    send2parent (parent2child, SRV_SET_VAL, message);
    sem_signal (mutex);
/* End critical section. */
    flprintf ("shared = %d in sub-child %d.\n",
              shared, getpid ());
    destroy_child2parent (child2parent);
    free (child2parent);
    exit (0);
}

#define NUM_SUBCHILD    3
void            client (shared_fifodata_tt *parent2child, int mutex)
{
    char            child_pidstr[INTLEN], message[1024] = {'\0'};
    reply_fifodata_tt *child2parent = NULL;
    const char     *reply_ptr;
    size_t          reply_len;
    server_command_tt command;
    int             subchild_cnt = 0;
    int             shared;

    sprintf (child_pidstr, "%d", getpid ());
    flprintf ("Child created.  PID = %s\n", child_pidstr);
    connect_to_parent (parent2child, child_pidstr, &child2parent);
/* Begin critical section. */
    sem_wait (mutex);
    send2parent (parent2child, SRV_GET_VAL, message);
    command = receive_fm_parent (child2parent, &reply_len);
    reply_ptr = reply_fifo_data (child2parent);
    shared = atoi (reply_ptr);
    ++shared;
    sprintf (message, "%d", shared);
    send2parent (parent2child, SRV_SET_VAL, message);
    sem_signal (mutex);
/* End critical section. */
    while (subchild_cnt < NUM_SUBCHILD) {
        if (fork () == 0)
            sub_client (parent2child, mutex);
        else
            subchild_cnt++;
    }
/* Wait for sub-processes to finish. */
    while (subchild_cnt > 0) {
        flprintf ("Sub-client %d completed\n", wait (0));
        --subchild_cnt;
    }
    message[0] = '\0';
    send2parent (parent2child, SRV_SHUTDOWN, message);
    destroy_child2parent (child2parent);
    free (child2parent);
    exit (0);
}
void            server (shared_fifodata_tt *parent2child,
                        int shared)
{
    char            child_pidstr[INTLEN];
    server_command_tt command;
    const char     *dataptr;
    char           *buf;
    size_t          datalen;
    int             old_val;

    flprintf ("Executing parent code.\n");

/* All children write to the parent2child FIFO. */
    open_parent2child_fifo (parent2child, O_RDONLY);
    if ((buf = malloc (shared_fifo_bufsiz (parent2child))) == NULL)
        util_abort (__LINE__, __FILE__, "malloc() failed.\n");

    do {
        command = receive_fm_child (parent2child, child_pidstr,
                                    &datalen);
        dataptr = shared_fifo_data (parent2child);

        switch (command) {
            case SRV_CONNECT:
                flprintf ("SRV_CONNECT: Parent received a connect "
                   "message from %s.\n", child_pidstr);
                parent_open_reply_fifo (parent2child, child_pidstr);
                break;

            case SRV_GET_VAL:
                sprintf (buf, "%d", shared);
                send2child (parent2child, child_pidstr,
                            command, buf);
                break;

            case SRV_SET_VAL:
                old_val = shared;
                shared = atoi (dataptr);
                flprintf ("Process %s changed shared from %d "
                          "to %d.\n",child_pidstr, old_val, shared);
                break;

            case SRV_SHUTDOWN:
                flprintf ("SRV_SHUTDOWN: Received from %s.\n",
                          child_pidstr);
                break;
        }
    } while (command != SRV_SHUTDOWN);
    destroy_fifos (parent2child);
    free (buf);
}

shared_fifodata_tt *parent2child;
int             main (void)
{
    char            parent_pidstr[INTLEN];/* String representation
                                           * of the parent process
                                           * ID. */
    pid_t           pid;    /* Process ID returned from fork() */
    int             shared = 0;     /* A value to be shared
                                         * by all sub-processes. */
    int             mutex = sem_create (); /* Semaphore protecting
                                            * shared. */

    sprintf (parent_pidstr, "%d", (int) getpid ());
    parent2child = init_parent2child_fifo (parent_pidstr);

    if ((pid = fork ()) == -1) {
        perror ("Erron in fork()");
        exit (-1);
    }
    else if (pid == 0)
        client (parent2child, mutex);   /* Child */
    else
        server (parent2child, shared);      /* Parent */

    return (0);
}
