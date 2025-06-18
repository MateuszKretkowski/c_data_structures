#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
};

struct Stack {
    struct Node *headNode;
    int size;
};

struct Stack *CreateStack(int value) {
    struct Stack *newStack;
    struct Node *newNode;
    newStack = malloc(sizeof(struct Stack));
    newNode = malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = NULL;
    newStack->headNode = newNode;
    newStack->size++;
    return newStack;
}

void Push(struct Stack *stack, int value) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = stack->headNode;
    stack->headNode = newNode;
    stack->size++;
}

void Pop(struct Stack *stack) {
    free(stack->headNode);
    stack->headNode = stack->headNode->next;
    stack->size--;
}

void PrintStack(struct Stack *stack) {
    struct Node *currentNode = stack->headNode;
    printf("\nHeadNode: %d", currentNode->value);
    while(currentNode->next != NULL) {
        currentNode = currentNode->next;
        printf("\nNode: %d", currentNode->value);
    }
}

int StackLength(struct Stack *stack) {
    return stack->size;
}

void FreeNodeMemory(struct Stack *stack) {
    while (stack->headNode != NULL) {
        struct Node *current = stack->headNode;
        stack->headNode = stack->headNode->next;
        free(current);
    }
    free(stack);
}


int main() {
    struct Stack *stack;
    printf("\nHow much Nodes would you like in a Stack: ");
    int num;
    scanf("%d", &num);
    for (int i=0; i<num; i++) {
        printf("\nPick a value for this specific Node: ");
        int value;
        scanf("%d", &value);
        if (i==0) {
            stack = CreateStack(value);
        }
        else {
            Push(stack, value);
        }
    }
    printf("\n===================================");
    PrintStack(stack);
    printf("\n===================================");
    printf("\nHow many pops: ");
    int popNum;
    scanf("%d", &popNum);
    for (int i=0; i<popNum; i++) {
        Pop(stack);
    }
    printf("\n===================================");
    PrintStack(stack);
    printf("\n===================================");

    return 0;
}