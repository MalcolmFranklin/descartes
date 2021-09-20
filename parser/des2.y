%{
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


%}

%union{
        int ival;
        NODE symbol;
}


%start modules
%token <symbol>   NEW_LINE NEW_PAGE  RETURN R_PAR  L_PAR INDENT
%token <symbol> RANGE LITERALS REFER MATCH CAP_C 
%token <symbol> P_PLUS P_MINUS P_TIMES P_DIVIDED_BY P_RAISED_TO
%token <symbol> P_EQUAL P_NOT_EQUAL P_GREATER_THAN P_LESS_THAN 
%token <symbol> P_GREATER_THAN_OR_EQUAL P_LESS_THAN_OR_EQUAL
%token <symbol> P_OR P_AND P_NOT
%token <symbol> P_PARALLEL P_CONCUR P_EQUAL_TO P_TIMER P_SEND_TO P_RECEIVE_FROM 
%token <symbol> P_DELAY P_ASEND_TO P_ARECEIVE_FROM  P_GTIME
%type <symbol> node_name module_call para non_argu_prim return hoare_tree 
%type <symbol>  module_title hoare_trees
%type <symbol> t_node_name  module_name nls name_seq  cap_char
%type <symbol>  module_node m_name_seq m_name_sequence primitives analysis_tree
%type <symbol> operators operator sequen disc_union  sequence_no name_sequence
%type <symbol> input_def_sec output_def_sec syn_tree_set node_set
%type <symbol> Indent
%%
modules : module
		{printf("rule 0 \n");
		}

	|modules module
		{printf("rule 01 \n");
		}
	;

module : module_name nls hoare_trees 
		{printf("rule 1 \n");
		tmp_indent=0;
		}
	| error nls hoare_trees 
	;
hoare_trees : hoare_tree
	| hoare_trees hoare_tree
	;

hoare_tree : input_def_sec 
	| output_def_sec
	;

nls : '\n'
	{
	printf("rule 30 new line\n");
	}
	;

t_node_name : cap_char
	|  LITERALS
	 
		{
		printf("rule 193 yylval %s %d  \n",yylval.symbol.str,yylval.symbol.val);
		printf("token %s\n",yytext);}
	|module_call
	;

module_name  :  name_sequence 
		{
		if(tmp_indent==0){
		node_type=MODULE_TITLE;
		} else 
		node_type=REFERENCE_DIRECT_PRODUCT;
             Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);
		}
	|	name_seq
		{printf("rule 2 \n");
		if(tmp_indent==0){
		node_type=MODULE_TITLE;
		printf("rule 31 %s indent %d %d\n",item_str,indentation,tmp_indent);
         Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);
		} else 
		node_type=REFERENCE_DIRECT_PRODUCT;
		}
	| REFER  
		{
		node_type=MODULE_TITLE;
		strcpy(item_str,$1.str);
             Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);

		}
	;

name_sequence : cap_char L_PAR cap_char R_PAR  
		{printf("rule 3 indent %d\n",indentation);
		strcpy(item_str,$1.str);
		strcat(item_str,"(");
		strcat(item_str,$3.str);
		strcat(item_str,")");
		$$.str=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy($$.str,item_str);

		}
	| cap_char L_PAR cap_char error  
		{err("Parithesis errror");
		}
	| name_sequence cap_char L_PAR cap_char R_PAR  
		{printf(" rule 32\n");
		strcat(item_str,$2.str);
		strcat(item_str,"(");
		strcat(item_str,$4.str);
		strcat(item_str,")");
		}
	
	| name_sequence cap_char L_PAR cap_char error  
	| name_sequence cap_char L_PAR cap_char R_PAR cap_char 
		{printf(" rule 33\n");
		strcat(item_str,$2.str);
		strcat(item_str,"(");
		strcat(item_str,$4.str);
		strcat(item_str,")");
		strcat(item_str,$6.str);
		}
	;

