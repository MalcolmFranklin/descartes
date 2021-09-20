%{
/*******************************************************************************
 * MODULE:	DES.L
 *
 * PURPOSE:	Lex specification for the lexical analyzer of the Descartes
 *		language processor.
 * $Date: 1994/08/03 22:02:14 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/des.l,v $
 *
 ******************************************************************************/
#if 0
/******************************************************************************
 *
$Log: des.l,v $
 * Revision 1.8  1994/08/03  22:02:14  franklin
 * Replace hardcoded constant 0x7FFFFFFF with INT_MAX from <limits.h>.
 *
 * Revision 1.7  1994/08/03  21:59:24  franklin
 * Changed "str" to "pstr"; prefix "str" is reserved by string.h
 *
 * Revision 1.6  1994/05/13  02:50:11  franklin
 * Does not need y.tab.h
 *
 * Revision 1.5  1994/04/14  22:49:18  franklin
 * You cannot suppress the warning about "share_rtn_h_rcsid" not used, without
 * turning off all such warnings in a module which #includes this file.
 * Live with the message.
 *
 * Revision 1.4  1994/04/14  18:31:41  franklin
 * Add module header and RCS tokens.
 *
 ******************************************************************************/
#endif
static char     *des_l_rcsid = "@(#) $Id: des.l,v 1.8, h4_3_8, h4_3_7, h4_3_6, h4_3_5, h4_3_4, h4_3_3 1994/08/03 22:02:14 franklin Exp $";

#include <stdlib.h>
#include <limits.h>
#include <stdio.h> 
#define ALLOC(x,s,t) do { x=(t)calloc(1,(s)); \
	if (x==0) { \
	printf("memory allocation failed\n"); \
	exit(1); } } while(0)

#define BCOPY(from,to,size) memcpy(to,from,size)

#define NEWSTR(from,to) do { int len=strlen(from); \
		ALLOC(to,len+1,char *); \
		BCOPY(from,to,len+1); \
		} while(0)
#define token(x)  x
%}
Return         [\t][r][e][t][u][r][n]
parallel	[P][A][R][A][L][L][E][L]
upletter       [_A-Z]
ws             [ ]
lowletter      [_a-z]
letter         [ /._A-Za-z]
digit          [0-9]
digset         {digit}+
char           {letter}+{digit}*
literal        \'[^\'\n]*\'
range          \({digit}+".""."({digit}|{ws})\)
up_case_id     {upletter}+
low_case_id    {lowletter}+
cap_char        {up_case_id}/(\(|\))
refer          {up_case_id} 
match          {low_case_id}
indent1         [\t]+/({letter}|\')
indent         [\t]
	
%%
		int i=0;
		int j=0;
\t              {++indentation;yylval.ival = indentation; return(INDENT);}
[\n]+           { printf("indent %d\n",indentation);indentation=0;
		NEWSTR(yytext,yylval.symbol.pstr); 
		return('\n');
		}

{Return}        {NEWSTR("return",yylval.symbol.pstr); 
		yylval.symbol.val = RETURN;
		printf("sym %s\n",yylval.symbol.pstr);
		return(RETURN);} 

[N][P]          {NEWSTR(yytext,yylval.symbol.pstr); 
		yylval.symbol.val = NEW_PAGE;
		return(NEW_PAGE);} 

[N][L]          {NEWSTR(yytext,yylval.symbol.pstr); 
		yylval.symbol.val = NEW_LINE;
		return(NEW_LINE);} 

{parallel}     {NEWSTR(yytext,yylval.symbol.pstr); 
		yylval.symbol.val = PARALLELS;
		yylval.symbol.type = PARALLELS;
		printf("PARALLEL sym %s\n",yylval.symbol.pstr);
		return(P_PARALLEL);} 

{literal}       {NEWSTR(yytext,yylval.symbol.pstr);
		yylval.symbol.val = LITERALS;
		return(LITERALS); }

{match}         {NEWSTR(yytext,yylval.symbol.pstr);
		yylval.symbol.val = MATCH;
		printf("MATCH sym %s %d\n",yylval.symbol.pstr,yylval.symbol.val);
		return(MATCH);  }

{cap_char}      {NEWSTR(yytext,yylval.symbol.pstr);
		yylval.symbol.val=lookup(CAP_C);
                printf("CAP sym %s %d\n",yylval.symbol.pstr,yylval.symbol.val);
		yylval.symbol.type = yylval.symbol.val;
		if(yylval.symbol.val==CAP_C)
		yylval.symbol.val=REFER;
              /*  return (yylval.symbol.type); */
                return (CAP_C);
		}


{refer}         {NEWSTR(yytext,yylval.symbol.pstr);
		yylval.symbol.val = REFER;
		printf("REFER sym %s %d\n",yylval.symbol.pstr,yylval.symbol.val);
		return(REFER);}

{range}         {NEWSTR(yytext,yylval.symbol.pstr); 
		i=1;
		printf("low_ %c\n",yytext[i]);
		while(yytext[i]!='.') {
			lower_bound[i-1] = yytext[i];
			i++;
		}
		lower_bound[i]='\0';
		i=i+2;
		j=0;
		printf("up_ %c\n",yytext[i]);
		while(yytext[i]!=')'){
			if(yytext[i] != ' '){
			upper_bound[j]=yytext[i];
			j++;
			}
			i++;
		}
		upper_bound[j]='\0';
		if(upper_bound[0]=='\0')
		sprintf(upper_bound,"%d",INT_MAX);	
		yylval.symbol.val = RANGE;
		return(RANGE);}

"("              {yylval.symbol.pstr=yytext;
                 yylval.symbol.val=L_PAR; 
		printf("sym %s\n",yylval.symbol.pstr);
		 return(L_PAR); }

")"              {yylval.symbol.pstr=yytext;
                 yylval.symbol.val=R_PAR; 
		printf("sym %s\n",yylval.symbol.pstr);
		 return(R_PAR); }

"+"              {NEWSTR(yytext,yylval.symbol.pstr); return('+'); }

"*"              {NEWSTR(yytext,yylval.symbol.pstr); return('*'); }

"#"              {NEWSTR(yytext,yylval.symbol.pstr);return('#'); }
%%

yywrap()
{
  return(1);
}
