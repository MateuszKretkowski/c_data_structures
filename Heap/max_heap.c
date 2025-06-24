#include <stdio.h>
#include <stdlib.h>

struct MaxHeap {
    int *data;
    int size;
    int capacity;
};

void HeapifyUp(struct MaxHeap *heap, int i);
void HeapifyDown(struct MaxHeap *heap, int i);
void Swap(struct MaxHeap *heap, int a, int b);

struct MaxHeap *CreateNewHeap(int value, int capacity) {
    struct MaxHeap *newHeap = malloc(sizeof(struct MaxHeap));
    newHeap->data = malloc(capacity * sizeof(int));
    newHeap->capacity = capacity;
    newHeap->size = 1;
    newHeap->data[0] = value;
    return newHeap;
}

void Insert(struct MaxHeap *heap, int value) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = realloc(heap->data, heap->capacity * sizeof(int));
    }
    heap->data[heap->size] = value;
    heap->size++;
    
    HeapifyUp(heap, (heap->size - 1));
}

int Remove(struct MaxHeap *heap, int index) {
    if (index < 0 || index >= heap->size) {
        return -1;
    }
    int value = heap->data[index];

    heap->data[index] = heap->data[heap->size - 1];
    heap->size--;

    if (heap->size > 0 && index < heap->size) {
        HeapifyDown(heap, index);
    }
    
    return value;
}

int ExtractMax(struct MaxHeap *heap) {
    int value = heap->data[0];
    Remove(heap, 0);
    return value;
}

int ExtractMin(struct MaxHeap *heap) {
    int value = heap->data[heap->size - 1];
    Remove(heap, heap->size - 1);
    return value;
}

void HeapifyUp(struct MaxHeap *heap, int i) {
    if (i == 0) {
        return;
    }
    int parent = (i - 1) / 2;
    if (heap->data[parent] < heap->data[i]) {
        Swap(heap, parent, i);
        HeapifyUp(heap, parent);
    }
}

void HeapifyDown(struct MaxHeap *heap, int i) {
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;
    int index = i;

    if (leftChild < heap->size && heap->data[i] < heap->data[leftChild]) {
        index = leftChild;
    }
    if (rightChild < heap->size && heap->data[rightChild] > heap->data[index]) {
        index = rightChild;
    }
    if (index != i) {
        Swap(heap, i, index);
        HeapifyDown(heap, index);
    }
    return;
}

void printHeap(struct MaxHeap *heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

void Swap(struct MaxHeap *heap, int a, int b) {
    int temp = heap->data[a];
    heap->data[a] = heap->data[b];
    heap->data[b] = temp;
}

int main() {
    struct MaxHeap *heap;
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
