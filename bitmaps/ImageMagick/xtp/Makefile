# Generated automatically from Makefile.in by configure.
#
#  Generic makefile for xtp for computers that do not have xmkmf.
#
#  Copyright 1994 E. I. du Pont de Nemours and Company
#
#  Permission to use, copy, modify, distribute, and sell this software and
#  its documentation for any purpose is hereby granted without fee,
#  provided that the above Copyright notice appear in all copies and that
#  both that Copyright notice and this permission notice appear in
#  supporting documentation, and that the name of E. I. du Pont de Nemours
#  and Company not be used in advertising or publicity pertaining to
#  distribution of the software without specific, written prior
#  permission.  E. I. du Pont de Nemours and Company makes no representations
#  about the suitability of this software for any purpose.  It is provided
#  "as is" without express or implied warranty.
#
#  E. I. du Pont de Nemours and Company disclaims all warranties with regard
#  to this software, including all implied warranties of merchantability
#  and fitness, in no event shall E. I. du Pont de Nemours and Company be
#  liable for any special, indirect or consequential damages or any
#  damages whatsoever resulting from loss of use, data or profits, whether
#  in an action of contract, negligence or other tortious action, arising
#  out of or in connection with the use or performance of this software.
#

CC = gcc
DEFS =  -DSTDC_HEADERS=1 -DDIRENT=1 -DHAVE_LIBNSL=1 -DHAVE_LIBM=1
INSTALL = ./../install.sh -c
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_PROGRAM = ${INSTALL}
LDFLAGS =
LIBS =  -lnsl -lm

LOCALDIR= /usr/local/bin

XTPObjects= xtp.o network.o regular.o

CFLAGS= -O

PROGRAMS= xtp 

all: $(PROGRAMS)

xtp: 	$(XTPObjects)
	rm -f $@
	$(CC) -o $@ $(XTPObjects) $(LIBS)

clean::
	rm -f xtp

install:: xtp
	$(INSTALL_PROG) xtp $(LOCALDIR)/xtp

clean::
	rm -f *.ln *.bak *.o core errs ,* *~ *.a .emacs_* make.log MakeOut

