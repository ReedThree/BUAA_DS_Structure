#ifndef __AVL_TREE_H
#define __AVL_TREE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define TREE_MAX_HEIGHT 1024

typedef struct {
    char *word;
    size_t count;
} BinaryTree_Data;

struct BinaryTree {
    struct BinaryTree_Node *root;
    size_t nodeCount;
};

struct BinaryTree_Node {
    BinaryTree_Data *data;
    long height;
    struct BinaryTree_Node *parent;
    struct BinaryTree_Node *left;
    struct BinaryTree_Node *right;
};

struct BinaryTree *BinaryTree_createTree(void);

struct BinaryTree *BinaryTree_fromPattern(const char *pattern);
// 以NULL结尾
struct BinaryTree_Node **BinaryTree_getPath(struct BinaryTree_Node *parent,
                                            struct BinaryTree_Node *child);
struct BinaryTree_Node *BinaryTree_getRoot(struct BinaryTree_Node *node);
struct BinaryTree_Node *BinaryTree_getParent(struct BinaryTree_Node *node);
struct BinaryTree_Node *BinaryTree_getLeft(struct BinaryTree_Node *node);
struct BinaryTree_Node *BinaryTree_getRight(struct BinaryTree_Node *node);
size_t BinaryTree_getHeight(const struct BinaryTree *tree);
size_t BinaryTree_getNodeDistanceFromRoot(const struct BinaryTree_Node *node);
size_t BinaryTree_getNodeCount(const struct BinaryTree *tree);
// 0 -> DLR; 1 -> LDR; 2-> LRD; 3 -> layer
void BinaryTree_forEach(struct BinaryTree *tree, int mode,
                        void (*f)(struct BinaryTree_Node *));
struct BinaryTree *BinaryTree_clone(const struct BinaryTree *source);
void BinaryTree_destroyTree(struct BinaryTree *target);
// otherType: 0 -> DLR 1 -> LRD
struct BinaryTree *BinaryTree_recover(const char *inSeq, int otherType,
                                      const char *otherSeq);

void BinaryTree_printTree(const struct BinaryTree *tree);

// AVL
int64_t BinaryTree_getNodeHeight(const struct BinaryTree_Node *node);
void BinaryTree_updateNodeHeight(struct BinaryTree_Node *node);
int64_t BinaryTree_getNodeBalanceFactor(const struct BinaryTree_Node *node);
struct BinaryTree_Node *BinaryTree_rightRotate(struct BinaryTree *tree,
                                               struct BinaryTree_Node *node);
struct BinaryTree_Node *BinaryTree_leftRotate(struct BinaryTree *tree,
                                              struct BinaryTree_Node *node);

struct BinaryTree_Node *BinaryTree_rotate(struct BinaryTree *tree,
                                          struct BinaryTree_Node *node);

bool BinaryTree_insert(struct BinaryTree *tree, BinaryTree_Data *data,
                       bool allowRepetiotion);
size_t BinaryTree_insertList(struct BinaryTree *tree, BinaryTree_Data *dataList,
                             size_t dataLen, bool allowRepetiotion);
bool BinaryTree_delete(struct BinaryTree *tree, BinaryTree_Data *data);
struct BinaryTree_Node *BinaryTree_find(const struct BinaryTree *tree,
                                        BinaryTree_Data *data);

// impl by user
int BinaryTree_dataCmp(BinaryTree_Data *a, BinaryTree_Data *b);

BinaryTree_Data *BinaryTree_copyData(BinaryTree_Data *source);
void BinaryTree_destroyData(BinaryTree_Data *target);

void BinaryTree_printData(BinaryTree_Data *target);
#endif
