#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
};

struct Queue {
    int size;
    struct Node *headNode;
    struct Node *lastNode;
};

struct Queue *CreateQueue(int value) {
    struct Node *headNode = malloc(sizeof(struct Node));
    struct Queue *queue = malloc(sizeof(struct Queue));
    headNode->value = value;
    headNode->next = NULL;
    queue->headNode = headNode;
    queue->lastNode = headNode;
    queue->size++;
    return queue;
}

void Enqueue(struct Queue *queue, int value) {
    if (queue->headNode == NULL || queue->size == 0) {
        return;
    }
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = NULL;
    queue->lastNode->next = newNode;
    queue->lastNode = newNode;
    queue->size++;
}

void Dequeue(struct Queue *queue) {
    if (queue->size < 1) {
        return;
    }
    free(queue->headNode);
    queue->headNode = queue->headNode->next;
    queue->size--;
}

void PrintQueue(struct Queue *queue) {
    struct Node *currNode = queue->headNode;
    printf("\n====================================");
    printf("\nHeadNode: %d", currNode->value);
    currNode = currNode->next;
    while (currNode != NULL) {
        printf("\nNode: %d", currNode->value);
        currNode = currNode->next;
    }
    printf("\n====================================");
} 

int main() {
    struct Queue *queue;
    printf("\nHow much Nodes would you like to Enqueue: ");
    int num;
    scanf("%d", &num);
    for (int i=0; i<num; i++) {
        printf("\nPick a value for this specific Node: ");
        int value;
        scanf("%d", &value);
        if (i == 0) {
            queue = CreateQueue(value);
        }
        else {
            Enqueue(queue, value);
        }
    }
    PrintQueue(queue);
    printf("ASD");
    printf("\nHow many Dequeues would you like?: ");
    scanf("%d", &num);
    for (int i=0; i<num; i++) {
        Dequeue(queue);
    }
    PrintQueue(queue);
    free(queue);
    return 0;
}