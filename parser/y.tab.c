
/*  A Bison parser, made from des2.y with Bison version GNU Bison version 1.22
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	NEW_LINE	258
#define	NEW_PAGE	259
#define	RETURN	260
#define	R_PAR	261
#define	L_PAR	262
#define	INDENT	263
#define	RANGE	264
#define	LITERALS	265
#define	REFER	266
#define	MATCH	267
#define	CAP_C	268
#define	P_PLUS	269
#define	P_MINUS	270
#define	P_TIMES	271
#define	P_DIVIDED_BY	272
#define	P_RAISED_TO	273
#define	P_EQUAL	274
#define	P_NOT_EQUAL	275
#define	P_GREATER_THAN	276
#define	P_LESS_THAN	277
#define	P_GREATER_THAN_OR_EQUAL	278
#define	P_LESS_THAN_OR_EQUAL	279
#define	P_OR	280
#define	P_AND	281
#define	P_NOT	282
#define	P_PARALLEL	283
#define	P_CONCUR	284
#define	P_EQUAL_TO	285
#define	P_TIMER	286
#define	P_SEND_TO	287
#define	P_RECEIVE_FROM	288
#define	P_DELAY	289
#define	P_ASEND_TO	290
#define	P_ARECEIVE_FROM	291
#define	P_GTIME	292

#line 1 "des2.y"

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
 * $Date: 1994/05/03 20:09:17 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/des2.y,v $
 *
 ******************************************************************************/
#if 0
/*******************************************************************************
 *
$Log: des2.y,v $
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
static char	*des2_y_rcsid = "$Id: des2.y,v 1.9 1994/05/03 20:09:17 franklin Exp $";

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
/* #include "build_hoare_tree.h" */ /* Declaration of Build_Hoare_Tree() */
extern void     Build_Hoare_Tree ( char *fmt, int type, char *name, int level_no, ... );

#define err(x) puts(x)

extern void Display_Build_User_Msg();
extern Widget Rd_text_w;

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



#line 105 "des2.y"
typedef union{
        int ival;
        NODE symbol;
} YYSTYPE;

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		136
#define	YYFLAG		-32768
#define	YYNTBASE	42

#define YYTRANSLATE(x) ((unsigned)(x) <= 292 ? yytranslate[x] : 73)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    38,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,    39,     2,     2,     2,     2,     2,
     2,    40,    41,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     5,     9,    13,    15,    18,    20,    22,    24,
    26,    28,    30,    32,    34,    36,    41,    46,    52,    58,
    65,    70,    75,    81,    87,    92,    97,   101,   105,   109,
   111,   114,   117,   120,   122,   125,   128,   132,   136,   140,
   144,   148,   152,   157,   162,   167,   172,   178,   184,   186,
   189,   191,   193,   195,   198,   201,   203,   205,   207,   209,
   211,   213,   215,   217,   219,   221,   223,   225,   227,   229,
   231,   233,   238,   244,   251,   256,   262,   267,   270,   272,
   274,   277
};

