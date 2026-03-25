#include <stdio.h>
#include <string.h>

#define SIZE 20
int bloom[SIZE] = {0};

int h1(char *word) {
    return strlen(word) % SIZE;
}

int h2(char *word) {
    int sum = 0;
    for (int i = 0; word[i] != '\0'; i++) sum += word[i];
    return sum % SIZE;
}

int main() {
    int choice;
    char word[30];

    while (1) {
        printf("\n1.Add 2.Check 3.Show 4.Exit: ");
        scanf("%d", &choice);

        if (choice == 4) break;

        if (choice == 3) {
            for (int i = 0; i < SIZE; i++)  

             printf("%d ", bloom[i]);
            printf("\n");
            continue;
        }

        printf("Enter word: ");
        scanf("%s", word);

        if (choice == 1) {
            bloom[h1(word)] = 1;
            bloom[h2(word)] = 1;
            printf("Added.\n");
        } 
        
        if (choice == 2) {
            if (bloom[h1(word)] && bloom[h2(word)]) 
                printf("Result: Maybe yes\n");
            else 
                printf("Result: Definitely no\n");
        }
    }
    return 0;
}
