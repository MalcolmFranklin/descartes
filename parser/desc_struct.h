#ifndef DESC_STRUCT_H
#define DESC_STRUCT_H
/*******************************************************************************
 *  Program Name:	desc_struct.h
 *  Written Date:	Jul. 15, 1990
 *  Modified Date:	Nov. 01, 1990
 *  Designer:		Lih-shiun Lee  at ASU
 *
 * PURPOSE:
 *  The data structures for the Hoare tree of the Descartes Specification
 *  are declared as shown the following:
 *
 *  There will have the necessary (enough) descriptions for the structures
 *
 * NOTE:
 *      Modules #including this file MUST FIRST include <unistd.h> and
 *	<sys/stat.h>.
 *
 * $Date: 1994/05/02 17:47:22 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/desc_struct.h,v $
 *
 **-M**************************************************************************/

#if 0
/******************************************************************************
 *
$Log: desc_struct.h,v $
 * Revision 1.10  1994/05/02  17:47:22  franklin
 * Dont nest #includes.  Dont reference sys/types.h any more
 * #include <unistd.h> and <sys/stat.h> in the using modules
 * instead.
 *
 * Revision 1.9  1994/04/14  22:40:14  franklin
 * You cannot suppress the warning about "share_rtn_h_rcsid" not used, without
 * turning off all such warnings in a module which #includes this file.
 * Live with the message.
 *
 * Revision 1.8  1994/04/14  18:24:58  franklin
 * 1. Suppress ObjectCenter warnings about "static variable rcsid unused".
 * 2. Remove "slash-star" inside a comment.
 *
 * Revision 1.7  1994/04/12  07:26:27  franklin
 * Run through "indent".
 *
 * Revision 1.6  1994/04/09  22:03:31  franklin
 * Convert enumerated lists into enumerated types, for the Activity and
 * globals in exec_rtn1.c and analysis1.c
 *
 * Revision 1.5  1994/04/08  08:56:11  franklin
 * Change "short"s to "int"s to avoid problems when linking
 * between ANSI and K&R object files and libraries.
 *
 * Revision 1.4  1994/04/08  04:36:20  franklin
 * Dont allow a user to #include this file more than once.
 *
 * Revision 1.3  1994/03/30  04:58:16  franklin
 * Change the name of "rcsid" to "desc_struct_h_rcsid" to avoid conflicts with
 * ".c" files containing an "rcsid" string.
 *
 * Revision 1.2  1994/03/24  19:35:27  franklin
 * Fix syntax error.  I also made an explainatory comment regarding
 * a misleading comment in the #definition of RANDOM.
 *
 ******************************************************************************/
#endif
static char    *desc_struct_h_rcsid = "@(#) $Id: desc_struct.h,v 1.10 1994/05/02 17:47:22 franklin Exp $";


/* struct stat     DESC_File_Stat; */

#define	ON		   1
#define	OFF		 (ON >> ON)

#define	NOT_YET		 OFF	       /* determine the building process */
#define	READY		 ON

#define	NO		 OFF
#define	YES		 ON

#define TRUE     1
#define FALSE    0

#define MAX_FILE_LEN	  60
#define	MAX_LINE_SIZE	 132
#define MAX_DIR_LEN	 256
#define	MAX_PATH_LEN	 512

#define SHMKEY    75
#define SEMKEY   ((key_t) 23456L)
#define SEMKEY1   ((key_t) 7891L)
#define MSGKEY   ((key_t) 7801L)
#define MSGKEY1   ((key_t) 6801L)

char            Current_Dir[MAX_DIR_LEN];
char            Path_Name[MAX_PATH_LEN];
char            Cmd_String[MAX_LINE_SIZE];

/*
 * the storage for saving the Descartes Spec. file
 */

char            DESC_Old_File_Name[MAX_FILE_LEN];
char            DESC_New_File_Name[MAX_FILE_LEN];
char            DESC_Line_Str[MAX_LINE_SIZE];

FILE           *DESC_File_Ptr;

/*
 * This variable is dedicated for the use of writing some char string into
 * the panel or alert window or used for doing some system calls
 */

char            User_Msg[MAX_LINE_SIZE];

/*
 * the flag for determining whether the tree building is completed or not
 */

short           Build_Flag_4_Old_File; /* 4 means for */
short           Build_Flag_4_New_File;

