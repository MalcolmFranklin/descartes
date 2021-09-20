############################### MAKEFILE #######################################
#
# @(#)  makefile  for  Descartes Language Processor   07/06/90  SERC (Lee)
#
#
################################################################################
# Put under RCS control, and edited for Sun4 by Malcolm L. Franklin
#
# $Id: makefile,v 1.3 1994/10/02 00:33:15 franklin Exp $
# $Author: franklin $
# $Date: 1994/10/02 00:33:15 $
# $State: Exp $
# $Locker:  $
# $Source: /all/franklin/thesis/descartes/win/fifo_ex/RCS/makefile,v $
# $Log: makefile,v $
# Revision 1.3  1994/10/02  00:33:15  franklin
# cleanup.
#
################################################################################
UNAME := $(shell platform)

################################################################################
# Platform independent and/or default macros
################################################################################


AR	= ar    # The library archive command.

# If you want to use Gnu Bison, then change the definition of
# YACC to "bison -y" and pass "-DUSE_BISON" to the C compiler, to turn on the
# definition of yytext[] in need_before_ytab.h
YACC	= yacc  # UNIX utility for creating a parser.

LEX	= lex   # UNIX utility for creating a lexical analyzer.
OPT	= -g    # Tell compiler to save debugging info in the binaries.
YFLAGS	= -d    # Tell yacc to generate token codes.

# If you want to print the xwd (X window picture dump facility) command to 
# generate bitmaps of all the windows/menus, then define the
# PRINT_SCREEN_DUMP_COMMANDS.  xwd commands will print to stderr, all you have
# to do is issue the command exactly as they are printed.

# PRINT_SCREEN_DUMP_COMMANDS = -DPRINT_SCREEN_DUMP_COMMANDS


################################################################################
# Platform dependent macros
################################################################################

ifeq "$(UNAME)" "Sun413"

   # Gnu C Compiler
   # CC	= /home/local/bin/gcc # The C compiler to use.
   # ANSI_CFLAGS = -ansi -pedantic # Turn on "anal retentive" mode.
   # PURIFY_LINKER = 

   #CenterLine C compiler (clcc)
   CC	= /all/CenterLine/bin/clcc
   ANSI_CFLAGS	= -ansi -Xa
   PURIFY_LINKER 	= -linker=/bin/ld

   MOTIF_LIB_PATHS	= -L/home/tools1/uimx2.5/motif12/usr/lib \
			   -L/home/local/X11R5/lib
   MOTIF_INCLUDEPATHS	= -I/home/local/X11R5/include \
			  -I/home/tools1/uimx2.5/motif12/usr/include
   ifeq "$(PURIFYHOME)" ""
      PURIFYHOME = /home/tools1/pure/purify2.1
   endif
   PLATSPEC = -Dsun
   DEBUG_LIBS = #/usr/lib/end.o for HP-UX.  Not needed for SunOS 4
#Defining the  WORK_WITH_EDITRES preprocessor macro, and linking the executable
# with -lXmu is entirely optional.  It simply allows the user to view and modify
# application resources with the "editres" program that ships with the standard
# MIT distribution of X11.
DEFINES         =  -DWORK_WITH_EDITRES#
EDITRES_LIB     =  -lXmu

endif

ifeq "$(UNAME)" "HP901"
   # Gnu C Compiler
   # CC	= /home/local/bin/gcc # The C compiler to use.
   # ANSI_CFLAGS = -ansi -pedantic # Turn on "anal retentive" mode.
   PURIFY_LINKER 	=
   # HP-UX Professional C compiler.
   CC	= c89
   ANSI_CFLAGS	= -Ae
   PURIFY_LINKER 	=
#   MOTIF_LIB_PATHS       = -L/usr/lib/X11R5 
   MOTIF_LIB_PATHS       = -L/usr/lib/X11R5 -L/usr/lib/Motif1.2
   MOTIF_INCLUDEPATHS = -I/usr/include/Motif1.2 -I/usr/include/X11R5
   ifeq "$(PURIFYHOME)" ""
      PURIFYHOME = /all/pure/purify2.1_hp
   endif
   #PLATSPEC = -Wp,-H150000
   DEBUG_LIBS = /usr/lib/end.o
endif

ifeq "$(UNAME)" "HP903"
   # Gnu C Compiler
   # CC	= /home/local/bin/gcc # The C compiler to use.
   # ANSI_CFLAGS = -ansi -pedantic # Turn on "anal retentive" mode.
   PURIFY_LINKER 	=
   # HP-UX Professional C compiler.
   CC	= c89
   ANSI_CFLAGS	= -Ae
   PURIFY_LINKER 	=
#   MOTIF_LIB_PATHS       = -L/usr/lib/X11R5 
   MOTIF_LIB_PATHS       = -L/usr/lib/X11R5 -L/usr/lib/Motif1.2 \
				-L/home/local/X11R5/lib
   MOTIF_INCLUDEPATHS = -I/usr/include/Motif1.2 -I/usr/include/X11R5 \
				-I/home/local/X11R5/include
   ifeq "$(PURIFYHOME)" ""
      PURIFYHOME = /all/pure/purify2.1_hp
   endif
   #PLATSPEC = -Wp,-H150000
   DEBUG_LIBS = /usr/lib/end.o
