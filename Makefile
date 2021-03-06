CC = gcc
CFLAGS = -g -O2 -W -Wall -std=c99 #-DMPOOL_THR_SAFE
OBJ = mpool.o main.o

mpool_test : $(OBJ)
	$(CC) $^ -lpthread -o $@

mpool.o : mpool.c mpool.h
main.o : main.c mpool.h

.PHONY : clean
clean :
	$(RM) $(OBJ) mpool_test
