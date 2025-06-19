#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node *next;
    int value;
};

struct LinkedList {
    struct Node *headNode;
    int size;
};

struct LinkedList *CreateLinkedList(int value) {
    struct LinkedList *linkedList = malloc(sizeof(struct LinkedList));
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = NULL;
    linkedList->headNode = newNode;
    linkedList->size++;
    return linkedList;
}

void CreateNode(struct LinkedList *linkedList, int value) {
    struct Node *currentNode = linkedList->headNode;
    while(currentNode->next != NULL) {
        currentNode = currentNode->next;
    }
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = NULL;
    currentNode->next = newNode;
    linkedList->size++;
}

void RemoveNode(struct LinkedList *linkedList, int index) {
    if (linkedList->size < index+1) {
        return;
    }
    if (index == 0) {
        free(linkedList->headNode);
        linkedList->headNode = linkedList->headNode->next;
        linkedList->size--;
        return;
    }
    struct Node *currNode = linkedList->headNode;
    printf("Size: %d", linkedList->size);
    for (int i=1; i<linkedList->size-1; i++) {
        if (i == index) {
            free(currNode->next);
            printf("Removing");
            currNode->next = currNode->next->next;
            linkedList->size--;
            return;
        }
        currNode = currNode->next;
    }
}

void PrintLinkedList(struct LinkedList *LinkedList) {
    struct Node *currentNode = LinkedList->headNode;
    printf("\n===================================");
    printf("\nHeadNode: %d", currentNode->value);
    while(currentNode->next != NULL) {
        currentNode = currentNode->next;
        printf("\nNode: %d", currentNode->value);
    }
    printf("\n===================================");
}


int main() {
    struct LinkedList *linkedList;
    printf("\nHow much Nodes would you like in a linked list: ");
    int num;
    scanf("%d", &num);
    for (int i=0; i<num; i++) {
        printf("\nPick a value for this specific Node: ");
        int value;
        scanf("%d", &value);
        if (i == 0) {
            linkedList = CreateLinkedList(value);
        }
        else {
            CreateNode(linkedList, value);
        }
    }
    PrintLinkedList(linkedList);
    printf("\nChoose an index to Remove: ");
    int indexToRemove;
    scanf("%d", &indexToRemove);
    RemoveNode(linkedList, indexToRemove);
    PrintLinkedList(linkedList);
    free(linkedList);
    return 0;
}