name_seq	: L_PAR cap_char R_PAR cap_char  
		{printf("rule 31 indent %d %d\n",indentation,tmp_indent);
		strcpy(item_str,"(");
		strcat(item_str,$2.str);
		strcat(item_str,")");
		strcat(item_str,$4.str);
		$$.str=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy($$.str,item_str);
		}
	|  L_PAR cap_char error  cap_char 
	| name_seq L_PAR cap_char R_PAR cap_char  
		{printf("rule 33 \n");
		strcat(item_str,"(");
		strcat(item_str,$3.str);
		strcat(item_str,")");
		strcat(item_str,$5.str);
		}
	| name_seq L_PAR cap_char error cap_char  
	| name_seq L_PAR cap_char R_PAR   
		{printf("rule 33 \n");
		strcat(item_str,"(");
		strcat(item_str,$3.str);
		strcat(item_str,")");
		}
	| name_seq L_PAR cap_char error   
	;


para :  INDENT REFER nls 
		{printf("rule 4 indent %d\n",indentation);
		node_type=REFERENCE_DIRECT_PRODUCT;
               Build_Hoare_Tree("%d %s %d",node_type,$2.str,1);

		}
	|  INDENT error nls 
	|  INDENT REFER error 
	;



input_def_sec : analysis_tree 
		{printf("rule 7 \n");}
	| input_def_sec analysis_tree
		{printf("rule 71 \n");}
	;

analysis_tree : para  node_set 
		{printf("rule 8 \n");
		}
	;

output_def_sec : return  syn_tree_set
		{printf("rule 10 indent%d\n",indentation);
		}
	;

syn_tree_set : node_set 
		{printf("rule 11 \n");}
	| syn_tree_set node_set  
		{printf("rule 11 \n");}
	;


return :	 RETURN nls
		{
		printf("rule 101 indent%d\n",indentation);
		node_type = MATCH_DIRECT_PRODUCT;
             Build_Hoare_Tree("%d %s %d",node_type,$1.str,1);

		}
	| RETURN operators nls
		{printf("rule 102 %s %s indent%d\n",$1.str,$2.str,indentation);
		strcpy(item_str,$1.str);
		strcat(item_str,$2.str);
		if(strcmp($2.str, "*") ==0){
		node_type = MATCH_SEQUENCE;
		printf("* SEQUENCE\n"); 
		sprintf(lower_bound,"0");
		sprintf(upper_bound,"%d",INT_MAX);
   Build_Hoare_Tree("%d %s %d",node_type,item_str,1,lower_bound,upper_bound);

		}
		if(strcmp($2.str, "+")==0) {
		node_type = MATCH_DISCRIMINATED_UNION;
		printf("* UNION\n"); 
             Build_Hoare_Tree("%d %s %d",node_type,item_str,1);

		}
		if($2.val== RANGE) {
		node_type = MATCH_SEQUENCE_RANGE;
             Build_Hoare_Tree("%d %s %d",node_type,item_str,1,lower_bound,upper_bound);

		}
		if(strcmp($2.str,"*+")==0) {
		node_type = MATCH_SEQUENCE_UNION;
		sprintf(lower_bound,"0");
		sprintf(upper_bound,"%d",INT_MAX);
         Build_Hoare_Tree("%d %s %d",node_type,item_str,1,lower_bound,upper_bound);

		}
		}
	| RETURN error nls
		{
		err("wrong operator");
		}
	| INDENT MATCH nls
		{
		node_type=MATCH_DIRECT_PRODUCT;
		printf("rule 10 %s indent%d\n",$2.str,indentation);
            Build_Hoare_Tree("%d %s %d",node_type,$2.str,1);

		}
	| INDENT error nls
	;

