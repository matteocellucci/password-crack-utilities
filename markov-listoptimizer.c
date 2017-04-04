#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "markov-listoptimizer.h"

int main(int argc, char *argv[]) {
	FILE *file;
	int flag_sanitarize = 0;
	int flag_purge = 0;
	int exit_code = 0;

	if(argc > 1 && argc < 4) {
		// leggi l'opzione
		if(strcmp(argv[1], "--sanitarize") == 0) {
			flag_sanitarize = 1;
		}
		else if(strcmp(argv[1], "--purge") == 0) {
			flag_purge = 1;
		}
		else {
			printf("Unknow option: %s\a\n", argv[1]);
			return 1;
		}

		// rinomina il file corrente, il nuovo file avrà lo stesso nome
		if(rename(argv[2], CACHE_FILE_NAME) != 0) {
			printf("Error: %s can't be modified\a\n", argv[2]);
			return 1;
		}

		file = fopen(CACHE_FILE_NAME, "r");
		if(file == NULL) {
			printf("Error: file can't be openend\a\n");
			return 1;
		}
		if(flag_sanitarize) {
			exit_code = sanitarize(file, argv[2]);
		}
		else if(flag_purge) {
			exit_code = purge(file, argv[2]);
		}
		fclose(file);
		remove(CACHE_FILE_NAME);
	}
	else {
		usage();
	}
	return exit_code;
}

int sanitarize(FILE *file, char *filename) {
	FILE *asciize_file;
	int c;
	asciize_file = fopen(filename, "w");
	if(asciize_file == NULL) {
		printf("Error: file can't be created\a\n");
		return 1;
	}
	while((c = fgetc(file)) != EOF) {
		if(isprint(c) || isspace(c)) {
			fputc(c, asciize_file);
		}
	}
	fclose(asciize_file);
	return 0;
}

int purge(FILE *file, char *filename) {
	FILE *asciize_file;
	int c;
	int prev_c = 10;
	asciize_file = fopen(filename, "w");
	if(asciize_file == NULL) {
		printf("Error: file can't be created\a\n");
		return 1;
	}
	while((c = fgetc(file)) != EOF) {
		if((c == 10 && prev_c != 10) || isprint(c)) {
			fputc(c, asciize_file);
			prev_c = c;
		}
	}
	fclose(asciize_file);
	return 0;
}

void usage() {
	printf("Markov List Optimizer\n");
	printf("<link to github>\n\n");
	printf("Usage: markovlo [OPTION] [FILE]\n");
	printf("--sanitarize\tCreate a new file, called asciized.txt, which is a copy\n");
	printf("\t\tof the input without any non-ascii character\n");
	printf("--purge\t\tRemove any control character (except of new lines) and\n");
	printf("\t\tmulti-words line\n");
}
