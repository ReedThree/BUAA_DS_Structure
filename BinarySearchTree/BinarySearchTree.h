#ifndef __BINARY_SEARCH_TREE_H
#define __BINARY_SEARCH_TREE_H

#include "AbstractBinaryTree.h"

bool BinaryTree_insert(struct BinaryTree *tree, BinaryTree_Data *data,
                       bool allowRepetiotion);
size_t BinaryTree_insertList(struct BinaryTree *tree, BinaryTree_Data *dataList,
                             size_t dataLen, bool allowRepetiotion);
bool BinaryTree_delete(struct BinaryTree *tree, BinaryTree_Data *data);
struct BinaryTree_Node *BinaryTree_find(const struct BinaryTree *tree,
                                        BinaryTree_Data *data);

// impl by user
int BinaryTree_dataCmp(BinaryTree_Data *a, BinaryTree_Data *b);
#endif
