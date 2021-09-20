############################### MAKEFILE #######################################
#
# @(#)  makefile  for  Descartes Language Processor   07/06/90  SERC (Lee)
#
#
################################################################################
# Put under RCS control, and edited for Sun4 by Malcolm L. Franklin
#
# $Id: makefile,v 1.46, h4_3_2 1994/08/01 21:00:59 franklin Exp franklin $
# $Author: franklin $
# $Date: 1994/08/01 21:00:59 $
# $State: Exp $
# $Locker: franklin $
# $Source: /all/franklin/thesis/descartes/win/RCS/makefile,v $
# $Log: makefile,v $
# Revision 1.46  1994/08/01  21:00:59  franklin
# Use 'c89' for the HP compiler
#
# Revision 1.45  1994/07/08  08:16:25  franklin
# Add PRINT_SCREEN_DUMP_COMMANDS macro.  Remove share_var.c
# from builds; it contained no code or data, only comments.
#
# Revision 1.44  1994/07/02  20:31:35  franklin
# 1. Move the EDITRES stuff into the Sun-specific block of this file.  I
#    could not find the Xmu library or header file on my HP-UX 9.01 machine.
# 2. wid1.o now reads rene_descartes.h
#
# Revision 1.43  1994/07/01  18:03:24  franklin
# update dependencies.
#
# Revision 1.42  1994/06/29  03:01:00  franklin
# Add support for the X11 "editres" program.
#
# Revision 1.41  1994/06/15  15:47:20  franklin
# Update dependencies
#
# Revision 1.40  1994/06/15  00:06:11  franklin
# Add desc_struct.o and rebuild dependencies.
#
# Revision 1.39  1994/06/14  20:34:02  franklin
# On the HP, link with /usr/lib/end.o so you can get a
# traceback stack when the program dies in a function from
# a shared library.
#
# Revision 1.38  1994/06/09  01:54:59  franklin
# Update path to the Motif libraries on the Sun.
#
# Revision 1.37  1994/06/07  22:00:13  franklin
# Add dependencies for the new file main.c
#
# Revision 1.36  1994/05/25  01:39:16  franklin
# Add "centerline" target, for loading source into ObjectCenter when you
# are interfacing with the IdE CDE tool.
# Add the commandline.[hc] module.
# Add "centerline.run" target for loading all source execept y.tab.o, so
# you can execute all human-generated source code in ObjectCenter with strict
# checking enabled.
#
# Revision 1.35  1994/05/17  01:14:40  franklin
# Embed the UNAME macro in the name of the executable.
#
# Revision 1.34  1994/05/17  00:10:53  franklin
# Get the lex/yacc generated code through the C compiler
# on both HP-UX 9.0 and SunOS 4.1.3
#
# Revision 1.33  1994/05/16  23:25:33  franklin
# Fix macro definitons for the HP-UX 9.0 compiler.
#
# Revision 1.32  1994/05/13  04:03:22  franklin
# Update dependencies
#
# Revision 1.31  1994/05/13  02:39:41  franklin
# Add dependencies for "need_before_ytab.h"
#
# Revision 1.30  1994/05/13  02:35:53  franklin
# Dont try to compile the output of lex and yacc with an ANSI
# C compiler (at least under SunOS4), it flat wont work.
#
# Also: In ObjectCenter, load the source code for everything EXCEPT
#       y.tab.o (Dont load lex.yy.c or y.tab.c).  This generates
#       numerous runtime errors in ObjectCenter whenever the YACC
#       generated code uses an index of -1 in to an array.
#
# Revision 1.29  1994/05/03  15:52:35  franklin
# Build msg.c --> msg.o as a separate module, dont
# #include it anymore.  Update dependencies.
#
# Revision 1.28  1994/05/02  15:59:22  franklin
# Put declarations missing from the SunOS 4.x include files into
# sunos4_missing.h
#
# Revision 1.27  1994/05/02  05:17:06  franklin
# 1. Andy moved the Motif librariy to /usr/lib/X11R5.
# 2. split sem.c into semops.h and semops.c
#
# Revision 1.26  1994/04/23  21:33:31  franklin
# Use CenterLines clcc compiler instead of gcc.  The
# installation at Motorola is unstable right now.
#
# Revision 1.25  1994/04/14  22:50:32  franklin
# Remove all dependencies on alert_dcl.h.  It is no longer needed.
#
# Revision 1.24  1994/04/12  13:12:21  franklin
# Fix syntax error.
#
# Revision 1.23  1994/04/12  07:57:48  franklin
# Type "make h4.purify" to make an instrumented executable to
# perform Pure Software Inc. "Purify" checks.
#
# Revision 1.22  1994/04/12  06:23:06  franklin
# Breakout some utility functions from analysis1.c into some_utils.c
#
# Revision 1.21  1994/04/11  22:38:07  franklin
# Use ANSI/ISO C compiler on ALL modules.
#
# Revision 1.20  1994/04/11  22:26:13  franklin
# Convert share_rtn.c to ANSI/ISO Standard C.
#
# Revision 1.19  1994/04/11  18:19:17  franklin
# Use gcc for ANSI and for K&R C modules.
#
# Revision 1.18  1994/04/11  16:11:09  franklin
# Converted wid1.c to ANSI/ISO Standard C.
#
# Revision 1.17  1994/04/09  23:57:29  franklin
# Update dependencies.
#
# Revision 1.16  1994/04/09  23:08:10  franklin
# Update dependencies.
#
# Revision 1.15  1994/04/09  22:40:26  franklin
# Update dependencies.
#
# Revision 1.14  1994/04/09  20:35:57  franklin
# Fix syntax error.
#
# Revision 1.13  1994/04/09  20:22:13  franklin
# Use the ANSI C compiler for build_rtn.c
#
# Revision 1.12  1994/04/08  09:23:09  franklin
# Tell pkg_freeze where to find gcc
#
# Revision 1.11  1994/04/08  09:02:58  franklin
# Convert build_hoare_tree.c to ANSI/ISO Standard C.
# Put declarations for it in build_hoare_tree.h
#
# Revision 1.10  1994/04/08  06:43:58  franklin
# Move more prototypes and #defines into header files.
#
# Revision 1.8  1994/04/08  03:39:13  franklin
# Start converting source code to ANSI C.
#
# Revision 1.5  1994/04/08  02:01:30  franklin
# Generate y.tab.c, y.tab.h, and lex.yy.c from des.l and des2.y.
#
# Revision 1.3  1994/03/25  23:03:21  franklin
# Store object files in a different subdirectory.  Reorgainize the makefile
# to make it easier to build on multiple platforms some day.
#
# Revision 1.2  1994/03/24  19:34:42  franklin
# Makefile to build the h4 Descartes language processor.
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
PRINT_SCREEN_DUMP_COMMANDS = -DPRINT_SCREEN_DUMP_COMMANDS


