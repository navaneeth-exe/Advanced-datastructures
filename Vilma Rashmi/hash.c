#include <stdio.h>
#define SIZE 10
int hashTable[SIZE];
void init() {
    for (int i = 0; i < SIZE; i++)
        hashTable[i] = -1;
int hashFunction(int key) {
    return key % SIZE;
}
void insert(int key) {
    int index = hashFunction(key);
    if (hashTable[index] == -1)
        hashTable[index] = key;
    else
        printf("Collision occurred at index %d\n", index);
}
void search(int key) {
    int index = hashFunction(key);
    if (hashTable[index] == key)
        printf("Key %d found at index %d\n", key, index);
    else
        printf("Key %d not found\n", key);
}
void delete(int key) {
    int index = hashFunction(key);
    if (hashTable[index] == key) {
        hashTable[index] = -1;
        printf("Key %d deleted\n", key);
    } else {
        printf("Key %d not found\n", key);
    }
}
void display() {
    for (int i = 0; i < SIZE; i++)
        printf("Index %d : %d\n", i, hashTable[i]);
}
int main() {
    init();
    insert(10);
    insert(25);
    insert(30);
    display();
    search(25);
    delete(25);
    search(25);
    return 0;
}
