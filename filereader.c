#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "filereader.h"


void readInput(Matrix *MatA, char *fileName, double dampingFactor)
{
    FILE *fp = fopen(fileName, "r");
    char *line = NULL;
    size_t len = 0;
    int fold = 0;
    int numOfWebPages = 0;
    double **A;
    int counter, ones, col, row;
    int i, j, val;
    int count = 0;
    double randomJumpFactor;
    while(getline(&line, &len, fp) != -1)
    {
        //printf("\n line = %s ", line);
        if(fold == 0)
        {
            numOfWebPages = atoi(line);
            randomJumpFactor = (1 - dampingFactor) / (numOfWebPages);

            A  = (double **)malloc(sizeof(double *) * numOfWebPages);
            A[0] = (double *)calloc(sizeof(double), numOfWebPages * numOfWebPages);
            for(i = 0; i < numOfWebPages; i++)
                A[i] = (*A + numOfWebPages * i);
            fold++;
        }
        else
        {
            ones = 0;
            row = fold-1;
            col = 0;
            char *link = strtok(line, " ");
            while (link != NULL)
            {
                val = atoi(link);
                A[row][col] = val;
                if(val)
                    ones++;
                link = strtok(NULL, " ");
                col++;
            }
            // printf("%d ", ones );
            for(i = 0; i < numOfWebPages; i++){
                if(!ones){
                    ones = 1;
                    count++;
                }

                A[row][i] = A[row][i]*dampingFactor/ones + randomJumpFactor;
            }

            fold++;
        }
    }
    MatA->A = A;
    MatA->A_rows = numOfWebPages;
    MatA->A_cols = numOfWebPages;
    // printf("\n");
}
