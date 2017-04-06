INSTALLATIONDIR = /usr/local/bin
BINDIR = ../run
CC = gcc
CFLAGS = -Wall

all : markovlo wlgen
	mv markovlo $(BINDIR)
	mv wlgen $(BINDIR)
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
	cp $(BINDIR)/markovlo /usr/local/bin
	cp $(BINDIR)/wlgen /usr/local/bin
remove :
	rm $(INSTALLATIONDIR)/$(NAME)
clean :
	rm *.o
