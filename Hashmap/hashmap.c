#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    int value;
    struct Node *next;
};

struct hm {
    struct Node **buckets;
    int size;
    int capacity;
};

int hash(int key, int capacity) {
    return key % capacity;
}

void Rehash(struct hm *hm) {
    hm->capacity = hm->capacity * 2;
    struct Node **newBuckets = malloc(hm->capacity * sizeof(struct Node*));
    for (int i=0; i <hm->size; i++) {
        struct Node *currNode = hm->buckets[i];
        if (currNode != NULL) {
            int index = hash(currNode->key, hm->capacity) % hm->capacity;
            if (newBuckets[index] != NULL) {
                currNode->next = newBuckets[index];
                newBuckets[index] = currNode;
            }
            else {
                newBuckets[index] = hm->buckets[i];
            }
        } 
    }
    free(hm->buckets);
    hm->buckets = newBuckets;
}

struct hm* CreateHashMap(int key, int value) {
    struct hm* newHm = malloc(sizeof(struct hm));
    newHm->capacity = 2;
    newHm->size = 1;
    newHm->buckets = malloc(newHm->capacity * sizeof(struct Node*));

    for (int i = 0; i < newHm->capacity; i++) {
        newHm->buckets[i] = NULL;
    }

    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    int index = hash(key, newHm->capacity);
    newHm->buckets[index] = newNode;

    return newHm;
}

void Insert(struct hm *hm, int key, int value) {
    if (hm->size == hm->capacity * 0.75) {
        Rehash(hm);
    }
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = value;
    int index = hash(key, hm->capacity) % hm->capacity;
    if (hm->buckets[index] != NULL) {
        newNode->next = hm->buckets[index];
        hm->buckets[index] = newNode; 
    }
    else {
        hm->buckets[index] = newNode;
    }
}

void Remove(struct hm *hm, int key) {
    int index = hash(key, hm->capacity);
    if (hm->buckets[index] == NULL) {
        return;
    }
    struct Node *currNode = hm->buckets[index];
    while (currNode->key != key) {
        currNode = currNode->next;
        if (currNode == NULL) {
            return;
        }
    }
    printf("Remove->key: %d\n", hm->buckets[index]->key);
    free(hm->buckets[index]);
    hm->buckets[index] = NULL;
}

struct Node *GetNode(struct hm *hm, int key) {
    int index = hash(key, hm->capacity);
    struct Node *currNode = hm->buckets[index];
    while (currNode->key != key) {
        currNode = currNode->next;
        if (currNode == NULL) {
            return NULL;
        }
    }
    printf("GetNode->value: %d\n", currNode->value);
    return currNode;
}



int main() {
    struct hm *hm = CreateHashMap(5, 10);
    Insert(hm, 20, 50);
    Insert(hm, 100, 223);
    int value = GetNode(hm, 20)->value;
    int value2 = GetNode(hm, 100)->value;
    printf("value: %d\n", value);
    printf("value2: %d\n", value2);
    Remove(hm, 20);
    int value3 = GetNode(hm, 20)->value;
    printf("value: %d\n", value3);
    return 0;
}