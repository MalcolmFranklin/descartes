#ifndef NEED_BEFORE_YTAB_H
#define NEED_BEFORE_YTAB_H	1
/*******************************************************************************
 * HEADER:	NEED_BEFORE_YTAB.H
 *
 * PURPOSE:	Provide the definition of type NODE, which is used as an
 *		element of the YACC-generated union YYSTYPE.  It has to be in
 *		this seperate header, because there is no other way to make
 *		it appear prior to the definition of YYSTYPE.
 *
 *		Also, declare "yylineno" so that it can be reset to 1
 *		between each call to yyparse().  If you do not reset this
 *		counter, yyerror() will not report the correct line number
 *		in error messages.
 *
 * AUTHOR:	Malcolm L. Franklin, Arizona State University.
 *******************************************************************************
 * $Date: 1994/08/03 21:59:39 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/need_before_ytab.h,v $
 *
 ******************************************************************************/

#if 0
/******************************************************************************
 *
$Log: need_before_ytab.h,v $
 * Revision 1.4  1994/08/03  21:59:39  franklin
 * Changed "str" to "pstr"; prefix "str" is reserved by string.h
 *
 * Revision 1.3  1994/06/30  23:28:09  franklin
 * Declare yylineno in this header, so that you can reset it ot
 * 1 between each call to yyparse().  (Reset before you read/reread
 * an input specification).
 * If you do not reset yylineno, then you wont get the correct line
 * number in error messages.
 *
 * Revision 1.2  1994/05/17  00:06:33  franklin
 * Only declare yytext[] if the user passes -DUSE_BISON to the compiler.
 *
 * Revision 1.1  1994/05/13  02:40:46  franklin
 * Initial revision
 *
 ******************************************************************************/
#endif
static char    *need_before_ytab_h_rcsid = "@(#) $Id: need_before_ytab.h,v 1.4, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3 1994/08/03 21:59:39 franklin Exp $";

/*
 * The following struct is an element of the yacc YYSTYPE union. It has to be
 * included befor y.tab.h, because there is no way to define code which will
 * precede the definition of YYSTYPE in y.tab.h.
 */
typedef struct node
{
	int             val;
	int             type;
	char           *pstr;
}               NODE;

/*
 * You will need the following declaration of yytext if you use Bison to
 * process des2.y.
 */

#ifdef USE_BISON
extern char     yytext[];

#endif

/* Reset this line counter before calling yyparse(). */
extern int      yylineno;

#endif				       /* NEED_BEFORE_YTAB_H */
