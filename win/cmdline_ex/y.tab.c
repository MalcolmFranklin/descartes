extern char *malloc(), *realloc();

# line 2 "des2.y"
/*******************************************************************************
 *
 * MODULE:	DES2.Y
 *
 * PURPOSE:	YACC Grammar for the Descartes Specification Language
 *
 * CREATED:	April   25   1992
 *
 * AUTHOR:	Believed to be Lee, of ASU
 *******************************************************************************
 * $Date: 1994/08/03 21:59:32 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/cmdline_ex/RCS/des2.y,v $
 *
 ******************************************************************************/
#if 0
/*******************************************************************************
 *
$Log: des2.y,v $
 * Revision 1.13  1994/08/03  21:59:32  franklin
 * Changed "str" to "pstr"; prefix "str" is reserved by string.h
 *
 * Revision 1.12  1994/08/03  17:05:07  franklin
 * Changed Error_Counter -> error_counter; "E" prefix is reserved by errno.h
 *
 * Revision 1.11  1994/06/07  21:46:56  franklin
 * Remove all references to global text widget Rd_text_w.
 *
 * Revision 1.10  1994/05/13  02:51:43  franklin
 * Clean up the file so it will run through Bison (at least with
 * the "-y" switch).
 *
 * Revision 1.9  1994/05/03  20:09:17  franklin
 * Replace hardcoded constant 0x7FFFFFFF with INT_MAX from <limits.h>.
 * Increase the size of lower_bound and upper_bound, where the upper and
 * lower bounds on the number of items in a sequence are stored (as strings
 * rather than as integers.).
 *
 * Revision 1.8  1994/05/02  17:46:56  franklin
 * Remove nested includes in desc_struct.h,  include unistd.h
 * and sys/stat.h here.
 *
 * Revision 1.7  1994/04/23  21:32:07  franklin
 * Get the declaration of Build_Hoare_Tree() from build_hoare_tree.h
 *
 * Revision 1.6  1994/04/12  09:02:42  franklin
 * Allocate enough storage for the string AND its null terminator.
 *
 * Revision 1.5  1994/04/09  23:53:28  franklin
 * Get the declaration of "para[]" from analysis1.h
 *
 * Revision 1.4  1994/04/09  22:32:45  franklin
 * wid1.h requires the definition of type Mesg in mesg.h.  As of this writing,
 * that is the only reason this file #includes mesg.h
 *
 * Revision 1.3  1994/04/08  03:14:14  franklin
 * Minor cleanup.
 *
 * Revision 1.2  1994/04/08  03:09:05  franklin
 * Add include files so that y.tab.o can be built as a standalone object file,
 * rather than having to #include y.tab.c in build_rtn.c.
 *
 ******************************************************************************/
#endif
static char	*des2_y_rcsid = "$Id: des2.y,v 1.13, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3 1994/08/03 21:59:32 franklin Exp $";

#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <limits.h>
#include <ctype.h>
#include <unistd.h> /* Required by desc_struct.h */
#include <sys/stat.h>
#include <X11/Intrinsic.h>
#include <X11/X.h> /* analysis1.h requires the definition of type Pixmap. */
#include "mesg.h" /* Required by wid1.h */
#include "wid1.h"
#include "desc_struct.h"
#include "desc_table.h"
#include "analysis1.h" /* Declaration of extern Pixmap para[5] */
#include "build_hoare_tree.h" /* Declaration of Build_Hoare_Tree() */

#define err(x) puts(x)

extern void Display_Build_User_Msg();

/* Definitions moved from near the end of the file, to make Bison happy. */
char item_str[80];
int item_val;
int tmp_indent;
int indentation=0;
char lower_bound[64];
char upper_bound[64];
short item_type=0;
int wk_indent;


int tmp;
short node_type;
#include "need_before_ytab.h"
/* Type "NODE" is defined in need_before_ytab.h.  It is one of the elements
 * in the lval struct defined in the "%union" statement below.  The "%union"
 * statement is translated into the definition of type YYSTYPE in y.tab.h */

/* I deleted the typedef of YYSTYPE that was here.  This type is automatically
 * taken from the "%union" construct in the YACC specification; it should
 * not be explicitly defined by the user.  This caused problems when porting
 * to the Solaris 2.3 version of lex and yacc, as well as when porting to the
 * Gnu "flex" and "bison" tools. */



# line 116 "des2.y"
typedef union {
        int ival;
        NODE symbol;
} YYSTYPE;
# define NEW_LINE 257
# define NEW_PAGE 258
# define RETURN 259
# define R_PAR 260
# define L_PAR 261
# define INDENT 262
# define RANGE 263
# define LITERALS 264
# define REFER 265
# define MATCH 266
# define CAP_C 267
# define P_PLUS 268
# define P_MINUS 269
# define P_TIMES 270
# define P_DIVIDED_BY 271
# define P_RAISED_TO 272
# define P_EQUAL 273
# define P_NOT_EQUAL 274
# define P_GREATER_THAN 275
# define P_LESS_THAN 276
# define P_GREATER_THAN_OR_EQUAL 277
# define P_LESS_THAN_OR_EQUAL 278
# define P_OR 279
# define P_AND 280
# define P_NOT 281
# define P_PARALLEL 282
# define P_CONCUR 283
# define P_EQUAL_TO 284
# define P_TIMER 285
# define P_SEND_TO 286
# define P_RECEIVE_FROM 287
# define P_DELAY 288
# define P_ASEND_TO 289
# define P_ARECEIVE_FROM 290
# define P_GTIME 291
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern int yyerrflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
YYSTYPE yylval, yyval;
# define YYERRCODE 256

# line 694 "des2.y"

