#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <iostream>

class Matrix {
private:
    int n;
    int** data;

    void allocate();
    void deallocate();

public:
    Matrix();
    Matrix(int size);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;
    ~Matrix();

    int size() const { return n; }

    void readFromFile(std::istream& in);
    void print() const;

    int get(int r, int c) const { return data[r][c]; }
    void set(int r, int c, int val) { data[r][c] = val; }

    // Diagonal sums
    int mainDiagonalSum() const;
    int secondaryDiagonalSum() const;

    // Operators
    Matrix operator+(const Matrix& rhs) const;
    Matrix operator*(const Matrix& rhs) const;
};

// Standalone utilities (copy by value required)
Matrix swapRows(Matrix m, int r1 = 0, int r2 = 1);
Matrix swapCols(Matrix m, int c1 = 0, int c2 = 1);

#endif
