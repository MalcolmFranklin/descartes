/*******************************************************************************
 * $Date: 1994/06/01 15:18:27 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/editor/RCS/xdesc1.c,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: xdesc1.c,v $
 * Revision 1.10  1994/06/01  15:18:27  franklin
 * 1. Do not produce screen dumps to temporary files when building popup
 *    menus in display_next_place_holder().
 * 2. Do not dump core when calculate_string_data() is passed a NULL pointer.
 *
 * Revision 1.8  1994/06/01  00:07:25  franklin
 * Workaround ANSI/ISO Standard C incompatibilities with the SunOS 4.x
 * include files.
 *
 * Revision 1.7  1994/05/31  23:16:45  franklin
 * 1. Removed local (auto) variables that were never referenced.
 * 2. Initialized some of the variables that might not always have a defined
 *    value before they are used.
 * 3. Broke source code lines > 132 columns into two or more shorter lines.
 * 4. Removed some exta whitespace.
 * 3. Tried to get clcc to recognize the declarations of XtVaCreateWidget(),
 *    XtVaCreateManagedWidget(), and XtVaGetValues() in <X11/Intrinsic.h>.
 *    I am not having much success here!
 *
 * Revision 1.6  1994/05/31  17:37:37  franklin
 * Run through the SunOS 4.1.x "indent" utility.
 *
 * Revision 1.5  1994/05/31  17:01:21  franklin
 * Get the declarations for functions outside of this file, from the appropriate
 * header files, instead of re-declaring them here.
 *    Make global variables used only in this file "static", so they cannot be
 * seen by the linker outside of this file.
 *    Make functions used only in this file "static".
 *    Add Function headers.
 *     Change the spelling of "return_iten" to "return_item".
 *    Correct the parameters to "XtInitialize()".
 *
 * Revision 1.4  1994/05/07  23:16:20  franklin
 * 1. Changed the third parameter to all calls to XtAddCallback() and
 *    XtRemoveCallback() (NOT CHANGED -- I MEAN CAST) to type
 *    XtCallbackProc.
 * 2. Cast the fourth parameter of all calls to XtAddCallback() and
 *    XtRemoveCallback() to type XtPointer (if it was non-NULL).
 * 3. Changed the definition of the second parameter of
 *    display_next_place_holder() from type XEvent to type XButtonPressedEvent.
 *    NOTE: I may decide to change this back later.
 *
 * Revision 1.3  1994/05/07  22:12:04  franklin
 * 1. Run through the Gnu "Protoize" tool to add ANSI/ISO Standard C
 *    function signatures.
 * 2. Deleted the 7th parameter (NULL) to XmMainWindowSetAreas().
 *
 * Revision 1.2  1994/05/05  23:51:53  franklin
 * The argument list and argument count parameters to XtSetArg() were never
 * initialized; this caused the program to fail immediately after being
 * invoked on a Sun sparc10 running SunOS 4.1.3.
 *
 ******************************************************************************/
#endif
static char    *rcsid = "@(#) $Id: xdesc1.c,v 1.10 1994/06/01 15:18:27 franklin Exp $";

#include <stdlib.h>
#include <limits.h>
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
 * WORKAROUND:
 *	When compiling with clcc, #define __STDC__ to 1 AFTER #including the 
 * system header files you need (<sys/xxx.h>), and hopefully before #including
 * any of the header files you (or I, or Yu-Kuh, or someone else) wrote.
 ******************************************************************************/
#ifdef __CLCC__
#ifdef __STDC__
#undef __STDC__
#endif
#define __STDC__ 1
#endif

#include <X11/Xlib.h>
#include <X11/IntrinsicP.h>

#include <Xm/Xm.h>
#include <X11/StringDefs.h>
#include <Xm/CascadeB.h>
#include <Xm/DialogS.h>
#include <Xm/DrawingA.h>
#include <Xm/DrawnB.h>
#include <Xm/FileSB.h>
#include <Xm/Frame.h>
#include <Xm/Label.h>
#include <Xm/LabelG.h>
#include <Xm/List.h>
#include <Xm/MainW.h>
#include <Xm/PanedW.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/ScrollBar.h>
#include <Xm/ScrolledW.h>
#include <Xm/SelectioB.h>
#include <Xm/Text.h>
#include <Xm/TextF.h>
#include <Xm/ToggleBG.h>

#include "editor1.h"
#include "xdesc1.h"		       /* Have the compiler check the header file against the definitions in this file. */
#include "xdesc2.h"
#include "xdesc3.h"

/* ------------------- */
/* NEW GLOBAL VARIABLE */
/* ------------------- */
static struct node *module_heads[30];
static struct node *module_tails[30];
static int      number_of_modules,
                current_module;
static int      screendump_count = 0;


/*
 * -------------------------------------------------------------------------
 * Function : exit_action Handle process to quit the editor
 * -------------------------------------------------------------------------
 */

static void     exit_action (Widget w, caddr_t client_data, XmAnyCallbackStruct * call_data)
{
	struct node    *temp_ptr,
	               *next_ptr;

	temp_ptr = template_tree_pointer;
	while (temp_ptr != NULL)
	{
		next_ptr = temp_ptr->next;
		free (temp_ptr->node_name);
		free (temp_ptr);
		temp_ptr = next_ptr;
	}

	XFreePixmap (XtDisplay (w), pix_a_tree);
	XFreePixmap (XtDisplay (w), pix_s_tree);
	XFreePixmap (XtDisplay (w), pix_ref_dp);
	XFreePixmap (XtDisplay (w), pix_ref_du);
	XFreePixmap (XtDisplay (w), pix_ref_sq1);
	XFreePixmap (XtDisplay (w), pix_ref_sq2);
	XFreePixmap (XtDisplay (w), pix_ref_sq3);
	XFreePixmap (XtDisplay (w), pix_mat_dp);
	XFreePixmap (XtDisplay (w), pix_mat_du);
	XFreePixmap (XtDisplay (w), pix_mat_sq1);
	XFreePixmap (XtDisplay (w), pix_mat_sq2);
	XFreePixmap (XtDisplay (w), pix_mat_sq3);
	XtCloseDisplay (XtDisplay (w));
	exit (0);
}


/*
 * --------------------------------------------------- Clear all elements in
 * the place_holder_array to '0'
 * ---------------------------------------------------
 */
static void     clear_int_array (int *any_int_array, int array_no)
{
	int             i;

	for (i = 0; i < array_no; ++i)
		any_int_array[i] = 0;
}

/*
 * --------------------------------------------------- Copy all elements in
 * the place_holder_array to next_p_h_array
 * ---------------------------------------------------
 */
static void     copy_p_h_array (int *place_holder_array, int *next_p_h_array)
{
	int             i;

	for (i = 0; i < max_place_holder; ++i)
	{
		next_p_h_array[i] = place_holder_array[i];
	}
}

/*******************************************************************************
 * FUNCTION:	NEVER_CALLED
 *
 *	A no-op XmNactivateCallback function for the global XmPushButton
 *	widgets in entry[].
 ******************************************************************************/
void            never_called (Widget w, XtPointer x, XmAnyCallbackStruct z)
{
}

static void     clear_more (int *next_p_h_array, int column)
{
	int             i;

	column = column + 1;
	for (i = column; i < max_place_holder; ++i)
		next_p_h_array[i] = 0;
}

/*
 * ----------------------------------------------------- Define the syntax of
 * Descartes specification language through the use of pre-defined templates
 * -----------------------------------------------------
 */
