#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// include SSE4.1
#include <smmintrin.h>
// include SSE2
#include <emmintrin.h>
#include "util.h"

/* size of the matrices */
#define LARGE 5000    // 5000x5000
#define YOURSIZE 100    // define your own
#define BYTE_ALIGNMENT 16
#define CLS 64
#define BLOCK_SIZE (CLS / sizeof(int))

int posix_memalign(void**, size_t, size_t);
__m128i _mm_mullo_epi32 (__m128i a, __m128i b);
__m128i _mm_loadu_si128 (__m128i const* mem_addr);
void _mm_storeu_si128 (__m128i* mem_addr, __m128i a);
int i, j, k, i_block, j_block, k_block, sum = 0;

size_t block_size = BLOCK_SIZE;
size_t size = 100;
size_t cache_align = CLS;
void* first_alloc = 0;
void* result_alloc = 0;

int main() {

    // dynamically allocate large matrix as an array with cache line alignment
    posix_memalign(&first_alloc, cache_align, size*size*sizeof(int));
    posix_memalign(&result_alloc, cache_align, size*size*sizeof(int));

    int *first, *res_block, *result, *first_blocks1, *first_blocks2 = 0;

    first = (int*) first_alloc;
    result = (int*) result_alloc;

    // intialize matrix
    for ( i= 0 ;i< size ; i++ ) {
        for ( j = 0 ; j < size ; j++) {
            first[i*size + j] = ((i+j) % 2) - 1;
            result[i*size + j] = 0;
        }
    }

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
                for (i_block = 0, res_block = &result[i*size + j], first_blocks1 = &first[i*size + k];
                    (i_block < block_size) && (i + i_block < size);
                    ++i_block, res_block += size, first_blocks1 += size) {
                    for (k_block = 0, first_blocks2 =  &first[k*size + j];
                        (k_block < block_size) && (k + k_block < size); ++k_block, first_blocks2 += size) {
                        // here we unroll what would be the inner loop
                        // looping over j_block in the computation of the
                        // multiplication of blocks of the first matrix
                        int first_blocks1_k_block = first_blocks1[k_block];
                        if (j + block_size < size) {
                            __m128i first_vec1 = _mm_set_epi32(first_blocks1_k_block, first_blocks1_k_block,
                            first_blocks1_k_block, first_blocks1_k_block);
                            __m128i *first_point = (__m128i*) &first_blocks2[0];
                            __m128i first_vec2 = _mm_loadu_si128 (first_point);
                            __m128i *res_point = (__m128i*) &res_block[0];
                            __m128i res_vec = _mm_loadu_si128(res_point);
                            __m128i mult_vec = _mm_mullo_epi32(first_vec2, first_vec1);
                            __m128i add_res_vec = _mm_add_epi32(mult_vec, res_vec);
                            _mm_storeu_si128(res_point,add_res_vec);
                            first_point = (__m128i*) &first_blocks2[4];
                            first_vec2 = _mm_loadu_si128 (first_point);
                            res_point = (__m128i*) &res_block[4];
                            res_vec = _mm_loadu_si128(res_point);
                            mult_vec = _mm_mullo_epi32(first_vec2, first_vec1);
                            add_res_vec = _mm_add_epi32(mult_vec, res_vec);
                            _mm_storeu_si128(res_point,add_res_vec);
                            first_point = (__m128i*) &first_blocks2[8];
                            first_vec2 = _mm_loadu_si128 (first_point);
                            res_point = (__m128i*) &res_block[8];
                            res_vec = _mm_loadu_si128(res_point);
                            mult_vec = _mm_mullo_epi32(first_vec2, first_vec1);
                            add_res_vec = _mm_add_epi32(mult_vec, res_vec);
                            _mm_storeu_si128(res_point,add_res_vec);
                            first_point = (__m128i*) &first_blocks2[12];
                            first_vec2 = _mm_loadu_si128 (first_point);
                            res_point = (__m128i*) &res_block[12];
                            res_vec = _mm_loadu_si128(res_point);
                            mult_vec = _mm_mullo_epi32(first_vec2, first_vec1);
                            add_res_vec = _mm_add_epi32(mult_vec, res_vec);
                            _mm_storeu_si128(res_point,add_res_vec);
                        }
                        else {
                            //printf("%d, %d, %d, %d, %d\n", i, j, k, i_block, k_block);
                            int *res_block_int = (int*) res_block;
                            int *first_blocks2_int = (int*) first_blocks2;
                            for (j_block = 0; j + j_block < size; ++j_block ){
                                res_block_int[j_block] = first_blocks1_k_block * first_blocks2_int[j_block];
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}