################################################################################
# Platform dependent macros
################################################################################

ifeq "$(UNAME)" "Sun413"

   # Gnu C Compiler
   CC	= /home/local/bin/gcc # The C compiler to use.
   ANSI_CFLAGS = -ansi -pedantic # Turn on "anal retentive" mode.

   #CenterLine C compiler (clcc)
   # CC	= /all/CenterLine/bin/clcc
   # ANSI_CFLAGS	= -ansi -Xa

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
   # HP-UX Professional C compiler.
   CC	= c89
   ANSI_CFLAGS	= -Ae
#   MOTIF_LIB_PATHS       = -L/usr/lib/X11R5 
   MOTIF_LIB_PATHS       = -L/usr/lib/X11R5 -L/usr/lib/Motif1.2
   MOTIF_INCLUDEPATHS = -I/usr/include/Motif1.2 -I/usr/include/X11R5
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
		  semops.o msg.o command_line.o main.o desc_struct.o
OBJS  = $(GENERIC_OBJS:%=$(UNAME)/%)
YACCFILE        = des2.y
LEXFILE         = des.l

################################################################################
# The main executable
################################################################################

h4.$(UNAME):	$(OBJS)
	$(CC) $(OBJS)  -o $@ $(LIBPATHS) $(LIBS)
	chmod a+r $@

