
#include <stdio.h>
#include <X11/Intrinsic.h>

#include "desc_struct.h"
#include "desc_table.h"
/*#include "y.tab.c"
*/
main(argc, argv)
int argc;
char *argv[];
{
  char *outfile,*infile;  
  char msg[512];
  FILE *yyin;

/* The first argument is the name of the Descartes spec.
 * If no filename is given, the program will get its input
 * from stdin. */

  if ((yyin = freopen(argv[1],"r",stdin)) == NULL ) {
     sprintf(msg,"can not open file %s",argv[1]);
  }
  yyparse();
}

/* Dummy function to resolve linker symbol */
int Build_Hoare_Tree()
{
	return;
}

/* Dummy from wid2.c */
Widget Rd_text_w;
Display_Build_User_Msg(text,msg)
Widget text;
char *msg;
{
	puts(msg);
}
