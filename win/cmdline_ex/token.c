/*******************************************************************************
 * MODULE:	TOKEN.C
 *
 * $Date: 1994/08/04 22:38:15 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/cmdline_ex/RCS/token.c,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: token.c,v $
 * Revision 1.12  1994/08/04  22:38:15  franklin
 * Add #includes for cchk_missing_<standard include>.h in order
 * to get prototypes that CodeCheck doesnt think are there.
 *
 * Revision 1.11  1994/08/04  17:05:36  franklin
 * Changed token_yylex -> ttoken_yylex; prefix "to" is reserved by ctype.h
 *
 * Revision 1.10  1994/08/04  16:47:38  franklin
 * Changed token -> ttoken; prefix "to" is reserved by ctype.h
 *
 * Revision 1.9  1994/08/02  13:35:44  franklin
 * EQUAL -> ISEQUAL (E prefix is reserved by ANSI)
 *
 * Revision 1.8  1994/06/02  17:24:42  franklin
 * Enable stricter type checking when running the CenterLine "clcc" in
 * K&R compatibility mode (-Xa switch) by re-defining __STDC__ after processing
 * the non-ansi SunOS system include files.
 *
 * Revision 1.7  1994/05/17  00:08:27  franklin
 * Port to HP-UX
 *
 * Revision 1.6  1994/05/13  13:46:32  franklin
 * Change definition of yytext[] to a declaration.
 *
 * Revision 1.5  1994/05/13  02:52:58  franklin
 * Include need_before_ytab.h before y.tab.h.
 *
 * Revision 1.4  1994/05/02  17:24:42  franklin
 * Remove nested includes in desc_struct.h,  include unistd.h
 * and sys/stat.h here.
 *
 * Revision 1.3  1994/04/23  16:30:51  franklin
 * Get definition of strcmp() from string.h
 *
 * Revision 1.2  1994/04/08  03:41:27  franklin
 * Run through SunOS 4.1.3 "indent", and make ANSI compliant.
 *
 ******************************************************************************/
#endif
static char    *rcsid = "@(#) $Id: token.c,v 1.12, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3 1994/08/04 22:38:15 franklin Exp $";

#include <stdlib.h>
#include "cchk_missing_stdlib.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>		       /* Required by desc_struct.h */
#include "cchk_missing_unistd.h"       /* Workaround for Spurious CodeCheck diagnostic messages. */
#include <sys/stat.h>		       /* Required by desc_struct.h */
/******************************************************************************
 * NOTE TO FUTURE MAINTAINERS USING CenterLine "clcc" COMPILER:
 *
 * Nearly all the SunOS 4.x Operating System include files (<sys/xxx.h>)
 * cause compilation errors under a strict ANSI/ISO compiler running in anal-
 * retentive mode such as CenterLine "clcc".  In order to get these to compile,
 * with clcc, you have to pass the  -Xa (K&R C compatibility switch) to the
 * compiler.  BUT (get this) when we do this, the CenterLine preprocessor
 * #defines __STDC__ to 0 (zero); when this happens, we dont see the vararg
 * prototypes for the X functions -- and get warning messages for calling them
 * with different numbers of arguments.  On top of all this noise, we DONT GET
 * all the ANSI/ISO C type checking that we could have.
 *
 * WORKAROUND:
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

#include "need_before_ytab.h"	       /* Definition of type NODE.  NODE is an element of the YYSTYPE union.  yylval is of type
				        * YYSTYPE. */

#include "y.tab.h"
#include "desc_struct.h"

/******************************************************************************
 * DEFINES
 *****************************************************************************/
#define ttoken(x) x

/******************************************************************************
 * GLOBAL: YYTEXT
 *****************************************************************************/
extern char     yytext[];


/******************************************************************************
 * GLOBAL KEYTABLE
 *	an array of keyword structs.
 *****************************************************************************/
static struct keyword
{
	char           *name;
	int             ttoken_yylex;
}               keytable[] =

{

	"_PLUS_", ttoken (PLUS),
	"_MINUS_", ttoken (MINUS),
	"_TIMES_", ttoken (TIMES),
	"_RAISED_TO_", ttoken (RAISED_TO),
	"_DIVIDED_BY_", ttoken (DIVIDED_BY),
	"_EQUAL_", ttoken (ISEQUAL),
	"_NOT_EQUAL_", ttoken (NOT_EQUAL),
	"_LESS_THAN_OR_EQUAL_", ttoken (LESS_THAN_OR_EQUAL),
	"_LESS_THAN_", ttoken (LESS_THAN),
	"_GREATER_THAN_OR_EQUAL_", ttoken (GREATER_THAN_OR_EQUAL),
	"_GREATER_THAN_", ttoken (GREATER_THAN),
	"_OR_", ttoken (OR),
	"_AND_", ttoken (AND),
	"NOT_", ttoken (NOT),
	"_SEND_TO_", ttoken (SEND_TO),
	"RECEIVE_FROM_", ttoken (RECEIVE_FROM),
	"_ASEND_TO_", ttoken (ASEND_TO),
	"ARECEIVE_FROM_", ttoken (ARECEIVE_FROM),
	"DELAY_", ttoken (DELAYS),
	"TIMER_", ttoken (TIMER),
	"GTIME_", ttoken (GET_TIME),
	0, 0
};


/******************************************************************************
 * FUNCTION: LOOKUP
 *****************************************************************************/
int             lookup (t)
	int             t;
{
	register struct keyword *p;

	p = keytable;

	while (p->name)
		if (!strcmp (yytext, p->name))
		{
			return (p->ttoken_yylex);
		}
		else
			p++;
	return t;
}
