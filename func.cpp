#include "Header.h"

int fill_matrix(RectangularMatrix*& pMatrix1) {
    int row, column;

    std::cout << std::endl << "Enter 'Row' value: ";
    if (get_number(row) == -1) exit(0);
    std::cout << std::endl << "Enter 'Column' value: ";
    if (get_number(column) == -1) exit(0);

    pMatrix1 = new RectangularMatrix;
    pMatrix1->row = row;
    pMatrix1->column = column;

    pMatrix1->pMatrix = new int* [row];
    for (int i = 0; i < pMatrix1->row; ++i) {
        pMatrix1->pMatrix[i] = new int[column];
    }

    for (int i = 0; i < pMatrix1->row; ++i) {
        for (int j = 0; j < pMatrix1->column; ++j) {
            std::cout << std::endl << "Enter 'matrix[" << i << "][" << j << "]' value: ";
            if (get_number(pMatrix1->pMatrix[i][j]) == -1) exit(0);
        }
    }

    return 1;
}

int get_data(RectangularMatrix*& pMatrix1) {
    int result = fill_matrix(pMatrix1);
    if (!result) {
        std::cout << std::endl << "Error: wrong number format!" << std::endl;
        return 0;
    }
    std::cout << std::endl << "You have successfully made a rectangular matrix!" << std::endl;
    return 1;
}

unsigned int zero_counter(RectangularMatrix& pMatrix1) {
    int zero_counter = 0;

    for (int i = 0; i < pMatrix1.row; ++i) {
        for (int j = 0; j < pMatrix1.column; ++j) {
            if (pMatrix1.pMatrix[i][j] == 0) ++zero_counter;
        }
    }

    return zero_counter;
}

void rectangular_to_sparse(RectangularMatrix& pMatrix1, SparseMatrix*& pMatrix2) {
    int zero_c = zero_counter(pMatrix1);
    int index = 0;

    pMatrix2 = new SparseMatrix;
    pMatrix2->length = pMatrix1.row * pMatrix1.column - zero_c;
    pMatrix2->pVector = new Item[pMatrix2->length];

    for (int i = 0; i < pMatrix1.row; ++i) {
        for (int j = 0; j < pMatrix1.column; ++j) {
            if (pMatrix1.pMatrix[i][j] != 0) {
                pMatrix2->pVector[index].value = pMatrix1.pMatrix[i][j];
                pMatrix2->pVector[index].iColumn = j;
                pMatrix2->pVector[index].iRow = i;
                ++index;
            }
        }
    }
}

void solution(SparseMatrix& pMatrix2, SparseMatrix*& nMatrix) {

    nMatrix = new SparseMatrix;
    nMatrix->pVector = new Item[pMatrix2.length];
    nMatrix->length = 0;

    int p = 0;
    for (int i = 0; i < pMatrix2.length; i++) {
        if (pMatrix2.pVector[i].value > 0) {
            for (int j = i + 1; j < pMatrix2.length; j++) {
                if (pMatrix2.pVector[j].iRow != pMatrix2.pVector[i].iRow) {
                    i = j-1;
                    
                    break;
                }

                if (pMatrix2.pVector[j].value > 0) {
                    nMatrix->pVector[p].value = pMatrix2.pVector[j].value;
                    nMatrix->pVector[p].iRow = pMatrix2.pVector[j].iRow;
                    nMatrix->pVector[p].iColumn = pMatrix2.pVector[j].iColumn - 1;
                    ++nMatrix->length;
                    ++p;
                    
                    if (pMatrix2.pVector[j].iRow != pMatrix2.pVector[j + 1].iRow) {
                        i = j;
                        break;
                    }
                }
                else {
                    i = j;
                    break;
                }

            }
        }
    }
}

void clean_memory(RectangularMatrix* pMatrix1, SparseMatrix* pMatrix2) {
    // erase rectangular matrix
    for (int i = 0; i < pMatrix1->row; ++i) {
        delete[] pMatrix1->pMatrix[i];
    }
    delete pMatrix1->pMatrix;
    delete pMatrix1;

    // erase sparse matrix
    delete[] pMatrix2->pVector;
    delete pMatrix2;
}

void print_rectangular_matrix(RectangularMatrix& pMatrix1) {
    for (int i = 0; i < pMatrix1.row; i++) {
        for (int j = 0; j < pMatrix1.column; j++) {
            cout << pMatrix1.pMatrix[i][j] << " ";
        }
        cout << endl;
       
    }
}

void print_sparse_matrix(SparseMatrix& pMatrix2) {

    cout << endl << "Row:    ";
    for (int i = 0; i < pMatrix2.length; ++i) {
        cout << pMatrix2.pVector[i].iRow << " ";
    }
    cout << endl;

    cout << "Column: ";
    for (int i = 0; i < pMatrix2.length; ++i) {
        cout << pMatrix2.pVector[i].iColumn << " ";
    }
    cout << endl;

    cout << "Value:  ";
    for (int i = 0; i < pMatrix2.length; ++i) {
        cout << pMatrix2.pVector[i].value << " ";
    }
    cout << endl;
}

void show(SparseMatrix matrix) {
    cout << endl;
    cout << "New matrix: " << endl;
    for (int i = 0; i < matrix.length; i++) {
        cout << matrix.pVector[i].value << " ";
        if (matrix.pVector[i].iRow != matrix.pVector[i + 1].iRow) { cout << endl; }
    }
}