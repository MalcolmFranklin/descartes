/*******************************************************************************
 * MODULE:	TOKEN.C
 *
 * $Date: 1994/05/02 17:24:42 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/token.c,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: token.c,v $
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
static char    *rcsid = "@(#) $Id: token.c,v 1.4 1994/05/02 17:24:42 franklin Exp $";

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>		       /* Required by desc_struct.h */
#include <sys/stat.h>		       /* Required by desc_struct.h */
#include "need_before_ytab.h"	       /* Definition of type NODE.  NODE is an element of the YYSTYPE union.  yylval is of type
				        * YYSTYPE. */

#include "y.tab.h"
#include "desc_struct.h"

/******************************************************************************
 * DEFINES
 *****************************************************************************/
#define token(x) x

/******************************************************************************
 * GLOBAL: YYTEXT
 *****************************************************************************/
char            yytext[];


/******************************************************************************
 * GLOBAL KEYTABLE
 *	an array of keyword structs.
 *****************************************************************************/
static struct keyword
{
	char           *name;
	int             token_yylex;
}               keytable[] =

{

	"_PLUS_", token (PLUS),
	"_MINUS_", token (MINUS),
	"_TIMES_", token (TIMES),
	"_RAISED_TO_", token (RAISED_TO),
	"_DIVIDED_BY_", token (DIVIDED_BY),
	"_EQUAL_", token (EQUAL),
	"_NOT_EQUAL_", token (NOT_EQUAL),
	"_LESS_THAN_OR_EQUAL_", token (LESS_THAN_OR_EQUAL),
	"_LESS_THAN_", token (LESS_THAN),
	"_GREATER_THAN_OR_EQUAL_", token (GREATER_THAN_OR_EQUAL),
	"_GREATER_THAN_", token (GREATER_THAN),
	"_OR_", token (OR),
	"_AND_", token (AND),
	"NOT_", token (NOT),
	"_SEND_TO_", token (SEND_TO),
	"RECEIVE_FROM_", token (RECEIVE_FROM),
	"_ASEND_TO_", token (ASEND_TO),
	"ARECEIVE_FROM_", token (ARECEIVE_FROM),
	"DELAY_", token (DELAYS),
	"TIMER_", token (TIMER),
	"GTIME_", token (GET_TIME),
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
			return (p->token_yylex);
		}
		else
			p++;
	return t;
}