#include "lex.yy.c"
yyerror()
{
   fprintf(stderr, "Error line no %d: \"%s\"\n",yylineno,yytext);
   sprintf(User_Msg,"Error line no %d: \"%s\"\n",yylineno,yytext);
   Display_Build_User_Msg(rd_spec_text_w,User_Msg);
   error_counter++;
}
/*
yyerror(s,t)
char *s,*t;
{
extern int yynerrs;

   fprintf(stderr, "%s error %d line no : %d %s expecting :%s\n",s,yynerrs+1,yylineno,yytext,t);
   warning(s,(char*)0);
}
warning(s,t)
char *s,*t;
{
  fprintf(stdout,"%s",s);
  if(t)
    fprintf(stdout,"%s",t);
  fprintf(stdout,"near line %d\n",yylineno);
}
*/
int yyexca[] ={
-1, 1,
	0, -1,
	-2, 0,
-1, 131,
	260, 73,
	263, 73,
	10, 73,
	35, 73,
	42, 73,
	43, 73,
	-2, 72,
	};
# define YYNPROD 83
# define YYLAST 307
int yyact[]={

    99,    78,    79,    10,    13,    82,    55,    41,    70,    72,
    69,    10,    68,    78,    79,    54,    56,    82,    13,    83,
    70,    72,    69,    10,    78,    79,    80,    36,    82,    51,
     4,   106,   109,    64,    10,     9,    53,    52,    80,     7,
   120,    10,    54,    51,    26,   119,   132,    27,   108,    80,
    53,    52,    94,    61,    59,    33,    93,    60,    58,    32,
    13,    29,    17,    16,   131,   129,   128,   123,   111,     8,
     8,    44,    39,    48,    15,   105,    49,    47,    18,   107,
    67,    52,    53,    38,    51,    30,    31,    12,    23,    19,
    13,    40,    14,    20,     2,    37,    11,    22,    57,    21,
     5,    62,    63,    46,    28,    73,    76,    77,    81,    42,
    35,    66,    74,    34,    43,    66,     6,     3,    -1,    71,
    24,    65,    34,    88,    86,    87,    75,    95,    96,    25,
     1,     0,    84,    85,     0,    81,     0,     0,    66,   101,
   103,     0,    89,    91,    92,   104,    71,    98,     0,     0,
     0,     0,    97,     0,     0,   100,   102,     0,   110,     0,
     0,     0,   112,     0,     0,     0,     0,     0,     0,     0,
   114,   116,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   121,   122,   113,   115,     0,   117,
     0,   118,   130,     0,     0,   126,   127,   133,     0,     0,
     0,   134,   124,     0,   125,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    45,     0,     0,     0,     0,     0,     0,    50,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    50,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    90 };
int yypact[]={

  -226,  -226, -1000,    80,    80,  -264,  -198, -1000,  -199,  -264,
 -1000, -1000,  -215, -1000,  -215,  -200,  -264,  -264,  -201,  -215,
 -1000,  -235, -1000, -1000,  -255,  -255,    -6,  -250,  -215,  -264,
  -202,  -203,  -264,  -264, -1000, -1000,  -223,  -255,  -255,  -244,
  -243, -1000,  -255, -1000,    80,    80,    49, -1000,    40,    38,
 -1000, -1000, -1000, -1000,    50,    80,    80,  -204,  -264,  -264,
 -1000, -1000, -1000, -1000,    80,  -255,  -256,     8,     8, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000,  -233,  -213, -1000, -1000,
 -1000,  -229,  -233, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000,  -264, -1000, -1000, -1000, -1000,     8,     8,
 -1000,    80, -1000,    80,  -216,  -221, -1000, -1000,  -233,  -233,
  -193,  -229, -1000, -1000,    80, -1000,    80, -1000, -1000,  -233,
  -233,  -194,  -195,  -264, -1000, -1000,  -196,  -214,  -264, -1000,
 -1000, -1000,  -264, -1000, -1000 };
int yypgo[]={

     0,   130,    80,    79,   129,   126,   120,    93,   118,    89,
    75,   117,    87,   116,    68,   112,   107,   106,   105,    88,
    71,   103,    76,    73,    77,   100,    99,    97,    95,    83,
    72,    94,    91 };
int yyr1[]={

     0,     1,     1,    31,    31,     9,     9,     7,     7,    12,
    10,    10,    10,    11,    11,    11,    25,    25,    25,    25,
    25,    13,    13,    13,    13,    13,    13,     4,     4,     4,
    26,    26,    19,    27,    28,    28,     6,     6,     6,     6,
     6,    29,    29,    29,    29,    29,    29,    29,    29,    20,
    20,    20,    21,    21,    21,    21,    21,    24,    22,    23,
    18,     3,     3,     2,     2,     2,     2,     5,     5,     5,
    15,    15,    17,    17,    17,    16,    16,    16,     8,    30,
    32,    32,    14 };
int yyr2[]={

     0,     3,     5,     7,     6,     2,     4,     2,     2,     3,
     2,     3,     2,     3,     3,     3,     9,     9,    11,    10,
    13,     9,     8,    11,    10,     9,     8,     7,     6,     6,
     3,     5,     5,     5,     3,     5,     5,     7,     7,     7,
     6,     7,     6,     9,     8,     9,     8,    11,    10,     3,
     5,     3,     3,     3,     5,     5,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     2,     3,     2,     2,     3,
     2,     3,     9,    11,    13,     9,    11,     9,     4,     3,
     3,     5,     3 };
int yychk[]={

 -1000,    -1,   -31,   -11,   256,   -25,   -13,   265,   -14,   261,
   267,   -31,   -12,    10,   -12,   -14,   261,   261,   -14,    -9,
    -7,   -26,   -27,   -19,    -6,    -4,   259,   262,    -9,   261,
   -14,   -14,   260,   256,    -7,   -19,   262,   -28,   -29,   -30,
   -32,   262,   -29,   -12,   -20,   256,   -21,   -24,   -23,   -22,
   263,    35,    43,    42,   265,   256,   266,   -14,   260,   256,
   260,   256,   -14,   -14,   256,   -29,   -30,    -2,   256,   266,
   264,    -3,   265,   -18,   -15,    -5,   -17,   -16,   257,   258,
   282,   -14,   261,   262,   -12,   -12,   -24,   -22,   -23,   -12,
   256,   -12,   -12,   260,   256,   -14,   -14,   -12,    -2,   256,
   -12,   -20,   -12,   -20,   -14,   -10,   264,    -3,   261,   261,
   -10,   -14,   -14,   -12,   -20,   -12,   -20,   -12,   -12,   261,
   261,   -10,   -10,   260,   -12,   -12,   -10,   -10,   260,   260,
   -14,   260,   260,   -14,   -14 };
