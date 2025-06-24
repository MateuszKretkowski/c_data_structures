#include <stdio.h>
#include <stdlib.h>

struct Heap {
    int *data;
    int size;
    int capacity;
};

void HeapifyUp(struct Heap *heap, int i);
void HeapifyDown(struct Heap *heap, int i);
void Swap(struct Heap *heap, int a, int b);

struct Heap *CreateNewHeap(int value, int capacity) {
    struct Heap *newHeap = malloc(sizeof(struct Heap));
    newHeap->data = malloc(capacity * sizeof(int));
    newHeap->capacity = capacity;
    newHeap->size = 1;
    newHeap->data[0] = value;
    return newHeap;
}
void Insert(struct Heap *heap, int value) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = realloc(heap->data, heap->capacity * sizeof(int));
    }
    heap->data[heap->size] = value;
    heap->size++;
    
    HeapifyUp(heap, (heap->size-1));
}

int Remove(struct Heap *heap, int index) {
    if (index < 0 || index >= heap->size) {
        return -1;
    }
    int value = heap->data[index];

    heap->data[index] = heap->data[heap->size-1];
    heap->size--;
    
    if (heap->size > 0 && index < heap->size) {
        HeapifyDown(heap, index);
    }
    
    return value;
}

int ExtractMin(struct Heap *heap) {
    int value = heap->data[0];
    Remove(heap, 0);
    return value;
}

int ExtractMax(struct Heap *heap) {
    int value = heap->data[heap->size-1];
    Remove(heap, heap->size-1);
    return value;
}


void HeapifyUp(struct Heap *heap, int i) {
    if (i == 0) {
        return;
    }
    int parent = (i - 1) / 2;
    if (heap->data[parent] > heap->data[i]) {
        Swap(heap, parent, i);
        HeapifyUp(heap, parent);
    }
}

// parent of currNode = (i - 1) / 2;
// left child = 2 * i + 1;
// right child = 2 * i + 2;


void HeapifyDown(struct Heap *heap, int i) {
    int leftChild = 2*i+1;
    int rightChild = 2*i+2;
    if (i >= heap->size-1) {
        return;
    }
    if (leftChild < heap->size || heap->data[i] > heap->data[leftChild]) {
        Swap(heap, i, leftChild);
        HeapifyDown(heap, leftChild);
    }
    else if (rightChild < heap->size || heap->data[i] > heap->data[rightChild]) {
        Swap(heap, i, rightChild);
        HeapifyDown(heap, rightChild);
    }
    return;
}

void printHeap(struct Heap *heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

void Swap(struct Heap *heap, int a, int b) {
    int temp = heap->data[a];
    heap->data[a] = heap->data[b];
    heap->data[b] = temp;
}

int main() {
    struct Heap *heap;
    heap = CreateNewHeap(3, 5);
    
    Insert(heap, 2);
    Insert(heap, 1);
    Insert(heap, 15);
    Insert(heap, 5);
    Insert(heap, 4);
    Insert(heap, 45); 

    Remove(heap, 0);

    printHeap(heap);
    return 0;
}