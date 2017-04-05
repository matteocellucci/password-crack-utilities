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
	char *r_file_path = NULL;
	char *w_file_path = NULL;
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
			default:
				abort();
		}
	}

	if(hflag || argc == 1) {
		usage();
		exit(EXIT_SUCCESS);
	}

	if(optind == 1) {
		fprintf(stderr, "Error: no option passed, use -h for help\a\n");
		exit(EXIT_FAILURE);
	}

	r_file_path = argv[optind];
	if(r_file_path == NULL) {
		fprintf(stderr, "Error: source file needed, use -h for help\a\n");
		exit(EXIT_FAILURE);
	}
	w_file_path = argv[optind + 1];
	if(w_file_path == NULL) {
		fprintf(stderr, "Error: destination file needed, use -h for help\a\n");
		exit(EXIT_FAILURE);
	}


	r_file = fopen(r_file_path, "r");
	if(r_file == NULL) {
		fprintf(stderr, "Error: %s can't be read\a\n", r_file_path);
		exit(EXIT_FAILURE);
	}
	w_file = fopen(w_file_path, "r");
	if(w_file == NULL) {
		fprintf(stderr, "Error: %s can't be written\a\n", w_file_path);
		exit(EXIT_FAILURE);
	}

	if(sflag) {
		sanitarize(r_file, w_file);
	}
	if(pflag) {
		purge(r_file, w_file);
	}

	fclose(r_file);
	fclose(w_file);
	exit(EXIT_SUCCESS);
}

void sanitarize(FILE *r_file, FILE *w_file) {
	int c;
	while((c = fgetc(r_file)) != EOF) {
		if(isprint(c) || isspace(c)) {
			fputc(c, w_file);
		}
	}
}

void purge(FILE *r_file, FILE *w_file) {
	int c;
	int prev_c = 10;
	while((c = fgetc(r_file)) != EOF) {
		if((c == 10 && prev_c != 10) || isprint(c)) {
			fputc(c, w_file);
			prev_c = c;
		}
	}
}

void usage() {
	printf("Markov List Optimizer\n");
	printf("<link to github>\n\n");
	printf("Usage: markovlo [OPTION] [SOURCE FILE] [DESTINATION FILE]\n");
	printf("-s\tSanitarize input file from all non-ascii characters\n");
	printf("-p\tPurge any control character (except of new lines)\n");
	printf("-h\tPrint this message\n");
	// TODO printf("-R\tRemove source file once finished\n");
}
