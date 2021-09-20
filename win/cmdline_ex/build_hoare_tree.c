/*******************************************************************************
 *  Program Name:	build_hoare_tree.c
 *  Written Date:	Aug 04, 1990
 *  Modified Date:	Nov 01, 1990
 *  Designer:		Lih-shiun Timothy Lee	at ASU
 *
 * $Date: 1994/08/04 22:39:28 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/cmdline_ex/RCS/build_hoare_tree.c,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: build_hoare_tree.c,v $
 * Revision 1.27  1994/08/04  22:39:28  franklin
 * Add #includes for cchk_missing_<standard include>.h in order
 * to get prototypes that CodeCheck doesnt think are there.
 *
 * Revision 1.26  1994/08/04  17:53:19  franklin
 * Add #includes for cchk_missing_<standard include>.h in order
 * to get prototypes that CodeCheck doesnt think are there.
 *
 * Revision 1.25  1994/08/03  21:38:38  franklin
 * Changed "str" to "mystr"; prefix str is reserved by string.h
 *
 * Revision 1.24  1994/08/03  16:56:13  franklin
 * Renamed functions beginning with "E", because the "E" prefix is reserved
 * by errno.h.
 *
 * I had to change the "error_code" parameter to Display_Error_Code to "errcode"
 * because of a name collision created when I downcased the name of the
 * Error_Code[] array to error_code[].
 *
 * Revision 1.23  1994/07/21  14:17:26  franklin
 * The Solaris 2.3 "/opt/SUNWspro/bin/cc" compiler requires
 * a cast from type size_t (returned by strlen()) to type
 * int in order to do comparisons w/o causing an error
 * message.
 *
 * Revision 1.22  1994/07/01  17:38:44  franklin
 * Delete the unused global variable "Line_No".
 *
 * Revision 1.21  1994/06/15  16:57:32  franklin
 * Remove global flag Build_Flag_4_New_File.
 * Add a check for a NULL pointer parameter to Free_Hoare_Tree().
 *
 * Revision 1.20  1994/06/02  17:23:09  franklin
 * Enable stricter type checking when running the CenterLine "clcc" in
 * K&R compatibility mode (-Xa switch) by re-defining __STDC__ after processing
 * the non-ansi SunOS system include files.
 *
 * Revision 1.19  1994/05/24  18:42:29  franklin
 * Do not free() sub-nodes after free()ing a parent
 * node; free() the sub-node first.  Set pointers to
 * NULL after you free() them, to prevent referencing
 * free()d memory.
 *
 * Revision 1.18  1994/05/23  16:55:58  franklin
 * Modified Build_Hoare_Tree()
 * 1. Only look for the two extra "vararg" parameters (lower and upper)
 *    for sequence nodes.
 * 2. Modified comments in the function header for Build_Hoare_Tree()
 * 3. Re-ran through "indent".
 *
 * Revision 1.17  1994/05/03  18:01:25  franklin
 * Put a comma before "..." in function signature of Build_Hoare_Tree().
 *
 * Revision 1.16  1994/05/02  17:35:25  franklin
 * Remove nested includes in desc_struct.h.  Include unistd.h
 * and sys/stat.h here instead.
 *
 * Revision 1.15  1994/05/02  15:24:07  franklin
 * State all required parameters to Build_Hoare_Tree() in the
 * parameter list.  Only the upper bound and lower bound
 * values of a sequence are optional parameters to this
 * function.
 *
 * Revision 1.14  1994/04/23  22:42:56  franklin
 * Convert Build_Hoare_Tree() from K&R style variable-arguments
 * to ANSI/ISO C variable-arguments.  Note that va_start has
 * an extra parameter, and that this module #includes
 * <stdart.h> instead of the old <vararg.h>.
 *
 * Revision 1.13  1994/04/22  05:12:23  franklin
 * 1. Deleted confusing comments.
 * 2. Seperated the allocation and the test of Root_Dummy
 *    into two statements to shut up gcc warning about
 *    the return type of calloc().
 * 3. CRITICAL BUG FIX:
 *    Changed assignment operator ("=") to the logical
 *    equality operator ("==") in an if statement!
 *
 * Revision 1.12  1994/04/12  13:05:10  franklin
 * Clarify some diagnostic messages.
 *
 * Revision 1.11  1994/04/12  10:52:34  franklin
 * Still needed to allocate another byte (detected by Purify.).
 *
 * Revision 1.10  1994/04/12  08:28:25  franklin
 * Allocate enough storage for a string AND its null terminator.
 *
 * Revision 1.9  1994/04/09  22:55:52  franklin
 * Read analysis1.h for the declaration of Get_Parameters().
 *
 * Revision 1.8  1994/04/09  22:28:31  franklin
 * wid1.h requires the definition of type Mesg in mesg.h.  As of this writing,
 * that is the only reason this file #includes mesg.h
 *
 * Revision 1.7  1994/04/08  08:53:43  franklin
 * Change Screen_Col to static; it is only used in this file.
 *
 * Revision 1.6  1994/04/08  08:37:58  franklin
 * Allocate memory for the Root_Dummy from the heap. Allocate_Hoare_Root_Dummy()
 * used to just return an address off the runtime stack!  It only worked by
 * accident in the past.
 *
 * Revision 1.5  1994/04/08  08:20:19  franklin
 * Fix syntax error in last file.
 *
 * Revision 1.4  1994/04/08  08:17:20  franklin
 * Convert to ANSI C.  Change "short"s to "int"s to head off problems linking
 * between ANSIfyd and K&R modules and libraries.
 *
 ******************************************************************************/