int yydef[]={

     0,    -2,     1,     0,     0,    13,    14,    15,     0,     0,
    82,     2,     0,     9,     0,     0,     0,     0,     0,     3,
     5,     7,     8,    30,     0,     0,     0,     0,     4,     0,
     0,     0,     0,     0,     6,    31,     0,    33,    34,     0,
    79,    80,    32,    36,     0,     0,    49,    51,    52,    53,
    56,    57,    59,    58,     0,     0,     0,     0,    25,    26,
    16,    17,    21,    22,     0,    35,     0,     0,     0,    63,
    64,    65,    66,    61,    62,    60,    70,    71,    67,    68,
    69,     0,     0,    81,    37,    38,    50,    55,    54,    27,
    29,    28,    39,    18,    19,    23,    24,    28,     0,     0,
    41,     0,    42,     0,     0,     0,    11,    12,     0,     0,
     0,    10,    20,    45,     0,    46,     0,    43,    44,     0,
     0,     0,     0,     0,    47,    48,     0,     0,    77,    72,
    75,    -2,     0,    76,    74 };
typedef struct { char *t_name; int t_val; } yytoktype;
#ifndef YYDEBUG
#	define YYDEBUG	0	/* don't allow debugging */
#endif

#if YYDEBUG

yytoktype yytoks[] =
{
	"NEW_LINE",	257,
	"NEW_PAGE",	258,
	"RETURN",	259,
	"R_PAR",	260,
	"L_PAR",	261,
	"INDENT",	262,
	"RANGE",	263,
	"LITERALS",	264,
	"REFER",	265,
	"MATCH",	266,
	"CAP_C",	267,
	"P_PLUS",	268,
	"P_MINUS",	269,
	"P_TIMES",	270,
	"P_DIVIDED_BY",	271,
	"P_RAISED_TO",	272,
	"P_EQUAL",	273,
	"P_NOT_EQUAL",	274,
	"P_GREATER_THAN",	275,
	"P_LESS_THAN",	276,
	"P_GREATER_THAN_OR_EQUAL",	277,
	"P_LESS_THAN_OR_EQUAL",	278,
	"P_OR",	279,
	"P_AND",	280,
	"P_NOT",	281,
	"P_PARALLEL",	282,
	"P_CONCUR",	283,
	"P_EQUAL_TO",	284,
	"P_TIMER",	285,
	"P_SEND_TO",	286,
	"P_RECEIVE_FROM",	287,
	"P_DELAY",	288,
	"P_ASEND_TO",	289,
	"P_ARECEIVE_FROM",	290,
	"P_GTIME",	291,
	"-unknown-",	-1	/* ends search */
};

char * yyreds[] =
{
	"-no such reduction-",
	"modules : module",
	"modules : modules module",
	"module : module_name nls hoare_trees",
	"module : error nls hoare_trees",
	"hoare_trees : hoare_tree",
	"hoare_trees : hoare_trees hoare_tree",
	"hoare_tree : input_def_sec",
	"hoare_tree : output_def_sec",
	"nls : '\n'",
	"t_node_name : cap_char",
	"t_node_name : LITERALS",
	"t_node_name : module_call",
	"module_name : name_sequence",
	"module_name : name_seq",
	"module_name : REFER",
	"name_sequence : cap_char L_PAR cap_char R_PAR",
	"name_sequence : cap_char L_PAR cap_char error",
	"name_sequence : name_sequence cap_char L_PAR cap_char R_PAR",
	"name_sequence : name_sequence cap_char L_PAR cap_char error",
	"name_sequence : name_sequence cap_char L_PAR cap_char R_PAR cap_char",
	"name_seq : L_PAR cap_char R_PAR cap_char",
	"name_seq : L_PAR cap_char error cap_char",
	"name_seq : name_seq L_PAR cap_char R_PAR cap_char",
	"name_seq : name_seq L_PAR cap_char error cap_char",
	"name_seq : name_seq L_PAR cap_char R_PAR",
	"name_seq : name_seq L_PAR cap_char error",
	"para : INDENT REFER nls",
	"para : INDENT error nls",
	"para : INDENT REFER error",
	"input_def_sec : analysis_tree",
	"input_def_sec : input_def_sec analysis_tree",
	"analysis_tree : para node_set",
	"output_def_sec : return syn_tree_set",
	"syn_tree_set : node_set",
	"syn_tree_set : syn_tree_set node_set",
	"return : RETURN nls",
	"return : RETURN operators nls",
	"return : RETURN error nls",
	"return : INDENT MATCH nls",
	"return : INDENT error nls",
	"node_set : Indent node_name nls",
	"node_set : Indent error nls",
	"node_set : Indent node_name operators nls",
	"node_set : Indent error operators nls",
	"node_set : node_set Indent node_name nls",
	"node_set : node_set Indent error nls",
	"node_set : node_set Indent node_name operators nls",
	"node_set : node_set Indent error operators nls",
	"operators : operator",
	"operators : operator sequence_no",
	"operators : sequence_no",
	"operator : disc_union",
	"operator : sequen",
	"operator : sequen disc_union",
	"operator : disc_union sequen",
	"operator : RANGE",
	"sequence_no : '#'",
	"sequen : '*'",
	"disc_union : '+'",
	"primitives : non_argu_prim",
	"module_call : primitives",
	"module_call : module_node",
	"node_name : MATCH",
	"node_name : LITERALS",
	"node_name : module_call",
	"node_name : REFER",
	"non_argu_prim : NEW_LINE",
	"non_argu_prim : NEW_PAGE",
	"non_argu_prim : P_PARALLEL",
	"module_node : m_name_sequence",
	"module_node : m_name_seq",
	"m_name_sequence : cap_char L_PAR t_node_name R_PAR",
	"m_name_sequence : m_name_sequence cap_char L_PAR t_node_name R_PAR",
	"m_name_sequence : m_name_sequence t_node_name L_PAR t_node_name R_PAR cap_char",
	"m_name_seq : L_PAR t_node_name R_PAR cap_char",
	"m_name_seq : m_name_seq L_PAR t_node_name R_PAR cap_char",
	"m_name_seq : m_name_seq L_PAR t_node_name R_PAR",
	"module_title : module_call nls",
	"Indent : indent",
	"indent : INDENT",
	"indent : indent INDENT",
	"cap_char : CAP_C",
};
#endif /* YYDEBUG */
#line 1 "/usr/lib/yaccpar"
/*	@(#)yaccpar 1.10 89/04/04 SMI; from S5R3 1.10	*/