/*
 * the error counter for recording the number of errors in Spec. file
 */

int             Error_Counter,
                Line_No;
short           return_flag;	       /* distinguish return tree from other synthesis trees */
short           concurrent;

#define	MATCH_NODE			0x40	/* 0100 0000  bit 6 */
#define	REFERENCE_NODE			0x80	/* 1000 0000  bit 7 */

#define	MATCH_DIRECT_PRODUCT		0x41	/* 0100 0001 */
#define	MATCH_DISCRIMINATED_UNION	0x42	/* 0100 0010 */
#define	MATCH_SEQUENCE			0x44	/* 0100 0100 */
#define	MATCH_SEQUENCE_UNION		0x45	/* 0100 0101 */
#define	MATCH_SEQUENCE_RANGE		0x46	/* 0100 0110 */

#define	LITERAL				0x81	/* 1000 0001 */
#define	MODULE_TITLE			0x82	/* 1000 0010 */
#define	REFERENCE_DIRECT_PRODUCT	0x83	/* 1000 0011 */
#define	REFERENCE_DISCRIMINATED_UNION	0x84	/* 1000 0100 */
#define	REFERENCE_SEQUENCE		0x85	/* 1000 0101 */
#define	REFERENCE_SEQUENCE_UNION	0x86	/* 1000 0110 */
#define	REFERENCE_SEQUENCE_RANGE	0x87	/* 1000 0111 */
#define	REFERENCE_SEQUENCE_NO		0x88	/* 1000 1000 */
#define	MODULE_CALL			0x89	/* 1000 1001 */
#define	SYMBOLIC			0x8a	/* 1000 1010 */

#define PRIMITIVE                       0xc0	/* 1100 0000 */
/* ARITHMETIC_PRIMITIVE            0xc1     1100 0001 */
#define PLUS                            0xc1	/* 1100 0001 */
#define MINUS                           0xc2	/* 1100 0010 */
#define TIMES                           0xc3	/* 1100 0011 */
#define DIVIDED_BY                      0xc4	/* 1100 0100 */
#define RAISED_TO                      0xc5	/* 1100 0100 */

/*
 * RANDOM (0xC6) is actually 1100 0110.  The original comment to the right of
 * the #define RANDOM statement is wrong. MLF 3/24/94
 */
#define RANDOM				0xc6	/* 1100 0101 */

/* LOGIC_PRIMITIVE                 0xc2     1100 0010 */
#define EQUAL                         0xd1	/* 1101 0001 */
#define NOT_EQUAL                     0xd2	/* 1101 0010 */
#define GREATER_THAN                  0xd3	/* 1101 0011 */
#define LESS_THAN                     0xd4	/* 1101 0100 */
#define LESS_THAN_OR_EQUAL            0xd5	/* 1101 0100 */
#define GREATER_THAN_OR_EQUAL         0xd6	/* 1101 0011 */

/* BOOLEAN_PRIMITIVE               0xc3     1100 0011 */
#define AND                         0xe1	/* 1110 0001 */
#define OR                          0xe2	/* 1110 0010 */
#define NOT                         0xe3	/* 1110 0011 */

#define REAL_TIME_PRIMITIVE             0xf0	/* 1111 0000 */
#define PARALLELS                        0xf1	/* 1111 0001 */
#define TIMER                        0xf2	/* 1111 0002 */
#define SEND_TO                      0xf3
#define RECEIVE_FROM                 0xf4
#define ASEND_TO                      0xf5
#define ARECEIVE_FROM                 0xf6
#define DELAYS				0xf7
#define GET_TIME                        0xf8	/* 1111 0002 */

/*
 * The following 2 node types are only used by SEQUENCE NODE
 */

#define	DUMMY_DIRECT_PRODUCT		0x21	/* 0010 0001 */
#define	DUMMY_DISCRIMINATED_UNION	0x22	/* 0010 0010 */


typedef enum
{
	FIRST,
	NEXT,
	SUCCEED,
	FAIL
}               processing_situation_t;

extern processing_situation_t Activity;/* Storage allocated in exec_rtn1.c */

typedef enum
{
	ANALYSIS,
	SYNTHESIS,
	SYNTHESIS1
}               tree_t;		       /* must use short type */

extern tree_t   Tree_Type;	       /* Storage allocated in exec_rtn1.c */
typedef char    DATA;

