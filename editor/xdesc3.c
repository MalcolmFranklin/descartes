/*******************************************************************************
 * $Date: 1994/06/01 15:09:20 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/editor/RCS/xdesc3.c,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: xdesc3.c,v $
 * Revision 1.7  1994/06/01  15:09:20  franklin
 * Do not try to free() null pointers in remove_semantic_listing().
 *
 * Revision 1.6  1994/06/01  00:09:21  franklin
 * Workaround ANSI/ISO Standard C incompatibilities with the SunOS 4.x
 * include files.
 *
 * Revision 1.5  1994/05/31  20:19:31  franklin
 * Define the length of a node name which has no '(' character in it.
 * (variable p_length).  Remove some extra whitespace.  Delete local variables
 * that are never referenced.
 *
 * Revision 1.4  1994/05/31  17:51:59  franklin
 * Run through the SunOS 4.1.x "indent" utility.
 *
 * Revision 1.3  1994/05/31  17:08:19  franklin
 * 1. Get the declarations of standard C functions from the appropriate
 *    header files, instead of having a local declaration.
 * 2. Add function headers for functions referenced in xdesc1.c and xdesc2.c
 *
 * Revision 1.2  1994/05/07  21:16:13  franklin
 * Run through the Gnu "protoize" tool.
 *
 * Revision 1.1  1994/05/06  01:07:05  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif
static char    *rcsid = "@(#) $Id: xdesc3.c,v 1.7 1994/06/01 15:09:20 franklin Exp $";

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
/******************************************************************************
 * NOTE TO FUTURE MAINTAINERS USING CenterLine "clcc" COMPILER:
 *
 * Nearly all the SunOS 4.x Operating System include files (<sys/xxx.h>)
 * because compilation errors under a strict ANSI/ISO compiler running in anal-
 * retentive mode such as CenterLine "clcc".  In order to get these to compile,
 * with clcc, you have to pass the  -Xa (K&R C compatibility switch) to the
 * compiler.  BUT (get this) when we do this, the CenterLine preprocessor
 * #defines __STDC__ to 0 (zero); when this happens, we dont see the vararg
 * prototypes for the X functions -- and get warning messages for calling them
 * with different numbers of arguments.  On top of all this noise, we DONT GET  
 * all the ANSI/ISO C type checking that we could have.
 *
 * WORKAROUND, IF YOU NEED IT.
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

#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include <X11/StringDefs.h>
#include <Xm/List.h>
#include <Xm/ScrollBar.h>
#include <Xm/ScrolledW.h>

#include "editor1.h"
#include "xdesc1.h"
#include "xdesc3.h"		       /* Have the compiler check the header file against the definitions in this file. */

/*
 * ------------------------------------ structure of a node for error
 * ------------------------------------
 */
struct error_item
{
	struct node    *error_child;
	struct error_item *next;
};


struct error_record
{
	struct node    *error_node;
	struct error_item *item;
	char           *message;
};

/* ----------------------------- */
/* Global variable from xdesc3.c */
/* ----------------------------- */
char           *arguments_array[30];
char           *match_node_array[100];
char           *refer_node_array[100];

struct error_record *error_log[30];
int             num_of_list_items;
int             match_index = 0,
                refer_index = 0;

static int      arg_num;	       /* Seems to be the number of arguments in a module title.  (MLF 5/26/94) */
char           *rule_1_def = "Input Argument Must Have A Corresponding Analysis Tree";
char           *rule_2_def = "No Corresponding Input Argument";
char           *rule_3_def = "Non-Literal Reference Node Must Have A Corresponding Match Node";
char           *rule_4_def = "A Discriminated Union Must Have Two (2) Or More Immediate Children";
char           *rule_5_def = "A Sequence Node Always Has At Least One (1) Immediate Children";
char           *rule_6_def = "Upper Bound Must Be Greater Or Equal To The Lower Bound";
char           *rule_8_def = "Ambiguous Match Node Name";

/* -------------------------------------- */
/* Function : recognize_input_arguments() */
/* Breakdown the input Arguments	  */
/* last update : 10/21/92		  */
/* -------------------------------------- */


extern void     calculate_string_data (struct node * node_ptr);

