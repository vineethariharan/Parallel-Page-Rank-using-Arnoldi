#ifndef MATRIX_H
#define MATRIX_H
typedef struct Matrix{
    double **A;
    int A_rows;
    int A_cols;
}Matrix;

void initMatrix(Matrix* A, int rows, int cols);
void displayMat(Matrix* Mat);
void displayMatStruct(Matrix* Mat);
void displayVector(double* q, int length);
void matrixTranspose(Matrix* Mat);
void setNull(double** A, int rows, int cols);

#endif
