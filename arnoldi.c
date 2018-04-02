#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "arnoldi.h"
#include "matrix.h"

void plainArnoldi(Matrix *Q, Matrix *H, Matrix *A, double *q, int k){
    int n = A->A_rows;
    double *z;
    double tempNorm = 0.0;
    double **AMat = A->A;
    double **QMat = Q->A;
    double **HMat = H->A;

    for(int i=0;i<n;i++){
        tempNorm += q[i]*q[i];
    }
    tempNorm = sqrt(tempNorm);

    for(int i=0;i<n;i++){
        QMat[i][0] = q[i]/tempNorm;
    }

    z = (double *)malloc(sizeof(double)*(n));
    for(int j = 0; j < k; j++)
    {

        for(int i = 0; i < n; i++)
        {
            double tempDot =0;
            for(int l = 0; l < n; l++)
                tempDot += AMat[i][l]*QMat[l][j];
            z[i] = tempDot;
        }

        for(int i = 0; i <= j; i++)
        {
            double tempDot = 0.0;
            for(int l = 0; l < n; l++)
            {
                tempDot+=QMat[l][i]*z[l];
            }
            HMat[i][j] = tempDot;


            for(int l = 0; l < n; l++)
            {
                z[l] -= tempDot * QMat[l][i];
            }
        }
        tempNorm = 0;

        for(int i = 0; i < n; i++)
        {
            tempNorm += z[i]*z[i];
        }
        tempNorm = sqrt(tempNorm);
        HMat[j+1][j] = tempNorm;

        for(int l = 0; l < n; l++)
        {
            QMat[l][j+1] = z[l]/ tempNorm;
        }


    }
    free(z);
}
