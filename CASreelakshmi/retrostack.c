#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int stack[MAX];
int top = -1;

// Push operation
void push(int value) {
    if (top >= MAX - 1) {
        printf("⚠️ Stack Overflow!\n");
        return;
    }
    stack[++top] = value;
    printf("✅ Pushed %d onto the stack.\n", value);
}

// Pop operation
void pop() {
    if (top < 0) {
        printf("⚠️ Stack Underflow!\n");
        return;
    }
    printf("🗑️ Popped %d from the stack.\n", stack[top--]);
}

// Peek operation
void peek() {
    if (top < 0) {
        printf("⚠️ Stack is empty.\n");
        return;
    }
    printf("👀 Top of stack: %d\n", stack[top]);
}

// Display stack
void display() {
    if (top < 0) {
        printf("Stack is empty.\n");
        return;
    }
    printf("📦 Stack (top -> bottom): ");
    for (int i = top; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

// Retro-style interactive menu
int main() {
    int choice, value;

    while (1) {
        printf("\n🎮 Retro Stack Menu 🎮\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display Stack\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(value);
                break;

            case 2:
                pop();
                break;

            case 3:
                peek();
                break;

            case 4:
                display();
                break;

            case 5:
                printf("👋 Exiting Retro Stack. Bye!\n");
                exit(0);

            default:
                printf("❌ Invalid choice!\n");
        }
    }
}
