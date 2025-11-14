#include <iostream>
#include <fstream>
#include "Matrix.h"

int main() {
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;

    std::ifstream fin(filename);
    if (!fin) {
        std::cerr << "Cannot open file.\n";
        return 1;
    }

    Matrix A;
    A.readFromFile(fin);

    Matrix B;
    B.readFromFile(fin);

    std::cout << "\nMatrix A:\n";
    A.print();
    std::cout << "Matrix B:\n";
    B.print();

    std::cout << "A + B:\n";
    Matrix C = A + B;
    C.print();

    std::cout << "A * B:\n";
    Matrix D = A * B;
    D.print();

    std::cout << "Diagonal sums of A:\n";
    std::cout << "Main diagonal: " << A.mainDiagonalSum() << "\n";
    std::cout << "Secondary diagonal: " << A.secondaryDiagonalSum() << "\n\n";

    std::cout << "Swap rows 0 and 1 of A:\n";
    swapRows(A).print();

    std::cout << "Swap cols 0 and 1 of A:\n";
    swapCols(A).print();

    std::cout << "Update A at (0,0) to 100:\n";
    A.set(0,0,100);
    A.print();

    return 0;
}
