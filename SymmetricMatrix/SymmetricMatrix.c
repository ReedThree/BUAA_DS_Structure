#include "SymmetricMatrix.h"
#include "trace.h"
#include <stdio.h>
#include <string.h>

struct SymmetricMatrix *SymmetricMatrix_createMatrix(size_t n) {
    struct SymmetricMatrix *result =
        (struct SymmetricMatrix *)_malloc(sizeof(struct SymmetricMatrix));
    result->data = (double *)_malloc(((n + 1) * n) / 2 * sizeof(double));
    result->n = n;
    memset(result->data, 0, ((n + 1) * n) / 2 * sizeof(double));
    return result;
}

void SymmetricMatrix_destroyMatrix(struct SymmetricMatrix *target) {
    _free(target->data);
    _free(target);
}

inline double SymmetricMatrix_getPos(struct SymmetricMatrix *matrix, size_t x,
                                     size_t y) {
    size_t index = 0;
    if (x >= y) {
        index = x * (x - 1) / 2 + y - 1;
    } else {
        index = y * (y - 1) / 2 + x - 1;
    }

    return matrix->data[index];
}

inline void SymmetricMatrix_setPos(struct SymmetricMatrix *matrix, size_t x,
                                   size_t y, double value) {
    size_t index = 0;
    if (x >= y) {
        index = x * (x - 1) / 2 + y - 1;
    } else {
        index = y * (y - 1) / 2 + x - 1;
    }

    matrix->data[index] = value;
}

void SymmetricMatrix_readMatrix(struct SymmetricMatrix *target) {
    size_t index = 0;
    for (size_t i = 0; i < target->n; i++) {
        for (size_t j = 0; j < target->n; j++) {
            double temp = 0.0;
            scanf("%lf", &temp);
            if (j <= i) {
                target->data[index] = temp;
                index++;
            }
        }
    }
}

void SymmetricMatrix_printMatrix(struct SymmetricMatrix *target) {
    for (size_t x = 1; x <= target->n; x++) {
        for (size_t y = 1; y < target->n; y++) {
            printf("%.2f ", SymmetricMatrix_getPos(target, x, y));
        }
        printf("%.2f\n", SymmetricMatrix_getPos(target, x, target->n));
    }
}
