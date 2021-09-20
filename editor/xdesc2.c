/*******************************************************************************
 * $Date: 1994/06/01 00:46:04 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/editor/RCS/xdesc2.c,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: xdesc2.c,v $
 * Revision 1.8  1994/06/01  00:46:04  franklin
 * Delete extraneous function declarations for functions never called
 * from this file.
 *
 * Revision 1.7  1994/06/01  00:35:35  franklin
 * Delete all unreferenced local (auto) variables.
 *
 * Revision 1.6  1994/06/01  00:08:55  franklin
 * Workaround ANSI/ISO Standard C incompatibilities with the SunOS 4.x
 * include files.
 *
 * Revision 1.5  1994/05/31  17:40:23  franklin
 * Run through the SunOS 4.1.x "indent" utility.
 *
 * Revision 1.4  1994/05/31  16:55:52  franklin
 * Null-terminate the global variable "node_name_string".  The
 * original code was copying the string "\o" instead of null-
 * terminating it.
 *
 * Revision 1.3  1994/05/31  16:41:04  franklin
 * Convert to ANSI C.  Add comment headers for functions called from xdesc1.c.
 * Get declarations of functions from other modules from the appropriate
 * header files instead of having a local copy of the declarations.
 *
 * Revision 1.2  1994/05/07  21:38:34  franklin
 * 1. Run through the Gnu "Protoize" utility.
 * 2. Changed the first parameter of draw_rubberband() from type
 *    "Display" to type "Display *".
 * 3. Added the missing graphics context parameter to the parameter list
 *    of the call to XCopyArea().
 *
 * Revision 1.1  1994/05/06  01:06:45  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif
static char    *rcsid = "@(#) $Id: xdesc2.c,v 1.8 1994/06/01 00:46:04 franklin Exp $";

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
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <Xm/Text.h>
#include <Xm/TextF.h>		       /* Declaration of XmTextFieldGetString() */
#include "editor.h"

#include "xdesc1.h"
#include "xdesc2.h"		       /* Have the compiler check the header file against the definitions in this file. */

/*******************************************************************************
 * FUNCTION:	SHOW_EDGE_REGION
 *	Display the edge_regions.  See also: no_show_edge_region
 ******************************************************************************/
void            show_edge_region (struct node * tp_tree_pointer)
{
	int             i;
	int             x1 = 0;
	int             y1 = 1;
	int             x2 = 2;
	int             y2 = 3;
	short           x,
	                y,
	                width,
	                height;
	Widget          w;

	w = drawing_area;
	i = 0;
	while (breakup_edge_region[i][0][x1] != 0 && breakup_edge_region[i][0][y1] != 0)
	{
		if (breakup_edge_region[i][0][x1] >= 0)
		{
			x = (short) (breakup_edge_region[i][0][x1] - edge_tile_width);
			y = (short) (breakup_edge_region[i][0][y1]);
			width = (short) (2 * edge_tile_width);
			height = (short) (breakup_edge_region[i][0][y2] - breakup_edge_region[i][0][y1]);
			XDrawRectangle (XtDisplay (w), XtWindow (w), theGC, x, y, width, height);
		}
		if (breakup_edge_region[i][1][x1] >= 0)
		{
			x = (short) (breakup_edge_region[i][1][x1]);
			y = (short) (breakup_edge_region[i][1][y1] - edge_tile_width);
			width = (short) (breakup_edge_region[i][1][x2] - breakup_edge_region[i][1][x1]);
			height = (short) (2 * edge_tile_width);
			XDrawRectangle (XtDisplay (w), XtWindow (w), theGC, x, y, width, height);
		}
		if (breakup_extra_region[i][front_empty][x1] != 0 &&
				breakup_extra_region[i][front_empty][y1] != 0)
		{
			x = (short) (breakup_extra_region[i][front_empty][x1] - edge_tile_width);
			y = (short) (breakup_extra_region[i][front_empty][y1]);
			width = (short) (2 * edge_tile_width);
			height = (short) (breakup_extra_region[i][front_empty][y2] - breakup_extra_region[i][front_empty][y1]);
			XDrawRectangle (XtDisplay (w), XtWindow (w), theGC, x, y, width, height);
		}
		if (breakup_extra_region[i][level_need][x1] != 0 &&
				breakup_extra_region[i][level_need][y1] != 0)
		{
			x = (short) (breakup_extra_region[i][level_need][x1]);
			y = (short) (breakup_extra_region[i][level_need][y1] - edge_tile_width);
			width = (short) (breakup_extra_region[i][level_need][x2] - breakup_extra_region[i][level_need][x1]);
			height = (short) (2 * edge_tile_width);
			XDrawRectangle (XtDisplay (w), XtWindow (w), theGC, x, y, width, height);
		}
		i = i + 1;
	}
}

/*******************************************************************************
 * FUNCTION:	NO_SHOW_EDGE_REGION
 *	Erase the edge_regions.  See also: show_edge_region
 ******************************************************************************/
void            no_show_edge_region (struct node * tp_tree_pointer)
{
	int             i;
	int             x1 = 0;
	int             y1 = 1;
	int             x2 = 2;
	int             y2 = 3;
	int             x3 = 4;
	int             y3 = 5;
	int             x4 = 6;
	int             y4 = 7;
	int             edge_end_x;
	int             edge_end_y;
	int             edge_origin_x;
	int             edge_origin_y;
	int             edge_upper_half_x;
	int             edge_upper_half_y;

	int             edge_lower_half_x;
	int             edge_lower_half_y;
	short           x,
	                y,
	                width,
	                height;
	Widget          w;

	w = drawing_area;
	i = 0;
/* XSetTile(XtDisplay(drawing_area),filledgeGC,pmap_bg); */
	while (breakup_edge_region[i][0][x1] != 0 && breakup_edge_region[i][0][y1] != 0)
	{
		x = (short) (breakup_edge_region[i][0][x1] - edge_tile_width);
		y = (short) (breakup_edge_region[i][0][y1]);
		width = (short) (2 * edge_tile_width);
		height = (short) (breakup_edge_region[i][0][y2] - breakup_edge_region[i][0][y1]);
		XDrawRectangle (XtDisplay (w), XtWindow (w), inverseGC, x, y, width, height);
		x = (short) (breakup_edge_region[i][1][x1]);
		y = (short) (breakup_edge_region[i][1][y1] - edge_tile_width);
		width = (short) (breakup_edge_region[i][1][x2] - breakup_edge_region[i][1][x1]);
		height = (short) (2 * edge_tile_width);
		XDrawRectangle (XtDisplay (w), XtWindow (w), inverseGC, x, y, width, height);
		if (breakup_extra_region[i][front_empty][x1] != 0 &&
				breakup_extra_region[i][front_empty][y1])
		{
			x = (short) (breakup_extra_region[i][front_empty][x1] - edge_tile_width);
			y = (short) (breakup_extra_region[i][front_empty][y1]);
			width = (short) (2 * edge_tile_width);
			height = (short) (breakup_extra_region[i][front_empty][y2] - breakup_extra_region[i][front_empty][y1]);
			XDrawRectangle (XtDisplay (w), XtWindow (w), inverseGC, x, y, width, height);
		}
		if (breakup_extra_region[i][level_need][x1] != 0 &&
				breakup_extra_region[i][level_need][y1])
		{
			x = (short) (breakup_extra_region[i][level_need][x1]);
			y = (short) (breakup_extra_region[i][level_need][y1] - edge_tile_width);
			width = (short) (breakup_extra_region[i][level_need][x2] - breakup_extra_region[i][level_need][x1]);
			height = (short) (2 * edge_tile_width);
			XDrawRectangle (XtDisplay (w), XtWindow (w), inverseGC, x, y, width, height);
		}

	/* ------------------------- */
	/* Replace the missing edges */
	/* ------------------------- */
		edge_end_x = edge_region[i][x4];
		edge_end_y = edge_region[i][y4];
		edge_origin_x = edge_region[i][x1];
		edge_origin_y = edge_region[i][y1];
		edge_upper_half_x = edge_region[i][x2];
		edge_upper_half_y = edge_region[i][y2];
		edge_lower_half_x = edge_region[i][x3];
		edge_lower_half_y = edge_region[i][y3];
		XDrawLine (XtDisplay (w), XtWindow (w), theGC, edge_origin_x, edge_origin_y, edge_upper_half_x, edge_upper_half_y);
		XDrawLine (XtDisplay (w), XtWindow (w), theGC, edge_upper_half_x, edge_upper_half_y, edge_lower_half_x, edge_lower_half_y);
		XDrawLine (XtDisplay (w), XtWindow (w), theGC, edge_lower_half_x, edge_lower_half_y, edge_end_x, edge_end_y);
		i = i + 1;
	}
/* XSetTile(XtDisplay(drawing_area),filledgeGC,pmap_75); */
}

/*******************************************************************************
 * FUNCTION:
 *	Check to see wether the cursor clicked in one of the legitimate regions
 *	Called from editing_proc() in xdesc1.c.
 ******************************************************************************/
int             check_region (int loc_x, int loc_y)
{
	int             x_in_range = FALSE;
	int             y_in_range = FALSE;
	int             in_range = FALSE;
	int             select,
	                range_min,
	                range_max;
	int             i = 1;
	int             x = 0;
	int             y = 1;

	while (region[i][y] != 0 && y_in_range == FALSE)
	{
		range_min = region[i][y];
		range_max = region[i][y] + 22;
		if (loc_y < range_max && loc_y > range_min)
			y_in_range = TRUE;
		i = i + 1;
	}
	i = 1;
	while (region[i][x] != 0 && x_in_range == FALSE)
	{
		range_min = region[i][x];
		range_max = region[i][x] + 14;
		if (loc_x < range_max && loc_x > range_min)
		{
			x_in_range = TRUE;
			select = i;
		}
		i = i + 1;
	}
	if (x_in_range == TRUE && y_in_range == TRUE)
		in_range = select;
	return (in_range);
}

/*******************************************************************************
 * FUNCTION:	CHECK_EDGE_REGION
 *
 *	See if the mouse was clicked in one of the legitimate EDGE regions.
 *	Called from editing_proc() in xdesc1.c, and from end_rubberband() in
 *	this file.
 ******************************************************************************/
int             check_edge_region (int loc_x, int loc_y)
{
	int             x1 = 0;
	int             y1 = 1;
	int             x2 = 2;
	int             y2 = 3;
	int             x_in_range = FALSE;
	int             y_in_range = FALSE;
	int             in_range = FALSE;
	int             select,
	                range_min,
	                range_max;
	int             i = 0;
	int             x = 0;
	int             y = 1;

	one_or_two = 0;
	while (breakup_edge_region[i][0][x1] != 0 && y_in_range == FALSE && i <= 49)
	{

		range_min = breakup_edge_region[i][0][y1];
		range_max = breakup_edge_region[i][0][y2];
		if (loc_y < range_max && loc_y > range_min)
		{
			range_min = breakup_edge_region[i][0][x1] - 3 * edge_tile_width;
			range_max = range_min + (6 * edge_tile_width);
			if (loc_x < range_max && loc_x > range_min)
			{
				x_in_range = TRUE;
				select = i;
				one_or_two = 1;
				y_in_range = TRUE;
				one_or_two = 0;

			}
		}
		range_min = breakup_edge_region[i][1][x1];
		range_max = breakup_edge_region[i][1][x2];
		if (loc_x < range_max && loc_x > range_min)
		{
			range_min = breakup_edge_region[i][1][y1] - 3 * edge_tile_width;
			range_max = range_min + (6 * edge_tile_width);
			if (loc_y < range_max && loc_y > range_min)
			{
				x_in_range = TRUE;
				select = i;
				one_or_two = 1;
				y_in_range = TRUE;

			}
		}
		range_min = breakup_extra_region[i][front_empty][y1];
		range_max = breakup_extra_region[i][front_empty][y2];
		if (loc_y < range_max && loc_y > range_min)
		{
			range_min = breakup_extra_region[i][front_empty][x1] - 3 * edge_tile_width;
			range_max = range_min + (6 * edge_tile_width);
			if (loc_x < range_max && loc_x > range_min)
			{
				x_in_range = TRUE;
				select = i;
				y_in_range = TRUE;
				one_or_two = 2;
			}
		}
		range_min = breakup_extra_region[i][level_need][x1];
		range_max = breakup_extra_region[i][level_need][x2];
		if (loc_x < range_max && loc_x > range_min)
		{
			range_min = breakup_extra_region[i][level_need][y1] - 3 * edge_tile_width;
			range_max = range_min + (6 * edge_tile_width);
			if (loc_y < range_max && loc_y > range_min)
			{
				x_in_range = TRUE;
				select = i;
				one_or_two = 3;
				y_in_range = TRUE;
			}
		}
		i = i + 1;
	}
	if (x_in_range == TRUE && y_in_range == TRUE)
		in_range = select;
	return (in_range);
}

/*******************************************************************************
 * FUNCTION:	PREORDER_LOCATE_LAST_DESC
 *	Utility used in several places in this file, and by del_node_proc() in
 *	xdesc1.c
 ******************************************************************************/
struct node    *preorder_locate_last_desc (struct node * subtree_pointer)
{
	struct node    *temp_ptr,
	               *child_ptr;

	child_ptr = subtree_pointer;
	if (subtree_pointer != 0)
	{
		temp_ptr = preorder_locate_last_desc (subtree_pointer->level);
		if (temp_ptr != 0)
			child_ptr = temp_ptr;
		temp_ptr = preorder_locate_last_desc (subtree_pointer->front);
		if (temp_ptr != 0)
			child_ptr = temp_ptr;
	}
	return (child_ptr);
}

/*
 * struct node *preorder_locate_longest(subtree_pointer) struct node
 * *subtree_pointer; { struct node *temp_ptr, *child_ptr, *longest_ptr;
 * 
 * child_ptr = subtree_pointer; longest_ptr = subtree_pointer; if
 * (subtree_pointer != 0) { temp_ptr =
 * preorder_locate_last_desc(subtree_pointer->level); if (temp_ptr != 0) {
 * child_ptr = temp_ptr; if (longest_ptr->name_length <
 * temp_ptr->name_length) longest_ptr = temp_ptr; { temp_ptr =
 * preorder_locate_last_desc(subtree_pointer->front); if (temp_ptr != 0) {
 * child_ptr = temp_ptr; if (longest_ptr->name_length <
 * temp_ptr->name_length) longest_ptr = temp_ptr; { } return(child_ptr); }
 */