static void     create_descartes_definition (struct construct * descartes_template)
{
	descartes_template[module].place_holder_1 = nn;
	descartes_template[module].place_holder_2 = nulll;
	descartes_template[module].place_holder_3 = nulll;
	descartes_template[module].place_holder_4 = nulll;
	descartes_template[module].place_holder_5 = nulll;
	descartes_template[module].place_holder_6 = nulll;
	descartes_template[module].place_holder_7 = nulll;
	descartes_template[module].place_holder_8 = nulll;
	descartes_template[module].place_holder_9 = nulll;
	descartes_template[module].place_holder_10 = nulll;
	descartes_template[module].phrase = nulll;
	descartes_template[module].next_place_holder_ind = indent;
	descartes_template[module].next_place_holder_1 = hoare_trees;
	descartes_template[module].next_place_holder_2 = nulll;

	descartes_template[hoare_trees].place_holder_1 = analysis_tree;
	descartes_template[hoare_trees].place_holder_2 = synthesis_tree;
	descartes_template[hoare_trees].place_holder_3 = nulll;
	descartes_template[hoare_trees].place_holder_4 = nulll;
	descartes_template[hoare_trees].place_holder_5 = nulll;
	descartes_template[hoare_trees].place_holder_6 = nulll;
	descartes_template[hoare_trees].place_holder_7 = nulll;
	descartes_template[hoare_trees].place_holder_8 = nulll;
	descartes_template[hoare_trees].place_holder_9 = nulll;
	descartes_template[hoare_trees].place_holder_10 = nulll;
	descartes_template[hoare_trees].phrase = nulll;
	descartes_template[hoare_trees].next_place_holder_ind = no_indent;
	descartes_template[hoare_trees].next_place_holder_1 = hoare_trees;
	descartes_template[hoare_trees].next_place_holder_2 = nulll;

	descartes_template[3].place_holder_1 = ref_direct_product;
	descartes_template[3].place_holder_2 = ref_discriminated_union;
	descartes_template[3].place_holder_3 = ref_sequence_1;
	descartes_template[3].place_holder_4 = ref_sequence_2;
	descartes_template[3].place_holder_5 = ref_sequence_3;
	descartes_template[3].place_holder_6 = nulll;
	descartes_template[3].place_holder_7 = nulll;
	descartes_template[3].place_holder_8 = nulll;
	descartes_template[3].place_holder_9 = nulll;
	descartes_template[3].place_holder_10 = nulll;
	descartes_template[3].phrase = nulll;
	descartes_template[3].next_place_holder_ind = indent;
	descartes_template[3].next_place_holder_1 = rest_of_analysis_tree;
	descartes_template[3].next_place_holder_2 = nulll;

	descartes_template[4].place_holder_1 = rtn;
	descartes_template[4].place_holder_2 = mat_direct_product;
	descartes_template[4].place_holder_3 = mat_discriminated_union;
	descartes_template[4].place_holder_4 = mat_sequence_1;
	descartes_template[4].place_holder_5 = mat_sequence_2;
	descartes_template[4].place_holder_6 = mat_sequence_3;
	descartes_template[4].place_holder_7 = nulll;
	descartes_template[4].place_holder_8 = nulll;
	descartes_template[4].place_holder_9 = nulll;
	descartes_template[4].place_holder_10 = nulll;
	descartes_template[4].phrase = nulll;
	descartes_template[4].next_place_holder_ind = indent;
	descartes_template[4].next_place_holder_1 = rest_of_synthesis_tree;
	descartes_template[4].next_place_holder_2 = nulll;

	descartes_template[5].place_holder_1 = ref_direct_product;
	descartes_template[5].place_holder_2 = ref_discriminated_union;
	descartes_template[5].place_holder_3 = ref_sequence_1;
	descartes_template[5].place_holder_4 = ref_sequence_2;
	descartes_template[5].place_holder_5 = ref_sequence_3;
	descartes_template[5].place_holder_6 = mat_direct_product;
	descartes_template[5].place_holder_7 = mat_discriminated_union;
	descartes_template[5].place_holder_8 = mat_sequence_1;
	descartes_template[5].place_holder_9 = mat_sequence_2;
	descartes_template[5].place_holder_10 = mat_sequence_3;
	descartes_template[5].phrase = nulll;
	descartes_template[5].next_place_holder_ind = no_indent;
	descartes_template[5].next_place_holder_1 = rest_of_analysis_tree;
	descartes_template[5].next_place_holder_2 = rest_of_analysis_tree;

	descartes_template[6].place_holder_1 = ref_direct_product;
	descartes_template[6].place_holder_2 = ref_discriminated_union;
	descartes_template[6].place_holder_3 = ref_sequence_1;
	descartes_template[6].place_holder_4 = ref_sequence_2;
	descartes_template[6].place_holder_5 = ref_sequence_3;
	descartes_template[6].place_holder_6 = mat_direct_product;
	descartes_template[6].place_holder_7 = mat_discriminated_union;
	descartes_template[6].place_holder_8 = mat_sequence_1;
	descartes_template[6].place_holder_9 = mat_sequence_2;
	descartes_template[6].place_holder_10 = mat_sequence_3;
	descartes_template[6].phrase = nulll;
	descartes_template[6].next_place_holder_ind = no_indent;
	descartes_template[6].next_place_holder_1 = rest_of_synthesis_tree;
	descartes_template[6].next_place_holder_2 = rest_of_synthesis_tree;

	descartes_template[7].place_holder_1 = ref_direct_product;
	descartes_template[7].place_holder_2 = ref_discriminated_union;
	descartes_template[7].place_holder_3 = ref_sequence_1;
	descartes_template[7].place_holder_4 = ref_sequence_2;
	descartes_template[7].place_holder_5 = ref_sequence_3;
	descartes_template[7].place_holder_6 = nulll;
	descartes_template[7].place_holder_7 = nulll;
	descartes_template[7].place_holder_8 = nulll;
	descartes_template[7].place_holder_9 = nulll;
	descartes_template[7].place_holder_10 = nulll;
	descartes_template[7].phrase = nulll;
	descartes_template[7].next_place_holder_ind = no_indent;
	descartes_template[7].next_place_holder_1 = nulll;
	descartes_template[7].next_place_holder_2 = nulll;

	descartes_template[8].place_holder_1 = mat_direct_product;
	descartes_template[8].place_holder_2 = mat_discriminated_union;
	descartes_template[8].place_holder_3 = mat_sequence_1;
	descartes_template[8].place_holder_4 = mat_sequence_2;
	descartes_template[8].place_holder_5 = mat_sequence_3;
	descartes_template[8].place_holder_6 = nulll;
	descartes_template[8].place_holder_7 = nulll;
	descartes_template[8].place_holder_8 = nulll;
	descartes_template[8].place_holder_9 = nulll;
	descartes_template[8].place_holder_10 = nulll;
	descartes_template[8].phrase = nulll;
	descartes_template[8].next_place_holder_ind = no_indent;
	descartes_template[8].next_place_holder_1 = nulll;
	descartes_template[8].next_place_holder_2 = nulll;

	descartes_template[ref_direct_product].place_holder_1 = nn;
	descartes_template[ref_direct_product].place_holder_2 = nulll;
	descartes_template[ref_direct_product].place_holder_3 = nulll;
	descartes_template[ref_direct_product].place_holder_4 = nulll;
	descartes_template[ref_direct_product].place_holder_5 = nulll;
	descartes_template[ref_direct_product].place_holder_6 = nulll;
	descartes_template[ref_direct_product].place_holder_7 = nulll;
	descartes_template[ref_direct_product].place_holder_8 = nulll;
	descartes_template[ref_direct_product].place_holder_9 = nulll;
	descartes_template[ref_direct_product].place_holder_10 = nulll;
	descartes_template[ref_direct_product].phrase = nulll;
	descartes_template[ref_direct_product].next_place_holder_ind = no_indent;
	descartes_template[ref_direct_product].next_place_holder_1 = nulll;
	descartes_template[ref_direct_product].next_place_holder_2 = nulll;

	descartes_template[ref_discriminated_union].place_holder_1 = nn;
	descartes_template[ref_discriminated_union].place_holder_2 = nulll;
	descartes_template[ref_discriminated_union].place_holder_3 = nulll;
	descartes_template[ref_discriminated_union].place_holder_4 = nulll;
	descartes_template[ref_discriminated_union].place_holder_5 = nulll;
	descartes_template[ref_discriminated_union].place_holder_6 = nulll;
	descartes_template[ref_discriminated_union].place_holder_7 = nulll;
	descartes_template[ref_discriminated_union].place_holder_8 = nulll;
	descartes_template[ref_discriminated_union].place_holder_9 = nulll;
	descartes_template[ref_discriminated_union].place_holder_10 = nulll;
	descartes_template[ref_discriminated_union].phrase = du;
	descartes_template[ref_discriminated_union].next_place_holder_ind = no_indent;
	descartes_template[ref_discriminated_union].next_place_holder_1 = nulll;
	descartes_template[ref_discriminated_union].next_place_holder_2 = nulll;

	descartes_template[ref_sequence_1].place_holder_1 = nn;
	descartes_template[ref_sequence_1].place_holder_2 = nulll;
	descartes_template[ref_sequence_1].place_holder_3 = nulll;
	descartes_template[ref_sequence_1].place_holder_4 = nulll;
	descartes_template[ref_sequence_1].place_holder_5 = nulll;
	descartes_template[ref_sequence_1].place_holder_6 = nulll;
	descartes_template[ref_sequence_1].place_holder_7 = nulll;
	descartes_template[ref_sequence_1].place_holder_8 = nulll;
	descartes_template[ref_sequence_1].place_holder_9 = nulll;
	descartes_template[ref_sequence_1].place_holder_10 = nulll;
	descartes_template[ref_sequence_1].phrase = sq1;
	descartes_template[ref_sequence_1].next_place_holder_ind = no_indent;
	descartes_template[ref_sequence_1].next_place_holder_1 = nulll;
	descartes_template[ref_sequence_1].next_place_holder_2 = nulll;

	descartes_template[ref_sequence_2].place_holder_1 = nn;
	descartes_template[ref_sequence_2].place_holder_2 = nulll;
	descartes_template[ref_sequence_2].place_holder_3 = nulll;
	descartes_template[ref_sequence_2].place_holder_4 = nulll;
	descartes_template[ref_sequence_2].place_holder_5 = nulll;
	descartes_template[ref_sequence_2].place_holder_6 = nulll;
	descartes_template[ref_sequence_2].place_holder_7 = nulll;
	descartes_template[ref_sequence_2].place_holder_8 = nulll;
	descartes_template[ref_sequence_2].place_holder_9 = nulll;
	descartes_template[ref_sequence_2].place_holder_10 = nulll;
	descartes_template[ref_sequence_2].phrase = sq2;
	descartes_template[ref_sequence_2].next_place_holder_ind = no_indent;
	descartes_template[ref_sequence_2].next_place_holder_1 = nulll;
	descartes_template[ref_sequence_2].next_place_holder_2 = nulll;

	descartes_template[ref_sequence_3].place_holder_1 = nn;
	descartes_template[ref_sequence_3].place_holder_2 = nulll;
	descartes_template[ref_sequence_3].place_holder_3 = nulll;
	descartes_template[ref_sequence_3].place_holder_4 = nulll;
	descartes_template[ref_sequence_3].place_holder_5 = nulll;
	descartes_template[ref_sequence_3].place_holder_6 = nulll;
	descartes_template[ref_sequence_3].place_holder_7 = nulll;
	descartes_template[ref_sequence_3].place_holder_8 = nulll;
	descartes_template[ref_sequence_3].place_holder_9 = nulll;
	descartes_template[ref_sequence_3].place_holder_10 = nulll;
	descartes_template[ref_sequence_3].phrase = sq3;
	descartes_template[ref_sequence_3].next_place_holder_ind = no_indent;
	descartes_template[ref_sequence_3].next_place_holder_1 = nulll;
	descartes_template[ref_sequence_3].next_place_holder_2 = nulll;

	descartes_template[mat_direct_product].place_holder_1 = nn;
	descartes_template[mat_direct_product].place_holder_2 = nulll;
	descartes_template[mat_direct_product].place_holder_3 = nulll;
	descartes_template[mat_direct_product].place_holder_4 = nulll;
	descartes_template[mat_direct_product].place_holder_5 = nulll;
	descartes_template[mat_direct_product].place_holder_6 = nulll;
	descartes_template[mat_direct_product].place_holder_7 = nulll;
	descartes_template[mat_direct_product].place_holder_8 = nulll;
	descartes_template[mat_direct_product].place_holder_9 = nulll;
	descartes_template[mat_direct_product].place_holder_10 = nulll;
	descartes_template[mat_direct_product].phrase = nulll;
	descartes_template[mat_direct_product].next_place_holder_ind = no_indent;
	descartes_template[mat_direct_product].next_place_holder_1 = nulll;
	descartes_template[mat_direct_product].next_place_holder_2 = nulll;

	descartes_template[mat_discriminated_union].place_holder_1 = nn;
	descartes_template[mat_discriminated_union].place_holder_2 = nulll;
	descartes_template[mat_discriminated_union].place_holder_3 = nulll;
	descartes_template[mat_discriminated_union].place_holder_4 = nulll;
	descartes_template[mat_discriminated_union].place_holder_5 = nulll;
	descartes_template[mat_discriminated_union].place_holder_6 = nulll;
	descartes_template[mat_discriminated_union].place_holder_7 = nulll;
	descartes_template[mat_discriminated_union].place_holder_8 = nulll;
	descartes_template[mat_discriminated_union].place_holder_9 = nulll;
	descartes_template[mat_discriminated_union].place_holder_10 = nulll;
	descartes_template[mat_discriminated_union].phrase = du;
	descartes_template[mat_discriminated_union].next_place_holder_ind = no_indent;
	descartes_template[mat_discriminated_union].next_place_holder_1 = nulll;
	descartes_template[mat_discriminated_union].next_place_holder_2 = nulll;

	descartes_template[mat_sequence_1].place_holder_1 = nn;
	descartes_template[mat_sequence_1].place_holder_2 = nulll;
	descartes_template[mat_sequence_1].place_holder_3 = nulll;
	descartes_template[mat_sequence_1].place_holder_4 = nulll;
	descartes_template[mat_sequence_1].place_holder_5 = nulll;
	descartes_template[mat_sequence_1].place_holder_6 = nulll;
	descartes_template[mat_sequence_1].place_holder_7 = nulll;
	descartes_template[mat_sequence_1].place_holder_8 = nulll;
	descartes_template[mat_sequence_1].place_holder_9 = nulll;
	descartes_template[mat_sequence_1].place_holder_10 = nulll;
	descartes_template[mat_sequence_1].phrase = sq1;
	descartes_template[mat_sequence_1].next_place_holder_ind = no_indent;
	descartes_template[mat_sequence_1].next_place_holder_1 = nulll;
	descartes_template[mat_sequence_1].next_place_holder_2 = nulll;

	descartes_template[mat_sequence_2].place_holder_1 = nn;
	descartes_template[mat_sequence_2].place_holder_2 = nulll;
	descartes_template[mat_sequence_2].place_holder_3 = nulll;
	descartes_template[mat_sequence_2].place_holder_4 = nulll;
	descartes_template[mat_sequence_2].place_holder_5 = nulll;
	descartes_template[mat_sequence_2].place_holder_6 = nulll;
	descartes_template[mat_sequence_2].place_holder_7 = nulll;
	descartes_template[mat_sequence_2].place_holder_8 = nulll;
	descartes_template[mat_sequence_2].place_holder_9 = nulll;
	descartes_template[mat_sequence_2].place_holder_10 = nulll;
	descartes_template[mat_sequence_2].phrase = sq2;
	descartes_template[mat_sequence_2].next_place_holder_ind = no_indent;
	descartes_template[mat_sequence_2].next_place_holder_1 = nulll;
	descartes_template[mat_sequence_2].next_place_holder_2 = nulll;

	descartes_template[mat_sequence_3].place_holder_1 = nn;
	descartes_template[mat_sequence_3].place_holder_2 = nulll;
	descartes_template[mat_sequence_3].place_holder_3 = nulll;
	descartes_template[mat_sequence_3].place_holder_4 = nulll;
	descartes_template[mat_sequence_3].place_holder_5 = nulll;
	descartes_template[mat_sequence_3].place_holder_6 = nulll;
	descartes_template[mat_sequence_3].place_holder_7 = nulll;
	descartes_template[mat_sequence_3].place_holder_8 = nulll;
	descartes_template[mat_sequence_3].place_holder_9 = nulll;
	descartes_template[mat_sequence_3].place_holder_10 = nulll;
	descartes_template[mat_sequence_3].phrase = sq3;
	descartes_template[mat_sequence_3].next_place_holder_ind = no_indent;
	descartes_template[mat_sequence_3].next_place_holder_1 = nulll;
	descartes_template[mat_sequence_3].next_place_holder_2 = nulll;
}

/*******************************************************************************
 * FUNCTION:	NEW_MODULE
 *
 *	Initiate a new Descartes specification module.
 *	Called by  parser(), add_module() and main() below, and by
 *	close_proc() in xdesc2.c.
 ******************************************************************************/
struct node    *new_module (void)
{
	struct node    *new_module_head;

	new_module_head = (struct node *) calloc (1, sizeof (struct node));
	if (new_module_head != 0)
	{
		new_module_head->node_name = "ROOT_DUMMY";
		new_module_head->ancester = 0;
		new_module_head->level = 0;
		new_module_head->front = 0;
		new_module_head->back = 0;
		new_module_head->row = 0;
		new_module_head->col = 0;
		new_module_head->before = 0;
		new_module_head->name_length = 10;
		new_module_head->origion_x = -81;

		if (number_of_modules < 1)
			new_module_head->origion_y = -17;
		else
		{
			new_module_head->origion_y = region[1][1];
		}

		new_module_head->tree_type = 0;
		new_module_head->node_type = 0;
		new_module_head->d_s_method = 0;

		new_module_head->append_head = (struct append_place_holder *) calloc
			(1, sizeof (struct append_place_holder));

		if (new_module_head->append_head != 0)
		{
			new_module_head->append_head->p_h_type = module;
			new_module_head->append_head->next = 0;
		}

	}
	return (new_module_head);
}

/*******************************************************************************
 * FUNCTION:	CALCULATE_STRING_DATA
 ******************************************************************************/
void            calculate_string_data (struct node * node_ptr)
{
	text_data_ptr   data_ptr;
	int             ll,
	                dir,
	                ascent,
	                descent;
	XCharStruct     char_info;

	if (node_ptr == NULL)
	{
/* Malcolm */
		printf("\nBOGUS: passed a null value for node_ptr\n");
		XBell (XtDisplay (drawing_area), 0);
		return;
	}
	data_ptr = &data;
	ll = strlen (node_ptr->node_name);
	XTextExtents (data_ptr->font, node_ptr->node_name, ll, &dir, &ascent, &descent,
		      &char_info);
	str_data.ascent = ascent;
	str_data.descent = descent;
	str_data.height = ascent + descent;
	str_data.origion_x = node_ptr->origion_x;
	str_data.origion_y = node_ptr->origion_y;
	str_data.text_origion_x = str_data.origion_x + text_border_margin;
	str_data.text_origion_y = str_data.origion_y + text_border_margin + str_data.height;
	str_data.text_xleft = str_data.text_origion_x;
	str_data.text_xright = str_data.text_origion_x + char_info.width;
	str_data.text_ytop = str_data.origion_y + text_border_margin;
	str_data.text_ybottom = str_data.text_origion_y;
	str_data.xleft = str_data.origion_x;
	str_data.xright = str_data.text_xright + text_border_margin;
	str_data.ytop = str_data.text_ytop - text_border_margin;
	str_data.ybottom = str_data.text_ybottom + text_border_margin;
}


/*******************************************************************************
 * FUNCTION:	CALCULATE_RB_DATA
 *
 *	Called only by functions in xdesc2.c.  Consider moving this
 *	function and making it static.
 *	Called from draw_rubberband() and end_rubberband()
 ******************************************************************************/
void            calculate_rb_data (struct rubber_node * node_ptr)
{
	text_data_ptr   data_ptr;
	int             ll,
	                dir,
	                ascent,
	                descent;
	XCharStruct     char_info;

	data_ptr = &data;
	ll = strlen (node_ptr->node_name);
	XTextExtents (data_ptr->font, node_ptr->node_name, ll, &dir, &ascent, &descent,
		      &char_info);
	str_data.ascent = ascent;
	str_data.descent = descent;
	str_data.height = ascent + descent;
	str_data.origion_x = node_ptr->origion_x;
	str_data.origion_y = node_ptr->origion_y;
	str_data.text_origion_x = str_data.origion_x + text_border_margin;
	str_data.text_origion_y = str_data.origion_y + text_border_margin + str_data.height;
	str_data.text_xleft = str_data.text_origion_x;
	str_data.text_xright = str_data.text_origion_x + char_info.width;
	str_data.text_ytop = str_data.origion_y + text_border_margin;
	str_data.text_ybottom = str_data.text_origion_y;
	str_data.xleft = str_data.origion_x;
	str_data.xright = str_data.text_xright + text_border_margin;
	str_data.ytop = str_data.text_ytop - text_border_margin;
	str_data.ybottom = str_data.text_ybottom + text_border_margin;
}

/*******************************************************************************
 * FUNCTION:	DISPLAY_TEMPLATE_TREE
 *
 *	Display content of a template tree in graphics format.
 ******************************************************************************/
void            display_template_tree (struct node * tp_tree_pointer)
{
	struct node    *back_pointer;
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
	int             displaying_index;
	text_data_ptr   data_ptr;
	Widget          w;
	XCharStruct     char_info;

	w = drawing_area;
	data_ptr = &data;

	displaying_index = 1;
	while (displaying_index <= number_of_modules)
	{
		tp_tree_pointer = module_heads[displaying_index];
		if (tp_tree_pointer->col == 0)
			tp_tree_pointer = tp_tree_pointer->next;
		while (tp_tree_pointer != 0)
		{
			calculate_string_data (tp_tree_pointer);
			save_xright = str_data.xright;
			save_orig_y = str_data.origion_y;
			XDrawString (XtDisplay (w), XtWindow (w), theGC, str_data.text_origion_x,
				     str_data.text_origion_y, tp_tree_pointer->node_name,
				     strlen (tp_tree_pointer->node_name));
		/* draw box */
			XDrawLine (XtDisplay (w), XtWindow (w), theGC, str_data.xleft, str_data.ytop,
				   str_data.xright, str_data.ytop);
			XDrawLine (XtDisplay (w), XtWindow (w), theGC, str_data.xright, str_data.ytop,
				   str_data.xright, str_data.ybottom);
			XDrawLine (XtDisplay (w), XtWindow (w), theGC, str_data.xright, str_data.ybottom,
				   str_data.xleft, str_data.ybottom);
			XDrawLine (XtDisplay (w), XtWindow (w), theGC, str_data.xleft, str_data.ybottom,
				   str_data.xleft, str_data.ytop);

		/* draw connecting edge */
			if (tp_tree_pointer->col == 1)
			{
				edge_origin_x = str_data.xright;
				edge_origin_y = str_data.origion_y + text_border_margin + str_data.ascent;
			}
			else
			{
				edge_end_x = str_data.xleft;
				edge_end_y = str_data.origion_y + text_border_margin + str_data.ascent;
				back_pointer = tp_tree_pointer;
				while (edge_end_x < edge_origin_x)
				{
					calculate_string_data (back_pointer);
					edge_origin_x = str_data.xright;
					edge_origin_y = str_data.origion_y + str_data.ascent + text_border_margin;
					back_pointer = back_pointer->before;
				}
				edge_upper_half_x = edge_origin_x + node_to_node_half_space;
				edge_upper_half_y = edge_origin_y;
				edge_lower_half_x = edge_upper_half_x;
				edge_lower_half_y = edge_end_y;
				XDrawLine (XtDisplay (w), XtWindow (w), theGC, edge_origin_x, edge_origin_y,
						edge_upper_half_x, edge_upper_half_y);
				XDrawLine (XtDisplay (w), XtWindow (w), theGC, edge_upper_half_x, edge_upper_half_y,
						edge_lower_half_x, edge_lower_half_y);
				XDrawLine (XtDisplay (w), XtWindow (w), theGC, edge_lower_half_x, edge_lower_half_y,
						edge_end_x, edge_end_y);
				edge_origin_x = save_xright;
				edge_origin_y = save_orig_y + str_data.ascent + text_border_margin;
			}
			tp_tree_pointer = tp_tree_pointer->next;
		}
		displaying_index = displaying_index + 1;
	}
}