/*
** Skeleton parser driver for yacc output
*/

/*
** yacc user known macros and defines
*/
#define YYERROR		goto yyerrlab
#define YYACCEPT	{ free(yys); free(yyv); return(0); }
#define YYABORT		{ free(yys); free(yyv); return(1); }
#define YYBACKUP( newtoken, newvalue )\
{\
	if ( yychar >= 0 || ( yyr2[ yytmp ] >> 1 ) != 1 )\
	{\
		yyerror( "syntax error - cannot backup" );\
		goto yyerrlab;\
	}\
	yychar = newtoken;\
	yystate = *yyps;\
	yylval = newvalue;\
	goto yynewstate;\
}
#define YYRECOVERING()	(!!yyerrflag)
#ifndef YYDEBUG
#	define YYDEBUG	1	/* make debugging available */
#endif

/*
** user known globals
*/
int yydebug;			/* set to 1 to get debugging */

/*
** driver internal defines
*/
#define YYFLAG		(-1000)

/*
** static variables used by the parser
*/
static YYSTYPE *yyv;			/* value stack */
static int *yys;			/* state stack */

static YYSTYPE *yypv;			/* top of value stack */
static int *yyps;			/* top of state stack */

static int yystate;			/* current state */
static int yytmp;			/* extra var (lasts between blocks) */

int yynerrs;			/* number of errors */

int yyerrflag;			/* error recovery flag */
int yychar;			/* current input token number */