void            preorder (struct node * subtree_pointer)
{
	Widget          w = drawing_area;
	text_data_ptr   data_ptr;

	data_ptr = &data;
	if (subtree_pointer != 0)
	{
		calculate_string_data (subtree_pointer);
		inverse_rect_area (str_data.origion_x + 1, str_data.xright - 1, str_data.ytop + 1, str_data.ybottom - 1);
		preorder (subtree_pointer->level);
		preorder (subtree_pointer->front);
	}
}

void            preorder_modi_location (struct node * subtree_pointer, int x_difference)
{
	if (subtree_pointer != 0)
	{
		subtree_pointer->origion_x = (subtree_pointer->origion_x) + x_difference;
		preorder_modi_location (subtree_pointer->level, x_difference);
		preorder_modi_location (subtree_pointer->front, x_difference);
	}
}

void            preorder_modi_location_y (struct node * subtree_pointer, int y_difference)
{
	if (subtree_pointer != 0)
	{
		subtree_pointer->origion_y = (subtree_pointer->origion_y) + y_difference;
		preorder_modi_location_y (subtree_pointer->level, y_difference);
		preorder_modi_location_y (subtree_pointer->front, y_difference);
	}
}
void            preorder_modi_col (struct node * subtree_pointer, int col_difference)
{
	if (subtree_pointer != 0)
	{
		subtree_pointer->col = subtree_pointer->col + col_difference;
		preorder_modi_col (subtree_pointer->level, col_difference);
		preorder_modi_col (subtree_pointer->front, col_difference);
	}
}

void            move_insert_modi_col (struct node * subtree_pointer, int col_difference)
{
	if (subtree_pointer != 0)
	{
		subtree_pointer->col = subtree_pointer->col + col_difference;
		move_insert_modi_col (subtree_pointer->level, col_difference);
		move_insert_modi_col (subtree_pointer->front, col_difference);
	}
}


void            move_insert_modi_row (struct node * subtree_pointer, int row_difference)
{
	if (subtree_pointer != 0)
	{
		subtree_pointer->row = subtree_pointer->row + row_difference;
		move_insert_modi_row (subtree_pointer->level, row_difference);
		move_insert_modi_row (subtree_pointer->front, row_difference);
	}
}

/*******************************************************************************
 * FUNCTION:	CLEAR_SUBTREE
 *
 *	Called from del_node_proc(), which is an XmNactivateCallback function
 *	of the XmPushButton widget pb1 ("DELETE") in main().
 ******************************************************************************/
void            clear_subtree (struct node * subtree_pointer)
{
	Widget          w;
	text_data_ptr   data_ptr;

	data_ptr = &data;
	w = drawing_area;
	if (subtree_pointer != 0)
	{
		calculate_string_data (subtree_pointer);
		clear_rect_area (str_data.origion_x + 1, str_data.xright - 1, str_data.ytop + 1, str_data.ybottom - 1);
		XDrawString (XtDisplay (w), XtWindow (w), theGC, str_data.text_origion_x, str_data.text_origion_y, subtree_pointer->node_name, strlen (subtree_pointer->node_name));
		clear_subtree (subtree_pointer->level);
		clear_subtree (subtree_pointer->front);
	}
}

/*******************************************************************************
 * FUNCTION:	CHECK_EXISTING_REGION
 *	Called from editing_proc() in xdesc1.c.  editing_proc() is an event
 *	handler for the drawing_area widget.
 ******************************************************************************/
void            check_existing_region (struct node * tp_pointer, int pos_x, int pos_y, XEvent * event_info)
{
	struct node    *check_pointer;
	int             in_region = FALSE;
	int             node_rect_xright;
	int             node_rect_ybottom;
	GC              tempGC;
	text_data_ptr   data_ptr;
	Widget          w;

	data_ptr = &data;
	w = drawing_area;
	check_pointer = tp_pointer->next;
	while (check_pointer != 0 && in_region == FALSE)
	{
		calculate_string_data (check_pointer);
		node_rect_xright = str_data.xright;
		node_rect_ybottom = str_data.ybottom;

		if (pos_x >= str_data.origion_x && pos_x <= node_rect_xright)

		{
			if (pos_y >= str_data.origion_y && pos_y <= node_rect_ybottom)
				in_region = TRUE;
		}
		if (in_region == TRUE)
		{
			switch (event_info->xbutton.button)
			{
				case Button1:
					if (block_head != 0)	/* A modify block already exist */
					{
						if (block_head->origion_x == str_data.origion_x && block_head->origion_y == str_data.origion_y)
						{
							clear_rect_area (str_data.xleft + 1, node_rect_xright - 1, str_data.ytop + 1, node_rect_ybottom - 1);
							XDrawString (XtDisplay (w), XtWindow (w), theGC, str_data.text_origion_x, str_data.text_origion_y, check_pointer->node_name, strlen (check_pointer->node_name));
							clear_subtree (block_head->level);
							block_tail = 0;
							block_head = 0;
						}
					}
					else
					{
						tempGC = theGC;
						XSetFunction (XtDisplay (w), tempGC, GXinvert);
						inverse_rect_area (str_data.xleft + 1, node_rect_xright - 1, str_data.ytop + 1, node_rect_ybottom - 1);
						XSetFunction (XtDisplay (w), tempGC, GXcopy);
						block_head = check_pointer;
					}
					break;
				case Button2:
					if (block_head != 0 && block_tail == 0)
					{
						if (block_head->level != 0)
						{
							preorder (block_head->level);
							block_tail = preorder_locate_last_desc (block_head->level);
						}
					}
					break;
			}
		}
		check_pointer = check_pointer->next;
	}
}



















/*******************************************************************************
 * FUNCTION:	LOCATE_ANCESTER
 ******************************************************************************/
struct node    *locate_ancester (struct node * tp_pointer, struct node * current_pointer, struct node * parent_pointer,
				                 struct node * back_pointer, int new_row, int new_col)
{
	int             parent_located = FALSE;
	int             back_located = FALSE;
	struct node    *temp_pointer;

	temp_pointer = current_pointer;
	while (temp_pointer != 0 && parent_located == FALSE)
	{
		if (temp_pointer->col == (new_col - 1))
		{
			parent_pointer = temp_pointer;
			parent_located = TRUE;
		}
		temp_pointer = temp_pointer->before;
	}
	return (parent_pointer);
}

struct node    *locate_back (struct node * tp_pointer, struct node * current_pointer, struct node * parent_pointer, struct node * back_pointer, int new_row, int new_col)
{
	int             parent_located = FALSE;
	int             back_located = FALSE;
	struct node    *temp_pointer;

	temp_pointer = current_pointer;
	while (temp_pointer != 0 && back_located == FALSE)
	{
		if (temp_pointer->col == (new_col))
		{
			if (temp_pointer->row > parent_pointer->row)
			{
				back_pointer = temp_pointer;
				back_located = TRUE;
			}
		}
		temp_pointer = temp_pointer->before;
	}
	return (back_pointer);

}

/*******************************************************************************
 * FUNCTION:	PREORDER_DECREASE_COL_AND_ROW
 *	Utility function used by del_node_proc() in xdesc1.c
 ******************************************************************************/
void            preorder_decrease_col_and_row (struct node * subtree_pointer, int col_diff, int row_diff)
{
	if (subtree_pointer != 0)
	{
		subtree_pointer->col = subtree_pointer->col - col_diff;
		subtree_pointer->row = subtree_pointer->row - row_diff;
		preorder_decrease_col_and_row (subtree_pointer->level, col_diff, row_diff);
		preorder_decrease_col_and_row (subtree_pointer->front, col_diff, row_diff);
	}
}

/*******************************************************************************
 * FUNCTION:	PREORDER_DECREASE_X_AND_Y
 *
 *	Called from del_node_proc(), which is an XmNactivateCallback function
 *	of the XmPushButton widget pb1 ("DELETE") in main().
 ******************************************************************************/
void            preorder_decrease_x_and_y (struct node * subtree_pointer, int x_diff, int y_diff)
{
	if (subtree_pointer != 0)
	{
		subtree_pointer->origion_x = subtree_pointer->origion_x - x_diff;
		subtree_pointer->origion_y = subtree_pointer->origion_y - y_diff;
		preorder_decrease_x_and_y (subtree_pointer->level, x_diff, y_diff);
		preorder_decrease_x_and_y (subtree_pointer->front, x_diff, y_diff);
	}
}

struct rubber_node *preorder_create_rubber_tree (struct node * subtree_pointer, struct rubber_node * parent)
{
	text_data_ptr   data_ptr;
	struct rubber_node *new_node;

	data_ptr = &data;
	if (subtree_pointer != 0)
	{
		new_node = (struct rubber_node *) calloc (1, sizeof (struct rubber_node));
		new_node->node_name = (char *) calloc (max_node_len, sizeof (char));
		rubber_tail->next = new_node;
		new_node->before = rubber_tail;
		strcpy (new_node->node_name, subtree_pointer->node_name);
		new_node->origion_x = subtree_pointer->origion_x;
		new_node->origion_y = subtree_pointer->origion_y;
		new_node->row = subtree_pointer->row;
		new_node->col = subtree_pointer->col;
		rubber_tail = new_node;
		preorder_create_rubber_tree (subtree_pointer->level, new_node);
		preorder_create_rubber_tree (subtree_pointer->front, new_node);
	}
	return (new_node);
}

/* --------------------------------- */
/* Draw a subtree in rubberband mode */
/* --------------------------------- */
draw_rubberband (Display * d, Window w, GC gc, struct rubber_node * rubber_h)
{
	struct rubber_node *rb_tree_ptr,
	               *back_pointer;
	int             edge_origin_x;
	int             edge_origin_y;
	int             edge_end_x;
	int             edge_end_y;
	int             edge_upper_half_x;
	int             edge_upper_half_y;
	int             edge_lower_half_x;
	int             edge_lower_half_y;
	int             save_xright;
	int             save_orig_y;
	int             strange_condition = FALSE;

	rb_tree_ptr = rubber_head;
	while (rb_tree_ptr != 0)
	{
		calculate_rb_data (rb_tree_ptr);
		save_xright = str_data.xright;
		save_orig_y = str_data.origion_y;
		XDrawString (XtDisplay (drawing_area), XtWindow (drawing_area), xorGC, str_data.text_origion_x,
			     str_data.text_origion_y, rb_tree_ptr->node_name,
			     strlen (rb_tree_ptr->node_name));
		XDrawLine (XtDisplay (drawing_area), XtWindow (drawing_area), xorGC, str_data.xleft, str_data.ytop,
			   str_data.xright, str_data.ytop);
		XDrawLine (XtDisplay (drawing_area), XtWindow (drawing_area), xorGC, str_data.xright, str_data.ytop + 1,
			   str_data.xright, str_data.ybottom - 1);
		XDrawLine (XtDisplay (drawing_area), XtWindow (drawing_area), xorGC, str_data.xright, str_data.ybottom,
			   str_data.xleft, str_data.ybottom);
		XDrawLine (XtDisplay (drawing_area), XtWindow (drawing_area), xorGC, str_data.xleft, str_data.ybottom - 1,
			   str_data.xleft, str_data.ytop + 1);

	/* draw connecting edge */
		if (rb_tree_ptr == rubber_head)
		{
			edge_origin_x = str_data.xright;
			edge_origin_y = str_data.origion_y + text_border_margin + str_data.ascent;
			edge_upper_half_x = str_data.xleft - node_to_node_half_space + 1;
			edge_upper_half_y = str_data.origion_y + text_border_margin + str_data.ascent;
			edge_end_x = str_data.xleft - 1;
			XDrawLine (XtDisplay (drawing_area), XtWindow (drawing_area), xorGC, edge_upper_half_x, edge_upper_half_y, edge_end_x, edge_upper_half_y);
		}
		else
		{
			edge_end_x = str_data.xleft;
			edge_end_y = str_data.origion_y + text_border_margin + str_data.ascent;
			back_pointer = rb_tree_ptr;
			if (edge_end_x < edge_origin_x)
			{
				while (back_pointer->col != rb_tree_ptr->col ||
						back_pointer->row >= rb_tree_ptr->row)
					back_pointer = back_pointer->before;
				calculate_rb_data (back_pointer);
				edge_origin_x = str_data.xleft;
				edge_origin_y = str_data.origion_y + text_border_margin + str_data.ascent;
				strange_condition = TRUE;
			}
			if (strange_condition == TRUE)
			{
				edge_upper_half_x = edge_origin_x - node_to_node_half_space + 1;
				edge_upper_half_y = edge_origin_y + 1;
				edge_lower_half_x = edge_upper_half_x;
				edge_lower_half_y = edge_end_y;
				XDrawLine (XtDisplay (drawing_area), XtWindow (drawing_area), xorGC, edge_upper_half_x, edge_upper_half_y, edge_lower_half_x, edge_lower_half_y);
				XDrawLine (XtDisplay (drawing_area), XtWindow (drawing_area), xorGC, edge_lower_half_x, edge_lower_half_y, edge_end_x - 1, edge_end_y);
				strange_condition = FALSE;
			}
			else
			{
				edge_upper_half_x = edge_origin_x + node_to_node_half_space;
				edge_upper_half_y = edge_origin_y;
				edge_lower_half_x = edge_upper_half_x;
				edge_lower_half_y = edge_end_y;
				XDrawLine (XtDisplay (drawing_area), XtWindow (drawing_area), xorGC, edge_origin_x + 1, edge_origin_y, edge_upper_half_x, edge_upper_half_y);
				XDrawLine (XtDisplay (drawing_area), XtWindow (drawing_area), xorGC, edge_upper_half_x, edge_upper_half_y + 1, edge_lower_half_x, edge_lower_half_y);
				XDrawLine (XtDisplay (drawing_area), XtWindow (drawing_area), xorGC, edge_lower_half_x + 1, edge_lower_half_y, edge_end_x - 1, edge_end_y);
			}
			edge_origin_x = save_xright;
			edge_origin_y = save_orig_y + str_data.ascent + text_border_margin;
		}
		rb_tree_ptr = rb_tree_ptr->next;
	}
}

