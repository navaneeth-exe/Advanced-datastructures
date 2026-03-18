#include <stdio.h>
#include <stdlib.h>

typedef struct HashNode {
    int key;
    int value;
    struct HashNode* next;
} HashNode;

#define SIZE 1000

HashNode* hashTable[SIZE];

int hash(int key) {
    if(key < 0) key = -key;
    return key % SIZE;
}

void insert(int key) {
    int h = hash(key);
    HashNode* node = hashTable[h];
    while (node) {
        if (node->key == key) {
            node->value++;
            return;
        }
        node = node->next;
    }
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->value = 1;
    newNode->next = hashTable[h];
    hashTable[h] = newNode;
}

int get(int key) {
    int h = hash(key);
    HashNode* node = hashTable[h];
    while (node) {
        if (node->key == key)
            return node->value;
        node = node->next;
    }
    return 0;
}


int countZeroSumSubarrays(int arr[], int n) {
    for(int i = 0; i < SIZE; i++) hashTable[i] = NULL;

    int sum = 0, count = 0;
    insert(0);

    for(int i = 0; i < n; i++) {
        sum += arr[i];
        count += get(sum);
        insert(sum);
    }
    return count;
}


int main() {
    int arr[] = {1, 2, -3, 3, -1, -2};
    int n = sizeof(arr)/sizeof(arr[0]);

    int result = countZeroSumSubarrays(arr, n);
    printf("Total subarrays with sum 0: %d\n", result);

    return 0;
}