endif

################################################################################
# Assemble the platform independent and dependent switches into macros for
# the translators (cc, lex, yacc)
################################################################################

INCLUDEPATHS    = -I. -I$(PURIFYHOME) $(MOTIF_INCLUDEPATHS)

CFLAGS          = $(INCLUDEPATHS) $(DEFINES) $(PLATSPEC) $(DEBUG) \
		  -D_POSIX_SOURCE  $(PRINT_SCREEN_DUMP_COMMANDS) \
		  $(ANSI_CFLAGS) $(OPT) 

ifeq "$(UNAME)" "HP901"
   KandR_CFLAGS	= $(CFLAGS) -O
endif
ifeq "$(UNAME)" "HP903"
   KandR_CFLAGS	= $(CFLAGS) -O
endif
ifeq "$(UNAME)" "Sun413"
   ifeq "$(CC)" "/home/local/bin/gcc "
      KandR_CFLAGS = $(INCLUDEPATHS) $(DEFINES) $(PLATSPEC) $(DEBUG) -O2
   else
      KandR_CFLAGS = $(INCLUDEPATHS) $(DEFINES) $(PLATSPEC) $(DEBUG) \
		  -traditional -O2
   endif
endif

LIBPATHS        = -L. $(MOTIF_LIB_PATHS)
STD_LIBS	= -lm -ll -ly
MOTIF_LIBS      = -lXm -lXt -lX11 $(EDITRES_LIB)
LIBS		= $(MOTIF_LIBS) $(STD_LIBS) $(DEBUG_LIBS)

############################################################################
# Look in ./RCS for RCS files.
############################################################################
%::RCS/%,v
	@[ -w $@ ] || ( echo "Getting '$@' from RCS." ; ${CO} $(COFLAGS) $< $@ )
############################################################################
# Look in cwd, or VPATH dirs, for RCS files.
############################################################################
%::%,v
	@[ -w $@ ] || ( echo "Getting '$@' from RCS." ; ${CO} $(COFLAGS) $< $@ )


################################################################################
# Tell make NOT to delete stuff automatically when a build fails!
################################################################################
.PRECIOUS: %

################################################################################
# The object code to assemble in order to build this guy.
################################################################################

GENERIC_OBJS	= some_utils.o token.o share_rtn.o build_rtn.o \
		  build_hoare_tree.o exec_rtn1.o analysis1.o y.tab.o wid1.o \
		  semops.o msg.o command_line.o main.o desc_struct.o fifo.o \
		  hash.o safe.o

OBJS  = $(GENERIC_OBJS:%=$(UNAME)/%)
YACCFILE        = des2.y
LEXFILE         = des.l

################################################################################
# Test driver program for the FIFO module:
################################################################################

FIFO_GENERIC_OBS = fifotst.o fifo.o hash.o semops.o some_utils.o safe.o
FIFO_OBJS = $(FIFO_GENERIC_OBS:%=$(UNAME)/%)

fifotst.$(UNAME): $(FIFO_OBJS)
	$(CC) $(FIFO_OBJS)  -o $@ $(LIBPATHS) $(LIBS) -lc

fifotst.purify: $(FIFO_OBJS)
	$(PURIFYHOME)/purify -chain-length=20 $(PURIFY_LINKER) $(CC) $(FIFO_OBJS)  -o $@ $(LIBPATHS) $(STD_LIBS) $(DEBUG_LIBS)
	
fifotst.sentinel: $(FIFO_OBJS)
	sentinel $(CC) $(FIFO_OBJS)  -o $@ $(LIBPATHS) $(STD_LIBS) $(DEBUG_LIBS)
	
################################################################################
# Target "centerline" is used by CDE. It needs to load everything as source
# in order to reverse-engineer the design.  Note that loading y.tab.c causes
# runtime errors everytime the lex/yacc output indexes an array by "-1" (it
# does this a lot, and since you cannot suppress errors, it is not productive
# to run this way).
# Use the "centerline.run" target, which loads y.tab.o as an optimized (no
# debug info) object module to avoid these spurious ObjectCenter runtime
# errors.
################################################################################
centerline:
	#load $(INCLUDEPATHS) $(DEFINES) $(PLATSPEC) [a-k,m-w]*.c
	#load -traditional y.tab.c
	#link

centerline.run:
	#load $(INCLUDEPATHS) $(DEFINES) $(PLATSPEC) [a-k,m-w]*.c
	#load Sun413/y.tab.o
	#link

################################################################################
# Default rule for creating a ".o" file from a ".c" file.
################################################################################
$(UNAME)/%.o: %.c
	@[ -d $(UNAME) ] || mkdir -p $(UNAME)
	$(CC) -c $(CFLAGS) $< -o $@
	@#unload $*.c
	@#unload $*.o
	@#load -C $(CFLAGS) $*.c

# To run a fname.c file through the preprocessor only, type "make fname.i"
%.i: %.c
	$(CC) -C -E $(CFLAGS) -c $*.c > $*.i

