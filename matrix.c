#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
void setNull(double** A, int rows, int cols){
    for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    A[i][j] = 0;
                }
            }
}
void initMatrix(Matrix* A, int rows, int cols){
    double **a;
    a  = (double **)malloc(sizeof(double *) * rows);
    a[0] = (double *)calloc(sizeof(double), rows * cols);
    for(int i = 0; i < rows; i++)
        a[i] = (*a + cols * i);
    A->A = a;
    A->A_rows = rows;
    A->A_cols = cols;
}
void displayMat(Matrix* Mat){
    for(int i=0; i<Mat->A_rows; i++){
        for (int j = 0;  j < Mat->A_cols; j++){
            printf("%lf ",Mat->A[i][j]);
        }
        printf("\n");
    }
}

void displayVector(double* q, int length){
    for(int i=0; i< length; i++){
        printf(" %lf ",q[i]);
    }
}

void displayMatStruct(Matrix* Mat){
    for(int i=0; i<Mat->A_rows; i++){
        for (int j = 0;  j <Mat->A_cols; j++){
            if(Mat->A[i][j] == 0.0)
                printf("0  ");
            else
                printf("1  ");
        }
        printf("\n");
    }
}
void matrixTranspose(Matrix* Mat){
    double temp;
    for(int i=0; i<Mat->A_rows; i++){
        for (int j = 0;  j < i; j++){
            temp = Mat->A[i][j];
            Mat->A[i][j] = Mat->A[j][i];
            Mat->A[j][i] = temp;
        }
    }
}
