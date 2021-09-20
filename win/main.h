#ifndef	MAIN_H
#define	MAIN_H	1
/*******************************************************************************
 *
 * HEADER:	MAIN.H
 *
 * PURPOSE:	Declare global variables in main.c that must be accessible
 *		to wid1.c
 *
 * FUNCTIONS DECLARED
 *	EXTERNAL:
 *
 * EXTERNAL INTERFACES
 *	GLOBALS:
 *	FILES:
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 * $Author: franklin $
 *******************************************************************************
 * $Date: 1994/08/03 18:07:50 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/main.h,v $
 *
 ******************************************************************************/



#if 0
/******************************************************************************
 *
$Log: main.h,v $
 * Revision 1.4  1994/08/03  18:07:50  franklin
 * Change toplevel -> ttoplevel, because "to" prefix is reserved by ctype.h
 *
 * Revision 1.3  1994/06/15  15:46:32  franklin
 * Add reset_descartes_specname()
 *
 * Revision 1.2  1994/06/09  23:05:29  franklin
 * wid1.c needs access to convert_to_inst_name() so it can build the shell
 * widget used to display ascii text in a standalone window.
 *
 * Revision 1.1  1994/06/09  06:34:58  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif

static char    *main_h_rcsid = "$Id: main.h,v 1.4, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3 1994/08/03 18:07:50 franklin Exp $";

extern Widget   ttoplevel;
extern XtAppContext app;
extern char    *convert_to_inst_name (char *name, char *suffix);
extern void     reset_descartes_specname (char *new_spec_name);

#endif				       /* MAIN_H  End if this file has not already been #included */
