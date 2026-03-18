#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define HASH_SIZE 50

// Node structure
typedef struct Node {
    char hash[HASH_SIZE];
    struct Node *left, *right;
} Node;

char dataBlocks[MAX][50];
int dataCount = 0;

// Simple hash function (djb2 variant)
void computeHash(char *input, char *output) {
    unsigned long hash = 5381;
    int c;

    while ((c = *input++))
        hash = ((hash << 5) + hash) + c;

    sprintf(output, "%lu", hash);
}

// Create node
Node* createNode(char *hash) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->hash, hash);
    node->left = node->right = NULL;
    return node;
}

// Build Merkle Tree
Node* buildTree() {
    if (dataCount == 0) return NULL;

    Node* nodes[MAX];

    // Create leaf nodes
    for (int i = 0; i < dataCount; i++) {
        char hash[HASH_SIZE];
        computeHash(dataBlocks[i], hash);
        nodes[i] = createNode(hash);
    }

    int n = dataCount;

    // Build tree upwards
    while (n > 1) {
        int j = 0;

        for (int i = 0; i < n; i += 2) {
            if (i + 1 < n) {
                char combined[HASH_SIZE * 2];
                strcpy(combined, nodes[i]->hash);
                strcat(combined, nodes[i + 1]->hash);

                char newHash[HASH_SIZE];
                computeHash(combined, newHash);

                Node* parent = createNode(newHash);
                parent->left = nodes[i];
                parent->right = nodes[i + 1];

                nodes[j++] = parent;
            } else {
                // If odd, duplicate last node
                nodes[j++] = nodes[i];
            }
        }
        n = j;
    }

    return nodes[0];
}

// Display tree (preorder)
void display(Node* root, int level) {
    if (!root) return;

    for (int i = 0; i < level; i++)
        printf("  ");

    printf("%s\n", root->hash);

    display(root->left, level + 1);
    display(root->right, level + 1);
}

// Verify a block
void verifyBlock(Node* root, char *data) {
    char hash[HASH_SIZE];
    computeHash(data, hash);

    printf("Computed Hash: %s\n", hash);
    printf("Merkle Root: %s\n", root ? root->hash : "NULL");

    printf("Note: Full proof path not implemented (basic verification only).\n");
}

// Print data blocks
void printData() {
    printf("Data Blocks:\n");
    for (int i = 0; i < dataCount; i++)
        printf("%d: %s\n", i, dataBlocks[i]);
}

// Main
int main() {
    int choice;
    char input[50];
    Node* root = NULL;

    while (1) {
        printf("\n--- Merkle Tree Menu ---\n");
        printf("1. Add Data Block\n");
        printf("2. Build Tree\n");
        printf("3. Display Tree\n");
        printf("4. Show Root Hash\n");
        printf("5. Verify Data Block\n");
        printf("6. Show Data Blocks\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (dataCount >= MAX) {
                    printf("Max limit reached!\n");
                    break;
                }
                printf("Enter data: ");
                scanf("%s", input);
                strcpy(dataBlocks[dataCount++], input);
                break;

            case 2:
                root = buildTree();
                printf("Merkle Tree built.\n");
                break;

            case 3:
                if (!root)
                    printf("Build tree first!\n");
                else
                    display(root, 0);
                break;

            case 4:
                if (root)
                    printf("Root Hash: %s\n", root->hash);
                else
                    printf("Tree not built!\n");
                break;

            case 5:
                if (!root) {
                    printf("Build tree first!\n");
                    break;
                }
                printf("Enter data to verify: ");
                scanf("%s", input);
                verifyBlock(root, input);
                break;

            case 6:
                printData();
                break;

            case 7:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
}