node_set : Indent node_name nls 
		{printf("rule 121 %s %d item_type%d\n",$2.str,$2.val,item_type);
		printf("rule 121 %s %d indent%d\n",item_str,item_val,tmp_indent);
		if(($2.val== REFER)&&(item_type==0))
		node_type=REFERENCE_DIRECT_PRODUCT;
		else if(($2.val == MATCH)&&(item_type==0))
		node_type = MATCH_DIRECT_PRODUCT;
		else if(($2.val == LITERALS)&&(item_type==0))
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
              Build_Hoare_Tree("%d %s %d",node_type,$2.str,tmp_indent);
		}
	| Indent error nls
	| Indent node_name operators  nls
		{printf("rule 122 %s %s %d indent%d\n",$2.str,$3.str,$2.val,tmp_indent);
		strcpy(item_str,$2.str);
		strcat(item_str,$3.str);
		printf("rule 122 %s %s %d indent%d\n",item_str,$3.str,item_val,tmp_indent);

		if(strcmp($3.str, "*") ==0){
		if(item_val== REFER)
		node_type = REFERENCE_SEQUENCE;
		else
		node_type = MATCH_SEQUENCE;
		printf("* SEQUENCE\n"); 
		sprintf(lower_bound,"0");
		sprintf(upper_bound,"%d",INT_MAX);
               Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent,lower_bound,upper_bound);

		}
		if(strcmp($3.str, "+")==0) {
		if(item_val == REFER)
		node_type = REFERENCE_DISCRIMINATED_UNION;
		else
		node_type = MATCH_DISCRIMINATED_UNION;
		printf("* UNION\n"); 
            Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);

		}
		if($3.val== RANGE) {
		node_type = REFERENCE_SEQUENCE_RANGE;
               Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent,lower_bound,upper_bound);

		}
		if(strcmp($3.str,"*+")==0) {
		node_type = REFERENCE_SEQUENCE_UNION;
		sprintf(lower_bound,"0");
		sprintf(upper_bound,"%d",INT_MAX);
               Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent,lower_bound,upper_bound);

		}
		if(strcmp($3.str,"#")==0) {
		node_type = REFERENCE_SEQUENCE_NO;
          Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);
		}
		printf("rule 122 %s %d\n",item_str,node_type);
		}
	| Indent error operators  nls
	|  node_set Indent node_name nls
		{printf("rule 123 %s %d item_type %d\n",$3.str,$3.val,item_type);
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
             Build_Hoare_Tree("%d %s %d",node_type,$3.str,tmp_indent);

		}
	|  node_set Indent error nls
	| node_set Indent  node_name operators nls
		{printf("rule 124 %s %s %d indent %d\n",$3.str,$4.str,$3.val,tmp_indent);
		strcpy(item_str,$3.str);
		strcat(item_str,$4.str);
		printf("rule 124 %s %s %d indent %d\n",item_str,$4.str,item_val,tmp_indent);

		if(strcmp($4.str, "*") ==0){
		if(item_val == REFER)
		node_type = REFERENCE_SEQUENCE;
		else if (item_val==MATCH)
		node_type = MATCH_SEQUENCE;
		printf("* SEQUENCE\n"); 
		sprintf(lower_bound,"0");
		sprintf(upper_bound,"%d",INT_MAX);
     Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent,lower_bound,upper_bound);

		}
		if(strcmp($4.str, "+")==0) {
		if(item_val == REFER)
		node_type = REFERENCE_DISCRIMINATED_UNION;
		else
		node_type = MATCH_DISCRIMINATED_UNION;
		printf("* UNION\n"); 
        Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);

		}
		if($4.val== RANGE){ 
		node_type = REFERENCE_SEQUENCE_RANGE;
		printf("range\n");
		printf("range\n");
     Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent,lower_bound,upper_bound);

		}
		if(strcmp($4.str,"*+")==0){
		node_type = REFERENCE_SEQUENCE_UNION;
		sprintf(lower_bound,"0");
		sprintf(upper_bound,"%d",INT_MAX);
     Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent,lower_bound,upper_bound);

		}
		if(strcmp($4.str,"#")==0) {
		node_type = REFERENCE_SEQUENCE_NO;
             Build_Hoare_Tree("%d %s %d",node_type,item_str,tmp_indent);

		}
		printf("rule 124 %s %d\n",item_str,node_type);
		}
	| node_set Indent  error operators nls
	;

operators : operator
		{printf("rule 14 %s\n",$1.str);}
	| operator sequence_no 
		{printf("rule 14 \n");}
	| sequence_no 
		{printf("rule 143 \n");}
	;

operator : disc_union 
		{printf("rule 13 \n");
		}
	| sequen 
		{printf("rule 13 \n");
		}
	| sequen disc_union
		{
		strcpy($$.str , $1.str);
		strcat($$.str,  $2.str);
		printf("rule 133 %s\n",$$.str);
		}
	| disc_union sequen 
		{
		strcpy($$.str , $1.str);
		strcat($$.str,  $2.str);
		printf("rule 134 %s\n",$$.str);
		}
	| RANGE
		{printf("rule 135 %s\n",$1.str);
		printf("token %s up %s low %s\n",yytext,upper_bound,lower_bound);
		if(upper_bound < lower_bound)
		  err("range error");
		}

	;