/*******************************************************************************
 * FUNCTION:	DISPLAY_TEMPLATE_TREE_DEBUG
 *
 *	Display content of a template tree in graphics format.  Called along
 *	with debugger() in xdesc1.c and xdesc2.c
 ******************************************************************************/
void            display_template_tree_debug (struct node * tp_tree_pointer)
{
	text_data_ptr   data_ptr;
	Widget          w;

	w = drawing_area;
	data_ptr = &data;
	if (tp_tree_pointer->col == 0)
		tp_tree_pointer = tp_tree_pointer->next;
	printf ("name | ancester | level | front | back | next | before |\n");
	printf ("-------------------------------------------------------\n");
	while (tp_tree_pointer != 0)
	{
		printf ("%s  |  ", tp_tree_pointer->node_name);

		if (tp_tree_pointer->ancester != NULL)
			printf ("%s  |  ", tp_tree_pointer->ancester->node_name);
		else
			printf ("---   |  ");

		if (tp_tree_pointer->level != NULL)
			printf ("%s | ", tp_tree_pointer->level->node_name);
		else
			printf ("---   |  ");

		if (tp_tree_pointer->front != NULL)
			printf ("%s  |  ", tp_tree_pointer->front->node_name);
		else
			printf ("---   |  ");

		if (tp_tree_pointer->back != NULL)
			printf ("%s  |  ", tp_tree_pointer->back->node_name);
		else
			printf ("---   |  ");

		if (tp_tree_pointer->next != NULL)
			printf ("%s  |  ", tp_tree_pointer->next->node_name);
		else
			printf ("---   |  ");

		if (tp_tree_pointer->before != NULL)
			printf ("%s  |\n", tp_tree_pointer->before->node_name);
		else
			printf ("---  |\n");

		printf ("row ==> %d col ==> %d\n", tp_tree_pointer->row, tp_tree_pointer->col);
		tp_tree_pointer = tp_tree_pointer->next;
	}
	printf ("-------------------------------------------------------\n");
}

/*******************************************************************************
 * FUNCTION:	DEBUGGER
 ******************************************************************************/
void            debugger (struct node * tp_tree_pointer)
{
	int             matched;
	struct node    *temp_ptr;

	if (tp_tree_pointer->col == 0)
		tp_tree_pointer = tp_tree_pointer->next;
	while (tp_tree_pointer != NULL)
	{

	/*
	 * ...................................................................
	 */
		if (tp_tree_pointer->ancester != NULL)
			matched = strcmp (tp_tree_pointer->node_name, tp_tree_pointer->ancester->node_name);
		if (tp_tree_pointer->level != NULL)
			matched = strcmp (tp_tree_pointer->node_name, tp_tree_pointer->level->node_name);
		if (tp_tree_pointer->front != NULL)
			matched = strcmp (tp_tree_pointer->node_name, tp_tree_pointer->front->node_name);
		if (tp_tree_pointer->back != NULL)
			matched = strcmp (tp_tree_pointer->node_name, tp_tree_pointer->back->node_name);
		if (tp_tree_pointer->next != NULL)
			matched = strcmp (tp_tree_pointer->node_name, tp_tree_pointer->next->node_name);
		if (tp_tree_pointer->before != NULL)
			matched = strcmp (tp_tree_pointer->node_name, tp_tree_pointer->before->node_name);
		if (matched == 0)
		{
			printf ("***** NODE NAME SAME AS ONE OF IT'S RELATIVES *****\n");
			XBell (XtDisplay (drawing_area), 0);
		}

	/*
	 * ...................................................................
	 */

		if (tp_tree_pointer->level != NULL)
		{
			if (tp_tree_pointer->level->ancester != tp_tree_pointer)
			{
				printf ("***** LEVEL <--> ANCESTER ERROR *****\n");
				XBell (XtDisplay (drawing_area), 0);
			}
		}

		if (tp_tree_pointer->back != NULL)
		{
			if (tp_tree_pointer->back->front != tp_tree_pointer)
			{
				printf ("***** BACK <--> FRONT ERROR *****\n");
				XBell (XtDisplay (drawing_area), 0);
			}
		}

		if (tp_tree_pointer->front != NULL)
		{
			if (tp_tree_pointer->front->back != tp_tree_pointer)
			{
				printf ("***** FRONT <--> BACK ERROR *****\n");
				XBell (XtDisplay (drawing_area), 0);
			}
		}

		if (tp_tree_pointer->next != NULL)
		{
			if (tp_tree_pointer->next->before != tp_tree_pointer)
			{
				printf ("***** NEXT <--> BEFORE ERROR *****\n");
				XBell (XtDisplay (drawing_area), 0);
			}
		}

		if (tp_tree_pointer->before != NULL)
		{
			if (tp_tree_pointer->before->next != tp_tree_pointer)
			{
				printf ("***** BEFORE <--> NEXT ERROR *****\n");
				XBell (XtDisplay (drawing_area), 0);
			}
		}

	/*
	 * ...................................................................
	 */
		if (tp_tree_pointer->level != NULL)
		{
			temp_ptr = tp_tree_pointer->level->front;
			while (temp_ptr != NULL)
			{
				if (temp_ptr->ancester != tp_tree_pointer->level->ancester)
				{
					printf ("***** LEVEL FRONT ANCESTER ERROR *****\n");
					XBell (XtDisplay (drawing_area), 0);
				}
				temp_ptr = temp_ptr->front;
			}
		}

	/*
	 * ...................................................................
	 */

		tp_tree_pointer = tp_tree_pointer->next;
	}
}


/*******************************************************************************
 * FUNCTION:	ERASE_TEMPLATE_TREE
 *
 *	Erase content of a template tree in graphics format.
 ******************************************************************************/
void            erase_template_tree (struct node * tp_tree_pointer)
{
	struct node    *back_pointer;
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
	int             displaying_index;
	text_data_ptr   data_ptr;
	Widget          w;

	w = drawing_area;

	data_ptr = &data;

	displaying_index = 1;
	while (displaying_index <= number_of_modules)
	{
		tp_tree_pointer = module_heads[displaying_index];
		if (tp_tree_pointer->col == 0)
			tp_tree_pointer = tp_tree_pointer->next;
		while (tp_tree_pointer != 0)
		{
			calculate_string_data (tp_tree_pointer);
			save_xright = str_data.xright;
			save_orig_y = str_data.origion_y;
			XDrawString (XtDisplay (w), XtWindow (w), inverseGC, str_data.text_origion_x,
				     str_data.text_origion_y, tp_tree_pointer->node_name, strlen (tp_tree_pointer->node_name));
		/* draw box */
			XDrawLine (XtDisplay (w), XtWindow (w), inverseGC, str_data.xleft,
					str_data.ytop, str_data.xright, str_data.ytop);
			XDrawLine (XtDisplay (w), XtWindow (w), inverseGC, str_data.xright,
					str_data.ytop, str_data.xright, str_data.ybottom);
			XDrawLine (XtDisplay (w), XtWindow (w), inverseGC, str_data.xright,
					str_data.ybottom, str_data.xleft, str_data.ybottom);
			XDrawLine (XtDisplay (w), XtWindow (w), inverseGC, str_data.xleft,
					str_data.ybottom, str_data.xleft, str_data.ytop);

		/* draw connecting edge */
			if (tp_tree_pointer->col == 1)
			{
				edge_origin_x = str_data.xright;
				edge_end_y = str_data.origion_y + text_border_margin + str_data.ascent;
			}
			else
			{
				edge_end_x = str_data.xleft;
				edge_end_y = str_data.origion_y + text_border_margin + str_data.ascent;
				back_pointer = tp_tree_pointer;
				while (edge_end_x < edge_origin_x)
				{
					calculate_string_data (back_pointer);
					edge_origin_x = str_data.xright;
					edge_origin_y = str_data.origion_y + str_data.ascent + text_border_margin;
					back_pointer = back_pointer->before;
				}
				edge_upper_half_x = edge_origin_x + node_to_node_half_space;
				edge_upper_half_y = edge_origin_y;
				edge_lower_half_x = edge_upper_half_x;
				edge_lower_half_y = edge_end_y;
				XDrawLine (XtDisplay (w), XtWindow (w), inverseGC, edge_origin_x,
						edge_origin_y, edge_upper_half_x, edge_upper_half_y);
				XDrawLine (XtDisplay (w), XtWindow (w), inverseGC, edge_upper_half_x,
						edge_upper_half_y, edge_lower_half_x, edge_lower_half_y);
				XDrawLine (XtDisplay (w), XtWindow (w), inverseGC, edge_lower_half_x,
						edge_lower_half_y, edge_end_x, edge_end_y);
				edge_origin_x = save_xright;
				edge_origin_y = save_orig_y + str_data.ascent + text_border_margin;
			}
			tp_tree_pointer = tp_tree_pointer->next;
		}
		displaying_index = displaying_index + 1;
	}
}

/*******************************************************************************
 * FUNCTION:	RETURN_ITEM
 *
 *	XmNentryCallback function for the following XmPopupMenu widgets:
 *		- popup_icon_menu in display_next_place_holder()
 *		- d_s_menu in mod_ds_method_proc()
 ******************************************************************************/
void            return_item (Widget menu_item, XtPointer item_nooo, XmRowColumnCallbackStruct * cbs)
{
	int             item_no;

	item_no = (int) (cbs->data);
	selected_item = item_no;
/*
 * if(item_no == 0) selected_item = 1;
 */
	answered = TRUE;
	return;
}

/*
 * ---------------------------------------- display connt of next row place
 * holders in a menu, after the user make a selection the menu is destroyed
 * (drawn button version) -----------------------------------------
 */

/*
 * Malcolm -- CAUTION:  I didn't see anything in the calling routines code
 * that would ensure that only XButtonPressedEvent s would get passed to this
 * function
 */
static int      display_next_place_holder (int *p_h_array, XButtonPressedEvent * event)
{
	int             menu_value;
	Pixmap          label_icon;
	Pixmap          icon[15];
	char           *string[15];
	int             i = 1;
	int             j = 1;
	int             k,
	                n;
	Widget          popup_icon_menu;
	Arg             args[10];
	Cardinal        narg;
	XmStringCharSet charset = XmSTRING_DEFAULT_CHARSET;
	char           *modt = "[MOD]";
	char           *htt = "[HT] ";
	char           *att = "[AT] ";
	char           *stt = "[ST] ";
	char           *ratt = "[RAT]";
	char           *rstt = "[RST]";
	char           *reft = "[REF]";
	char           *matt = "[MAT]";
	char           *ref_dpt = "[DP] ";
	char           *ref_dut = "[DU+]";
	char           *indt = "[IND]";
	char           *ref_sq1t = "[SQ*]";
	char           *ref_sq2t = "[SQ:]";
	char           *ref_sq3t = "[S*+]";
	char           *mat_dpt = "[dp] ";
	char           *mat_dut = "[du+]";
	char           *mat_sq1t = "[sq*]";
	char           *mat_sq2t = "[sq:]";
	char           *mat_sq3t = "[s*+]";
	char           *rtnt = "[rtn]";
	char           *command1 = "screendump > temp1";
	char           *command2 = "screendump > temp2";
	char           *command3 = "screendump > temp3";
	char           *command4 = "screendump > temp4";
	char           *command5 = "screendump > temp5";
	char           *command6 = "screendump > temp6";

	for (k = 0; k <= 14; ++k)
		string[k] = (char *) calloc (10, sizeof (char));

	answered = FALSE;
	while (p_h_array[i] != 0 && p_h_array[i] != nulll)
	{
		switch (p_h_array[i])
		{
			case analysis_tree:

				icon[j] = pix_a_tree;
				strcpy (string[j], "icon1");
				break;
			case synthesis_tree:
				icon[j] = pix_s_tree;
				strcpy (string[j], "icon2");
				break;
			case ref_direct_product:
				icon[j] = pix_ref_dp;
				strcpy (string[j], "icon3");
				break;
			case ref_discriminated_union:
				icon[j] = pix_ref_du;
				strcpy (string[j], "icon4");
				break;
			case ref_sequence_1:
				icon[j] = pix_ref_sq1;
				strcpy (string[j], "icon5");
				break;
			case ref_sequence_2:
				icon[j] = pix_ref_sq2;
				strcpy (string[j], "icon6");
				break;
			case ref_sequence_3:
				icon[j] = pix_ref_sq3;
				strcpy (string[j], "icon7");
				break;
			case mat_direct_product:
				icon[j] = pix_mat_dp;
				strcpy (string[j], "icon8");
				break;
			case mat_discriminated_union:
				icon[j] = pix_mat_du;
				strcpy (string[j], "icon9");
				break;
			case mat_sequence_1:
				icon[j] = pix_mat_sq1;
				strcpy (string[j], "icon10");
				break;
			case mat_sequence_2:
				icon[j] = pix_mat_sq2;
				strcpy (string[j], "icon11");
				break;
			case mat_sequence_3:
				icon[j] = pix_mat_sq3;
				strcpy (string[j], "icon12");
				break;
			case rtn:
				icon[j] = pix_ret;
				strcpy (string[j], "icon13");
				break;
			default:
				break;
		}
		++i;
		++j;
	}
	narg = 0;
	XtSetArg (args[narg], XmNorientation, XmVERTICAL);
	narg++;
	XtSetArg (args[narg], XmNpacking, XmPACK_COLUMN);
	narg++;
/* XtSetArg(args[narg], XmNbackgroundPixmap, pmap_50); narg++; */
/* ---------------------------------------------- */
	if (icon[1] == pix_ref_dp && icon[6] == pix_mat_dp)
	{
		XtSetArg (args[narg], XmNnumColumns, 2);
		narg++;
	}
	printf ("BEFORE CREATE POPUP\n");
	popup_icon_menu = XmCreatePopupMenu (drawing_area, "Popup_icon", args, narg);
	printf ("AFTER CREATE POPUP\n");
	XtAddCallback (popup_icon_menu, XmNentryCallback, (XtCallbackProc) return_item, NULL);
	for (i = 1; i < j; ++i)
	{
		label_icon = icon[i];
		narg = 0;
		XtSetArg (args[narg], XmNlabelType, XmPIXMAP);
		narg++;
		XtSetArg (args[narg], XmNlabelPixmap, label_icon);
		narg++;
		entry[i] = XmCreatePushButton (popup_icon_menu, string[i], args, narg);
		XtAddCallback (entry[i], XmNactivateCallback, (XtCallbackProc) never_called, (XtPointer) i);
		XtManageChild (entry[i]);
	}
	XmMenuPosition (popup_icon_menu, event);
	XtManageChild (popup_icon_menu);
/* ----------------------------- */
/* CODES TO GENERATE SCREEN DUMP */
/* ----------------------------- */
/********************************************************
DISABLE SCREEN DUMP FOR NOW -- Malcolm
	switch (screendump_count)
	{
		case 0:
			n = system (command1);
			screendump_count = screendump_count + 1;
			break;
		case 1:
			n = system (command2);
			screendump_count = screendump_count + 1;
			break;
		case 2:
			n = system (command3);
			screendump_count = screendump_count + 1;
			break;
		case 3:
			n = system (command4);
			screendump_count = screendump_count + 1;
			break;
		case 4:
			n = system (command5);
			screendump_count = screendump_count + 1;
			break;
		case 5:
			n = system (command6);
			screendump_count = screendump_count + 1;
			break;
	}
END OF SCREEN DUMP
 *******************************************************/
	answered = FALSE;
/********************************************************
 * THE EDITOR HANGS HERE
 *******************************************************/
	while (answered == FALSE)
		XtProcessEvent (XtIMAll);
	answered = FALSE;
	XtDestroyWidget (XtParent (popup_icon_menu));
	menu_value = selected_item;
	for (k = 0; k <= 14; ++k)
		free (string[k]);

	return (menu_value);
}