#endif
static char    *rcsid = "@(#) $Id: build_hoare_tree.c,v 1.27, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3 1994/08/04 22:39:28 franklin Exp $";

#include <stdlib.h>
#include "cchk_missing_stdlib.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <stdio.h>
#include <string.h>
#include <stdarg.h>		       /* This code used to use the K&R C <vararg.h> */
#include "cchk_missing_stdarg.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */

#include <unistd.h>
#include "cchk_missing_unistd.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <sys/stat.h>
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

#include <Xm/Text.h>

#include "desc_struct.h"
#include "desc_table.h"
#include "build_rtn.h"
#include "mesg.h"		       /* Required by wid1.h. */
#include "wid1.h"
#include "analysis1.h"		       /* Declaration of Get_Parameters() */
#include "build_hoare_tree.h"
#include "some_utils.h"		       /* Declaration of dump_bits(), for printing integers in binary format. */

#define FORMAT_STRING	"|%%-%ds|%%-%ds|%%-%ds|%%-%ds|%%-%ds|\n"

/******************************************************************************
 * GLOBALS
 ******************************************************************************/
int             Screen_Row;	       /* Set by Read_Spec_And_Build_Tree() in build_rtn.c */
int             Max_Name_Size;	       /* Used by Show_Hoare_Tree() in build_rtn.c */

/* The following globals are only visible within this file. */
static int      Screen_Col;
static char    *String_Header;
static char    *String_Border;
static char     String_Format[1024];
static int      Number_of_Nodes;
static struct Template_Node *Sub_Root_Dummy;	/* for sub module */


/******************************************************************************
 * FUNCTION:	ALLOCATE_HOARE_ROOT_DUMMY
 *	Allocate  Root  Dummy  Node
 ******************************************************************************/
#define   ROOT_DUMMY	"ROOT_DUMMY"   /* size 10 */

struct Template_Node *Allocate_Hoare_Root_Dummy (void)
{
	struct Template_Node *Root_Dummy;	/* This used to be a parameter, but it was overwritten before it was ever read.
						 * Also, all existing calls to this function did not pass a parameter anyway. */

	Root_Dummy = (struct Template_Node *) calloc (1, sizeof (struct Template_Node));
	if (Root_Dummy == NULL)
		abort ();

	Prev_Node = Root_Dummy;

/* Screen_Row     = 80;	 initialize 2 base position for x & y axes */
	Screen_Col = -110;	/* 8*10+30 where 30 from Gap 36 idea */
	Prev_Node->row = Screen_Row;
	Prev_Node->col = Screen_Col;

