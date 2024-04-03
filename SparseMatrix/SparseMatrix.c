#include "SparseMatrix.h"
#include "trace.h"
#include <stdio.h>

size_t max(size_t a, size_t b);

struct SparseMatrix *SparseMatrix_createMatrix(size_t rowNum, size_t colNum) {
    struct SparseMatrix *result =
        (struct SparseMatrix *)_malloc(sizeof(struct SparseMatrix));
    result->rowNum = rowNum;
    result->colNum = colNum;
    struct SparseMatrix_Node **nodeList = (struct SparseMatrix_Node **)_malloc(
        max(rowNum, colNum) * sizeof(struct SparseMatrix_Node *));
    for (size_t i = 0; i < max(rowNum, colNum); i++) {
        nodeList[i] = (struct SparseMatrix_Node *)_malloc(
            sizeof(struct SparseMatrix_Node));
        nodeList[i]->m = 0;
        nodeList[i]->n = 0;
        // nodeList[i]->value -> undefined
        nodeList[i]->right = nodeList[i]; // currently no data
        nodeList[i]->down = nodeList[i];  // currently no data
    }
    result->nodeList = nodeList;
    return result;
}

void SparseMatrix_destroyMatrix(struct SparseMatrix *target) {
    for (size_t i = 0; i < max(target->rowNum, target->colNum); i++) {
        struct SparseMatrix_Node *head = target->nodeList[i];
        struct SparseMatrix_Node *current = head;
        while (current != head) {
            struct SparseMatrix_Node *temp = current->down;
            _free(current);
            current = temp;
        }
        _free(head);
    }
    _free(target);
}
void SparseMatrix_readMatrix(struct SparseMatrix *target) {
    for (size_t i = 0; i < target->rowNum; i++) {
        struct SparseMatrix_Node *thisRow = target->nodeList[i];
        for (size_t j = 0; j < target->colNum; j++) {
            DataType temp;
            scanf("%" SCAN_DATA, &temp);
            bool first = true;
            struct SparseMatrix_Node *prevRowNode = NULL;
            if (!SparseMatrix_isZero(temp)) {
                struct SparseMatrix_Node *thisData =
                    (struct SparseMatrix_Node *)_malloc(
                        sizeof(struct SparseMatrix_Node));
                thisData->m = i + 1;
                thisData->n = j + 1;
                thisData->value = temp;
            }
        }
    }
}

inline size_t max(size_t a, size_t b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}