static const short yyrhs[] = {    43,
     0,    42,    43,     0,    48,    46,    44,     0,     1,    46,
    44,     0,    45,     0,    44,    45,     0,    52,     0,    54,
     0,    38,     0,    72,     0,    10,     0,    64,     0,    49,
     0,    50,     0,    11,     0,    72,     7,    72,     6,     0,
    72,     7,    72,     1,     0,    49,    72,     7,    72,     6,
     0,    49,    72,     7,    72,     1,     0,    49,    72,     7,
    72,     6,    72,     0,     7,    72,     6,    72,     0,     7,
    72,     1,    72,     0,    50,     7,    72,     6,    72,     0,
    50,     7,    72,     1,    72,     0,    50,     7,    72,     6,
     0,    50,     7,    72,     1,     0,     8,    11,    46,     0,
     8,     1,    46,     0,     8,    11,     1,     0,    53,     0,
    52,    53,     0,    51,    57,     0,    56,    55,     0,    57,
     0,    55,    57,     0,     5,    46,     0,     5,    58,    46,
     0,     5,     1,    46,     0,     8,    12,    46,     0,     8,
     1,    46,     0,    70,    65,    46,     0,    70,     1,    46,
     0,    70,    65,    58,    46,     0,    70,     1,    58,    46,
     0,    57,    70,    65,    46,     0,    57,    70,     1,    46,
     0,    57,    70,    65,    58,    46,     0,    57,    70,     1,
    58,    46,     0,    59,     0,    59,    60,     0,    60,     0,
    62,     0,    61,     0,    61,    62,     0,    62,    61,     0,
     9,     0,    39,     0,    40,     0,    41,     0,    66,     0,
    63,     0,    67,     0,    12,     0,    10,     0,    64,     0,
    11,     0,     3,     0,     4,     0,    28,     0,    68,     0,
    69,     0,    72,     7,    47,     6,     0,    68,    72,     7,
    47,     6,     0,    68,    47,     7,    47,     6,    72,     0,
     7,    47,     6,    72,     0,    69,     7,    47,     6,    72,
     0,    69,     7,    47,     6,     0,    64,    46,     0,    71,
     0,     8,     0,    71,     8,     0,    13,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   128,   132,   137,   141,   143,   144,   147,   148,   151,   157,
   158,   163,   166,   174,   183,   192,   202,   205,   213,   214,
   224,   233,   234,   241,   242,   248,   252,   258,   259,   264,
   266,   270,   275,   280,   282,   287,   294,   325,   329,   336,
   339,   360,   361,   405,   406,   429,   430,   477,   480,   482,
   484,   488,   491,   494,   500,   506,   517,   522,   528,   535,
   542,   544,   549,   556,   563,   564,   575,   576,   577,   586,
   587,   591,   601,   611,   625,   636,   646,   657,   659,   665,
   669,   675
};

static const char * const yytname[] = {   "$","error","$illegal.","NEW_LINE",
"NEW_PAGE","RETURN","R_PAR","L_PAR","INDENT","RANGE","LITERALS","REFER","MATCH",
"CAP_C","P_PLUS","P_MINUS","P_TIMES","P_DIVIDED_BY","P_RAISED_TO","P_EQUAL",
"P_NOT_EQUAL","P_GREATER_THAN","P_LESS_THAN","P_GREATER_THAN_OR_EQUAL","P_LESS_THAN_OR_EQUAL",
"P_OR","P_AND","P_NOT","P_PARALLEL","P_CONCUR","P_EQUAL_TO","P_TIMER","P_SEND_TO",
"P_RECEIVE_FROM","P_DELAY","P_ASEND_TO","P_ARECEIVE_FROM","P_GTIME","'\\n'",
"'#'","'*'","'+'","modules","module","hoare_trees","hoare_tree","nls","t_node_name",
"module_name","name_sequence","name_seq","para","input_def_sec","analysis_tree",
"output_def_sec","syn_tree_set","return","node_set","operators","operator","sequence_no",
"sequen","disc_union","primitives","module_call","node_name","non_argu_prim",
"module_node","m_name_sequence","m_name_seq","Indent","indent","cap_char","cap_char"
};
#endif

static const short yyr1[] = {     0,
    42,    42,    43,    43,    44,    44,    45,    45,    46,    47,
    47,    47,    48,    48,    48,    49,    49,    49,    49,    49,
    50,    50,    50,    50,    50,    50,    51,    51,    51,    52,
    52,    53,    54,    55,    55,    56,    56,    56,    56,    56,
    57,    57,    57,    57,    57,    57,    57,    57,    58,    58,
    58,    59,    59,    59,    59,    59,    60,    61,    62,    63,
    64,    64,    65,    65,    65,    65,    66,    66,    66,    67,
    67,    68,    68,    68,    69,    69,    69,    -1,    70,    71,
    71,    72
};

