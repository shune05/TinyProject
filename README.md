# Linear System Solvers & CPU Performance Prediction

## Overview
This project implements custom C++ classes for solving systems of linear equations and applies them to predict CPU performance using linear regression. It includes support for both square and non-square systems, as well as methods suitable for symmetric positive-definite matrices.
## Structure
### Part A: Linear Solvers

- **Vector.cpp**  
  This class supports one-dimensional arrays with dynamic memory allocation. It overloads the assignment, unary and binary operators, square bracket operator and round bracket operator.

- **Matrix.cpp**  
  This class represents two-dimensional matrices and implements various linear algebra operations, such as addition, multiplication, determinant computation, and calculation of inverse and Moore-Penrose pseudo-inverse.

- **LinearSystem.cpp**  
  Designed to solve general systems of linear equations using Gaussian elimination with partial pivoting to ensure numerical stability.

- **PosSymLinSystem.cpp**  
  A specialized subclass optimized for symmetric positive-definite systems, using the Conjugate Gradient method to achieve efficient iterative solutions.

---

### Part B: Regression and Real-world Application

- **main.cpp**  
  - Model trainning using: Moore-Penrose Pseudo-inverse and Tikhonov Regularization

---

## 📊 Results
RMSE on test set: 101.899
