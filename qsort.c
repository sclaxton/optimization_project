#include <stdlib.h>
#include <stdio.h>
#define SMALL 1000         // 1K
#define MEDIUM  10000      // 10K
#define LARGE  100000    // 100k
#define XLARGE  1000000  // 1M

void QuickSort_recur(int *array, int l, int r) {
    if (l < r) {
        int tmp;
        int p_index = l; //pivot index
        int p_val = array[p_index];
        tmp = p_val;
        array[p_index] = array[r];
        array[r] = tmp;
        int store_index = l;
        int i;
        for (i = l; i  < r; i++) {
            if ( array[i] < p_val ){
                tmp = array[i];
                array[i] = array[store_index];
                array[store_index] = tmp;
                store_index++;
            }
        }
        tmp = array[r];
        array[r] = array[store_index];
        array[store_index] = tmp;
        QuickSort_recur(array, l, store_index - 1);
        QuickSort_recur(array, store_index + 1, r);
    }
}

void QuickSort(int *array, int size){
    int l = 0;
    int r = size - 1;
    QuickSort_recur(array, l, r);
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

  return 0;
}
