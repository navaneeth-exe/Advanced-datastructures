#include<stdio.h>
#include <stdlib.h>

#define SIZE 97     //prime number to avoid collision

struct Node{
    int key;
    struct Node* next;
};

struct Node *hashTable[SIZE];

//hashing
int hashfn(int key){
    return key % SIZE;
}


//to insert the array elements into the hash table
void insert(int key){
    int index = hashfn(key);  //find the index
    struct Node *temp = hashTable[index]; 
    while(temp!=NULL){
        if(temp->key == key){
            return;             //if key already exists, then return.
        }
        temp = temp->next;  
    }
    //else insert it at the beginning
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

//to search whether the array element exists in the hash table or not.
int search(int key){
    int index = hashfn(key);
    struct Node *temp = hashTable[index];
    while(temp!=NULL){
        if(temp->key == key){
            return 1;           //if the key exists in the table
        }
        temp = temp->next;
    }
    return 0;   //if not
}

int main(){

    int n;          //size of the array
    int maxLength = 0;

    printf("Enter number of elements : ");
    scanf("%d", &n);

    int arr[n];

    //insert the elements into the array
    printf("Enter the array elements :\n");
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }

    //insert those array elements into the hash table
    for(int i=0; i<n; i++){
        insert(arr[i]);
    }

    for(int i=0; i<n; i++){
        if (search(arr[i] - 1) == 0){ 
        //(x-1) not found. To start from the smallest number in the sequence       
            int current = arr[i];
            int count = 1;                //number starting point
            while(search(current + 1) == 1){   //checks if (x+1) element exists
                current ++;
                count ++;
            }

            if(count > maxLength){
                maxLength = count;
            }
        }
    }

    printf("The longest sequence is : %d",maxLength);
}

