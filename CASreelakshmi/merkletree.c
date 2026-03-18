#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char data[MAX][100];
char tree[2 * MAX][100];
int n = 0;

// Simple hash (demo only)
void simpleHash(char *input, char *output) {
    int hash = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        hash = (hash * 31 + input[i]) % 100000;
    }
    sprintf(output, "%d", hash);
}

// Build Merkle Tree
int buildMerkleTree() {
    if (n == 0) {
        printf("No transactions available!\n");
        return -1;
    }

    int size = n;

    // Step 1: Leaf hashing
    for (int i = 0; i < n; i++) {
        simpleHash(data[i], tree[i]);
    }

    int levelStart = 0;
    int levelSize = size;

    // Build upward
    while (levelSize > 1) {
        int newSize = 0;

        for (int i = 0; i < levelSize; i += 2) {
            char combined[200];

            if (i + 1 < levelSize) {
                strcpy(combined, tree[levelStart + i]);
                strcat(combined, tree[levelStart + i + 1]);
            } else {
                strcpy(combined, tree[levelStart + i]);
                strcat(combined, tree[levelStart + i]);
            }

            simpleHash(combined, tree[levelStart + levelSize + newSize]);
            newSize++;
        }

        levelStart += levelSize;
        levelSize = newSize;
    }

    printf("Merkle Root: %s\n", tree[levelStart]);
    return levelStart;
}

// Display tree levels
void displayTree() {
    if (n == 0) {
        printf("Tree is empty!\n");
        return;
    }

    int size = n;
    int index = 0;

    printf("\n--- Merkle Tree Levels ---\n");

    while (size > 0) {
        printf("Level: ");
        for (int i = 0; i < size; i++) {
            printf("%s ", tree[index + i]);
        }
        printf("\n");

        index += size;
        size = (size + 1) / 2;
    }
}

// Add transaction
void addTransaction() {
    if (n >= MAX) {
        printf("Limit reached!\n");
        return;
    }

    printf("Enter transaction: ");
    getchar();
    fgets(data[n], 100, stdin);
    data[n][strcspn(data[n], "\n")] = 0;

    n++;
}

// Verify transaction (simple check)
void verifyTransaction() {
    char input[100], hash[100];
    int found = 0;

    printf("Enter transaction to verify: ");
    getchar();
    fgets(input, 100, stdin);
    input[strcspn(input, "\n")] = 0;

    simpleHash(input, hash);

    for (int i = 0; i < n; i++) {
        char temp[100];
        simpleHash(data[i], temp);
        if (strcmp(temp, hash) == 0) {
            found = 1;
            break;
        }
    }

    if (found)
        printf("Transaction EXISTS in tree\n");
    else
        printf("Transaction NOT FOUND\n");
}

// Menu
int main() {
    int choice;

    while (1) {
        printf("\n--- Merkle Tree Menu ---\n");
        printf("1. Add Transaction\n");
        printf("2. Build Merkle Tree\n");
        printf("3. Display Tree Levels\n");
        printf("4. Verify Transaction\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTransaction();
                break;

            case 2:
                buildMerkleTree();
                break;

            case 3:
                displayTree();
                break;

            case 4:
                verifyTransaction();
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
}