/*
 * ----------------------------------- Retrieve list of next place holders
 * -----------------------------------
 */
static void     retrieve_next_p_h (int *p_h_array, struct node * current_node)
{
	int             j;
	struct append_place_holder *cur_place_ret;

	j = 1;
	if (current_node->append_head != 0)
	{
		cur_place_ret = current_node->append_head;
		while (cur_place_ret != 0)
		{
			p_h_array[j] = cur_place_ret->p_h_type;
			++j;
			cur_place_ret = cur_place_ret->next;
		}
	}
}

/*******************************************************************************
 * FUNCTION:	INCREASE_VERTICAL_MODULES
 *
 *	Increase vertical position of all other modules.
 *	Called by del_node_proc() below, and by the "insert_subtree..., and the
 *	"insert_new_node...", functions in xdesc2.c.
 ******************************************************************************/
void            increase_vertical_modules (int row_diff, int y_diff)
{
	int             i;
	struct node    *tp_tree_pointer;

	for (i = (current_module + 1); i <= number_of_modules; ++i)
	{
		tp_tree_pointer = module_heads[i];
		while (tp_tree_pointer != NULL)
		{
			tp_tree_pointer->origion_y = tp_tree_pointer->origion_y + y_diff;
			tp_tree_pointer->row = tp_tree_pointer->row + row_diff;
			tp_tree_pointer = tp_tree_pointer->next;
		}
	}
}
static void     update_modi_info (struct modi_info * m_i_pointer, int node_p_h)
{
	switch (node_p_h)
	{

			case ref_direct_product:
			m_i_pointer->node_type = reference_node;
			m_i_pointer->ds_method = ref_direct_product;
			break;
		case ref_discriminated_union:
			m_i_pointer->node_type = reference_node;
			m_i_pointer->ds_method = ref_discriminated_union;
			break;
		case ref_sequence_1:
			m_i_pointer->node_type = reference_node;
			m_i_pointer->ds_method = ref_sequence_1;
			break;
		case ref_sequence_2:
			m_i_pointer->node_type = reference_node;
			m_i_pointer->ds_method = ref_sequence_2;
			break;
		case ref_sequence_3:
			m_i_pointer->node_type = reference_node;
			m_i_pointer->ds_method = ref_sequence_3;
			break;
		case mat_direct_product:
			m_i_pointer->node_type = match_node;
			m_i_pointer->ds_method = mat_direct_product;
			break;
		case mat_discriminated_union:
			m_i_pointer->node_type = match_node;
			m_i_pointer->ds_method = mat_discriminated_union;
			break;
		case mat_sequence_1:
			m_i_pointer->node_type = match_node;
			m_i_pointer->ds_method = mat_sequence_1;
			break;
		case mat_sequence_2:
			m_i_pointer->node_type = match_node;
			m_i_pointer->ds_method = mat_sequence_2;
			break;
		case mat_sequence_3:
			m_i_pointer->node_type = match_node;
			m_i_pointer->ds_method = mat_sequence_3;
			break;
	}
}

static void     update_module_info (void)
{
/* ------------- */
/* Starts From 1 */
/* ------------- */
	number_of_modules = number_of_modules + 1;
	module_heads[number_of_modules] = template_tree_pointer;

	if (number_of_modules > 1)
		module_tails[current_module] = current_node;

	current_module = number_of_modules;
}

/*
 * ------------------------------------------------ If place_holder_2 in the
 * definition template is not = 'nulll', then a choice must be made at this
 * point. ------------------------------------------------
 */
static int      look_up (int node_p_h, struct construct * descartes_template, struct modi_info * m_i_pointer)
{
	int             replacement_type;

	update_modi_info (m_i_pointer, node_p_h);
	switch (descartes_template[node_p_h].place_holder_2)
	{
		case nulll:
			replacement_type = descartes_template[node_p_h].place_holder_1;
			break;
		default:
			replacement_type = more_than_one;
			break;
	}

	return (replacement_type);
}

/*
 * ------------------------------------------------ Determine the Descartes
 * construct to replace the current place holder
 * ------------------------------------------------
 */
static int      determine_replace (int inter_node, int column, struct construct * descartes_template, int *next_p_h_array, int *inter_result, struct modi_info * m_i_pointer)
{
	int             result,
	                temp_col;

	temp_col = column;
	result = inter_node;
	*inter_result = result;
	while (result < 21)
	{
		if (descartes_template[result].next_place_holder_1 != nulll)
		{
			if (descartes_template[result].next_place_holder_ind == indent)
			{
				if (next_p_h_array[temp_col] == 0 || next_p_h_array[temp_col] == 1)
					next_p_h_array[temp_col] = indent;
				temp_col = temp_col + 1;
			}
			next_p_h_array[temp_col] = descartes_template[result].next_place_holder_1;
			++temp_col;
			if (descartes_template[result].next_place_holder_2 != nulll)
			{
				next_p_h_array[temp_col] = descartes_template[result].next_place_holder_2;
				++temp_col;
			}
		}
		result = look_up (result, descartes_template, m_i_pointer);
		if (result < 21)
		{
			*inter_result = result;
		}
	}
	if (result == more_than_one)
		return (more_than_one);
	else
		return (result);
}


/*******************************************************************************
 * FUNCTION:	MAKE_NODE_NAME
 *
 *	Attach the appropriate phrase (descartes construct) after the node
 *	name.  Called only from xdesc2.c - consider moving this function
 *	to that file, and making it static.
 ******************************************************************************/
void            make_node_name (char *temp_name, struct modi_info * m_i_pointer)
{
	char            append[5];

	switch (m_i_pointer->ds_method)
	{
		case ref_discriminated_union:
			strcpy (append, "+");
			strcat (temp_name, append);
			break;
		case ref_sequence_1:
			strcpy (append, "*");
			strcat (temp_name, append);
			break;
		case ref_sequence_2:
			strcpy (append, "");
			strcat (temp_name, append);
			break;
		case ref_sequence_3:
			strcpy (append, "*+");
			strcat (temp_name, append);
			break;
		case mat_discriminated_union:
			strcpy (append, "+");
			strcat (temp_name, append);
			break;
		case mat_sequence_1:
			strcpy (append, "*");
			strcat (temp_name, append);
			break;
		case mat_sequence_2:
			strcpy (append, "");
			strcat (temp_name, append);
			break;
		case mat_sequence_3:
			strcpy (append, "*+");
			strcat (temp_name, append);
			break;
	}
}

/*******************************************************************************
 * FUNCTION:	CLEAR_RECT_AREA
 *
 *	clear a rectangular area specified by xleft, xright,ytop and ybottom by
 *	pw_vector line by line in (0) pixel
 ******************************************************************************/
void            clear_rect_area (int xleft, int xright, int ytop, int ybottom)
{
	Widget          w;
	int             x = xleft;

	w = drawing_area;
	while (x <= xright)
	{
		XDrawLine (XtDisplay (w), XtWindow (w), inverseGC, x, ytop, x, ybottom);
		++x;
	}
}

/*******************************************************************************
 * FUNCTION:	INVERSE_RECT_AREA
 *
 *	inverse_video a rectangular area specified by xleft, xright,ytop and
 *	ybottom by pw_vector line by line in (0) pixel
 *
 *	Called from preorder() and check_existing_region().
 *	Called only from functions in xdesc2.c.  Consider moving this function
 *	and making it static.
 ******************************************************************************/
void            inverse_rect_area (int xleft, int xright, int ytop, int ybottom)
{
	int             x = xleft;
	Widget          w;
	GC              tempGC;

	tempGC = theGC;
	w = drawing_area;
	XSetFunction (XtDisplay (w), tempGC, GXinvert);
	while (x <= xright)
	{
		XDrawLine (XtDisplay (w), XtWindow (w), tempGC, x, ytop, x, ybottom);
		++x;
	}
	XSetFunction (XtDisplay (w), tempGC, GXcopy);
}

/*******************************************************************************
 * FUNCTION:	REAL_INVERSE_RECT_AREA
 *
 *	Called from semantic_display() in xdesc3.c
 ******************************************************************************/
void            real_inverse_rect_area (int xleft, int xright, int ytop, int ybottom)
{
	int             x = xleft;
	Widget          w;
	GC              tempGC;

	tempGC = theGC;
	w = drawing_area;
	XSetFunction (XtDisplay (w), tempGC, GXinvert);
	while (x <= xright)
	{
		XDrawLine (XtDisplay (w), XtWindow (w), xorGC, x, ytop, x, ybottom);
		++x;
	}
	XSetFunction (XtDisplay (w), tempGC, GXcopy);
}

/*
 * ------------------------------------------------ Show a small (14 x 22
 * pixcels) dash rectangular to indicate the placeholders
 * ------------------------------------------------
 */
static void     show_region (int origin_x, int origin_y)
{
	int             box_left,
	                box_right,
	                box_top,
	                box_bottom,
	                i;
	int             dash_interval = 2;
	Widget          w;

	w = drawing_area;
	box_left = origin_x;
	box_right = origin_x + 14;
	box_top = origin_y + 2;
	box_bottom = origin_y + 22;

/* draw dashed box */
	for (i = box_left; i < box_right; i = i + (2 * dash_interval))
		XDrawLine (XtDisplay (w), XtWindow (w), theGC, i, box_top, i + 1, box_top);
	for (i = box_top; i < box_bottom; i = i + (2 * dash_interval))
		XDrawLine (XtDisplay (w), XtWindow (w), theGC, box_right, i, box_right, i + 1);
	for (i = box_right; i > box_left; i = i - (2 * dash_interval))
		XDrawLine (XtDisplay (w), XtWindow (w), theGC, i, box_bottom, i - 1, box_bottom);
	for (i = box_bottom; i > box_top; i = i - (2 * dash_interval))
		XDrawLine (XtDisplay (w), XtWindow (w), theGC, box_left, i, box_left, i - 1);
	return;
}

/*
 * ---------------------------- Erase the last row rectangle to indicate no
 * placeholders ----------------------------
 */
static void     no_show_region (int origion_x, int origion_y)
{
	int             xleft,
	                xright,
	                ytop,
	                ybottom;
	Widget          w;

	w = drawing_area;
	xleft = origion_x;
	xright = origion_x + 14;
	ytop = origion_y + 2;
	ybottom = origion_y + 22;

/* draw box */
	XDrawLine (XtDisplay (w), XtWindow (w), inverseGC, xleft, ytop, xright, ytop);
	XDrawLine (XtDisplay (w), XtWindow (w), inverseGC, xright, ytop, xright, ybottom);
	XDrawLine (XtDisplay (w), XtWindow (w), inverseGC, xright, ybottom, xleft, ybottom);
	XDrawLine (XtDisplay (w), XtWindow (w), inverseGC, xleft, ybottom, xleft, ytop);
}

/*******************************************************************************
 * FUNCTION:	ELIMINATE_IND_REGION
 ******************************************************************************/
void            eliminate_ind_region (int *p_h_array)
{
	int             i,
	                end_of_p_h;
	int             x = 0;
	int             y = 1;

	i = 1;
	while (p_h_array[i] != 0)
		++i;
	end_of_p_h = i - 1;
	for (i = 1; i <= end_of_p_h; ++i)
	{
		if (p_h_array[i] == indent)
			no_show_region (region[i][x], region[i][y]);
	}
}


/*
 * ---------------------- clear the region array ----------------------
 */
static void     clear_region (void)
{
	int             i;

	for (i = 0; i < 50; ++i)
	{
		region[i][0] = 0;
		region[i][1] = 0;
	}
}

/*******************************************************************************
 * FUNCTION:	SYNTAX_CHECK
 *
 *	Called by the "one_more_new_node..." functions in xdesc2.c and by
 *	make_region() below.
 ******************************************************************************/
int             syntax_check (struct node * node_to_check)
{
	int             condition = nulll;

	if (*(node_to_check->node_name) == '\'')
		condition = is_literal;
	if (node_to_check->tree_type == analysis_tree && node_to_check->col > 2)
	{
		switch (node_to_check->tree_type)
		{
			case module:
				condition = is_module_call;
				break;
			default:
				break;
		}
	}
	return (condition);
}


/*******************************************************************************
 * FUNCTION:	MAKE_EDGE_REGION
 *
 *	Make connecting edges as mark region
 *	Called by editing_proc() and toggled() below, and by start_rubberband()
 *	in xdesc2.c.
 ******************************************************************************/
