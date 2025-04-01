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
    unsigned i, j, iidx, jidx;

    arr[0] = arr[0] & ~(1 << 0);
    for (i = 3; i < sqrt(64*n); i += 2) {
        iidx = i/2;
        if (arr[iidx/32] & ~(1 << (iidx%32))) {
            for (j = i * i; j < 64*n; j += 2*i) {
                jidx = j/2;
                arr[jidx/32] = arr[jidx/32] & ~(1 << (jidx%32));
            }
        }
    }

}

void display_primes(unsigned *arr, unsigned n)
{
    unsigned i, j, k, x, y, w, f;
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
        x = 0;
        for (j = 0; j < 32; ++j) {
            y = arr[i] ^ x;
            if ((y >> j) & 1) {
                if (2 * (32 * i + j) + 1 > n)   /* done */
                    break;
                printf(fmt, 2 * (32 * i + j) + 1);
                ++k;
                if (k % f == 0)
                    putchar('\n');
            }
            x <<= 1;
        }
    }
    if (k % f != 0)
        putchar('\n');
    printf("no. of primes = %u\n", k);
}

unsigned count_primes(unsigned *arr, unsigned n)
{
    unsigned i, j, k, x, y;

    /* count primes */
    k = 1;
    for (i = 0; i < ceil(n / 64.0); ++i) { /* iterate over at least one word */
        x = 0;
        for (j = 0; j < 32; ++j) {
            y = arr[i] ^ x;
            if ((y >> j) & 1) {
                if (2 * (32 * i + j) + 1 > n)   /* done */
                    break;
                ++k;
            }
            x <<= 1;
        }
    }
    return(k);
}