static const short yyr2[] = {     0,
     1,     2,     3,     3,     1,     2,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     4,     4,     5,     5,     6,
     4,     4,     5,     5,     4,     4,     3,     3,     3,     1,
     2,     2,     2,     1,     2,     2,     3,     3,     3,     3,
     3,     3,     4,     4,     4,     4,     5,     5,     1,     2,
     1,     1,     1,     2,     2,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     4,     5,     6,     4,     5,     4,     2,     1,     1,
     2,     1
};

static const short yydefact[] = {     0,
     0,     0,    15,    82,     0,     1,     0,    13,    14,     0,
     9,     0,     0,     2,     0,     0,     0,     0,     0,     0,
     4,     5,     0,     7,    30,     8,     0,     0,     0,     3,
     0,     0,     0,     0,    56,    57,    58,    59,    36,     0,
    49,    51,    53,    52,     0,     0,     0,     6,    80,    32,
     0,    79,     0,    31,    33,    34,    22,    21,     0,    26,
    25,    17,    16,    38,    37,    50,    54,    55,    28,    29,
    27,    39,     0,     0,    67,    68,     0,    64,    66,    63,
    69,    61,    65,     0,    60,    62,    70,    71,     0,    81,
     0,    35,    19,    18,    24,    23,     0,     0,    42,     0,
    11,     0,    12,    10,    41,     0,     0,     0,     0,     0,
    28,    20,    46,     0,    45,     0,    44,     0,    43,     0,
     0,     0,     0,    48,    47,    75,     0,     0,    77,    72,
     0,    72,    76,    74,     0,     0
};

static const short yydefgoto[] = {     5,
     6,    21,    22,    12,   102,     7,     8,     9,    23,    24,
    25,    26,    55,    27,    50,    40,    41,    42,    43,    44,
    82,   103,    84,    85,    86,    87,    88,    51,    52,   104
};

static const short yypact[] = {   123,
   -29,    -3,-32768,-32768,   115,-32768,   -29,    -3,     6,    16,
-32768,    67,    43,-32768,    67,    17,    -3,    -3,    18,    10,
    67,-32768,    40,    42,-32768,-32768,    40,    -3,    -3,    67,
    -3,    91,   119,   -29,-32768,-32768,-32768,-32768,-32768,   -29,
    32,-32768,    -5,    15,   -29,     2,   -29,-32768,-32768,    40,
    73,    70,     5,-32768,    40,    40,-32768,-32768,   131,    -3,
    -3,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,    99,    28,-32768,-32768,    86,-32768,-32768,-32768,
-32768,-32768,-32768,    28,-32768,-32768,    86,    75,    81,-32768,
   -29,    40,-32768,    -3,-32768,-32768,    28,    28,-32768,   -29,
-32768,    89,-32768,    81,-32768,   -29,   101,   110,    86,    86,
-32768,-32768,-32768,   -29,-32768,   -29,-32768,    -3,-32768,    86,
    86,   113,   127,-32768,-32768,-32768,   129,   132,    -3,-32768,
    -3,    24,-32768,-32768,   139,-32768
};

static const short yypgoto[] = {-32768,
   135,   126,    49,     7,   -75,-32768,-32768,-32768,-32768,-32768,
   118,-32768,-32768,-32768,   -23,   -59,-32768,   102,   100,   103,
-32768,   -31,    72,-32768,-32768,-32768,-32768,   -49,-32768,     0
};


#define	YYLAST		146


static const short yytable[] = {    10,
    73,    13,    70,    56,    10,    91,    73,    16,    11,     4,
    45,   107,    17,    15,   100,    46,    32,    33,    34,    83,
    46,    47,    18,    31,   106,    39,    35,    57,    58,   -73,
    59,    92,   -73,   122,   123,    38,    35,   114,   116,    11,
    64,    83,    73,    28,   127,   128,    65,    49,    29,    53,
    89,    69,    71,    72,    37,    11,    36,    37,    38,    95,
    96,   -73,   -73,   -73,   -73,    11,    36,    37,    38,    48,
    36,    19,    89,    74,    20,    75,    76,    90,    48,    77,
    99,   109,    78,    79,    80,     4,   108,   110,    75,    76,
   105,    60,    77,   112,   118,   101,    61,   111,     4,    97,
    81,    75,    76,   113,   115,    77,   117,   120,    78,    79,
    80,     4,   119,    81,   135,     1,   121,   126,   129,    62,
   124,     2,   125,     1,    63,     3,    81,     4,   133,     2,
   134,    93,   130,     3,   131,     4,    94,   132,   136,    14,
    30,    54,    66,    68,    98,    67
};

