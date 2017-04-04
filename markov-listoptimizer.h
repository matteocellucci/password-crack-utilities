#define CACHE_FILE_NAME "markovlo.part.txt"

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
 * Copia il file passato in input rimuovendo i caratteri di controllo eccetto
 * \n non ripetute
 * Input: 	il file da copiare
 * 		il nome del nuovo file
 * Output: 	0 se è terminata correttamente
 *		1 se non è riuscita a creare il nuovo file
 */
int purge(FILE *, char *);
