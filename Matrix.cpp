#include "Matrix.hpp"
#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

Matrix::Matrix() : mNumRows(0), mNumCols(0), mData(nullptr) { 
}

// Copy constructor
Matrix::Matrix(const Matrix& other): mNumRows(other.mNumRows), mNumCols(other.mNumCols) { 
    mData = new double*[mNumRows];  //Allocate memory 
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; ++j) {
            mData[i][j] = other.mData[i][j]; //Copy entries of the original matrix
        }
    }
}

Matrix::Matrix(int numRows, int numCols) : mNumRows(numRows), mNumCols(numCols)
{
    if (numRows <= 0 || numCols <= 0) {
        cout << "Not the size of matrix\n";
        exit(1);
    }
    mData = new double*[mNumRows]; //Trỏ dòng
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols];  //Mỗi dòng là 1 cột
        for (int j = 0; j < mNumCols; ++j)
            mData[i][j] = 0.0;
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < mNumRows; ++i) {
        delete[] mData[i];  //Delete each row
    }
    delete[] mData;  //Delete the array of pointers
}

//Getter for accessing number of rows and columns
int Matrix::numRows() const { return mNumRows; }
int Matrix::numCols() const { return mNumCols; }

//Gán
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {  //TH: A same with A
        for (int i = 0; i < mNumRows; ++i) {
            delete[] mData[i];
        }
        delete[] mData;

        mNumRows = other.mNumRows;
        mNumCols = other.mNumCols;
        mData = new double*[mNumRows];
        for (int i = 0; i < mNumRows; ++i) {
            mData[i] = new double[mNumCols];
            for (int j = 0; j < mNumCols; ++j) {
                mData[i][j] = other.mData[i][j];
            }
        }
    }
    return *this;
}


//Can write
double& Matrix::operator()(int i, int j) {
    if (i < 1 || i > mNumRows || j < 1 || j > mNumCols) {
        cout << "Out of range\n";
        exit(1);
    }
    return mData[i - 1][j - 1];
}

//Read only
double Matrix::operator()(int i, int j) const {
    if (i < 1 || i > mNumRows || j < 1 || j > mNumCols) {
        cout << "Out of range\n";
        return 0.0;
    }
    return mData[i - 1][j - 1];
}

Matrix Matrix::operator+(const Matrix& other) const {
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = mData[i][j] + other.mData[i][j];
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = mData[i][j] - other.mData[i][j];
    return result;
}

// MxM
Matrix Matrix::operator*(const Matrix& other) const {
    assert(mNumCols == other.mNumRows);
    Matrix result(mNumRows, other.mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < other.mNumCols; ++j)
            for (int k = 0; k < mNumCols; ++k)
                result.mData[i][j] += mData[i][k] * other.mData[k][j];
    return result;
}

// MxV
Vector Matrix::operator*(const Vector& vec) const {
    assert(mNumCols == vec.size());
    Vector result(mNumRows);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result[i] += mData[i][j] * vec(j + 1);
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = mData[i][j] * scalar;
    return result;
}

double Matrix::determinant() const {
    assert(mNumRows == mNumCols); // Ma trận phải vuông
    int n = mNumRows;
    // Copy to a new matrix
    double** ma2 = new double*[n];
    for (int i = 0; i < n; ++i) {
        ma2[i] = new double[n];
        for (int j = 0; j < n; ++j)
            ma2[i][j] = mData[i][j];
    }
    double det = 1.0;
    int sign = 1; //đổi dòng
    //Chose pivot
    for (int i = 0; i < n; ++i) { 
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (abs(ma2[k][i]) > abs(ma2[maxRow][i])) 
                maxRow = k;
        }
        double pivot = ma2[maxRow][i];
        if (pivot < 1e-12) { // Gần bằng 0 -> ma trận suy biến
            det = 0.0;
            break;
        }
        if (i != maxRow) {
            swap(ma2[i], ma2[maxRow]);
            sign *= -1;
        }
        det *= ma2[i][i]; // Nhân với phần tử chéo chính
        // Khử các dòng dưới
        for (int k = i + 1; k < n; ++k) {
            double factor = ma2[k][i] / ma2[i][i];
            for (int j = i; j < n; ++j)
                ma2[k][j] -= factor * ma2[i][j];
        }
    }

    // Giải phóng ma trận vừa tạo
    for (int i = 0; i < n; ++i)
        delete[] ma2[i];
    delete[] ma2;

    return det * sign;
}


