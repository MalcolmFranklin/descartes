/*******************************************************************************
 *  MODULE:	DESC_STRUCT.C
 *
 * PURPOSE:
 *	Declare storage for the objects declared in desc_struct.h.  Note that
 *	desc_struct.h used to define storage, which was replicated by each
 *	including object file, and merged back to a single reference by the
 *	linker.  This works on UNIX systems, but fails on others, such as
 *	VAX/VMS.
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 *
 * $Date: 1994/08/03 18:11:04 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/desc_struct.c,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
$Log: desc_struct.c,v $
 * Revision 1.7  1994/08/03  18:11:04  franklin
 * Change Error_Counter -> error_counter; E prefix is reserved by errno.h.
 *
 * Revision 1.6  1994/07/05  02:28:49  franklin
 * Initialize global file names to zero length strings.
 *
 * Revision 1.5  1994/07/01  17:39:59  franklin
 * Delete the unused global variable "Line_No".
 * Move the definition of "Max_Value_of" to this file, and only declare it
 * in desc_struct.h
 *
 * Revision 1.4  1994/06/15  17:20:26  franklin
 * 1. Remove global flag Build_Flag_4_Old_File.
 * 2. Initialize global Template_Node pointers to NULL.
 *
 * Revision 1.3  1994/06/15  16:18:39  franklin
 * Remove Build_Flag_4_Old_File.
 *
 * Revision 1.2  1994/06/15  15:41:45  franklin
 * 1. Move Hoare_Table_Name here from build_rtn.c.
 * 2. Remove variables that were never used.
 *    (Current_Dir, Path_Name, Cmd_String were never used).
 * 3. Increase buffer sizes.
 *
 * Revision 1.1  1994/06/15  03:23:02  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif
static char    *rcsid = "@(#) $Id: desc_struct.c,v 1.7, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3 1994/08/03 18:11:04 franklin Exp $";

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include "desc_struct.h"

struct stat     DESC_File_Stat;

struct Template_Node *Hoare_Root_Dummy = NULL,
               *Temp_Node = NULL,
               *Current_Node = NULL,
               *Prev_Node = NULL,
               *pre_root = NULL,
               *F_Hoare_Root_Dummy = NULL;

struct Stack_Node *Root_Stack,
               *Temp_Stack,
               *Current_Stack,
               *Prev_Stack;

char            DESC_New_File_Name[MAX_PATH_LEN] = { '\0' };
char            DESC_Line_Str[MAX_LINE_SIZE] = { '\0' };
FILE           *DESC_File_Ptr;
char            Hoare_Table_Name[MAX_PATH_LEN] = { '\0' };	/* File containing the tabular representation of the Hoare tree */


/*
 * This variable is dedicated for the use of writing some char string into
 * the panel or alert window or used for doing some system calls
 */

char            User_Msg[MAX_LINE_SIZE] = { '\0' };

/*
 * the error counter for recording the number of errors in Spec. file
 */

int             error_counter;

short           return_flag;	       /* distinguish return tree from other synthesis trees */
short           concurrent;

struct maxval_struct Max_Value_of;
