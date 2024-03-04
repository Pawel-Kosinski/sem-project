#include <stdio.h>
#include <stdlib.h>

void rozkladLU(double** A, double** L, double** U, int n) {
    for (int i = 0; i < n; i++) {
        L[i][i] = 1.0;

        for (int j = i; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < i; k++)
                sum += L[i][k] * U[k][j];
            U[i][j] = A[i][j] - sum;
        }

        for (int j = i + 1; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < i; k++)
                sum += L[j][k] * U[k][i];
            L[j][i] = (A[j][i] - sum) / U[i][i];
        }
    }
}

double* rownanieLU(double** A, double* b, int n) {
    double* x = (double*)malloc(n * sizeof(double));
    double* y = (double*)malloc(n * sizeof(double));
    double** L = (double**)malloc(n * sizeof(double*));
    double** U = (double**)malloc(n * sizeof(double*));

    for (int i = 0; i < n; i++) {
        L[i] = (double*)malloc(n * sizeof(double));
        U[i] = (double*)malloc(n * sizeof(double));
    }

    rozkladLU(A, L, U, n);

    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < i; j++)
            sum += L[i][j] * y[j];
        y[i] = (b[i] - sum) / L[i][i];
    }

    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++)
            sum += U[i][j] * x[j];
        x[i] = (y[i] - sum) / U[i][i];
    }

    for (int i = 0; i < n; i++) {
        free(L[i]);
        free(U[i]);
    }

    free(L);
    free(U);
    free(y);

    return x;
}

int main() {
    int n;
    printf("Podaj wymiar macierzy A: ");
    if (scanf_s("%d", &n) != 1)
    {
        printf("Bledne dane. \n");
        return 0;
    }

    double** A = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) 
        A[i] = (double*)malloc(n * sizeof(double));
    
    printf("Podaj elementy macierzy A:\n");
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) {
            if (scanf_s("%lf", &A[i][j]) != 1)
            {
                printf("Bledne dane. \n");
                return 0;
            }
        }
        
    double* b= (double*)malloc(n * sizeof(double*));
    printf("Podaj elementy wektora b:\n");
    for (int i = 0; i < n; i++) {
        if(scanf_s("%lf", &b[i])!=1)
        {
            printf("Bledne dane. \n");
            return 0;
        }
    }
    double* x = rownanieLU(A, b, n);

    printf("Solution:\n");
    for (int i = 0; i < n; i++) 
        printf("x[%d] = %.6f\n", i, x[i]);
    
    for (int i = 0; i < n; i++) 
        free(A[i]);
    
    free(A);
    free(x);
    free(b);
    return 0;
}