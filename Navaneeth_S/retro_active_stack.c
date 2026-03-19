#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// -------- OPERATION STRUCT --------
typedef struct {
    int time;
    int type;   // 1 = push, 2 = pop
    int value;
} Operation;

Operation ops[MAX];
int opCount = 0;


// -------- SORT OPERATIONS BY TIME --------
void sortOperations() {
    for (int i = 0; i < opCount - 1; i++) {
        for (int j = i + 1; j < opCount; j++) {
            if (ops[i].time > ops[j].time) {
                Operation temp = ops[i];
                ops[i] = ops[j];
                ops[j] = temp;
            }
        }
    }
}


// -------- ADD OPERATION (RETROACTIVE INSERT) --------
void addOperation(int time, int type, int value) {
    ops[opCount].time = time;
    ops[opCount].type = type;
    ops[opCount].value = value;
    opCount++;

    sortOperations(); // keep timeline correct
}


// -------- DELETE OPERATION BY TIME --------
void deleteOperation(int time) {
    for (int i = 0; i < opCount; i++) {
        if (ops[i].time == time) {
            for (int j = i; j < opCount - 1; j++) {
                ops[j] = ops[j + 1];
            }
            opCount--;
            break;
        }
    }
}


// -------- COMPUTE CURRENT STACK --------
void computeStack() {
    int stack[MAX];
    int top = -1;

    for (int i = 0; i < opCount; i++) {

        if (ops[i].type == 1) { // push
            stack[++top] = ops[i].value;
        }

        else if (ops[i].type == 2) { // pop
            if (top >= 0)
                top--;
        }
    }

    printf("\nCurrent Stack:\n");

    if (top == -1) {
        printf("Stack is empty\n");
        return;
    }

    for (int i = 0; i <= top; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}


// -------- DISPLAY OPERATIONS --------
void displayOperations() {
    printf("\nOperations Timeline:\n");

    for (int i = 0; i < opCount; i++) {
        if (ops[i].type == 1)
            printf("Time %d: push(%d)\n", ops[i].time, ops[i].value);
        else
            printf("Time %d: pop()\n", ops[i].time);
    }
}


// -------- MAIN FUNCTION --------
int main() {

    // Add operations
    addOperation(1, 1, 10); // push 10
    addOperation(2, 1, 20); // push 20
    addOperation(3, 2, 0);  // pop

    displayOperations();
    computeStack();

    // Retroactive insert
    printf("\n--- Insert push(15) at time 2 ---\n");
    addOperation(2, 1, 15);

    displayOperations();
    computeStack();

    // Delete operation
    printf("\n--- Delete operation at time 3 ---\n");
    deleteOperation(3);

    displayOperations();
    computeStack();

    return 0;
}