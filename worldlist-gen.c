#include <stdio.h>

#define PRINT_SIZE 96

int main(int argc, char *argv[]) {
	char printable[] = {
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

	FILE *list = fopen("wordlist_gen.txt","w");
	for(int a = 0; a < PRINT_SIZE; a++) {
		for(int b = 0; b < PRINT_SIZE; b++) {
			for(int c = 0; c < PRINT_SIZE; c++) {
				for(int d = 0; d < PRINT_SIZE; d++) {
					for(int e = 0; e < PRINT_SIZE; e++) {
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
	fclose(list);
	return 0;
}