static const short yycheck[] = {     0,
    50,     2,     1,    27,     5,     1,    56,     8,    38,    13,
     1,    87,     7,     7,    74,    11,    17,    18,     1,    51,
    11,    12,     7,     7,    84,    19,     9,    28,    29,     6,
    31,    55,     9,   109,   110,    41,     9,    97,    98,    38,
    34,    73,    92,     1,   120,   121,    40,     8,     6,     8,
    51,    45,    46,    47,    40,    38,    39,    40,    41,    60,
    61,    38,    39,    40,    41,    38,    39,    40,    41,    21,
    39,     5,    73,     1,     8,     3,     4,     8,    30,     7,
    74,     7,    10,    11,    12,    13,    87,     7,     3,     4,
    84,     1,     7,    94,     6,    10,     6,    91,    13,     1,
    28,     3,     4,    97,    98,     7,   100,     7,    10,    11,
    12,    13,   106,    28,     0,     1,     7,   118,     6,     1,
   114,     7,   116,     1,     6,    11,    28,    13,   129,     7,
   131,     1,     6,    11,     6,    13,     6,     6,     0,     5,
    15,    24,    41,    44,    73,    43
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/home/local/lib/bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Bob Corbett and Richard Stallman

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */


#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#define YYLEX		yylex(&yylval, &yylloc)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_bcopy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_bcopy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_bcopy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 184 "/home/local/lib/bison.simple"
int
yyparse()
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_bcopy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_bcopy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_bcopy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 129 "des2.y"
{printf("rule 0 \n");
		;
    break;}
case 2:
#line 133 "des2.y"
{printf("rule 01 \n");
		;
    break;}
case 3:
#line 138 "des2.y"
{printf("rule 1 \n");
		tmp_indent=0;
		;
    break;}
case 9:
#line 152 "des2.y"
{
	printf("rule 30 new line\n");
	;
    break;}
case 11:
#line 160 "des2.y"
{
		printf("rule 193 yylval %s %d  \n",yylval.symbol.str,yylval.symbol.val);
		printf("token %s\n",yytext);;
    break;}
case 13:
#line 167 "des2.y"
{
		if(tmp_indent==0){
		node_type=MODULE_TITLE;
		} else 
		node_type=REFERENCE_DIRECT_PRODUCT;
             Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);
		;
    break;}
case 14:
#line 175 "des2.y"
{printf("rule 2 \n");
		if(tmp_indent==0){
		node_type=MODULE_TITLE;
		printf("rule 31 %s indent %d %d\n",item_str,indentation,tmp_indent);
         Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);
		} else 
		node_type=REFERENCE_DIRECT_PRODUCT;
		;
    break;}
case 15:
#line 184 "des2.y"
{
		node_type=MODULE_TITLE;
		strcpy(item_str,yyvsp[0].symbol.str);
             Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);

		;
    break;}
case 16:
#line 193 "des2.y"
{printf("rule 3 indent %d\n",indentation);
		strcpy(item_str,yyvsp[-3].symbol.str);
		strcat(item_str,"(");
		strcat(item_str,yyvsp[-1].symbol.str);
		strcat(item_str,")");
		yyval.symbol.str=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy(yyval.symbol.str,item_str);

		;
    break;}
case 17:
#line 203 "des2.y"
{err("Parithesis errror");
		;
    break;}
case 18:
#line 206 "des2.y"
{printf(" rule 32\n");
		strcat(item_str,yyvsp[-3].symbol.str);
		strcat(item_str,"(");
		strcat(item_str,yyvsp[-1].symbol.str);
		strcat(item_str,")");
		;
    break;}