Matrix Matrix::inverse() const {
    assert(mNumRows == mNumCols); 
    int n = mNumRows;
    // Tạo bản sao của ma trận gốc và ma trận đơn vị
    double** a = new double*[n];
    double** inv = new double*[n];
    for (int i = 0; i < n; ++i) {
        a[i] = new double[n];
        inv[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            a[i][j] = mData[i][j];
            inv[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Gauss-Jordan elimination
    for (int i = 0; i < n; ++i) {
        // Tìm dòng có phần tử lớn nhất ở cột i (pivot)
        int maxRow = i;
        for (int k = i + 1; k < n; ++k)
            if (fabs(a[k][i]) > fabs(a[maxRow][i]))
                maxRow = k;
        if (fabs(a[maxRow][i]) < 1e-12) {
            // Ma trận suy biến, không khả nghịch
            for (int t = 0; t < n; ++t) { delete[] a[t]; delete[] inv[t]; }
            delete[] a; delete[] inv;
            cout << "Can not invert\n";
            exit(1);
        }
        // Đổi dòng
        if (i != maxRow) {
            swap(a[i], a[maxRow]);
            swap(inv[i], inv[maxRow]);
        }
        // Chia dòng i cho phần tử chéo chính
        double pivot = a[i][i];
        for (int j = 0; j < n; ++j) {
            a[i][j] /= pivot;
            inv[i][j] /= pivot;
        }
        // Khử các dòng khác
        for (int k = 0; k < n; ++k) {
            if (k == i) continue;
            double factor = a[k][i];
            for (int j = 0; j < n; ++j) {
                a[k][j] -= factor * a[i][j];
                inv[k][j] -= factor * inv[i][j];
            }
        }
    }

    // Tạo ma trận kết quả
    Matrix result(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            result.mData[i][j] = inv[i][j];

    // Giải phóng bộ nhớ tạm
    for (int i = 0; i < n; ++i) {
        delete[] a[i];
        delete[] inv[i];
    }
    delete[] a;
    delete[] inv;

    return result;
}

Matrix Matrix::pseudoInverse(double tol) const {
    // Square matrix: use inverse if possible
    if (mNumRows == mNumCols) {
        return this->inverse();
    }
    // Tall matrix (more rows than columns): (A^T A)^{-1} A^T
    if (mNumRows > mNumCols) {
        Matrix At(mNumCols, mNumRows);
        // Compute transpose
        for (int i = 0; i < mNumRows; ++i)
            for (int j = 0; j < mNumCols; ++j)
                At(j+1, i+1) = mData[i][j];
        Matrix AtA = At * (*this);
        Matrix AtA_inv = AtA.inverse();
        return AtA_inv * At;
    }
    // Wide matrix (more columns than rows): A^T (A A^T)^{-1}
    if (mNumCols > mNumRows) {
        Matrix At(mNumCols, mNumRows);
        // Compute transpose
        for (int i = 0; i < mNumRows; ++i)
            for (int j = 0; j < mNumCols; ++j)
                At(j+1, i+1) = mData[i][j];
        Matrix AAt = (*this) * At;
        Matrix AAt_inv = AAt.inverse();
        return At * AAt_inv;
    }
    // If not handled, print error and exit
    cout << "pseudoInverse() not implemented\n";
    exit(1);
}

void Matrix::print() const {
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j)
            cout << mData[i][j] << " ";
        cout << endl;
    }
}

bool Matrix::isSymmetric(double tol) const
{
    return false;
}
