CC := gcc
CFLAGS := -g -O2 -Wall -std=c99 # -DPOOL_THR_SAFE
OBJ := main.o mpool.o

test : $(OBJ)
	$(CC) $^ -o $@

mpool.o : mpool.c mpool.h
main.o : main.c mpool.h

.PHONY : all re fclean clean

all : test

re : fclean all

fclean : clean
	$(RM) test

clean :
	$(RM) $(OBJ)
