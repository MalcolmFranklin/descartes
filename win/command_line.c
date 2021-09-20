/***********************************************************
 * MODULE:	COMMAND_LINE.C
 *
 ***********************************************************
 * PURPOSE:	Use the X11 "resource" mechanism to
 * implement command line switches for the Descartes
 * language processor.  We are getting more than a
 * commandline interface here, you can set any of the
 * custom Xt "resources" defined here, in your .Xdefaults
 * file, or vial any other mechanism for setting X
 * application resource values.
 ***********************************************************
 * FUNCTIONS DECLARED
 *
 *	EXTERNAL:
 *		Functions to interface with the Xt resource
 *		system:
 *			fetch_command_line_args_struct()
 *			fetch_num_commandline_args()
 *			get_commandline_values()
 *
 *		Functions to return the values of command
 *		line switches:
 *			fetch_infile_name()
 *			fetch_outfile_name()
 *			fetch_batch_switch()
 *			fetch_drawing_width()
 *			fetch_drawing_height()
 ***********************************************************
 * USE:
 * In main (), use the following protocol to load your 
 * custom command line switches into the Xt resource system:
 *
 * toplevel = XtVaAppInitialize (&app, "Descartes",
 *		       *fetch_command_line_args_struct (),
 *			   *fetch_num_commandline_args (),
 *			       *&argc, argv, NULL);
 * get_commandline_values (toplevel);
 *
 * Now you can fetch the value of any custom resource with
 * the access function defined for it in this file.  Ex:
 *
 *	*infileptr = fopen (fetch_infile_name (), "r");
 *
 * AUTHOR: Malcolm L.Franklin, Arizona State University
 ***********************************************************
 * NOTE:	I learned how to implement custom
 * application resources by following instructions given to
 * me by by Mr. Bill Parrette of ITDC.  Most of the
 * comments regarding the XtResource and XrmOptionDescRec
 * structures, were taken from instructions he sent me via
 * email.
 ***********************************************************
 * $Date: 1994/10/20 08:29:57 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/command_line.c,v $
 **********************************************************/
    static char    *rcsid = "$Id: command_line.c,v 1.13 1994/10/20 08:29:57 franklin Exp $";

#ifndef PARTIAL_GCC_INSTALLATION
#include <stddef.h>
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

/* Some systems still do not provide the Standard C offsetof
 * macro definition, even when they do provide stddef.h */

#ifndef offsetof
#define offsetof(TYPE, MEMBER) \
((size_t) &((TYPE *)0)->MEMBER)
#endif

/**********************************************************
 * NOTE TO FUTURE MAINTAINERS USING CenterLine "clcc"
 * COMPILER:
 * 
 * Nearly all the SunOS 4.x Operating System include files
 * (<sys/xxx.h>) cause compilation errors under a strict
 * ANSI/ISO compiler running in ANSI mode, such
 * as CenterLine "clcc".  In order to get these to compile,
 * with clcc, you have to pass the  -Xa (K&R C
 * compatibility switch) to the compiler.  BUT (get this)
 * when we do this, the CenterLine preprocessor #defines
 * __STDC__ to 0 (zero); when this happens, we dont see the
 * vararg prototypes for the X functions -- and get warning
 * messages for calling them with different numbers of
 * arguments.  On top of all this noise, we DONT GET all
 * the ANSI/ISO C type checking that we could have.
 * 
 * WORKAROUND: When compiling with clcc, #define __STDC__
 * to 1 AFTER #including the system header files you need
 * (<sys/xxx.h>), and hopefully before #including any of
 * the header files you (or I, or Yu-Kuh, or someone else)
 * wrote. Here is the code:
 *********************************************************/

#ifdef __CLCC__

#ifdef __STDC__
#undef __STDC__
#endif

#define __STDC__ 1
#endif

#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>    /* List of valid values
				* for the XtResource
				* ".resource_type"
				* field (like XtRString
				* and XtRImmediate). */

#include "command_line.h"

/**********************************************************
 * Declare 1 element in the following struct for each
 * custom resource that you want to add. This is where the
 * Xt library will store the actual values for your custom
 * resources.
 *********************************************************/
    typedef struct custom_resources_struct
    {
	char           *infile;
	char           *outfile;
	Boolean         batch;
	Boolean         iconic;
	int		drawing_height;
	int 		drawing_width;
    }               custom_resources_tt;
    static custom_resources_tt cmdline_data;

/**********************************************************
 * Use this enumerated type to index into the arrays of
 * structures for the custom resources.  I used it for
 * clarity; it is not required.
 *********************************************************/
    typedef enum
    {
	INFILE_SWITCH,
	OUTFILE_SWITCH,
	BATCH_SWITCH,
	ICONIC_SWITCH,
	DRAWING_HEIGHT,
	DRAWING_WIDTH,
	THE_END_OF_SWITCHES
    } switch_idx_tt;

