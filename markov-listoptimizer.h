#define CACHE_FILE_NAME "asciize.txt"

/*
 * Stampa il manuale d'uso
 */
void usage();

/*
 * Copia il file passato come input senza i caratteri non-ASCII
 * Input: 	il file da copiare
 * 		il nome del nuovo dile
 * Output: 	0 se è terminata correttamente
 *		1 se non è riuscita a creare il nuovo file
 */
int sanitarize(FILE *, char *);

/*
 * Copia il file passato in input rimuovendo le linee vuote
 * Input: 	il file da copiare
 * 		il nome del nuovo dile
 * Output: 	0 se è terminata correttamente
 *		1 se non è riuscita a creare il nuovo file
 */
int emptyline(FILE *, char *);

/*
 * Copia il file passato in input ottimizzando una word per riga
 * Input: 	il file da copiare
 * 		il nome del nuovo dile
 * Output: 	0 se è terminata correttamente
 *		1 se non è riuscita a creare il nuovo file
 */
int optimize(FILE *, char *);
