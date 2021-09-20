#ifndef XDESC1_H
#define XDESC1_H	1
/*******************************************************************************
 * HEADER:	XDESC1.H
 *
 * PURPOSE:	Declare external functions defined in xdesc1.c
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 * $Author: franklin $
 *******************************************************************************
 * $Date: 1994/06/01 15:50:20 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/editor/RCS/xdesc1.h,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: xdesc1.h,v $
 * Revision 1.1  1994/06/01  15:50:20  franklin
 * Initial revision
 *
 ******************************************************************************/

static char    *xdesc1_h_rcsid = "$Id: xdesc1.h,v 1.1 1994/06/01 15:50:20 franklin Exp $";

#endif
extern void     calculate_string_data (struct node * node_ptr);

/*
 * Malcolm: you have not put any comments in the following fns headers (like
 * who calls them from what file....)yet.
 */
extern void     debugger (struct node * tp_tree_pointer);
extern void     real_inverse_rect_area (int xleft, int xright, int ytop, int ybottom);
extern void     display_template_tree_debug (struct node * tp_tree_pointer);
extern void     return_item (Widget menu_item, XtPointer item_nooo, XmRowColumnCallbackStruct * cbs);
extern void     clear_region_marker_display (void);
extern void     eliminate_ind_region (int *p_h_array);
extern void     never_called (Widget w, XtPointer x, XmAnyCallbackStruct z);
extern void     make_node_name (char *temp_name, struct modi_info * m_i_pointer);
extern int      syntax_check (struct node * node_to_check);
extern void     make_edge_region (struct node * tp_tree_pointer);
extern void     clear_rect_area (int xleft, int xright, int ytop, int ybottom);
extern void     display_template_tree (struct node * tp_tree_pointer);
extern void     erase_template_tree (struct node * tp_tree_pointer);
extern void     calculate_rb_data (struct rubber_node * node_ptr);
extern void     inverse_rect_area (int xleft, int xright, int ytop, int ybottom);
extern void     make_region (struct node * template_tree_pointer, struct node * current_node);
extern struct node *new_module (void);
extern void     increase_vertical_modules (int row_diff, int y_diff);
extern void     editing_proc (Widget w, caddr_t client_data, XEvent * event_info);
extern void     del_node_proc (Widget w, caddr_t client_data, XmAnyCallbackStruct * cbs);

#endif				       /* XDESC1_H End if this file has not already been #included. */
