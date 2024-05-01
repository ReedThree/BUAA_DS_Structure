#include "AVLTree.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORDLEN 85

int getWordLower(char **ptrToWord);
void countWords(struct BinaryTree *tree);
void printResult(struct BinaryTree *tree);

void _BinaryTree_printData(struct BinaryTree_Node *target);

int main(void) {
    freopen("../article_random.txt", "r", stdin);
    struct BinaryTree *tree = BinaryTree_createTree();
    countWords(tree);
    printResult(tree);
    BinaryTree_destroyTree(tree);
    return 0;
}

int getWordLower(char **ptrToWord) {
    char buffer[MAXWORDLEN] = {0};
    int len = 0;
    int ch = 0;
    while (1) {
        ch = getchar();
        if (isalpha(ch)) {
            buffer[len] = (char)tolower(ch);
            len++;
            continue;
        }
        if (ch == EOF) {
            break;
        }
        if (len > 0) {
            break;
        } else {
            continue;
        }
    }
    if (len == 0) {
        return -1;
    }
    *ptrToWord = (char *)malloc((unsigned)(len + 1) * sizeof(char));
    strcpy(*ptrToWord, buffer);
    if (ch != EOF) {
        return 1;
    }
    return 0;
}

void countWords(struct BinaryTree *tree) {
    while (1) {
        char *word = NULL;
        int r = getWordLower(&word);
        if (word != NULL) {
            BinaryTree_Data thisWord = {word, 1};
            struct BinaryTree_Node *searchResult =
                BinaryTree_find(tree, &thisWord);
            if (searchResult != NULL) {
                searchResult->data->count++;
                free(word);
            } else {
                BinaryTree_insert(tree, &thisWord, false);
                free(word);
            }
        } else {
            break;
        }

        if (r == 0) {
            break;
        }
    }
}

void printResult(struct BinaryTree *tree) {
    printf("%s ", tree->root->data->word);
    if (tree->root->right != NULL) {

        if (tree->root->right->right != NULL) {
            printf("%s ", tree->root->right->data->word);
            printf("%s\n", tree->root->right->right->data->word);
        } else {
            printf("%s\n", tree->root->right->data->word);
        }
    }
    BinaryTree_forEach(tree, 1, _BinaryTree_printData);
}

BinaryTree_Data *BinaryTree_copyData(BinaryTree_Data *source) {
    BinaryTree_Data *result =
        (BinaryTree_Data *)malloc(sizeof(BinaryTree_Data));
    result->word = (char *)malloc((strlen(source->word) + 1) * sizeof(char));
    strcpy(result->word, source->word);
    result->count = source->count;
    return result;
}
void BinaryTree_destroyData(BinaryTree_Data *target) {
    free(target->word);
    free(target);
}

void _BinaryTree_printData(struct BinaryTree_Node *target) {
    BinaryTree_printData(target->data);
}

void BinaryTree_printData(BinaryTree_Data *target) {
    printf("%s %zu\n", target->word, target->count);
}

int BinaryTree_dataCmp(BinaryTree_Data *a, BinaryTree_Data *b) {
    int result = strcmp(a->word, b->word);
    if (result < 0) {
        return -1;
    } else if (result > 0) {
        return 1;
    } else {
        return 0;
    }
}