/*
** yyparse - return 0 if worked, 1 if syntax error not recovered from
*/
int
yyparse()
{
	register YYSTYPE *yypvt;	/* top of value stack for $vars */
	unsigned yymaxdepth = YYMAXDEPTH;

	/*
	** Initialize externals - yyparse may be called more than once
	*/
	yyv = (YYSTYPE*)malloc(yymaxdepth*sizeof(YYSTYPE));
	yys = (int*)malloc(yymaxdepth*sizeof(int));
	if (!yyv || !yys)
	{
		yyerror( "out of memory" );
		return(1);
	}
	yypv = &yyv[-1];
	yyps = &yys[-1];
	yystate = 0;
	yytmp = 0;
	yynerrs = 0;
	yyerrflag = 0;
	yychar = -1;

	goto yystack;
	{
		register YYSTYPE *yy_pv;	/* top of value stack */
		register int *yy_ps;		/* top of state stack */
		register int yy_state;		/* current state */
		register int  yy_n;		/* internal state number info */

		/*
		** get globals into registers.
		** branch to here only if YYBACKUP was called.
		*/
	yynewstate:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;
		goto yy_newstate;

		/*
		** get globals into registers.
		** either we just started, or we just finished a reduction
		*/
	yystack:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;

		/*
		** top of for (;;) loop while no reductions done
		*/
	yy_stack:
		/*
		** put a state and value onto the stacks
		*/
#if YYDEBUG
		/*
		** if debugging, look up token value in list of value vs.
		** name pairs.  0 and negative (-1) are special values.
		** Note: linear search is used since time is not a real
		** consideration while debugging.
		*/
		if ( yydebug )
		{
			register int yy_i;

			(void)printf( "State %d, token ", yy_state );
			if ( yychar == 0 )
				(void)printf( "end-of-file\n" );
			else if ( yychar < 0 )
				(void)printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				(void)printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ++yy_ps >= &yys[ yymaxdepth ] )	/* room on stack? */
		{
			/*
			** reallocate and recover.  Note that pointers
			** have to be reset, or bad things will happen
			*/
			int yyps_index = (yy_ps - yys);
			int yypv_index = (yy_pv - yyv);
			int yypvt_index = (yypvt - yyv);
			yymaxdepth += YYMAXDEPTH;
			yyv = (YYSTYPE*)realloc((char*)yyv,
				yymaxdepth * sizeof(YYSTYPE));
			yys = (int*)realloc((char*)yys,
				yymaxdepth * sizeof(int));
			if (!yyv || !yys)
			{
				yyerror( "yacc stack overflow" );
				return(1);
			}
			yy_ps = yys + yyps_index;
			yy_pv = yyv + yypv_index;
			yypvt = yyv + yypvt_index;
		}
		*yy_ps = yy_state;
		*++yy_pv = yyval;

		/*
		** we have a new state - find out what to do
		*/
	yy_newstate:
		if ( ( yy_n = yypact[ yy_state ] ) <= YYFLAG )
			goto yydefault;		/* simple state */
#if YYDEBUG
		/*
		** if debugging, need to mark whether new token grabbed
		*/
		yytmp = yychar < 0;
#endif
		if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
			yychar = 0;		/* reached EOF */
#if YYDEBUG
		if ( yydebug && yytmp )
		{
			register int yy_i;

			(void)printf( "Received token " );
			if ( yychar == 0 )
				(void)printf( "end-of-file\n" );
			else if ( yychar < 0 )
				(void)printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				(void)printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ( ( yy_n += yychar ) < 0 ) || ( yy_n >= YYLAST ) )
			goto yydefault;
		if ( yychk[ yy_n = yyact[ yy_n ] ] == yychar )	/*valid shift*/
		{
			yychar = -1;
			yyval = yylval;
			yy_state = yy_n;
			if ( yyerrflag > 0 )
				yyerrflag--;
			goto yy_stack;
		}

	yydefault:
		if ( ( yy_n = yydef[ yy_state ] ) == -2 )
		{
#if YYDEBUG
			yytmp = yychar < 0;
#endif
			if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
				yychar = 0;		/* reached EOF */
#if YYDEBUG
			if ( yydebug && yytmp )
			{
				register int yy_i;

				(void)printf( "Received token " );
				if ( yychar == 0 )
					(void)printf( "end-of-file\n" );
				else if ( yychar < 0 )
					(void)printf( "-none-\n" );
				else
				{
					for ( yy_i = 0;
						yytoks[yy_i].t_val >= 0;
						yy_i++ )
					{
						if ( yytoks[yy_i].t_val
							== yychar )
						{
							break;
						}
					}
					(void)printf( "%s\n", yytoks[yy_i].t_name );
				}
			}
#endif /* YYDEBUG */
			/*
			** look through exception table
			*/
			{
				register int *yyxi = yyexca;

				while ( ( *yyxi != -1 ) ||
					( yyxi[1] != yy_state ) )
				{
					yyxi += 2;
				}
				while ( ( *(yyxi += 2) >= 0 ) &&
					( *yyxi != yychar ) )
					;
				if ( ( yy_n = yyxi[1] ) < 0 )
					YYACCEPT;
			}
		}

		/*
		** check for syntax error
		*/
		if ( yy_n == 0 )	/* have an error */
		{
			/* no worry about speed here! */
			switch ( yyerrflag )
			{
			case 0:		/* new error */
				yyerror( "syntax error" );
				goto skip_init;
			yyerrlab:
				/*
				** get globals into registers.
				** we have a user generated syntax type error
				*/
				yy_pv = yypv;
				yy_ps = yyps;
				yy_state = yystate;
				yynerrs++;
			skip_init:
			case 1:
			case 2:		/* incompletely recovered error */
					/* try again... */
				yyerrflag = 3;
				/*
				** find state where "error" is a legal
				** shift action
				*/
				while ( yy_ps >= yys )
				{
					yy_n = yypact[ *yy_ps ] + YYERRCODE;
					if ( yy_n >= 0 && yy_n < YYLAST &&
						yychk[yyact[yy_n]] == YYERRCODE)					{
						/*
						** simulate shift of "error"
						*/
						yy_state = yyact[ yy_n ];
						goto yy_stack;
					}
					/*
					** current state has no shift on
					** "error", pop stack
					*/
#if YYDEBUG
#	define _POP_ "Error recovery pops state %d, uncovers state %d\n"
					if ( yydebug )
						(void)printf( _POP_, *yy_ps,
							yy_ps[-1] );
#	undef _POP_
#endif
					yy_ps--;
					yy_pv--;
				}
				/*
				** there is no state on stack with "error" as
				** a valid shift.  give up.
				*/
				YYABORT;
			case 3:		/* no shift yet; eat a token */
#if YYDEBUG
				/*
				** if debugging, look up token in list of
				** pairs.  0 and negative shouldn't occur,
				** but since timing doesn't matter when
				** debugging, it doesn't hurt to leave the
				** tests here.
				*/
				if ( yydebug )
				{
					register int yy_i;

					(void)printf( "Error recovery discards " );
					if ( yychar == 0 )
						(void)printf( "token end-of-file\n" );
					else if ( yychar < 0 )
						(void)printf( "token -none-\n" );
					else
					{
						for ( yy_i = 0;
							yytoks[yy_i].t_val >= 0;
							yy_i++ )
						{
							if ( yytoks[yy_i].t_val
								== yychar )
							{
								break;
							}
						}
						(void)printf( "token %s\n",
							yytoks[yy_i].t_name );
					}
				}
#endif /* YYDEBUG */
				if ( yychar == 0 )	/* reached EOF. quit */
					YYABORT;
				yychar = -1;
				goto yy_newstate;
			}
		}/* end if ( yy_n == 0 ) */
		/*
		** reduction by production yy_n
		** put stack tops, etc. so things right after switch
		*/
#if YYDEBUG
		/*
		** if debugging, print the string that is the user's
		** specification of the reduction which is just about
		** to be done.
		*/
		if ( yydebug )
			(void)printf( "Reduce by (%d) \"%s\"\n",
				yy_n, yyreds[ yy_n ] );
#endif
		yytmp = yy_n;			/* value to switch over */
		yypvt = yy_pv;			/* $vars top of value stack */
		/*
		** Look in goto table for next state
		** Sorry about using yy_state here as temporary
		** register variable, but why not, if it works...
		** If yyr2[ yy_n ] doesn't have the low order bit
		** set, then there is no action to be done for
		** this reduction.  So, no saving & unsaving of
		** registers done.  The only difference between the
		** code just after the if and the body of the if is
		** the goto yy_stack in the body.  This way the test
		** can be made before the choice of what to do is needed.
		*/
		{
			/* length of production doubled with extra bit */
			register int yy_len = yyr2[ yy_n ];

			if ( !( yy_len & 01 ) )
			{
				yy_len >>= 1;
				yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
				yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
					*( yy_ps -= yy_len ) + 1;
				if ( yy_state >= YYLAST ||
					yychk[ yy_state =
					yyact[ yy_state ] ] != -yy_n )
				{
					yy_state = yyact[ yypgo[ yy_n ] ];
				}
				goto yy_stack;
			}
			yy_len >>= 1;
			yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
			yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
				*( yy_ps -= yy_len ) + 1;
			if ( yy_state >= YYLAST ||
				yychk[ yy_state = yyact[ yy_state ] ] != -yy_n )
			{
				yy_state = yyact[ yypgo[ yy_n ] ];
			}
		}
					/* save until reenter driver code */
		yystate = yy_state;
		yyps = yy_ps;
		yypv = yy_pv;
	}
	/*
	** code supplied by user is placed in this switch
	*/
	switch( yytmp )
	{
		
case 1:
# line 140 "des2.y"
{printf("rule 0 \n");
		} break;
case 2:
# line 144 "des2.y"
{printf("rule 01 \n");
		} break;
case 3:
# line 149 "des2.y"
{printf("rule 1 \n");
		tmp_indent=0;
		} break;
case 9:
# line 163 "des2.y"
{
	printf("rule 30 new line\n");
	} break;
case 11:
# line 171 "des2.y"
{
		printf("rule 193 yylval %s %d  \n",yylval.symbol.pstr,yylval.symbol.val);
		printf("token %s\n",yytext);} break;
case 13:
# line 178 "des2.y"
{
		if(tmp_indent==0){
		node_type=MODULE_TITLE;
		} else 
		node_type=REFERENCE_DIRECT_PRODUCT;
             Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);
		} break;
case 14:
# line 186 "des2.y"
{printf("rule 2 \n");
		if(tmp_indent==0){
		node_type=MODULE_TITLE;
		printf("rule 31 %s indent %d %d\n",item_str,indentation,tmp_indent);
         Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);
		} else 
		node_type=REFERENCE_DIRECT_PRODUCT;
		} break;
