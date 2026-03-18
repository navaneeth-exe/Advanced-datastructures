#include <stdio.h>
#define MAX 100
typedef struct {
    int type; 
    int value;
} Operation;

Operation ops[MAX];
int opCount = 0;
void addOperation(int type, int value) {
    ops[opCount].type = type;
    ops[opCount].value = value;
    opCount++;
}
void removeOperation(int index) {
    for (int i = index; i < opCount - 1; i++)
        ops[i] = ops[i + 1];
    opCount--;
}
void computeState() {
    int arr[100], size = 0;

    for (int i = 0; i < opCount; i++) {
        if (ops[i].type == 1) {
            arr[size++] = ops[i].value;
        } else if (ops[i].type == 2) {
            for (int j = 0; j < size; j++) {
                if (arr[j] == ops[i].value) {
                    for (int k = j; k < size - 1; k++)
                        arr[k] = arr[k + 1];
                    size--;
                    break;
                }
            }
        }
    }

    printf("Current State: ");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    addOperation(1, 5);   // Insert 5
    addOperation(1, 10);  // Insert 10
    addOperation(2, 5);   // Delete 5
    computeState();
    removeOperation(0);
    computeState();
    return 0;
}
