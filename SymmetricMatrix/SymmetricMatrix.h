#ifndef __SYMMETRIC_MATRIX_H
#define __SYMMETRIC_MATRIX_H

#include <stddef.h>

struct SymmetricMatrix {
    double *data;
    size_t n;
};

struct SymmetricMatrix *SymmetricMatrix_createMatrix(size_t n);
void SymmetricMatrix_destroyMatrix(struct SymmetricMatrix *target);
// From 1,1 to n, n
double SymmetricMatrix_getPos(struct SymmetricMatrix *matrix, size_t x, size_t y);
void SymmetricMatrix_setPos(struct SymmetricMatrix *matrix, size_t x, size_t y, double value);
void SymmetricMatrix_readMatrix(struct SymmetricMatrix *target);
void SymmetricMatrix_printMatrix(struct SymmetricMatrix *target);

#endif
