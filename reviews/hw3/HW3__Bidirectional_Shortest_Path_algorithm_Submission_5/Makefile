# $Id: Makefile,v 1.1 2014-02-05 19:42:46-08 - - $
MKFILE    = Makefile
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}
SUBMAKE   = ${MAKE} --no-print-directory

GCC       = g++ -std=c++11
MAKEDEPS  = cc -MM

CHEADER   = 
CSOURCE   = main.cpp ${CHEADER:.h=.c}
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = asg3
SOURCES   = ${CHEADER} ${CSOURCE} ${MKFILE}

all: ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}

%.o : %.c
	cid + $<
	${GCC} -c $<

clean:
	- rm ${EXECBIN} ${OBJECTS}

ifeq "${NEEDINCL}" ""
endif