/* -------------------- */
/* Continue rubber-band */
/* -------------------- */
continue_rubberband (Widget w, caddr_t data, XEvent * p_event)
{
	int             new_x = p_event->xbutton.x,
	                new_y = p_event->xbutton.y,
	                x_diff,
	                y_diff,
	                x = 0,
	                y = 1;
	struct rubber_node *temp_ptr = rubber_head;
	int             narg;
	int             view_area_height,
	                view_area_width;
	int             scroll_mode,
	                old_bar_value;
	Arg             args[5];
	Widget          h_scroll_bar,
	                view_area;
	int             move_dist = 15;

/* Draw once at the old location */
	draw_rubberband (XtDisplay (w), XtWindow (w), xorGC, rubber_head);

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ */
/* The follow codes takes care of Automatic Scrolling */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++ */
	if (new_x < (visible.x_right - 15) && new_y < (visible.y_bottom - 15))
		scroll_mode = No_Scroll;
	else
	{
		if (new_x >= (visible.x_right - 15))
			scroll_mode = X_Scroll;
		else
			scroll_mode = Y_Scroll;
	}
	switch (scroll_mode)
	{
		case X_Scroll:
			narg = 0;
			XtSetArg (args[narg], XmNhorizontalScrollBar, &h_scroll_bar);
			narg++;
			XtSetArg (args[narg], XmNworkWindow, &view_area);
			narg++;
			XtGetValues (main_shell, args, narg);
			narg = 0;
			XtSetArg (args[narg], XmNheight, &view_area_height);
			narg++;
			XtSetArg (args[narg], XmNwidth, &view_area_width);
			narg++;
			XtGetValues (view_area, args, narg);
			narg = 0;
			XtSetArg (args[narg], XmNvalue, &old_bar_value);
			narg++;
			XtGetValues (h_scroll_bar, args, narg);
		/* -------------------------------- */
		/* Scroll the horizontal scroll_bar */
		/* -------------------------------- */
			old_bar_value = old_bar_value + move_dist;
			narg = 0;
			XtSetArg (args[narg], XmNvalue, old_bar_value);
			narg++;
			XtSetValues (h_scroll_bar, args, narg);

		/* ------------------------ */
		/* Update VISIBLE structure */
		/* ------------------------ */
			visible.x_left = visible.x_left + move_dist;
			visible.x_right = visible.x_right + move_dist;

		/* -------------------------- */
		/* Update VIEW_AREA structure */
		/* -------------------------- */

		/*
		 * NOTE: The original call to XCopyArea() was missing the
		 * graphic context parameter. I am guessing that it is either
		 * theGC or xorGC. Malcolm Franklin 5/7/94 ALSO NOTE: that
		 * the view_area_height and view_area_width parameters may be
		 * swapped.
		 */
			fflush (stderr);
			fflush (stdout);
			printf ("*--- Making suspicious call to XCopyArea() at line %d of %s ---*\n\n", __LINE__, __FILE__);
			XCopyArea (XtDisplay (drawing_area), XtWindow (drawing_area), XtWindow (view_area), theGC,
				   visible.x_left, visible.y_top, view_area_height, view_area_width, 0, 0);
			break;
		case Y_Scroll:
			break;
	}
/* ++++++++++++++++++++++++++ */
/* End of Automatic Scrolling */
/* ++++++++++++++++++++++++++ */

/* Now update and redraw */
	x_diff = new_x - rubber_position[x];
	y_diff = new_y - rubber_position[y];
	while (temp_ptr != 0)
	{
		temp_ptr->origion_x = temp_ptr->origion_x + x_diff;
		temp_ptr->origion_y = temp_ptr->origion_y + y_diff;
		temp_ptr = temp_ptr->next;
	}
	draw_rubberband (XtDisplay (w), XtWindow (w), xorGC, rubber_head);
	rubber_position[x] = new_x;
	rubber_position[y] = new_y;
}

/*----------------------
  Erase the edge_regions
 -----------------------*/
void            negate_edge_region (struct node * head, struct node * tail)
{
	int             i;
	int             x1 = 0;
	int             y1 = 1;
	int             x2 = 2;
	int             y2 = 3;
	int             x3 = 4;
	int             y3 = 5;
	int             x4 = 6;
	int             y4 = 7;
	int             edge_head_index,
	                edge_tail_index;

	printf ("I am in NEGATE\n");
	i = 0;
	while (insert_mode_block_tail[i]->row != tail->row)
	{
		++i;
	}
	edge_tail_index = i + 1;
	i = 0;
	if (head != tail)
	{
		while (insert_mode_block_head[i]->row != head->row)
			++i;
		edge_head_index = i - 1;
	}
	else
	{
		edge_head_index = edge_tail_index - 1;
	}

	i = edge_head_index;
	while (breakup_edge_region[i][0][x1] != 0 && breakup_edge_region[i][0][y1] != 0 && i <= edge_tail_index)
	{
		if (head != tail)
		{
			if (i < edge_tail_index)
			{
				breakup_edge_region[i][0][x1] = -1;
				breakup_edge_region[i][0][y1] = -1;
				breakup_edge_region[i][0][x2] = -1;
				breakup_edge_region[i][0][y2] = -1;
				breakup_edge_region[i][1][x1] = -1;
				breakup_edge_region[i][1][y1] = -1;
				breakup_edge_region[i][1][x2] = -1;
				breakup_edge_region[i][1][y2] = -1;
				breakup_extra_region[i][front_empty][x1] = 0;
				breakup_extra_region[i][front_empty][y1] = 0;
				breakup_extra_region[i][front_empty][x2] = 0;
				breakup_extra_region[i][front_empty][y2] = 0;
				breakup_extra_region[i][level_need][x1] = 0;
				breakup_extra_region[i][level_need][y1] = 0;
				breakup_extra_region[i][level_need][x2] = 0;
				breakup_extra_region[i][level_need][y2] = 0;
			}
			else
			{
				if (head->ancester == insert_mode_block_head[i])
				{
					breakup_edge_region[i][0][x1] = -1;
					breakup_edge_region[i][0][y1] = -1;
					breakup_edge_region[i][0][x2] = -1;
					breakup_edge_region[i][0][y2] = -1;
				}
			}
		}
		else
		{
			if (head->level != 0)
			{
				if (i < edge_tail_index)
				{
					breakup_edge_region[i][0][x1] = -1;
					breakup_edge_region[i][0][y1] = -1;
					breakup_edge_region[i][0][x2] = -1;
					breakup_edge_region[i][0][y2] = -1;
					breakup_edge_region[i][1][x1] = -1;
					breakup_edge_region[i][1][y1] = -1;
					breakup_edge_region[i][1][x2] = -1;
					breakup_edge_region[i][1][y2] = -1;
					breakup_extra_region[i][front_empty][x1] = 0;
					breakup_extra_region[i][front_empty][y1] = 0;
					breakup_extra_region[i][front_empty][x2] = 0;
					breakup_extra_region[i][front_empty][y2] = 0;
					breakup_extra_region[i][level_need][x1] = 0;
					breakup_extra_region[i][level_need][y1] = 0;
					breakup_extra_region[i][level_need][x2] = 0;
					breakup_extra_region[i][level_need][y2] = 0;
				}
				else
				{
					breakup_edge_region[i][1][x1] = -1;
					breakup_edge_region[i][1][y1] = -1;
					breakup_edge_region[i][1][x2] = -1;
					breakup_edge_region[i][1][y2] = -1;
				}
			}
			else
			{
				if (i < edge_tail_index)
				{
					breakup_edge_region[i][0][x1] = -1;
					breakup_edge_region[i][0][y1] = -1;
					breakup_edge_region[i][0][x2] = -1;
					breakup_edge_region[i][0][y2] = -1;
					breakup_edge_region[i][1][x1] = -1;
					breakup_edge_region[i][1][y1] = -1;
					breakup_edge_region[i][1][x2] = -1;
					breakup_edge_region[i][1][y2] = -1;
					breakup_extra_region[i][front_empty][x1] = 0;
					breakup_extra_region[i][front_empty][y1] = 0;
					breakup_extra_region[i][front_empty][x2] = 0;
					breakup_extra_region[i][front_empty][y2] = 0;
					breakup_extra_region[i][level_need][x1] = 0;
					breakup_extra_region[i][level_need][y1] = 0;
					breakup_extra_region[i][level_need][x2] = 0;
					breakup_extra_region[i][level_need][y2] = 0;
				}
			}
		}
		i = i + 1;
	}
	if (head == tail && head->level != 0)
	{
		breakup_edge_region[i][0][x1] = -1;
		breakup_edge_region[i][0][y1] = -1;
		breakup_edge_region[i][0][x2] = -1;
		breakup_edge_region[i][0][y2] = -1;
		breakup_edge_region[i][1][x1] = -1;
		breakup_edge_region[i][1][y1] = -1;
		breakup_edge_region[i][1][x2] = -1;
		breakup_edge_region[i][1][y2] = -1;
		breakup_extra_region[i][front_empty][x1] = 0;
		breakup_extra_region[i][front_empty][y1] = 0;
		breakup_extra_region[i][front_empty][x2] = 0;
		breakup_extra_region[i][front_empty][y2] = 0;
		breakup_extra_region[i][level_need][x1] = 0;
		breakup_extra_region[i][level_need][y1] = 0;
		breakup_extra_region[i][level_need][x2] = 0;
		breakup_extra_region[i][level_need][y2] = 0;
	}
	printf ("about to out NEGATE\n");
}

/* ------------------ */
/* Insert a move tree */
/* ------------------ */
void            insert_subtree (struct node * parent, struct node * front)
{
	struct node    *tp_ptr;
	struct node    *ancester = 0;
	struct node    *level = 0;
	struct node    *back = 0;
	int             single_distance;
	int             y1 = 1;
	int             col_difference,
	                row_difference;
	int             x_diff,
	                y_diff;

	erase_template_tree (parent);
/*---------------*/
/* row_col issue */
/*---------------*/
	col_difference = (parent->col + 1) - block_head->col;
	row_difference = front->row - block_head->row;
	block_head->col = block_head->col + col_difference;
	block_head->row = block_head->row + row_difference;

	x_diff = front->origion_x - block_head->origion_x;
	y_diff = front->origion_y - block_head->origion_y;
	block_head->origion_x = (block_head->origion_x) + x_diff;
	block_head->origion_y = (block_head->origion_y) + y_diff;

/* ------------------------------------------------- */
/* Only for SUBTREE, NOT, repeat NOT for SINGLE node */
/* ------------------------------------------------- */
	if (block_head != block_tail)
	{
		move_insert_modi_col (block_head->level, col_difference);
		move_insert_modi_row (block_head->level, row_difference);

		preorder_modi_location (block_head->level, x_diff);
		preorder_modi_location_y (block_head->level, y_diff);
	}

/* ----------------------------------------------------- */
/* All node after the new tree has to increase row index */
/* ----------------------------------------------------- */
	row_difference = (block_tail->row - block_head->row) + 1;
	tp_ptr = front;
	while (tp_ptr != 0)
	{
		tp_ptr->row = tp_ptr->row + row_difference;
		tp_ptr = tp_ptr->next;
	}


/* ------------------------------------------------ */
/* Update all possible link to and from the subtree */
/* ------------------------------------------------ */
/* ANCESTER */
	ancester = parent;
	if (ancester != 0)
	{
		block_head->ancester = ancester;
		if (ancester->level == 0)
			ancester->level = block_head;
		else
		{
			if (ancester->level->row > block_head->row)
				ancester->level = block_head;
		}
	}

/* BACK */
	if (front->back != 0)
	{
		block_head->back = front->back;
		front->back->front = block_head;
	}
	else
		block_head->back = 0;

/* FRONT */
	block_head->front = front;
	front->back = block_head;

/* NEXT and BEFORE */
	tp_ptr = front;
	block_tail->next = tp_ptr;
	block_head->before = tp_ptr->before;
	tp_ptr->before->next = block_head;
	tp_ptr->before = block_tail;
	block_tail->level = NULL;
	if (block_tail != block_head)
	{
		block_tail->front = NULL;
	}
	calculate_string_data (block_head);
	single_distance = (str_data.ybottom - str_data.ytop) + node_to_node_space_y;
	tp_ptr = front;
	while (tp_ptr != 0)
	{
		tp_ptr->origion_y = tp_ptr->origion_y + (row_difference * single_distance);
		tp_ptr = tp_ptr->next;
	}
/* ------------------------ */
/* multi_modules processing */
/* ------------------------ */
	increase_vertical_modules (row_difference, (row_difference * single_distance));

	display_template_tree_debug (template_tree_pointer);
	debugger (template_tree_pointer);
}


/* ------------------ */
/* Insert a move tree */
/* ------------------ */
void            insert_subtree_with_children (struct node * parent, struct node * level)
{
	struct node    *tp_ptr;
	struct node    *ancester = 0;
	int             tree_type = 0;
	int             node_type = 1;
	int             ds_method = 2;
	int             single_distance;
	int             y1 = 1;
	int             col_difference,
	                row_difference;
	int             x_diff,
	                y_diff;

	erase_template_tree (parent);
/*---------------*/
/* row_col issue */
/*---------------*/
	col_difference = (parent->col + 1) - block_head->col;
	row_difference = level->row - block_head->row;
	block_head->col = block_head->col + col_difference;
	block_head->row = block_head->row + row_difference;

	x_diff = level->origion_x - block_head->origion_x;
	y_diff = level->origion_y - block_head->origion_y;
	block_head->origion_x = (block_head->origion_x) + x_diff;
	block_head->origion_y = (block_head->origion_y) + y_diff;

/* ------------------------------------------------- */
/* Only for SUBTREE, NOT, repeat NOT for SINGLE node */
/* ------------------------------------------------- */
	if (block_head != block_tail)
	{
		move_insert_modi_col (block_head->level, col_difference);
		move_insert_modi_row (block_head->level, row_difference);

		preorder_modi_location (block_head->level, x_diff);
		preorder_modi_location_y (block_head->level, y_diff);
	}

/* ----------------------------------------------------- */
/* All node after the new tree has to increase row index */
/* ----------------------------------------------------- */
	row_difference = (block_tail->row - block_head->row) + 1;
	col_difference = (block_tail->col - block_head->col) + 1;
	tp_ptr = level;
	while (tp_ptr != 0)
	{
		tp_ptr->row = tp_ptr->row + row_difference;
		tp_ptr = tp_ptr->next;
	}
	level->col = level->col + col_difference;
	move_insert_modi_col (level->level, col_difference);


/* ------------------------------------------------ */
/* Update all possible link to and from the subtree */
/* ------------------------------------------------ */
/* ANCESTER */
	ancester = parent;
	if (ancester != 0)
	{
		block_head->ancester = ancester;
		if (ancester->level == 0)
			ancester->level = block_head;
		else
		{
			if (ancester->level == level)
				ancester->level = block_head;
		}
	}

/* BACK */
	if (level->back != 0)
	{
		block_head->back = level->back;
		level->back->front = block_head;
	}
	else
		block_head->back = 0;

/* FRONT */
	if (level->front != 0)
	{
		block_head->front = level->front;
		level->front->back = block_head;
	}
	else
		block_head->front = 0;

/* NEXT and BEFORE */
	block_tail->next = level;
	block_head->before = level->before;
	block_tail->level = level;
	level->before->next = block_head;
	level->before = block_tail;
	level->ancester = block_tail;
	level->front = NULL;
	level->back = NULL;
	calculate_string_data (block_head);
	single_distance = (str_data.ybottom - str_data.ytop) + node_to_node_space_y;
	tp_ptr = level;
	while (tp_ptr != 0)
	{
		tp_ptr->origion_y = tp_ptr->origion_y + (row_difference * single_distance);
		tp_ptr = tp_ptr->next;
	}

/* ------------------------ */
/* multi_modules processing */
/* ------------------------ */
	increase_vertical_modules (row_difference, (row_difference * single_distance));

	calculate_string_data (block_tail);
	x_diff = (str_data.xright + node_to_node_space) - block_head->origion_x;
	level->origion_x = level->origion_x + x_diff;
	preorder_modi_location (level->level, x_diff);
	display_template_tree_debug (template_tree_pointer);
	debugger (template_tree_pointer);
}