int             recognize_input_arguments (char *module_name)
{
	char           *start_ptr,
	               *front_ptr,
	               *back_ptr,
	               *rest_of_string,
	               *temp_string;
	int             i,
	                rest_length,
	                cut_length,
	                argument_length;


	rest_of_string = (char *) calloc (80, sizeof (char));
	temp_string = (char *) calloc (80, sizeof (char));
	i = 0;
	front_ptr = (char *) strchr (module_name, '(');
	while (front_ptr != NULL)
	{
		strcpy (rest_of_string, front_ptr);
		rest_length = (int) strlen (rest_of_string);
		back_ptr = (char *) strchr (rest_of_string, ')');
		strcpy (temp_string, strchr (rest_of_string, ')'));
		cut_length = (int) strlen (temp_string);
		argument_length = (rest_length - cut_length) - 1;
		start_ptr = rest_of_string + 1;
		arguments_array[i] = (char *) calloc (50, sizeof (char));
		strncpy (arguments_array[i], rest_of_string + 1, argument_length);
		i = i + 1;
		strcpy (temp_string, back_ptr + 1);
		front_ptr = (char *) strchr (temp_string, '(');
	}
	free (rest_of_string);
	free (temp_string);
	return (i);
}

void            recognize_match_or_refer_nodes (void)
{
	struct node    *temp_ptr;
	char           *temp_node_name,
	               *p;
	int             temp_length,
	                p_length;

	match_index = 0;
	refer_index = 0;
	temp_node_name = (char *) calloc (80, sizeof (char));
	temp_ptr = template_tree_pointer->next;
	while (temp_ptr != NULL)
	{
		temp_length = temp_ptr->name_length;
		switch (temp_ptr->node_type)
		{
			case match_node:
				switch (temp_ptr->d_s_method)
				{
					case mat_direct_product:
						strncpy (temp_node_name, temp_ptr->node_name, temp_length);
						strcpy (temp_node_name + temp_length, "");
						break;
					case mat_discriminated_union:
						strncpy (temp_node_name, temp_ptr->node_name, temp_length - 1);
						strcpy (temp_node_name + temp_length - 1, "");
						break;
					case mat_sequence_1:
						strncpy (temp_node_name, temp_ptr->node_name, temp_length - 1);
						strcpy (temp_node_name + temp_length - 1, "");
						break;
					case mat_sequence_2:
						p = (char *) strchr (temp_ptr->node_name, '(');
						if (p != NULL)
							p_length = strlen (p);
						else
							p_length = 0; /* If there is no '(' in the name */
						strncpy (temp_node_name, temp_ptr->node_name, temp_length - p_length);
						strcpy (temp_node_name + temp_length - p_length, "");
						break;
					case mat_sequence_3:
						strncpy (temp_node_name, temp_ptr->node_name, temp_length - 2);
						strcpy (temp_node_name + temp_length - 2, "");
						break;
				}
				match_node_array[match_index] = (char *) calloc (50, sizeof (char));
				strcpy (match_node_array[match_index], temp_node_name);
				++match_index;
				break;
			case reference_node:
				switch (temp_ptr->d_s_method)
				{
					case ref_direct_product:
						strncpy (temp_node_name, temp_ptr->node_name, temp_length);
						strcpy (temp_node_name + temp_length, "");
						break;
					case ref_discriminated_union:
						strncpy (temp_node_name, temp_ptr->node_name, temp_length - 1);
						strcpy (temp_node_name + temp_length - 1, "");
						break;
					case ref_sequence_1:
						strncpy (temp_node_name, temp_ptr->node_name, temp_length - 1);
						strcpy (temp_node_name + temp_length - 1, "");
						break;
					case ref_sequence_2:
						p = (char *) strchr (temp_ptr->node_name, '(');
						if (p != NULL)
							p_length = strlen (p);
						else
							p_length = 0; /* If there is no '(' in the name */
						strncpy (temp_node_name, temp_ptr->node_name, temp_length - p_length);
						strcpy (temp_node_name + temp_length - p_length, "");
						break;
					case ref_sequence_3:
						strncpy (temp_node_name, temp_ptr->node_name, temp_length - 2);
						strcpy (temp_node_name + temp_length - 2, "");
						break;
				}
				refer_node_array[refer_index] = (char *) calloc (50, sizeof (char));
				strcpy (refer_node_array[refer_index], temp_node_name);
				++refer_index;
				break;
		}
		temp_ptr = temp_ptr->next;
	}
	free (temp_node_name);
}

