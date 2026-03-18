#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Operation types
#define PUSH 1
#define POP  2

// Operation structure
typedef struct {
    int time;
    int type;
    int value;
} Operation;

Operation ops[MAX];
int opCount = 0;

// Swap for sorting
void swap(Operation *a, Operation *b) {
    Operation temp = *a;
    *a = *b;
    *b = temp;
}

// Sort operations by time
void sortOps() {
    for (int i = 0; i < opCount - 1; i++) {
        for (int j = 0; j < opCount - i - 1; j++) {
            if (ops[j].time > ops[j + 1].time) {
                swap(&ops[j], &ops[j + 1]);
            }
        }
    }
}

// Rebuild stack
void rebuildStack(int stack[], int *top) {
    *top = -1;
    sortOps();

    for (int i = 0; i < opCount; i++) {
        if (ops[i].type == PUSH) {
            stack[++(*top)] = ops[i].value;
        } else if (ops[i].type == POP) {
            if (*top >= 0)
                (*top)--;
        }
    }
}

// Insert operation
void insertOperation(int time, int type, int value) {
    if (opCount >= MAX) {
        printf("Operation list full!\n");
        return;
    }
    ops[opCount].time = time;
    ops[opCount].type = type;
    ops[opCount].value = value;
    opCount++;
}

// Delete operation at time
void deleteOperation(int time) {
    int found = 0;
    for (int i = 0; i < opCount; i++) {
        if (ops[i].time == time) {
            for (int j = i; j < opCount - 1; j++)
                ops[j] = ops[j + 1];
            opCount--;
            found = 1;
            break;
        }
    }
    if (!found)
        printf("No operation at given time!\n");
}

// Print stack
void printStack(int stack[], int top) {
    if (top == -1) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack (bottom -> top): ");
    for (int i = 0; i <= top; i++)
        printf("%d ", stack[i]);
    printf("\n");
}

// Print operations
void printOperations() {
    sortOps();
    printf("Operations (time ordered):\n");
    for (int i = 0; i < opCount; i++) {
        if (ops[i].type == PUSH)
            printf("Time %d: PUSH %d\n", ops[i].time, ops[i].value);
        else
            printf("Time %d: POP\n", ops[i].time);
    }
}

// Main
int main() {
    int choice, time, value;
    int stack[MAX], top;

    while (1) {
        printf("\n--- Retroactive Stack ---\n");
        printf("1. Add PUSH operation\n");
        printf("2. Add POP operation\n");
        printf("3. Delete operation by time\n");
        printf("4. Show current stack\n");
        printf("5. Show all operations\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter time and value: ");
                scanf("%d %d", &time, &value);
                insertOperation(time, PUSH, value);
                break;

            case 2:
                printf("Enter time: ");
                scanf("%d", &time);
                insertOperation(time, POP, 0);
                break;

            case 3:
                printf("Enter time to delete operation: ");
                scanf("%d", &time);
                deleteOperation(time);
                break;

            case 4:
                rebuildStack(stack, &top);
                printStack(stack, top);
                break;

            case 5:
                printOperations();
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
}