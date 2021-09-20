#ifndef BUILD_HOARE_TREE_H
#define BUILD_HOARE_TREE_H	1
/*******************************************************************************
 * HEADER:	BUILD_HOARE_TREE.H
 *
 * PURPOSE:	Contains declarations of external functions defined in
 *		build_hoare_tree.c
 *
 * CREATED:	4/8/1994
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 *
 * NOTE:	Struct Template_Node is defined in "desc_struct.h"
 *******************************************************************************
 * $Date: 1994/08/03 21:38:13 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/build_hoare_tree.h,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: build_hoare_tree.h,v $
 * Revision 1.10  1994/08/03  21:38:13  franklin
 * Changed "str" to "mystr"; prefix str is reserved by string.h
 *
 * Revision 1.9  1994/08/03  17:01:42  franklin
 * Renamed error_code parameter to Display_Error_Code because of a potential
 * for a name collision with the error_code[] array.
 *
 * Revision 1.8  1994/05/03  18:00:42  franklin
 * Put a comma before "..." in function signature of Build_Hoare_Tree().
 *
 * Revision 1.7  1994/05/02  15:25:59  franklin
 * State all required parameters to Build_Hoare_Tree() in the
 * parameter list.  Only the upper bound and lower bound
 * values of a sequence are optional parameters to this
 * function.
 *
 * Revision 1.6  1994/04/23  22:45:21  franklin
 * Convert Build_Hoare_Tree() from K&R style variable-arguments
 * to ANSI/ISO C variable-arguments.
 *
 * Revision 1.5  1994/04/14  22:39:32  franklin
 * You cannot suppress the warning about "share_rtn_h_rcsid" not used, without
 * turning off all such warnings in a module which #includes this file.
 * Live with the message.
 *
 * Revision 1.4  1994/04/14  18:24:12  franklin
 * Suppress ObjectCenter warnings about "static variable rcsid unused".
 *
 * Revision 1.3  1994/04/12  07:23:42  franklin
 * Remove #ifdef __STDC__.  All the code is now ANSI compliant.
 *
 * Revision 1.2  1994/04/08  08:54:21  franklin
 * Add declarations for globals used/set in build_rtn.c
 *
 * Revision 1.1  1994/04/08  07:57:31  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif
static char    *build_hoare_tree_h_rcsid = "@(#) $Id: build_hoare_tree.h,v 1.10, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3 1994/08/03 21:38:13 franklin Exp $";

/******************************************************************************
 * GLOBALS
 ******************************************************************************/
extern int      Screen_Row;	       /* Set by Read_Spec_And_Build_Tree() in build_rtn.c */
extern int      Max_Name_Size;	       /* Used by Show_Hoare_Tree() in build_rtn.c */

/******************************************************************************
 ******************************************************************************/
extern struct Template_Node *Allocate_Hoare_Root_Dummy (void);

/******************************************************************************
 ******************************************************************************/
extern void     Build_Hoare_Tree ( char *fmt, int type, char *name, int level_no, ... );

/******************************************************************************
 ******************************************************************************/
extern struct Template_Node *Find_Ancestor (struct Template_Node * prev_node, int level_no);

/******************************************************************************
 ******************************************************************************/
extern void     Scan_Tree_For_Seq (struct Template_Node * cur_node);

/******************************************************************************
 ******************************************************************************/
extern void     Add_One_More_Node (struct Template_Node * cur_node);

/******************************************************************************
 ******************************************************************************/
extern void     Free_Hoare_Tree (struct Template_Node * cur_node);

/******************************************************************************
 ******************************************************************************/
extern void     Generate_String_Format (int size);

/******************************************************************************
 ******************************************************************************/
extern void     Make_One_Blank_Line (void);

/******************************************************************************
 ******************************************************************************/
extern void     Write_Hoare_Table_To_Disk (char *msg);

/******************************************************************************
 ******************************************************************************/
extern void     Write_Hoare_Tree (struct Template_Node * cur_node);

/******************************************************************************
 ******************************************************************************/
extern void     Write_Tree_Node (struct Template_Node * cur_node);

/******************************************************************************
 ******************************************************************************/
extern void     Free_String_Format (void);

/******************************************************************************
 ******************************************************************************/
extern void     Display_Error_Code (int line_no, int location, int errcode, int col, char *mystr);

#endif				       /* BUILD_HOARE_TREE_H (end if this file has already been #included) */
