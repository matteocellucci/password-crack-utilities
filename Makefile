NAMEDIR = /usr/local/bin
NAME = markovlo
CC = gcc
CFLAGS = -Wall
OBJS = markov-listoptimizer.o

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
markov-listoptimizer.o : markov-listoptimizer.c
	$(CC) $(CFLAGS) -c markov-listoptimizer.c -o $@

.PHONY : install remove clean

install : $(NAME)
	mv $(NAME) /usr/local/bin
remove :
	rm $(NAMEDIR)/$(NAME)
clean :
	rm *.o
