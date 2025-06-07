#ifndef LINEARSYSTEM_HPP
#define LINEARSYSTEM_HPP

#include "Matrix.hpp"
#include "Vector.hpp"

class LinearSystem {
protected: // Use protected vì không cho phép gọi nhưng lớp con có thể truy cập
    int mSize;
    Matrix* mpA;
    Vector* mpb;

    LinearSystem(); 

private:
    LinearSystem(const LinearSystem&);  // Không cho phép copy constructor                                                                                                                                  

public:
    LinearSystem(const Matrix& A, const Vector& b);
    virtual ~LinearSystem();

    virtual Vector Solve(); // phương pháp Gaussian elimination với pivoting
};

class PosSymLinSystem : public LinearSystem {
public:
    PosSymLinSystem(const Matrix& A, const Vector& b);

    // Giải bằng Conjugate Gradient
    Vector Solve() override;
};

#endif 
