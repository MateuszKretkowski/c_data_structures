#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *leftNode;
    struct Node *rightNode;
};

struct bst {
    int size;
    struct Node *rootNode;
};

struct bst *CreateBinarySearchTree(int value) {
    struct Node *newRootNode = malloc(sizeof(struct Node));
    struct bst *newBst = malloc(sizeof(struct bst));

    newRootNode->value = value;
    newRootNode->leftNode = NULL;
    newRootNode->rightNode = NULL;

    newBst->size = 1;
    newBst->rootNode = newRootNode;

    return newBst;
}

void AddValue(struct bst *bst, int value, struct Node *currNode) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->value = value;
    if (currNode->value < value) {
        if (currNode->rightNode == NULL) {
            currNode->rightNode = newNode;
            return;
        }
        AddValue(bst, value, currNode->rightNode);
    }
    else {
        if (currNode->leftNode == NULL) {
            currNode->leftNode = newNode;
            return;
        }
        AddValue(bst, value, currNode->leftNode);
    }
}

void InOrderTraversalPrint(struct Node *currNode) {
    if (currNode == NULL) {
        return;
    }
    InOrderTraversalPrint(currNode->leftNode);
    printf("\n%d, ", currNode->value);
    InOrderTraversalPrint(currNode->rightNode);
}

int main() {
    struct bst *bst;
    printf("\nHow many nodes would you like to add to BST: ");
    int num;
    scanf("%d", &num);
    for (int i=0; i<num; i++) {
        printf("\nAdd a Value: ");
        int value;
        scanf("%d", &value);
        if (i==0) {
            bst = CreateBinarySearchTree(value);
        }
        else {
            AddValue(bst, value, bst->rootNode);
        }
    }
    InOrderTraversalPrint(bst->rootNode);
    return 0;
}