void            make_edge_region (struct node * tp_tree_pointer)
{
	struct node    *back_pointer,
	               *edge_head_pointer;
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
	int             x1 = 0;
	int             y1 = 1;
	int             x2 = 2;
	int             y2 = 3;
	int             x3 = 4;
	int             y3 = 5;
	int             x4 = 6;
	int             y4 = 7;
	int             i = 0;
	int             no_of_edges;
	int             threshhold;
	int             y_difference;
	int             insert_condition[50][3];
	int             xright = 2;

/* -------------------------------- */
/* clear breakup_extra_region array */
/* -------------------------------- */
	for (i = 0; i < 50; ++i)
	{
		breakup_extra_region[i][front_empty][x1] = 0;
		breakup_extra_region[i][front_empty][y1] = 0;
		breakup_extra_region[i][front_empty][x2] = 0;
		breakup_extra_region[i][front_empty][y2] = 0;
		breakup_extra_region[i][level_need][x1] = 0;
		breakup_extra_region[i][level_need][y1] = 0;
		breakup_extra_region[i][level_need][x2] = 0;
		breakup_extra_region[i][level_need][y2] = 0;
	}
	for (i = 0; i < 50; ++i)
	{
		breakup_edge_region[i][0][x1] = 0;
		breakup_edge_region[i][0][y1] = 0;
		breakup_edge_region[i][0][x2] = 0;
		breakup_edge_region[i][0][y2] = 0;
		breakup_edge_region[i][1][x1] = 0;
		breakup_edge_region[i][1][y1] = 0;
		breakup_edge_region[i][1][x2] = 0;
		breakup_edge_region[i][1][y2] = 0;
	}
	for (i = 0; i < 50; ++i)
	{
		insert_condition[i][0] = FALSE;
		insert_condition[i][1] = FALSE;
		insert_condition[i][2] = FALSE;
	}
	for (i = 0; i < 50; ++i)
	{
		edge_region[i][x1] = 0;
		edge_region[i][y1] = 0;
		edge_region[i][x2] = 0;
		edge_region[i][y2] = 0;
		edge_region[i][x3] = 0;
		edge_region[i][y3] = 0;
		edge_region[i][x4] = 0;
		edge_region[i][y4] = 0;
	}

	i = 0;
	if (tp_tree_pointer->row == 0)
		tp_tree_pointer = tp_tree_pointer->next;
	while (tp_tree_pointer != 0)
	{
		calculate_string_data (tp_tree_pointer);
		save_xright = str_data.xright;
		save_orig_y = str_data.origion_y;
		if (tp_tree_pointer->row == 1)
		{
			edge_head_pointer = tp_tree_pointer;
			edge_origin_x = str_data.xright;
			edge_origin_y = str_data.origion_y + text_border_margin + str_data.ascent;
		}
		else
		{
			edge_end_x = str_data.xleft;
			edge_end_y = str_data.origion_y + text_border_margin + str_data.ascent;
			back_pointer = tp_tree_pointer;

			while (edge_end_x < edge_origin_x)
			{
				calculate_string_data (back_pointer);
				edge_origin_x = str_data.xright;
				edge_origin_y = str_data.origion_y + str_data.ascent + text_border_margin;
				edge_head_pointer = back_pointer;
				back_pointer = back_pointer->before;
			}
			edge_upper_half_x = edge_origin_x + node_to_node_half_space;
			edge_upper_half_y = edge_origin_y;
			edge_lower_half_x = edge_upper_half_x;
			edge_lower_half_y = edge_end_y;

		/* store edge-region data into data structure */
			insert_mode_block_head[i] = edge_head_pointer;
			insert_mode_block_tail[i] = tp_tree_pointer;
			edge_region[i][x1] = edge_origin_x;
			edge_region[i][y1] = edge_origin_y;
			edge_region[i][x2] = edge_upper_half_x;
			edge_region[i][y2] = edge_upper_half_y;
			edge_region[i][x3] = edge_lower_half_x;
			edge_region[i][y3] = edge_lower_half_y;
			edge_region[i][x4] = edge_end_x;
			edge_region[i][y4] = edge_end_y;
			edge_origin_x = save_xright;
			edge_origin_y = save_orig_y + str_data.ascent + text_border_margin;
			if (tp_tree_pointer->front == 0 && tp_tree_pointer != current_node)
				insert_condition[i][front_empty] = TRUE;
			else
				insert_condition[i][front_empty] = FALSE;
			if (tp_tree_pointer->level == 0 && tp_tree_pointer != current_node && tp_tree_pointer->node_type != literal)
			{
				if (tp_tree_pointer->node_type != reference_node)
				{
					insert_condition[i][level_need] = TRUE;
					insert_condition[i][xright] = edge_origin_x;
				}
				else
				{
					if (tp_tree_pointer->col == 2)
					{
						insert_condition[i][level_need] = TRUE;
						insert_condition[i][xright] = edge_origin_x;
					}
				}
			}
			else
				insert_condition[i][level_need] = FALSE;
			i = i + 1;
		}
		threshhold = node_to_node_space_y + (2 * text_border_margin)
			+ str_data.ascent + str_data.descent;
		no_of_edges = i;
		edge_head_pointer = tp_tree_pointer;
		tp_tree_pointer = tp_tree_pointer->next;
	}
	for (i = 0; i < (no_of_edges); ++i)
	{
		y_difference = edge_region[i][y3] - edge_region[i][y2];
		if (y_difference <= threshhold)
		{
			breakup_edge_region[i][0][x1] = edge_region[i][x2];
			breakup_edge_region[i][0][y1] = edge_region[i][y2] + y_break_clear;
			breakup_edge_region[i][0][x2] = edge_region[i][x3];
			breakup_edge_region[i][0][y2] = edge_region[i][y3] - y_break_clear;

			breakup_edge_region[i][1][x1] = edge_region[i][x3] + x_break_clear;
			breakup_edge_region[i][1][y1] = edge_region[i][y3];
			breakup_edge_region[i][1][x2] = edge_region[i][x4] - x_break_clear;
			breakup_edge_region[i][1][y2] = edge_region[i][y4];
		}
		else
		{
			breakup_edge_region[i][0][x1] = edge_region[i][x2];
			breakup_edge_region[i][0][y1] = edge_region[i][y3] - threshhold + y_break_clear;
			breakup_edge_region[i][0][x2] = edge_region[i][x3];
			breakup_edge_region[i][0][y2] = edge_region[i][y3] - y_break_clear;
			breakup_edge_region[i][1][x1] = edge_region[i][x3] + x_break_clear;
			breakup_edge_region[i][1][y1] = edge_region[i][y3];
			breakup_edge_region[i][1][x2] = edge_region[i][x4] - x_break_clear;
			breakup_edge_region[i][1][y2] = edge_region[i][y4];
		}
		if (insert_condition[i][front_empty] == TRUE)
		{
			breakup_extra_region[i][front_empty][x1] = breakup_edge_region[i][0][x1];
			breakup_extra_region[i][front_empty][y1] = edge_region[i][y3] + x_break_clear;
			breakup_extra_region[i][front_empty][x2] = breakup_edge_region[i][0][x2];
			breakup_extra_region[i][front_empty][y2] = edge_region[i][y3] + 3 * x_break_clear;
		}
		if (insert_condition[i][level_need] == TRUE)
		{
			breakup_extra_region[i][level_need][x1] = insert_condition[i][xright] + x_break_clear;
			breakup_extra_region[i][level_need][y1] = breakup_edge_region[i][1][y1];
			breakup_extra_region[i][level_need][x2] = insert_condition[i][xright] + 3 * x_break_clear;
			breakup_extra_region[i][level_need][y2] = breakup_edge_region[i][1][y2];
		}
	}
}

/*******************************************************************************
 * FUNCTION:	MAKE_REGION
 *
 *	Make block region.
 ******************************************************************************/
void            make_region (struct node * template_tree_pointer, struct node * current_node)
{
	struct node    *node_one_row_up;
	int             origion_y,
	                text_origion_y;
	int             text_ybottom;
	int             node_rect_xright;
	int             node_rect_ybottom;
	int             xright = 2;
	int             ybottom = 3;
	int             condition;
	int             height;

	int             i = 1;
	int             x = 0;
	int             y = 1;
	int             inverse_region[50][2],
	                no_of_p_h,
	                last;
	text_data_ptr   data_ptr;

	data_ptr = &data;
	height = data_ptr->font->ascent + data_ptr->font->descent;
	condition = syntax_check (current_node);
	switch (condition)
	{
		case is_literal:
			origion_y = current_node->origion_y;
			text_origion_y = origion_y + text_border_margin;
			text_ybottom = text_origion_y + height;
			node_rect_ybottom = text_ybottom + text_border_margin;
			break;
		case is_module_call:
			origion_y = current_node->origion_y;
			text_origion_y = origion_y + text_border_margin;
			text_ybottom = text_origion_y + height;
			node_rect_ybottom = text_ybottom + text_border_margin;
			break;
		default:
			calculate_string_data (current_node);
			node_rect_xright = str_data.xright;
			node_rect_ybottom = str_data.ybottom;
			inverse_region[i][x] = node_rect_xright + node_to_node_space;
			inverse_region[i][y] = node_rect_ybottom + node_to_node_space_y;
			++i;
			break;
	}
	while (current_node->col != 0)
	{
		inverse_region[i][x] = current_node->origion_x;
		inverse_region[i][y] = node_rect_ybottom + node_to_node_space_y;
		++i;
		node_one_row_up = current_node->before;
		while (node_one_row_up->col >= current_node->col)
			node_one_row_up = node_one_row_up->before;
		current_node = node_one_row_up;
	}
	clear_region ();
	no_of_p_h = i - 1;
	last = i - 1;
	for (i = 1; i <= no_of_p_h; ++i)
	{
		region[last][x] = inverse_region[i][x];
		region[last][y] = inverse_region[i][y];
		show_region (region[last][x], region[last][y]);
		last = last - 1;
	}
}
/*******************************************************************************
 * FUNCTION	DRAW_A_STRING
 *
 *	This function is not called from anywhere.  Keep it around in case it
 *	comes in handy.
 ******************************************************************************/
static void     draw_a_string (Widget w, caddr_t client_data, XmAnyCallbackStruct * call_data)
{
	int             ll,
	                dir,
	                ascent,
	                desc;
	XCharStruct     char_info;
	char           *test_string = "This is a Test !";
	text_data_ptr   data_ptr;
	int             ytop,
	                xleft,
	                xright,
	                height;

	data_ptr = &data;
	XDrawString (XtDisplay (w), XtWindow (w), theGC, 100, 100, test_string, strlen (test_string));
	ll = strlen (test_string);
	XTextExtents (data_ptr->font, test_string, ll, &dir, &ascent, &desc, &char_info);
	xleft = 100;
	ytop = 100 - data_ptr->font->ascent - data_ptr->font->descent;
	xright = xleft + char_info.width;
	height = data_ptr->font->ascent + data_ptr->font->descent + 5;
	XDrawRectangle (XtDisplay (w), XtWindow (w), theGC, 100, ytop, char_info.width, height);
	make_region (template_tree_pointer, current_node);
	XDrawRectangle (XtDisplay (drawing_area), XtWindow (drawing_area), theGC,
			current_node->origion_x, current_node->origion_y, 40, 10);
	return;
}

static void     handle_expose (Widget w, caddr_t client_data, XmDrawingAreaCallbackStruct * call_data)
{
	display_template_tree (template_tree_pointer);
	make_region (template_tree_pointer, current_node);
	eliminate_ind_region (next_p_h_array);
	return;
}

/*******************************************************************************
 * FUNCTION:	clear_region_marker_display
 ******************************************************************************/
void            clear_region_marker_display (void)
{
	int             xleft,
	                xright,
	                ytop,
	                ybottom,
	                i;
	int             x = 0;
	int             y = 1;

	xleft = region[1][x];
	ytop = region[1][y] + 2;
	i = 1;
	while (region[i][y] != 0)
		++i;
	--i;
	xright = region[i][x] + 14;
	ybottom = region[i][y] + 22;
	clear_rect_area (xleft, xright, ytop, ybottom);

}

/***********************************************************************/
/* The Following codes read in a descartes specification and do parsing */
/***********************************************************************/

static          determine_column (char *buffer)
{
	int             i = 0;
	int             interval,
	                col;

	while (*(buffer + i) == '\t')
		++i;
	interval = i;
	col = interval + 1;
	return (col);
}

static int      determine_node_type (char *buffer)
{
	char            temp_char;
	int             type;

	temp_char = *(buffer);
	if (isupper (temp_char))
		type = reference_node;
	else if (temp_char == '\'')
		type = match_node;
	else
		type = match_node;
	return (type);
}

static int      determine_ds_method (char *buffer, int n)
{
	char            temp_char;
	int             type,
	                i;
	int             is_alpha_numeric;
	int             ref_or_mat;

/* --------------------------------------- */
/* First determine reference or match node */
/* --------------------------------------- */
	is_alpha_numeric = FALSE;
	temp_char = *buffer; /* Initialize in case the following while() loop executes zero times. */
	i = 0;

	while (is_alpha_numeric == FALSE && i <= n)
	{
		temp_char = *(buffer + i);

		if (isalpha (temp_char))
			is_alpha_numeric = TRUE;
		i = i + 1;
	}
	if (islower (temp_char))
		ref_or_mat = match_node;
	else
		ref_or_mat = reference_node;
/* --------------------------------------- */
	temp_char = *(buffer + n);

	switch (ref_or_mat)
	{
		case reference_node:
			type = ref_direct_product;
			if (temp_char == '+')
			{
				if (*(buffer + (n - 1)) == '*')
					type = ref_sequence_3;
				else
					type = ref_discriminated_union;
			}
			if (temp_char == ')')
			{
				if (isalpha (*(buffer + (n - 1))))
					type = ref_direct_product;
				else
					type = ref_sequence_2;
			}
			if (temp_char == '*')
				type = ref_sequence_1;
			break;
		case match_node:
			type = mat_direct_product;
			if (temp_char == '+')
			{
				if (*(buffer + (n - 1)) == '*')
					type = mat_sequence_3;
				else
					type = mat_discriminated_union;
			}
			if (temp_char == ')')
				type = mat_sequence_2;
			if (temp_char == '*')
				type = mat_sequence_1;
			break;
		default:
			type = INT_MAX; /* Return an obviously bogus type. */
	}
	return (type);
}

static int      determine_tree_type (char *buffer, int col, int row)
{
	char            temp_char;
	int             type;
	struct node    *ancester;
	struct node    *back = 0;

	temp_char = *(buffer);
	if (col == 1)
		type = module;
	else if (col == 2)
	{
		if (isupper (temp_char))
			type = analysis_tree;
		else
		{
			type = synthesis_tree;
		}
	}
	else
	{
		ancester = locate_ancester (template_tree_pointer, current_node, ancester, back, row, col);
		type = ancester->tree_type;
	}
	return (type);
}

static int      psudo_selection (int tree_type_t, int node_type_t, int ds_method_t, int *place_holder_array)
{
	int		inter_select;
inter_select = INT_MAX; /* Ensure that a bogus value is returned if it is not handled by some condition below. */

	if (tree_type_t == place_holder_array[1])
		inter_select = 1;
	else if (tree_type_t == place_holder_array[2])
		inter_select = 2;

	if (node_type_t == place_holder_array[1])
		inter_select = 1;
	else if (node_type_t == place_holder_array[2])
		inter_select = 2;
	else if (node_type_t == place_holder_array[3])
		inter_select = 3;

	if (ds_method_t == place_holder_array[1])
		inter_select = 1;
	else if (ds_method_t == place_holder_array[2])
		inter_select = 2;
	else if (ds_method_t == place_holder_array[3])
		inter_select = 3;
	else if (ds_method_t == place_holder_array[4])
		inter_select = 4;
	else if (ds_method_t == place_holder_array[5])
		inter_select = 5;
	else if (ds_method_t == place_holder_array[6])
		inter_select = 6;
	else if (ds_method_t == place_holder_array[7])
		inter_select = 7;
	else if (ds_method_t == place_holder_array[8])
		inter_select = 8;
	else if (ds_method_t == place_holder_array[9])
		inter_select = 9;
	else if (ds_method_t == place_holder_array[10])
		inter_select = 10;

	return (inter_select);
}

static void     toggled (Widget widget, int which, XmToggleButtonCallbackStruct * state)
{
	int             select_button;

	if (state->set)
		select_button = which;
	else
		select_button = 1;

	if (select_button == 1)
		selected_edit_mode = state_append;
	else
		selected_edit_mode = state_insert;

	if (selected_edit_mode == state_insert)
	{
		clear_region_marker_display ();
		make_edge_region (template_tree_pointer);
		show_edge_region (template_tree_pointer);
	}
	else
	{
		make_edge_region (template_tree_pointer);
		no_show_edge_region (template_tree_pointer);
		make_region (template_tree_pointer, current_node);
		eliminate_ind_region (next_p_h_array);

	}
}

static void     check_switch_module (struct node * tp_pointer, int pos_x, int pos_y, XEvent * event_info)
{
	struct node    *check_pointer;
	int             in_region = FALSE;
	int             node_rect_xright;
	int             node_rect_ybottom;
	text_data_ptr   data_ptr;
	Widget          w;
	int             i;

	data_ptr = &data;
	w = drawing_area;


	for (i = 1; i <= number_of_modules; ++i)
	{
		if (in_region == FALSE)
		{
			check_pointer = module_heads[i]->next;
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
				clear_region_marker_display ();

				module_tails[current_module] = current_node;
				current_module = i;
				template_tree_pointer = module_heads[current_module];
				current_node = module_tails[current_module];

				XBell (XtDisplay (drawing_area), 0);
				XBell (XtDisplay (drawing_area), 0);
				XBell (XtDisplay (drawing_area), 0);

				make_region (template_tree_pointer, current_node);
				no_show_region (region[1][0], region[1][1]);
			}
		}
	}
}

