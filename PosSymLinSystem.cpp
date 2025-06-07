#include "LinearSystem.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <cassert>
using namespace std;

PosSymLinSystem::PosSymLinSystem(const Matrix& A, const Vector& b): LinearSystem(A, b) {
    if (!A.isSymmetric())
        assert(A.isSymmetric() && "Not symmetric\n");
}

Vector PosSymLinSystem::Solve() {
    // Conjugate Gradient method
    Vector x(mSize); // Khởi tạo x = 0
    Vector r = *mpb - (*mpA * x);
    Vector p = r;
    double rsold = 0;
    for (int i = 0; i < mSize; ++i)
        rsold += r[i] * r[i];

    for (int iter = 0; iter < mSize; ++iter) {
        Vector Ap = (*mpA) * p;
        double alpha = rsold;
        double pAp = 0;
        for (int i = 0; i < mSize; ++i)
            pAp += p[i] * Ap[i];
        alpha /= pAp;
        for (int i = 0; i < mSize; ++i)
            x[i] += alpha * p[i];
        for (int i = 0; i < mSize; ++i)
            r[i] -= alpha * Ap[i];
        double rsnew = 0;
        for (int i = 0; i < mSize; ++i)
            rsnew += r[i] * r[i];
        if (sqrt(rsnew) < 1e-10)
            break;
        for (int i = 0; i < mSize; ++i)
            p[i] = r[i] + (rsnew / rsold) * p[i];
        rsold = rsnew;
    }
    return x;
}