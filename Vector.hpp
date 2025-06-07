#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

class Vector {
private:
    int mSize;
    double* mData; //Dynamic array to hold vector elements
    //This
public:
    Vector(); // Default constructot
    Vector(int size); // Initialization constructor
    Vector(const double* values, int size); // Constructor with values
    Vector(const Vector& other); //Copy constructor
    ~Vector(); // Destructor

    Vector& operator=(const Vector& other);

    // Overload operators
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;
    friend Vector operator*(double scalar, const Vector& vec);
    Vector operator-() const; // Unary minus operator

    double& operator[](int index); // 0-based index
    double operator[](int index) const;
    double operator()(int index) const; // 1-based index (read only) vd: double x = v(1);

    int size() const;
    void print() const;
};

#endif // VECTOR_HPP