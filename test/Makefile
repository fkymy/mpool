VPATH = ../

TARGETS = mpool_test
CC = gcc
CFLAGS = -g -O2 -std=c99 #-DMPOOL_THR_SAFE
OBJ = mpool.o main.o
LDLIBS = -lcunit
IFLAGS = -I..

mpool_test : $(OBJ)
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $^

mpool.o : mpool.c mpool.h
main.o : main.c mpool.h

.PHONY : clean
clean :
	make -C .. $@
	$(RM) $(OBJ) $(TARGETS)
