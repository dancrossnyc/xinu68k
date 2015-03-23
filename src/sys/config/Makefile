#
# Make the Xinu configuration program
#
YFLAGS=         -d
CFLAGS=		-O -Wall -ansi -pedantic -std=c11
OBJS=           parser.o
SRCS=           parser.y lexer.l
PROG=           config
LIBS=           -ly -ll
RM=             rm -f

all:		${PROG}

${PROG}:        lexer.c ${OBJS}
		${CC} -o ${PROG} ${OBJS} ${LIBS}
		${RM} lexer.c

install:	${PROG}
		cp ${PROG} ../sys/config

clean:
		${RM} ${PROG} ${OBJS} lexer.c *.o y.tab.h