h4.purify: $(OBJS)
	# For purify 3 if it ever works: $(PURIFYHOME)/purify purecov $(CC) $(OBJS) -o $@ $(LIBPATHS) $(LIBS)
	$(PURIFYHOME)/purify purecov $(CC) $(OBJS) -o $@ $(LIBPATHS) $(LIBS)

h4.sentinel: $(OBJS)
	# For purify 3 if it ever works: $(PURIFYHOME)/purify purecov $(CC) $(OBJS) -o $@ $(LIBPATHS) $(LIBS)
	sentinel $(CC) $(OBJS) -o $@ $(LIBPATHS) $(LIBS)

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
	makedepend -p'$$(UNAME)/' $(CFLAGS) *.[c,l,y]

# DO NOT DELETE THIS LINE -- make depend depends on it.

$(UNAME)/analysis1.o: desc_struct.h share_rtn.h analysis1.h mesg.h wid1.h
$(UNAME)/analysis1.o: exec_rtn1.h some_utils.h semops.h
$(UNAME)/build_hoare_tree.o: desc_struct.h desc_table.h build_rtn.h mesg.h
$(UNAME)/build_hoare_tree.o: wid1.h analysis1.h build_hoare_tree.h
$(UNAME)/build_hoare_tree.o: some_utils.h
$(UNAME)/build_rtn.o: desc_struct.h need_before_ytab.h y.tab.h mesg.h wid1.h
$(UNAME)/build_rtn.o: share_rtn.h build_hoare_tree.h some_utils.h build_rtn.h
$(UNAME)/command_line.o: command_line.h
$(UNAME)/des2.o: mesg.h wid1.h desc_struct.h desc_table.h analysis1.h
$(UNAME)/des2.o: build_hoare_tree.h need_before_ytab.h lex.yy.c
$(UNAME)/des2.o: /usr/include/stdio.h
$(UNAME)/desc_struct.o: desc_struct.h
$(UNAME)/exec_rtn1.o: desc_struct.h share_rtn.h analysis1.h mesg.h wid1.h
$(UNAME)/exec_rtn1.o: exec_rtn1.h semops.h some_utils.h
$(UNAME)/fifo.o: semops.h some_utils.h hash.h
$(UNAME)/hash.o: hash.h
$(UNAME)/lex.yy.o: /usr/include/stdio.h
$(UNAME)/main.o: some_utils.h command_line.h build_rtn.h mesg.h desc_struct.h
$(UNAME)/main.o: exec_rtn1.h wid1.h main.h
$(UNAME)/msg.o: mesg.h
$(UNAME)/semops.o: sunos4_missing.h some_utils.h semops.h
$(UNAME)/share_rtn.o: desc_struct.h share_rtn.h
$(UNAME)/some_utils.o: some_utils.h
$(UNAME)/token.o: need_before_ytab.h y.tab.h desc_struct.h
$(UNAME)/wid1.o: desc_struct.h build_rtn.h share_rtn.h semops.h mesg.h
$(UNAME)/wid1.o: analysis1.h exec_rtn1.h some_utils.h command_line.h
$(UNAME)/wid1.o: rene_descartes.h main.h wid1.h
$(UNAME)/y.tab.o: mesg.h wid1.h desc_struct.h desc_table.h analysis1.h
$(UNAME)/y.tab.o: build_hoare_tree.h need_before_ytab.h lex.yy.c
$(UNAME)/y.tab.o: /usr/include/stdio.h
