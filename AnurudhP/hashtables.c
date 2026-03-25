#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};
struct Node* table[15]; 
int  Index(int key) {
    return key % 15;
}
void insert() {
    int val;
    printf("Enter number to add: ");
    scanf("%d", &val);

    int i = Index(val);
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = table[i];
    table[i] = newNode;
}
void delete() {
    int val;
    printf("Enter number to delete: ");
    scanf("%d", &val);

    int i = Index(val);
    struct Node *temp = table[i], *prev = NULL;

    while (temp != NULL) {
        if (temp->data == val) {
            if (prev == NULL) table[i] = temp->next; 
            else prev->next = temp->next;             
            free(temp);
            printf("Deleted!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Not found.\n");
}
void display() {
    for (int i = 0; i < 15; i++) {
        printf("%d: ", i);
        struct Node* t = table[i];
        while (t) {
            printf("%d -> ", t->data);
            t = t->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int choice;
    for (int i = 0; i < 15; i++) table[i] = NULL;

    while (1) {
        printf("\n1.Add 2.Del 3.Show 4.Exit: ");
        scanf("%d", &choice);
        if (choice == 1) insert();
        else if (choice == 2) delete();
        else if (choice == 3) display();
        else break;
    }
    return 0;
}