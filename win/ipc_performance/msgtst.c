#undef _POSIX_SOURCE /* SysV message queues are not in POSIX.1-1990 */
/*******************************************************************************
 * $Date: 1994/06/30 22:15:24 $
 * $State: Exp $
 * $Locker: franklin $
 * $Source: /all/franklin/thesis/descartes/win/RCS/msg.c,v $
 *
 **-M**************************************************************************/

#if 0
/******************************************************************************
 *
$Log: msg.c,v $
 * Revision 1.10  1994/06/30  22:15:24  franklin
 * Print more information when you get a nonsensical message.
 *
 * Revision 1.9  1994/06/02  17:23:46  franklin
 * Enable stricter type checking when running the CenterLine "clcc" in
 * K&R compatibility mode (-Xa switch) by re-defining __STDC__ after processing
 * the non-ansi SunOS system include files.
 *
 * Revision 1.8  1994/06/01  16:41:00  franklin
 * Undefine _POSIX_SOURCE for now, until we replace the SysV message queues.
 *
 * Revision 1.7  1994/05/19  23:55:57  franklin
 * Report more informative diagnostic messages when a message
 * operation fails.
 *
 * Revision 1.6  1994/05/16  22:43:58  franklin
 * break assignment out of "if" statement.
 *
 * Revision 1.5  1994/05/03  00:55:59  franklin
 * #include mesg.h to make sure prototypes are valid.
 * Use perror() instead of printf() to report that system calls exited with
 * a failure status.
 *
 * Revision 1.4  1994/04/14  22:50:01  franklin
 * Run through "indent".
 *
 * Revision 1.3  1994/04/14  19:12:47  franklin
 * Convert function signatures to ANSI/ISO standard.  (Object Center detected
 * that I had not done this yet; gcc -ansi -pedantic let it pass by.
 *
 * Revision 1.2  1994/04/08  01:07:03  franklin
 * Run through SunOS 4.1.3 "indent" program
 *
 ******************************************************************************/
#endif
static char    *msg_c_rcsid = "@(#) $Id: msg.c,v 1.10, h4_3_1 1994/06/30 22:15:24 franklin Exp franklin $";

#include <stdio.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
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

#include "mesg.h"

/* 
 * Malcolm:  When you update this function, have it send mega-big messages
 * in multiple parts, if need be.  Make it handle arbitrary-length messages.
 */
void            mesg_send (int id, Mesg * mesgptr)
{
	int n;

	n = msgsnd (id, (char *) &(mesgptr->mesg_type), mesgptr->mesg_len, 0);
	if (n != 0)
	{
		perror ("msgsnd() error in mesg_send()");
		printf ("Line %d of \"%s\": msgsnd() error; message_len == %d"
			" (nonzero).\n", __LINE__, __FILE__, n);
	}
}

int             mesg_recv (int id, Mesg * mesgptr)
{
	int             n;

	n = msgrcv (id, (char *) &(mesgptr->mesg_type), MAXMESGDATA, mesgptr->mesg_type, 0);
	if (n < 0)
	{
		perror ("msgrcv() error in mesg_recv()");
		printf ("Line %d of \"%s\": msgrcv() error; message_len == %d"
			" (less than zero length).\n", __LINE__, __FILE__, n);
		printf ( "\tmsgrcv() returned = %d; message type = %d\n",
			 n, mesgptr->mesg_type);

	}

	mesgptr->mesg_len = n;
	return (n);
}

int             mesg_arecv (int id, Mesg * mesgptr)
{
	int             n;

	n = msgrcv (id, (char *) &(mesgptr->mesg_type), MAXMESGDATA, mesgptr->mesg_type, IPC_NOWAIT);
	if (n < 0)
	{
		perror ("msgrcv() error in mesg_arecv()");
		printf ("Line %d of \"%s\": msgrcv() error; message_len == %d"
			" (less than zero length).\n", __LINE__, __FILE__, n);
	}

	mesgptr->mesg_len = n;
	return (n);
}

#define MSGKEY   ((key_t) 7801L)
#define ITERATIONS 10000000
void client ()
{
	Mesg            mesg_d;
	int		msgid;
	int		idx;

	if ((msgid = msgget (MSGKEY, 0)) < 0)
	{
		perror ("msgget (MSGKEY, 0)");
		printf ("Client failed to open message queue.\n");
		exit(-1);
	}
	sprintf (mesg_d.mesg_data, "This is the message");
	mesg_d.mesg_len = strlen (mesg_d.mesg_data);
	mesg_d.mesg_type = 1L;
	mesg_send (msgid, &mesg_d);
	for (idx = 0; idx < ITERATIONS; idx++)
	{
		sprintf (mesg_d.mesg_data, "%1024d", idx);
		mesg_d.mesg_len = strlen (mesg_d.mesg_data);
		mesg_send (msgid, &mesg_d);
	}
	exit(0);
}
void server ()
{
	Mesg            mesg_d;
	int		n;
	int		msgid;
	int		idx;
	
	if ((msgid = msgget (MSGKEY, 0)) < 0)
	{
		perror ("msgget (MSGKEY, 0)");
		printf ("Server failed to open message queue.\n");
		exit(-1);
	}
	mesg_d.mesg_type = 0L;
	if ((n = mesg_recv (msgid, &mesg_d)) <= 0)
	{
		printf ("message read error \n");
		n = 0;
	}
	mesg_d.mesg_data[n] = '\0';
	printf("Received \"%s\"\n", mesg_d.mesg_data);
	for (idx = 0; idx < ITERATIONS; idx++)
	{
		if ((n = mesg_recv (msgid, &mesg_d)) <= 0)
		{
			printf ("message read error \n");
			n = 0;
		}
		mesg_d.mesg_data[n] = '\0';
	}
}
int main (void)
{
        pid_t           pid;           /* Process ID returned from fork() */
	int		msgid;
	if ((msgid = msgget (MSGKEY /* + 1 */, 0666 | IPC_CREAT)) < 0)
	{
		perror ("msgget((MSGKEY + 1, 0)");
		exit(-1);
	}
	
        if ((pid = fork ()) == -1)
        {
                perror ("Erron in fork()");
                exit (-1);
        }
        else if (pid == 0)
                client ();  /* Child */
        else
                server ();  /* Parent */

	if (msgctl (msgid, IPC_RMID, (struct msqid_ds *) 0) < 0)
	{
		perror("msgctl(msgid, IPC_RMID, (struct msqid_ds *) 0)");
		printf ("can not remove message queue\n");
	}
        return (0);
}
