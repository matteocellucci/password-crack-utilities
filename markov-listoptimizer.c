#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "asciize.h"

int main(int argc, char *argv[]) {
	FILE *file;
	int flag_sanitarize = 0;
	int flag_emptyline = 0;
	int flag_optimize = 0;
	int exit_code = 0;

	if(argc > 1 && argc < 4) {
		// leggi l'opzione
		if(strcmp(argv[1], "--sanitarize") == 0) {
			flag_sanitarize = 1;
		}
		else if(strcmp(argv[1], "--emptyline") == 0) {
			flag_emptyline = 1;
		}
		else if(strcmp(argv[1], "--optimize") == 0) {
			flag_optimize = 1;
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
			return sanitarize(file, argv[2]);
		}
		else if(flag_emptyline) {
			return emptyline(file, argv[2]);
		}
		else if(flag_optimize) {
			return optimize(file, argv[2]);
		}
		fclose(file);
		remove(CACHE_FILE_NAME);
	}
	else {
		usage();
	}
	return 0;
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
		if(c>= 0 && c < 128) {
			fputc(c, asciize_file);
		}
	}
	fclose(asciize_file);
	return 0;
}

int emptyline(FILE *file, char *filename) {
	FILE *asciize_file;
	int c;
	int prev_c = -1;
	asciize_file = fopen(filename, "w");
	if(asciize_file == NULL) {
		printf("Error: file can't be created\a\n");
		return 1;
	}
	while((c = fgetc(file)) != EOF) {
		if(prev_c != 10 || (prev_c == 10 && c != 10)) {
			fputc(c, asciize_file);
			prev_c = c;
		}
	}
	fclose(asciize_file);
	return 0;
}

int optimize(FILE *file, char *filename) {
	FILE *asciize_file;
	int c;
	int delete_flag = 0;
	asciize_file = fopen(filename, "w");
	if(asciize_file == NULL) {
		printf("Error: file can't be created\a\n");
		return 1;
	}
	while((c = fgetc(file)) != EOF) {
		if(c == 10) {
			delete_flag = 0;
		}
		if(!delete_flag && !isspace(c)) {
			fputc(c, asciize_file);
		}
		else {
			delete_flag = 1;
		}
	}
	fclose(asciize_file);
	return 0;
}

void usage() {
	printf("<link to github>\n\n");
	printf("Usage: asciize [OPTION] [FILE]\n");
	printf("--sanitarize\t	Create a new file, called asciized.txt, which is a copy\n");
	printf("\t		of the input without any non-ascii character\n");
	printf("--emptyline\t	Remove any empty line\n");
	printf("--optimize\t	Ensure that every line is a single word\n");
}
