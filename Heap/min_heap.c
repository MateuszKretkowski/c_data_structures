#include <stdio.h>
#include <stdlib.h>

struct Heap {
    int *data;
    int size;
    int capacity;
};

struct Heap *CreateNewHeap(int *value, int capacity) {
    struct Heap *newHeap = malloc(sizeof(struct Heap));
    newHeap->data = malloc(sizeof(capacity) * sizeof(int));
    newHeap->capacity = capacity;
    newHeap->size = 1;
    newHeap->data[0] = value;
    return newHeap;
}

void Insert(int value, struct Heap *heap) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = realloc(heap->data, heap->capacity * sizeof(int));
    }
    heap->data[heap->size] = value;
    
    HeapifyDown(heap->data, (heap->size + (heap->size-1)/2));
}

int *Remove(int value, struct Heap *heap) {
    if (heap->size == 1) {
        heap->data[0] = NULL;
    }
    else if (heap->data[sizeof(heap->data)/sizeof(heap->data[0])] == value) {
        // bede potem tworzyl...
    }
}

// parent of currNode = (i - 1) / 2;
// left child = 2 * i + 1;
// right child = 2 * i + 2;

int *HeapifyDown(int *data, int i) {
    if (i < 0) {
        return data[0];
    }
    int currValue = data[i];
    int index = NULL;
    if (currValue > data[2 * i + 1]) {
        int temp = data[2*i+1];
        data[2*i+1] = currValue;
        data[i] = temp;
        index = 2*i+1;
    }
    else if (currValue > data[2*i+2]) {
        int temp = data[2*i+2];
        data[2*i+2] = currValue;
        data[i] = temp;
        index = 2*i+2;
    }

    if (index != NULL) {
        data[index] = Heapify(data, index);
    }
    else {
        return Heapify(data, (i-1)/2);
    }
}

int main() {
    return 0;
}