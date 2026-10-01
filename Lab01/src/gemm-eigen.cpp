#include <iostream>
#include <cstdlib>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

void allocate_matrices(int N, MatrixXd &a, MatrixXd &b, MatrixXd &c)
{
    a.resize(N, N);
    b.resize(N, N);
    c.resize(N, N);
}

void initialize_matrices(MatrixXd &a, MatrixXd &b, MatrixXd &c)
{
    a = MatrixXd::Random(a.rows(), a.cols());
    b = MatrixXd::Random(b.rows(), b.cols());
    c.setZero();
}

void gemm(const MatrixXd &a, const MatrixXd &b, MatrixXd &c)
{
    c = a * b;
}

int main(int argc, char *argv[])
{
    int N = std::atoi(argv[1]);

    MatrixXd a, b, c;

    allocate_matrices(N, a, b, c);
    initialize_matrices(a, b, c);
    gemm(a, b, c);

    return 0;
}