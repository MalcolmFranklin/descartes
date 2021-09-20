#ifndef COMMAND_LINE_H
#define COMMAND_LINE	1
/***********************************************************
 * HEADER:	COMMAND_LINE.H
 *
 * PURPOSE:	Declare functions to interract with the Xt
 *              library command line processor, and to fetch
 *              the values of command line switches.
 *
 * AUTHOR:    Malcolm L. Franklin, Arizona State University
 *
 * $Author: franklin $
 ***********************************************************
 * $Date: 1994/10/17 05:41:24 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/cmdline_ex/RCS/command_line.h,v $
 *
 **********************************************************/


static char    *command_line_h_rcsid = "$Id: command_line.h,v 1.5 1994/10/17 05:41:24 franklin Exp $";

extern XrmOptionDescRec
	       *fetch_command_line_args_struct (void);
extern int      fetch_num_commandline_args (void);
extern void     get_commandline_values (Widget AppTopShell);
extern char    *fetch_infile_name (void);
extern char    *fetch_outfile_name (void);
extern int      fetch_batch_switch (void);
extern int      fetch_iconic_switch (void);

#endif	/* command_line.h has not already been #included. */