case 20:
#line 215 "des2.y"
{printf(" rule 33\n");
		strcat(item_str,yyvsp[-4].symbol.str);
		strcat(item_str,"(");
		strcat(item_str,yyvsp[-2].symbol.str);
		strcat(item_str,")");
		strcat(item_str,yyvsp[0].symbol.str);
		;
    break;}
case 21:
#line 225 "des2.y"
{printf("rule 31 indent %d %d\n",indentation,tmp_indent);
		strcpy(item_str,"(");
		strcat(item_str,yyvsp[-2].symbol.str);
		strcat(item_str,")");
		strcat(item_str,yyvsp[0].symbol.str);
		yyval.symbol.str=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy(yyval.symbol.str,item_str);
		;
    break;}
case 23:
#line 235 "des2.y"
{printf("rule 33 \n");
		strcat(item_str,"(");
		strcat(item_str,yyvsp[-2].symbol.str);
		strcat(item_str,")");
		strcat(item_str,yyvsp[0].symbol.str);
		;
    break;}
case 25:
#line 243 "des2.y"
{printf("rule 33 \n");
		strcat(item_str,"(");
		strcat(item_str,yyvsp[-1].symbol.str);
		strcat(item_str,")");
		;
    break;}
case 27:
#line 253 "des2.y"
{printf("rule 4 indent %d\n",indentation);
		node_type=REFERENCE_DIRECT_PRODUCT;
               Build_Hoare_Tree("%d %s %d",node_type,yyvsp[-1].symbol.str,1);

		;
    break;}
case 30:
#line 265 "des2.y"
{printf("rule 7 \n");;
    break;}
case 31:
#line 267 "des2.y"
{printf("rule 71 \n");;
    break;}
case 32:
#line 271 "des2.y"
{printf("rule 8 \n");
		;
    break;}
case 33:
#line 276 "des2.y"
{printf("rule 10 indent%d\n",indentation);
		;
    break;}
case 34:
#line 281 "des2.y"
{printf("rule 11 \n");;
    break;}
case 35:
#line 283 "des2.y"
{printf("rule 11 \n");;
    break;}
case 36:
#line 288 "des2.y"
{
		printf("rule 101 indent%d\n",indentation);
		node_type = MATCH_DIRECT_PRODUCT;
             Build_Hoare_Tree("%d %s %d",node_type,yyvsp[-1].symbol.str,1);

		;
    break;}
case 37:
#line 295 "des2.y"
{printf("rule 102 %s %s indent%d\n",yyvsp[-2].symbol.str,yyvsp[-1].symbol.str,indentation);
		strcpy(item_str,yyvsp[-2].symbol.str);
		strcat(item_str,yyvsp[-1].symbol.str);
		if(strcmp(yyvsp[-1].symbol.str, "*") ==0){
		node_type = MATCH_SEQUENCE;
		printf("* SEQUENCE\n"); 
		sprintf(lower_bound,"0");
		sprintf(upper_bound,"%d",INT_MAX);
   Build_Hoare_Tree("%d %s %d",node_type,item_str,1,lower_bound,upper_bound);

		}
		if(strcmp(yyvsp[-1].symbol.str, "+")==0) {
		node_type = MATCH_DISCRIMINATED_UNION;
		printf("* UNION\n"); 
             Build_Hoare_Tree("%d %s %d",node_type,item_str,1);

		}
		if(yyvsp[-1].symbol.val== RANGE) {
		node_type = MATCH_SEQUENCE_RANGE;
             Build_Hoare_Tree("%d %s %d",node_type,item_str,1,lower_bound,upper_bound);

		}
		if(strcmp(yyvsp[-1].symbol.str,"*+")==0) {
		node_type = MATCH_SEQUENCE_UNION;
		sprintf(lower_bound,"0");
		sprintf(upper_bound,"%d",INT_MAX);
         Build_Hoare_Tree("%d %s %d",node_type,item_str,1,lower_bound,upper_bound);

		}
		;
    break;}
case 38:
#line 326 "des2.y"
{
		err("wrong operator");
		;
    break;}
