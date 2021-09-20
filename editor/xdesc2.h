#ifndef XDESC2_H
#define XDESC2_H	1
/*******************************************************************************
 * HEADER:	XDESC2.H
 *
 * PURPOSE:	Declare external functions defined in xdesc2.c
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University
 * $Author: franklin $
 *******************************************************************************
 * $Date: 1994/06/01 15:50:36 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/editor/RCS/xdesc2.h,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: xdesc2.h,v $
 * Revision 1.1  1994/06/01  15:50:36  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif

static char    *xdesc2_h_rcsid = "$Id: xdesc2.h,v 1.1 1994/06/01 15:50:36 franklin Exp $";

extern void     start_open (Widget w, caddr_t client_data, XmAnyCallbackStruct * call_data);
extern void     close_proc (Widget w, caddr_t client_data, XmAnyCallbackStruct * call_data);
extern void     draw_text (Widget w, XtPointer client_data, XmAnyCallbackStruct * cbs);
extern void     start_open (Widget w, caddr_t client_data, XmAnyCallbackStruct * call_data);
extern void     move_proc (Widget w, caddr_t client_data, XmAnyCallbackStruct * cbs);
extern void     mod_name_proc (Widget w, caddr_t client_data, XmAnyCallbackStruct * cbs);
extern void     mod_ds_method_proc (Widget w, caddr_t client_data, XmAnyCallbackStruct * cbs);
extern struct node *preorder_locate_last_desc (struct node * subtree_pointer);
extern void     preorder_decrease_col_and_row (struct node * subtree_pointer, int col_diff, int row_diff);
extern void     one_more_new_node_read_in (int *next_p_h_array, int selected_p_h,
				                    struct modi_info * modi_info_pointer, int *node_attr, char *temp_node_name);
extern struct node *locate_ancester (struct node * tp_pointer, struct node * current_pointer, struct node * parent_pointer,
				                     struct node * back_pointer, int new_row, int new_col);
extern void     cancel_file_select (Widget w, caddr_t client_data, XmAnyCallbackStruct * call_data);
extern void     show_edge_region (struct node * tp_tree_pointer);
extern void     no_show_edge_region (struct node * tp_tree_pointer);
extern void     check_existing_region (struct node * tp_pointer, int pos_x, int pos_y, XEvent * event_info);
extern int      check_region (int loc_x, int loc_y);
extern void     get_node_attribute (int place_holder, int *node_attribute_array);
extern void     one_more_new_node (int *next_p_h_array, int selected_p_h, struct modi_info * modi_info_pointer, int *node_attr);
extern int      check_edge_region (int loc_x, int loc_y);
extern void     insert_one_more_new_node (int *next_p_h_array, int selected_p_h,
				                    struct modi_info * modi_info_pointer, int *node_attr, struct node * parent);
extern void     insert_one_more_new_node_with_child (int *next_p_h_array, int selected_p_h,
				                    struct modi_info * modi_info_pointer, int *node_attr, struct node * parent);
extern void     insert_new_node_case_if_empty (int *next_p_h_array, int selected_p_h,
				                    struct modi_info * modi_info_pointer, int *node_attr, struct node * parent);
extern void     insert_new_node_case_level_need (int *next_p_h_array, int selected_p_h,
				                    struct modi_info * modi_info_pointer, int *node_attr, struct node * parent);
extern void     preorder_decrease_x_and_y (struct node * subtree_pointer, int x_diff, int y_diff);
extern void     clear_subtree (struct node * subtree_pointer);

#endif				       /* XDESC2_H; End if this file has not already been #included */
