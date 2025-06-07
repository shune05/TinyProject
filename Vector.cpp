#include "Vector.hpp"
#include <iostream>
using namespace std;

Vector::Vector() : mSize(0), mData(nullptr) {}

// Initialization constructor
Vector::Vector(int size) : mSize(size), mData(nullptr) {  //Lớp::Hàm
    if (size >0){
        mData = new double[mSize];
        for (int i = 0; i < mSize; ++i)
            mData[i] = 0.0; // Initialize with 0.0
    } 
 
} 

//Truyền vào giá trị
Vector::Vector(const double* values, int size) : mSize(size), mData(nullptr) { // use const double* to make sure just only read the input values
        if (mSize > 0) {
            mData = new double[mSize];
            for (int i = 0; i < mSize; ++i)
                mData[i] = values[i];
        }
    }

// Copy constructor
Vector::Vector(const Vector& other) : mSize(other.mSize), mData(new double[other.mSize]) {
    for (int i = 0; i < mSize; ++i)
        mData[i] = other.mData[i];
}

// Destructor
Vector::~Vector() {
    delete[] mData;
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) return *this;
    delete[] mData;
    mSize = other.mSize;
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i)
        mData[i] = other.mData[i];
    return *this;
}

Vector Vector::operator+(const Vector& other) const {
    if (mSize != other.mSize) {
        cout << "Can not addtion\n";
        return Vector(0);
    }
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] + other.mData[i];
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    if (mSize != other.mSize) {
        cout << "Can not subtraction\n";
        return Vector(0);
    }
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] - other.mData[i];
    return result;
}

// Vetor * scalar
Vector Vector::operator*(double scalar) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] * scalar;
    return result;
}

// Scalar * vector
Vector operator*(double scalar, const Vector& vec) {
    Vector result(vec.mSize);
    for (int i = 0; i < vec.mSize; ++i)
        result.mData[i] = scalar * vec.mData[i];
    return result;
}

// Unary minus 
Vector Vector::operator-() const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = -mData[i];
    return result;
}

double& Vector::operator[](int index) {
    if (index < 0 || index >= mSize) {
        cout << "Out of range 0-based\n";
        return mData[0]; 
    }
    return mData[index];
}


double Vector::operator[](int index) const {
    return mData[index];
}

double Vector::operator()(int index) const {
    if (index < 1 || index > mSize) {
        cout << "Out of range 1-based\n";
        return 0.0;
    }
    return mData[index - 1];
}

int Vector::size() const {
    return mSize;
}

void Vector::print() const {
    for (int i = 0; i < mSize; ++i) {
        cout << mData[i];
        if (i < mSize - 1) cout << ", ";
    }
    cout << endl;
}