#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    int height;
    struct Node *leftNode;
    struct Node *rightNode;
};

struct Node *CreateNewNode(int value) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->height = 1;
    newNode->leftNode = NULL;
    newNode->rightNode = NULL;
    return newNode;
}

int myMax(int a, int b)
{
    return (a > b)? a : b;
}

struct Node *LeftRotation(struct Node *currNode) {
    struct Node* pivot = currNode->rightNode;
    struct Node* transferSubtree = pivot->leftNode;
    pivot->leftNode = currNode;     
    currNode->rightNode = transferSubtree; 

    int leftHeight = (currNode->leftNode != NULL) ? currNode->leftNode->height : 0;
    int rightHeight = (currNode->rightNode != NULL) ? currNode->rightNode->height : 0;
    currNode->height = myMax(leftHeight, rightHeight) + 1;
    pivot->height = myMax(pivot->leftNode->height, pivot->rightNode->height) + 1;

    return pivot;
}

struct Node *RightRotation(struct Node *currNode) {
    struct Node* pivot = currNode->leftNode;
    struct Node* transferSubtree = pivot->rightNode; 
    pivot->rightNode = currNode;
    currNode->leftNode = transferSubtree;

    int leftHeight = (currNode->leftNode != NULL) ? currNode->leftNode->height : 0;
    int rightHeight = (currNode->rightNode != NULL) ? currNode->rightNode->height : 0;
    currNode->height = myMax(leftHeight, rightHeight) + 1;

    leftHeight = (pivot->leftNode != NULL) ? pivot->leftNode->height : 0;
    rightHeight = (pivot->rightNode != NULL) ? pivot->rightNode->height : 0;
    pivot->height = myMax(leftHeight, rightHeight) + 1;

    return pivot;
}

struct Node *AddValue(struct Node *currNode, int value) {
    if (currNode == NULL) {
        return CreateNewNode(value);
    }
    if (value >= currNode->value) {
        currNode->rightNode = AddValue(currNode->rightNode, value);
    }
    else if (value < currNode->value) {
        currNode->leftNode = AddValue(currNode->leftNode, value);
    }

    int leftHeight = (currNode->leftNode != NULL) ? currNode->leftNode->height : 0;
    int rightHeight = (currNode->rightNode != NULL) ? currNode->rightNode->height : 0;
    int currNodeBalance = leftHeight - rightHeight;
    if (currNodeBalance < -1 && value > currNode->rightNode->value) {
        return LeftRotation(currNode);
    }
    else if (currNodeBalance < -1 && value < currNode->rightNode->value) {
        currNode->rightNode = RightRotation(currNode->rightNode); 
        return LeftRotation(currNode);
    }
    else if (currNodeBalance > 1 && value > currNode->leftNode->value) {
        currNode->leftNode = LeftRotation(currNode->leftNode);
        return RightRotation(currNode);
    }
    else if (currNodeBalance > 1 && value < currNode->leftNode->value) {
        return RightRotation(currNode);
    }

    currNode->height = myMax(leftHeight, rightHeight) + 1;
    return currNode;
}

void preOrder(struct Node *root)
{
    if(root != NULL)
    {
        printf("\n%d ", root->value);
        preOrder(root->leftNode);
        preOrder(root->rightNode);
    }
}

int main() {
    struct Node *root = NULL;
    root = AddValue(root, 10);
    root = AddValue(root, 20);
    root = AddValue(root, 30);
    root = AddValue(root, 40);
    root = AddValue(root, 50);
    root = AddValue(root, 25);

    printf("preOrder: \n");
    preOrder(root);
    return 0;
}