sequence_no : '#'
		{printf("rule 201 \n");
		}
	;

sequen : '*' 
		{printf("rule 16 \n");
		}
	;
 

disc_union : '+'
		{printf("rule 15 \n");
		
		}
	;


primitives : non_argu_prim
		{printf("rule 18 \n");
		item_val = $1.val;
		strcpy(item_str,$1.str);
		}
	;

module_call : primitives 
		{printf("rule 18 \n");}
	| module_node 
		{printf("rule 184 \n");
		}
	;

node_name :MATCH 
		{
		item_val = $1.val;
		strcpy(item_str,$1.str);
		printf("rule 192 %d\n",$1.val);
		printf("yylval %s %d  \n",yylval.symbol.str,yylval.symbol.val);
		printf("token %s\n",yytext);}
	| LITERALS
		{
		yyerrok;
		printf("rule 17 \n");
		item_val = $1.val;
		strcpy(item_str,$1.str);
		}
	| module_call
	| REFER
		{
		yyerrok;
		printf("rule 18 \n");
		item_val = $1.val;
		strcpy(item_str,$1.str);
		}
	;



non_argu_prim : NEW_LINE
	| NEW_PAGE
	| P_PARALLEL
		{
		item_type=$1.type;
		item_val = $1.val;
		}
	;

      

module_node :  m_name_sequence 
	|	m_name_seq
		{printf("rule 2 \n");}
	;

m_name_sequence : cap_char L_PAR t_node_name R_PAR  
		{printf("rule 003 indent %d\n",indentation);
		item_type=$1.val;
		strcpy(item_str,$1.str);
		strcat(item_str,"(");
		strcat(item_str,$3.str);
		strcat(item_str,")");
		$$.str=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy($$.str,item_str);
		}
	| m_name_sequence cap_char L_PAR t_node_name R_PAR  
		{printf(" rule 0032\n");
		item_type=$2.val;
		strcat(item_str,$2.str);
		strcat(item_str,"(");
		strcat(item_str,$4.str);
		strcat(item_str,")");
		$$.str=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy($$.str,item_str);
		}
	| m_name_sequence t_node_name L_PAR t_node_name R_PAR cap_char 
		{printf(" rule 0032\n");
		item_type=$6.val;
		strcat(item_str,$2.str);
		strcat(item_str,"(");
		strcat(item_str,$4.str);
		strcat(item_str,")");
		strcat(item_str,$6.str);
		$$.str=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy($$.str,item_str);
		}
	
	;

m_name_seq	: L_PAR t_node_name R_PAR cap_char   
		{printf("rule 0041 indent %d %d\n",indentation,tmp_indent);
		item_type=$4.val;
		strcpy(item_str,"(");
		strcat(item_str,$2.str);
		strcat(item_str,")");
		strcat(item_str,$4.str);
		$$.str=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy($$.str,item_str);
		printf("rule 0041 %s %s\n",item_str,$$.str);
		}
	| m_name_seq L_PAR t_node_name R_PAR cap_char 
	{printf("rule 0043 \n");
		item_type=$5.val;
		strcat(item_str,"(");
		strcat(item_str,$3.str);
		strcat(item_str,")");
		strcat(item_str,$5.str);
		$$.str=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy($$.str,item_str);
		}
	| m_name_seq L_PAR t_node_name R_PAR 
	{printf("rule 0044 \n");
		strcat(item_str,"(");
		strcat(item_str,$3.str);
		strcat(item_str,")");
		$$.str=(char *)calloc(1+strlen(item_str),sizeof(char));
		strcpy($$.str,item_str);
		printf("rule 0044 %s %s\n",item_str,$$.str);
		}
	;

module_title : module_call nls;

Indent : indent
	{ tmp_indent = wk_indent;
	}
	;


indent : INDENT
		{printf("rule 61 %d\n",indentation);
	wk_indent = indentation; 
		}
	|  indent  INDENT
		{ 
		wk_indent = indentation; 
		printf("rule 62 %d\n",indentation);}
	;

cap_char : CAP_C 
		{
		yyerrok;
		printf("rule 20 yylval %s %d  \n",yylval.symbol.str,yylval.symbol.val);
		printf("token %s\n",yytext);}
	;
       

%%
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