	Max_Value_of.col = Screen_Col + 2 + strlen (ROOT_DUMMY) * 8 + 2;
	Max_Value_of.row = Screen_Row + 18 + 30;

	Prev_Node->name = (char *) calloc (strlen (ROOT_DUMMY) + 1, sizeof (char));
	Prev_Node->name = ROOT_DUMMY;

/* Note: pointer can not be negative; otherwise, get error if compiled */
	Prev_Node->level_no = -1;

/* do initializations  */
	Max_Name_Size = strlen (ROOT_DUMMY);

	error_counter = 0;
	Number_of_Nodes = 0;
	return (Root_Dummy);
}

/*******************************************************************************
 * FUNCTION:	BUILD_HOARE_TREE
 *         use node type to store the different information
 *
 *	Sets the screen row & column for the node.
 *
 *	where "..." = Nothing for most things; but is the lower and
 *	upper bound of sequence nodes.
 *
 *	(mlf 5/2/1994) I made all the parameters required except upper and
 *	lower (upper bound and lower bound of a sequence).
 ******************************************************************************/

void            Build_Hoare_Tree (char *fmt, int type, char *name, int level_no,...)
{
	va_list         args;	       /* This function expects two extra parameters for sequence nodes, being the lower bound,
				        * and the upper bound of the number of elements in the sequence. */
	char           *lower;
	char           *upper;

/*
 * Print node_type in binary, cause that is how the values are defined in
 * desc_struct.h
 */

	printf ("Build_Hoare_Tree(): type = ");
	dump_bits (stdout, type);
	printf (" = 0x%X; name = %s; level = %d\n", type, name, level_no);


/* Max_Name_Size is used as the segment length for displaying Hoare Tree */
	if (Max_Name_Size < (int) strlen (name))
		Max_Name_Size = strlen (name);

	Current_Node = (struct Template_Node *)
		calloc (1, sizeof (struct Template_Node));

	Current_Node->name = (char *) calloc (strlen (name) + 1, sizeof (char));
	sprintf (Current_Node->name, "%s", name);
	Current_Node->level_no = level_no;
	Current_Node->type = type;

/* go back to  dummy node for module */

	printf ("Current_Node->name = \"%s\"\n", Current_Node->name);
	if (type == MODULE_TITLE)
	{
		printf ("\tMODULE_TITLE\n");
		Sub_Root_Dummy = Allocate_Hoare_Root_Dummy ();
		pre_root->front = Sub_Root_Dummy;
		Sub_Root_Dummy->back = pre_root;
		pre_root = Sub_Root_Dummy;

	/* Get_Parameters(); */

	}
/* modified Oct 1992  */
	if ((type & REFERENCE_NODE) && (type != LITERAL))
		Get_Parameters ();

	switch (type)
	{
		case MATCH_SEQUENCE:
		case MATCH_SEQUENCE_UNION:
		case MATCH_SEQUENCE_RANGE:
		case REFERENCE_SEQUENCE:
		case REFERENCE_SEQUENCE_UNION:
		case REFERENCE_SEQUENCE_RANGE:

			va_start (args, level_no);	/* initialize arg list */
			lower = va_arg (args, char *);
			upper = va_arg (args, char *);
			va_end (args);	/* clean up argument list */

			Current_Node->lower = atoi (lower);
			Current_Node->upper = atoi (upper);
			break;

		default:
			;
	}

	if (level_no > Prev_Node->level_no)	/* immediate son */
	{
		printf ("level_no = %d Immediate son of \"%s\"\n", level_no, Prev_Node->name);
		Prev_Node->level_point = Current_Node;
		Current_Node->ancestor = Prev_Node;
		Screen_Col = Prev_Node->col + 2 + (8 * strlen (Prev_Node->name)) + 2 + 36;
	}
	else if (level_no < Prev_Node->level_no)	/* another prev. sibling */
	{
		printf ("level_no = %d  Another sibling of \"%s\"\n", level_no, Prev_Node->name);
		Temp_Node = Find_Ancestor (Prev_Node, level_no);
		Current_Node->ancestor = Temp_Node->ancestor;
		Temp_Node->front = Current_Node;
		Current_Node->back = Temp_Node;
		Screen_Col = Temp_Node->col;
	}

/*
 * NASTY BUG fixed by Malcolm Franklin on 4/21/94.  The following "if"
 * statement had an assignment operator instead of "=="
 */
	else if (level_no == Prev_Node->level_no)	/* immediate sibling */
	{
		printf ("level_no = %d  Immediate sibling of %s\n", level_no, Prev_Node->name);
		Current_Node->ancestor = Prev_Node->ancestor;
		Prev_Node->front = Current_Node;
		Current_Node->back = Prev_Node;
	}

	if (Max_Value_of.col < (Screen_Col + 2 + (int) strlen (name) * 8 + 2))
	{
		Max_Value_of.col = Screen_Col + 2 + strlen (name) * 8 + 2;
	}

	Screen_Row = Prev_Node->row + 25;	/* 9+9+6+1 */
	Max_Value_of.row = Screen_Row + 18 + 30;

	Current_Node->col = Screen_Col;
	Current_Node->row = Screen_Row;

	Number_of_Nodes++;

/* all processings are finished and change current node to prev node */
	Prev_Node = Current_Node;

}				       /**  Build_Hoare_Tree()  **/



