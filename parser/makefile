.PRECIOUS: %

CC		= gcc -ansi -I/usr/include/X11R5
#OBJFILES=main.o real_des.o lex.o
OBJFILES	= main.o y.tab.o token.o
YFLAGS=-d
#YACC		= yacc
YACC		= bison -y
YACCFILE	= des2.y
YACCOUT_C	= y.tab.c
YACCOUT_H	= y.tab.h
LEX		= lex
LEXFLAGS	=
LEXFILE		= des.l
INCLUDES	= -I/all/edu/X11R5/include

parser:	$(OBJFILES) $(YACCOUT_C) $(YACCOUT_H)
	$(CC) -o parser $(OBJFILES) -ly -ll 

$(YACCOUT_C) : $(YACCFILE) lex.yy.c
	( rm $(YACCOUT_C) > /dev/null 2>&1 ; true )
	$(YACC) $(YFLAGS) $(YACCFILE) $(YACCOUT_H)
	# YACC on some platforms inserts declarations of calloc() and malloc()
	# that are inconsistent with the ANSI/ISO C declarations in <stdlib.h>
	grep -v "extern char \*malloc()" $(YACCOUT_C) | grep -v "extern char \*calloc()" > $(YACCOUT_C).tmp
	cp  $(YACCOUT_C).tmp $(YACCOUT_C)

lex.yy.c: $(LEXFILE) 
	$(LEX) $(LEXFLAGS) $(LEXFILE)

clean:
	rm $(OBJFILES) lex.yy.c $(YACCOUT_C) $(YACCOUT_H)

centerline:
	#load -ly -ll
	#load main.c token.c y.tab.c
	#link