/*******************************************************************************
 * FUNCTION:	EDITING_PROC
 *
 *	Guts of the editor.
 *
 *	It is a ButtonPressMask event handler on the global XmDrawingArea
 *	widget drawing_area.  move_proc() in xdesc2.c un-registers, then
 *	re-registers this callback function.
 *
 *	Consider moving this function, along with several functions in xdesc2.c
 *	and xdesc3.c, which are only used by this function, into its own
 *	separate file.
 ******************************************************************************/
void            editing_proc (Widget w, caddr_t client_data, XEvent * event_info)
{
	struct modi_info *modi_info_pointer;
	int             selected_template,
	                place_holder_array[max_place_holder];
	int             selected_p_h,
	                action,
	                inter_select,
	               *inter_result;
	int             event_x_pos,
	                event_y_pos;
	int             node_attribute_array[3];
	int             tree_type = 0;
	int             node_type = 1;
	int             ds_method = 2;
	int             k;


	remove_semantic_listing ();
	event_x_pos = event_info->xbutton.x;
	event_y_pos = event_info->xbutton.y;
	modi_info_pointer = (struct modi_info *) calloc
		(1, sizeof (struct modi_info));
	inter_result = (int *) calloc (1, sizeof (int));
	if (selected_edit_mode == state_append)
	{
		switch (event_info->xbutton.button)
		{
			case Button2:	/* Middle */
				check_existing_region (template_tree_pointer, event_x_pos, event_y_pos, event_info);
				check_switch_module (template_tree_pointer, event_x_pos, event_y_pos, event_info);
			case Button1:	/* Left  */
				clear_int_array (place_holder_array, max_place_holder);
				retrieve_next_p_h (place_holder_array, current_node);
				selected_p_h = check_region (event_x_pos, event_y_pos);
				get_node_attribute (place_holder_array[selected_p_h], node_attribute_array);
				clear_int_array (next_p_h_array, max_place_holder);
				copy_p_h_array (place_holder_array, next_p_h_array);
				if (selected_p_h == FALSE && event_info->type == ButtonPress)
					check_existing_region (template_tree_pointer, event_x_pos, event_y_pos, event_info);
				if (selected_p_h != FALSE && place_holder_array[selected_p_h] != indent)
				{
					clear_region_marker_display ();
					clear_more (next_p_h_array, selected_p_h);
					selected_template = place_holder_array[selected_p_h];
					action = determine_replace (place_holder_array[selected_p_h], selected_p_h,
							descartes_template, next_p_h_array, inter_result, modi_info_pointer);

					while (action == more_than_one)
					{
						clear_int_array (place_holder_array, max_place_holder);
						place_holder_array[1] = descartes_template[selected_template].place_holder_1;
						place_holder_array[2] = descartes_template[selected_template].place_holder_2;
						place_holder_array[3] = descartes_template[selected_template].place_holder_3;
						place_holder_array[4] = descartes_template[selected_template].place_holder_4;
						place_holder_array[5] = descartes_template[selected_template].place_holder_5;
						place_holder_array[6] = descartes_template[selected_template].place_holder_6;
						place_holder_array[7] = descartes_template[selected_template].place_holder_7;
						place_holder_array[8] = descartes_template[selected_template].place_holder_8;
						place_holder_array[9] = descartes_template[selected_template].place_holder_9;
						place_holder_array[10] = descartes_template[selected_template].place_holder_10;

						inter_select = display_next_place_holder (place_holder_array,
										(XButtonPressedEvent *) event_info);
						while (inter_select == 0)
							inter_select = display_next_place_holder (place_holder_array,
											(XButtonPressedEvent *) event_info);
						action = determine_replace (place_holder_array[inter_select], selected_p_h,
										descartes_template, next_p_h_array, inter_result,
										modi_info_pointer);
						selected_template = *inter_result;
						get_node_attribute (selected_template, node_attribute_array);
					}
					one_more_new_node (next_p_h_array, selected_p_h, modi_info_pointer, node_attribute_array);
					display_template_tree (template_tree_pointer);
					make_region (template_tree_pointer, current_node);
					eliminate_ind_region (next_p_h_array);
				}
				break;
		}
	}
	else
	{
		selected_p_h = check_edge_region (event_x_pos, event_y_pos);
		k = selected_p_h;

		if (selected_p_h != FALSE)
		{
			clear_int_array (place_holder_array, max_place_holder);
			retrieve_next_p_h (place_holder_array, insert_mode_block_head[selected_p_h]);
			clear_int_array (next_p_h_array, max_place_holder);
			copy_p_h_array (place_holder_array, next_p_h_array);
			if (selected_p_h != FALSE && place_holder_array[(insert_mode_block_head[selected_p_h]->col) + 1] != indent)
			{
				clear_more (next_p_h_array, (insert_mode_block_head[selected_p_h]->col) + 1);
				selected_template = place_holder_array[(insert_mode_block_head[selected_p_h]->col) + 1];
				action = determine_replace (place_holder_array[(insert_mode_block_head[selected_p_h]->col) + 1],
								(insert_mode_block_head[selected_p_h]->col) + 1,
								 descartes_template, next_p_h_array, inter_result,
								 modi_info_pointer);
				while (action == more_than_one)
				{
					clear_int_array (place_holder_array, max_place_holder);
					place_holder_array[1] = descartes_template[selected_template].place_holder_1;
					place_holder_array[2] = descartes_template[selected_template].place_holder_2;
					place_holder_array[3] = descartes_template[selected_template].place_holder_3;
					place_holder_array[4] = descartes_template[selected_template].place_holder_4;
					place_holder_array[5] = descartes_template[selected_template].place_holder_5;
					place_holder_array[6] = descartes_template[selected_template].place_holder_6;
					place_holder_array[7] = descartes_template[selected_template].place_holder_7;
					place_holder_array[8] = descartes_template[selected_template].place_holder_8;
					place_holder_array[9] = descartes_template[selected_template].place_holder_9;
					place_holder_array[10] = descartes_template[selected_template].place_holder_10;

					inter_select = display_next_place_holder (place_holder_array,
										(XButtonPressedEvent *) event_info);
					while (inter_select == 0)
						inter_select = display_next_place_holder (place_holder_array,
											(XButtonPressedEvent *) event_info);
					action = determine_replace (place_holder_array[inter_select],
										(insert_mode_block_head[selected_p_h]->col) + 1,
							   descartes_template, next_p_h_array, inter_result, modi_info_pointer);
					selected_template = *inter_result;
					get_node_attribute (selected_template, node_attribute_array);
				}
				switch (one_or_two)
				{
					case 0:
						insert_one_more_new_node (next_p_h_array, selected_p_h, modi_info_pointer,
									node_attribute_array, insert_mode_block_head[selected_p_h]);
						break;
					case 1:
						insert_one_more_new_node_with_child (next_p_h_array, selected_p_h,
									modi_info_pointer, node_attribute_array,
									insert_mode_block_head[selected_p_h]);
						break;
					case 2:
						insert_new_node_case_if_empty (next_p_h_array, selected_p_h, modi_info_pointer,
									node_attribute_array, insert_mode_block_head[selected_p_h]);
						break;
					case 3:
						insert_new_node_case_level_need (next_p_h_array, selected_p_h, modi_info_pointer,
									node_attribute_array, insert_mode_block_tail[selected_p_h]);
						break;
				}
				display_template_tree (template_tree_pointer);
				make_edge_region (template_tree_pointer);
				show_edge_region (template_tree_pointer);
			}
		}
	}
	free (modi_info_pointer);
	free (inter_result);
}
static void     parser (Widget w, XtPointer client_data, XmFileSelectionBoxCallbackStruct * cbs)
{
	FILE           *in_file,
	               *fopen (const char *, const char *);
	XmStringCharSet charset = XmSTRING_DEFAULT_CHARSET;
	char            buffer[132];
	int             col,
	                row,
	                i;
	char           *temp_char,
	                temp_length,
	               *temp_node_name_1;
	int             node_type_here;
	int             ds_method_here;
	int             tree_type_here;
	struct modi_info *modi_info_pointer;
	int             selected_template,
	                place_holder_array[max_place_holder];
	int             selected_p_h,
	                action,
	                inter_select,
	               *inter_result;
	int             node_attribute_array[3];
	char           *file_name;
	int             is_new_module;

	modi_info_pointer = (struct modi_info *) calloc
		(1, sizeof (struct modi_info));
	temp_char = (char *) calloc (50, sizeof (char));
	temp_node_name_1 = (char *) calloc (max_node_len, sizeof (char));
	file_name = (char *) calloc (50, sizeof (char));
	inter_result = (int *) calloc (1, sizeof (int));
	strcpy (temp_char, "t");
	row = current_node->row;

	file_name = (char *) calloc (50, sizeof (char));
	XmStringGetLtoR (cbs->value, charset, &file_name);
	in_file = fopen (file_name, "r");
	XtUnmanageChild (file_select_dialog);

	i = -1;
	if (in_file != NULL)
	{
		clear_region_marker_display ();
		temp_char = fgets (buffer, 132, in_file);
		while (temp_char != NULL)
		{
			clear_region_marker_display ();
			temp_length = strlen (buffer) - 1;
			strcpy (buffer + temp_length, "\0");
			if ((strlen (buffer) > 0) && ((*temp_char) != '\0'))
			{
				strcpy (temp_node_name_1, "              ");
				row = row + 1;

			/* ---------------------------- */
			/* Codes to Handle multi module */
			/* ---------------------------- */
				is_new_module = FALSE;
				col = determine_column (buffer);
				if (col == 1 && row != 1)
					is_new_module = TRUE;
			/* ---------------------------- */
				if (is_new_module == TRUE)
				{
					clear_region_marker_display ();
					template_tree_pointer = new_module ();
					update_module_info ();
					current_node = template_tree_pointer;
					make_region (template_tree_pointer, current_node);
					clear_region_marker_display ();
					is_new_module = FALSE;
				}
			/* ---------------------------- */

				strcpy (temp_node_name_1, buffer + ((col - 1)));
				tree_type_here = determine_tree_type (temp_node_name_1, col, row);
				node_type_here = determine_node_type (temp_node_name_1);
				ds_method_here = determine_ds_method (buffer, temp_length - 1);
				clear_int_array (place_holder_array, max_place_holder);
				retrieve_next_p_h (place_holder_array, current_node);
				selected_p_h = col;
				get_node_attribute (place_holder_array[selected_p_h], node_attribute_array);
				clear_int_array (next_p_h_array, max_place_holder);
				copy_p_h_array (place_holder_array, next_p_h_array);
				if (selected_p_h != done)
				{
					clear_more (next_p_h_array, selected_p_h);
					selected_template = place_holder_array[selected_p_h];
					action = determine_replace (place_holder_array[selected_p_h], selected_p_h,
							descartes_template, next_p_h_array, inter_result, modi_info_pointer);
					while (action == more_than_one)
					{
						clear_int_array (place_holder_array, max_place_holder);
						place_holder_array[1] = descartes_template[selected_template].place_holder_1;
						place_holder_array[2] = descartes_template[selected_template].place_holder_2;
						place_holder_array[3] = descartes_template[selected_template].place_holder_3;
						place_holder_array[4] = descartes_template[selected_template].place_holder_4;
						place_holder_array[5] = descartes_template[selected_template].place_holder_5;
						place_holder_array[6] = descartes_template[selected_template].place_holder_6;
						place_holder_array[7] = descartes_template[selected_template].place_holder_7;
						place_holder_array[8] = descartes_template[selected_template].place_holder_8;
						place_holder_array[9] = descartes_template[selected_template].place_holder_9;
						place_holder_array[10] = descartes_template[selected_template].place_holder_10;

						inter_select = psudo_selection (tree_type_here, node_type_here, ds_method_here,
											place_holder_array);
						action = determine_replace (place_holder_array[inter_select], selected_p_h,
										descartes_template, next_p_h_array, inter_result,
										modi_info_pointer);
						selected_template = *inter_result;
						get_node_attribute (selected_template, node_attribute_array);
					}
					one_more_new_node_read_in (next_p_h_array, selected_p_h, modi_info_pointer,
										node_attribute_array, temp_node_name_1);
					display_template_tree (template_tree_pointer);
					make_region (template_tree_pointer, current_node);
					eliminate_ind_region (next_p_h_array);
					strcpy (temp_char, "");
					temp_char = fgets (buffer, 132, in_file);
				}
			}
		}
	}
	fclose (in_file);
	free (modi_info_pointer);
	free (temp_char);
	free (temp_node_name_1);
	free (inter_result);
	make_region (template_tree_pointer, current_node);
	eliminate_ind_region (next_p_h_array);
	display_template_tree_debug (template_tree_pointer);
	debugger (template_tree_pointer);
}

/*******************************************************************************
 * FUNCTION:	DEL_NODE_PROC
 *
 *	XmNactivateCallback function for XmPushButton widget pb1 ("DELETE")
 *	in main().  This function is also called directly, by end_rubberband()
 *	in xdesc2.c.
 ******************************************************************************/