################################################################################
# Rules for the parser code (for lex and yacc).
#	lex and yacc generate code that uses K&R C constructs that are not
#	legal in ISO/ANSI Standard C.  Run the compiler in K&R compatibility
#	mode.
################################################################################
$(UNAME)/y.tab.o : y.tab.c lex.yy.c
	$(CC)  -c $(KandR_CFLAGS) $< -o $@
	@#unload $*.c
	@#unload $*.o
	@#load -C $(KandR_CFLAGS) $*.c

y.tab.c y.tab.h : $(YACCFILE) lex.yy.c wid1.h desc_struct.h desc_table.h analysis1.h
	$(YACC) $(YFLAGS) $(YACCFILE)

lex.yy.c: $(LEXFILE)
	$(LEX) $(LEXFILE)

################################################################################
# Make will use the following rule to delete all translator-generated files
# when you type "make clean".
################################################################################
clean:
	rm $(OBJS) lex.yy.c y.tab.c y.tab.h

################################################################################
# Run utility to automatically generate makefile dependencies.
################################################################################
depend depends: makefile
	#gcc -MM  *.[c] >! outf
	makedepend -p'$$(UNAME)/' $(CFLAGS) *.[c,l,y]

# DO NOT DELETE THIS LINE -- make depend depends on it.

$(UNAME)/analysis1.o : analysis1.c cchk_missing_stdlib.h cchk_missing_unistd.h cchk_missing_signal.h \
  desc_struct.h share_rtn.h analysis1.h mesg.h wid1.h some_utils.h hash.h fifo.h \
  exec_rtn1.h semops.h safe.h 
$(UNAME)/build_hoare_tree.o : build_hoare_tree.c cchk_missing_stdlib.h cchk_missing_stdarg.h \
  cchk_missing_unistd.h desc_struct.h desc_table.h build_rtn.h mesg.h wid1.h analysis1.h \
  build_hoare_tree.h some_utils.h 
$(UNAME)/build_rtn.o : build_rtn.c cchk_missing_stdlib.h cchk_missing_unistd.h desc_struct.h \
  need_before_ytab.h y.tab.h mesg.h wid1.h share_rtn.h build_hoare_tree.h some_utils.h \
  build_rtn.h 
$(UNAME)/command_line.o : command_line.c command_line.h 
$(UNAME)/desc_struct.o : desc_struct.c desc_struct.h 
$(UNAME)/exec_rtn1.o : exec_rtn1.c cchk_missing_stdlib.h cchk_missing_stdarg.h cchk_missing_unistd.h \
  desc_struct.h share_rtn.h analysis1.h mesg.h some_utils.h hash.h fifo.h wid1.h \
  exec_rtn1.h semops.h 
$(UNAME)/fifo.o : fifo.c cchk_missing_stdlib.h cchk_missing_unistd.h cchk_missing_signal.h \
  semops.h some_utils.h hash.h safe.h fifo.h 
$(UNAME)/hash.o : hash.c cchk_missing_stdlib.h hash.h 
$(UNAME)/lex.yy.o : lex.yy.c /home/local/lib/gcc-lib/sparc-sun-sunos4.1.3/2.5.8/include/stdio.h 
$(UNAME)/main.o : main.c cchk_missing_stdlib.h cchk_missing_unistd.h some_utils.h command_line.h \
  build_rtn.h mesg.h desc_struct.h hash.h fifo.h exec_rtn1.h wid1.h main.h 
$(UNAME)/msg.o : msg.c mesg.h 
$(UNAME)/safe.o : safe.c cchk_missing_stdlib.h cchk_missing_unistd.h semops.h some_utils.h \
  hash.h fifo.h desc_struct.h exec_rtn1.h safe.h 
$(UNAME)/semops.o : semops.c cchk_missing_stdlib.h cchk_missing_unistd.h sunos4_missing.h \
  some_utils.h semops.h 
$(UNAME)/share_rtn.o : share_rtn.c desc_struct.h share_rtn.h 
$(UNAME)/some_utils.o : some_utils.c cchk_missing_stdlib.h cchk_missing_stdarg.h cchk_missing_unistd.h \
  some_utils.h 
$(UNAME)/token.o : token.c cchk_missing_stdlib.h cchk_missing_unistd.h need_before_ytab.h \
  y.tab.h desc_struct.h 
$(UNAME)/wid1.o : wid1.c cchk_missing_stdlib.h cchk_missing_stdarg.h cchk_missing_unistd.h \
  desc_struct.h build_rtn.h share_rtn.h semops.h mesg.h analysis1.h some_utils.h \
  hash.h fifo.h exec_rtn1.h command_line.h rene_descartes.h main.h wid1.h 
$(UNAME)/y.tab.o : y.tab.c mesg.h wid1.h desc_struct.h desc_table.h analysis1.h build_hoare_tree.h \
  need_before_ytab.h lex.yy.c 
$(UNAME)/fifotst.o : fifotst.c cchk_missing_stdlib.h cchk_missing_unistd.h \
  semops.h some_utils.h hash.h fifo.h 
