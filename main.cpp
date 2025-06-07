#include <iostream>
#include "Matrix.hpp"
#include "Vector.hpp"
#include "LinearSystem.hpp"
#include "PosSymLinSystem.hpp"
#include "LinearRegression.hpp"
using namespace std;

int main() {
    //Gaussian Elimination Test
    cout << "Testing LinearSystem" << endl;
    Matrix A1(3, 3);
    A1(1,1) = 5;  A1(1,2) = 2;  A1(1,3) = -3;
    A1(2,1) = -1; A1(2,2) = 4;  A1(2,3) = 1;
    A1(3,1) = 3;  A1(3,2) = -2; A1(3,3) = 6;

    Vector b1(3);
    b1[0] = 7;
    b1[1] = 2;
    b1[2] = 13;

    LinearSystem sys1(A1, b1);
    Vector x1 = sys1.Solve();
    cout << "Solution x (Gaussian): ";
    x1.print();
    cout << endl;

    //Conjugate Gradient Test
    cout << "Testing PosSymLinSystem" << endl;
    Matrix A2(3, 3);
    A2(1,1) = 6;  A2(1,2) = 2;  A2(1,3) = 1;
    A2(2,1) = 2;  A2(2,2) = 5;  A2(2,3) = 0;
    A2(3,1) = 1;  A2(3,2) = 0;  A2(3,3) = 3;

    Vector b2(3);
    b2[0] = 9;
    b2[1] = 8;
    b2[2] = 5;

    if (!A2.isSymmetric()) {
        cerr << "Error: Matrix is not symmetric" << endl;
    } else {
        PosSymLinSystem sys2(A2, b2);
        Vector x2 = sys2.Solve();
        cout << "Solution x (Conjugate Gradient): ";
        x2.print();
        cout << endl;
    }
    
    
    LinearRegression lr;
    if (!lr.loadData("machine.data")) {
        cout << "Cannot open data file!" << endl;
        return 1;
    }
    lr.fit();
    lr.printWeights();
    double error = lr.evaluate();
    cout << "Test RMSE: " << error << endl;
    return 0;
}