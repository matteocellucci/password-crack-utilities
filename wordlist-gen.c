#include <stdio.h>
#include <math.h>
#include "wordlist-gen.h"

#define PRINTABLE_SIZE 96

const static char printable[PRINTABLE_SIZE] = {
	// alphanumeric
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
	'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
	'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
	'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9',
	// punctation
	'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
	':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|',
	'}', '~',
	// space
	'\t', ' '
};

int main(int argc, char *argv[]) {
	int opt;
	int hflag = 0;
	int numvalue = 0;

	opterr = 0;
	while((opt = getopt(argc, argv, "sph")) != -1) {
		switch(opt) {
			case 'n':
				numvalue = optarg;
				break;
			case 'h':
				hflag = 1;
				break;
			case '?':
				if(isprint(optopt)) {
					fprintf(stderr, "Unknow option: -%c\a\n", optopt);
				}
				else {
					fprintf(stderr, "Unknow option character \\x%x\a\n", optopt);
				}
				exit(EXIT_FAILURE);
			default:
				abort();
		}
	}

	if(hflag || argc == 1) {
		usage();
		exit(EXIT_SUCCESS);
	}

	if(optind == 1 || numvalue = 0) {
		fprintf(stderr, "Error: use -n to specify depth\a\n");
		exit(EXIT_FAILURE);
	}

	FILE *list = fopen("wordlist-gen.txt","w");
	combine(list, numvalue);
	fclose(list);

	return 0;
}

void combine(FILE *list, int depth) {
	for(unsigned long long int i = 0; i < pow(PRINTABLE_SIZE, depth); i++) {
		fputc(printable[i % PRINTABLE_SIZE], list);
		if(depth > 1) {
			combine(list, depth - 1, printable[i]);
		}
	}
}

void usage() {
	printf("Worldlist generator\n");
	printf("<link to github>\n\n");
	printf("Usage: wordlist-gen [OPTION]\n");
	printf("-nNUM\tRecursion depth, it generates combinations of NUM characters\n");
	printf("-h\tPrint this message\n");
}