case 39:
#line 330 "des2.y"
{
		node_type=MATCH_DIRECT_PRODUCT;
		printf("rule 10 %s indent%d\n",yyvsp[-1].symbol.str,indentation);
            Build_Hoare_Tree("%d %s %d",node_type,yyvsp[-1].symbol.str,1);

		;
    break;}
case 41:
#line 340 "des2.y"
{printf("rule 121 %s %d item_type%d\n",yyvsp[-1].symbol.str,yyvsp[-1].symbol.val,item_type);
		printf("rule 121 %s %d indent%d\n",item_str,item_val,tmp_indent);
		if((yyvsp[-1].symbol.val== REFER)&&(item_type==0))
		node_type=REFERENCE_DIRECT_PRODUCT;
		else if((yyvsp[-1].symbol.val == MATCH)&&(item_type==0))
		node_type = MATCH_DIRECT_PRODUCT;
		else if((yyvsp[-1].symbol.val == LITERALS)&&(item_type==0))
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
              Build_Hoare_Tree("%d %s %d",node_type,yyvsp[-1].symbol.str,tmp_indent);
		;
    break;}
case 43:
#line 362 "des2.y"
{printf("rule 122 %s %s %d indent%d\n",yyvsp[-2].symbol.str,yyvsp[-1].symbol.str,yyvsp[-2].symbol.val,tmp_indent);
		strcpy(item_str,yyvsp[-2].symbol.str);
		strcat(item_str,yyvsp[-1].symbol.str);
		printf("rule 122 %s %s %d indent%d\n",item_str,yyvsp[-1].symbol.str,item_val,tmp_indent);

		if(strcmp(yyvsp[-1].symbol.str, "*") ==0){
		if(item_val== REFER)
		node_type = REFERENCE_SEQUENCE;
		else
		node_type = MATCH_SEQUENCE;
		printf("* SEQUENCE\n"); 
		sprintf(lower_bound,"0");
		sprintf(upper_bound,"%d",INT_MAX);
               Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent,lower_bound,upper_bound);

		}
		if(strcmp(yyvsp[-1].symbol.str, "+")==0) {
		if(item_val == REFER)
		node_type = REFERENCE_DISCRIMINATED_UNION;
		else
		node_type = MATCH_DISCRIMINATED_UNION;
		printf("* UNION\n"); 
            Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);

		}
		if(yyvsp[-1].symbol.val== RANGE) {
		node_type = REFERENCE_SEQUENCE_RANGE;
               Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent,lower_bound,upper_bound);

		}
		if(strcmp(yyvsp[-1].symbol.str,"*+")==0) {
		node_type = REFERENCE_SEQUENCE_UNION;
		sprintf(lower_bound,"0");
		sprintf(upper_bound,"%d",INT_MAX);
               Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent,lower_bound,upper_bound);

		}
		if(strcmp(yyvsp[-1].symbol.str,"#")==0) {
		node_type = REFERENCE_SEQUENCE_NO;
          Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);
		}
		printf("rule 122 %s %d\n",item_str,node_type);
		;
    break;}
case 45:
#line 407 "des2.y"
{printf("rule 123 %s %d item_type %d\n",yyvsp[-1].symbol.str,yyvsp[-1].symbol.val,item_type);
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
             Build_Hoare_Tree("%d %s %d",node_type,yyvsp[-1].symbol.str,tmp_indent);

		;
    break;}
