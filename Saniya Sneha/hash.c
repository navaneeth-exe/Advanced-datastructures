#include <stdio.h>

#define TABLE_SIZE 10
#define EMPTY -1
#define DELETED -2

int hashTable[TABLE_SIZE];


int hash(int key) {
return key % TABLE_SIZE;
}


void insert(int key) {
int index = hash(key);
while (hashTable[index] != EMPTY && hashTable[index] != DELETED) {
index = (index + 1) % TABLE_SIZE;
}
hashTable[index] = key;
printf("Inserted %d\n", key);
}


void search(int key) {
int index = hash(key);
int start = index;

while (hashTable[index] != EMPTY) {  
    if (hashTable[index] == key) {  
        printf("Key %d found at index %d\n", key, index);  
        return;  
    }  
    index = (index + 1) % TABLE_SIZE;  
    if (index == start)  
        break;  
}  
printf("Key %d not found\n", key);

}


void deleteKey(int key) {
int index = hash(key);
int start = index;

while (hashTable[index] != EMPTY) {  
    if (hashTable[index] == key) {  
        hashTable[index] = DELETED;  
        printf("Key %d deleted\n", key);  
        return;  
    }  
    index = (index + 1) % TABLE_SIZE;  
    if (index == start)  
        break;  
}  
printf("Key %d not found for deletion\n", key);

}


void display() {
for (int i = 0; i < TABLE_SIZE; i++) {
if (hashTable[i] >= 0)
printf("[%d] %d\n", i, hashTable[i]);
else
printf("[%d] ---\n", i);
}
}
int main() {
    int choice, key;

    
    for (int i = 0; i < TABLE_SIZE; i++)
        hashTable[i] = EMPTY;

    while (1) {
        printf("\n--- HASH TABLE MENU ---\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(key);
                break;

            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                search(key);
                break;

            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteKey(key);
                break;

            case 4:
                display();
                break;

            case 5:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
