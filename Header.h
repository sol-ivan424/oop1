#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H

#include <iostream>

using namespace std;

struct Item {
    int iRow, iColumn;
    int value;
};

struct SparseMatrix {
    Item* pVector;
    int length;
};

struct RectangularMatrix {
    int** pMatrix;
    int row, column;
};

template <class T>
int number_length(T f_number) {
    std::ostringstream ss;
    ss << f_number;
    std::string s(ss.str());
    return s.length();
}

template <class V>
int get_number(V& a) {
    std::cin >> a;
    if (!std::cin.good()) {
        return -1;
    }
    return 1;
}

int get_data(RectangularMatrix*& pMatrix1);
void rectangular_to_sparse(RectangularMatrix& pMatrix1, SparseMatrix*& pMatrix2);
void solution(SparseMatrix& pMatrix2, SparseMatrix*& nMatrix);
void clean_memory(RectangularMatrix* pMatrix1, SparseMatrix* pMatrix2);
void show(SparseMatrix matrix);
void print_rectangular_matrix(RectangularMatrix& pMatrix1);
void print_sparse_matrix(SparseMatrix& pMatrix2);


#endif