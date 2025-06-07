#include "LinearRegression.hpp"
#include "LinearSystem.hpp"
#include <fstream>
#include <sstream> //deal with string
#include <algorithm> //using shuffle
#include <random>
#include <iostream>
using namespace std;

LinearRegression::LinearRegression() {} //private 

//Reading from file
bool LinearRegression::loadData(const string& filename, double train_ratio) {
    vector<vector<double>> features;
    vector<double> targets;
    ifstream fin(filename);
    if (!fin) return false;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string field;
        vector<string> fields;
        while (getline(ss, field, ',')) { // tách bằng dấu phẩy
            fields.push_back(field);
        }
        if (fields.size() < 9) continue; // Bỏ qua dòng thiếu dữ liệu
        vector<double> row;
        // Lấy 2-7
        for (int i = 2; i <= 7; ++i) row.push_back(stod(fields[i]));
        features.push_back(row);
        targets.push_back(stod(fields[8])); // PRP ở vị trí 8
    }
    
    // Shuffle and split
    vector<int> idx(features.size()); //with index for shuffling
    for (int i = 0; i < idx.size(); ++i) idx[i] = i;
    random_device rand; mt19937 g(rand());
    shuffle(idx.begin(), idx.end(), g);
    int n_train = int(train_ratio * features.size()); 
    X_train = Matrix(n_train, 6); //Matrix n_train x 6
    y_train = Vector(n_train);
    X_test = Matrix(features.size() - n_train, 6);
    y_test = Vector(features.size() - n_train);
    for (int i = 0; i < n_train; ++i) {
        for (int j = 0; j < 6; ++j)
            X_train(i+1, j+1) = features[idx[i]][j];
        y_train[i] = targets[idx[i]];
    }
    for (int i = n_train; i < features.size(); ++i) {
        for (int j = 0; j < 6; ++j)
            X_test(i-n_train+1, j+1) = features[idx[i]][j];
        y_test[i-n_train] = targets[idx[i]];
    }
    return true;
}

void LinearRegression::fit() {
    // Solve (X^T X) w = X^T y
    Matrix Xt = Matrix(X_train.numCols(), X_train.numRows());
    for (int i = 0; i < X_train.numRows(); ++i)
        for (int j = 0; j < X_train.numCols(); ++j)
            Xt(j+1, i+1) = X_train(i+1, j+1);
    Matrix XtX = Xt * X_train;
    Vector Xty = Xt * y_train;
    LinearSystem sys(XtX, Xty);
    weights = sys.Solve();
}

// Predict using the learned weights
Vector LinearRegression::predict(const Matrix& X) const {
    Vector y_pred(X.numRows());
    for (int i = 0; i < X.numRows(); ++i) {
        double val = 0;
        for (int j = 0; j < X.numCols(); ++j)
            val += weights[j] * X(i+1, j+1);
        y_pred[i] = val;
    }
    return y_pred;
}

double LinearRegression::rmse(const Vector& y_true, const Vector& y_pred) const {
    double sum = 0;
    for (int i = 0; i < y_true.size(); ++i)
        sum += (y_true[i] - y_pred[i]) * (y_true[i] - y_pred[i]);
    return sqrt(sum / y_true.size());
}

void LinearRegression::printWeights() const {
    cout << "Model weights: ";
    for (int i = 0; i < weights.size(); ++i)
        cout << weights[i] << " ";
    cout << endl;
}

//Tính RMSE trên tập test
double LinearRegression::evaluate() {
    Vector y_pred = predict(X_test);
    return rmse(y_test, y_pred);
}