case 47:
#line 431 "des2.y"
{printf("rule 124 %s %s %d indent %d\n",yyvsp[-2].symbol.str,yyvsp[-1].symbol.str,yyvsp[-2].symbol.val,tmp_indent);
		strcpy(item_str,yyvsp[-2].symbol.str);
		strcat(item_str,yyvsp[-1].symbol.str);
		printf("rule 124 %s %s %d indent %d\n",item_str,yyvsp[-1].symbol.str,item_val,tmp_indent);

		if(strcmp(yyvsp[-1].symbol.str, "*") ==0){
		if(item_val == REFER)
		node_type = REFERENCE_SEQUENCE;
		else if (item_val==MATCH)
		node_type = MATCH_SEQUENCE;
		printf("* SEQUENCE\n"); 
		sprintf(lower_bound,"0");
		sprintf(upper_bound,"%d",INT_MAX);
     Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent,lower_bound,upper_bound);

		}
		if(strcmp(yyvsp[-1].symbol.str, "+")==0) {
		if(item_val == REFER)
		node_type = REFERENCE_DISCRIMINATED_UNION;
		else
		node_type = MATCH_DISCRIMINATED_UNION;
		printf("* UNION\n"); 
        Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);

		}
		if(yyvsp[-1].symbol.val== RANGE){ 
		node_type = REFERENCE_SEQUENCE_RANGE;
		printf("range\n");
		printf("range\n");
     Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent,lower_bound,upper_bound);

		}
		if(strcmp(yyvsp[-1].symbol.str,"*+")==0){
		node_type = REFERENCE_SEQUENCE_UNION;
		sprintf(lower_bound,"0");
		sprintf(upper_bound,"%d",INT_MAX);
     Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent,lower_bound,upper_bound);

		}
		if(strcmp(yyvsp[-1].symbol.str,"#")==0) {
		node_type = REFERENCE_SEQUENCE_NO;
             Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);

		}
		printf("rule 124 %s %d\n",item_str,node_type);
		;
    break;}
case 49:
#line 481 "des2.y"
{printf("rule 14 %s\n",yyvsp[0].symbol.str);;
    break;}
case 50:
#line 483 "des2.y"
{printf("rule 14 \n");;
    break;}
case 51:
#line 485 "des2.y"
{printf("rule 143 \n");;
    break;}
case 52:
#line 489 "des2.y"
{printf("rule 13 \n");
		;
    break;}
case 53:
#line 492 "des2.y"
{printf("rule 13 \n");
		;
    break;}
case 54:
#line 495 "des2.y"
{
		strcpy(yyval.symbol.str , yyvsp[-1].symbol.str);
		strcat(yyval.symbol.str,  yyvsp[0].symbol.str);
		printf("rule 133 %s\n",yyval.symbol.str);
		;
    break;}
case 55:
#line 501 "des2.y"
{
		strcpy(yyval.symbol.str , yyvsp[-1].symbol.str);
		strcat(yyval.symbol.str,  yyvsp[0].symbol.str);
		printf("rule 134 %s\n",yyval.symbol.str);
		;
    break;}
case 56:
#line 507 "des2.y"
{printf("rule 135 %s\n",yyvsp[0].symbol.str);
		printf("token %s up %s low %s\n",yytext,upper_bound,lower_bound);
		if(upper_bound < lower_bound)
		  err("range error");
		;
    break;}
case 57:
#line 518 "des2.y"
{printf("rule 201 \n");
		;
    break;}
case 58:
#line 523 "des2.y"
{printf("rule 16 \n");
		;
    break;}
case 59:
#line 529 "des2.y"
{printf("rule 15 \n");
		
		;
    break;}
case 60:
#line 536 "des2.y"
{printf("rule 18 \n");
		item_val = yyvsp[0].symbol.val;
		strcpy(item_str,yyvsp[0].symbol.str);
		;
    break;}
case 61:
#line 543 "des2.y"
{printf("rule 18 \n");;
    break;}
case 62:
#line 545 "des2.y"
{printf("rule 184 \n");
		;
    break;}
case 63:
#line 550 "des2.y"
{
		item_val = yyvsp[0].symbol.val;
		strcpy(item_str,yyvsp[0].symbol.str);
		printf("rule 192 %d\n",yyvsp[0].symbol.val);
		printf("yylval %s %d  \n",yylval.symbol.str,yylval.symbol.val);
		printf("token %s\n",yytext);;
    break;}
case 64:
#line 557 "des2.y"
{
		yyerrok;
		printf("rule 17 \n");
		item_val = yyvsp[0].symbol.val;
		strcpy(item_str,yyvsp[0].symbol.str);
		;
    break;}
