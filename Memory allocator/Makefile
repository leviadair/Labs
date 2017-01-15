
CC = gcc -I ./include
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

INC = ./include
SRC = ./src
OBJ = ./obj
DOC = ./doc
BIN = ./bin

vpath %.h ./include
vpath %.c ./src

EXECS = dlisttest memorytest_1 frag-eval

all: $(EXECS)

doc:
	doxygen

$(OBJ)/dnode.o: dnode.h dnode.c
	$(CC) $(CFLAGS) -c $(SRC)/dnode.c -o $(OBJ)/dnode.o

$(OBJ)/dlist.o: dlist.h dlist.c dnode.h
	$(CC) $(CFLAGS) -c $(SRC)/dlist.c -o $(OBJ)/dlist.o


$(OBJ)/allocator.o: $(SRC)/allocator.h allocator.c dlist.h dnode.h 
	$(CC) $(CFLAGS) -c $(SRC)/allocator.c -o $(OBJ)/allocator.o

dlisttest: $(SRC)/dlisttest.c $(OBJ)/dnode.o $(OBJ)/dlist.o
	$(CC) $(CFLAGS) $(OBJ)/dnode.o $(OBJ)/dlist.o $(SRC)/dlisttest.c -o $(BIN)/dlisttest 



memorytest_1: $(SRC)/memorytest_1.c $(OBJ)/allocator.o $(OBJ)/dnode.o $(OBJ)/dlist.o
	$(CC) $(CFLAGS) $(SRC)/memorytest_1.c $(OBJ)/allocator.o  $(OBJ)/dnode.o $(OBJ)/dlist.o -o $(BIN)/memorytest_1 

frag-eval: $(SRC)/frag_eval.c $(OBJ)/allocator.o $(OBJ)/dnode.o $(OBJ)/dlist.o
	$(CC) $(CFLAGS) $(SRC)/frag_eval.c $(OBJ)/allocator.o  $(OBJ)/dnode.o $(OBJ)/dlist.o -o $(BIN)/frag_eval

.PHONY: clean
clean:
	/bin/rm -rf $(BIN)/* $(OBJ)/* core* *~