/**********************************************************
 * custom_xt_resource[] tells the Xt library how to convert
 * the external representation of your resources, into the
 * values stored in cmdline_data (defined above).  Here is
 * a definition of the fields:
 *
 *	typedef struct {
 *		String   resource_name;
 *		String   resource_class;
 *		String   resource_type;
 *		Cardinal resource_size;
 *		Cardinal resource_offset;
 *		String   default_type;
 *		caddr_t  default_address;
 *	} XtResource;
 *
 *	Where:
 *	    resource_name   Is the instance name for your
 *			    custom resource.
 *	    resource_class  Is the class name for your
 *			    custom resource.
 *	    resource_type   Is the data type for your custom
 *			    resource from
 *			    the  list below.
 *	    resource_size   Is the size,  in bytes,  of your
 *                          custom resource.
 *	    resource_offset Is the offset  from the
 *                          beginning  of the
 *			    structure  that you defined to
 *			    hold all of your custom
 *			    resources.  You can use the
 *			    ANSI/ISO C "offsetof()" macro
 *                          (#defined in <stddef.h>) to get
 *			    this value.
 *	    default_type    Is the data  type (from the
 *			    list below) of the default value
 *			    to be used if your custom
 *			    resource is not specified
 *                          anywhere.
 *	    default_address Is the address  of the  default
 *			    value for your custom resource
 *			    if it is not specified anywhere.
 *
 *	If your resource type is:     Then the resource_type
 *				      used above is:
 *	-------------------------     ----------------------
 *	XtAccelerators                 XtRAcceleratorTable
 *	Boolean                        XtRBoolean
 *	Bool                           XtRBool
 *	XtCallbackList                 XtRCallback
 *	XColor                         XtRColor
 *	Cursor                         XtRCursor
 *	Dimension                      XtRDimension
 *	Display *                      XtRDisplay
 *	FILE *                         XtRFile
 *	float                          XtRFloat
 *	Font                           XtRFont
 *	XFontStruct *                  XtRFontStruct
 *	(*)()                          XtRFunction
 *	int                            XtRInt
 *	Pixel                          XtRPixel
 *	Pixmap                         XtRPixmap
 *	caddr_t *	               XtRPointer
 *	Position                       XtRPosition
 *	short                          XtRShort
 *	char *                         XtRString
 *	XtTranslations                 XtRTranslationTable
 *	unsigned char                  XtRUnsignedChar
 *	Widget                         XtRWidget
 *	Window                         XtRWindow
 *	The default_address field
 *	      really contains the value    XtRImmediate
 *	The default_address field
 *	      contains a function pointer
 *	      called to return the value   XtRCallProc
 *
 **********************************************************/
static XtResource custom_xt_resource[THE_END_OF_SWITCHES] ={
	{/* custom_xt_resource[INFILE_SWITCH] */
	    (String) "infile",
	    (String) "Infile",
	    XtRString,
	    (Cardinal) sizeof (char *),
	    (Cardinal)offsetof(custom_resources_tt, infile),
	    XtRImmediate,
	    ""
	},
	{/* custom_xt_resource[OUTFILE_SWITCH] */
	    (String) "outfile",
	    (String) "Outfile",
	    XtRString,
	    (Cardinal) sizeof (char *),
	    (Cardinal)offsetof(custom_resources_tt,outfile),
	    XtRImmediate,
	    "descartes.out"
	},
	{/* custom_xt_resource[BATCH_SWITCH] */
	    (String) "batch",
	    (String) "Batch",
	    XtRBoolean,
	    (Cardinal) sizeof (Boolean),
	    (Cardinal) offsetof(custom_resources_tt, batch),
	    XtRImmediate,
	    (Boolean) FALSE
	},
	{/* custom_xt_resource[ICONIC_SWITCH] */
	    (String) "iconic",
	    (String) "Iconic",
	    XtRBoolean,
	    (Cardinal) sizeof (Boolean),
	    (Cardinal)offsetof(custom_resources_tt, iconic),
	    XtRImmediate,
	    (Boolean) FALSE
	},
	{/* custom_xt_resource[DRAWING_HEIGHT] */
	    (String) "drawing_height",
	    (String) "Drawing_height",
	    XtRInt,
	    (Cardinal) sizeof (int),
	    (Cardinal)offsetof(custom_resources_tt, drawing_height),
	    XtRImmediate,
	    (caddr_t) 1280
	},
	{/* custom_xt_resource[DRAWING_WIDTH] */
	    (String) "drawing_width",
	    (String) "Drawing_width",
	    XtRInt,
	    (Cardinal) sizeof (int),
	    (Cardinal)offsetof(custom_resources_tt, drawing_width),
	    XtRImmediate,
	    (caddr_t) 1500
	}
    };

