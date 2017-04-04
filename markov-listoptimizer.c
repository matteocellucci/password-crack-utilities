#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "markov-listoptimizer.h"

int main(int argc, char *argv[]) {
	int opt;
	int sflag = 0;
	int pflag = 0;
	int hflag = 0;
	char *fvalue = NULL;
	FILE *r_file;
	FILE *w_file;

	opterr = 0;
	while((opt = getopt(argc, argv, "sph")) != -1) {
		switch(opt) {
			case 's':
				sflag = 1;
				break;
			case 'p':
				pflag = 1;
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
		}
		default:
			abort();
	}

	if(hflag) {
		usage();
		exit(EXIT_SUCCESS);
	}

	fvalue = argv[optind];
	if(rename(fvalue, CACHE_FILE_NAME) != 0) {
		fprintf(stderr, "Error: %s can't be modified\a\n", fvalue);
		exit(EXIT_FAILURE);
	}
	file = fopen(CACHE_FILE_NAME, "r");
	if(file == NULL) {
		fprintf(stderr, "Error: %s can't be updated\a\n", fvalue);
		rename(CACHE_FILE_NAME, fvalue);
		exit(EXIT_FAILURE);
	}

	if(sflag) {
		sanitarize(r_file, w_file);
	}
	if(pflag) {
		purge(r_file, w_file);
	}

	fclose(file);
	remove(CACHE_FILE_NAME);
	exit(EXIT_SUCCESS);
}

FILE sanitarize(FILE *file, char *filename) {
	FILE *opt_file;
	int c;
	opt_file = fopen(filename, "w");
	if(opt_file == NULL) {
		fprintf(stderr, "Error: %s can't be updated\a\n", fvalue);
		rename(CACHE_FILE_NAME, fvalue);
		exit(EXIT_FAILURE);
	}
	while((c = fgetc(file)) != EOF) {
		if(isprint(c) || isspace(c)) {
			fputc(c, opt_file);
		}
	}
	fclose(file);
	file = opt_file;
}

void purge(FILE *file, char *filename) {
	FILE *opt_file;
	int c;
	int prev_c = 10;
	opt_file = fopen(filename, "w");
	if(opt_file == NULL) {
		printf("Error: file can't be created\a\n");
		return 1;
	}
	while((c = fgetc(file)) != EOF) {
		if((c == 10 && prev_c != 10) || isprint(c)) {
			fputc(c, opt_file);
			prev_c = c;
		}
	}
	fclose(opt_file);
	return 0;
}

void usage() {
	printf("Markov List Optimizer\n");
	printf("<link to github>\n\n");
	printf("Usage: markovlo [OPTION] [FILE]\n");
	printf("-s\tSanitarize input file from all non-ascii characters\n");
	printf("-p\tPurge any control character (except of new lines)\n");
}