struct stack
{
	DATA            d;
	struct stack   *next;
};

struct link_list
{
	char           *name;
	struct link_list *next;
};

typedef struct stack ELEMENT;
typedef ELEMENT *TOP;




/*
 * Template node for Hoare tree structure
 */

/*
 * typedef struct { Pixmap  pix; Dimension  width,height; } pixmap_data;
 */

/*
 * Pixmap Module_pix[20]; Pixmap Curent_pix;
 */

struct Template_Node
{

	struct Template_Node *ancestor;/* the direct father */
	struct Template_Node *level_point;	/* 1st immediate son; level break point */
	struct Template_Node *front;   /* next immediate sibling	 */
	struct Template_Node *back;    /* previously immediate sibling */

/* following 2 var's are used for "Sequence Node" */
	struct Template_Node *extra_front;	/* check for FREE */
	struct Template_Node *extra_back;

/* forward pointer referencing to a stack; check for FREE  */
	struct Stack_Node *top_of_stack;

	char           *name;	       /* name string; check for FREE */

/* add   April   1992    */
	char           *module_name;   /* name string; check for FREE */
	struct link_list *para;

	int             level_no;      /* based on indentation; also use for the starting position at x axis */

/*
 * The following 2 variables are used to locate the 1st char of the string on
 * the canvas.  Remember "character origin" and "baseline" 2 factors.  Refer
 * to Pixrect manual.
 */
	int             row;	       /* use for drawing each node in the certain position at y axis */
	int             col;	       /* use for drawing each node in the certain position at x axis */
	int             type;	       /* node type */

/* struct	Template_Node	*bound_back;   no longer used */
/* unsigned int   bound_free; Not used. Original comment: free - match; bound - reference */

/*
 * char  *condition; int	begin_string; int	end_string;
 */

/*
 * Sequence Range  ( Xl .. Xu ):
 * 
 * NO lower bound is not allowed; this lower bound value must be > 0; if no
 * upper bound, then set -1 to upper for internal control. Also, the value
 * for lower and upper must be positive.
 * 
 * Sequence  ( * ):
 * 
 * Set 0 to lower bound; and set -1 to upper bound.
 * 
 * Sequence Union  ( *+ ):
 * 
 * Do the same thing as the previous situation; in addition, create a dummy node
 * for Discriminated Union.
 * 
 * Note: -1 indicates the infinity.
 */

	int             lower;	       /* lower bound */
	int             upper;	       /* upper bound */

}              *Hoare_Root_Dummy, *Temp_Node, *Current_Node, *Prev_Node, *pre_root, *F_Hoare_Root_Dummy;

struct Stack_Node
{
/* sort of backward ptr to template node */
	struct Template_Node *template_node_ptr;

	int             no_of_elements;/* the # of elements in Sequence node */

	int             begin,
	                end;	       /* indices to input buffer string */
/* only used for Match node */

/*
 * free   - Match node bound  - Reference node
 */
	struct Stack_Node *prev_stack_element;	/* same stack, diff element */
	struct Stack_Node *bound_buddy;/* ptr to corresponding match node */

/* threads used for matching process; diff stack & diff element */
	struct Stack_Node *forward_stack_ptr;
	struct Stack_Node *backward_stack_ptr;

/* point to the last processed template node for NEXT activity */
	struct Stack_Node *tcp_save;

/*
 * pointers for module call (might be used for recursive call) struct
 * Template_Node  *invoking_back; struct	Template_Node
 * *invoking_front;
 */

	int             from_tree_type;/* Analysis or Synthesis */

/*
 * the following might be no longer used any more from the day of this design
 * 
 * int	number_of_lower; int	number_of_upper; struct	Template_Node
 * *template_link_ptr; char	*template_name; int	new_level_no;   <-
 * macro substitution ?? struct	Stack_Node  *ancestor_sp;
 */
}              *Root_Stack, *Temp_Stack, *Current_Stack, *Prev_Stack;

struct
{
	int             col;
	int             row;
}               Max_Value_of;

/*
 * the structure for the Descartes Spec's errors
 * 
 * struct	Error_Node { int	error_code; int	line_no; struct	Error_Node
 * *next; } *Error_Root_Dummy, *Current_Error, *Prev_Error;
 */

#endif				       /* DESC_STRUCT_H (end if already #included this file) */