void            insert_subtree_front_empty (struct node * back)
{
	struct node    *tp_ptr,
	               *before_ptr;
	struct node    *ancester = 0;
	struct node    *level = 0;
	int             tree_type = 0;
	int             node_type = 1;
	int             ds_method = 2;
	int             single_distance;
	int             y1 = 1;
	int             col_difference,
	                row_difference;
	int             x_diff,
	                y_diff;

	erase_template_tree (back);

	before_ptr = preorder_locate_last_desc (back);
/*---------------*/
/* row_col issue */
/*---------------*/
	col_difference = (back->col) - block_head->col;
	row_difference = (before_ptr->row + 1) - block_head->row;
	block_head->col = block_head->col + col_difference;
	block_head->row = block_head->row + row_difference;

	calculate_string_data (before_ptr);
	x_diff = back->origion_x - block_head->origion_x;
	y_diff = (str_data.ybottom + node_to_node_space_y) - block_head->origion_y;
	block_head->origion_x = (block_head->origion_x) + x_diff;
	block_head->origion_y = (block_head->origion_y) + y_diff;

/* ------------------------------------------------- */
/* Only for SUBTREE, NOT, repeat NOT for SINGLE node */
/* ------------------------------------------------- */
	if (block_head != block_tail)
	{
		move_insert_modi_col (block_head->level, col_difference);
		move_insert_modi_row (block_head->level, row_difference);

		preorder_modi_location (block_head->level, x_diff);
		preorder_modi_location_y (block_head->level, y_diff);
	}

/* ----------------------------------------------------- */
/* All node after the new tree has to increase row index */
/* ----------------------------------------------------- */
	row_difference = (block_tail->row - block_head->row) + 1;
	tp_ptr = before_ptr->next;
	while (tp_ptr != 0)
	{
		tp_ptr->row = tp_ptr->row + row_difference;
		tp_ptr = tp_ptr->next;
	}


/* ------------------------------------------------ */
/* Update all possible link to and from the subtree */
/* ------------------------------------------------ */
/* ANCESTER */
	block_head->ancester = back->ancester;

/* BACK */
	block_head->back = back;
	back->front = block_head;


/* FRONT */
	block_head->front = NULL;

/* NEXT and BEFORE */
	tp_ptr = before_ptr;
	block_tail->next = tp_ptr->next;
	tp_ptr->next->before = block_tail;
	block_head->before = tp_ptr;
	tp_ptr->next = block_head;
	calculate_string_data (block_head);
	single_distance = (str_data.ybottom - str_data.ytop) + node_to_node_space_y;
	tp_ptr = block_tail->next;
	while (tp_ptr != 0)
	{
		tp_ptr->origion_y = tp_ptr->origion_y + (row_difference * single_distance);
		tp_ptr = tp_ptr->next;
	}

/* ------------------------ */
/* multi_modules processing */
/* ------------------------ */
	increase_vertical_modules (row_difference, (row_difference * single_distance));

	display_template_tree_debug (template_tree_pointer);
	debugger (template_tree_pointer);
}


/* --------------------------- */
/* Insert a subtree level_need */
/* --------------------------- */
void            insert_subtree_level_need (struct node * parent)
{
	struct node    *tp_ptr;
	struct node    *ancester = 0;
	struct node    *level = 0;
	struct node    *front = 0;
	struct node    *back = 0;
	int             tree_type = 0;
	int             node_type = 1;
	int             ds_method = 2;
	int             y1 = 1;
	int             col_difference,
	                row_difference;
	int             single_distance;
	int             x_diff,
	                y_diff;


	erase_template_tree (parent);
/*---------------*/
/* row_col issue */
/*---------------*/
	col_difference = (parent->col + 1) - block_head->col;
	row_difference = (parent->row + 1) - block_head->row;
	block_head->col = block_head->col + col_difference;
	block_head->row = block_head->row + row_difference;

	calculate_string_data (parent);
	x_diff = (str_data.xright + node_to_node_space) - block_head->origion_x;
	y_diff = (str_data.ybottom + node_to_node_space_y) - block_head->origion_y;
	block_head->origion_x = (block_head->origion_x) + x_diff;
	block_head->origion_y = (block_head->origion_y) + y_diff;

/* ------------------------------------------------- */
/* Only for SUBTREE, NOT, repeat NOT for SINGLE node */
/* ------------------------------------------------- */
	if (block_head != block_tail)
	{
		move_insert_modi_col (block_head->level, col_difference);
		move_insert_modi_row (block_head->level, row_difference);

		preorder_modi_location (block_head->level, x_diff);
		preorder_modi_location_y (block_head->level, y_diff);
	}

/* ----------------------------------------------------- */
/* All node after the new tree has to increase row index */
/* ----------------------------------------------------- */
	row_difference = (block_tail->row - block_head->row) + 1;
	tp_ptr = parent->next;
	while (tp_ptr != 0)
	{
		tp_ptr->row = tp_ptr->row + row_difference;
		tp_ptr = tp_ptr->next;
	}


/* ------------------------------------------------ */
/* Update all possible link to and from the subtree */
/* ------------------------------------------------ */
/* ANCESTER */
	block_head->ancester = parent;
	parent->level = block_head;

/* BACK */
	block_head->back = 0;

/* FRONT */
	block_head->front = 0;

/* NEXT and BEFORE */
	block_tail->next = parent->next;
	parent->next->before = block_tail;
	block_head->before = parent;
	parent->next = block_head;

	calculate_string_data (block_head);
	single_distance = (str_data.ybottom - str_data.ytop) + node_to_node_space_y;
	tp_ptr = block_tail->next;
	while (tp_ptr != 0)
	{
		tp_ptr->origion_y = tp_ptr->origion_y + (row_difference * single_distance);
		tp_ptr = tp_ptr->next;
	}
/* ------------------------ */
/* multi_modules processing */
/* ------------------------ */
	increase_vertical_modules (row_difference, (row_difference * single_distance));
	display_template_tree_debug (template_tree_pointer);
	debugger (template_tree_pointer);
}

/*******************************************************************************
 * FUNCTION:	END_RUBBERBAND
 *
 *	ButtonReleaseMask event handler for the global drawing_area widget.
 *	This function is registered in start_rubberband(), and un-registered in
 *	move_proc() below.
 ******************************************************************************/
static void     end_rubberband (Widget w, caddr_t data, XEvent * p_event)
{
	int             edge_check_result,
	                new_x = p_event->xbutton.x,
	                new_y = p_event->xbutton.y,
	                x_diff,
	                y_diff,
	                x = 0,
	                y = 1,
	                x1 = 0,
	                y1 = 1,
	                x2 = 2,
	                y2 = 3;
	caddr_t         client_data;
	XmAnyCallbackStruct *cbs;
	struct node    *temp_block_head;
	struct node    *temp_block_tail;


	struct rubber_node *next_ptr,
	               *temp_ptr = rubber_head;
	int             insert_confirmed = FALSE;
	float           ratio,
	                real_y,
	                real_x;
	int             i,
	                j;
	int             pseudo_new_x,
	                insertion_point_x;
	int             pseudo_new_y,
	                insertion_point_y;

/* Draw once at the old location */
	draw_rubberband (XtDisplay (w), XtWindow (w), xorGC, rubber_head);

/* Now update and redraw */
/* in normal theGC	    */
	x_diff = rubber_position[x] - new_x;
	y_diff = rubber_position[y] - new_y;
	while (temp_ptr != 0)
	{
		temp_ptr->origion_x = temp_ptr->origion_x + x_diff;
		temp_ptr->origion_y = temp_ptr->origion_y + y_diff;
		temp_ptr = temp_ptr->next;
	}

/* -------------------- */
/* Check_if_insert	   */
/* -------------------- */
	calculate_rb_data (rubber_head);
	insertion_point_x = str_data.xleft - node_to_node_half_space + 1;
	insertion_point_y = str_data.origion_y + text_border_margin + str_data.ascent;
	edge_check_result = check_edge_region (insertion_point_x, insertion_point_y);
	if (edge_check_result != FALSE)
	{
		insert_confirmed = TRUE;
	}
	switch (insert_confirmed)
	{
		case FALSE:
			x_diff = new_x - (block_head->origion_x + offset_from_origion[x]);
			y_diff = new_y - (block_head->origion_y + offset_from_origion[y]);
			if (x_diff < 0)
				x_diff = x_diff * (-1);
			if (y_diff < 0)
				y_diff = y_diff * (-1);
			if (x_diff > y_diff)
			{
				ratio = (float) y_diff / (float) x_diff;
				real_y = (float) rubber_position[y];
				pseudo_new_x = new_x;
				pseudo_new_y = new_y;
				for (i = new_x; i > (block_head->origion_x + offset_from_origion[x]); --i)
				{
					if (i != new_x)
						draw_rubberband (XtDisplay (w), XtWindow (w), xorGC, rubber_head);
					pseudo_new_x = i;
					real_y = real_y - ratio;
					pseudo_new_y = (int) (real_y);
					x_diff = rubber_position[x] - pseudo_new_x;
					y_diff = rubber_position[y] - pseudo_new_y;
					temp_ptr = rubber_head;
					while (temp_ptr != 0)
					{
						temp_ptr->origion_x = temp_ptr->origion_x - x_diff;
						temp_ptr->origion_y = temp_ptr->origion_y - y_diff;
						temp_ptr = temp_ptr->next;
					}
					rubber_position[x] = pseudo_new_x;
					rubber_position[y] = pseudo_new_y;
					if (i - 1 != block_head->origion_x)
						draw_rubberband (XtDisplay (w), XtWindow (w), xorGC, rubber_head);
					for (j = 0; j <= 5; ++j)
					{
					}
				}
				draw_rubberband (XtDisplay (w), XtWindow (w), xorGC, rubber_head);
				no_show_edge_region (template_tree_pointer);
				make_region (template_tree_pointer, current_node);
				eliminate_ind_region (next_p_h_array);
				display_template_tree (template_tree_pointer);
			}
			else
			{
				ratio = (float) x_diff / (float) y_diff;
				real_x = (float) rubber_position[x];
				pseudo_new_x = new_x;
				pseudo_new_y = new_y;
				for (i = new_y; i > (block_head->origion_y + offset_from_origion[y]); --i)
				{
					if (i != new_y)
						draw_rubberband (XtDisplay (w), XtWindow (w), xorGC, rubber_head);
					pseudo_new_y = i;
					real_x = real_x - ratio;
					pseudo_new_x = (int) (real_x);
					x_diff = rubber_position[x] - pseudo_new_x;
					y_diff = rubber_position[y] - pseudo_new_y;
					temp_ptr = rubber_head;
					while (temp_ptr != 0)
					{
						temp_ptr->origion_x = temp_ptr->origion_x - x_diff;
						temp_ptr->origion_y = temp_ptr->origion_y - y_diff;
						temp_ptr = temp_ptr->next;
					}
					rubber_position[x] = pseudo_new_x;
					rubber_position[y] = pseudo_new_y;
					if (i - 1 != block_head->origion_y)
						draw_rubberband (XtDisplay (w), XtWindow (w), xorGC, rubber_head);
					for (j = 0; j <= 5; ++j)
					{
					}
				}
				draw_rubberband (XtDisplay (w), XtWindow (w), xorGC, rubber_head);
				no_show_edge_region (template_tree_pointer);
				make_region (template_tree_pointer, current_node);
				eliminate_ind_region (next_p_h_array);

			}
			calculate_string_data (block_head);
			XClearArea (XtDisplay (drawing_area), XtWindow (drawing_area),
				    (short) str_data.xleft,
				    (short) str_data.ytop,
				    (short) (str_data.xright - str_data.xleft) + 1,
				    (short) (str_data.ybottom - str_data.ytop) + 1, 0);
			display_template_tree (template_tree_pointer);
			break;
		case TRUE:
			no_show_edge_region (template_tree_pointer);
			temp_block_head = block_head;
			temp_block_tail = block_tail;
			calculate_string_data (block_head);

		/* --------------------------------- */
		/* clear BLOCK_HEAD's inner bounbary */
		/* --------------------------------- */
			XClearArea (XtDisplay (drawing_area), XtWindow (drawing_area),
				    (short) str_data.xleft,
				    (short) str_data.ytop,
				    (short) (str_data.xright - str_data.xleft) + 1,
				    (short) (str_data.ybottom - str_data.ytop) + 1, 0);

		/* -------------- */
		/* first_del_node */
		/* -------------- */

		/*
		 * -- For del_node_proc_to_differenciate SINGLE NODE or TREE
		 * --
		 */
			if (block_head == block_tail)
				block_tail = 0;

		/*
		 * -----------------------------------------------------------
		 * -
		 */
			del_node_proc (w, client_data, cbs);
			clear_region_marker_display ();
			erase_template_tree (template_tree_pointer);
		/* ------------- */
		/* then insert  */
		/* ------------- */
			block_head = temp_block_head;
			block_tail = temp_block_tail;
			switch (one_or_two)
			{
				case 0:
					insert_subtree (insert_mode_block_head[edge_check_result],
							insert_mode_block_tail[edge_check_result]);
					break;
				case 1:
					insert_subtree_with_children (insert_mode_block_head[edge_check_result],
								      insert_mode_block_tail[edge_check_result]);
					break;
				case 2:
					insert_subtree_front_empty (insert_mode_block_tail[edge_check_result]);
					break;
				case 3:
					insert_subtree_level_need (insert_mode_block_tail[edge_check_result]);
					break;
			}
			make_region (template_tree_pointer, current_node);
			eliminate_ind_region (next_p_h_array);
			display_template_tree (template_tree_pointer);
			break;
	}

/* --------------------------------------------------- */
/* Free Dynamically allocated memory for "rubber_tree" */
/* --------------------------------------------------- */

	temp_ptr = rubber_head;
	while (temp_ptr != NULL)
	{
		next_ptr = temp_ptr->next;
		free (temp_ptr->node_name);
		free (temp_ptr);
		temp_ptr = next_ptr;
	}
/* --------------------------------------------------- */

	block_tail = 0;
	block_head = 0;
}
void            upper_or_lower_already_created (char *node_name, struct node * the_node)
{
	int             i = 0;

	switch (the_node->node_type)
	{
		case reference_node:
			while (*(node_name + i) != '\0')
			{
				*(node_name + i) = toupper (*(node_name + i));
				++i;
			}
			break;
		case match_node:
			while (*(node_name + i) != '\0')
			{
				*(node_name + i) = tolower (*(node_name + i));
				++i;
			}
			break;
	}
}

