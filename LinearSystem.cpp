#include "LinearSystem.hpp"
#include <cmath>
#include <iostream>
#include <cassert>
using namespace std;

LinearSystem::LinearSystem() {} //không truy cập

LinearSystem::LinearSystem(const LinearSystem&) {}  // không cho phép copy

LinearSystem::LinearSystem(const Matrix& A, const Vector& b): mSize(A.numRows()) { // Constructor nhận matrix vector
    if (A.numRows() != A.numCols())
        assert(A.numRows() == A.numCols());
    if (A.numRows() != b.size())
        assert(A.numRows() == b.size());
    mpA = new Matrix(A);
    mpb = new Vector(b);
}

LinearSystem::~LinearSystem() {
    delete mpA;
    delete mpb;
}

Vector LinearSystem::Solve() {
    Matrix A = *mpA;
    Vector b = *mpb;
    Vector x(mSize);

    // Gaussian elimination with partial pivoting
    for (size_t k = 0; k < mSize; ++k) {
        // Find pivot
        size_t maxRow = k;
        double maxVal = std::abs(A(k + 1, k + 1));
        for (size_t i = k + 1; i < mSize; ++i) {
            if (abs(A(i + 1, k + 1)) > maxVal) {
                maxVal = abs(A(i + 1, k + 1));
                maxRow = i;
            }
        }
        // Swap rows in A and b
        if (maxRow != k) {
            for (size_t j = 1; j <= mSize; ++j)
                swap(A(k + 1, j), A(maxRow + 1, j));
            swap(b[k], b[maxRow]);
        }
        // Elimination
        for (size_t i = k + 1; i < mSize; ++i) {
            double factor = A(i + 1, k + 1) / A(k + 1, k + 1);
            for (size_t j = k + 1; j <= mSize; ++j)
                A(i + 1, j) -= factor * A(k + 1, j);
            b[i] -= factor * b[k];
        }
    }
    // Back substitution
    for (int i = mSize - 1; i >= 0; --i) {
        x[i] = b[i];
        for (size_t j = i + 1; j < mSize; ++j)
            x[i] -= A(i + 1, j + 1) * x[j];
        x[i] /= A(i + 1, i + 1);
    }
    return x;  // trả về object vector
}


