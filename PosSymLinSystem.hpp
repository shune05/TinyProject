#ifndef LINEARSYSTEM_HPP
#define LINEARSYSTEM_HPP

#include "Matrix.hpp"
#include "Vector.hpp"
#include <stdexcept>

class LinearSystem {
protected:
    int mSize;
    Matrix* mpA;
    Vector* mpb;

    LinearSystem();
private:
    LinearSystem(const LinearSystem&);
public:
    LinearSystem(const Matrix& A, const Vector& b);
    virtual ~LinearSystem();
    virtual Vector Solve();
};

class PosSymLinSystem : public LinearSystem {
public:
    PosSymLinSystem(const Matrix& A, const Vector& b);
    Vector Solve() override;
};

#endif