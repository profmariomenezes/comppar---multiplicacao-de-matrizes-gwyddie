/**
 * Created by Daniel Omiya on 16/09/21.
 */

#ifndef MATRIX_MULTIPLICATION_MATRIX_H
#define MATRIX_MULTIPLICATION_MATRIX_H

struct matrix {
  int i, j;
  long int **matrix;
};

void matrixInit(struct matrix *matrix, int i, int j);

void matrixDestroy(struct matrix *matrix);

void matrixPrint(struct matrix *matrix);

void matrixSequential(struct matrix *matrix);

void matrixRandom(struct matrix *matrix);

void matrixMultiply(struct matrix *a, struct matrix *b, struct matrix *result);

#endif
