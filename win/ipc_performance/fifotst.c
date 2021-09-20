/* Test time: 109.3u 17.5s 2:24 87% 0+264k 0+0io 0pf+0w */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

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
	int		fd;/* FIFO file descriptor */
	int             pid,
	                length;
	static const int ITERATIONS = 10000000;

	printf ("Creating the FIFO...");
	fflush (stdout);
	if (mkfifo (SERVER_FIFO, 0666) < 0)
	{
		perror ("mkfifo()");
		exit (1);
	}
	printf ("FIFO created.");
	fflush (stdout);
	bufsiz = pathconf (SERVER_FIFO, _PC_PIPE_BUF);
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
		if ((fd = open ( SERVER_FIFO, O_WRONLY))== -1)
		{
			perror ("open()");
			exit(1);
		}
	/* Child */
		(void) strcpy (message, "This is the message");
		length = strlen (message);

		printf ("Child writing message length to the pipe.  length = %d.\n", length);
		fflush (stdout);
		write (fd, &length, sizeof (int));	/* write the length */
		printf ("Child writing message to the pipe.  message = \"%s\".\n", message);
		fflush (stdout);
		write (fd, message, length);	/* write the message */
		for (idx = 0; idx < ITERATIONS; idx++);
		{
			sprintf (message, "%d", idx);
			length = strlen (message);
			write (fd, &length, sizeof (int));
			write (fd, message, length);
		}
		printf ("Child (writer).  idx = %d; message = %s length = %d\n",
			idx, message, length);
		exit (0);
	}
	else
	{
		printf ("Executing parent code.\n");
		fflush (stdout);
		if ((fd = open ( SERVER_FIFO, O_RDONLY))== -1)
		{
			perror ("open()");
			exit(1);
		}
	/* Parent */
		memset (message, '\0', bufsiz);

		read (fd, &length, sizeof (int));	/* read the length */
		read (fd, message, length);	/* read the message */

		printf ("Parent read the following message:\n\t\"%s\"\n", message);
		fflush (stdout);
		for (idx = 0; idx < ITERATIONS; idx++);
		{
			read (fd, &length, sizeof (int));
			read (fd, message, length);
		}
		printf ("Parent (reader).  idx = %d; message = %s length = %d\n",
			idx, message, length);
	}
	unlink (SERVER_FIFO);
}

/*
 * Just remember to convert byte order if the reader and writer run on
 * processors with differing Endian-ness.
 * 
 * -- Fester
 */