/* ------------------------------------ */
/* List All Semantic Errors for display */
/* ------------------------------------ */

void            semantic_listing (void)
{
	int             position;
	XmString        temp_xm_string;
	char           *temp_string;
	XmStringCharSet charset = XmSTRING_DEFAULT_CHARSET;

	num_of_list_items = 0;
	temp_string = (char *) calloc (80, sizeof (char));
	strcpy (temp_string, "");
	position = 1;
	while (error_log[position] != NULL)
	{
	/* --------------------------- */
	/* formulate the output string */
	/* --------------------------- */
		temp_xm_string = XmStringCreate (error_log[position]->message, charset);
		XmListAddItemUnselected (semantic_list, temp_xm_string, position);
		XmStringFree (temp_xm_string);
		num_of_list_items = num_of_list_items + 1;
		position = position + 1;
	}
}


/*******************************************************************************
 * FUNCTION:	REMOVE_SEMANTIC_LISTING
 *
 * PURPOSE:	Remove All Semantic Errors for display.
 *
 * NOTE:	Called by editing_proc() in xdesc1.c, which is a
 *		ButtonPressMask event handler for drawing_area.
 ******************************************************************************/
void            remove_semantic_listing (void)
{
	int             i;

	if (num_of_list_items > 0)
		XmListDeleteAllItems (semantic_list);
/* ------------------------------------- */
/* FREE ALL DYNAMICALLY ALLOCATED MEMORY */
/* ------------------------------------- */
	for (i = 0; i < arg_num; ++i)
	{
		if (arguments_array[i])
			free (arguments_array[i]);
		arguments_array[i] = NULL;
	}
	for (i = 0; i < match_index; ++i)
	{
		if (match_node_array[i])
			free (match_node_array[i]);
		match_node_array[i] = NULL;
	}
	for (i = 0; i < refer_index; ++i)
	{
		if (refer_node_array[i])
			free (refer_node_array[i]);
		refer_node_array[i] = NULL;
	}
}


/*******************************************************************************
 * FUNCTION:	SEMANTIC_ANALYSIS
 *
 *	XmNactivateCallback function for the XmPushButton widget entry2_2
 *	("Semantic Analysis") in main().
 ******************************************************************************/

