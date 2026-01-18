## 1. Implement a simple hash table and demonstrate insertion, searching and deletion in it.
## ANS,

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

/* Structure for a hash table node */
typedef struct Node {
    int key;
    char value[50];
    struct Node *next;
} Node;

/* Hash table (array of pointers) */
Node *hashTable[TABLE_SIZE];

/* Hash function */
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

/* Insert key-value pair */
void insert(int key, const char *value) {
    int index = hashFunction(key);

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    strcpy(newNode->value, value);
    newNode->next = hashTable[index];

    hashTable[index] = newNode;
}

/* Search for a key */
Node *search(int key) {
    int index = hashFunction(key);
    Node *temp = hashTable[index];

    while (temp != NULL) {
        if (temp->key == key)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

/* Delete a key */
void delete(int key) {
    int index = hashFunction(key);
    Node *temp = hashTable[index];
    Node *prev = NULL;

    while (temp != NULL) {
        if (temp->key == key) {
            if (prev == NULL)
                hashTable[index] = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            printf("Key %d deleted successfully.\n", key);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Key %d not found.\n", key);
}

/* Display hash table */
void display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *temp = hashTable[i];
        printf("Index %d: ", i);
        while (temp != NULL) {
            printf("(%d, %s) -> ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

/* Main function to demonstrate operations */
int main() {
    /* Initialize hash table */
    for (int i = 0; i < TABLE_SIZE; i++)
        hashTable[i] = NULL;

    /* Insert elements */
    insert(1, "Apple");
    insert(11, "Banana");
    insert(21, "Orange");
    insert(2, "Grapes");

    printf("Hash Table after insertion:\n");
    display();

    /* Search */
    Node *result = search(11);
    if (result != NULL)
        printf("\nSearch result: Key 11 => Value %s\n", result->value);
    else
        printf("\nKey not found.\n");

    /* Delete */
    delete(11);

    printf("\nHash Table after deletion:\n");
    display();

    return 0;
}

## 2. Implement a bloom filter and demonstrate it's probabilistic nature.
## ANS,

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOOM_SIZE 100
#define HASH_COUNT 3

/* Bloom filter bit array */
int bloom[BLOOM_SIZE] = {0};

/* Hash functions */
unsigned int hash1(const char *str) {
    unsigned int hash = 5381;
    while (*str)
        hash = ((hash << 5) + hash) + (*str++);
    return hash % BLOOM_SIZE;
}

unsigned int hash2(const char *str) {
    unsigned int hash = 0;
    while (*str)
        hash = (hash * 31) + (*str++);
    return hash % BLOOM_SIZE;
}

unsigned int hash3(const char *str) {
    unsigned int hash = 7;
    while (*str)
        hash = (hash * 17) + (*str++);
    return hash % BLOOM_SIZE;
}

/* Insert element into Bloom filter */
void bloom_insert(const char *item) {
    bloom[hash1(item)] = 1;
    bloom[hash2(item)] = 1;
    bloom[hash3(item)] = 1;
}

/* Check membership */
int bloom_check(const char *item) {
    if (bloom[hash1(item)] &&
        bloom[hash2(item)] &&
        bloom[hash3(item)])
        return 1;   // Possibly present
    return 0;       // Definitely not present
}

/* Main demonstration */
int main() {
    /* Insert elements */
    bloom_insert("apple");
    bloom_insert("banana");
    bloom_insert("orange");

    /* Test elements */
    const char *testItems[] = {
        "apple",     // present
        "banana",    // present
        "grape",     // not inserted
        "melon",     // not inserted
        "orange"     // present
    };

    printf("Bloom Filter Test Results:\n\n");

    for (int i = 0; i < 5; i++) {
        if (bloom_check(testItems[i]))
            printf("%s: Possibly present\n", testItems[i]);
        else
            printf("%s: Definitely not present\n", testItems[i]);
    }

    return 0;
}

Demonstrating the Probabilistic Nature

-> No False Negatives

Any inserted item (apple, banana, orange) is never reported as not present

->False Positives

An item not inserted (e.g., grape) may appear present

This happens due to hash collisions