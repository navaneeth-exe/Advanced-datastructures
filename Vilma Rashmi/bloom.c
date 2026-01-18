#include <stdio.h>

#define SIZE 10

int bloom[SIZE] = {0};

/* Hash functions */
int hash1(int key) {
    return key % SIZE;
}

int hash2(int key) {
    return (key / 7) % SIZE;
}

/* Insert */
void insert(int key) {
    bloom[hash1(key)] = 1;
    bloom[hash2(key)] = 1;
}

/* Search */
void search(int key) {
    if (bloom[hash1(key)] == 1 && bloom[hash2(key)] == 1)
        printf("Key %d is probably present\n", key);
    else
        printf("Key %d is definitely not present\n", key);
}

/* Display */
void display() {
    for (int i = 0; i < SIZE; i++)
        printf("%d ", bloom[i]);
    printf("\n");
}

int main() {
    insert(10);
    insert(20);
    insert(30);

    display();

    search(10);
    search(25);   // may give false positive or not

    return 0;
}