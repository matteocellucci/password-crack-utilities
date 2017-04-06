#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "wordlist-gen.h"

// TODO togliere il limite ad n

int main(int argc, char *argv[]) {
	int opt;
	int hflag = 0;
	int nvalue = 0;

	opterr = 0;
	while((opt = getopt(argc, argv, "n:h")) != -1) {
		switch(opt) {
			case 'n':
				nvalue = atoi(optarg);
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

	if(optind == 1 || nvalue == 0) {
		fprintf(stderr, "Error: use -nNUM to specify depth\a\n");
		exit(EXIT_FAILURE);
	}

	FILE *list = fopen("wordlist-gen.txt", "w");
	combine(list, nvalue);
	fclose(list);

	return 0;
}

void combine(FILE *list, int depth) {
	for(int a = 0; a < PRINTABLE_SIZE && depth > 0; a++) {
		fputc(printable[a], list);
		fputc(10, list);
		for(int b = 0; b < PRINTABLE_SIZE && depth > 1; b++) {
			fputc(printable[a], list);
			fputc(printable[b], list);
			fputc(10, list);
			for(int c = 0; c < PRINTABLE_SIZE && depth > 2; c++) {
				fputc(printable[a], list);
				fputc(printable[b], list);
				fputc(printable[c], list);
				fputc(10, list);
				for(int d = 0; d < PRINTABLE_SIZE && depth > 3; d++) {
					fputc(printable[a], list);
					fputc(printable[b], list);
					fputc(printable[c], list);
					fputc(printable[d], list);
					fputc(10, list);
					for(int e = 0; e < PRINTABLE_SIZE && depth > 4; e++) {
						fputc(printable[a], list);
						fputc(printable[b], list);
						fputc(printable[c], list);
						fputc(printable[d], list);
						fputc(printable[e], list);
						fputc(10, list);
					}
				}
			}
		}
	}
}

void usage() {
	printf("Worldlist generator\n");
	printf("<link to github>\n\n");
	printf("Usage: wlgen [OPTION]\n");
	printf("-nNUM\tRecursion depth, it generates combinations of NUM characters (max 5)\n");
	printf("-h\tPrint this message\n");
}
