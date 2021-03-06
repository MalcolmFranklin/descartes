/* IN THE CLIENT CODE: */
void            client (shared_fifodata_tt *parent2child)
{
    char            child_pidstr[INTLEN];
    char           *message;
    reply_fifodata_tt *child2parent = NULL;
    const char     *reply_ptr;
    size_t          reply_len;
    server_command_tt command;	/* Vaule from an enumerated
				 * type. */

    sprintf (child_pidstr, "%d", getpid ());
    connect_to_parent (parent2child, child_pidstr, &child2parent);

    message = malloc (shared_fifo_bufsiz (parent2child));
    sprintf (message, "sub_client's message.");
    send2parent (parent2child, SRV_ECHO, message);
    receive_fm_parent (child2parent, &reply_len);
    reply_ptr = reply_fifo_data (child2parent);

/* ... continue sending messages and getting replies ... */

/* CRITICAL only let ONE client send the shutdown message
 * to the server; call wait() once for each spawned
 * subchild. */
    sprintf (message, "");
    send2parent (parent2child, SRV_SHUTDOWN, message);
    destroy_child2parent (child2parent);
    free (child2parent);
    free (message);
    exit (0);
}


/* IN THE SERVER CODE */
void            server (shared_fifodata_tt *parent2child)
{
    char            child_pidstr[INTLEN];
    server_command_tt command;
    const char     *dataptr;	/* Points at data in the
				 * parent2child internal
				 * structures; therefore
				 * const. */
    char           *echobuf;	/* Make a local copy of the
				 * data before echoing it
				 * back to client. */
    SRV_ECHO        command;	/* (Dont pass a ptr into
				 * the parent2child
				 * internal structures). */
    size_t          datalen;

    open_parent2child_fifo (parent2child, O_RDONLY);
    echobuf = malloc (shared_fifo_bufsiz (parent2child));

    do {	/* Process commands until you get an
		 * SRV_SHUTDOWN command. */

	command = receive_fm_child (parent2child, child_pidstr,
				    &datalen);
	dataptr = shared_fifo_data (parent2child);
	switch (command) {

	    /* The SRV_CONNECT message is automatically
	     * sent by the client process when it calls
	     * connect_to_parent() */
	    case SRV_CONNECT:
		parent_open_reply_fifo (parent2child,
					child_pidstr);
		break;

	    /* SRV_ECHO is a test message you can send. You
	     * should get your message echoed right back to
	     * you. */
	    case SRV_ECHO:
		strcpy (echobuf, dataptr);
		send2child (parent2child, child_pidstr,
			    command, echobuf);
		break;

	    /* ... any other commands you add here are
	     * handled here ... */

	    default:
		printf ("Parent received %d byte message from "
		  "%s.  Command %d, message:\n\t\"%s\"\n",
			datalen, child_pidstr, command,
			dataptr);
	}	/* end switch */
    } while (command != SRV_SHUTDOWN);

    destroy_fifos (parent2child);
    free (echobuf);
}

/* In the parent process, before calling fork() */
int             main (void)
{
    shared_fifodata_tt *parent2child;
    char            parent_pidstr[INTLEN];	/* String representation
						 * of the parent
						 * (server) process ID. */
    pid_t           pid;	/* Process ID returned from
				 * fork() */

    sprintf (parent_pidstr, "%d", (int) getpid ());
    parent2child = init_parent2child_fifo (parent_pidstr);
    if ((pid = fork ()) == -1) {
	perror ("Erron in fork()");
	exit (-1);
    }
    else if (pid == 0)
	client (parent2child);	/* Execute client (child)
				 * code. */
    else
	server (parent2child);	/* Execute server (parent)
				 * code. */
}