/******************************************************************************
 * FUNCTION:	FIND_ANCESTOR
 *	Finding the proper ancestor for the current node.
 *****************************************************************************/
struct Template_Node *Find_Ancestor (struct Template_Node * prev_node, int level_no)
{
	struct Template_Node *cur;

/* find the proper ancestor from the same level sibling  */
	for
		(cur = prev_node; cur->ancestor->level_no > level_no; cur = cur->ancestor)
	{
		printf ("cur->name = \"%s\" level_no = %d\n", cur->name, level_no);
	}
	printf ("level_no = %d\n", level_no);
	return (cur->ancestor);
}


/******************************************************************************
 * FUNCTION:	SCAN_TREE_FOR_SEQ
 *****************************************************************************/
void            Scan_Tree_For_Seq (struct Template_Node * cur_node)
{
	if (cur_node->level_point == NULL && cur_node->front == NULL)
	{
		Add_One_More_Node (cur_node);
		return;
	}

	if (cur_node != NULL)
	{
		Add_One_More_Node (cur_node);
		if (cur_node->level_point != NULL)
			Scan_Tree_For_Seq (cur_node->level_point);
	}

	if (cur_node->front != NULL)
	{
		Scan_Tree_For_Seq (cur_node->front);
	}
	return;
}


/******************************************************************************
 * FUNCTION:	ADD_ONE_MORE_NODE
 *****************************************************************************/
void            Add_One_More_Node (struct Template_Node * cur_node)
{
#define	DUMMY_LEVEL	-2

	switch (cur_node->type)
	{

			case MATCH_SEQUENCE:
			case MATCH_SEQUENCE_UNION:
			case MATCH_SEQUENCE_RANGE:
			case REFERENCE_SEQUENCE:
			case REFERENCE_SEQUENCE_UNION:
			case REFERENCE_SEQUENCE_RANGE:

			Current_Node = (struct Template_Node *)
			calloc (1, sizeof (struct Template_Node));
			cur_node->extra_front = Current_Node;
			Current_Node->extra_back = cur_node;

			if (cur_node->type & MATCH_NODE)
			{
				sprintf (User_Msg, "match_dummy");
				Current_Node->name = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
				sprintf (Current_Node->name, "%s", User_Msg);
				Current_Node->level_no = DUMMY_LEVEL;
			}
			else
			{
				sprintf (User_Msg, "reference_dummy");
				Current_Node->name = (char *) calloc (strlen (User_Msg) + 1, sizeof (char));
				sprintf (Current_Node->name, "%s", User_Msg);
				Current_Node->level_no = DUMMY_LEVEL;
			}

			switch (cur_node->type)
			{

				case MATCH_SEQUENCE:	/* Add 1 more Direct Product */
					Current_Node->type = MATCH_DIRECT_PRODUCT;
					break;
				case MATCH_SEQUENCE_UNION:
					Current_Node->type = MATCH_DISCRIMINATED_UNION;
					break;
				case MATCH_SEQUENCE_RANGE:	/* Add 1 more Direct Product */
					Current_Node->type = MATCH_DIRECT_PRODUCT;
					break;
				case REFERENCE_SEQUENCE:
					Current_Node->type = REFERENCE_DIRECT_PRODUCT;
					break;
				case REFERENCE_SEQUENCE_UNION:
					Current_Node->type = REFERENCE_DISCRIMINATED_UNION;
					break;
				case REFERENCE_SEQUENCE_RANGE:
					Current_Node->type = REFERENCE_DIRECT_PRODUCT;
					break;
			}

		default:
			break;

	}			/* switch */
}


