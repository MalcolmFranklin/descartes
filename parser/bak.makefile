.PRECIOUS: %

CC		= gcc -ansi
YFLAGS=-d
#OBJFILES=main.o real_des.o lex.o
OBJFILES	= main.o y.tab.o token.o
YACCFILE	= des2.y
LEXFILE		= des.l
INCLUDES	= -I/all/edu/X11R5/include

parser:	$(OBJFILES) y.tab.c y.tab.h
	$(CC) -o parser $(OBJFILES) -ly -ll 

y.tab.c : $(YACCFILE) lex.yy.c
	yacc $(YFLAGS) $(YACCFILE) y.tab.h
	
lex.yy.c: $(LEXFILE) 
	lex $(LEXFILE)

#lex.c:
#real_des.c+real_des.h:
#	yacc real_des.y y.tab.h
#	mv y.tab.c real_des.c 
#	mv y.tab.h real_des.h

clean:
	rm $(OBJFILES) lex.yy.c y.tab.c y.tab.h