/* ----------------- */
/* Start rubber-band */
/* ----------------- */
start_rubberband (Widget w, caddr_t data, XEvent * p_event)
{
	int             x = 0;
	int             y = 1;
	int             x1 = 0;
	int             y1 = 1;
	int             x2 = 2;
	int             y2 = 3;
	int             i = 0;
	int             pos_x = p_event->xbutton.x;
	int             pos_y = p_event->xbutton.y;
	short           dash_upper_x,
	                dash_upper_y,
	                dash_bottom_x,
	                dash_bottom_y;

	rubber_position[x] = p_event->xbutton.x;
	rubber_position[y] = p_event->xbutton.y;
/* ------------------------------------------ */
/* check to	see if the cursor  is within the */
/* boundary of the first block in the subtree */
/* ------------------------------------------ */
	calculate_string_data (block_head);
	if (pos_x >= str_data.origion_x && pos_x <= str_data.xright)
	{
		if (pos_y >= str_data.origion_y && pos_y <= str_data.ybottom)
		{
			offset_from_origion[x] = pos_x - str_data.origion_x;
			offset_from_origion[y] = pos_y - str_data.origion_y;
			XtAddEventHandler (drawing_area, ButtonMotionMask, False, (XtEventHandler) continue_rubberband, NULL);
			XtAddEventHandler (drawing_area, ButtonReleaseMask, False, (XtEventHandler) end_rubberband, NULL);

		/*
		 * clear_subtree(block_head);
		 * erase_template_tree(block_head);
		 */

			if (block_tail != 0)
			{
				calculate_string_data (block_head);
				clear_rect_area (str_data.xleft + 1, str_data.xright - 1, str_data.ytop + 1, str_data.ybottom - 1);
				XDrawString (XtDisplay (w), XtWindow (w), theGC, str_data.text_origion_x, str_data.text_origion_y, block_head->node_name, strlen (block_head->node_name));
				clear_subtree (block_head->level);
				calculate_string_data (block_head);
				dash_upper_x = (short) (str_data.origion_x - node_to_node_half_space) + 2;
				dash_upper_y = (short) (str_data.origion_y - node_to_node_space_y + 1);
				calculate_string_data (block_tail);
				dash_bottom_x = (short) dash_upper_x;
				dash_bottom_y = (short) (str_data.ybottom + node_to_node_space_y - 1);

			/*
			 * empty_region[x1] = dash_upper_x -
			 * (short)node_to_node_half_space + 1;
			 */
				empty_region[x1] = dash_upper_x;
				empty_region[y1] = dash_upper_y;
				empty_region[x2] = (short) str_data.xright;
				empty_region[y2] = dash_bottom_y;
				clear_region_marker_display ();
				make_edge_region (template_tree_pointer);
				i = 0;
				while (breakup_edge_region[i][0][y1] != 0)
				{
					if ((short) breakup_edge_region[i][1][x2] > empty_region[x2])
					{
						calculate_string_data (insert_mode_block_tail[i]);
						empty_region[x2] = (short) (str_data.xright + 1);
					}
					if ((short) breakup_extra_region[i][level_need][x2] > empty_region[x2])
						empty_region[x2] = (short) breakup_extra_region[i][level_need][x2];
					i = i + 1;
				}
				XClearArea (XtDisplay (drawing_area), XtWindow (drawing_area),
					    empty_region[x1],
					    empty_region[y1],
					    (short) (empty_region[x2] - empty_region[x1]) + 1,
					    empty_region[y2] - empty_region[y1], 0);
				negate_edge_region (block_head, block_tail);
				show_edge_region (template_tree_pointer);
				if (block_head->front == NULL)
				{
					dash_bottom_x = dash_upper_x - 1;
					dash_bottom_y = dash_upper_y + node_to_node_space_y + str_data.ascent + text_border_margin;
					if (block_head->back != NULL)
					{
						calculate_string_data (block_head->back);
						dash_upper_y = (short) (str_data.text_origion_y) - 2;
						dash_upper_x = dash_bottom_x;
						XDrawLine (XtDisplay (drawing_area), XtWindow (drawing_area), inverseGC,
							   dash_upper_x,
							   dash_upper_y,
							   dash_bottom_x,
							   dash_bottom_y);
					}
					else
					{
						calculate_string_data (block_head);
						empty_region[x1] = (short) (str_data.origion_x - node_to_node_space) + 2;
						empty_region[x2] = str_data.xright;
						empty_region[y1] = (short) (str_data.origion_y - node_to_node_space_y - text_border_margin - str_data.descent);
						XClearArea (XtDisplay (drawing_area), XtWindow (drawing_area),
							    empty_region[x1],
							    empty_region[y1],
							    (short) (empty_region[x2] - empty_region[x1]) + 1,
							    empty_region[y2] - empty_region[y1], 0);
					}
				}
			}
			else
			{
				block_tail = block_head;
				calculate_string_data (block_head);
				dash_upper_x = (short) (str_data.origion_x);
				dash_upper_y = (short) (str_data.origion_y - node_to_node_space_y);
				calculate_string_data (block_tail);
				dash_bottom_x = (short) str_data.xright;
				dash_bottom_y = (short) (str_data.ybottom + node_to_node_space_y - 1);

			/* ------------------------------------------ */
			/* Clear Within the boundary of a SINGLE node */
			/* ------------------------------------------ */
				printf ("I am before clear_area\n");
				empty_region[x1] = (short) (str_data.xleft);
				empty_region[y1] = (short) str_data.ytop;
				empty_region[x2] = (short) str_data.xright;
				empty_region[y2] = (short) str_data.ybottom;
				XClearArea (XtDisplay (drawing_area), XtWindow (drawing_area),
					    empty_region[x1],
					    empty_region[y1],
					    (empty_region[x2] - empty_region[x1]) + 1,
					    empty_region[y2] - empty_region[y1] + 1, 0);
			/* ------------------------------------------ */

				empty_region[x1] = dash_upper_x;
				empty_region[y1] = dash_upper_y;
				empty_region[x2] = (short) str_data.xright;
				empty_region[y2] = dash_bottom_y;
				clear_region_marker_display ();
				make_edge_region (template_tree_pointer);
				i = 0;
				while (breakup_edge_region[i][0][y1] != 0)
				{
					if ((short) breakup_edge_region[i][1][x2] > empty_region[x2])
					{
						calculate_string_data (insert_mode_block_tail[i]);
						empty_region[x2] = (short) (str_data.xright + 1);
					}
					if ((short) breakup_extra_region[i][level_need][x2] > empty_region[x2])
						empty_region[x2] = (short) breakup_extra_region[i][level_need][x2];
					i = i + 1;
				}
				negate_edge_region (block_head, block_tail);
				show_edge_region (template_tree_pointer);
				if (block_head->front == NULL)
				{
					calculate_string_data (block_head);
					dash_bottom_x = (short) (str_data.xleft - node_to_node_half_space) + 1;
					dash_bottom_y = (short) (str_data.ytop + str_data.ascent + text_border_margin);
					if (block_head->back != NULL && block_head->level == NULL)
					{
						calculate_string_data (block_head->back);
						dash_upper_y = (short) (str_data.ytop + text_border_margin + str_data.ascent) + 2;
						dash_upper_x = dash_bottom_x;
						XDrawLine (XtDisplay (drawing_area), XtWindow (drawing_area), inverseGC,
							   dash_upper_x,
							   dash_upper_y,
							   dash_bottom_x,
							   dash_bottom_y);
						dash_upper_x = dash_bottom_x + node_to_node_half_space;
						dash_upper_y = dash_bottom_y;
						XDrawLine (XtDisplay (drawing_area), XtWindow (drawing_area), inverseGC,
							   dash_upper_x,
							   dash_upper_y,
							   dash_bottom_x,
							   dash_bottom_y);
					}
					else if (block_head->level == NULL)
					{
						calculate_string_data (block_head);
						empty_region[x1] = (short) (str_data.origion_x - node_to_node_space) + 1;
						empty_region[x2] = str_data.xright;
						empty_region[y1] = (short) (str_data.origion_y - node_to_node_space_y - text_border_margin - str_data.descent);
						XClearArea (XtDisplay (drawing_area), XtWindow (drawing_area),
							    empty_region[x1],
							    empty_region[y1],
							    (short) (empty_region[x2] - empty_region[x1]) + 1,
							    empty_region[y2] - empty_region[y1], 0);
					}
				}
			}
			if (block_head == block_tail && block_head->level != NULL)
			{
				calculate_string_data (block_tail);
				XDrawLine (XtDisplay (drawing_area), XtWindow (drawing_area), theGC,
					   (short) block_tail->origion_x,
					   (short) block_tail->origion_y + (text_border_margin) + str_data.ascent,
					   (short) str_data.xright,
					   (short) block_tail->origion_y + (text_border_margin) + str_data.ascent);
			}
			if (block_head == block_tail && block_head->level == NULL)
			{
				calculate_string_data (block_tail);
				XDrawLine (XtDisplay (drawing_area), XtWindow (drawing_area), inverseGC,
					   (short) ((block_tail->origion_x - node_to_node_half_space) + 2),
					   (short) block_tail->origion_y + (text_border_margin) + str_data.ascent,
					   (short) str_data.xleft,
					   (short) block_tail->origion_y + (text_border_margin) + str_data.ascent);
			}
			draw_rubberband (XtDisplay (w), XtWindow (w), xorGC, rubber_head);
		}
	}
}

/*******************************************************************************
 * FUNCTION:	MOVE_PROC
 *	XmNactivateCallback function for xmPushButton widget pb2 (MOVE) in
 *	main().
 ******************************************************************************/
void            move_proc (Widget w, caddr_t client_data, XmAnyCallbackStruct * cbs)
{
	struct rubber_node *rubber_dummy;

/* If there are actually node to be MOVE */
	if (block_head != 0)
	{
		XtRemoveEventHandler (drawing_area, ButtonPressMask, False, (XtEventHandler) editing_proc, NULL);
		XtAddEventHandler (drawing_area, ButtonPressMask, False, (XtEventHandler) start_rubberband, NULL);


		rubber_head = (struct rubber_node *) calloc (1, sizeof (struct rubber_node));
		rubber_head->node_name = (char *) calloc (max_node_len, sizeof (char));
		strcpy (rubber_head->node_name, block_head->node_name);
		rubber_head->origion_x = block_head->origion_x;
		rubber_head->origion_y = block_head->origion_y;
		rubber_head->row = block_head->row;
		rubber_head->col = block_head->col;
		rubber_head->next = NULL;
		rubber_head->before = NULL;

		rubber_tail = rubber_head;
		if (block_tail != 0)
			rubber_dummy = preorder_create_rubber_tree (block_head->level, rubber_head);
		while (block_head != 0)
		{
			XtProcessEvent (XtIMAll);	/* continue with the move operation */
		}
		XtRemoveEventHandler (drawing_area, ButtonPressMask, False, (XtEventHandler) start_rubberband, NULL);
		XtRemoveEventHandler (drawing_area, ButtonMotionMask, False, (XtEventHandler) continue_rubberband, NULL);
		XtRemoveEventHandler (drawing_area, ButtonReleaseMask, False, (XtEventHandler) end_rubberband, NULL);
		XtAddEventHandler (drawing_area, ButtonPressMask, False, (XtEventHandler) editing_proc, NULL);
	}
}

/*******************************************************************************
 * FUNCTION:	MOD_NAME_PROC
 *	XmNactivateCallback function for xmPushButton widget pb4 (NODE NAME)
 *	in main()
 ******************************************************************************/
