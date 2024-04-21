#include "AbstractBinaryTree.h"
#include "trace.h"
#include <stdio.h>
#include <string.h>

size_t max(size_t a, size_t b);
size_t _BinaryTree_getHeight(const struct BinaryTree_Node *node);
size_t _BinaryTree_getNodeCount(const struct BinaryTree_Node *node);
struct BinaryTree_Node *_BinaryTree_clone(const struct BinaryTree_Node *source,
                                          struct BinaryTree_Node *parent);
void _BinaryTree_destroyTree(struct BinaryTree_Node *target);
struct BinaryTree_Node *_BinaryTree_fromPattern(const char *pattern,
                                                struct BinaryTree_Node *parent,
                                                struct BinaryTree *tree);

struct BinaryTree *BinaryTree_fromPattern(const char *pattern) {

    struct BinaryTree *tree =
        (struct BinaryTree *)_malloc(sizeof(struct BinaryTree));
    tree->nodeCount = 0;
    tree->root = _BinaryTree_fromPattern(pattern, NULL, tree);

    return tree;
}

struct BinaryTree_Node *_BinaryTree_fromPattern(const char *pattern,
                                                struct BinaryTree_Node *parent,
                                                struct BinaryTree *tree) {
    static size_t index = 0;

    char ch = pattern[index];
    index++;

    if (ch == '^') {
        return NULL;
    } else {
        struct BinaryTree_Node *result =
            (struct BinaryTree_Node *)_malloc(sizeof(struct BinaryTree_Node));
        struct BinaryTree_Data *data =
            (struct BinaryTree_Data *)_malloc(sizeof(struct BinaryTree_Data));

        data->p = ch;
        result->data = data;
        result->left = _BinaryTree_fromPattern(pattern, result, tree);
        result->right = _BinaryTree_fromPattern(pattern, result, tree);
        result->parent = parent;
        tree->nodeCount++;
        return result;
    }
}

struct BinaryTree_Node **BinaryTree_getPath(struct BinaryTree_Node *parent,
                                            struct BinaryTree_Node *child) {
    struct BinaryTree_Node *pathStack[TREE_MAX_HEIGHT] = {0};
    pathStack[0] = child;
    size_t pathStackTop = 0;
    pathStack[pathStackTop] = child;
    if (child->parent == NULL) {
        return NULL;
    }
    struct BinaryTree_Node *current = child->parent;

    while (current != parent) {
        pathStackTop++;
        pathStack[pathStackTop] = current;
        if (current->parent != NULL) {
            current = current->parent;
        } else {
            break;
        }
    }

    pathStackTop++;
    pathStack[pathStackTop] = parent;

    struct BinaryTree_Node **result = (struct BinaryTree_Node **)_malloc(
        (pathStackTop + 2) * sizeof(struct BinaryTree_Node *));

    for (size_t i = 0; i <= pathStackTop; i++) {
        result[pathStackTop - i] = pathStack[i];
    }
    result[pathStackTop + 1] = NULL;
    return result;
}
struct BinaryTree_Node *BinaryTree_getRoot(struct BinaryTree_Node *node) {
    while (node->parent != NULL) {
        node = node->parent;
    }
    return node;
}
struct BinaryTree_Node *BinaryTree_getParent(struct BinaryTree_Node *node) {
    return node->parent;
}
struct BinaryTree_Node *BinaryTree_getLeft(struct BinaryTree_Node *node) {
    return node->left;
}
struct BinaryTree_Node *BinaryTree_getRight(struct BinaryTree_Node *node) {
    return node->right;
}

size_t BinaryTree_getHeight(const struct BinaryTree *tree) {
    return _BinaryTree_getHeight(tree->root);
}

size_t _BinaryTree_getHeight(const struct BinaryTree_Node *node) {
    if (node == NULL) {
        return 0;
    } else {
        return max(_BinaryTree_getHeight(node->left),
                   _BinaryTree_getHeight(node->right)) +
               1;
    }
}

size_t BinaryTree_getNodeCount(const struct BinaryTree *tree) {
    return tree->nodeCount;
}

