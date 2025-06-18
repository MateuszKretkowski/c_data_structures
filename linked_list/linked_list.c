#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
};

struct Node *CreateHeadNode(int value, struct Node *next) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = next;
    return newNode;
}

void CreateNode(struct Node *headNode, int value) {
    struct Node *currentNode = headNode;
    while(currentNode->next != NULL) {
        currentNode = currentNode->next;
    }
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = NULL;
    currentNode->next = newNode;
}

void PrintLinkedList(struct Node *headNode) {
    struct Node *currentNode = headNode;
    printf("\nHeadNode: %d", currentNode->value);
    while(currentNode->next != NULL) {
        currentNode = currentNode->next;
        printf("\nNode: %d", currentNode->value);
    }
}


int main() {
    struct Node *headNode = NULL;
    headNode = CreateHeadNode(0, NULL);
    printf("\nHow much Nodes would you like in a linked list: ");
    int num;
    scanf("%d", &num);
    for (int i=0; i<num; i++) {
        printf("\nPick a value for this specific Node: ");
        int value;
        scanf("%d", &value);
        CreateNode(headNode, value);
    }
    printf("\n===================================");
    PrintLinkedList(headNode);
    return 0;
}