# include "stdio.h"
# define U(x) x
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# define YYLMAX BUFSIZ
# define output(c) putc(c,yyout)
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
# define ECHO fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng; extern char yytext[];
int yymorfg;
extern char *yysptr, yysbuf[];
int yytchar;
FILE *yyin = {stdin}, *yyout = {stdout};
extern int yylineno;
struct yysvf { 
	struct yywork *yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;
/*******************************************************************************
 * MODULE:	DES.L
 *
 * PURPOSE:	Lex specification for the lexical analyzer of the Descartes
 *		language processor.
 * $Date: 1994/04/14 22:49:18 $
 * $State: Exp $
 * $Locker:  $
 * $Source: /all/franklin/thesis/descartes/win/RCS/des.l,v $
 *
 ******************************************************************************/
#if 0
/******************************************************************************
 *
$Log: des.l,v $
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
static char     *des_l_rcsid = "@(#) $Id: des.l,v 1.5, h4_2_2 1994/04/14 22:49:18 franklin Exp $";

#include <stdlib.h>
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
	
# define YYNEWLINE 10
yylex(){
int nstr; extern int yyprevious;
	int i=0;
	int j=0;
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:
             {++indentation;yylval.ival = indentation; return(INDENT);}
break;
case 2:
          { printf("indent %d\n",indentation);indentation=0;
		NEWSTR(yytext,yylval.symbol.str); 
		return('\n');
		}
break;
case 3:
       {NEWSTR("return",yylval.symbol.str); 
		yylval.symbol.val = RETURN;
		printf("sym %s\n",yylval.symbol.str);
		return(RETURN);}
break;
case 4:
         {NEWSTR(yytext,yylval.symbol.str); 
		yylval.symbol.val = NEW_PAGE;
		return(NEW_PAGE);}
break;
case 5:
         {NEWSTR(yytext,yylval.symbol.str); 
		yylval.symbol.val = NEW_LINE;
		return(NEW_LINE);}
break;
case 6:
    {NEWSTR(yytext,yylval.symbol.str); 
		yylval.symbol.val = PARALLELS;
		yylval.symbol.type = PARALLELS;
		printf("PARALLEL sym %s\n",yylval.symbol.str);
		return(P_PARALLEL);}
break;
case 7:
      {NEWSTR(yytext,yylval.symbol.str);
		yylval.symbol.val = LITERALS;
		return(LITERALS); }
break;
case 8:
        {NEWSTR(yytext,yylval.symbol.str);
		yylval.symbol.val = MATCH;
		printf("MATCH sym %s %d\n",yylval.symbol.str,yylval.symbol.val);
		return(MATCH);  }
break;
case 9:
     {NEWSTR(yytext,yylval.symbol.str);
		yylval.symbol.val=lookup(CAP_C);
                printf("CAP sym %s %d\n",yylval.symbol.str,yylval.symbol.val);
		yylval.symbol.type = yylval.symbol.val;
		if(yylval.symbol.val==CAP_C)
		yylval.symbol.val=REFER;
              /*  return (yylval.symbol.type); */
                return (CAP_C);
		}
break;
case 10:
         {NEWSTR(yytext,yylval.symbol.str);
		yylval.symbol.val = REFER;
		printf("REFER sym %s %d\n",yylval.symbol.str,yylval.symbol.val);
		return(REFER);}
break;
case 11:
        {NEWSTR(yytext,yylval.symbol.str); 
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
		sprintf(upper_bound,"%d",0x7FFFFFFF);	
		yylval.symbol.val = RANGE;
		return(RANGE);}
break;
case 12:
             {yylval.symbol.str=yytext;
                 yylval.symbol.val=L_PAR; 
		printf("sym %s\n",yylval.symbol.str);
		 return(L_PAR); }
break;
case 13:
             {yylval.symbol.str=yytext;
                 yylval.symbol.val=R_PAR; 
		printf("sym %s\n",yylval.symbol.str);
		 return(R_PAR); }
break;
case 14:
             {NEWSTR(yytext,yylval.symbol.str); return('+'); }
break;
case 15:
             {NEWSTR(yytext,yylval.symbol.str); return('*'); }
break;
case 16:
             {NEWSTR(yytext,yylval.symbol.str);return('#'); }
break;
case -1:
break;
default:
fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */

yywrap()
{
  return(1);
}
int yyvstop[] = {
0,

1,
0,

2,
0,

16,
0,

12,
0,

13,
0,

15,
0,

14,
0,

10,
-9,
0,

10,
-9,
0,

10,
-9,
0,

8,
10,
-9,
0,

8,
0,

7,
0,

9,
0,

5,
10,
-9,
0,

4,
10,
-9,
0,

10,
-9,
0,

10,
-9,
0,

10,
-9,
0,

10,
-9,
0,

11,
0,

10,
-9,
0,

3,
0,

10,
-9,
0,

6,
10,
-9,
0,
0};
# define YYTYPE char
struct yywork { YYTYPE verify, advance; } yycrank[] = {
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,3,	1,4,	
4,4,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
1,5,	0,0,	0,0,	0,0,	
1,6,	1,7,	1,8,	1,9,	
1,10,	0,0,	30,33,	18,24,	
24,27,	7,18,	7,18,	7,18,	
7,18,	7,18,	7,18,	7,18,	
7,18,	7,18,	7,18,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,11,	1,11,	
1,11,	1,11,	1,11,	1,11,	
1,11,	1,11,	1,11,	1,11,	
1,11,	1,11,	1,11,	1,12,	
1,11,	1,13,	1,11,	1,11,	
1,11,	1,11,	1,11,	1,11,	
1,11,	1,11,	1,11,	1,11,	
13,22,	12,20,	22,25,	25,28,	
1,14,	12,21,	1,15,	1,15,	
1,15,	1,15,	1,15,	1,15,	
1,15,	1,15,	1,15,	1,15,	
1,15,	1,15,	1,15,	1,15,	
1,15,	1,15,	1,15,	1,15,	
1,15,	1,15,	1,15,	1,15,	
1,15,	1,15,	1,15,	1,15,	
3,16,	6,6,	16,23,	23,26,	
26,29,	27,30,	28,31,	29,32,	
31,34,	6,6,	6,0,	32,35,	
34,36,	36,37,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	27,30,	27,30,	27,30,	
27,30,	27,30,	27,30,	27,30,	
27,30,	27,30,	27,30,	0,0,	
6,6,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	6,17,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
6,6,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	6,6,	6,6,	0,0,	
0,0,	6,6,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
6,6,	0,0,	6,6,	0,0,	
6,6,	0,0,	6,6,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	11,19,	11,19,	6,6,	
0,0,	6,6,	0,0,	0,0,	
0,0,	6,6,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	6,6,	0,0,	
0,0,	0,0,	6,6,	0,0,	
6,6,	6,6,	11,11,	11,11,	
11,11,	11,11,	11,11,	11,11,	
11,11,	11,11,	11,11,	11,11,	
11,11,	11,11,	11,11,	11,11,	
11,11,	11,11,	11,11,	11,11,	
11,11,	11,11,	11,11,	11,11,	
11,11,	11,11,	11,11,	11,11,	
0,0,	0,0,	0,0,	14,14,	
11,11,	14,15,	14,15,	14,15,	
14,15,	14,15,	14,15,	14,15,	
14,15,	14,15,	14,15,	14,15,	
14,15,	14,15,	14,15,	14,15,	
14,15,	14,15,	14,15,	14,15,	
14,15,	14,15,	14,15,	14,15,	
14,15,	14,15,	14,15,	15,15,	
0,0,	15,15,	15,15,	15,15,	
15,15,	15,15,	15,15,	15,15,	
15,15,	15,15,	15,15,	15,15,	
15,15,	15,15,	15,15,	15,15,	
15,15,	15,15,	15,15,	15,15,	
15,15,	15,15,	15,15,	15,15,	
15,15,	15,15,	15,15,	0,0,	
0,0};
struct yysvf yysvec[] = {
0,	0,	0,
yycrank+1,	0,		0,	
yycrank+0,	yysvec+1,	0,	
yycrank+10,	0,		yyvstop+1,
yycrank+2,	0,		yyvstop+3,
yycrank+0,	0,		yyvstop+5,
yycrank+-124,	0,		0,	
yycrank+1,	0,		yyvstop+7,
yycrank+0,	0,		yyvstop+9,
yycrank+0,	0,		yyvstop+11,
yycrank+0,	0,		yyvstop+13,
yycrank+177,	0,		yyvstop+15,
yycrank+17,	yysvec+11,	yyvstop+18,
yycrank+27,	yysvec+11,	yyvstop+21,
yycrank+176,	yysvec+11,	yyvstop+24,
yycrank+204,	0,		yyvstop+28,
yycrank+25,	0,		0,	
yycrank+0,	0,		yyvstop+30,
yycrank+1,	yysvec+7,	0,	
yycrank+0,	0,		yyvstop+32,
yycrank+0,	yysvec+11,	yyvstop+34,
yycrank+0,	yysvec+11,	yyvstop+38,
yycrank+12,	yysvec+11,	yyvstop+42,
yycrank+11,	0,		0,	
yycrank+2,	0,		0,	
yycrank+30,	yysvec+11,	yyvstop+45,
yycrank+11,	0,		0,	
yycrank+97,	0,		0,	
yycrank+54,	yysvec+11,	yyvstop+48,
yycrank+17,	0,		0,	
yycrank+5,	0,		0,	
yycrank+56,	yysvec+11,	yyvstop+51,
yycrank+25,	0,		0,	
yycrank+0,	0,		yyvstop+54,
yycrank+67,	yysvec+11,	yyvstop+56,
yycrank+0,	0,		yyvstop+59,
yycrank+61,	yysvec+11,	yyvstop+61,
yycrank+0,	yysvec+11,	yyvstop+64,
0,	0,	0};
struct yywork *yytop = yycrank+326;
struct yysvf *yybgin = yysvec+1;
char yymatch[] = {
00  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,011 ,012 ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
040 ,01  ,01  ,01  ,01  ,01  ,01  ,047 ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,
'0' ,'0' ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,'A' ,'B' ,'B' ,'B' ,'E' ,'B' ,'B' ,
'B' ,'B' ,'B' ,'B' ,'L' ,'B' ,'N' ,'B' ,
'P' ,'B' ,'R' ,'B' ,'B' ,'B' ,'B' ,'B' ,
'B' ,'B' ,'B' ,01  ,01  ,01  ,01  ,'_' ,
01  ,'a' ,'a' ,'a' ,'a' ,'e' ,'a' ,'a' ,
'a' ,'a' ,'a' ,'a' ,'a' ,'a' ,'n' ,'a' ,
'a' ,'a' ,'r' ,'a' ,'t' ,'u' ,'a' ,'a' ,
'a' ,'a' ,'a' ,01  ,01  ,01  ,01  ,01  ,
0};
char yyextra[] = {
0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
#ifndef lint
static	char ncform_sccsid[] = "@(#)ncform 1.6 88/02/08 SMI"; /* from S5R2 1.2 */
#endif

int yylineno =1;
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
char yytext[YYLMAX];
struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
char yysbuf[YYLMAX];
char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
yylook(){
	register struct yysvf *yystate, **lsp;
	register struct yywork *yyt;
	struct yysvf *yyz;
	int yych, yyfirst;
	struct yywork *yyr;
# ifdef LEXDEBUG
	int debug;
# endif
	char *yylastch;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
	yyfirst=1;
	if (!yymorfg)
		yylastch = yytext;
	else {
		yymorfg=0;
		yylastch = yytext+yyleng;
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
# ifdef LEXDEBUG
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
# endif
			yyt = yystate->yystoff;
			if(yyt == yycrank && !yyfirst){  /* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == yycrank)break;
				}
			*yylastch++ = yych = input();
			yyfirst=0;
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( (int)yyt > (int)yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if((int)yyt < (int)yycrank) {		/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"compressed state\n");
# endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt= yystate->yystoff) != yycrank){
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
				yyleng = yylastch-yytext+1;
				yytext[yyleng] = 0;
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"\nmatch ");
					sprint(yytext);
					fprintf(yyout," action %d\n",*yyfnd);
					}
# endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
		if (yytext[0] == 0  /* && feof(yyin) */)
			{
			yysptr=yysbuf;
			return(0);
			}
		yyprevious = yytext[0] = input();
		if (yyprevious>0)
			output(yyprevious);
		yylastch=yytext;
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}
yyback(p, m)
	int *p;
{
if (p==0) return(0);
while (*p)
	{
	if (*p++ == m)
		return(1);
	}
return(0);
}
	/* the following are only used in the lex library */
yyinput(){
	return(input());
	}
yyoutput(c)
  int c; {
	output(c);
	}
yyunput(c)
   int c; {
	unput(c);
	}