case 15:
# line 195 "des2.y"
{
		node_type=MODULE_TITLE;
		strcpy(item_str,yypvt[-0].symbol.pstr);
             Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);

		} break;
case 16:
# line 204 "des2.y"
{printf("rule 3 indent %d\n",indentation);
		strcpy(item_str,yypvt[-3].symbol.pstr);
		strcat(item_str,"(");
		strcat(item_str,yypvt[-1].symbol.pstr);
		strcat(item_str,")");
		yyval.symbol.pstr=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy(yyval.symbol.pstr,item_str);

		} break;
case 17:
# line 214 "des2.y"
{err("Parithesis errror");
		} break;
case 18:
# line 217 "des2.y"
{printf(" rule 32\n");
		strcat(item_str,yypvt[-3].symbol.pstr);
		strcat(item_str,"(");
		strcat(item_str,yypvt[-1].symbol.pstr);
		strcat(item_str,")");
		} break;
case 20:
# line 226 "des2.y"
{printf(" rule 33\n");
		strcat(item_str,yypvt[-4].symbol.pstr);
		strcat(item_str,"(");
		strcat(item_str,yypvt[-2].symbol.pstr);
		strcat(item_str,")");
		strcat(item_str,yypvt[-0].symbol.pstr);
		} break;
case 21:
# line 236 "des2.y"
{printf("rule 31 indent %d %d\n",indentation,tmp_indent);
		strcpy(item_str,"(");
		strcat(item_str,yypvt[-2].symbol.pstr);
		strcat(item_str,")");
		strcat(item_str,yypvt[-0].symbol.pstr);
		yyval.symbol.pstr=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy(yyval.symbol.pstr,item_str);
		} break;
case 23:
# line 246 "des2.y"
{printf("rule 33 \n");
		strcat(item_str,"(");
		strcat(item_str,yypvt[-2].symbol.pstr);
		strcat(item_str,")");
		strcat(item_str,yypvt[-0].symbol.pstr);
		} break;
case 25:
# line 254 "des2.y"
{printf("rule 33 \n");
		strcat(item_str,"(");
		strcat(item_str,yypvt[-1].symbol.pstr);
		strcat(item_str,")");
		} break;
case 27:
# line 264 "des2.y"
{printf("rule 4 indent %d\n",indentation);
		node_type=REFERENCE_DIRECT_PRODUCT;
               Build_Hoare_Tree("%d %s %d",node_type,yypvt[-1].symbol.pstr,1);

		} break;
case 30:
# line 276 "des2.y"
{printf("rule 7 \n");} break;
case 31:
# line 278 "des2.y"
{printf("rule 71 \n");} break;
case 32:
# line 282 "des2.y"
{printf("rule 8 \n");
		} break;
case 33:
# line 287 "des2.y"
{printf("rule 10 indent%d\n",indentation);
		} break;
case 34:
# line 292 "des2.y"
{printf("rule 11 \n");} break;
case 35:
# line 294 "des2.y"
{printf("rule 11 \n");} break;
case 36:
# line 299 "des2.y"
{
		printf("rule 101 indent%d\n",indentation);
		node_type = MATCH_DIRECT_PRODUCT;
             Build_Hoare_Tree("%d %s %d",node_type,yypvt[-1].symbol.pstr,1);

		} break;
case 37:
# line 306 "des2.y"
{printf("rule 102 %s %s indent%d\n",yypvt[-2].symbol.pstr,yypvt[-1].symbol.pstr,indentation);
		strcpy(item_str,yypvt[-2].symbol.pstr);
		strcat(item_str,yypvt[-1].symbol.pstr);
		if(strcmp(yypvt[-1].symbol.pstr, "*") ==0){
		node_type = MATCH_SEQUENCE;
		printf("* SEQUENCE\n"); 
		sprintf(lower_bound,"0");
		sprintf(upper_bound,"%d",INT_MAX);
   Build_Hoare_Tree("%d %s %d",node_type,item_str,1,lower_bound,upper_bound);

		}
		if(strcmp(yypvt[-1].symbol.pstr, "+")==0) {
		node_type = MATCH_DISCRIMINATED_UNION;
		printf("* UNION\n"); 
             Build_Hoare_Tree("%d %s %d",node_type,item_str,1);

		}
		if(yypvt[-1].symbol.val== RANGE) {
		node_type = MATCH_SEQUENCE_RANGE;
             Build_Hoare_Tree("%d %s %d",node_type,item_str,1,lower_bound,upper_bound);

		}
		if(strcmp(yypvt[-1].symbol.pstr,"*+")==0) {
		node_type = MATCH_SEQUENCE_UNION;
		sprintf(lower_bound,"0");
		sprintf(upper_bound,"%d",INT_MAX);
         Build_Hoare_Tree("%d %s %d",node_type,item_str,1,lower_bound,upper_bound);

		}
		} break;
case 38:
# line 337 "des2.y"
{
		err("wrong operator");
		} break;
case 39:
# line 341 "des2.y"
{
		node_type=MATCH_DIRECT_PRODUCT;
		printf("rule 10 %s indent%d\n",yypvt[-1].symbol.pstr,indentation);
            Build_Hoare_Tree("%d %s %d",node_type,yypvt[-1].symbol.pstr,1);

		} break;
