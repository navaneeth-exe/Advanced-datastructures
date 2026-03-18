#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Operation {
    int time;
    char type[5];
    int value;
    struct Operation* next;
} Operation;

Operation* head = NULL;

void insertOperation(int time, char* type, int value) {
    Operation* newOp = malloc(sizeof(Operation));
    newOp->time = time;
    strcpy(newOp->type, type);
    newOp->value = value;
    newOp->next = NULL;

    if (!head || time < head->time) {
        newOp->next = head;
        head = newOp;
        return;
    }

    Operation* curr = head;
    while (curr->next && curr->next->time < time)
        curr = curr->next;

    newOp->next = curr->next;
    curr->next = newOp;
}


void deleteOperation(int time) {
    if (!head) return;

    if (head->time == time) {
        Operation* tmp = head;
        head = head->next;
        free(tmp);
        return;
    }

    Operation* curr = head;
    while (curr->next && curr->next->time != time)
        curr = curr->next;

    if (curr->next && curr->next->time == time) {
        Operation* tmp = curr->next;
        curr->next = tmp->next;
        free(tmp);
    }
}

int getTop() {
    int stack[1000];
    int top = -1;
    Operation* curr = head;

    while (curr) {
        if (strcmp(curr->type, "push") == 0)
            stack[++top] = curr->value;
        else if (strcmp(curr->type, "pop") == 0)
            if (top >= 0) top--;
        curr = curr->next;
    }
    return (top >= 0) ? stack[top] : -1;
}

int main() {
    int choice, time, value;

    while (1) {
        printf("\n1. Push operation\n2. Pop operation\n3. Delete operation by time\n4. Get top\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter time: ");
                scanf("%d", &time);
                printf("Enter value to push: ");
                scanf("%d", &value);
                insertOperation(time, "push", value);
                break;
            case 2:
                printf("Enter time: ");
                scanf("%d", &time);
                insertOperation(time, "pop", 0);
                break;
            case 3:
                printf("Enter time of operation to delete: ");
                scanf("%d", &time);
                deleteOperation(time);
                break;
            case 4:
                value = getTop();
                if (value == -1)
                    printf("Stack is empty\n");
                else
                    printf("Current top = %d\n", value);
                break;
            case 5:
                exit(0);
        }
    }
    return 0;
}
