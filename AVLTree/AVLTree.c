#include "AVLTree.h"
#include "trace.h"
#include <stdio.h>
#include <string.h>

size_t max(size_t a, size_t b);
int64_t max_signed(int64_t a, int64_t b);
size_t _BinaryTree_getHeight(const struct BinaryTree_Node *node);
size_t _BinaryTree_getNodeCount(const struct BinaryTree_Node *node);
struct BinaryTree_Node *_BinaryTree_clone(const struct BinaryTree_Node *source,
                                          struct BinaryTree_Node *parent);
void _BinaryTree_destroyTree(struct BinaryTree_Node *target);
struct BinaryTree_Node *_BinaryTree_fromPattern(const char *pattern,
                                                struct BinaryTree_Node *parent,
                                                struct BinaryTree *tree);

struct BinaryTree_Node *_BinaryTree_recover_DLR(char *inSeq, char *preSeq,
                                                struct BinaryTree_Node *parent,
                                                struct BinaryTree *tree);
struct BinaryTree_Node *_BinaryTree_recover_LRD(char *inSeq, char *postSeq,
                                                size_t postLen,
                                                struct BinaryTree_Node *parent,
                                                struct BinaryTree *tree);

struct BinaryTree *BinaryTree_createTree(void) {
    struct BinaryTree *tree =
        (struct BinaryTree *)_malloc(sizeof(struct BinaryTree));
    tree->root = NULL;
    tree->nodeCount = 0;

    return tree;
}

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
        BinaryTree_Data *data =
            (BinaryTree_Data *)_malloc(sizeof(BinaryTree_Data));

        *data = ch;
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

