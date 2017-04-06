INSTALLATIONDIR = /usr/local/bin
CC = gcc
CFLAGS = -Wall

all : markovlo wlgen

markovlo : markov-listoptimizer.o
	$(CC) $(CFLAGS) markov-listoptimizer.o -o $@
markov-listoptimizer.o : markov-listoptimizer.c
	$(CC) $(CFLAGS) -c markov-listoptimizer.c -o $@

wlgen : wordlist-gen.o
		$(CC) $(CFLAGS) wordlist-gen.o -o $@
wordlist-gen.o : wordlist-gen.c
		$(CC) $(CFLAGS) -c wordlist-gen.c -o $@

.PHONY : install remove clean

install :
	mv markovlo /usr/local/bin
	mv wlgen /usr/local/bin
	make clean
remove :
	rm $(INSTALLATIONDIR)/$(NAME)
clean :
	rm *.o
