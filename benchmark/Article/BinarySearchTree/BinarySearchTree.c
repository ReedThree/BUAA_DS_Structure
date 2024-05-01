#include "BinarySearchTree.h"
#include "AbstractBinaryTree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool BinaryTree_insert(struct BinaryTree *tree, BinaryTree_Data *data,
                       bool allowRepetiotion) {
    struct BinaryTree_Node *newNode =
        (struct BinaryTree_Node *)malloc(sizeof(struct BinaryTree_Node));

    newNode->data = BinaryTree_copyData(data);
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;

    if (tree->nodeCount == 0) {
        tree->root = newNode;
    } else {
        struct BinaryTree_Node *current = tree->root;
        while (1) {
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
                    if (current->right != NULL) {
                        current = current->right;
                    } else {
                        current->right = newNode;
                        newNode->parent = current;
                        break;
                    }
                } else {
                    return false;
                }
            }
        }
    }

    tree->nodeCount++;
    return true;
}

size_t BinaryTree_insertList(struct BinaryTree *tree, BinaryTree_Data *dataList,
                             size_t dataLen, bool allowRepetiotion) {
    struct BinaryTree_Node *newNode =
        (struct BinaryTree_Node *)malloc(sizeof(struct BinaryTree_Node));

    if (dataLen == 0) {
        return 0;
    }

    newNode->data = BinaryTree_copyData(&dataList[0]);
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;

    tree->nodeCount = 1;
    tree->root = newNode;

    for (size_t i = 1; i < dataLen; i++) {
        BinaryTree_Data *newData = BinaryTree_copyData(&dataList[i]);
        newNode =
            (struct BinaryTree_Node *)malloc(sizeof(struct BinaryTree_Node));
        newNode->data = newData;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;

        struct BinaryTree_Node *current = tree->root;
        while (1) {
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
    }

    return tree->nodeCount;
}

bool BinaryTree_delete(struct BinaryTree *tree, BinaryTree_Data *data) {
    struct BinaryTree_Node *current = tree->root;
    while (1) {
        int result = BinaryTree_dataCmp(data, current->data);
        if (result < 0) {
            if (current->left == NULL) {
                return false;
            } else {
                current = current->left;
            }
        } else if (result > 0) {
            if (current->right == NULL) {
                return false;
            } else {
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
                free(current);
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
                free(current);
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
                free(current);
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

                    free(rightMin);
                } else {
                    rightMin->right->parent = rightMin->parent;
                    if (rightMin->parent != current) {
                        rightMin->parent->left = rightMin->right;
                    } else {
                        current->right = NULL;
                    }

                    free(rightMin);
                }
            }

            break;
        }
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
