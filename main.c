#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sieve.h"

int main(int argc, char *argv[])
{
    const unsigned LIMIT = 1000000;
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
    printf("%u bytes allocated  %u words allocted\n", siz, siz/8);
    erat = (unsigned *) malloc(siz * sizeof(unsigned));
    initialize(erat, siz);
    sieve(erat, siz);
    if (n <= LIMIT)
        display_primes(erat, n);
    else 
        printf("no. of primes = %u\n", count_primes(erat, n));
    free(erat);
    return(0);
}