void            mod_name_proc (Widget w, caddr_t client_data, XmAnyCallbackStruct * cbs)
{
	char            temp_node_name[80];
	int             temp_length,
	                old_name_length;
	int             ds_method;
	int             x_difference;

	if (block_head != 0 && block_tail == 0)
	{
		calculate_string_data (block_head);
		old_name_length = str_data.text_xright - str_data.text_xleft;
		temp_length = block_head->name_length;
		ds_method = block_head->d_s_method;
		switch (ds_method)
		{
			case ref_direct_product:
				strncpy (temp_node_name, block_head->node_name, temp_length);
				strcpy (temp_node_name + temp_length, "");
				break;
			case ref_discriminated_union:
				strncpy (temp_node_name, block_head->node_name, temp_length - 1);
				strcpy (temp_node_name + temp_length - 1, "");
				break;
			case ref_sequence_1:
				strncpy (temp_node_name, block_head->node_name, temp_length - 1);
				strcpy (temp_node_name + temp_length - 1, "");
				break;
			case ref_sequence_2:
				strncpy (temp_node_name, block_head->node_name, temp_length);
				strcpy (temp_node_name + temp_length, "");
				break;
			case ref_sequence_3:
				strncpy (temp_node_name, block_head->node_name, temp_length - 2);
				strcpy (temp_node_name + temp_length - 2, "");
				break;
			case mat_direct_product:
				strncpy (temp_node_name, block_head->node_name, temp_length);
				strcpy (temp_node_name + temp_length, "");
				break;
			case mat_discriminated_union:
				strncpy (temp_node_name, block_head->node_name, temp_length - 1);
				strcpy (temp_node_name + temp_length - 1, "");
				break;
			case mat_sequence_1:
				strncpy (temp_node_name, block_head->node_name, temp_length - 1);
				strcpy (temp_node_name + temp_length - 1, "");
				break;
			case mat_sequence_2:
				strncpy (temp_node_name, block_head->node_name, temp_length);
				strcpy (temp_node_name + temp_length, "");
				break;
			case mat_sequence_3:
				strncpy (temp_node_name, block_head->node_name, temp_length - 2);
				strcpy (temp_node_name + temp_length - 2, "");
				break;
		}
		*node_name_string = '\0';	/* Original code was: "strcpy(node_name_string,"\o");" */
		XmTextSetString (text_area, temp_node_name);
		XBell (XtDisplay (drawing_area), 0);
		XtProcessEvent (XtIMAll);
		while (answered == FALSE)
		{
			XtProcessEvent (XtIMAll);	/* (XtImXEvent) */
		}
		answered = FALSE;
		clear_region_marker_display ();
		strcpy (temp_node_name, node_name_string);
		calculate_string_data (block_head);
		clear_rect_area (str_data.origion_x + 1, str_data.xright - 1, str_data.origion_y + 1, str_data.ybottom - 1);
		erase_template_tree (block_head);
		switch (ds_method)
		{
			case ref_direct_product:
				strcpy (block_head->node_name, temp_node_name);
				block_head->name_length = strlen (block_head->node_name);
				break;
			case ref_discriminated_union:
				strcat (temp_node_name, "+");
				strcpy (block_head->node_name, temp_node_name);
				block_head->name_length = strlen (block_head->node_name);
				break;
			case ref_sequence_1:
				strcat (temp_node_name, "*");
				strcpy (block_head->node_name, temp_node_name);
				block_head->name_length = strlen (block_head->node_name);
				break;
			case ref_sequence_2:
				strcpy (block_head->node_name, temp_node_name);
				block_head->name_length = strlen (block_head->node_name);
				break;
			case ref_sequence_3:
				strcat (temp_node_name, "*+");
				strcpy (block_head->node_name, temp_node_name);
				block_head->name_length = strlen (block_head->node_name);
				break;
			case mat_direct_product:
				strcpy (block_head->node_name, temp_node_name);
				block_head->name_length = strlen (block_head->node_name);
				break;
			case mat_discriminated_union:
				strcat (temp_node_name, "+");
				strcpy (block_head->node_name, temp_node_name);
				block_head->name_length = strlen (block_head->node_name);
				break;
			case mat_sequence_1:
				strcat (temp_node_name, "*");
				strcpy (block_head->node_name, temp_node_name);
				block_head->name_length = strlen (block_head->node_name);
				break;
			case mat_sequence_2:
				strcpy (block_head->node_name, temp_node_name);
				block_head->name_length = strlen (block_head->node_name);
				break;
			case mat_sequence_3:
				strcat (temp_node_name, "*+");
				strcpy (block_head->node_name, temp_node_name);
				block_head->name_length = strlen (block_head->node_name);
				break;
		}
		upper_or_lower_already_created (block_head->node_name, block_head);
		calculate_string_data (block_head);
		x_difference = (str_data.text_xright - str_data.text_xleft) - old_name_length;
		preorder_modi_location (block_head->level, x_difference);
		make_region (template_tree_pointer, current_node);
		eliminate_ind_region (next_p_h_array);

		display_template_tree (template_tree_pointer);
		block_head = 0;
	}
}

/*******************************************************************************
 * FUNCTION:	MOD_DS_METHOD_PROC
 *	XmNactivateCallback function for xmPushButton widget pb5 (D-S METHOD)
 *	in main()
 ******************************************************************************/
void            mod_ds_method_proc (Widget w, caddr_t client_data, XmAnyCallbackStruct * cbs)
{
	char            temp_node_name[80];
	int             menu_value,
	                temp_length,
	                old_name_length;
	int             ds_method,
	                i,
	                x_difference;
	Pixmap          ds_method_array[5];
	Widget          d_s_menu;
	Pixmap          label_icon;
	Arg             args[10];
	XmStringCharSet charset = XmSTRING_DEFAULT_CHARSET;
	Cardinal        narg;
	char           *b_name[6];
	char           *b1 = "b1";
	char           *b2 = "b2";
	char           *b3 = "b3";
	char           *b4 = "b4";
	char           *b5 = "b5";
	char           *b6 = "b6";
	char           *p;
	int             p_length;

/* ---------------------------------------- */
/* Guarantees that ONE and only ONE node is */
/* selected for this operation	       */
/* ---------------------------------------- */
	if (block_head != 0 && block_tail == 0)
	{

		if (block_head->node_type == reference_node)
		{
			ds_method_array[0] = pix_ref_dp;
			ds_method_array[1] = pix_ref_du;
			ds_method_array[2] = pix_ref_sq1;
			ds_method_array[3] = pix_ref_sq2;
			ds_method_array[4] = pix_ref_sq3;
			b_name[0] = b1;
			b_name[1] = b2;
			b_name[2] = b3;
			b_name[3] = b4;
			b_name[4] = b5;
			b_name[5] = b6;
		}
		else
		{
			ds_method_array[0] = pix_mat_dp;
			ds_method_array[1] = pix_mat_du;
			ds_method_array[2] = pix_mat_sq1;
			ds_method_array[3] = pix_mat_sq2;
			ds_method_array[4] = pix_mat_sq3;
			b_name[0] = b1;
			b_name[1] = b2;
			b_name[2] = b3;
			b_name[3] = b4;
			b_name[4] = b5;
			b_name[5] = b6;
		}
		calculate_string_data (block_head);
		old_name_length = (str_data.xright - str_data.xleft);
		ds_method = block_head->d_s_method;

		narg = 0;
		XtSetArg (args[narg], XmNorientation, XmVERTICAL);
		narg++;
		XtSetArg (args[narg], XmNpacking, XmPACK_COLUMN);
		narg++;
		XtSetArg (args[narg], XmNx, block_head->origion_x);
		narg++;
		XtSetArg (args[narg], XmNy, block_head->origion_y);
		narg++;
		d_s_menu = XmCreatePopupMenu (drawing_area, "DS_Menu", args, narg);
		XtAddCallback (d_s_menu, XmNentryCallback, (XtCallbackProc) return_item, NULL);
		for (i = 0; i < 5; ++i)
		{
			label_icon = ds_method_array[i];
			narg = 0;
			XtSetArg (args[narg], XmNlabelType, XmPIXMAP);
			narg++;
			XtSetArg (args[narg], XmNlabelPixmap, label_icon);
			narg++;
			entry[i] = XmCreatePushButton (d_s_menu, b_name[i], args, narg);
			XtAddCallback (entry[i], XmNactivateCallback, (XtCallbackProc) never_called, (XtPointer) i);
			XtManageChild (entry[i]);
		}
		XtManageChild (d_s_menu);
		answered = FALSE;
		while (answered == FALSE)
			XtProcessEvent (XtIMAll);
		answered = FALSE;
		menu_value = selected_item;
		temp_length = block_head->name_length;
		switch (ds_method)
		{
			case ref_direct_product:
				strncpy (temp_node_name, block_head->node_name, temp_length);
				strcpy (temp_node_name + temp_length, "");
				break;
			case ref_discriminated_union:
				strncpy (temp_node_name, block_head->node_name, temp_length - 1);
				strcpy (temp_node_name + temp_length - 1, "");
				break;
			case ref_sequence_1:
				strncpy (temp_node_name, block_head->node_name, temp_length - 1);
				strcpy (temp_node_name + temp_length - 1, "");
				break;
			case ref_sequence_2:
				p = strchr (block_head->node_name, '(');
				if (p != NULL)
					p_length = strlen (p);
				strncpy (temp_node_name, block_head->node_name, temp_length - p_length);
				strcpy (temp_node_name + temp_length - p_length, "");
				break;
			case ref_sequence_3:
				strncpy (temp_node_name, block_head->node_name, temp_length - 2);
				strcpy (temp_node_name + temp_length - 2, "");
				break;
			case mat_direct_product:
				strncpy (temp_node_name, block_head->node_name, temp_length);
				strcpy (temp_node_name + temp_length, "");
				break;
			case mat_discriminated_union:
				strncpy (temp_node_name, block_head->node_name, temp_length - 1);
				strcpy (temp_node_name + temp_length - 1, "");
				break;
			case mat_sequence_1:
				strncpy (temp_node_name, block_head->node_name, temp_length - 1);
				strcpy (temp_node_name + temp_length - 1, "");
				break;
			case mat_sequence_2:
				p = strchr (block_head->node_name, '(');
				if (p != NULL)
					p_length = strlen (p);
				strncpy (temp_node_name, block_head->node_name, temp_length - p_length);
				strcpy (temp_node_name + temp_length - p_length, "");
				break;
			case mat_sequence_3:
				strncpy (temp_node_name, block_head->node_name, temp_length - 2);
				strcpy (temp_node_name + temp_length - 2, "");
				break;
		}
		calculate_string_data (block_head);
		clear_rect_area (str_data.origion_x + 1, str_data.xright - 1,
				 str_data.origion_y + 1, str_data.ybottom - 1);
		erase_template_tree (block_head);
		XtDestroyWidget (XtParent (d_s_menu));

		if (block_head->node_type == reference_node)
		{
			switch (menu_value)
			{
				case 0:
					strcpy (block_head->node_name, temp_node_name);
					block_head->name_length = strlen (block_head->node_name);
					block_head->d_s_method = ref_direct_product;
					break;
				case 1:
					strcat (temp_node_name, "+");
					strcpy (block_head->node_name, temp_node_name);
					block_head->name_length = strlen (block_head->node_name);
					block_head->d_s_method = ref_discriminated_union;
					break;
				case 2:
					strcat (temp_node_name, "*");
					strcpy (block_head->node_name, temp_node_name);
					block_head->name_length = strlen (block_head->node_name);
					block_head->d_s_method = ref_sequence_1;
					break;
				case 3:
					strcat (temp_node_name, "(..)");
					strcpy (block_head->node_name, temp_node_name);
					block_head->name_length = strlen (block_head->node_name);
					block_head->d_s_method = ref_sequence_2;
					break;
				case 4:
					strcat (temp_node_name, "*+");
					strcpy (block_head->node_name, temp_node_name);
					block_head->name_length = strlen (block_head->node_name);
					block_head->d_s_method = ref_sequence_3;
					break;
			}
		}
		else
		{
			switch (menu_value)
			{
				case 0:
					strcpy (block_head->node_name, temp_node_name);
					block_head->name_length = strlen (block_head->node_name);
					block_head->d_s_method = mat_direct_product;
					break;
				case 1:
					strcat (temp_node_name, "+");
					strcpy (block_head->node_name, temp_node_name);
					block_head->name_length = strlen (block_head->node_name);
					block_head->d_s_method = mat_discriminated_union;
					break;
				case 2:
					strcat (temp_node_name, "*");
					strcpy (block_head->node_name, temp_node_name);
					block_head->name_length = strlen (block_head->node_name);
					block_head->d_s_method = mat_sequence_1;
					break;
				case 3:
					strcat (temp_node_name, "(..)");
					strcpy (block_head->node_name, temp_node_name);
					block_head->name_length = strlen (block_head->node_name);
					block_head->d_s_method = mat_sequence_2;
					break;
				case 4:
					strcat (temp_node_name, "*+");
					strcpy (block_head->node_name, temp_node_name);
					block_head->name_length = strlen (block_head->node_name);
					block_head->d_s_method = mat_sequence_3;
					break;
			}
		}
		calculate_string_data (block_head);
		x_difference = (str_data.xright - str_data.xleft) - old_name_length;
		preorder_modi_location (block_head->level, x_difference);
		display_template_tree (template_tree_pointer);
		block_head = 0;
	}
}

/*******************************************************************************
 * FUNCTION:	START_OPEN
 *	XmNactivateCallback for global XmPushButton widget entry1 ("Open")
 *	created in main().
 ******************************************************************************/
void            start_open (Widget w, caddr_t client_data, XmAnyCallbackStruct * call_data)
{
	XtManageChild (file_select_dialog);
}

/*******************************************************************************
 * FUNCTION:	CANCEL_FILE_SELECT
 *	XmNcancelCallback for global XmFileSelectionDialog widget
 *	file_select_dialog (instance name "filesb", created in main())
 ******************************************************************************/
void            cancel_file_select (Widget w, caddr_t client_data, XmAnyCallbackStruct * call_data)
{
	XtUnmanageChild (file_select_dialog);
}

/*******************************************************************************
 * FUNCTION:	CLOSE_PROC
 *	XmNactivateCallback function for entry2 widget (in main())
 ******************************************************************************/
void            close_proc (Widget w, caddr_t client_data, XmAnyCallbackStruct * call_data)
{
	struct node    *destroy;

	erase_template_tree (template_tree_pointer);
	clear_region_marker_display ();
	while (current_node != 0)
	{
		destroy = current_node;
		current_node = current_node->before;
		free (destroy);
	}
	template_tree_pointer = new_module ();
	current_node = template_tree_pointer;
	make_region (template_tree_pointer, current_node);
}

/*******************************************************************************
 * FUNCTION:	GET_NODE_ATTRIBUTE
 ******************************************************************************/
