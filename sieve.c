#include <stdio.h>
#include <string.h>
#include <math.h>
#include "sieve.h"

void initialize(unsigned *arr, unsigned n)
{
    memset(arr, 0xffffffff, n * sizeof(unsigned));
}

void sieve(unsigned *arr, unsigned n)
{
    unsigned i, j;

    arr[0] = arr[0] & ~(1 << 0);
    for (i = 3; i < sqrt(64*n); i += 2) 
        if (arr[i/64] & ~(1 << ((i/2)%32))) 
            for (j = i * i; j < 64*n; j += 2*i) 
                arr[j/64] = arr[j/64] & ~(1 << ((j/2)%32));
}

void display_primes(unsigned *arr, unsigned n)
{
    unsigned i, j, k, w, f;
    char nstr[10], fmt[10];

    /* determine field width for displaying prime nos. */
    sprintf(nstr, "%u", n);
    w = 1 + strlen(nstr);
    strcpy(fmt, "%");
    sprintf(nstr, "%u", w);
    strcat(fmt, nstr);
    strcat(fmt, "u");
    /* determine fields per line */
    f = 80 / w;
    /* print and count primes */
    k = 0;
    printf(fmt, 2);
    ++k;
    for (i = 0; i < ceil(n / 64.0); ++i) { /* iterate over at least one word */
        for (j = 0; j < 32; ++j) {
            if (((arr[i] ^ 0) >> j) & 1) {
                if (2 * (32 * i + j) + 1 > n)   /* done */
                    break;
                printf(fmt, 2 * (32 * i + j) + 1);
                ++k;
                if (k % f == 0)
                    putchar('\n');
            }
        }
    }
    if (k % f != 0)
        putchar('\n');
    printf("no. of primes = %u\n", k);
}

unsigned count_primes(unsigned *arr, unsigned n)
{
    unsigned i, j, k;

    /* count primes */
    k = 1;
    for (i = 0; i < ceil(n / 64.0); ++i)    /* iterate over at least one word */
        for (j = 0; j < 32; ++j)
            if (((arr[i] ^ 0) >> j) & 1) {
                if (2 * (32 * i + j) + 1 > n)   /* done */
                    break;
                ++k;
            }
    return(k);
}
