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

void dump(unsigned *arr, unsigned n)
{
    unsigned i, j, k, x, y;

    /* print primes */
    k = 0;
    printf("     2");
    ++k;
    for (i = 0; i < ceil(n / 64.0); ++i) { /* iterate over at least one word */
        x = 0;
        for (j = 0; j < 32; ++j) {
            y = arr[i] ^ x;
            if ((y >> j) & 1) {
                if (2 * (32 * i + j) + 1 > n)   /* done */
                    break;
                printf("%6u", 2 * (32 * i + j) + 1);
                ++k;
                if (k%13 == 0)
                    putchar('\n');
            }
            x <<= 1;
        }
    }
    putchar('\n');
    printf("no. of primes = %u\n", k);
}
