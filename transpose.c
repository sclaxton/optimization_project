#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"

/* size of the matrices */
#define TINY 10         // 10x10
#define SMALL  100      // 100x100
#define MEDIUM 1000    // 1000x1000
#define BYTE_ALIGNMENT 16
#define CLS 64

int main() {

    int i, j, k, sum = 0;
    size_t size = 100;
    size_t cache_align = CLS;
    int first[size][size];
    int firstT[size][size];
    int multiply[size][size];

    // initalize first matrix
    for ( i= 0 ;i< size ; i++ )
        for ( j = 0 ; j < size ; j++)
            first[i][j] = ((i+j) % 2) - 1;

    // Transpose first before multiplication
    for (i = 0; i < size; ++i)
        for (j = 0; j < size; ++j)
            firstT[i][j] = first[j][i];

    for (i= 0 ;i< size ; i++ )
    {
        for ( j = 0 ; j < size ; j++ )
        {
            for ( k = 0 ; k < size ; k++ )
            {
                sum += first[i][k]*firstT[k][j];
            }
            multiply[i][j] = sum;
            printf("%d\n", multiply[i][j]);
            sum = 0;
        }
    }
    return 0;
};


