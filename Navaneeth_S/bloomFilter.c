#include<stdio.h>
#include<string.h>

#define SIZE 25

int bitArray[SIZE];

//1st hash func
int hash1(char *str){
    int h = 0;
    for(int i=0; str[i]!='\0'; i++){
        h = (h * 31 + str[i]) % SIZE;
    }
    return h;
}

//2nd hash function
int hash2(char *str){
    int h=0;
    for(int i=0; str[i]!='\0'; i++){
        h = (h * 17 + str[i]) % SIZE;
    }
    return h;
}

//The string is case sensitive so i need to find the solution for that
//convert the uppercase chara to lowercase, create a fn and call it in insert and search

void toLowerCase(char *str){
    for(int i=0; str[i]!='\0'; i++){
        if(str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;    //converting to lower
        }
    }
}
//insert functin
void insert(char *str){
    toLowerCase(str);

    int index1 = hash1(str);
    int index2 = hash2(str);

    //set both index's bit array value to 1
    bitArray[index1] = 1;
    bitArray[index2] = 1;
}

//gonna write the search func next
void search(char *str){
    toLowerCase(str);

    int index1 = hash1(str);
    int index2 = hash2(str);

    //if both the indexes are 1 then there is a *possibility* that the string is present
    if(bitArray[index1] == 1 && bitArray[index2] == 1){
        printf("%s is POSSIBLY present \n", str);
    }else{
        printf("%s is NOT present :( \n",str);
    }
}

//display function to display the bit array
void display(){
    printf("Bit Array is : ");
    for(int i=0; i<SIZE; i++){
        printf("%d ", bitArray[i]);
    }
    printf("\n");
}

//main func
int main(){
    int choice;
    char str[20];

    //need to initialize the bit array with 0 initially 
    for(int i=0; i<SIZE; i++){
        bitArray[i] = 0;
    }

    while(1){
        
        printf("1.Insert \n2.Search \n3.Display \n4.Exit! \n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch(choice){
            case 1: 
                printf("Enter the string/value to insert : ");
                scanf("%s", str);
                //call insert function
                insert(str);
                break;

            case 2:
                printf("Enter the string to search : ");
                scanf("%s", str);
                //call the search function
                search(str);
                break;

            case 3:
                //Calling display func
                display();
                break;
            
            case 4:
                return 0;
            
            default:
                printf("Enter a valid choice!!!!\n");
            
        }
    }
}

