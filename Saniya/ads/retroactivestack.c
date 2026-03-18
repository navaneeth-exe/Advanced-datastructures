#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Operation structure
typedef struct {
    int time;
    char type[5]; // "push" or "pop"
    int value;
} Operation;

Operation ops[MAX];
int opCount = 0;

// Compare for sorting by time
int compare(const void *a, const void *b) {
    return ((Operation*)a)->time - ((Operation*)b)->time;
}

// Rebuild stack
void buildStack() {
    int stack[MAX];
    int top = -1;

    // Sort operations by time
    qsort(ops, opCount, sizeof(Operation), compare);

    for (int i = 0; i < opCount; i++) {
        if (strcmp(ops[i].type, "push") == 0) {
            stack[++top] = ops[i].value;
        } else if (strcmp(ops[i].type, "pop") == 0) {
            if (top >= 0) top--;
        }
    }

    // Display current stack
    printf("Current Stack: ");
    if (top == -1) {
        printf("Empty");
    } else {
        for (int i = 0; i <= top; i++) {
            printf("%d ", stack[i]);
        }
    }
    printf("\n");
}

// Add operation
void addOperation(int time, char *type, int value) {
    ops[opCount].time = time;
    strcpy(ops[opCount].type, type);
    ops[opCount].value = value;
    opCount++;

    buildStack();
}

// Delete operation at time
void deleteOperation(int time) {
    int found = 0;

    for (int i = 0; i < opCount; i++) {
        if (ops[i].time == time) {
            found = 1;
            for (int j = i; j < opCount - 1; j++) {
                ops[j] = ops[j + 1];
            }
            opCount--;
            break;
        }
    }

    if (!found) {
        printf("No operation found at time %d\n", time);
    }

    buildStack();
}

// Display all operations
void displayOperations() {
    printf("\nOperations Timeline:\n");
    for (int i = 0; i < opCount; i++) {
        printf("Time %d: %s", ops[i].time, ops[i].type);
        if (strcmp(ops[i].type, "push") == 0)
            printf(" %d", ops[i].value);
        printf("\n");
    }
}

// Main
int main() {
    int choice, time, value;
    char type[5];

    while (1) {
        printf("\n--- Retroactive Stack ---\n");
        printf("1. Add Operation\n");
        printf("2. Delete Operation\n");
        printf("3. Show Operations\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter time: ");
                scanf("%d", &time);

                printf("Enter operation (push/pop): ");
                scanf("%s", type);

                if (strcmp(type, "push") == 0) {
                    printf("Enter value: ");
                    scanf("%d", &value);
                } else {
                    value = 0;
                }

                addOperation(time, type, value);
                break;

            case 2:
                printf("Enter time to delete operation: ");
                scanf("%d", &time);
                deleteOperation(time);
                break;

            case 3:
                displayOperations();
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
}