void            get_node_attribute (int place_holder, int *node_attribute_array)
{
	int             tree_type = 0;
	int             node_type = 1;
	int             ds_method = 2;

	switch (place_holder)
	{
		case module:
			node_attribute_array[tree_type] = module;
			node_attribute_array[node_type] = reference_node;
			node_attribute_array[ds_method] = ref_direct_product;
			break;
		case analysis_tree:
			node_attribute_array[tree_type] = analysis_tree;
			break;
		case synthesis_tree:
			node_attribute_array[tree_type] = synthesis_tree;
			break;
		case rest_of_analysis_tree:
			node_attribute_array[tree_type] = analysis_tree;
			break;
		case rest_of_synthesis_tree:
			node_attribute_array[tree_type] = synthesis_tree;
			break;
		case match_node:
			node_attribute_array[node_type] = match_node;
			break;
		case reference_node:
			node_attribute_array[node_type] = reference_node;
			break;
		case ref_direct_product:
			node_attribute_array[node_type] = reference_node;
			node_attribute_array[ds_method] = ref_direct_product;
			break;
		case ref_discriminated_union:
			node_attribute_array[node_type] = reference_node;
			node_attribute_array[ds_method] = ref_discriminated_union;
			break;
		case ref_sequence_1:
			node_attribute_array[node_type] = reference_node;
			node_attribute_array[ds_method] = ref_sequence_1;
			break;
		case ref_sequence_2:
			node_attribute_array[node_type] = reference_node;
			node_attribute_array[ds_method] = ref_sequence_2;
			break;
		case ref_sequence_3:
			node_attribute_array[node_type] = reference_node;
			node_attribute_array[ds_method] = ref_sequence_3;
			break;
		case mat_direct_product:
			node_attribute_array[node_type] = match_node;
			node_attribute_array[ds_method] = mat_direct_product;
			break;
		case mat_discriminated_union:
			node_attribute_array[node_type] = match_node;
			node_attribute_array[ds_method] = mat_discriminated_union;
			break;
		case mat_sequence_1:
			node_attribute_array[node_type] = match_node;
			node_attribute_array[ds_method] = mat_sequence_1;
			break;
		case mat_sequence_2:
			node_attribute_array[node_type] = match_node;
			node_attribute_array[ds_method] = mat_sequence_2;
			break;
		case mat_sequence_3:
			node_attribute_array[node_type] = match_node;
			node_attribute_array[ds_method] = mat_sequence_3;
			break;
		case rtn:
			node_attribute_array[node_type] = match_node;
			break;
	}
}


void            upper_or_lower (char *node_name, int *node_attribute)
{
	int             tree_type = 0;
	int             node_type = 1;
	int             ds_method = 2;
	int             i = 0;

	switch (node_attribute[node_type])
	{
		case reference_node:
			while (node_name[i] != '\0')
			{
				node_name[i] = toupper (node_name[i]);
				++i;
			}
			break;
		case match_node:
			while (node_name[i] != '\0')
			{
				node_name[i] = tolower (node_name[i]);
				++i;
			}
			break;
	}
}





/*******************************************************************************
 * FUNCTION:	DRAW_TEXT
 *	XmNactivateCallback on text_area widget (in main())
 ******************************************************************************/
void            draw_text (Widget w, XtPointer client_data, XmAnyCallbackStruct * cbs)
{
	char           *text;

	answered = TRUE;
	text = XmTextFieldGetString (w);
	strncpy (node_name_string, text, sizeof (node_name_string));
	XtFree (text);
	return;
}

/*******************************************************************************
 * FUNCTION:	ONE_MORE_NEW_NODE
 *	Called from editing_proc() in xdesc1.c
 ******************************************************************************/
void            one_more_new_node (int *next_p_h_array, int selected_p_h, struct modi_info * modi_info_pointer, int *node_attr)
{
	struct node    *new_node;
	int             j;
	char            temp_node_name[180];
	struct node    *ancester = 0;
	struct node    *level = 0;
	struct node    *front = 0;
	struct node    *back = 0;
	struct append_place_holder *append_tail,
	               *new_tail;
	int             tree_type = 0;
	int             node_type = 1;
	int             ds_method = 2;
	int             condition;
	text_data_ptr   data_ptr;
	int             height,
	                increased_distance;


	new_node = (struct node *) calloc (1, sizeof (struct node));
	new_node->node_name = (char *) calloc (max_node_len, sizeof (char));
	*node_name_string = '\0';	/* Original code was: strcpy(node_name_string,"\o"); */
	if (node_attr[ds_method] == ref_sequence_2 ||
			node_attr[ds_method] == mat_sequence_2)
		XmTextSetString (text_area, "(..)");
	else
		XmTextSetString (text_area, "");
	XBell (XtDisplay (drawing_area), 0);
	XtProcessEvent (XtIMAll);
	while (answered == FALSE)
	{
		XtProcessEvent (XtIMAll);	/* (XtImXEvent) */
	}
	answered = FALSE;
	strcpy (temp_node_name, node_name_string);
	if (strlen (temp_node_name) != 0)
	{
		erase_template_tree (template_tree_pointer);
		upper_or_lower (temp_node_name, node_attr);
		make_node_name (temp_node_name, modi_info_pointer);
		strcpy (new_node->node_name, temp_node_name);
		new_node->name_length = strlen (temp_node_name);
		new_node->col = selected_p_h;
		new_node->row = current_node->row + 1;
		ancester = locate_ancester (template_tree_pointer, current_node, ancester, back, new_node->row, new_node->col);
		if (ancester != 0)
		{
			new_node->ancester = ancester;
			if (ancester->level == 0)
				ancester->level = new_node;
		}
		else
		{
			new_node->ancester = 0;
		}
		back = locate_back (template_tree_pointer, current_node, ancester, back, new_node->row, new_node->col);
		if (back != 0)
		{
			new_node->back = back;
			back->front = new_node;
		}
		else
			new_node->back = 0;
		new_node->next = 0;
		j = 1;
		while (next_p_h_array[j] != 0)
		{
			new_tail = (struct append_place_holder *) calloc
				(1, sizeof (struct append_place_holder));
			new_tail->p_h_type = next_p_h_array[j];
			new_tail->next = 0;
			if (j == 1)
				new_node->append_head = new_tail;
			else
				append_tail->next = new_tail;
			append_tail = new_tail;
			++j;
		}
		new_node->origion_x = region[selected_p_h][0];
		new_node->origion_y = region[selected_p_h][1];
		new_node->tree_type = node_attr[tree_type];
		new_node->node_type = node_attr[node_type];
		new_node->d_s_method = node_attr[ds_method];
		condition = syntax_check (new_node);
		if (condition == is_literal)
			new_node->node_type = literal;
		current_node->next = new_node;
		new_node->before = current_node;
		current_node = new_node;

	/* ------------------------ */
	/* multi_modules processing */
	/* ------------------------ */
		data_ptr = &data;
		height = data_ptr->font->ascent + data_ptr->font->descent;
		increased_distance = 2 * text_border_margin + height + node_to_node_space_y;
		increase_vertical_modules (1, increased_distance);
	}
}

/*******************************************************************************
 * FUNCTION:	ONE_MORE_NEW_NODE_READ_IN
 *
 *	Called by "parser()" function in xdesc1.c
 ******************************************************************************/
void            one_more_new_node_read_in (int *next_p_h_array, int selected_p_h, struct modi_info * modi_info_pointer, int *node_attr, char *temp_node_name)
{
	struct node    *new_node;
	int             j;

	struct node    *ancester = 0;
	struct node    *level = 0;
	struct node    *front = 0;
	struct node    *back = 0;
	struct append_place_holder *append_tail,
	               *new_tail;
	int             tree_type = 0;
	int             node_type = 1;
	int             ds_method = 2;
	int             condition;

	new_node = (struct node *) calloc (1, sizeof (struct node));
	new_node->node_name = (char *) calloc (max_node_len, sizeof (char));

	if (strlen (temp_node_name) != 0)
	{
		make_node_name (temp_node_name, modi_info_pointer);
		strcpy (new_node->node_name, temp_node_name);
		new_node->name_length = strlen (temp_node_name);
		new_node->col = selected_p_h;
		new_node->row = current_node->row + 1;
		ancester = locate_ancester (template_tree_pointer, current_node, ancester, back, new_node->row, new_node->col);
		if (ancester != 0)
		{
			new_node->ancester = ancester;
			if (ancester->level == 0)
				ancester->level = new_node;
		}
		else
		{
			new_node->ancester = 0;
		}
		back = locate_back (template_tree_pointer, current_node, ancester, back, new_node->row, new_node->col);
		if (back != 0)
		{
			new_node->back = back;
			back->front = new_node;
		}
		else
			new_node->back = 0;
		new_node->next = 0;
		j = 1;
		while (next_p_h_array[j] != 0)
		{
			new_tail = (struct append_place_holder *) calloc
				(1, sizeof (struct append_place_holder));
			new_tail->p_h_type = next_p_h_array[j];
			new_tail->next = 0;
			if (j == 1)
				new_node->append_head = new_tail;
			else
				append_tail->next = new_tail;
			append_tail = new_tail;
			++j;
		}
		new_node->origion_x = region[selected_p_h][0];
		new_node->origion_y = region[selected_p_h][1];

		new_node->tree_type = node_attr[tree_type];
		new_node->node_type = node_attr[node_type];
		new_node->d_s_method = node_attr[ds_method];
		condition = syntax_check (new_node);
		if (condition == is_literal)
			new_node->node_type = literal;
		current_node->next = new_node;
		new_node->before = current_node;
		current_node = new_node;
	}
}

/*******************************************************************************
 * FUNCTION:	INSERT_ONE_MORE_NEW_NODE
 *
 *	Called from editing_proc() in xdesc1.c
 ******************************************************************************/
void            insert_one_more_new_node (int *next_p_h_array, int selected_p_h, struct modi_info * modi_info_pointer,
					                  int *node_attr, struct node * parent)
{
	struct node    *new_node,
	               *front_ptr,
	               *back_ptr,
	               *tp_ptr;
	int             j,
	                height,
	                increased_distance;
	char            temp_node_name[180];
	struct node    *ancester = 0;
	struct node    *level = 0;
	struct node    *front = 0;
	struct node    *back = 0;
	struct append_place_holder *append_tail,
	               *new_tail;
	int             tree_type = 0;
	int             node_type = 1;
	int             ds_method = 2;
	text_data_ptr   data_ptr;
	int             y1 = 1;
	int             condition;

	new_node = (struct node *) calloc (1, sizeof (struct node));
	new_node->node_name = (char *) calloc (max_node_len, sizeof (char));
	strcpy (node_name_string, "\0");
	XmTextSetString (text_area, "");
	XBell (XtDisplay (drawing_area), 0);
	XtProcessEvent (XtIMAll);
	while (answered == FALSE)
	{
		XtProcessEvent (XtIMAll);	/* (XtImXEvent) */
	}
	answered = FALSE;
	strcpy (temp_node_name, node_name_string);
	if (strlen (temp_node_name) != 0)
	{
		no_show_edge_region (template_tree_pointer);
		erase_template_tree (parent);
		upper_or_lower (temp_node_name, node_attr);
		make_node_name (temp_node_name, modi_info_pointer);
		strcpy (new_node->node_name, temp_node_name);
		new_node->name_length = strlen (temp_node_name);
		front_ptr = parent->level;
		back_ptr = 0;
		while (front_ptr != 0 && front_ptr->origion_y < breakup_edge_region[selected_p_h][0][y1] && front_ptr != 0)
		{
			back_ptr = front_ptr;
			front_ptr = front_ptr->front;
		}
		new_node->col = parent->col + 1;
		new_node->row = front_ptr->row;
		tp_ptr = parent;
	/* All node after the new node has to increase row index */
		while (tp_ptr != 0)
		{
			if (tp_ptr->row >= new_node->row)
				tp_ptr->row = tp_ptr->row + 1;
			tp_ptr = tp_ptr->next;
		}
		ancester = parent;
		if (ancester != 0)
		{
			new_node->ancester = ancester;
			if (ancester->level->row > new_node->row)
				ancester->level = new_node;
			if (ancester->level == 0)
				ancester->level = new_node;
		}
		else
		{
			new_node->ancester = 0;
		}
		if (back_ptr != 0)
		{
			new_node->back = back_ptr;
			back_ptr->front = new_node;
		}
		else
			new_node->back = 0;
		tp_ptr = parent;
		while (tp_ptr != 0)
		{
			if (tp_ptr->row == new_node->row + 1)
			{
				new_node->front = tp_ptr;
				new_node->next = tp_ptr;
				new_node->before = tp_ptr->before;
				tp_ptr->before->next = new_node;
				tp_ptr->before = new_node;
				tp_ptr->back = new_node;
			}
			tp_ptr = tp_ptr->next;
		}
		j = 1;
		while (next_p_h_array[j] != 0)
		{
			new_tail = (struct append_place_holder *) calloc
				(1, sizeof (struct append_place_holder));
			new_tail->p_h_type = next_p_h_array[j];
			new_tail->next = 0;
			if (j == 1)
				new_node->append_head = new_tail;
			else
				append_tail->next = new_tail;
			append_tail = new_tail;
			++j;
		}
		new_node->origion_x = new_node->next->origion_x;
		new_node->origion_y = new_node->next->origion_y;
		new_node->tree_type = node_attr[tree_type];
		new_node->node_type = node_attr[node_type];
		new_node->d_s_method = node_attr[ds_method];
		condition = syntax_check (new_node);
		if (condition == is_literal)
			new_node->node_type = literal;
		tp_ptr = parent;
		data_ptr = &data;
		height = data_ptr->font->ascent + data_ptr->font->descent;
		increased_distance = 2 * text_border_margin + height + node_to_node_space_y;
	/* calculate_string_data(block_head); */

	/*
	 * clear_rect_area(str_data.origion_x+1,str_data.xright-1,str_data.ori
	 * gion_y+1,str_data.ybottom-1)
		 */ ;
		while (tp_ptr != 0)
		{
			if (tp_ptr->row > new_node->row)
			{
				tp_ptr->origion_y = tp_ptr->origion_y + increased_distance;
			}
			tp_ptr = tp_ptr->next;
		}
	/* ------------------------ */
	/* multi_modules processing */
	/* ------------------------ */
		data_ptr = &data;
		height = data_ptr->font->ascent + data_ptr->font->descent;
		increased_distance = 2 * text_border_margin + height + node_to_node_space_y;
		increase_vertical_modules (1, increased_distance);
	}

	display_template_tree_debug (template_tree_pointer);
	debugger (template_tree_pointer);
}

/*******************************************************************************
 * FUNCTION:	INSERT_ONE_MORE_NEW_NODE_WITH_CHILD
 *
 *	Called from editing_proc() in xdesc1.c
 ******************************************************************************/
void            insert_one_more_new_node_with_child (int *next_p_h_array, int selected_p_h,
				                     struct modi_info * modi_info_pointer, int *node_attr, struct node * parent)
{
	struct node    *new_node,
	               *front_ptr,
	               *back_ptr,
	               *tp_ptr,
	               *tail_ptr;
	int             j,
	                height,
	                increased_distance;
	char            temp_node_name[180];
	struct node    *ancester = 0;
	struct node    *level = 0;
	struct node    *front = 0;
	struct node    *back = 0;
	struct append_place_holder *append_tail,
	               *new_tail;
	int             tree_type = 0;
	int             node_type = 1;
	int             ds_method = 2;
	text_data_ptr   data_ptr;
	int             y1 = 1;
	int             condition;