/**********************************************************
 * commandline_args[] tells the Xt library how to parse the
 * command line for your custom resources.  Here is a
 * description of the fields.
 *
 *	typedef struct {
 *		char *option;
 *		char *specifier;
 *		XrmOptionKind argKind;
 *		caddr_t value;
 *	} XrmOptionDescRec, *XrmOptionDescList;
 *
 * Where:
 *	option	 Is the actual name of the argument in argv.
 *	specifier Is the resource name for the command line 
 *                option along with any bindings (such as
 *		  tight binding (.) or loose bindings (*)).
 *	argKind   Is the style of command line option
 *		  specification (see below).
 *	value     Is the default value if argKind is
 *                XrmoptionNoArg.
 *
 * If your command line                   Then the argKind:
 * argument style is:                     above is this:
 * -----------------------------------    ------------------
 * -red (the option itself is the data)   XrmoptionIsArg
 * -cred (no space between arg & data)    XrmoptionStickyArg
 * -c red (space between arg & data)      XrmoptionSepArg
 * -c red (ignore arg & data)             XrmoptionSkipArg
 * -c red (ignore this arg & all others)  XrmoptionSkipLine
 * (use the value member of the
 *  XrmOptionDescRec structure
 *  for the data)                         XrmoptionNoArg
 **********************************************************/

static XrmOptionDescRec
	         commandline_args[THE_END_OF_SWITCHES] = {
	{/* commandline_args[INFILE_SWITCH] */
	    "-infile",
	    "*infile",
	    XrmoptionSepArg,
	    NULL
	},
	{/* commandline_args[OUTFILE_SWITCH] */
	    "-outfile",
	    "*outfile",
	    XrmoptionSepArg,
	    NULL
	},
	{/* commandline_args[BATCH_SWITCH] */
	    "-batch",
	    "*batch",
	    XrmoptionSepArg,
	    NULL
	},
	{/* commandline_args[ICONIC_SWITCH] */
	    "-iconic",
	    "*iconic",
	    XrmoptionSepArg,
	    NULL
	},
	{/* commandline_args[DRAWING_HEIGHT] */
	    "-drawing_height",
	    "*drawing_height",
	    XrmoptionSepArg,
	    NULL
	},
	{/* commandline_args[DRAWING_WIDTH] */
	    "-drawing_width",
	    "*drawing_width",
	    XrmoptionSepArg,
	    NULL
	}
    };

/***********************************************************
 * FUNCTION:	FETCH_COMMAND_LINE_ARGS_STRUCT
 *	Use this function to pass the address of the
 *	commandline_args[] array to 
 *	XtAppInitialize()/XtVaAppInitialize().
 **********************************************************/
XrmOptionDescRec *fetch_command_line_args_struct (void)
{
    return (commandline_args);
}

/***********************************************************
 * FUNCTION:	FETCH_NUM_COMMANDLINE_ARGS
 *	Use this function to pass the number of custom
 *	resources that are referenced in the
 *	commandline_args[] array, to XtAppInitialize()/
 *	XtVaAppInitialize().
 **********************************************************/
int             fetch_num_commandline_args (void)
{
    return ((int) THE_END_OF_SWITCHES);
}

/***********************************************************
 * FUNCTION:	GET_COMMANDLINE_VALUES
 *	Call this function immediately after
 *      XtAppInitialize()/ XtVaAppInitialize(), to fetch
 *	the actual values for the resources, and store them
 *	in to the cmdline_data struct.
 **********************************************************/
void            get_commandline_values (Widget AppTopShell)
{
    XtGetApplicationResources (AppTopShell, &cmdline_data,
			   custom_xt_resource,
		  fetch_num_commandline_args (), NULL, 0);
}

/***********************************************************
 * FUNCTION:	FETCH_INFILE_NAME
 *	Must only be called AFTER get_commandline_values().
 **********************************************************/
char           *fetch_infile_name (void)
{
    return (cmdline_data.infile);
}

/***********************************************************
 * FUNCTION:	FETCH_OUTFILE_NAME
 *	Must only be called AFTER get_commandline_values().
 **********************************************************/
char           *fetch_outfile_name (void)
{
    return (cmdline_data.outfile);
}

/***********************************************************
 * FUNCTION:	FETCH_BATCH_SWITCH
 *	Must only be called AFTER get_commandline_values().
 **********************************************************/
int             fetch_batch_switch (void)
{
    return ((int) cmdline_data.batch);
}

/***********************************************************
 * FUNCTION:	FETCH_ICONIC_SWITCH
 *	Must only be called AFTER get_commandline_values().
 **********************************************************/
int             fetch_iconic_switch (void)
{
    return ((int) cmdline_data.iconic);
}

/***********************************************************
 * FUNCTION:	FETCH_DRAWING_HEIGHT
 *	Must only be called AFTER get_commandline_values().
 **********************************************************/
int             fetch_drawing_height (void)
{
    return ((int) cmdline_data.drawing_height);
}

/***********************************************************
 * FUNCTION:	FETCH_DRAWING_WIDTH
 *	Must only be called AFTER get_commandline_values().
 **********************************************************/
int             fetch_drawing_width (void)
{
    return ((int) cmdline_data.drawing_width);
}