/******************************************************************************
 * FUNCTION:	FREE_HOARE_TREE
 *	Release (Free) Hoare Tree.
 *****************************************************************************/
void            Free_Hoare_Tree (struct Template_Node * cur_node)
{
	if (cur_node)
	{
		if (cur_node->level_point == NULL && cur_node->front == NULL)
		{
			printf ("Node name - %s is freed\n", cur_node->name);
			if (cur_node->extra_front)
			{
				free (cur_node->extra_front->name);
				free (cur_node->extra_front);
			}
			free (cur_node->name);
			free (cur_node);
			cur_node = NULL;
			return;
		}

		if (cur_node->level_point != NULL)
			Free_Hoare_Tree (cur_node->level_point);

		if (cur_node->front != NULL)
			Free_Hoare_Tree (cur_node->front);

		printf ("Node name - %s is freed\n", cur_node->name);
		if (cur_node->extra_front)
		{
			free (cur_node->extra_front->name);
			free (cur_node->extra_front);
		}
		free (cur_node->name);
		free (cur_node);
		cur_node = NULL;
	}
	return;
}


/******************************************************************************
 * FUNCTION:	GENERATE_STRING_FORMAT
 *****************************************************************************/

void            Generate_String_Format (int size)
{
	int             i;

	i = size;
	sprintf (String_Format, FORMAT_STRING, i, i, i, i, i);
	String_Header = (char *) calloc (5 * size + 6 + 2, sizeof (char));
	sprintf (String_Header, String_Format,
		 "[Node]", "[Ancestor]", "[Level]", "[Front]", "[Back]");
	String_Border = (char *) calloc (5 * size + 6 + 2, sizeof (char));
	for (i = 0; i < (5 * size + 6); i++)
		*(String_Border + i) = '-';
	for (i = 0; i <= 5; i++)
		*(String_Border + (i + (size * i))) = '+';

/*
 * there are 2 lines per node plus 3 heading lines & 10 extra line i =
 * (5*size+6) * (2*Number_of_Nodes+3+10);
 */


/* open file pointer to store an new table file */
	DESC_File_Ptr = fopen (Hoare_Table_Name, "w");
	printf ("Writing the Hoare table to \"%s\".\n", Hoare_Table_Name);
	Make_One_Blank_Line ();
	sprintf (User_Msg, "The name of a Descartes Specification is [%s].\n",
		 DESC_New_File_Name);
	Write_Hoare_Table_To_Disk (User_Msg);
	Make_One_Blank_Line ();
	sprintf (User_Msg, "The name of template tree table is [%s].\n", Hoare_Table_Name);
	Write_Hoare_Table_To_Disk (User_Msg);
	Make_One_Blank_Line ();
	sprintf (User_Msg, "The width of this table is %d.\n", (5 * size + 6));
	Write_Hoare_Table_To_Disk (User_Msg);
	Make_One_Blank_Line ();

	sprintf (User_Msg, "%s\n", String_Border);
	Write_Hoare_Table_To_Disk (User_Msg);
	sprintf (User_Msg, "%s\n", String_Header);	/* need "\n" */
	Write_Hoare_Table_To_Disk (User_Msg);

	for (i = 0; i < (5 * size + 6); i++)
		*(String_Border + i) = '=';
	for (i = 0; i <= 5; i++)
		*(String_Border + (i + (size * i))) = '+';

	sprintf (User_Msg, "%s\n", String_Border);
	Write_Hoare_Table_To_Disk (User_Msg);

	for (i = 0; i < (5 * size + 6); i++)
		*(String_Border + i) = '-';
	for (i = 0; i <= 5; i++)
		*(String_Border + (i + (size * i))) = '+';
}


