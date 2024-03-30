#include "SymmetricMatrix.h"
#include "trace.h"
#include <stdio.h>
int main(void) {
    traceInit();
    struct SymmetricMatrix *sm = SymmetricMatrix_createMatrix(5U);
    SymmetricMatrix_readMatrix(sm);
    SymmetricMatrix_setPos(sm, 5, 5, 10);
    printf("%.2f\n", SymmetricMatrix_getByPos(sm, 5, 5));
    SymmetricMatrix_setPos(sm, 2, 3, 3);
    SymmetricMatrix_printMatrix(sm);
    SymmetricMatrix_destroyMatrix(sm);
    traceSummarize();
    traceFree();
    return 0;
}