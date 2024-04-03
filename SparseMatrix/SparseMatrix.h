#ifndef __SPARSE_MATRIX_H
#define __SPARSE_MATRIX_H

#include <stddef.h>
#include <stdbool.h>
typedef double DataType;
#define SCAN_DATA "lf"
#define PRINT_DATA "f"

bool SparseMatrix_isZero(DataType data);

struct SparseMatrix_Node {
    size_t m;                                       // row of current data, only valid in Data Node
    size_t n;                                       // col of current data, only valid in Data Node
    DataType value;                                 // only valid in Data Node
    struct SparseMatrix_Node *right;                // only valid in Data Node
    struct SparseMatrix_Node *down;                 // valid in Data Node, Head Node
};

struct SparseMatrix {
    size_t rowNum;
    size_t colNum;
    struct SparseMatrix_Node **nodeList;                   // List of Head Node
};

struct SparseMatrix *SparseMatrix_createMatrix(size_t rowNum, size_t colNum);
void SparseMatrix_destroyMatrix(struct SparseMatrix *target);
void SparseMatrix_readMatrix(struct SparseMatrix *target);
void SparseMatrix_printMatrix(struct SparseMatrix *target);
DataType SparseMatrix_getPos(struct SparseMatrix *target, size_t row, size_t col);
void SparseMatrix_setPos(struct SparseMatrix *target, size_t row, size_t col, DataType value);
#endif
