#include <stdio.h>

#include "AVLTree.h"
#include "trace.h"

void f(struct BinaryTree_Node *node);
void printPath(struct BinaryTree_Node **path);
void checkPath(struct BinaryTree_Node *node);
void checkRoot(struct BinaryTree_Node *node);
void doDelete(struct BinaryTree_Node *target);
void checkFind(struct BinaryTree_Node *node);

static struct BinaryTree_Node *testHead = NULL;

static struct BinaryTree *targetTree = NULL;

int main(void) {
    traceInit();

    int toSort[13] = {35, 64, 73, 38, 50, 100, 30, 40, 70, 60, 10, 58, 50};

    struct BinaryTree *tree = BinaryTree_createTree();

    for (size_t i = 0; i < 13; i++) {
        BinaryTree_insert(tree, &toSort[i], true);
    }

    printf("1:\n");
    BinaryTree_forEach(tree, 1, f);
    putchar('\n');

    BinaryTree_destroyTree(tree);

    tree = BinaryTree_createTree();

    BinaryTree_insertList(tree, toSort, 13, true);

    printf("2:\n");
    BinaryTree_forEach(tree, 1, f);
    putchar('\n');

    targetTree = tree;

    printf("3:\n");

    BinaryTree_forEach(tree, 3, checkFind);
    putchar('\n');

    int deleteOrder[13] = {35, 30, 64, 10, 38, 73, 50, 70, 100, 40, 60, 50, 58};
    printf("4:\n");
    for (size_t i = 0; i < 13; i++) {
        BinaryTree_delete(tree, &deleteOrder[i]);
        BinaryTree_forEach(tree, 1, f);
        putchar('\n');
    }

    BinaryTree_destroyTree(tree);

    traceFree();
    return 0;
}

BinaryTree_Data *BinaryTree_copyData(BinaryTree_Data *source) {
    BinaryTree_Data *result =
        (BinaryTree_Data *)_malloc(sizeof(BinaryTree_Data));
    *result = *source;
    return result;
}
void BinaryTree_destroyData(BinaryTree_Data *target) { _free(target); }

void f(struct BinaryTree_Node *node) { printf("%d ", *(node->data)); }

void printPath(struct BinaryTree_Node **path) {

    size_t i = 0;
    struct BinaryTree_Node *current = path[i];

    while (current != NULL) {
        printf("%d ", *(current->data));
        i++;
        current = path[i];
    }
    putchar('\n');
}

void checkPath(struct BinaryTree_Node *node) {
    struct BinaryTree_Node **path = BinaryTree_getPath(testHead, node);
    if (path != NULL) {
        printf("%d: ", *(node->data));
        printPath(path);
        _free(path);
    }
}
void checkRoot(struct BinaryTree_Node *node) {
    struct BinaryTree_Node *root = BinaryTree_getRoot(node);
    if (root == testHead) {
        printf("Success!Rock and stone!\n");
    } else {
        printf("Failed!\n");
    }
}

int BinaryTree_dataCmp(BinaryTree_Data *a, BinaryTree_Data *b) {
    if (*a < *b) {
        return -1;
    } else if (*a > *b) {
        return 1;
    } else {
        return 0;
    }
}

void BinaryTree_printData(BinaryTree_Data *target) { printf("%d", *target); }

void checkFind(struct BinaryTree_Node *node) {
    struct BinaryTree_Node *found = BinaryTree_find(targetTree, node->data);
    printf("%d ", *found->data);
}