size_t BinaryTree_getNodeDistanceFromRoot(const struct BinaryTree_Node *node) {
    size_t height = 0;
    const struct BinaryTree_Node *current = node;

    while (current != NULL) {
        height++;
        current = current->parent;
    }

    return height;
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
    BinaryTree_Data *data = BinaryTree_copyData(source->data);
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

struct BinaryTree *BinaryTree_recover(const char *inSeq, int otherType,
                                      const char *otherSeq) {
    char *_inSeq = (char *)_malloc((strlen(inSeq) + 1) * sizeof(char));
    char *_otherSeq = (char *)_malloc((strlen(otherSeq) + 1) * sizeof(char));

    strcpy(_inSeq, inSeq);
    strcpy(_otherSeq, otherSeq);

    struct BinaryTree *result =
        (struct BinaryTree *)_malloc(sizeof(struct BinaryTree));
    result->nodeCount = 0;
    if (otherType == 0) {
        result->root = _BinaryTree_recover_DLR(_inSeq, _otherSeq, NULL, result);
    } else {
        result->root = _BinaryTree_recover_LRD(
            _inSeq, _otherSeq, strlen(otherSeq) - 1, NULL, result);
    }

    _free(_inSeq);
    _free(_otherSeq);
    return result;
}

// DLR
struct BinaryTree_Node *_BinaryTree_recover_DLR(char *inSeq, char *preSeq,
                                                struct BinaryTree_Node *parent,
                                                struct BinaryTree *tree) {
    static size_t preIndex = 0;

    struct BinaryTree_Node *root =
        (struct BinaryTree_Node *)_malloc(sizeof(struct BinaryTree_Node));
    BinaryTree_Data *data = (BinaryTree_Data *)_malloc(sizeof(BinaryTree_Data));
    *data = preSeq[preIndex];

    preSeq[preIndex] = '\0';
    root->data = data;
    root->parent = parent;
    preIndex++;
    tree->nodeCount++;

    size_t inIndex = 0;
    while (inSeq[inIndex] != *data) {
        inIndex++;
    }

    inSeq[inIndex] = '\0';
    if ((inIndex != 0) && (inSeq[inIndex - 1] != '\0')) {
        root->left = _BinaryTree_recover_DLR(inSeq, preSeq, root, tree);
    } else {
        root->left = NULL;
    }

    if (inSeq[inIndex + 1] != '\0') {
        root->right = _BinaryTree_recover_DLR(inSeq, preSeq, root, tree);
    } else {
        root->right = NULL;
    }
    return root;
}

// LRD
struct BinaryTree_Node *_BinaryTree_recover_LRD(char *inSeq, char *postSeq,
                                                size_t postLen,
                                                struct BinaryTree_Node *parent,
                                                struct BinaryTree *tree) {
    static size_t postIndex = 0;
    if (parent == NULL) {
        postIndex = postLen;
    }
    struct BinaryTree_Node *root =
        (struct BinaryTree_Node *)_malloc(sizeof(struct BinaryTree_Node));
    BinaryTree_Data *data = (BinaryTree_Data *)_malloc(sizeof(BinaryTree_Data));
    *data = postSeq[postIndex];

    postSeq[postIndex] = '\0';
    root->data = data;
    root->parent = parent;
    postIndex--;
    tree->nodeCount++;

    size_t inIndex = 0;
    while (inSeq[inIndex] != *data) {
        inIndex++;
    }

    inSeq[inIndex] = '\0';

    if (inSeq[inIndex + 1] != '\0') {
        root->right =
            _BinaryTree_recover_LRD(inSeq, postSeq, postLen, root, tree);
    } else {
        root->right = NULL;
    }

    if ((inIndex != 0) && (inSeq[inIndex - 1] != '\0')) {
        root->left =
            _BinaryTree_recover_LRD(inSeq, postSeq, postLen, root, tree);
    } else {
        root->left = NULL;
    }

    return root;
}

void BinaryTree_printTree(const struct BinaryTree *tree) {
    if (tree->nodeCount == 0) {
        printf("^\n");
        return;
    }
    struct BinaryTree_Node **nodeQueue = (struct BinaryTree_Node **)_malloc(
        tree->nodeCount * sizeof(struct BinaryTree_Node *));
    size_t front = 0;
    size_t rear = tree->nodeCount - 1;
    size_t count = 0;

    rear = (rear + 1) % tree->nodeCount;

    nodeQueue[rear] = tree->root;
    count++;
    BinaryTree_printData(tree->root->data);
    size_t currentHeight = 1;
    while (count > 0) {
        struct BinaryTree_Node *current = nodeQueue[front];
        front = (front + 1) % tree->nodeCount;
        count--;

        size_t newHeight = BinaryTree_getNodeDistanceFromRoot(current);
        if (newHeight + 1 > currentHeight) {
            putchar('\n');
            currentHeight = newHeight + 1;
        }

        if (current->left != NULL) {
            BinaryTree_printData(current->left->data);
            putchar(' ');
            rear = (rear + 1) % tree->nodeCount;

            nodeQueue[rear] = current->left;
            count++;
        } else {
            printf("^ ");
        }

        if (current->right != NULL) {
            BinaryTree_printData(current->right->data);
            putchar(' ');
            rear = (rear + 1) % tree->nodeCount;

            nodeQueue[rear] = current->right;
            count++;
        } else {
            printf("^ ");
        }
    }
    _free(nodeQueue);
}

// AVL Tree
int64_t BinaryTree_getNodeHeight(const struct BinaryTree_Node *node) {
    if (node == NULL) {
        return -1;
    } else {
        return node->height;
    }
}

void BinaryTree_updateNodeHeight(struct BinaryTree_Node *node) {
    node->height = max_signed(BinaryTree_getNodeHeight(node->left),
                              BinaryTree_getNodeHeight(node->right)) +
                   1;
}

int64_t BinaryTree_getNodeBalanceFactor(const struct BinaryTree_Node *node) {
    if (node == NULL) {
        return 0;
    }

    return (BinaryTree_getNodeHeight(node->left) -
            BinaryTree_getNodeHeight(node->right));
}

struct BinaryTree_Node *BinaryTree_rightRotate(struct BinaryTree *tree,
                                               struct BinaryTree_Node *node) {
    struct BinaryTree_Node *child = node->left;
    if (child == NULL) {
        return NULL;
    }

    struct BinaryTree_Node *grandChild = child->right;

    if (node->parent == NULL) {
        tree->root = child;
    } else {
        if (node->parent->left == node) {
            node->parent->left = child;
        } else {
            node->parent->right = child;
        }
    }

    child->right = node;
    child->parent = node->parent;
    node->parent = child;

    node->left = grandChild;
    if (grandChild != NULL) {
        grandChild->parent = node;
    }

    BinaryTree_updateNodeHeight(node);
    BinaryTree_updateNodeHeight(child);

    return child;
}

struct BinaryTree_Node *BinaryTree_leftRotate(struct BinaryTree *tree,
                                              struct BinaryTree_Node *node) {
    struct BinaryTree_Node *child = node->right;
    if (child == NULL) {
        return NULL;
    }

    struct BinaryTree_Node *grandChild = child->left;

    if (node->parent == NULL) {
        tree->root = child;
    } else {
        if (node->parent->left == node) {
            node->parent->left = child;
        } else {
            node->parent->right = child;
        }
    }

    child->left = node;
    child->parent = node->parent;

    node->parent = child;

    node->right = grandChild;
    if (grandChild != NULL) {
        grandChild->parent = node;
    }

    BinaryTree_updateNodeHeight(node);
    BinaryTree_updateNodeHeight(child);

    return child;
}

struct BinaryTree_Node *BinaryTree_rotate(struct BinaryTree *tree,
                                          struct BinaryTree_Node *node) {
    int64_t nodeBalanceFactor = BinaryTree_getNodeBalanceFactor(node);

    // 左偏
    if (nodeBalanceFactor > 1) {
        if (BinaryTree_getNodeBalanceFactor(node->left) >= 0) {
            return BinaryTree_rightRotate(tree, node);
        } else {
            node->left = BinaryTree_leftRotate(tree, node->left);
            return BinaryTree_rightRotate(tree, node);
        }
    } else if (nodeBalanceFactor < -1) {
        if (BinaryTree_getNodeBalanceFactor(node->right) <= 0) {
            return BinaryTree_leftRotate(tree, node);
        } else {
            node->right = BinaryTree_rightRotate(tree, node->right);
            return BinaryTree_leftRotate(tree, node);
        }
    }

    return node;
}

bool BinaryTree_insert(struct BinaryTree *tree, BinaryTree_Data *data,
                       bool allowRepetiotion) {
    struct BinaryTree_Node *newNode =
        (struct BinaryTree_Node *)_malloc(sizeof(struct BinaryTree_Node));

    struct BinaryTree_Node *findPath[TREE_MAX_HEIGHT] = {0};
    size_t findPathLen = 0;

    newNode->data = BinaryTree_copyData(data);
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    newNode->height = 0;

    if (tree->nodeCount == 0) {
        tree->root = newNode;
    } else {
        struct BinaryTree_Node *current = tree->root;
        while (1) {
            findPath[findPathLen] = current;
            findPathLen++;
            int result = BinaryTree_dataCmp(newNode->data, current->data);
            if (result < 0) {
                if (current->left != NULL) {
                    current = current->left;
                } else {
                    current->left = newNode;
                    newNode->parent = current;
                    break;
                }
            } else if (result > 0) {
                if (current->right != NULL) {
                    current = current->right;
                } else {
                    current->right = newNode;
                    newNode->parent = current;
                    break;
                }
            } else {
                if (allowRepetiotion) {
                    if (current->left != NULL) {
                        current = current->left;
                    } else {
                        current->left = newNode;
                        newNode->parent = current;
                        break;
                    }
                } else {
                    return false;
                }
            }
        }
    }

    for (size_t i = 0; i < findPathLen; i++) {
        BinaryTree_updateNodeHeight(findPath[findPathLen - i - 1]);
    }

    for (size_t i = 0; i < findPathLen; i++) {
        BinaryTree_rotate(tree, findPath[findPathLen - i - 1]);
    }

    tree->nodeCount++;
    return true;
}

size_t BinaryTree_insertList(struct BinaryTree *tree, BinaryTree_Data *dataList,
                             size_t dataLen, bool allowRepetiotion) {
    struct BinaryTree_Node *newNode =
        (struct BinaryTree_Node *)_malloc(sizeof(struct BinaryTree_Node));

    if (dataLen == 0) {
        return 0;
    }

    newNode->data = BinaryTree_copyData(&dataList[0]);
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    newNode->height = 0;

    tree->nodeCount = 1;
    tree->root = newNode;

    for (size_t i = 1; i < dataLen; i++) {
        struct BinaryTree_Node *findPath[TREE_MAX_HEIGHT] = {0};
        size_t findPathLen = 0;

        BinaryTree_Data *newData = BinaryTree_copyData(&dataList[i]);
        newNode =
            (struct BinaryTree_Node *)_malloc(sizeof(struct BinaryTree_Node));
        newNode->data = newData;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;
        newNode->height = 0;

        struct BinaryTree_Node *current = tree->root;
        while (1) {
            findPath[findPathLen] = current;
            findPathLen++;
            int result = BinaryTree_dataCmp(newData, current->data);
            if (result < 0) {
                if (current->left != NULL) {
                    current = current->left;
                } else {
                    current->left = newNode;
                    newNode->parent = current;
                    tree->nodeCount++;
                    break;
                }
            } else if (result > 0) {
                if (current->right != NULL) {
                    current = current->right;
                } else {
                    current->right = newNode;
                    newNode->parent = current;
                    tree->nodeCount++;
                    break;
                }
            } else {
                if (allowRepetiotion) {
                    if (current->left != NULL) {
                        current = current->left;
                    } else {
                        current->left = newNode;
                        newNode->parent = current;
                        tree->nodeCount++;
                        break;
                    }
                } else {
                    break;
                }
            }
        }

        for (size_t j = 0; j < findPathLen; j++) {
            BinaryTree_updateNodeHeight(findPath[findPathLen - j - 1]);
        }

        for (size_t j = 0; j < findPathLen; j++) {
            BinaryTree_rotate(tree, findPath[findPathLen - j - 1]);
        }
    }

    return tree->nodeCount;
}

bool BinaryTree_delete(struct BinaryTree *tree, BinaryTree_Data *data) {
    struct BinaryTree_Node *current = tree->root;
    struct BinaryTree_Node *findPath[TREE_MAX_HEIGHT] = {0};
    size_t findPathLen = 0;
    while (1) {

        int result = BinaryTree_dataCmp(data, current->data);
        if (result < 0) {
            if (current->left == NULL) {
                return false;
            } else {
                findPath[findPathLen] = current;
                findPathLen++;
                current = current->left;
            }
        } else if (result > 0) {
            if (current->right == NULL) {
                return false;
            } else {
                findPath[findPathLen] = current;
                findPathLen++;
                current = current->right;
            }
        } else {
            struct BinaryTree_Node *parent = current->parent;

            if ((current->left == NULL) && (current->right == NULL)) {
                if (parent == NULL) {
                    tree->root = NULL;
                } else {
                    if (parent->left == current) {
                        parent->left = NULL;
                    } else {
                        parent->right = NULL;
                    }
                }
                BinaryTree_destroyData(current->data);
                _free(current);
            } else if (current->left == NULL) {
                current->right->parent = parent;
                if (parent == NULL) {
                    tree->root = current->right;
                } else {
                    if (parent->left == current) {
                        parent->left = current->right;
                    } else {
                        parent->right = current->right;
                    }
                }
                BinaryTree_destroyData(current->data);
                _free(current);
            } else if (current->right == NULL) {
                current->left->parent = parent;
                if (parent == NULL) {
                    tree->root = current->left;
                } else {
                    if (parent->left == current) {
                        parent->left = current->left;
                    } else {
                        parent->right = current->left;
                    }
                }
                BinaryTree_destroyData(current->data);
                _free(current);
            } else {
                struct BinaryTree_Node *rightMin = current->right;

                while (rightMin->left != NULL) {
                    rightMin = rightMin->left;
                }
                BinaryTree_destroyData(current->data);
                current->data = rightMin->data;

                if (rightMin->right == NULL) {
                    if (rightMin->parent != current) {
                        rightMin->parent->left = NULL;
                    } else {
                        current->right = NULL;
                    }

                    _free(rightMin);
                } else {
                    rightMin->right->parent = rightMin->parent;
                    if (rightMin->parent != current) {
                        rightMin->parent->left = rightMin->right;
                    } else {
                        current->right = NULL;
                    }

                    _free(rightMin);
                }
            }

            break;
        }
    }

    for (size_t i = 0; i < findPathLen; i++) {
        BinaryTree_updateNodeHeight(findPath[findPathLen - i - 1]);
    }

    for (size_t i = 0; i < findPathLen; i++) {
        BinaryTree_rotate(tree, findPath[findPathLen - i - 1]);
    }

    tree->nodeCount--;
    return true;
}
struct BinaryTree_Node *BinaryTree_find(const struct BinaryTree *tree,
                                        BinaryTree_Data *data) {
    if (tree->nodeCount == 0) {
        return NULL;
    }
    struct BinaryTree_Node *current = tree->root;
    while (1) {
        int result = BinaryTree_dataCmp(data, current->data);

        if (result < 0) {
            if (current->left != NULL) {
                current = current->left;
            } else {
                return NULL;
            }
        } else if (result > 0) {
            if (current->right != NULL) {
                current = current->right;
            } else {
                return NULL;
            }
        } else {
            return current;
        }
    }
}

void BinaryTree_dotGraph(const struct BinaryTree *tree, char *output) {
    const char dotGraphBegin[] = "graph G {\nnode [shape = circle;];\n";
    const char dotGraphEnd[] = "}";

    char formatBuffer[DOT_GRAPH_FORMAT_BUFFER_LEN] = {0};

    strcpy(output, dotGraphBegin);

    // node label
    struct BinaryTree_Node **nodeQueue = (struct BinaryTree_Node **)_malloc(
        tree->nodeCount * sizeof(struct BinaryTree_Node *));
    size_t front = 0;
    size_t rear = tree->nodeCount - 1;
    size_t count = 0;

    size_t nodeId = 0;

    rear = (rear + 1) % tree->nodeCount;

    nodeQueue[rear] = tree->root;
    count++;

    // edge

    struct BinaryTree_Node **nodeList = (struct BinaryTree_Node **)_malloc(
        tree->nodeCount * sizeof(struct BinaryTree_Node *));

    while (count > 0) {
        struct BinaryTree_Node *current = nodeQueue[front];
        front = (front + 1) % tree->nodeCount;
        count--;

        nodeList[nodeId] = current;

        sprintf(formatBuffer, "%zu [label = \"%d\";];\n", nodeId,
                *(current->data));

        strcat(output, formatBuffer);
        nodeId++;

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

    front = 0;
    rear = tree->nodeCount - 1;
    count = 0;

    nodeId = 0;

    rear = (rear + 1) % tree->nodeCount;

    nodeQueue[rear] = tree->root;
    count++;

    while (count > 0) {
        struct BinaryTree_Node *current = nodeQueue[front];
        front = (front + 1) % tree->nodeCount;
        count--;

        if (current->parent != NULL) {
            size_t parentId = 0;
            for (size_t i = 0; i < nodeId; i++) {
                if (nodeList[i] == current->parent) {
                    parentId = i;
                    break;
                }
            }
            sprintf(formatBuffer, "%zu -- %zu;\n", parentId, nodeId);
            strcat(output, formatBuffer);
        }

        nodeId++;

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

    strcat(output, dotGraphEnd);
    _free(nodeQueue);
    _free(nodeList);
}

inline size_t max(size_t a, size_t b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

inline int64_t max_signed(int64_t a, int64_t b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}