/******************************************************************************
 * FUNCTION:	MAKE_ONE_BLANK_LINE
 *****************************************************************************/
void            Make_One_Blank_Line (void)
{
	sprintf (User_Msg, "\n");
	Write_Hoare_Table_To_Disk (User_Msg);
}


/******************************************************************************
 * FUNCTION:	WRITE_HOARE_TABLE_TO_DISK
 *****************************************************************************/
void            Write_Hoare_Table_To_Disk (char *msg)
{

	fputs (msg, DESC_File_Ptr);
}

/******************************************************************************
 * FUNCTION:	WRITE_HOARE_TREE
 *	Write the Hoare tree starting from the node under the root dummy node.
 *****************************************************************************/

void            Write_Hoare_Tree (struct Template_Node * cur_node)
{
/* Terminal  Node  */
	if (cur_node->level_point == NULL && cur_node->front == NULL)
	{
		Write_Tree_Node (cur_node);
		return;
	}

	if (cur_node != NULL)
	{
		Write_Tree_Node (cur_node);
		if (cur_node->level_point != NULL)
			Write_Hoare_Tree (cur_node->level_point);
	}

	if (cur_node->front != NULL)
	{
		Write_Hoare_Tree (cur_node->front);
	}
	return;
}


/******************************************************************************
 * FUNCTION:	WRITE_TREE_NODE
 *****************************************************************************/

void            Write_Tree_Node (struct Template_Node * cur_node)
{
	char           *level,
	               *front,
	               *back;

	if (cur_node->level_point == NULL)
		level = "null";
	else
		level = cur_node->level_point->name;

	if (cur_node->front == NULL)
		front = "null";
	else
		front = cur_node->front->name;

	if (cur_node->back == NULL)
		back = "null";
	else
		back = cur_node->back->name;

	sprintf (User_Msg, String_Format,
		 cur_node->name, cur_node->ancestor->name, level, front, back);
	Write_Hoare_Table_To_Disk (User_Msg);

	sprintf (User_Msg, "%s\n", String_Border);
	Write_Hoare_Table_To_Disk (User_Msg);
}

/******************************************************************************
 * FUNCTION:	FREE_STRING_FORMAT
 *****************************************************************************/
void            Free_String_Format (void)
{
	free (String_Header);
	String_Header = NULL;
	free (String_Border);
	String_Border = NULL;
	fclose (DESC_File_Ptr);
}

/******************************************************************************
 * FUNCTION:	DISPLAY_ERROR_CODE
 *****************************************************************************/
void            Display_Error_Code (int line_no, int location, int errcode, int col, char *mystr)
{
	int             i;

	sprintf (User_Msg, "%s<< at Line %d", mystr, line_no);
	Display_Build_User_Msg (rd_spec_text_w, User_Msg);

	if ((errcode != 14) && (errcode != 15))
	{
		for (i = 0; i < sizeof (User_Msg); i++)
			User_Msg[i] = '\0';
		for (i = 0; i < location; i++)
			User_Msg[i] = ' ';
		User_Msg[strlen (User_Msg)] = '^';
		Display_Build_User_Msg (rd_spec_text_w, User_Msg);
	}
	if ((errcode >= 12) && (errcode <= 16))
		sprintf (User_Msg, error_code[errcode]);
	else
		sprintf (User_Msg, error_code[errcode], error_supplement[col]);

	Display_Build_User_Msg (rd_spec_text_w, User_Msg);
}
