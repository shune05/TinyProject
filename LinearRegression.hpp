#ifndef LINEARREGRESSION_HPP
#define LINEARREGRESSION_HPP

#include "Matrix.hpp"
#include "Vector.hpp"
#include <string>
#include <vector>
using namespace std;

class LinearRegression {
private:
    Matrix X_train;
    Vector y_train;
    Matrix X_test;
    Vector y_test;
    Vector weights;

public:
    LinearRegression();
    bool loadData(const string& filename, double train_ratio = 0.8);
    void fit();
    Vector predict(const Matrix& X) const;
    double rmse(const Vector& y_true, const Vector& y_pred) const;
    void printWeights() const;
    double evaluate();
};

#endif