size_t _BinaryTree_getNodeCount(const struct BinaryTree_Node *node) {
    if (node == NULL) {
        return 0;
    } else {
        return _BinaryTree_getNodeCount(node->left) +
               _BinaryTree_getNodeCount(node->right) + 1;
    }
}
// 0 -> DLR; 1 -> LDR; 2-> LRD; 3 -> layer
void BinaryTree_forEach(struct BinaryTree *tree, int mode,
                        void (*f)(struct BinaryTree_Node *)) {
    if ((mode == 0) || (mode == 1)) {
        struct BinaryTree_Node *nodeStack[TREE_MAX_HEIGHT] = {0};
        size_t nodeStackTop = 0;

        struct BinaryTree_Node *p = tree->root;

        while (!((p == NULL) && (nodeStackTop == 0))) {
            while (p != NULL) {
                if (mode == 0) {
                    f(p);
                }
                nodeStack[nodeStackTop] = p;
                nodeStackTop++;

                p = p->left;
            }

            nodeStackTop--;
            p = nodeStack[nodeStackTop];

            if (mode == 1) {
                f(p);
            }

            p = p->right;
        }
    } else if (mode == 2) {
        struct BinaryTree_Node *nodeStack[TREE_MAX_HEIGHT] = {0};
        size_t nodeStackTop = 0;

        struct BinaryTree_Node *p = tree->root;
        struct BinaryTree_Node *prev = NULL;
        while (!((p == NULL) && (nodeStackTop == 0))) {
            while (p != NULL) {
                nodeStack[nodeStackTop] = p;
                nodeStackTop++;
                p = p->left;
            }

            p = nodeStack[nodeStackTop - 1];
            nodeStackTop--;

            // 访问节点的条件（已经过LR）
            if (p->right == NULL || p->right == prev) {
                f(p);
                prev = p;
                p = NULL;
            } else {
                nodeStack[nodeStackTop] = p;
                nodeStackTop++;
                p = p->right;
            }
        }
    } else {
        struct BinaryTree_Node **nodeQueue = (struct BinaryTree_Node **)_malloc(
            tree->nodeCount * sizeof(struct BinaryTree_Node *));
        size_t front = 0;
        size_t rear = tree->nodeCount - 1;
        size_t count = 0;

        rear = (rear + 1) % tree->nodeCount;

        nodeQueue[rear] = tree->root;
        count++;

        while (count > 0) {
            struct BinaryTree_Node *current = nodeQueue[front];
            front = (front + 1) % tree->nodeCount;
            count--;

            f(current);

            if (current->left != NULL) {
                rear = (rear + 1) % tree->nodeCount;

                nodeQueue[rear] = current->left;
                count++;
            }

            if (current->right != NULL) {
                rear = (rear + 1) % tree->nodeCount;

                nodeQueue[rear] = current->right;
                count++;
            }
        }
        _free(nodeQueue);
    }
}

struct BinaryTree *BinaryTree_clone(const struct BinaryTree *source) {
    struct BinaryTree *result =
        (struct BinaryTree *)_malloc(sizeof(struct BinaryTree));
    result->nodeCount = source->nodeCount;
    result->root = _BinaryTree_clone(source->root, NULL);
    return result;
}

struct BinaryTree_Node *_BinaryTree_clone(const struct BinaryTree_Node *source,
                                          struct BinaryTree_Node *parent) {
    struct BinaryTree_Node *current =
        (struct BinaryTree_Node *)_malloc(sizeof(struct BinaryTree_Node));
    struct BinaryTree_Data *data = BinaryTree_copyData(source->data);
    current->data = data;
    current->parent = parent;
    current->left = NULL;
    current->right = NULL;
    if (source->left != NULL) {
        current->left = _BinaryTree_clone(source->left, current);
    }
    if (source->right != NULL) {
        current->right = _BinaryTree_clone(source->right, current);
    }

    return current;
}

void BinaryTree_destroyTree(struct BinaryTree *target) {
    _BinaryTree_destroyTree(target->root);
    _free(target);
}

void _BinaryTree_destroyTree(struct BinaryTree_Node *target) {
    if (target == NULL) {
        return;
    }

    _BinaryTree_destroyTree(target->left);
    _BinaryTree_destroyTree(target->right);
    BinaryTree_destroyData(target->data);

    _free(target);
}

inline size_t max(size_t a, size_t b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}