case 41:
# line 351 "des2.y"
{printf("rule 121 %s %d item_type%d\n",yypvt[-1].symbol.pstr,yypvt[-1].symbol.val,item_type);
		printf("rule 121 %s %d indent%d\n",item_str,item_val,tmp_indent);
		if((yypvt[-1].symbol.val== REFER)&&(item_type==0))
		node_type=REFERENCE_DIRECT_PRODUCT;
		else if((yypvt[-1].symbol.val == MATCH)&&(item_type==0))
		node_type = MATCH_DIRECT_PRODUCT;
		else if((yypvt[-1].symbol.val == LITERALS)&&(item_type==0))
		node_type = LITERAL;
		else if(item_type!=0){
		if(item_type==REFER)
		node_type=REFERENCE_DIRECT_PRODUCT; 
		else
		node_type = item_type;
		item_type=0;
		}
		else
		node_type=REFERENCE_DIRECT_PRODUCT; 
		printf("rule 121 %s %d\n",item_str,node_type);
              Build_Hoare_Tree("%d %s %d",node_type,yypvt[-1].symbol.pstr,tmp_indent);
		} break;
case 43:
# line 373 "des2.y"
{printf("rule 122 %s %s %d indent%d\n",yypvt[-2].symbol.pstr,yypvt[-1].symbol.pstr,yypvt[-2].symbol.val,tmp_indent);
		strcpy(item_str,yypvt[-2].symbol.pstr);
		strcat(item_str,yypvt[-1].symbol.pstr);
		printf("rule 122 %s %s %d indent%d\n",item_str,yypvt[-1].symbol.pstr,item_val,tmp_indent);

		if(strcmp(yypvt[-1].symbol.pstr, "*") ==0){
		if(item_val== REFER)
		node_type = REFERENCE_SEQUENCE;
		else
		node_type = MATCH_SEQUENCE;
		printf("* SEQUENCE\n"); 
		sprintf(lower_bound,"0");
		sprintf(upper_bound,"%d",INT_MAX);
               Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent,lower_bound,upper_bound);

		}
		if(strcmp(yypvt[-1].symbol.pstr, "+")==0) {
		if(item_val == REFER)
		node_type = REFERENCE_DISCRIMINATED_UNION;
		else
		node_type = MATCH_DISCRIMINATED_UNION;
		printf("* UNION\n"); 
            Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);

		}
		if(yypvt[-1].symbol.val== RANGE) {
		node_type = REFERENCE_SEQUENCE_RANGE;
               Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent,lower_bound,upper_bound);

		}
		if(strcmp(yypvt[-1].symbol.pstr,"*+")==0) {
		node_type = REFERENCE_SEQUENCE_UNION;
		sprintf(lower_bound,"0");
		sprintf(upper_bound,"%d",INT_MAX);
               Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent,lower_bound,upper_bound);

		}
		if(strcmp(yypvt[-1].symbol.pstr,"#")==0) {
		node_type = REFERENCE_SEQUENCE_NO;
          Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);
		}
		printf("rule 122 %s %d\n",item_str,node_type);
		} break;
case 45:
# line 418 "des2.y"
{printf("rule 123 %s %d item_type %d\n",yypvt[-1].symbol.pstr,yypvt[-1].symbol.val,item_type);
		printf("rule 123 %s %d indent%d\n",item_str,item_val,tmp_indent);
		if((item_val== REFER)&&(item_type == 0))
		node_type=REFERENCE_DIRECT_PRODUCT;
		else if((item_val == MATCH)&&(item_type==0))
		node_type = MATCH_DIRECT_PRODUCT;
		else if((item_val == LITERALS)&&(item_type==0))
		node_type = LITERAL;
		else if(item_type!=0){
		if(item_type==REFER)
		node_type=REFERENCE_DIRECT_PRODUCT; 
		else
		node_type = item_type;
		item_type=0;
		}
		else 
		node_type =REFERENCE_DIRECT_PRODUCT ;

		printf("rule 123%s %d\n",item_str,node_type);
             Build_Hoare_Tree("%d %s %d",node_type,yypvt[-1].symbol.pstr,tmp_indent);

		} break;
case 47:
# line 442 "des2.y"
{printf("rule 124 %s %s %d indent %d\n",yypvt[-2].symbol.pstr,yypvt[-1].symbol.pstr,yypvt[-2].symbol.val,tmp_indent);
		strcpy(item_str,yypvt[-2].symbol.pstr);
		strcat(item_str,yypvt[-1].symbol.pstr);
		printf("rule 124 %s %s %d indent %d\n",item_str,yypvt[-1].symbol.pstr,item_val,tmp_indent);

		if(strcmp(yypvt[-1].symbol.pstr, "*") ==0){
		if(item_val == REFER)
		node_type = REFERENCE_SEQUENCE;
		else if (item_val==MATCH)
		node_type = MATCH_SEQUENCE;
		printf("* SEQUENCE\n"); 
		sprintf(lower_bound,"0");
		sprintf(upper_bound,"%d",INT_MAX);
     Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent,lower_bound,upper_bound);

		}
		if(strcmp(yypvt[-1].symbol.pstr, "+")==0) {
		if(item_val == REFER)
		node_type = REFERENCE_DISCRIMINATED_UNION;
		else
		node_type = MATCH_DISCRIMINATED_UNION;
		printf("* UNION\n"); 
        Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);

		}
		if(yypvt[-1].symbol.val== RANGE){ 
		node_type = REFERENCE_SEQUENCE_RANGE;
		printf("range\n");
		printf("range\n");
     Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent,lower_bound,upper_bound);

		}
		if(strcmp(yypvt[-1].symbol.pstr,"*+")==0){
		node_type = REFERENCE_SEQUENCE_UNION;
		sprintf(lower_bound,"0");
		sprintf(upper_bound,"%d",INT_MAX);
     Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent,lower_bound,upper_bound);

		}
		if(strcmp(yypvt[-1].symbol.pstr,"#")==0) {
		node_type = REFERENCE_SEQUENCE_NO;
             Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);

		}
		printf("rule 124 %s %d\n",item_str,node_type);
		} break;
case 49:
# line 492 "des2.y"
{printf("rule 14 %s\n",yypvt[-0].symbol.pstr);} break;
case 50:
# line 494 "des2.y"
{printf("rule 14 \n");} break;
case 51:
# line 496 "des2.y"
{printf("rule 143 \n");} break;
case 52:
# line 500 "des2.y"
{printf("rule 13 \n");
		} break;
