CC=gcc
CFLAGS=

asciize : asciize.o
	$(CC) $(CFLAGS) asciize.o -o $@
asciize.o : asciize.c
	$(CC) $(CFLAGS) -c asciize.c -o $@

.PHONY: install clean

install : asciize
	mv asciize /usr/local/bin

clean :
	rm *.o
