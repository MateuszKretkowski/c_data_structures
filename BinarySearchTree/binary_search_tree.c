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

void AddValue(int value, struct Node *currNode) {
    if (currNode->value < value) {
        if (currNode->rightNode == NULL) {
            struct Node *newNode = malloc(sizeof(struct Node));
            newNode->value = value;
            currNode->rightNode = newNode;
            return;
        }
        AddValue(value, currNode->rightNode);
    }
    else {
        if (currNode->leftNode == NULL) {
            struct Node *newNode = malloc(sizeof(struct Node));
            newNode->value = value;
            currNode->leftNode = newNode;
            return;
        }
        AddValue(value, currNode->leftNode);
    }
}

struct Node *FindSuccessor(struct Node *currNode) {
    currNode = currNode->rightNode;
    while (currNode->leftNode != NULL) {
        currNode = currNode->leftNode;
    }
    return currNode;
}

struct Node *RemoveValue(struct Node *currNode, int value) {
    if (value > currNode->value) {
        currNode->rightNode = RemoveValue(currNode->rightNode, value);
    }
    else if (value < currNode->value) {
        currNode->leftNode = RemoveValue(currNode->leftNode, value);
    }
    else {
        if (currNode->leftNode == NULL) {
            struct Node *temp = currNode->rightNode;
            free(currNode);
            return temp;
        }

        if (currNode->rightNode == NULL) {
            struct Node *temp = currNode->leftNode;
            free(currNode);
            return temp;
        }

        struct Node *successor = FindSuccessor(currNode->rightNode);
        currNode->value = successor->value;
        currNode->rightNode = RemoveValue(currNode->rightNode, successor->value);
        
    }
    return currNode;
}

void InOrderTraversalPrint(struct Node *currNode) {
    if (currNode == NULL) {
        return;
    }
    InOrderTraversalPrint(currNode->leftNode);
    printf("\n%d, ", currNode->value);
    InOrderTraversalPrint(currNode->rightNode);
}

void FreeTree(struct bst *bst, struct Node *currNode) {
    FreeTree(bst, currNode->leftNode);
    free(currNode);
    FreeTree(bst, currNode->rightNode);
    free(bst);
}

// NA JUTRO:
/* 
- Free Tree();
- GetValue();
- Jestem Zajebisty;
*/

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
            AddValue(value, bst->rootNode);
        }
    }
    InOrderTraversalPrint(bst->rootNode);

    printf("Pick a value to Remove: ");
    int num2;
    scanf("%d", &num2);
    bst->rootNode = RemoveValue(bst->rootNode, num2);
    InOrderTraversalPrint(bst->rootNode);
    return 0;
}