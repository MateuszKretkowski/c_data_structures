#include <stdio.h>
#include <stdlib.h>

struct MinHeap {
    int *data;
    int size;
    int capacity;
};

void HeapifyUp(struct MinHeap *heap, int i);
void HeapifyDown(struct MinHeap *heap, int i);
void Swap(struct MinHeap *heap, int a, int b);

struct MinHeap *CreateNewHeap(int value, int capacity) {
    struct MinHeap *newHeap = malloc(sizeof(struct MinHeap));
    newHeap->data = malloc(capacity * sizeof(int));
    newHeap->capacity = capacity;
    newHeap->size = 1;
    newHeap->data[0] = value;
    return newHeap;
}

void Insert(struct MinHeap *heap, int value) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = realloc(heap->data, heap->capacity * sizeof(int));
    }
    heap->data[heap->size] = value;
    heap->size++;
    
    HeapifyUp(heap, (heap->size - 1));
}

int Remove(struct MinHeap *heap, int index) {
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

int ExtractMin(struct MinHeap *heap) {
    int value = heap->data[0];
    Remove(heap, 0);
    return value;
}

int ExtractMax(struct MinHeap *heap) {
    int value = heap->data[heap->size - 1];
    Remove(heap, heap->size - 1);
    return value;
}

void HeapifyUp(struct MinHeap *heap, int i) {
    if (i == 0) {
        return;
    }
    int parent = (i - 1) / 2;
    if (heap->data[parent] > heap->data[i]) {
        Swap(heap, parent, i);
        HeapifyUp(heap, parent);
    }
}

void HeapifyDown(struct MinHeap *heap, int i) {
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;
    int index = i;
    if (i >= heap->size - 1) {
        return;
    }
    if (leftChild < heap->size && heap->data[i] > heap->data[leftChild]) {
        index = leftChild;
    }
    if (rightChild < heap->size && heap->data[rightChild] < heap->data[index]) {
        index = rightChild;
    }
    if (index != i) {
        Swap(heap, i, index);
        HeapifyDown(heap, index);
    }
    return;
}

void printHeap(struct MinHeap *heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

void Swap(struct MinHeap *heap, int a, int b) {
    int temp = heap->data[a];
    heap->data[a] = heap->data[b];
    heap->data[b] = temp;
}

int main() {
    struct MinHeap *heap;
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