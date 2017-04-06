/*
 * Stampa il manuale d'uso
 */
void usage();

/*
 * Copia il file sanitarizzando i caratteri non-ASCII
 */
void sanitarize(FILE *, FILE *);

/*
 * Copia il file purgando i caratteri non stampabili ad eccezione di \n se
 * non ripetuta
 */
void purge(FILE *, FILE *);
