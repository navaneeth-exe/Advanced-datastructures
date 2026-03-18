#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure
typedef struct Node {
    char hash[100];
    struct Node *left, *right;
} Node;

// Simple hash function (for demo)
void simpleHash(char *input, char *output) {
    int sum = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        sum += input[i];
    }
    sprintf(output, "%d", sum);
}

// Create node
Node* createNode(char *data) {
    Node *node = (Node*)malloc(sizeof(Node));
    strcpy(node->hash, data);
    node->left = node->right = NULL;
    return node;
}

// Build Merkle Tree
Node* buildMerkleTree(char data[][50], int n) {
    Node* nodes[100];
    int i;

    // Create leaf nodes
    for (i = 0; i < n; i++) {
        char hash[100];
        simpleHash(data[i], hash);
        nodes[i] = createNode(hash);
    }

    int count = n;

    // Build tree upward
    while (count > 1) {
        int j = 0;

        for (i = 0; i < count; i += 2) {
            if (i + 1 < count) {
                char combined[200], hash[100];

                strcpy(combined, nodes[i]->hash);
                strcat(combined, nodes[i + 1]->hash);

                simpleHash(combined, hash);

                Node *parent = createNode(hash);
                parent->left = nodes[i];
                parent->right = nodes[i + 1];

                nodes[j++] = parent;
            } else {
                // If odd, carry forward
                nodes[j++] = nodes[i];
            }
        }
        count = j;
    }

    return nodes[0]; // root
}

// Print tree (preorder)
void printTree(Node *root) {
    if (root == NULL) return;

    printf("Hash: %s\n", root->hash);
    printTree(root->left);
    printTree(root->right);
}

// Free tree
void freeTree(Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Main
int main() {
    int n;
    char data[100][50];

    printf("Enter number of data blocks: ");
    scanf("%d", &n);

    printf("Enter data:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", data[i]);
    }

    Node *root = buildMerkleTree(data, n);

    printf("\n--- Merkle Tree (Preorder) ---\n");
    printTree(root);

    printf("\nRoot Hash: %s\n", root->hash);

    freeTree(root);
    return 0;
}
