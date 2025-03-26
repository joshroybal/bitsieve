#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sieve.h"

int main(int argc, char *argv[])
{
    unsigned n, siz;
    unsigned *erat = (unsigned *) NULL;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return(1);
    }
    n = atoi(argv[1]);
    if (n <= 1) /* nothing to do */
        return(0);
    siz = ceil(n / 64.0);   /* allocate at least one word */
    erat = (unsigned *) malloc(siz * sizeof(unsigned));
    initialize(erat, siz);
    sieve(erat, siz);
    dump(erat, n);
    free(erat);
    return(0);
}
