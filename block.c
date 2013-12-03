#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"

/* size of the matrices */
#define LARGE 5000    // 5000x5000
#define YOURSIZE 100    // define your own
#define CLS 64
#define BLOCK_SIZE (CLS / sizeof(int))

int i, j, k, i_block, j_block, k_block, sum = 0;
size_t block_size = BLOCK_SIZE;
size_t size = 100;
size_t cache_align = CLS;

int main() {

    int *first_blocks1, *first_blocks2, *res_block;
    int first[size][size] __attribute__ ((aligned (64)));
    int result[size][size] __attribute__ ((aligned (64)));

    // intialize matrix
    for ( i= 0 ;i< size ; i++ )
        for ( j = 0 ; j < size ; j++)
            first[i][j] = ((i+j) % 2) - 1;

    // multiply the matrix in blocks determined by the cache
    // line size for optimal cache usage
    for (i= 0 ; i < size ; i += block_size ) {
        for ( j = 0 ; j < size ; j += block_size ) {
            // computation of the block of the result
            // matrix of size block_size with upper,
            // right most index at i,j
            for ( k = 0 ; k < size ; k += block_size ) {
                // multiplication of blocks of the first matrix
                // corresponding to the summands of the comuputation
                // of the block of the result matrix being computed
                for (i_block = 0, res_block = &result[i][j],
                    first_blocks1 = &first[i][k]; (i_block < block_size) && (i + i_block < size);
                    ++i_block, res_block += size, first_blocks1 += size) {
                    for (k_block = 0, first_blocks2 = &first[k][j];
                        (k_block < block_size) && (k + k_block < size); ++k_block, first_blocks2 += size) {
                        // here we unroll what would be the inner loop
                        // looping over j_block in the computation of the
                        // multiplication of blocks of the first matrix
                        int first_blocks1_k_block = first_blocks1[k_block];
                        if (j + block_size < size) {
                            res_block[0] += first_blocks1_k_block * first_blocks2[0];
                            res_block[1] += first_blocks1_k_block * first_blocks2[1];
                            res_block[2] += first_blocks1_k_block * first_blocks2[2];
                            res_block[3] += first_blocks1_k_block * first_blocks2[3];
                            res_block[4] += first_blocks1_k_block * first_blocks2[4];
                            res_block[5] += first_blocks1_k_block * first_blocks2[5];
                            res_block[6] += first_blocks1_k_block * first_blocks2[6];
                            res_block[7] += first_blocks1_k_block * first_blocks2[7];
                            res_block[8] += first_blocks1_k_block * first_blocks2[8];
                            res_block[9] += first_blocks1_k_block * first_blocks2[9];
                            res_block[10] += first_blocks1_k_block * first_blocks2[10];
                            res_block[11] += first_blocks1_k_block * first_blocks2[11];
                            res_block[12] += first_blocks1_k_block * first_blocks2[12];
                            res_block[13] += first_blocks1_k_block * first_blocks2[13];
                            res_block[14] += first_blocks1_k_block * first_blocks2[14];
                            res_block[15] += first_blocks1_k_block * first_blocks2[15];
                        }
                        else {
                            for (j_block = 0; j + j_block < size; j_block++ ){
                                res_block[j_block] = first_blocks1_k_block * first_blocks2[j_block];
                            }
                        }
                    }
                }
            }
        }
    }
    for ( i= 0 ;i< size ; i++ )
            for ( j = 0 ; j < size ; j++)
                printf("%d\n", result[i][j]);
    return 0;
}


