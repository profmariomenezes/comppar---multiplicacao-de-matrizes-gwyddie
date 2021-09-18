#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SEED 1105277
#define TRUE (1 == 1)
#define FALSE (!TRUE)

typedef int boolean;

int getRandom() {
  static boolean isInitialized = FALSE;

  if (!isInitialized) {
    srand(time(NULL) + SEED);
    isInitialized = TRUE;
  }

  return rand();
}

void matrixInit(struct matrix *matrix, int i, int j) {
  int x;
  matrix->i = i;
  matrix->j = j;

  matrix->matrix = malloc(sizeof(long int *) * i);

  for (x = 0; x < i; x++) {
    matrix->matrix[x] = calloc(j, sizeof(long int));
  }
}

void matrixDestroy(struct matrix *matrix) {
  int i;
  for (i = 0; i < matrix->i; i++) {
    free(matrix->matrix[i]);
  }
  free(matrix->matrix);
}

void matrixPrint(struct matrix *matrix) {
  int i, j;
  for (i = 0; i < matrix->i; i++) {
    for (j = 0; j < matrix->j; j++) {
      printf("%ld ", matrix->matrix[i][j]);
    }
    printf("\n");
  }
}

void matrixSequential(struct matrix *matrix) {
  int i, j, counter = 1;
  for (i = 0; i < matrix->i; i++)
    for (j = 0; j < matrix->j; j++)
      matrix->matrix[i][j] = counter++;
}

void matrixRandom(struct matrix *matrix) {
  int i, j;

  for (i = 0; i < matrix->i; i++)
    for (j = 0; j < matrix->j; j++)
      matrix->matrix[i][j] = getRandom();
}

void matrixMultiply(struct matrix *a, struct matrix *b, struct matrix *result) {
  int i, j, k;

  if (a->j != b->i) {
    matrixInit(result, 0, 0);
    return;
  }

  matrixInit(result, a->i, b->j);

  for (i = 0; i < result->i; i++)
    for (k = 0; k < result->i; k++)
      for (j = 0; j < result->j; j++)
        result->matrix[i][j] += a->matrix[i][k] * b->matrix[k][j];
}
