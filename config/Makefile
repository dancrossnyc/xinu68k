#
# Make the Xinu configuration program
#
YFLAGS=		-d
CFLAGS=		-O -Wall -ansi -pedantic -std=c11
OBJ=		parser.o
SRCS=		parser.y lexer.l
PROG=		config
LIBS=		-ly -ll
RM=		rm -f

all:		${PROG}

${PROG}:	${OBJ}
		${CC} -o ${PROG} ${OBJ} ${LIBS}
		${RM} lexer.c

install:	${PROG}
		cp ${PROG} ../xinu/config

clean:
		${RM} ${PROG} ${OBJ} parser.c lexer.c *.o y.tab.h

parser.c:	lexer.c
