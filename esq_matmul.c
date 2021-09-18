#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N_SIZES 10

int main() {
  /* size of matrices to be generated */
  int sizes[N_SIZES] = {32, 64, 128, 256, 512, 640, 768, 896, 1024, 1536};
  struct matrix a, b, result;
  struct timeval startedAt, endedAt;
  long spentMicroseconds;
  int i;

  for (i = 0; i < N_SIZES; i++) {
    /* init matrices with random values */
    matrixInit(&a, sizes[i], sizes[i]);
    matrixRandom(&a);

    matrixInit(&b, sizes[i], sizes[i]);
    matrixRandom(&b);

    printf("MULTIPLYING MATRICES OF SIZE %d x %d: ", sizes[i], sizes[i]);

    /* start stopwatch */
    gettimeofday(&startedAt, NULL);

    /* do the magic */
    matrixMultiply(&a, &b, &result);

    /* calculate total microseconds */
    gettimeofday(&endedAt, NULL);
    spentMicroseconds = ((endedAt.tv_sec * 1000000 + endedAt.tv_usec) -
                         (startedAt.tv_sec * 1000000 + startedAt.tv_usec));

    printf("spent %lf seconds\n", (double)spentMicroseconds / 1e+6);

    /* destroy allocated memory */
    matrixDestroy(&a);
    matrixDestroy(&b);
    matrixDestroy(&result);
  }

  return EXIT_SUCCESS;
}
