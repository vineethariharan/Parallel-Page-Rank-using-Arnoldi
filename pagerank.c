#include <stdio.h>
#include <stdlib.h>
#include "arnoldi.h"
#include "matrix.h"
#include <math.h>
#include <string.h>
#include "filereader.h"
#include "svd.h"
int main()
{
    Matrix A;
    Matrix Q;
    Matrix H;
    Matrix V;
    Matrix Aq;
    double *diag;
    double *q;
    double *v;

    int k = 32;
    int n;

    readInput(&A,"ip2.txt",0.85);
    n = A.A_rows;
    initMatrix(&Aq, n, 1);
    initMatrix(&Q, n, k+1);
    initMatrix(&H, k+1, k);
    initMatrix(&V, k, k);

    matrixTranspose(&A);
    // printf("\n A transpose is \n");
    // displayMat(&A);

    diag = (double*)malloc(sizeof(double)*(k));
    v = (double *)malloc(sizeof(double) * k);
    q = (double*)malloc(sizeof(double)*(n));

    for(int i=0; i<n; i++) q[i] = 1;// rand()%10 + 1;

    // start fold
    for(int fold = 0; fold < 100; fold++)
    {
        setNull(Q.A, n, k+1);
        setNull(H.A, k+1, k);

        //#############  Calling Arnoldi to get Q and H  ##################
        plainArnoldi(&Q, &H, &A, q, k);

        for(int i = 0; i < k; i++)
        {
            H.A[i][i] -= 1;
        }

        /*
        ###############  Calling SVD on H-I   #####################
        */
        dsvd(H.A,H.A_rows, H.A_cols, diag, V.A);

        int smallestEigen = 9999;
        int smallestIndex = 0;

        for(int i = 0; i < k; i++)
        {
            for(int j = 0; j < k; j++)
            {
                if(i == j)
                {
                    if(diag[i] < smallestEigen)
                    {
                        smallestEigen = diag[i];
                        smallestIndex = i;
                    }
                    // printf(" %lf ",diag[i]);
                }
                    // printf(" 0 ");
            }
            // printf("\n");
        }

        // Selecting singular vector corresponding to smallest singular value
        for(int i = 0; i < k; i++)
        {
            double f;
            v[i] = V.A[i][smallestIndex];
        }

        double **QMat = Q.A;

        for(int i=0;i < Q.A_rows;i++){
            double tempDot = 0;
            for(int l=0;l<k;l++){
                tempDot+=QMat[i][l]*v[l];
            }
            q[i] = tempDot;
        }

        double temp = 0;
        for(int i = 0; i < n; i++) temp += q[i]*q[i];
            temp = sqrt(temp);

        // printf("\n Aq \n");

        for(int i=0;i < n;i++){
            double tempDot = 0;
            for(int l=0;l<n;l++){
                tempDot += A.A[i][l]*q[l];
            }
            Aq.A[i][0] = tempDot;
        }
        // displayMat(&Aq);


        // printf("\nAq - q \n");
        double tempDot = 0;
        for(int i=0;i < n;i++)
        {
            Aq.A[i][0] -= q[i];
            tempDot += Aq.A[i][0] * Aq.A[i][0];
        }
        // displayMat(&Aq);

        double normDiff = sqrt(tempDot);
       /* printf("\nAq-q norm for %d\n",fold);
        printf("%.20lf \n",normDiff);
        if(normDiff < 0.000001){
            printf("Converged in %d folds.\n", fold);
            break;
        }*/
    }

    // end fold
    int neg = 1;
    if(q[0]<0)
        neg = -1;
    for(int i=0;i < n;i++){
           printf("%lf\n",q[i] * neg);
        }
    free(A.A[0]);
    free(A.A);
    free(Q.A[0]);
    free(Q.A);
    free(H.A[0]);
    free(H.A);
    free(Aq.A[0]);
    free(Aq.A);
    free(V.A[0]);
    free(V.A);
    free(v);
    free(q);
    return 0;

}
