#include<stdio.h>
#include<string.h>

#define size 20

int bloom[size];

int hash1(char *str){
    int hash = 0;
    for(int i = 0; str[i] != 0; i++){
        hash = (hash + str[i]) % size;
    }
    return hash;
}

int hash2(char *str){
    int hash = 0;
    for(int i = 0; str[i] != 0; i++){
        hash = (hash * 31 + str[i]) % size;
    }
    return hash;
}

void insert(char *str){
    int h1 = hash1(str);
    int h2 = hash2(str);
    bloom[h1] = 1;
    bloom[h2] = 1;
    printf("inserted : %s\n", str);
}

void search(char *str){
    int h1 = hash1(str);
    int h2 = hash2(str);

    if(bloom[h1] && bloom[h2])
        printf("%s is possibly present\n", str);
    else
        printf("%s is definitely not present\n", str);
}

void display(){
    for(int i = 0; i < size; i++){
        printf("%d ", bloom[i]);
    }
    printf("\n");
}

int main(){
    int choice;
    char word[50];

    while(1){
        printf("\n1.insert\n2.search\n3.display\n4.exit\n");
        printf("enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("enter the word to insert: ");
                scanf("%s", word);
                insert(word);
                break;

            case 2:
                printf("enter the word to search: ");
                scanf("%s", word);
                search(word);
                break;

            case 3:
                display();
                break;

            case 4:
                return 0;

            default:
                printf("invalid choice\n");
        }
    }
}
