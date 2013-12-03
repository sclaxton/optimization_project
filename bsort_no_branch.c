/* Bubble sort code */

#include <stdio.h>
#include <mmintrin.h>
#include <xmmintrin.h>
#define SMALL 1000         // 1K
#define MEDIUM  10000      // 10K
#define LARGE  100000    // 100k
#define XLARGE  1000000  // 1M

int main()
{
  int n = 100000;
  int array[n], c, d, swap, tmp;

  printf("Generating %d Integers\n", n);

  for (c = 0; c < n; c++){
    array[c] = (c << 6) % (17*17);
  }

  printf("Sorting %d integers\n You should try to time this part. \n", n);
  for (c = 0 ; c < ( n - 1 ); c++)
    {
      for (d = 0 ; d < n - c - 1; d++)
	{
        tmp = array[d];
        swap = array[d] > array[d+1];
        array[d] = swap ? array[d+1] : tmp;
        array[d+1] = swap ? tmp : array[d+1];
    }
    }
  return 0;
}
