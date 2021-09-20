/* csh time: 107.3u 20.0s 2:28 85% 0+272k 0+0io 0pf+0w */
/* /usr/5bin real     2:14.2, user     1:49.9, sys        15.4 */
/*******************************************************************************
>The hard part seems to be making sure that the reader gets a complete message,
>and NO MORE than a single complete message.  If I could solve this, I could
>create a linked-list of received messages, and provide a function call to
>either fetch a message from the list, or block until another process writes
>a message.

This is easy. Write the 2 or 4 bytes of length immediately in front of the
message, then write the message. The reader will then read the 2 or 4 bytes
of length and then read (length) bytes from the pipe/FIFO. You're guaranteed
to read only one complete message. I do this with most of my socket/pipe
communications.
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#define SERVER_FIFO "SERVER_FIFO"      /* Filename of the FIFO that children use to send requests to server process */

/*
 * All messages to server are prefaced by a string containing the child
 * process pid, followed by a character which identifies the specific
 * request.  ex: "27191 c" tells the server to open a reply connection to a
 * child whose pid is 27191.  The filename used for the return connection is
 * the string reperesentation of the pid.  Sever must handle SIGPIPE signals
 * to decrement the number of active child processes, otherwise it will
 * shudtown a FIFO which other subprocesses are using. Server opens FIFO in
 * read-write mode,  This number of children counter must be declared
 * "volatile".   Writes to a FIFO are guaranteed to be atomic, as long as
 * they are less than PIPE_BUF bytes in size.
 * 
 * Name of FIFO is determined by a call to tmpnam(), which is guaranteed to
 * return a unique value.  This must be done before making any calls to for
 */
/* Needs: sys/types.h sys/stat.h  fd = mkfifo (SERVER_FIFO, mode); */
void            main ()
{
	char            *message;
	int		bufsiz;
	int		idx;
	int             pid,
	                length,
	                pipe_d[2];

	printf ("Creating the pipe...");
	fflush (stdout);
	if (pipe (pipe_d) < 0)
	{
		perror ("pipe");
		exit (1);
	}
	printf ("Pipe created.");
	fflush (stdout);
	bufsiz = fpathconf (pipe_d[0], _PC_PIPE_BUF);
	printf ("  bufsiz = %d\n", bufsiz);
	fflush(stdout);
	if ( (message = malloc (bufsiz)) == NULL)
	{
		perror("malloc()");
		exit(1);
	}
	if ((pid = fork ()) == -1)
	{
		perror ("Erron in fork()");
		exit (-1);
	}
	else if (pid == 0)
	{
		printf ("Child created.\n");
		fflush (stdout);
	/* Child */
		(void) strcpy (message, "This is the message");
		length = strlen (message);

		printf ("Child writing message length to the pipe.  length = %d.\n", length);
		fflush (stdout);
		write (pipe_d[1], &length, sizeof (int));	/* write the length */
		printf ("Child writing message to the pipe.  message = \"%s\".\n", message);
		fflush (stdout);
		write (pipe_d[1], message, length);	/* write the message */
		for (idx = 0; idx < 1000000000; idx++);
		{
			sprintf (message, "%1024d", idx);
			length = strlen (message);
			write (pipe_d[1], &length, sizeof (int));
			write (pipe_d[1], message, length);
		}
		printf ("Child (writer).  idx = %d; message = %s length = %d\n",
			idx, message, length);
		exit (0);
	}
	else
	{
		printf ("Executing parent code.\n");
		fflush (stdout);
	/* Parent */
		memset (message, '\0', bufsiz);

		read (pipe_d[0], &length, sizeof (int));	/* read the length */
		read (pipe_d[0], message, length);	/* read the message */

		printf ("Parent read the following message:\n\t\"%s\"\n", message);
		fflush (stdout);
		for (idx = 0; idx < 1000000000; idx++);
		{
			read (pipe_d[0], &length, sizeof (int));
			read (pipe_d[0], message, length);
		}
		printf ("Parent (reader).  idx = %d; message = %s length = %d\n",
			idx, message, length);
	}
}

/*
 * Just remember to convert byte order if the reader and writer run on
 * processors with differing Endian-ness.
 * 
 * -- Fester
 */