void            del_node_proc (Widget w, caddr_t client_data, XmAnyCallbackStruct * cbs)
{
	struct node    *replace_ptr,
	               *temp_ptr,
	               *tail_ptr;
	int             x_diff,
	                y_diff,
	                old_y,
	                old_row,
	                row_diff,
	                single_distance;
	int             height,
	                increased_distance;
	text_data_ptr   data_ptr;


/* ----------------------- */
/* deletion of SINGLE node */
/* ----------------------- */
	if (block_head != 0 && block_tail == 0)
	{
		switch (block_head->tree_type)
		{
			case module:
				break;
			default:
				if (block_head->col == 2)
				{
				}
				else
				{
					calculate_string_data (block_head);
					clear_rect_area (str_data.origion_x + 1, str_data.xright - 1,
								str_data.ytop + 1, str_data.ybottom - 1);
					erase_template_tree (template_tree_pointer);
					clear_region_marker_display ();
					if (block_head->level != 0)
					{
						replace_ptr = block_head->level;
						tail_ptr = preorder_locate_last_desc (block_head->level);
						temp_ptr = tail_ptr->next;
						y_diff = tail_ptr->origion_y;
						row_diff = tail_ptr->row;
						while (temp_ptr != 0)
						{
							old_y = temp_ptr->origion_y;
							old_row = temp_ptr->row;
							temp_ptr->origion_y = y_diff;
							temp_ptr->row = row_diff;
							y_diff = old_y;
							row_diff = old_row;
							temp_ptr = temp_ptr->next;
						}
						temp_ptr = replace_ptr;
						preorder_decrease_col_and_row (replace_ptr, 1, 1);
						x_diff = replace_ptr->origion_x - block_head->origion_x;
						y_diff = replace_ptr->origion_y - block_head->origion_y;
						temp_ptr = replace_ptr;
						preorder_decrease_x_and_y (replace_ptr, x_diff, y_diff);
						if (block_head->ancester->level == block_head)
							block_head->ancester->level = replace_ptr;
						replace_ptr->ancester = block_head->ancester;
						if (block_head->front != 0)
						{
							block_head->front->back = replace_ptr;
							replace_ptr->front = block_head->front;
						}
						if (block_head->back != 0)
						{
							block_head->back->front = replace_ptr;
							replace_ptr->back = block_head->back;
						}
						else
							replace_ptr->back = NULL;
						block_head->before->next = replace_ptr;
						replace_ptr->before = block_head->before;
						temp_ptr = replace_ptr->front;
						while (temp_ptr != NULL)
						{
							temp_ptr->ancester = replace_ptr->ancester;
							temp_ptr = temp_ptr->front;
						}
						temp_ptr = replace_ptr->back;
						while (temp_ptr != NULL)
						{
							temp_ptr->ancester = replace_ptr->ancester;
							temp_ptr = temp_ptr->back;
						}
					}
					else
					{
						if (block_head->front != 0)
						{
							replace_ptr = block_head->front;
							if (block_head->ancester->level == block_head)
								block_head->ancester->level = replace_ptr;
							replace_ptr->ancester = block_head->ancester;
							if (block_head->back != 0)
							{
								block_head->back->front = replace_ptr;
								replace_ptr->back = block_head->back;
							}
							else
								replace_ptr->back = NULL;
							block_head->before->next = replace_ptr;
							replace_ptr->before = block_head->before;
							y_diff = block_head->origion_y;
							row_diff = block_head->row;
							while (replace_ptr != 0)
							{
								old_y = replace_ptr->origion_y;
								old_row = replace_ptr->row;
								replace_ptr->origion_y = y_diff;
								replace_ptr->row = row_diff;
								y_diff = old_y;
								row_diff = old_row;
								replace_ptr = replace_ptr->next;
							}
						}
						else
						{
							if (block_head->ancester->level == block_head)
								block_head->ancester->level = 0;
							if (block_head->back != 0)
								block_head->back->front = 0;

							if (block_head->next == 0)
							{
								block_head->before->next = 0;
								current_node = block_head->before;
							}
							else
							{
								block_head->before->next = block_head->next;
								block_head->next->before = block_head->before;
								y_diff = block_head->origion_y;
								row_diff = block_head->row;
								temp_ptr = block_head->next;
								while (temp_ptr != 0)
								{
									old_y = temp_ptr->origion_y;
									old_row = temp_ptr->row;
									temp_ptr->origion_y = y_diff;
									temp_ptr->row = row_diff;
									y_diff = old_y;
									row_diff = old_row;
									temp_ptr = temp_ptr->next;
								}
							}
						}
					}
				/* ------------------------ */
				/* multi_modules processing */
				/* ------------------------ */
					data_ptr = &data;
					height = data_ptr->font->ascent + data_ptr->font->descent;
					increased_distance = (-1 * (2 * text_border_margin + height + node_to_node_space_y));
					increase_vertical_modules (-1, increased_distance);

				}
				break;
		}
		block_head->ancester = NULL;
		block_head->level = NULL;
		block_head->front = NULL;
		block_head->back = NULL;
		block_head->next = NULL;
		block_head->before = NULL;

		block_head = 0;

		display_template_tree (template_tree_pointer);
		make_region (template_tree_pointer, current_node);
		eliminate_ind_region (next_p_h_array);
	}
/* ------------------- */
/* deletion of SUBTREE */
/* ------------------- */
	else
	{
		if (block_head != 0 && block_tail != 0)
		{
			if (block_head->front != 0)
			{
				calculate_string_data (block_head);
				single_distance = (str_data.ybottom - str_data.ytop) + node_to_node_space_y;
				row_diff = (block_tail->row - block_head->row) + 1;
				clear_rect_area (str_data.origion_x + 1, str_data.xright - 1,
							str_data.ytop + 1, str_data.ybottom - 1);
				clear_subtree (block_head->level);
				erase_template_tree (block_head);
				clear_region_marker_display ();
				replace_ptr = block_head->front;
				if (block_head->ancester->level == block_head)
					block_head->ancester->level = replace_ptr;
				replace_ptr->ancester = block_head->ancester;
				if (block_head->back != 0)
				{
					block_head->back->front = replace_ptr;
					replace_ptr->back = block_head->back;
				}
				else
					replace_ptr->back = NULL;
				block_head->before->next = replace_ptr;
				replace_ptr->before = block_head->before;
				while (replace_ptr != 0)
				{
					replace_ptr->row = replace_ptr->row - row_diff;
					replace_ptr->origion_y = replace_ptr->origion_y - (row_diff * single_distance);
					replace_ptr = replace_ptr->next;
				}
			}
			else
			{
			/* --------------------------- */
			/* BLOCK_HEAD -> FRONT == NULL */
			/* --------------------------- */

				calculate_string_data (block_head);
				single_distance = (str_data.ybottom - str_data.ytop) + node_to_node_space_y;
				row_diff = (block_tail->row - block_head->row) + 1;
				clear_rect_area (str_data.origion_x + 1, str_data.xright - 1,
							str_data.ytop + 1, str_data.ybottom - 1);
				clear_subtree (block_head->level);
				erase_template_tree (block_head);
				clear_region_marker_display ();
				if (block_tail->next != 0)
				{
					replace_ptr = block_tail->next;
					if (block_head->back != 0)
						block_head->back->front = NULL;
					if (block_head->ancester->level == block_head)
						block_head->ancester->level = 0;
					block_head->before->next = replace_ptr;
					replace_ptr->before = block_head->before;
					while (replace_ptr != 0)
					{
						replace_ptr->row = replace_ptr->row - row_diff;
						replace_ptr->origion_y = replace_ptr->origion_y - (row_diff * single_distance);
						replace_ptr = replace_ptr->next;
					}
				}
				else
				{
					if (block_head->ancester->level == block_head)
						block_head->ancester->level = 0;
					block_head->before->next = 0;
					if (block_head->back != 0)
						block_head->back->front = 0;
					current_node = block_head->before;

				/*
				 * if the sub-tree is the last tree in the
				 * module
				 */
				}
			}
		/* ------------------------ */
		/* multi_modules processing */
		/* ------------------------ */
			increase_vertical_modules ((-1 * row_diff), (-1 * row_diff * single_distance));

			display_template_tree (template_tree_pointer);

		}

		if (block_head != NULL)
		{
			block_head->before = NULL;
			block_head->back = NULL;
			block_head->ancester = NULL;
			block_head->front = NULL;
			block_head = NULL;
		}
		if (block_tail != NULL)
		{
			block_tail->next = NULL;
			block_tail->front = NULL;
			block_tail->level = NULL;
			block_tail = NULL;
		}

		make_region (template_tree_pointer, current_node);
		eliminate_ind_region (next_p_h_array);
	}
	display_template_tree_debug (template_tree_pointer);
	debugger (template_tree_pointer);
	if (current_module < number_of_modules)
	{
		display_template_tree_debug (module_heads[current_module + 1]);
		debugger (module_heads[current_module + 1]);
	}
}


static void     save_action (Widget w, XtPointer client_data, XmFileSelectionBoxCallbackStruct * cbs)
{

	FILE           *out_file,
	               *fopen (const char *, const char *);
	XmStringCharSet charset = XmSTRING_DEFAULT_CHARSET;
	struct node    *tp_tree_pointer;
	int             i;
	char           *file_name;

	file_name = (char *) calloc (50, sizeof (char));
	XmStringGetLtoR (cbs->value, charset, &file_name);
	XtUnmanageChild (file_select_dialog);
	out_file = fopen (file_name, "w");
	if (out_file != NULL)
	{
		tp_tree_pointer = template_tree_pointer;
		if (tp_tree_pointer->row == 0)
			tp_tree_pointer = tp_tree_pointer->next;
		while (tp_tree_pointer != 0)
		{
			for (i = 0; i < (tp_tree_pointer->col - 1); ++i)
				fprintf (out_file, "\t");
			fprintf (out_file, "%s\n", tp_tree_pointer->node_name);
			tp_tree_pointer = tp_tree_pointer->next;
		}
	}
	fclose (out_file);
	free (file_name);
	XtRemoveCallback (file_select_dialog, XmNokCallback, (XtCallbackProc) save_action, NULL);
	XtAddCallback (file_select_dialog, XmNokCallback, (XtCallbackProc) parser, NULL);
}


static void     save_file_select (Widget w, caddr_t client_data, XmAnyCallbackStruct * call_data)
{

	XtRemoveCallback (file_select_dialog, XmNokCallback, (XtCallbackProc) parser, NULL);
	XtAddCallback (file_select_dialog, XmNokCallback, (XtCallbackProc) save_action, NULL);

	XtManageChild (file_select_dialog);
}

/* ------------------------------------ */
/* Handles the addition of a new module */
/* ------------------------------------ */
static void     add_module (Widget w, caddr_t client_data, XmAnyCallbackStruct * call_data)
{
	if (number_of_modules >= 1)
	{
		clear_region_marker_display ();
		template_tree_pointer = new_module ();
		update_module_info ();
		current_node = template_tree_pointer;
		make_region (template_tree_pointer, current_node);
	}
}

