#include <iostream>
#include <cstdlib>

using namespace std;

void alloc_matrices(int N, double **&a, double **&b, double **&c)
{
    a = new double*[N];
    b = new double*[N];
    c = new double*[N];

    for (int i = 0; i < N; ++i) {
        a[i] = new double[N];
        b[i] = new double[N];
        c[i] = new double[N];
    }
}

void init_matrices(int N, double **a, double **b, double **c)
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            a[i][j] = ((double)rand()) / RAND_MAX;
            b[i][j] = ((double)rand()) / RAND_MAX;
            c[i][j] = 0;
        }
}

void gemm(int N, double **a, double **b, double **c)
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                c[i][j] += a[i][k] * b[k][j];
}

int main(int argc, char *argv[])
{
    int N = std::atoi(argv[1]);

    double **a, **b, **c;

    alloc_matrices(N, a, b, c);
    init_matrices(N, a, b, c);
    gemm(N, a, b, c);

    return 0;
}
