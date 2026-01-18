#include <stdio.h>
#include <stdbool.h>
#define SIZE 20

int bloom[SIZE]={0};

int hash1(int key){
    return key%SIZE;
}

int hash2(int key){
    return (key/7)%SIZE;
}

void insert(){
    int key;
    printf("enter key to insert:");
    scanf("%d",&key);
    bloom[hash1(key)]=1;
    bloom[hash2(key)]=1;
    printf("insertion done ");
    }
    
void search(){
    int key;
    printf("enter key to search:");
    scanf("%d",&key);
    if(bloom[hash1(key)]&& bloom[hash2(key)])
    printf("the element might be present");
    else
    printf("the element is not present");
}

void display(){
printf("the bloom filter array\n: ");
for(int i=0;i<SIZE;i++){
    printf("%d",bloom[i]);
}}

int main() {
 int choice;
 do{
 printf("\n----bloom filter----\n");
 printf("1)insert element\n");
 printf("2)search element\n");
 printf("3)display\n");
 printf("4)exit\n");
 printf("enter you choice :");
 scanf("%d",&choice);
 switch (choice){
     case 1:insert();
     break;
     case 2:search();
     break;
     case 3:display();
     break;
     case 4: printf("exiting form program");
     break;
     default: printf("invalid choice. try again");
     
 }
 }while(choice!=4);

    return 0;
}