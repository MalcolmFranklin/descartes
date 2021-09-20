#ifndef NEED_BEFORE_YTAB_H
#define NEED_BEFORE_YTAB_H	1

/* The following struct is an element of the yacc YYSTYPE union.
 * It has to be included befor y.tab.h, because there is no way to define
 * code which will precede the definition of YYSTYPE in y.tab.h.
 */
typedef struct node {
	int val;
	int type;
	char *str;
}NODE;

extern char yytext[];

#endif /* NEED_BEFORE_YTAB_H */
