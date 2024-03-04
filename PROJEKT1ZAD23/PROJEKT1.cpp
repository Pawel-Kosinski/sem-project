#include <stdio.h>
#include <math.h>

double szereg(double a, double b, int n, int M, double dokladnosc);

int main()
{
    double a = -1, b = 1, dokladnosc = 0;
    int n, M;

    printf("Podaj poczatek i koniec przedzialu: (musi sie zawierac w (-1,1>) \n");
    if (scanf_s("%lf %lf", &a, &b) != 2 || a <= -1 || b > 1)
    {
        printf("Bledne dane. \n");
        return 0;
    }

    printf("Z jaka dokladnoscia chcesz obliczyc szereg? \n");
    if (scanf_s("%lf", &dokladnosc) != 1)
    {
        printf("Bledne dane. \n");
        return 0;
    }

    printf("Ile wyrazow chcesz sumowac? \n");
    if (scanf_s("%d", &M) != 1)
    {
        printf("Bledne dane. \n");
        return 0;
    }

    printf("Na ile czesci chcesz podzielic przedzial? \n");
    if (scanf_s("%d", &n) != 1)
    {
        printf("Bledne dane. \n");
        return 0;
    }

    double result = szereg(a, b, n, M, dokladnosc);

    if (result == 1)
        printf("Dokladnosc nie zostala osiagnieta. \n");
    else
        printf("Dokladnosc zostala osiagnieta.\n");

    return 0;
}

double szereg(double a, double b, int n, int M, double dokladnosc)
{
    double x, suma = 0.0, wartosc = 0;

    for (int j = 0; j < n; j++)
    {
        wartosc = 0;
        x = a + j * (b - a) / (n - 1);

        for (int i = 0; i < M; i++)
            wartosc += (i % 2 == 0 ? 1 : -1) * pow(x, i + 1) / (i + 1);

        double wanalityczna = log(1 + x);

        if (fabs(wartosc - wanalityczna) > dokladnosc)
            return 1;

        printf("x%d = %lf \n", j, wartosc);
        suma += wartosc;
    }

    printf("Suma szeregu wynosi: %lf \n", suma);

    return 0;
}