case 66:
#line 565 "des2.y"
{
		yyerrok;
		printf("rule 18 \n");
		item_val = yyvsp[0].symbol.val;
		strcpy(item_str,yyvsp[0].symbol.str);
		;
    break;}
case 69:
#line 578 "des2.y"
{
		item_type=yyvsp[0].symbol.type;
		item_val = yyvsp[0].symbol.val;
		;
    break;}
case 71:
#line 588 "des2.y"
{printf("rule 2 \n");;
    break;}
case 72:
#line 592 "des2.y"
{printf("rule 003 indent %d\n",indentation);
		item_type=yyvsp[-3].symbol.val;
		strcpy(item_str,yyvsp[-3].symbol.str);
		strcat(item_str,"(");
		strcat(item_str,yyvsp[-1].symbol.str);
		strcat(item_str,")");
		yyval.symbol.str=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy(yyval.symbol.str,item_str);
		;
    break;}
case 73:
#line 602 "des2.y"
{printf(" rule 0032\n");
		item_type=yyvsp[-3].symbol.val;
		strcat(item_str,yyvsp[-3].symbol.str);
		strcat(item_str,"(");
		strcat(item_str,yyvsp[-1].symbol.str);
		strcat(item_str,")");
		yyval.symbol.str=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy(yyval.symbol.str,item_str);
		;
    break;}
case 74:
#line 612 "des2.y"
{printf(" rule 0032\n");
		item_type=yyvsp[0].symbol.val;
		strcat(item_str,yyvsp[-4].symbol.str);
		strcat(item_str,"(");
		strcat(item_str,yyvsp[-2].symbol.str);
		strcat(item_str,")");
		strcat(item_str,yyvsp[0].symbol.str);
		yyval.symbol.str=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy(yyval.symbol.str,item_str);
		;
    break;}
case 75:
#line 626 "des2.y"
{printf("rule 0041 indent %d %d\n",indentation,tmp_indent);
		item_type=yyvsp[0].symbol.val;
		strcpy(item_str,"(");
		strcat(item_str,yyvsp[-2].symbol.str);
		strcat(item_str,")");
		strcat(item_str,yyvsp[0].symbol.str);
		yyval.symbol.str=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy(yyval.symbol.str,item_str);
		printf("rule 0041 %s %s\n",item_str,yyval.symbol.str);
		;
    break;}
case 76:
#line 637 "des2.y"
{printf("rule 0043 \n");
		item_type=yyvsp[0].symbol.val;
		strcat(item_str,"(");
		strcat(item_str,yyvsp[-2].symbol.str);
		strcat(item_str,")");
		strcat(item_str,yyvsp[0].symbol.str);
		yyval.symbol.str=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy(yyval.symbol.str,item_str);
		;
    break;}
case 77:
#line 647 "des2.y"
{printf("rule 0044 \n");
		strcat(item_str,"(");
		strcat(item_str,yyvsp[-1].symbol.str);
		strcat(item_str,")");
		yyval.symbol.str=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy(yyval.symbol.str,item_str);
		printf("rule 0044 %s %s\n",item_str,yyval.symbol.str);
		;
    break;}
case 79:
#line 660 "des2.y"
{ tmp_indent = wk_indent;
	;
    break;}
case 80:
#line 666 "des2.y"
{printf("rule 61 %d\n",indentation);
	wk_indent = indentation; 
		;
    break;}
case 81:
#line 670 "des2.y"
{ 
		wk_indent = indentation; 
		printf("rule 62 %d\n",indentation);;
    break;}
case 82:
#line 676 "des2.y"
{
		yyerrok;
		printf("rule 20 yylval %s %d  \n",yylval.symbol.str,yylval.symbol.val);
		printf("token %s\n",yytext);;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 465 "/home/local/lib/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 683 "des2.y"

#include "lex.yy.c"
yyerror()
{
   fprintf(stderr, "Error line no %d: \"%s\"\n",yylineno,yytext);
   sprintf(User_Msg,"Error line no %d: \"%s\"\n",yylineno,yytext);
   Display_Build_User_Msg(Rd_text_w,User_Msg);
   Error_Counter++;
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
