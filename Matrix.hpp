#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Vector.hpp"
#include <iostream>

class Matrix {
private:
    int mNumRows;
    int mNumCols;
    double** mData; //Con trỏ trỏ đến hàng và cột (2D array)

public:
    Matrix();
    Matrix(int numRows, int numCols);
    Matrix(const Matrix& other);
    ~Matrix();

    Matrix& operator=(const Matrix& other);

    int numRows() const;
    int numCols() const;

    double& operator()(int i, int j);        // 1-based indexing
    double operator()(int i, int j) const;   // const version

    // Operators
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Vector operator*(const Vector& vec) const;
    Matrix operator*(double scalar) const;

    // Utilities
    double determinant() const;
    Matrix inverse() const;
    Matrix pseudoInverse(double tol = 1e-10) const;

    void print() const;
    bool isSymmetric(double tol = 1e-10) const;
};

#endif // MATRIX_HPP