void            semantic_analysis (Widget w, caddr_t client_data, XEvent * event_info)
{
	char           *p;
	int             i,
	                j,
	                no_match[30],
	                matched,
	                temp_length,
	                ds_method,
	                p_length;
	int             comp_result,
	                error_index;
	int             calloc_length;
	char           *temp_node_name;
	struct node    *temp_ptr;
	struct error_item *search_front_ptr,
	               *search_behind_ptr;
	char           *q,
	               *lower_bound_string,
	               *upper_bound_string;
	int             first_time,
	                copy_length,
	                is_numerical,
	                lower_bound,
	                upper_bound;

	temp_node_name = (char *) calloc (80, sizeof (char));
/* ------------------ */
/* Reset all elements */
/* ------------------ */
	for (i = 0; i < 30; ++i)
	{
		no_match[i] = FALSE;
		error_log[i] = NULL;
	}

/* error_index_begins with 1 not 0 */
	error_index = 1;

/* ----------------------------------------- */
/* Prepare data for faster SEMANTIC ANALYSIS */
/* ----------------------------------------- */
	recognize_match_or_refer_nodes ();
	arg_num = recognize_input_arguments (template_tree_pointer->next->node_name);

/* ------ */
/* RULE 1 */
/* ------ */
	if (template_tree_pointer->level != NULL)
	{
		for (i = 0; i < arg_num; ++i)
		{
			matched = FALSE;
			temp_ptr = template_tree_pointer->next->level;
			while (temp_ptr != NULL && matched != TRUE)
			{
			/* -------------------------- */
			/* process only ANALYSIS TREE */
			/* -------------------------- */
				if (temp_ptr->tree_type == analysis_tree)
				{
					temp_length = temp_ptr->name_length;
					ds_method = temp_ptr->d_s_method;

					switch (ds_method)
					{
						case ref_direct_product:
							strncpy (temp_node_name, temp_ptr->node_name, temp_length);
							break;
						case ref_discriminated_union:
							strncpy (temp_node_name, temp_ptr->node_name, temp_length - 1);
							strcpy (temp_node_name + temp_length - 1, "");
							break;
						case ref_sequence_1:
							strncpy (temp_node_name, temp_ptr->node_name, temp_length - 1);
							strcpy (temp_node_name + temp_length - 1, "");
							break;
						case ref_sequence_2:
							p = (char *) strchr (temp_ptr->node_name, '(');
							if (p != NULL)
								p_length = strlen (p);
							else
								p_length = 0; /* If there is no '(' in the name */
							strncpy (temp_node_name, temp_ptr->node_name, temp_length - p_length);
							strcpy (temp_node_name + temp_length - p_length, "");
							break;
						case ref_sequence_3:
							strncpy (temp_node_name, temp_ptr->node_name, temp_length - 2);
							strcpy (temp_node_name + temp_length - 2, "");
							break;
						default:
							strcpy (temp_node_name, "");
							break;
					}
					comp_result = strcmp (temp_node_name, arguments_array[i]);
					if (comp_result == 0)
						matched = TRUE;
				}
				temp_ptr = temp_ptr->front;
			}
			if (matched == FALSE)
			{
				error_log[error_index] = (struct error_record *)
					calloc (1, sizeof (struct error_record));
				calloc_length = strlen (arguments_array[i]) + strlen (rule_1_def) + 10;
				error_log[error_index]->message = (char *)
					calloc (calloc_length,
						sizeof (char));
				error_log[error_index]->error_node = template_tree_pointer->level;
				strcpy (error_log[error_index]->message, "[");
				strcat (error_log[error_index]->message, arguments_array[i]);
				strcat (error_log[error_index]->message, "] ");
				strcat (error_log[error_index]->message, rule_1_def);
				error_index = error_index + 1;
			}

		}		/* end for each argument */
	}			/* end if level pointer is not NULL */
/* -------------------------------------------------------------- */
/* RULE #2 : 						     */
/* The reference root node of an analysis tree must be one of the */
/* arguments appeared in the module title.			     */
/* -------------------------------------------------------------- */
	temp_ptr = template_tree_pointer->next->level;
	while (temp_ptr != NULL)
	{
		matched = FALSE;
	/* -------------------------- */
	/* process only ANALYSIS TREE */
	/* -------------------------- */
		if (temp_ptr->tree_type == analysis_tree)
		{

			temp_length = temp_ptr->name_length;
			ds_method = temp_ptr->d_s_method;

			switch (ds_method)
			{
				case ref_direct_product:
					strcpy (temp_node_name, temp_ptr->node_name);
					break;
				case ref_discriminated_union:
					strncpy (temp_node_name, temp_ptr->node_name, temp_length - 1);
					strcpy (temp_node_name + temp_length - 1, "");
					break;
				case ref_sequence_1:
					strncpy (temp_node_name, temp_ptr->node_name, temp_length - 1);
					strcpy (temp_node_name + temp_length - 1, "");
					break;
				case ref_sequence_2:
					p = (char *) strchr (temp_ptr->node_name, '(');
					if (p != NULL)
						p_length = strlen (p);
					else
						p_length = 0; /* If there is no '(' in the name */
					strncpy (temp_node_name, temp_ptr->node_name, temp_length - p_length);
					strcpy (temp_node_name + temp_length - p_length, "");
					break;
				case ref_sequence_3:
					strncpy (temp_node_name, temp_ptr->node_name, temp_length - 2);
					strcpy (temp_node_name + temp_length - 2, "");
					break;
				default:
					strcpy (temp_node_name, "");
					break;
			}
			for (i = 0; i < arg_num; ++i)
			{
				comp_result = strcmp (temp_node_name, arguments_array[i]);
				if (comp_result == 0)
					matched = TRUE;
			}
			if (matched == FALSE)
			{
				error_log[error_index] = (struct error_record *)
					calloc (1, sizeof (struct error_record));
				calloc_length = strlen (temp_ptr->node_name) + strlen (rule_2_def) + 10;
				error_log[error_index]->message = (char *)
					calloc (calloc_length,
						sizeof (char));
				error_log[error_index]->error_node = temp_ptr;
				strcpy (error_log[error_index]->message, "[");
				strcat (error_log[error_index]->message, temp_ptr->node_name);
				strcat (error_log[error_index]->message, "] ");
				strcat (error_log[error_index]->message, rule_2_def);
				error_index = error_index + 1;
			}
		}
		temp_ptr = temp_ptr->front;
	}

/* -------------------------------------------------------------- */
/* RULE #6							     */
/* The reference root node of an analysis tree must be one of the */
/* arguments appeared in the module title.			     */
/* -------------------------------------------------------------- */
	temp_ptr = template_tree_pointer->next->next;
	while (temp_ptr != NULL)
	{
		strcpy (temp_node_name, "\0");
		matched = FALSE;
		if (temp_ptr->node_type == reference_node)
		{
			temp_length = temp_ptr->name_length;
			switch (temp_ptr->d_s_method)
			{
				case ref_direct_product:
					strncpy (temp_node_name, temp_ptr->node_name, temp_length);
					strcpy (temp_node_name + temp_length, "");
					break;
				case ref_discriminated_union:
					strncpy (temp_node_name, temp_ptr->node_name, temp_length - 1);
					strcpy (temp_node_name + temp_length - 1, "");
					break;
				case ref_sequence_1:
					strncpy (temp_node_name, temp_ptr->node_name, temp_length - 1);
					strcpy (temp_node_name + temp_length - 1, "");
					break;
				case ref_sequence_2:
					p = (char *) strchr (temp_ptr->node_name, '(');
					if (p != NULL)
						p_length = strlen (p);
					else
						p_length = 0; /* If there is no '(' in the name */
					strncpy (temp_node_name, temp_ptr->node_name, temp_length - p_length);
					strcpy (temp_node_name + temp_length - p_length, "");
					break;
				case ref_sequence_3:
					strncpy (temp_node_name, temp_ptr->node_name, temp_length - 2);
					strcpy (temp_node_name + temp_length - 2, "");
					break;
			}
			for (i = 0; i < arg_num; ++i)
			{
				comp_result = strcmp (temp_node_name, arguments_array[i]);
				if (comp_result == 0)
					matched = TRUE;
			}
			if (matched == FALSE)
			{
				for (i = 0; i < match_index; ++i)
				{

					j = 0;
					while (*(temp_node_name + j) != '\0')
					{
						*(temp_node_name + j) = tolower (*(temp_node_name + j));
						++j;
					}
					comp_result = strcmp (temp_node_name, match_node_array[i]);
					if (comp_result == 0)
						matched = TRUE;
				}
			}

			if (matched == FALSE)
			{
				error_log[error_index] = (struct error_record *)
					calloc (1, sizeof (struct error_record));
				calloc_length = strlen (rule_3_def) + 5;
				error_log[error_index]->message = (char *)
					calloc (calloc_length,
						sizeof (char));
				error_log[error_index]->error_node = temp_ptr;
				strcpy (error_log[error_index]->message, rule_3_def);
				error_index = error_index + 1;
			}
		}
		temp_ptr = temp_ptr->next;
	}
/* --------------------------------------------------------- */
/* RULE #4 : 						 */
/* A discriminated union should have two or more immediate	 */
/* children							 */
/* --------------------------------------------------------- */
	temp_ptr = template_tree_pointer->next;
	while (temp_ptr != NULL)
	{
		if (temp_ptr->d_s_method == ref_discriminated_union ||
				temp_ptr->d_s_method == mat_discriminated_union)
		{
			matched = FALSE;
			if (temp_ptr->level != NULL)
			{
				if (temp_ptr->level->front != NULL)
				{
					matched = TRUE;
				}
			}
			if (matched == FALSE)
			{
				error_log[error_index] = (struct error_record *)
					calloc (1, sizeof (struct error_record));
				calloc_length = strlen (rule_4_def) + 5;
				error_log[error_index]->message = (char *)
					calloc (calloc_length,
						sizeof (char));
				error_log[error_index]->error_node = temp_ptr;
				strcpy (error_log[error_index]->message, rule_4_def);
				error_index = error_index + 1;
			}
		}
		temp_ptr = temp_ptr->next;
	}

/* --------------------------------------------------------- */
/* RULE #5 : 						 */
/* A SEQUENCE NODE ALWAYS HAS AT LEAST ONE (1) IMMEDIATE	 */
/* CHILDREN							 */
/* --------------------------------------------------------- */
	temp_ptr = template_tree_pointer->next;
	while (temp_ptr != NULL)
	{
		if (temp_ptr->d_s_method == ref_sequence_1 ||
				temp_ptr->d_s_method == ref_sequence_2 ||
				temp_ptr->d_s_method == ref_sequence_3 ||
				temp_ptr->d_s_method == mat_sequence_1 ||
				temp_ptr->d_s_method == mat_sequence_2 ||
				temp_ptr->d_s_method == mat_sequence_3)
		{
			matched = FALSE;
			if (temp_ptr->level != NULL)
			{
				matched = TRUE;
			}
			if (matched == FALSE)
			{
				error_log[error_index] = (struct error_record *)
					calloc (1, sizeof (struct error_record));
				calloc_length = strlen (rule_5_def) + 5;
				error_log[error_index]->message = (char *)
					calloc (calloc_length,
						sizeof (char));
				error_log[error_index]->error_node = temp_ptr;
				strcpy (error_log[error_index]->message, rule_5_def);
				error_index = error_index + 1;
			}
		}
		temp_ptr = temp_ptr->next;
	}
/* --------------------------------------------------------- */
/* RULE #6 : 						 */
/* UPPER BOUND MUST BE GREATER OR EQUAL TO THE LOWER BOUND	 */
/* --------------------------------------------------------- */
	lower_bound_string = (char *) calloc (10, sizeof (char));
	upper_bound_string = (char *) calloc (10, sizeof (char));
	temp_ptr = template_tree_pointer->next;
	while (temp_ptr != NULL)
	{
		if (temp_ptr->d_s_method == ref_sequence_2 ||
				temp_ptr->d_s_method == mat_sequence_2)
		{
			p = (char *) strchr (temp_ptr->node_name, '(');
			q = (char *) strchr (temp_ptr->node_name, '.');
			copy_length = (strlen (p + 1) - strlen (q));
			strncpy (lower_bound_string, p + 1, copy_length);
			p = (char *) strrchr (temp_ptr->node_name, '.');
			is_numerical = isdigit (*(p + 1));
			if (is_numerical)
			{
				strncpy (upper_bound_string, p + 1, 1);
				i = 2;
				is_numerical = isdigit (*(p + i));
			}
			while (is_numerical)
			{
				strncat (upper_bound_string, p + i, 1);
				++i;
				is_numerical = isdigit (*(p + i));
			}
			p = lower_bound_string;
			lower_bound = 0;
			while (isdigit (*p))
			{
				switch (*p)
				{
					case '0':
						lower_bound = (lower_bound * 10) + 0;
						break;
					case '1':
						lower_bound = (lower_bound * 10) + 1;
						break;
					case '2':
						lower_bound = (lower_bound * 10) + 2;
						break;
					case '3':
						lower_bound = (lower_bound * 10) + 3;
						break;
					case '4':
						lower_bound = (lower_bound * 10) + 4;
						break;
					case '5':
						lower_bound = (lower_bound * 10) + 5;
						break;
					case '6':
						lower_bound = (lower_bound * 10) + 6;
						break;
					case '7':
						lower_bound = (lower_bound * 10) + 7;
						break;
					case '8':
						lower_bound = (lower_bound * 10) + 8;
						break;
					case '9':
						lower_bound = (lower_bound * 10) + 9;
						break;
				}
				++p;
			}
			p = upper_bound_string;
			upper_bound = 0;
			while (isdigit (*p))
			{
				switch (*p)
				{
					case '0':
						upper_bound = (upper_bound * 10) + 0;
						break;
					case '1':
						upper_bound = (upper_bound * 10) + 1;
						break;
					case '2':
						upper_bound = (upper_bound * 10) + 2;
						break;
					case '3':
						upper_bound = (upper_bound * 10) + 3;
						break;
					case '4':
						upper_bound = (upper_bound * 10) + 4;
						break;
					case '5':
						upper_bound = (upper_bound * 10) + 5;
						break;
					case '6':
						upper_bound = (upper_bound * 10) + 6;
						break;
					case '7':
						upper_bound = (upper_bound * 10) + 7;
						break;
					case '8':
						upper_bound = (upper_bound * 10) + 8;
						break;
					case '9':
						upper_bound = (upper_bound * 10) + 9;
						break;
				}
				++p;
			}
			if (upper_bound < lower_bound)
			{
				error_log[error_index] = (struct error_record *)
					calloc (1, sizeof (struct error_record));
				calloc_length = strlen (rule_6_def) + 2;
				error_log[error_index]->message = (char *)
					calloc (calloc_length,
						sizeof (char));
				error_log[error_index]->error_node = temp_ptr;
				strcpy (error_log[error_index]->message, rule_6_def);
				error_index = error_index + 1;
			}
		}
		temp_ptr = temp_ptr->next;
	}
/* --------------------------------------------------------- */
/* RULE #8 : 						 */
/* MATCH NODE MUST BE UNAMBIGUOUSE				 */
/* --------------------------------------------------------- */
	for (i = 0; i < match_index; ++i)
	{
		first_time = TRUE;
		for (j = i + 1; j < match_index; ++j)
		{
			matched = strcmp (match_node_array[i], match_node_array[j]);
			if (matched == 0)
			{
				temp_ptr = template_tree_pointer;
				while (temp_ptr != NULL)
				{
					matched = (int) strcmp (temp_ptr->node_name, match_node_array[i]);
					if (matched == 0)
					{
						switch (first_time)
						{
							case TRUE:
								first_time = FALSE;
								error_log[error_index] = (struct error_record *)
									calloc (1, sizeof (struct error_record));
								calloc_length = strlen (rule_8_def) + 2;
								error_log[error_index]->message = (char *)
									calloc (calloc_length,
										sizeof (char));
								error_log[error_index]->error_node = temp_ptr;
								error_log[error_index]->item = NULL;
								strcpy (error_log[error_index]->message, rule_8_def);
								error_index = error_index + 1;
								break;
							case FALSE:
								if (error_log[error_index - 1]->item == NULL)
								{
									error_log[error_index - 1]->item = (struct error_item *)
										calloc (1, sizeof (struct error_item));
									error_log[error_index - 1]->item->error_child = temp_ptr;
									error_log[error_index - 1]->item->next = NULL;
								}
								else
								{
									search_front_ptr = error_log[error_index - 1]->item;
									search_behind_ptr = error_log[error_index - 1]->item;
									while (search_front_ptr != NULL)
									{
										search_behind_ptr = search_front_ptr;
										search_front_ptr = search_front_ptr->next;
									}
									search_behind_ptr->next = (struct error_item *)
										calloc (1, sizeof (struct error_item));
									search_front_ptr = search_behind_ptr->next;
									search_front_ptr->error_child = temp_ptr;
									search_front_ptr->next = NULL;
								}
								break;
						}
					}
					temp_ptr = temp_ptr->next;
				}
			}
		}
	}
	semantic_listing ();
}

/*******************************************************************************
 * FUNCTION:	SEMANTIC_DISPLAY
 *	XmNdefaultActionCallback function registered with semantic_list
 *	widget in main()
 ******************************************************************************/
void            semantic_display (Widget w, XtPointer client_data, XmListCallbackStruct * cbs)
{
	struct error_record *error_info;
	struct node    *bad_node;
	struct error_item *related_item;

	error_info = error_log[cbs->item_position];

/* ---------------------------- */
/* first inverse the error node */
/* ---------------------------- */
	bad_node = error_info->error_node;
	calculate_string_data (bad_node);
	real_inverse_rect_area (str_data.xleft + 1, str_data.xright - 1, str_data.ytop + 1, str_data.ybottom - 1);

/* -------------------------- */
/* then inverse related nodes */
/* -------------------------- */
	related_item = error_info->item;
	while (related_item != NULL)
	{
		calculate_string_data (related_item->error_child);
		real_inverse_rect_area (str_data.xleft + 1, str_data.xright - 1, str_data.ytop + 1, str_data.ybottom - 1);
		related_item = related_item->next;
	}
}