case 53:
# line 503 "des2.y"
{printf("rule 13 \n");
		} break;
case 54:
# line 506 "des2.y"
{
		strcpy(yyval.symbol.pstr , yypvt[-1].symbol.pstr);
		strcat(yyval.symbol.pstr,  yypvt[-0].symbol.pstr);
		printf("rule 133 %s\n",yyval.symbol.pstr);
		} break;
case 55:
# line 512 "des2.y"
{
		strcpy(yyval.symbol.pstr , yypvt[-1].symbol.pstr);
		strcat(yyval.symbol.pstr,  yypvt[-0].symbol.pstr);
		printf("rule 134 %s\n",yyval.symbol.pstr);
		} break;
case 56:
# line 518 "des2.y"
{printf("rule 135 %s\n",yypvt[-0].symbol.pstr);
		printf("token %s up %s low %s\n",yytext,upper_bound,lower_bound);
		if(upper_bound < lower_bound)
		  err("range error");
		} break;
case 57:
# line 529 "des2.y"
{printf("rule 201 \n");
		} break;
case 58:
# line 534 "des2.y"
{printf("rule 16 \n");
		} break;
case 59:
# line 540 "des2.y"
{printf("rule 15 \n");
		
		} break;
case 60:
# line 547 "des2.y"
{printf("rule 18 \n");
		item_val = yypvt[-0].symbol.val;
		strcpy(item_str,yypvt[-0].symbol.pstr);
		} break;
case 61:
# line 554 "des2.y"
{printf("rule 18 \n");} break;
case 62:
# line 556 "des2.y"
{printf("rule 184 \n");
		} break;
case 63:
# line 561 "des2.y"
{
		item_val = yypvt[-0].symbol.val;
		strcpy(item_str,yypvt[-0].symbol.pstr);
		printf("rule 192 %d\n",yypvt[-0].symbol.val);
		printf("yylval %s %d  \n",yylval.symbol.pstr,yylval.symbol.val);
		printf("token %s\n",yytext);} break;
case 64:
# line 568 "des2.y"
{
		yyerrok;
		printf("rule 17 \n");
		item_val = yypvt[-0].symbol.val;
		strcpy(item_str,yypvt[-0].symbol.pstr);
		} break;
case 66:
# line 576 "des2.y"
{
		yyerrok;
		printf("rule 18 \n");
		item_val = yypvt[-0].symbol.val;
		strcpy(item_str,yypvt[-0].symbol.pstr);
		} break;
case 69:
# line 589 "des2.y"
{
		item_type=yypvt[-0].symbol.type;
		item_val = yypvt[-0].symbol.val;
		} break;
case 71:
# line 599 "des2.y"
{printf("rule 2 \n");} break;
case 72:
# line 603 "des2.y"
{printf("rule 003 indent %d\n",indentation);
		item_type=yypvt[-3].symbol.val;
		strcpy(item_str,yypvt[-3].symbol.pstr);
		strcat(item_str,"(");
		strcat(item_str,yypvt[-1].symbol.pstr);
		strcat(item_str,")");
		yyval.symbol.pstr=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy(yyval.symbol.pstr,item_str);
		} break;
case 73:
# line 613 "des2.y"
{printf(" rule 0032\n");
		item_type=yypvt[-3].symbol.val;
		strcat(item_str,yypvt[-3].symbol.pstr);
		strcat(item_str,"(");
		strcat(item_str,yypvt[-1].symbol.pstr);
		strcat(item_str,")");
		yyval.symbol.pstr=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy(yyval.symbol.pstr,item_str);
		} break;
case 74:
# line 623 "des2.y"
{printf(" rule 0032\n");
		item_type=yypvt[-0].symbol.val;
		strcat(item_str,yypvt[-4].symbol.pstr);
		strcat(item_str,"(");
		strcat(item_str,yypvt[-2].symbol.pstr);
		strcat(item_str,")");
		strcat(item_str,yypvt[-0].symbol.pstr);
		yyval.symbol.pstr=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy(yyval.symbol.pstr,item_str);
		} break;
case 75:
# line 637 "des2.y"
{printf("rule 0041 indent %d %d\n",indentation,tmp_indent);
		item_type=yypvt[-0].symbol.val;
		strcpy(item_str,"(");
		strcat(item_str,yypvt[-2].symbol.pstr);
		strcat(item_str,")");
		strcat(item_str,yypvt[-0].symbol.pstr);
		yyval.symbol.pstr=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy(yyval.symbol.pstr,item_str);
		printf("rule 0041 %s %s\n",item_str,yyval.symbol.pstr);
		} break;
case 76:
# line 648 "des2.y"
{printf("rule 0043 \n");
		item_type=yypvt[-0].symbol.val;
		strcat(item_str,"(");
		strcat(item_str,yypvt[-2].symbol.pstr);
		strcat(item_str,")");
		strcat(item_str,yypvt[-0].symbol.pstr);
		yyval.symbol.pstr=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy(yyval.symbol.pstr,item_str);
		} break;
case 77:
# line 658 "des2.y"
{printf("rule 0044 \n");
		strcat(item_str,"(");
		strcat(item_str,yypvt[-1].symbol.pstr);
		strcat(item_str,")");
		yyval.symbol.pstr=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy(yyval.symbol.pstr,item_str);
		printf("rule 0044 %s %s\n",item_str,yyval.symbol.pstr);
		} break;
case 79:
# line 671 "des2.y"
{ tmp_indent = wk_indent;
	} break;
case 80:
# line 677 "des2.y"
{printf("rule 61 %d\n",indentation);
	wk_indent = indentation; 
		} break;
case 81:
# line 681 "des2.y"
{ 
		wk_indent = indentation; 
		printf("rule 62 %d\n",indentation);} break;
case 82:
# line 687 "des2.y"
{
		yyerrok;
		printf("rule 20 yylval %s %d  \n",yylval.symbol.pstr,yylval.symbol.val);
		printf("token %s\n",yytext);} break;
	}
	goto yystack;		/* reset registers in driver code */
}