	new_node = (struct node *) calloc (1, sizeof (struct node));
	new_node->node_name = (char *) calloc (max_node_len, sizeof (char));
	*node_name_string = '\0';	/* Original code was: strcpy(node_name_string,"\o"); */
	XmTextSetString (text_area, "");
	XBell (XtDisplay (drawing_area), 0);
	XtProcessEvent (XtIMAll);
	while (answered == FALSE)
	{
		XtProcessEvent (XtIMAll);	/* (XtImXEvent) */
	}
	answered = FALSE;
	strcpy (temp_node_name, node_name_string);
	if (strlen (temp_node_name) != 0)
	{
		no_show_edge_region (template_tree_pointer);
		erase_template_tree (parent);
		upper_or_lower (temp_node_name, node_attr);
		make_node_name (temp_node_name, modi_info_pointer);
		strcpy (new_node->node_name, temp_node_name);
		new_node->name_length = strlen (temp_node_name);
	/* --------------------------------------------------- */
	/* find out the node that is the FRONT of the new node */
	/* --------------------------------------------------- */
		front_ptr = insert_mode_block_tail[selected_p_h]->front;
		back_ptr = insert_mode_block_tail[selected_p_h]->back;
		tail_ptr = insert_mode_block_tail[selected_p_h];

		new_node->col = parent->col + 1;
		new_node->row = tail_ptr->row;
		tp_ptr = parent;

	/* ----------------------------------------------------- */
	/* All node after the new node has to increase row index */
	/* ----------------------------------------------------- */
		while (tp_ptr != 0)
		{
			if (tp_ptr->row >= new_node->row)
				tp_ptr->row = tp_ptr->row + 1;
			tp_ptr = tp_ptr->next;
		}
		ancester = parent;
		if (ancester != 0)
		{
			new_node->ancester = ancester;
			if (ancester->level->row > new_node->row)
				ancester->level = new_node;
			if (ancester->level == 0)
				ancester->level = new_node;
		}
		else
		{
			new_node->ancester = 0;
		}
		if (back_ptr != 0)
		{
			if (back_ptr->front != 0)
				back_ptr->front->back = NULL;
			new_node->back = back_ptr;
			back_ptr->front = new_node;
		}
		else
			new_node->back = 0;
		if (front_ptr != 0)
		{
			tp_ptr = front_ptr;
			new_node->front = tp_ptr;
			tp_ptr->back = new_node;
			tail_ptr->front = 0;
			tail_ptr->back = 0;
		}
		new_node->level = tail_ptr;
		insert_mode_block_tail[selected_p_h]->ancester = new_node;
		new_node->next = insert_mode_block_tail[selected_p_h];
		new_node->before = insert_mode_block_tail[selected_p_h]->before;
		insert_mode_block_tail[selected_p_h]->before->next = new_node;
		insert_mode_block_tail[selected_p_h]->before = new_node;
		j = 1;
		while (next_p_h_array[j] != 0)
		{
			new_tail = (struct append_place_holder *) calloc
				(1, sizeof (struct append_place_holder));
			new_tail->p_h_type = next_p_h_array[j];
			new_tail->next = 0;
			if (j == 1)
				new_node->append_head = new_tail;
			else
				append_tail->next = new_tail;
			append_tail = new_tail;
			++j;
		}
		new_node->origion_x = new_node->next->origion_x;
		new_node->origion_y = new_node->next->origion_y;
		new_node->tree_type = node_attr[tree_type];
		new_node->node_type = node_attr[node_type];
		new_node->d_s_method = node_attr[ds_method];
		condition = syntax_check (new_node);
		if (condition == is_literal)
			new_node->node_type = literal;
		tp_ptr = parent;
		data_ptr = &data;
		height = data_ptr->font->ascent + data_ptr->font->descent;
		increased_distance = 2 * text_border_margin + height + node_to_node_space_y;
		while (tp_ptr != 0)
		{
			if (tp_ptr->row > new_node->row)
			{
				tp_ptr->origion_y = tp_ptr->origion_y + increased_distance;
			}
			tp_ptr = tp_ptr->next;
		}
		calculate_string_data (new_node);
		increased_distance = (str_data.xright - str_data.xleft) + node_to_node_space;
		preorder_modi_location (new_node->level, increased_distance);
		preorder_modi_col (new_node->level, 1);

	/* ------------------------ */
	/* multi_modules processing */
	/* ------------------------ */
		data_ptr = &data;
		height = data_ptr->font->ascent + data_ptr->font->descent;
		increased_distance = 2 * text_border_margin + height + node_to_node_space_y;
		increase_vertical_modules (1, increased_distance);
	}

	display_template_tree_debug (template_tree_pointer);
	debugger (template_tree_pointer);
}

/*******************************************************************************
 * FUNCTION:	INSERT_NEW_NODE_CASE_IF_EMPTY
 *
 *	Insert one more new node if front is empty.  Called from editing_proc()
 *	in xdesc1.c
 ******************************************************************************/
void            insert_new_node_case_if_empty (int *next_p_h_array, int selected_p_h, struct modi_info * modi_info_pointer,
					                       int *node_attr, struct node * parent)
{
	struct node    *new_node,
	               *front_ptr,
	               *back_ptr,
	               *tp_ptr,
	               *tail_ptr;
	int             j,
	                height,
	                increased_distance;
	char            temp_node_name[180];
	struct node    *ancester = 0;
	struct node    *level = 0;
	struct node    *front = 0;
	struct node    *back = 0;
	struct append_place_holder *append_tail,
	               *new_tail;
	int             tree_type = 0;
	int             node_type = 1;
	int             ds_method = 2;
	text_data_ptr   data_ptr;
	int             y1 = 1;

	new_node = (struct node *) calloc (1, sizeof (struct node));
	new_node->node_name = (char *) calloc (max_node_len, sizeof (char));
	*node_name_string = '\0';	/* Original code was: strcpy(node_name_string,"\o"); */
	XmTextSetString (text_area, "");
	XBell (XtDisplay (drawing_area), 0);
	XtProcessEvent (XtIMAll);
	while (answered == FALSE)
	{
		XtProcessEvent (XtIMAll);	/* (XtImXEvent) */
	}
	answered = FALSE;
	strcpy (temp_node_name, node_name_string);
	if (strlen (temp_node_name) != 0)
	{
		no_show_edge_region (template_tree_pointer);
		erase_template_tree (parent);
		upper_or_lower (temp_node_name, node_attr);
		make_node_name (temp_node_name, modi_info_pointer);
		strcpy (new_node->node_name, temp_node_name);
		new_node->name_length = strlen (temp_node_name);
		back_ptr = 0;
		front_ptr = parent->level;
	/* --------------------------------------------------- */
	/* find out the node that is the FRONT of the new node */
	/* --------------------------------------------------- */
		while (front_ptr != 0 && front_ptr->origion_y < breakup_extra_region[selected_p_h][0][y1])
		{
			back_ptr = front_ptr;
			front_ptr = front_ptr->front;
		}
	/* ------------------------------------ */
	/* FRONT of the new node is always NULL */
	/* ------------------------------------ */
		new_node->front = 0;

	/* --------------------------------------------------------- */
	/* find out the node that is the going to be the  node	    */
	/* BEFORE of new node (the last descendant of new_node->back */
	/* --------------------------------------------------------- */
		tail_ptr = preorder_locate_last_desc (back_ptr);
		new_node->col = parent->col + 1;
		new_node->row = tail_ptr->row + 1;
		tp_ptr = parent;
	/* ----------------------------------------------------- */
	/* All node after the new node has to increase row index */
	/* ----------------------------------------------------- */
		while (tp_ptr != 0)
		{
			if (tp_ptr->row >= new_node->row)
				tp_ptr->row = tp_ptr->row + 1;
			tp_ptr = tp_ptr->next;
		}
		ancester = parent;
		if (ancester != 0)
		{
			new_node->ancester = ancester;
			if (ancester->level->row > new_node->row)
				ancester->level = new_node;
			if (ancester->level == 0)
				ancester->level = new_node;
		}
		else
		{
			new_node->ancester = 0;
		}
		if (back_ptr != 0)
		{
			new_node->back = back_ptr;
			back_ptr->front = new_node;
		}
		else
			new_node->back = 0;
		tp_ptr = parent;
		while (tp_ptr != 0)
		{
			if (tp_ptr->row == new_node->row + 1)
			{
				new_node->level = 0;
				new_node->next = tp_ptr;
				new_node->before = tp_ptr->before;
				tp_ptr->before->next = new_node;
				tp_ptr->before = new_node;
			}
			tp_ptr = tp_ptr->next;
		}
		j = 1;
		while (next_p_h_array[j] != 0)
		{
			new_tail = (struct append_place_holder *) calloc
				(1, sizeof (struct append_place_holder));
			new_tail->p_h_type = next_p_h_array[j];
			new_tail->next = 0;
			if (j == 1)
				new_node->append_head = new_tail;
			else
				append_tail->next = new_tail;
			append_tail = new_tail;
			++j;
		}
		data_ptr = &data;
		height = data_ptr->font->ascent + data_ptr->font->descent;
		increased_distance = 2 * text_border_margin + height + node_to_node_space_y;
		new_node->origion_x = new_node->before->origion_x;
		new_node->origion_y = new_node->before->origion_y + increased_distance;
		new_node->tree_type = node_attr[tree_type];
		new_node->node_type = node_attr[node_type];
		new_node->d_s_method = node_attr[ds_method];
		tp_ptr = parent;
		while (tp_ptr != 0)
		{
			if (tp_ptr->row > new_node->row)
			{
				tp_ptr->origion_y = tp_ptr->origion_y + increased_distance;
			}
			tp_ptr = tp_ptr->next;
		}
	/* ------------------------ */
	/* multi_modules processing */
	/* ------------------------ */
		data_ptr = &data;
		height = data_ptr->font->ascent + data_ptr->font->descent;
		increased_distance = 2 * text_border_margin + height + node_to_node_space_y;
		increase_vertical_modules (1, increased_distance);
	}

	display_template_tree_debug (template_tree_pointer);
	debugger (template_tree_pointer);
}

/*******************************************************************************
 * FUNCTION:	INSERT_NEW_NODE_CASE_LEVEL_NEED
 *
 *	Insert one more new node case level_need.  Called from editing_proc()
 *	in xdesc1.c
 ******************************************************************************/
void            insert_new_node_case_level_need (int *next_p_h_array, int selected_p_h, struct modi_info * modi_info_pointer, int *node_attr, struct node * parent)
{
	struct node    *new_node,
	               *tp_ptr;
	int             j,
	                height,
	                increased_distance;
	char            temp_node_name[180];
	struct node    *ancester = 0;
	struct node    *level = 0;
	struct node    *front = 0;
	struct node    *back = 0;
	struct append_place_holder *append_tail,
	               *new_tail;
	int             tree_type = 0;
	int             node_type = 1;
	int             ds_method = 2;
	text_data_ptr   data_ptr;
	int             y1 = 1;

	new_node = (struct node *) calloc (1, sizeof (struct node));
	new_node->node_name = (char *) calloc (max_node_len, sizeof (char));
	*node_name_string = '\0';	/* Original code was: strcpy(node_name_string,"\o"); */
	XBell (XtDisplay (drawing_area), 0);
	XmTextSetString (text_area, "");
	XtProcessEvent (XtIMAll);
	while (answered == FALSE)
	{
		XtProcessEvent (XtIMAll);	/* (XtImXEvent) */
	}
	answered = FALSE;
	strcpy (temp_node_name, node_name_string);
	if (strlen (temp_node_name) != 0)
	{
		no_show_edge_region (template_tree_pointer);
		erase_template_tree (parent);
		upper_or_lower (temp_node_name, node_attr);
		make_node_name (temp_node_name, modi_info_pointer);

		strcpy (new_node->node_name, temp_node_name);
		new_node->name_length = strlen (temp_node_name);
		new_node->col = parent->col + 1;
		new_node->row = parent->row + 1;

		tp_ptr = parent;
	/* ----------------------------------------------------- */
	/* All node after the new node has to increase row index */
	/* ----------------------------------------------------- */
		while (tp_ptr != 0)
		{
			if (tp_ptr->row >= new_node->row)
				tp_ptr->row = tp_ptr->row + 1;
			tp_ptr = tp_ptr->next;
		}
		ancester = parent;
		if (ancester != 0)
		{
			new_node->ancester = ancester;
			if (ancester->level == 0)
				ancester->level = new_node;
		}
		else
		{
			new_node->ancester = 0;
		}

		new_node->back = 0;
		new_node->front = 0;

		tp_ptr = parent;
		while (tp_ptr != 0)
		{
			if (tp_ptr->row == new_node->row + 1)
			{
				new_node->level = 0;
				new_node->next = tp_ptr;
				new_node->before = tp_ptr->before;
				tp_ptr->before->next = new_node;
				tp_ptr->before = new_node;
			}
			tp_ptr = tp_ptr->next;
		}
		j = 1;
		while (next_p_h_array[j] != 0)
		{
			new_tail = (struct append_place_holder *) calloc
				(1, sizeof (struct append_place_holder));
			new_tail->p_h_type = next_p_h_array[j];
			new_tail->next = 0;
			if (j == 1)
				new_node->append_head = new_tail;
			else
				append_tail->next = new_tail;
			append_tail = new_tail;
			++j;
		}
		calculate_string_data (parent);
		increased_distance = (str_data.xright - str_data.xleft) + node_to_node_space;
		new_node->origion_x = parent->origion_x + increased_distance;
		data_ptr = &data;
		height = data_ptr->font->ascent + data_ptr->font->descent;
		increased_distance = 2 * text_border_margin + height + node_to_node_space_y;
		new_node->origion_y = parent->origion_y + increased_distance;	/* new_node->next->origion_y */
		new_node->tree_type = node_attr[tree_type];
		new_node->node_type = node_attr[node_type];
		new_node->d_s_method = node_attr[ds_method];
		tp_ptr = parent;
		while (tp_ptr != 0)
		{
			if (tp_ptr->row > new_node->row)
			{
				tp_ptr->origion_y = tp_ptr->origion_y + increased_distance;
			}
			tp_ptr = tp_ptr->next;
		}
	/* ------------------------ */
	/* multi_modules processing */
	/* ------------------------ */
		data_ptr = &data;
		height = data_ptr->font->ascent + data_ptr->font->descent;
		increased_distance = 2 * text_border_margin + height + node_to_node_space_y;
		increase_vertical_modules (1, increased_distance);
	}

	display_template_tree_debug (template_tree_pointer);
	debugger (template_tree_pointer);
}
