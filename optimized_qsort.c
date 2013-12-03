#include <stdlib.h>
#include <stdio.h>
#define SMALL 1000         // 1K
#define MEDIUM  10000      // 10K
#define LARGE  100000    // 100k
#define XLARGE  1000000  // 1M

void insertion_sort (int *array, int n) {
    int i, j;
    int value;
    for (i = 1; i < n; i++) {
        value = array[i];
        //printf("%d, %d\n", i, value);
        for (j = i; j > 0 && value < array[j - 1]; j--) {
            array[j] = array[j - 1];
        }
        array[j] = value;
    }
}

typedef struct qstack {
    int l, r;
} qstack_t;

void QuickSort (int *array, int n) {
    qstack_t stack[32], *sp;
    int i, j;
    int l, r;
    int tmp;
    int max_depth = 9;
    int done_bool = n <= max_depth;
    int v;
    // initialize our stack
    sp = stack;
    sp->r = n - 1;
    sp->l = 0;
    sp++;
    l = 0;
    r = n - 1;
    while (!done_bool) {
        //  MEDIAN OF THREE AS PIVOT
        //  switch array((l+r)/2) and array(l+1)
        tmp = array[(l + r) / 2];
        array[(l + r) / 2] =  array[l + 1];
        array[l + 1] = tmp;
        if ( array[l + 1] > array[r] ){
            // switch array(r) and array(l+1)
            tmp = array[r];
            array[r] =  array[l + 1];
            array[l + 1] = tmp;
        }
        if ( array[l] > array[r]) {
            // switch array(l) and array(r)
            tmp = array[r];
            array[r] = array[l];
            array[l] = tmp;
        }
        if ( array[l + 1] > array[l]) {
            // switch array(l+1) and array(l)
            tmp = array[l];
            array[l] =  array[l + 1];
            array[l + 1] = tmp;
        }
        //  END MEDIAN OF THREE PIVOT
        i = l + 1;
        j = r;
        v = array[l];
        //printf("pivot: %d\n", l);
        do {
            while (array[i] < v) {
                i++;
            }

            /* find the last element with a value <= pivot value */
            while (array[j] > v){
                j--;
            }

            if (i <= j) {
                tmp = array[j];
                array[j] =  array[i];
                array[i] = tmp;
                j--;
                i++;
            } else {
                break;
            }
        } while (1);
        // switch array(l) and array(j)
        tmp = array[l];
        array[l] = array[j];
        array[j] = tmp;
        int large_l, large_r, small_l,small_r;
        int tmp1 = r - i + 1;
        int tmp2 = j - l;
        int max, min;
        if ( tmp1 <= tmp2 ){
            large_l = l;
            large_r = j - 1;
            small_l = i;
            small_r = r;
            max = tmp2;
            min = tmp1;
        }
        else {
            large_l = i;
            large_r = r;
            small_l = l;
            small_r = j - 1;
            max = tmp1;
            min = tmp2;
        }
        if (max <= max_depth) {
            if (sp <= stack) {
                done_bool = 1;
            }
            else {
                sp--;
                l = sp->l;
                r = sp->r;
            }
            int *large = &array[large_l];
            int  large_size = large_r <= large_l ? 0 : large_r - large_l + 1;
            insertion_sort(large, large_size);
            int *small = &array[small_l];
            int  small_size = small_r <= small_l ? 0 : small_r - small_l + 1;
            insertion_sort(small, small_size);
        }
        else {
            if (min <= max_depth) {
                l = large_l;
                r = large_r;
                // insertion sort small subarray
                int *small = &array[small_l];
                int small_size = small_r <= small_l ? 0 : small_r - small_l + 1;
                insertion_sort(small, small_size);
            }
            else {
                sp->l = large_l;
                sp->r = large_r;
                sp++;
                l = small_l;
                r = small_r;
            }
        }
    }
}

int main()
{
  int n = 1000000;
  int array[n], c, d;

  printf("Generating %d integers\n", n);

  for (c = 0; c < n; c++){
    array[c] = (c << 6) % (17*17);
  }

  printf("Sorting %d integers\n You should try to time this part. \n", n);
  QuickSort(array, n);
  for ( c = 0 ; c < n-1 ; c++ )
    if (array[c] > array[c+1])   printf("Whoops: error at position %d\n", c);

  return 0;
}
