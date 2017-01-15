CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

EXECS = gshell

all: $(EXECS)

gshell: gshell.c wrappers.o
	${CC} ${CFLAGS} -I . -c gshell.c
	${CC} ${CFLAGS} wrappers.o gshell.o -o gshell -lm -l readline

wrappers.o: wrappers.c wrappers.h
	${CC} ${CFLAGS} -I . -c wrappers.c


.PHONY: clean
clean:
	/bin/rm -rf $(EXECS) wrappers.o

