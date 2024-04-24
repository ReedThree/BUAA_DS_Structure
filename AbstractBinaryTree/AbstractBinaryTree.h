#ifndef __ABSTRACT_BINARY_TREE_H
#define __ABSTRACT_BINARY_TREE_H

#include <stdbool.h>
#include <stddef.h>

#define TREE_MAX_HEIGHT 64

struct BinaryTree_Data {
    int p;
};

struct BinaryTree {
    struct BinaryTree_Node *root;
    size_t nodeCount;
};

struct BinaryTree_Node {
    struct BinaryTree_Data *data;
    struct BinaryTree_Node *parent;
    struct BinaryTree_Node *left;
    struct BinaryTree_Node *right;
};

struct BinaryTree *BinaryTree_fromPattern(const char *pattern);
// 以NULL结尾
struct BinaryTree_Node **BinaryTree_getPath(struct BinaryTree_Node *parent,
                                            struct BinaryTree_Node *child);
struct BinaryTree_Node *BinaryTree_getRoot(struct BinaryTree_Node *node);
struct BinaryTree_Node *BinaryTree_getParent(struct BinaryTree_Node *node);
struct BinaryTree_Node *BinaryTree_getLeft(struct BinaryTree_Node *node);
struct BinaryTree_Node *BinaryTree_getRight(struct BinaryTree_Node *node);
size_t BinaryTree_getHeight(const struct BinaryTree *tree);
size_t BinaryTree_getNodeCount(const struct BinaryTree *tree);
// 0 -> DLR; 1 -> LDR; 2-> LRD; 3 -> layer
void BinaryTree_forEach(struct BinaryTree *tree, int mode,
                        void (*f)(struct BinaryTree_Node *));
struct BinaryTree *BinaryTree_clone(const struct BinaryTree *source);
void BinaryTree_destroyTree(struct BinaryTree *target);
// otherType: 0 -> DLR 1 -> LRD
struct BinaryTree *BinaryTree_recover(const char *inSeq, int otherType,
                                      const char *otherSeq);

// Abstract
bool BinaryTree_insert(struct BinaryTree *tree,
                       const struct BinaryTree_Data *data);
bool BinaryTree_delete(struct BinaryTree *tree,
                       const struct BinaryTree_Data *data);
struct BinaryTree *BinaryTree_find(const struct BinaryTree *tree,
                                   const struct BinaryTree_Data *data);

struct BinaryTree_Data *
BinaryTree_copyData(const struct BinaryTree_Data *source);
void BinaryTree_destroyData(struct BinaryTree_Data *target);
#endif
