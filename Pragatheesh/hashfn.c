#include<stdio.h>
#include<stdlib.h>

#define tablesize 10 

struct node {
    int key;
    struct node* next;
};

struct node* hashTable[tablesize];

int hashfunction(int key){
    return key % tablesize;
}

void insert(int key){
    int index = hashfunction(key);
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->key = key;
    newnode->next = hashTable[index];
    hashTable[index] = newnode;
    printf("key %d inserted at index %d\n", key, index);
}

void search(int key){
    int index = hashfunction(key);
    struct node* temp = hashTable[index];

    while(temp != NULL){
        if(temp->key == key){
            printf("key %d found at index %d\n", key, index);
            return;
        }
        temp = temp->next;
    }
    printf("key %d not found\n", key);
}

void delete(int key){
    int index = hashfunction(key);
    struct node* temp = hashTable[index];
    struct node* prev = NULL;

    while(temp != NULL){
        if(temp->key == key){
            if(prev == NULL)
                hashTable[index] = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            printf("key %d deleted from index %d\n", key, index);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("key %d not found for deletion\n", key);
}

void display(){
    for(int i = 0; i < tablesize; i++){
        struct node* temp = hashTable[i];
        printf("index %d: ", i);
        while(temp != NULL){
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main(){
    int key, choice;

    for(int i = 0; i < tablesize; i++)
        hashTable[i] = NULL;

    while(1){
        printf("\n1.Insert\n2.Search\n3.Delete\n4.Display\n5.Exit\n");
        printf("enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("enter the value to insert: ");
                scanf("%d", &key);
                insert(key);
                break;

            case 2:
                printf("enter the value to search: ");
                scanf("%d", &key);
                search(key);
                break;

            case 3:
                printf("enter the value to delete: ");
                scanf("%d", &key);
                delete(key);
                break;

            case 4:
                display();
                break;

            case 5:
                exit(0);

            default:
                printf("invalid choice\n");
        }
    }
    return 0;
}
