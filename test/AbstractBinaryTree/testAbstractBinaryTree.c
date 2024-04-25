#include <stdio.h>

#include "AbstractBinaryTree.h"
#include "trace.h"

void f(struct BinaryTree_Node *node);
void printPath(struct BinaryTree_Node **path);
void checkPath(struct BinaryTree_Node *node);
void checkRoot(struct BinaryTree_Node *node);

static struct BinaryTree_Node *testHead = NULL;

int main(void) {
    traceInit();

    char input[] = "ABD^^EJ^^^CF^I^^G^^";

    struct BinaryTree *tree = BinaryTree_fromPattern(input);
    testHead = tree->root;
    printf("1:\n");
    printf("%zu\n", BinaryTree_getNodeCount(tree));
    printf("2:\n");
    printf("%zu\n", BinaryTree_getHeight(tree));
    printf("3:\n");
    BinaryTree_forEach(tree, 3, f);
    putchar('\n');
    printf("4:\n");
    BinaryTree_forEach(tree, 3, checkPath);
    printf("5:\n");
    BinaryTree_forEach(tree, 3, checkRoot);
    printf("6:\n");
    BinaryTree_forEach(tree, 0, f);
    putchar('\n');
    printf("7:\n");
    BinaryTree_forEach(tree, 1, f);
    putchar('\n');
    printf("8:\n");
    BinaryTree_forEach(tree, 2, f);
    putchar('\n');
    printf("9:\n");
    BinaryTree_forEach(tree, 3, f);
    putchar('\n');

    struct BinaryTree *cloned = BinaryTree_clone(tree);
    printf("10:\n");
    BinaryTree_forEach(tree, 3, f);
    putchar('\n');

    struct BinaryTree *test = BinaryTree_recover("HEIBADFCG", 0, "ABEHICDFG");

    printf("11:\n");
    BinaryTree_forEach(test, 3, f);
    putchar('\n');

    BinaryTree_destroyTree(test);
    test = BinaryTree_recover("HEIBADFCG", 1, "HIEBFDGCA");

    printf("12:\n");
    BinaryTree_forEach(test, 3, f);
    putchar('\n');

    BinaryTree_destroyTree(tree);
    BinaryTree_destroyTree(cloned);
    BinaryTree_destroyTree(test);
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

void f(struct BinaryTree_Node *node) { printf("%c", *(node->data)); }

void printPath(struct BinaryTree_Node **path) {

    size_t i = 0;
    struct BinaryTree_Node *current = path[i];

    while (current != NULL) {
        printf("%c ", *(current->data));
        i++;
        current = path[i];
    }
    putchar('\n');
}

void checkPath(struct BinaryTree_Node *node) {
    struct BinaryTree_Node **path = BinaryTree_getPath(testHead, node);
    if (path != NULL) {
        printf("%c: ", *(node->data));
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