int             main (int argc, char **argv)
{
	Widget          text_area_shell;
	Widget          menu1,
	                menu2,
	                entry1,
	                entry2,
	                entry3,
	                entry4,
	                entry5;
	Widget          menu_bar,
	                mbar_cbutton1;
	Widget          mbar_cbutton2;
	Widget          paned_window,
	                control_area_shell;
	Cardinal        narg;
	Arg             args[10];
	XGCValues       xgcv;
	int             fg,
	                bg,
	                tile_fg,
	                tile_bg,
	                tile_fg2,
	                tile_bg2;
	Widget          frame;
	XFontStruct    *font;
	XmFontList      fontlist;
	Widget          pb1,
	                pb2,
/*	                pb3, */
	                pb4,
	                pb5,
	                pb6;
	Widget          radio_box;
	Widget          insert_mode_toggle;
	Widget          append_mode_toggle;
	int             test_width,
	                test_height,
	                i;
	Dimension       main_window_height,
	                main_window_width;
	Window          test_window;
	Widget          entry2_2;


	create_descartes_definition (descartes_template);
/* ---------------- */
/* Initiate Modules */
/* ---------------- */
	for (i = 0; i <= 29; ++i)
		module_heads[i] = NULL;
	number_of_modules = 0;
/* ---------------- */

	template_tree_pointer = new_module ();
	update_module_info ();
	current_node = template_tree_pointer;

/* ---------------------------------------------- */
/* Create the top level shell for the application */
/* ---------------------------------------------- */
/* top_level = XtInitialize(argv[0], "XVedit", NULL, 0, &argc,argv); */
	top_level = XtInitialize (argv[0], "Xdesc", NULL, 0, &argc, argv);

	narg = 0;
	XtSetArg (args[narg], XmNtitle, argv[0]);
	++narg;
	XtSetValues (top_level, args, narg);

	narg = 0;
	XtSetArg (args[narg], XmNtitle, "Descartes Visual Editor");
	narg++;
	XtSetValues (top_level, args, narg);
/*
 * Create the pixmaps for use as tiles in widgets.
 * Also create a fontlist 
 */
	narg = 0;
	XtSetArg (args[narg], XmNforeground, &tile_fg);
	narg++;
	XtSetArg (args[narg], XmNbackground, &tile_bg);
	narg++;
	XtGetValues (top_level, args, narg);
	pmap_25 = XmGetPixmap (XtScreen (top_level), "25_foreground", tile_fg, tile_bg);
	pmap_50 = XmGetPixmap (XtScreen (top_level), "50_foreground", tile_fg, tile_bg);
	pmap_75 = XmGetPixmap (XtScreen (top_level), "75_foreground", tile_fg, tile_bg);

	font = XLoadQueryFont (XtDisplay (top_level), "-adobe-helvetica-bold-r-*-*-14-*-75-75-p-82-iso8859-*");

	fontlist = XmFontListCreate (font, "charset1");
/* -------------------------------------------- */
/* Create paned widget as the top manager shell */
/* -------------------------------------------- */
	paned_window = XtVaCreateWidget ("Paned", xmRowColumnWidgetClass, top_level,
					 XmNbackgroundPixmap, pmap_50,

/*
 * XmNsashHeight, 0, XmNsashWidth, 0, XmNseparatorOn, False,
 */
					 XmNorientation, XmVERTICAL,
					 XmNspacing, 2,
					 NULL);
/* ------------------------------ */
/* Create and manage the menu_bar */
/* ------------------------------ */
	narg = 0;
	XtSetArg (args[narg], XmNbackgroundPixmap, pmap_50);
	narg++;
	menu_bar = XmCreateMenuBar (paned_window, "MenuBar", args, narg);
	XtManageChild (menu_bar);

/* -------------------------------------------- */
/* Create the pull_down_menu under the menu_bar */
/* -------------------------------------------- */
	narg = 0;
	XtSetArg (args[narg], XmNdefaultFontList, fontlist);
	narg++;
	XtSetArg (args[narg], XmNbackgroundPixmap, pmap_50);
	narg++;
	XtSetArg (args[narg], XmNhighlightThickness, 0);
	narg++;
	menu1 = XmCreatePulldownMenu (menu_bar, "File", args, narg);
	narg = 0;
	XtSetArg (args[narg], XmNdefaultFontList, fontlist);
	narg++;
	XtSetArg (args[narg], XmNbackgroundPixmap, pmap_50);
	narg++;
	XtSetArg (args[narg], XmNhighlightThickness, 0);
	narg++;
	menu2 = XmCreatePulldownMenu (menu_bar, "View", args, narg);

/* ------------------------------------------------------- */
/* create pushbutton widgets as the entries of the menubar */
/* ------------------------------------------------------- */
	narg = 0;
	XtSetArg (args[narg], XmNfontList, fontlist);
	narg++;
	entry1 = XmCreatePushButton (menu1, "Open", args, narg);
	XtAddCallback (entry1, XmNactivateCallback, (XtCallbackProc) start_open, NULL);
	XtManageChild (entry1);
	narg = 0;
	XtSetArg (args[narg], XmNfontList, fontlist);
	narg++;
	entry2 = XmCreatePushButton (menu1, "Close", args, narg);
	XtAddCallback (entry2, XmNactivateCallback, (XtCallbackProc) close_proc, NULL);
	XtManageChild (entry2);
	narg = 0;
	XtSetArg (args[narg], XmNfontList, fontlist);
	narg++;
	entry3 = XmCreatePushButton (menu1, "Save", args, narg);
	XtAddCallback (entry3, XmNactivateCallback, (XtCallbackProc) save_file_select, NULL);
	XtManageChild (entry3);
	narg = 0;
	XtSetArg (args[narg], XmNfontList, fontlist);
	narg++;
	entry4 = XmCreatePushButton (menu1, "Exit", args, narg);
	XtAddCallback (entry4, XmNactivateCallback, (XtCallbackProc) exit_action, NULL);
	XtManageChild (entry4);
	narg = 0;
	XtSetArg (args[narg], XmNfontList, fontlist);
	narg++;
	entry5 = XmCreatePushButton (menu1, "New Module", args, narg);
	XtAddCallback (entry5, XmNactivateCallback, (XtCallbackProc) add_module, NULL);
	XtManageChild (entry5);

	narg = 0;
	XtSetArg (args[narg], XmNfontList, fontlist);
	narg++;
	entry2_2 = XmCreatePushButton (menu2, "Semantic Analysis", args, narg);
	XtAddCallback (entry2_2, XmNactivateCallback, (XtCallbackProc) semantic_analysis, NULL);
	XtManageChild (entry2_2);


/* -------------------------------------------------------------- */
/* manage the menubar as its entries has been created and managed */
/* -------------------------------------------------------------- */
	XtManageChild (menu1);
	XtManageChild (menu2);

	narg = 0;
	XtSetArg (args[narg], XmNbackgroundPixmap, pmap_50);
	narg++;
	XtSetArg (args[narg], XmNsubMenuId, menu1);
	narg++;
	XtSetArg (args[narg], XmNfontList, fontlist);
	narg++;
	mbar_cbutton1 = XmCreateCascadeButton (menu_bar, "File", args, narg);
	XtManageChild (mbar_cbutton1);
	narg = 0;
	XtSetArg (args[narg], XmNbackgroundPixmap, pmap_50);
	narg++;
	XtSetArg (args[narg], XmNfontList, fontlist);
	narg++;
	XtSetArg (args[narg], XmNsubMenuId, menu2);
	narg++;
	mbar_cbutton2 = XmCreateCascadeButton (menu_bar, "View", args, narg);
	XtManageChild (mbar_cbutton2);

/* ---------------------------------------------- */
/* Create a manager for the node name key-in area */
/* ---------------------------------------------- */
	text_area_shell = XtVaCreateWidget ("Textareashell", xmRowColumnWidgetClass,
					    paned_window,
					    XmNbackgroundPixmap, pmap_50,
					    XmNorientation, XmHORIZONTAL,
					    XmNpacking, XmPACK_TIGHT,
					    XmNspacing, 6,
					    XmNnumColumns, 1,
					    XmNmarginHeight, 0,
					    XmNmarginWidth, 0,
					    NULL);

/* -------------------------------------------- */
/* Create a label for the node name key-in area */
/* -------------------------------------------- */
	XtVaCreateManagedWidget ("Node-Name :", xmLabelGadgetClass, text_area_shell,
				 XmNfontList, fontlist,
				 NULL);

/* ----------------------------------------------- */
/* Create a text field for accepting the node name */
/* ----------------------------------------------- */
	text_area = XtVaCreateManagedWidget ("Textarea", xmTextFieldWidgetClass,
					     text_area_shell,
					     XmNvalue, " Empty node name ... ",
					     XmNcolumns, 40,
					     XmNtopShadowPixmap, pmap_75,
					     XmNhighlightThickness, 0,
					     XmNshadowThickness, 2,
					     NULL);
	XtAddCallback (text_area, XmNactivateCallback, (XtCallbackProc) draw_text, NULL);

	frame = XtVaCreateManagedWidget ("frame1", xmFrameWidgetClass, text_area_shell,
					 XmNshadowType, XmSHADOW_IN,
					 NULL);
/* --------------------- */
/* create the radion box */
/* --------------------- */
	narg = 0;
	XtSetArg (args[narg], XmNradioAlwaysOne, True);
	narg++;
	XtSetArg (args[narg], XmNbackgroundPixmap, pmap_50);
	narg++;
	XtSetArg (args[narg], XmNorientation, XmHORIZONTAL);
	narg++;
	radio_box = XmCreateRadioBox (frame, "radio_box", args, narg);
	append_mode_toggle = XtVaCreateManagedWidget ("Append",
						      xmToggleButtonGadgetClass, radio_box,
						      XmNhighlightThickness, 0,
						      XmNfontList, fontlist, NULL);
	XtAddCallback (append_mode_toggle, XmNvalueChangedCallback, (XtCallbackProc) toggled, (XtPointer) 1);
	insert_mode_toggle = XtVaCreateManagedWidget ("Insert",
						      xmToggleButtonGadgetClass, radio_box,
						      XmNhighlightThickness, 0,
						      XmNfontList, fontlist, NULL);
	XtAddCallback (insert_mode_toggle, XmNvalueChangedCallback, (XtCallbackProc) toggled, (XtPointer) 2);
	XtManageChild (radio_box);
/* -------------------------------------------------- */
/* Node name key-in area completed : manage the shell */
/* -------------------------------------------------- */
	XtManageChild (text_area_shell);

/* -------------------------------------------------- */
/* Create the main working area as the second child of */
/* the paned_window 				  */
/* -------------------------------------------------- */
	narg = 0;
	XtSetArg (args[narg], XmNwidth, 500);
	narg++;
	XtSetArg (args[narg], XmNheight, 500);
	narg++;
	XtSetArg (args[narg], XmNbackgroundPixmap, pmap_50);
	narg++;
	XtSetArg (args[narg], XmNshadowThickness, 2);
	narg++;
	XtSetArg (args[narg], XmNscrollingPolicy, XmAUTOMATIC);
	narg++;
	XtSetArg (args[narg], XmNscrollBarPlacement, XmBOTTOM_RIGHT);
	narg++;
	XtSetArg (args[narg], XmNscrollBarDisplayPolicy, XmSTATIC);
	narg++;
	XtSetArg (args[narg], XmNvisualPolicy, XmCONSTANT);
	narg++;
	main_shell = XmCreateMainWindow (paned_window, "Main", args, narg);
/* ----------------------- */
/* Create the drawing area */
/* ----------------------- */
	narg = 0;
	XtSetArg (args[narg], XmNresizePolicy, XmRESIZE_ANY);
	narg++;
	XtSetArg (args[narg], XmNwidth, 4000);
	narg++;
	XtSetArg (args[narg], XmNheight, 4000);
	narg++;
	drawing_area = XmCreateDrawingArea (main_shell,
					    "Drawing_area", args, narg);
	XtAddEventHandler (drawing_area, ButtonPressMask, False, (XtEventHandler) editing_proc, NULL);
	XtAddCallback (drawing_area, XmNexposeCallback, (XtCallbackProc) handle_expose, &drawing_area);
	XtManageChild (drawing_area);
	XtVaGetValues (drawing_area, XmNwidth, &test_width, XmNheight, &test_height);

/* --------------------------------------------------------------------- */
/* Manage the main_shell as the menubar and drawing area is been managed */
/* --------------------------------------------------------------------- */

/*
 * NOTE: I deleted the extraneous 7th parameter that was passed to
 * XmMainWindowSetAreas() in the original code below.  (The value passed was
 * "NULL".)
 */
	XmMainWindowSetAreas (main_shell, menu_bar, NULL, NULL, NULL,
			      drawing_area);
	XtManageChild (main_shell);
/* ------------------------ */
/* Create the control panel */
/* ------------------------ */
	control_area_shell = XtVaCreateWidget (
					       "Controlareashell", xmRowColumnWidgetClass,
					       paned_window,
					       XmNbackgroundPixmap, pmap_50,
					       XmNorientation, XmHORIZONTAL,
					       XmNspacing, 8,
					       XmNisAligned, True,
					       XmNresizeHeight, True,
					       XmNresizeWidth, True,
					       XmNpacking, XmPACK_COLUMN,
					       XmNentryAlignment, XmALIGNMENT_CENTER,
					       NULL);

/* --------------------------- */
/* Create a file selection box */
/* --------------------------- */
	narg = 0;
	XtSetArg (args[narg], XmNx, 10);
	narg++;
	XtSetArg (args[narg], XmNy, 10);
	narg++;
	file_select_dialog = XmCreateFileSelectionDialog (drawing_area, "filesb", args, narg);
	XtAddCallback (file_select_dialog, XmNcancelCallback, (XtCallbackProc) cancel_file_select, NULL);
	XtAddCallback (file_select_dialog, XmNokCallback, (XtCallbackProc) parser, NULL);

/* -------------------------------------------------------- */
/* Create the pushbuttons to be placed in the control panel */
/* -------------------------------------------------------- */
	pb1 = XtVaCreateManagedWidget ("DELETE", xmPushButtonWidgetClass, control_area_shell,
				       XmNborderWidth, 0,
				       XmNtopShadowPixmap, pmap_50,
				       XmNfontList, fontlist,
				       XmNhighlightThickness, 0,
				       XmNfillOnArm, False,
				       NULL);
	XtAddCallback (pb1, XmNactivateCallback, (XtCallbackProc) del_node_proc, NULL);
	pb2 = XtVaCreateManagedWidget ("MOVE", xmPushButtonWidgetClass, control_area_shell,
				       XmNborderWidth, 0,
				       XmNtopShadowPixmap, pmap_50,
				       XmNfontList, fontlist,
				       XmNhighlightThickness, 0,
				       XmNfillOnArm, False,
				       NULL);
	XtAddCallback (pb2, XmNactivateCallback, (XtCallbackProc) move_proc, NULL);

/*
 * pb3=XtVaCreateManagedWidget("COPY",xmPushButtonWidgetClass,
 * control_area_shell, XmNborderWidth, 0, XmNalignment, XmALIGNMENT_CENTER,
 * XmNhighlightThickness, 0, XmNfontList, fontlist, XmNfillOnArm, False,
 * NULL);
 */
	pb4 = XtVaCreateManagedWidget ("NODE NAME", xmPushButtonWidgetClass, control_area_shell,
				       XmNborderWidth, 0,
				       XmNfillOnArm, False,
				       XmNtopShadowPixmap, pmap_50,
				       XmNfontList, fontlist,
				       XmNhighlightThickness, 0,
				       NULL);
	XtAddCallback (pb4, XmNactivateCallback, (XtCallbackProc) mod_name_proc, NULL);
	pb5 = XtVaCreateManagedWidget ("D-S METHOD", xmPushButtonWidgetClass, control_area_shell,
				       XmNborderWidth, 0,
				       XmNhighlightThickness, 0,
				       XmNfillOnArm, False,
				       XmNfontList, fontlist,
				       NULL);
	XtAddCallback (pb5, XmNactivateCallback, (XtCallbackProc) mod_ds_method_proc, NULL);
	pb6 = XtVaCreateManagedWidget ("NODE-TYPE", xmPushButtonWidgetClass, control_area_shell,
				       XmNborderWidth, 0,
				       XmNhighlightThickness, 0,
				       XmNtopShadowPixmap, pmap_50,
				       XmNfontList, fontlist,
				       XmNfillOnArm, False,
				       NULL);
	XtManageChild (control_area_shell);

/* ---------------------------------------- */
/* Create the SEMANTIC ERROR control window */
/* ---------------------------------------- */
	narg = 0;
	XtSetArg (args[narg], XmNvisibleItemCount, 5);
	narg++;
	XtSetArg (args[narg], XmNselectionPolicy, XmSINGLE_SELECT);
	narg++;
	XtSetArg (args[narg], XmNfontList, fontlist);
	narg++;
	semantic_list = XmCreateScrolledList (paned_window, "Semantic_Errors", args, narg);
	XtAddCallback (semantic_list, XmNdefaultActionCallback, (XtCallbackProc) semantic_display, NULL);
	XtManageChild (semantic_list);

	XtManageChild (paned_window);
/* --------------------------------------------------------------------- */
/* Create the GC. First retrieve the backgound and foreground color from */
/* the widget's resource                                                 */
/* --------------------------------------------------------------------- */
	narg = 0;
	XtSetArg (args[narg], XmNforeground, &fg);
	narg++;
	XtSetArg (args[narg], XmNbackground, &bg);
	narg++;
	XtGetValues (drawing_area, args, narg);

/* --------------------------------------------- */
/* Define a GC and a inverse GC with these color */
/* --------------------------------------------- */
	xgcv.foreground = fg;
	xgcv.background = bg;
	theGC = XtGetGC (drawing_area, GCForeground | GCBackground, &xgcv);
/* ---------------------------------- */
/* Set up a GC with exclusive-OR mode */
/* (for rubber-band drawing)	  */
/* ---------------------------------- */
	xgcv.foreground = fg ^ bg;
	xgcv.background = bg;
	xgcv.function = GXxor;
	xorGC = XtGetGC (drawing_area, GCForeground | GCBackground | GCFunction, &xgcv);

	xgcv.foreground = bg;
	xgcv.background = bg;
	inverseGC = XtGetGC (drawing_area, GCForeground | GCBackground, &xgcv);

	XtRealizeWidget (top_level);
	XtGetApplicationResources (top_level, &data, resources, XtNumber (resources), NULL, 0);
	narg = 0;
	XtSetArg (args[narg], XmNforeground, &tile_fg2);
	narg++;
	XtSetArg (args[narg], XmNbackground, &tile_bg2);
	narg++;
	XtGetValues (drawing_area, args, narg);
	pmap_bg = XmGetPixmap (XtScreen (drawing_area), "background", tile_fg2, tile_bg2);
	narg = 0;
	XtSetArg (args[narg], XmNtopShadowPixmap, pmap_bg);
	narg++;
	XtSetValues (frame, args, narg);
	narg = 0;
	XtSetArg (args[narg], XmNtopShadowPixmap, pmap_bg);
	narg++;
	XtSetValues (menu_bar, args, narg);
	narg = 0;
	XtSetArg (args[narg], XmNtopShadowPixmap, pmap_bg);
	narg++;
	XtSetValues (text_area, args, narg);
/* --------------------------- */
/* start creating icon pixmaps */
/* --------------------------- */

	pix_a_tree = XmGetPixmap (XtScreen (drawing_area), "a_tree.icon", fg, bg);
	pix_s_tree = XmGetPixmap (XtScreen (drawing_area), "s_tree.icon", fg, bg);
	pix_ref_dp = XmGetPixmap (XtScreen (drawing_area), "dp_ref.icon", fg, bg);
	pix_ref_du = XmGetPixmap (XtScreen (drawing_area), "du_ref.icon", fg, bg);
	pix_ref_sq1 = XmGetPixmap (XtScreen (drawing_area), "seq1_ref.icon", fg, bg);
	pix_ref_sq2 = XmGetPixmap (XtScreen (drawing_area), "seq2_ref.icon", fg, bg);
	pix_ref_sq3 = XmGetPixmap (XtScreen (drawing_area), "seq3_ref.icon", fg, bg);
	pix_mat_dp = XmGetPixmap (XtScreen (drawing_area), "dp_mat.icon", fg, bg);
	pix_mat_du = XmGetPixmap (XtScreen (drawing_area), "du_mat.icon", fg, bg);
	pix_mat_sq1 = XmGetPixmap (XtScreen (drawing_area), "seq1_mat.icon", fg, bg);
	pix_mat_sq2 = XmGetPixmap (XtScreen (drawing_area), "seq2_mat.icon", fg, bg);
	pix_mat_sq3 = XmGetPixmap (XtScreen (drawing_area), "seq3_mat.icon", fg, bg);
	pix_ret = XmGetPixmap (XtScreen (drawing_area), "ret.icon", fg, bg);

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ */
/* The follow codes takes care of Automatic Scrolling */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++ */
	narg = 0;
	XtSetArg (args[narg], XmNheight, &main_window_height);
	narg++;
	XtSetArg (args[narg], XmNwidth, &main_window_width);
	narg++;
	XtGetValues (main_shell, args, narg);
/* ----------------------------------------------------------- */
/* Set initial data on the visible portion of the drawing_area */
/* ----------------------------------------------------------- */
	visible.x_left = 0;
	visible.x_right = (int) main_window_width;
	visible.y_top = 0;
	visible.y_bottom = (int) main_window_height;
/* ++++++++++++++++++++++++++ */
/* End of Automatic Scrolling */
/* ++++++++++++++++++++++++++ */

	XtVaGetValues (main_shell, XmNclipWindow, &test_window, NULL);

/*
 * XDrawString(XtDisplay(test_window),test_window, theGC, 100, 100,"This is
 * clip_window", 21);
 */

/*
 * XCopyArea(XtDisplay(drawing_area),XtWindow(drawing_area),test_window,theGC,
 * 0,0,100,100,200,200);
 */
	make_region (template_tree_pointer, current_node);
	XtMainLoop ();

	return (1);		/* This statement is never reached.  It is here to keep the compiler happy about functions
				 * returning with a value. */
}
