#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


double find_det(double **a_ptr_det, int a_size_det);
long int mtime();

double find_det(double **a_ptr_det, int a_size_det)
{
    const double eps = 0.000001;

    double res = 1;
    int i, j, k;
    int new_i = 0, new_j = 0;
    double tmp;

    for (k = 0; k < a_size_det - 1; k++)
    {
        if (fabs(a_ptr_det[new_i][new_j]) < eps)
        {
            i = new_i + 1; j = new_j;
            while ((i < a_size_det) && (fabs(a_ptr_det[i][j]) < eps)) i++;
            if (i == a_size_det) return res = 0;
            for (; j < a_size_det; j++)
                {
                    tmp = a_ptr_det[new_i][j];
                    a_ptr_det[new_i][j] = a_ptr_det[i][j];
                    a_ptr_det[i][j] = tmp;
                }

            res *= -1;
        }

        res *= a_ptr_det[new_i][new_j];

        for (j = new_j + 1; j < a_size_det; j++)
            for (i = new_i + 1; i < a_size_det; i++)
                a_ptr_det[i][j] +=
                ((a_ptr_det[i][new_j] * -1) /
                 a_ptr_det[new_i][new_j]) * a_ptr_det[new_i][j];

        j = new_j;
        for (i = new_i + 1; i < a_size_det; i++)
            a_ptr_det[i][j] = 0;

        new_i++; new_j++;
    }
    res *= a_ptr_det[a_size_det - 1][a_size_det - 1];


    return res + 0.0;
}

long int mtime()
{
    struct timespec time;

    long int mt;

    clock_gettime(CLOCK_REALTIME, &time);
    mt = time.tv_sec * 1000 + time.tv_nsec / 1000000;


    return mt;
}

int main()
{
    const int max_size_det = 1000;

    double **ptr_det;
    int size_det;
    int i, j;
    double val_det;
    long int t_start, t_ex = 0;

    srand(time(NULL));

    for (size_det = 0; size_det <= max_size_det; size_det += 25)
    {
        printf("%ld\n", t_ex);
        if (size_det == 0) continue;

        ptr_det = (double**)malloc(size_det * sizeof(double*));
        for (i = 0; i < size_det; i++)
            ptr_det[i] = (double*)malloc(size_det * sizeof(double));

        for (i = 0; i < size_det; i++)
            for (j = 0; j < size_det; j++)
                ptr_det[i][j] = (double)(rand()) / (double)(rand() + 1);

        t_start = mtime();
        val_det = find_det(ptr_det, size_det);
        t_ex = mtime() - t_start;

        for (i = 0; i < size_det; i++)
            free(ptr_det[i]);
        free(ptr_det);
    }


    return 0;
}
