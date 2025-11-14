#include "Matrix.h"
#include <iomanip>
#include <stdexcept>

Matrix::Matrix() : n(0), data(nullptr) {}

Matrix::Matrix(int size) : n(size) {
    allocate();
}

void Matrix::allocate() {
    data = new int*[n];
    for (int i = 0; i < n; i++)
        data[i] = new int[n]{0};
}

void Matrix::deallocate() {
    if (!data) return;
    for (int i = 0; i < n; i++)
        delete[] data[i];
    delete[] data;
    data = nullptr;
}

Matrix::~Matrix() {
    deallocate();
}

Matrix::Matrix(const Matrix& other) : n(other.n) {
    allocate();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            data[i][j] = other.data[i][j];
}

Matrix::Matrix(Matrix&& other) noexcept
    : n(other.n), data(other.data) {
    other.n = 0;
    other.data = nullptr;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) return *this;

    deallocate();
    n = other.n;
    allocate();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            data[i][j] = other.data[i][j];

    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this == &other) return *this;

    deallocate();
    n = other.n;
    data = other.data;

    other.n = 0;
    other.data = nullptr;
    return *this;
}

void Matrix::readFromFile(std::istream& in) {
    in >> n;
    allocate();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            in >> data[i][j];
}

void Matrix::print() const {
    if (n == 0) return;

    int maxWidth = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            maxWidth = std::max(maxWidth, (int)std::to_string(data[i][j]).size());

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            std::cout << std::setw(maxWidth + 1) << data[i][j];
        std::cout << "\n";
    }
    std::cout << "\n";
}

Matrix Matrix::operator+(const Matrix& rhs) const {
    if (n != rhs.n)
        throw std::runtime_error("Matrix sizes do not match for addition.");

    Matrix result(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result.data[i][j] = data[i][j] + rhs.data[i][j];
    return result;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
    if (n != rhs.n)
        throw std::runtime_error("Matrix sizes do not match for multiplication.");

    Matrix result(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                result.data[i][j] += data[i][k] * rhs.data[k][j];

    return result;
}

int Matrix::mainDiagonalSum() const {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += data[i][i];
    return sum;
}

int Matrix::secondaryDiagonalSum() const {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += data[i][n - 1 - i];
    return sum;
}


Matrix swapRows(Matrix m, int r1, int r2) {
    if (r1 < 0 || r2 < 0 || r1 >= m.size() || r2 >= m.size())
        return m;

    for (int j = 0; j < m.size(); j++) {
        int temp = m.get(r1, j);
        m.set(r1, j, m.get(r2, j));
        m.set(r2, j, temp);
    }
    return m;
}

Matrix swapCols(Matrix m, int c1, int c2) {
    if (c1 < 0 || c2 < 0 || c1 >= m.size() || c2 >= m.size())
        return m;

    for (int i = 0; i < m.size(); i++) {
        int temp = m.get(i, c1);
        m.set(i, c1, m.get(i, c2));
        m.set(i, c2, temp);
    }
    return m;
}
