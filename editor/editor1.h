/*******************************************************************************
 * $Date: 1994/05/06 01:07:59 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/editor/RCS/editor1.h,v $
 *
 ******************************************************************************/
#if 0
/******************************************************************************
 *
$Log: editor1.h,v $
 * Revision 1.1  1994/05/06  01:07:59  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif
static char	*editor1_h_rcsid = "@(#) $Id: editor1.h,v 1.1 1994/05/06 01:07:59 franklin Exp $";

#define module 1
#define hoare_trees 2
#define analysis_tree 3
#define synthesis_tree 4
#define rest_of_analysis_tree 5
#define rest_of_synthesis_tree 6
#define reference_node 7
#define match_node 8
#define ref_direct_product 9
#define ref_discriminated_union 10
#define ref_sequence_1 11
#define ref_sequence_2 12
#define ref_sequence_3 13
#define mat_direct_product 16
#define mat_discriminated_union 17
#define mat_sequence_1 18
#define mat_sequence_2 19
#define mat_sequence_3 20
#define indent 14
#define no_indent 15
#define nn 21
#define rtn 22
#define du  23
#define sq1 24
#define sq2 25
#define sq3 26
#define done 101
#define nulll -1
#define max_node_len 80
#define max_place_holder 50
#define more_than_one 10001
#define top_row   1
#define TRUE 1
#define FALSE 0
#define max_width 8
#define max_height 16
#define caps_height 11
#define x_height 7
#define baseline 11
#define text_border_margin 3
#define node_to_node_space 17
#define node_to_node_space_y 4
#define edge_line 11
#define node_to_node_half_space 9
#define is_literal  101
#define is_module_call 102
#define MAX_ENTRIES 80
#define WIDTH	350
#define HEIGHT	500
#define MAXARGS 20
#define edge_tile_width 1
#define x_break_clear  2
#define y_break_clear  5
#define state_insert 101
#define state_append 100
#define literal 27
#define No_Scroll 0
#define X_Scroll  10
#define Y_Scroll  20

struct modi_info
{
   int node_type;
   int ds_method;
};

/*  --------------------------------------------------------
    structure of a record in the laguage definition template
    -------------------------------------------------------- */
struct construct
{
   int place_holder_1;
   int place_holder_2;
   int place_holder_3;
   int place_holder_4;
   int place_holder_5;
   int place_holder_6;
   int place_holder_7;
   int place_holder_8;
   int place_holder_9;
   int place_holder_10;
   int phrase;
   int next_place_holder_ind;
   int next_place_holder_1;
   int next_place_holder_2;
 };

/* -------------------------------------------
    structure of a record in the template tree
   ------------------------------------------- */
struct node
{
   struct node *ancester;
   struct node *level;
   struct node *front;
   struct node *back;
   struct node *next;
   struct node *before;
   char   *node_name;
   int	  name_length;
   int	  origion_x;
   int	  origion_y;
   int	  row;
   int	  col;
   int	  tree_type;
   int	  node_type;
   int	  d_s_method;
   struct append_place_holder *append_head;



 };
/* -------------------------------------------
    structure of a record for append link list
   ------------------------------------------- */
struct append_place_holder
{
   int p_h_type;
   struct append_place_holder *next;
};

typedef struct
{
  int ascent;
  int descent;
  int height;
  int origion_x;
  int origion_y;
  int text_origion_x;
  int text_origion_y;
  int text_xleft;
  int text_xright;
  int text_ytop;
  int text_ybottom;
  int xleft;
  int xright;
  int ytop;
  int ybottom;
} STRING_DATA;

typedef struct ITEM_ACTION
{
   char 	  *label;
   XtCallbackProc callbacks;
} ITEM_ACTION;

typedef struct PULLDOWN_MENU_INFO
{
   int size;
   char *name;
   ITEM_ACTION items[MAX_ENTRIES];
} PULLDOWN_MENU_INFO;

typedef struct CASCADE_ITEM
{
   char *label;
   PULLDOWN_MENU_INFO *submenu;
}CASCADE_ITEM;

typedef struct CASCADE_MENU_INFO
{
   int	  size;
   char    *name;
   CASCADE_ITEM items[MAX_ENTRIES];
}  CASCADE_MENU_INFO;

typedef struct {
   XFontStruct *font;
} text_data, *text_data_ptr;

typedef struct {
  int x_right;
  int x_left;
  int y_top;
  int y_bottom;
} visible_data;

typedef struct {
   int	box_origin_x;
   int	box_origin_y;
   int	text_origin_x;
   int	text_origin_y;
   int	box_width;
   int	box_height;
   int	box_right;
   int	box_bottom;
} node_layout_info;

/* ------------------------------------
    structure of a node for RUBBERBAND
   ------------------------------------ */
struct rubber_node
{
   struct rubber_node *next;
   struct rubber_node *before;
   char   *node_name;
   int	  origion_x;
   int	  origion_y;
   int	  row;
   int	  col;
 };

struct node *template_tree_pointer,*current_node;
struct construct descartes_template[21];
int		  next_p_h_array[max_place_holder],thickness;
int		  breakup_extra_region[50][2][4];
GC		  theGC, xorGC;   /* GC for regular drawing	*/
GC		  inverseGC; /* GC for clear existing pixel*/
GC		  filledgeGC;/* GC for mark edge_regions   */
Widget		  drawing_area,entry[15],main_shell,top_level,file_select_dialog;
static Widget	  dialog_shell = (Widget)0;
text_data	  data;
int		  region[max_place_holder][2],edge_region[50][8];
int		  breakup_edge_region[50][2][4];
struct node	  *insert_mode_block_head[50];
struct node	  *insert_mode_block_tail[50];
int		  selected_item,selected_edit_mode;
struct node	  *block_head;
struct node	  *block_tail;
char		  node_name_string[80];
static XtResource resources[] = {
		  {XtNfont, XtCFont, XtRFontStruct, sizeof(XFontStruct *),
		  XtOffset(text_data_ptr,font), XtRString, "Fixed"}};
Widget		  text_area;
int		  answered,one_or_two;
STRING_DATA	  str_data;

Widget            semantic_list;
Pixmap		  pmap_25,pmap_50,pmap_75,pmap_bg;
int		  front_empty;
int		  level_need;
visible_data	  visible;
Pixmap		  pix_a_tree;
Pixmap		  pix_s_tree;
Pixmap		  pix_ref_dp;
Pixmap		  pix_ref_du;
Pixmap		  pix_ref_sq1;
Pixmap		  pix_ref_sq2;
Pixmap		  pix_ref_sq3;
Pixmap		  pix_mat_dp;
Pixmap		  pix_mat_du;
Pixmap		  pix_mat_sq1;
Pixmap		  pix_mat_sq2;
Pixmap		  pix_mat_sq3,pix_ret;
struct rubber_node	  *rubber_head;
int		  rubber_position[2];
int		  offset_from_origion[2];
struct rubber_node *rubber_tail;
short empty_region[4];
