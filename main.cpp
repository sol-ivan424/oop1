#include <iostream>
#include "Header.h"

int main() {

    RectangularMatrix* pMatrix1;
    SparseMatrix* pMatrix2;

    try {
        get_data(pMatrix1);
    }
    catch (std::bad_alloc& e) {
        std::cout << std::endl << "Error: " << e.what() << std::endl;
    }

    rectangular_to_sparse(*pMatrix1, pMatrix2);

    print_rectangular_matrix(*pMatrix1);
    print_sparse_matrix(*pMatrix2);

    SparseMatrix *newm;

    solution(*pMatrix2, newm);

    print_sparse_matrix(*newm);

    show(*newm);

    clean_memory(pMatrix1, pMatrix2);

    return 0;
}