#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Operation {
    int time;
    char type[5]; 
    int value;
};

struct Operation ops[MAX];
int opCount = 0;
void sortOps() {
    for (int i = 0; i < opCount - 1; i++) {
        for (int j = i + 1; j < opCount; j++) {
            if (ops[i].time > ops[j].time) {
                struct Operation temp = ops[i];
                ops[i] = ops[j];
                ops[j] = temp;
            }
        }
    }
}

void rebuildStack() {
    int stack[MAX];
    int top = -1;

    sortOps();

    printf("\nCurrent Stack after applying operations:\n");

    for (int i = 0; i < opCount; i++) {
        if (strcmp(ops[i].type, "push") == 0) {
            stack[++top] = ops[i].value;
        } else if (strcmp(ops[i].type, "pop") == 0) {
            if (top >= 0)
                top--;
        }
    }

    if (top == -1) {
        printf("Stack is empty\n");
        return;
    }

    for (int i = top; i >= 0; i--)
        printf("%d ", stack[i]);
    printf("\n");
}

void addOperation() {
    printf("Enter time: ");
    scanf("%d", &ops[opCount].time);

    printf("Enter operation (push/pop): ");
    scanf("%s", ops[opCount].type);

    if (strcmp(ops[opCount].type, "push") == 0) {
        printf("Enter value: ");
        scanf("%d", &ops[opCount].value);
    }

    opCount++;
}

void deleteOperation() {
    int t;
    printf("Enter time to delete: ");
    scanf("%d", &t);

    for (int i = 0; i < opCount; i++) {
        if (ops[i].time == t) {
            for (int j = i; j < opCount - 1; j++)
                ops[j] = ops[j + 1];
            opCount--;
            printf("Operation deleted\n");
            return;
        }
    }
    printf("Not found\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n1.Add Operation\n2.Delete Operation\n3.Show Stack\n4.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addOperation();
                break;

            case 2:
                deleteOperation();
                break;

            case 3:
                rebuildStack();
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}
