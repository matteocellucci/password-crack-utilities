#include <stdio.h>
#include "asciize.h"

/*
 * Crea una copia del file passato in input rimuovendo tutti i caratteri non ASCII
 */
int main(int argc, char *argv[]) {
	FILE *file;
	FILE *asciize_file;
	if(argc > 1) {
		file = fopen(argv[1], "r");
		if(file == NULL) {
			printf("Error: file can't be openend\a\n");
			return 1;
		}
		int c;
		int prev_c = 0;
		printf("ASCIIzation");
		asciize_file = fopen("asciized.txt", "w");
		if(asciize_file == NULL) {
			printf("Error: file can't be created\a\n");
			return 1;
		}
		while((c = fgetc(file)) != EOF) {
			if(c>= 0 && c < 128) {
				fputc(c, asciize_file);
				prev_c = c;
			}
		}
		fclose(file);
		fclose(asciize_file);
		printf("Complete");
	}
	else {
		usage();
	}
	return 0;
}

void usage() {
	printf("<link to github>\n\n");
	printf("Usage: asciize [FILE]\n");
}
