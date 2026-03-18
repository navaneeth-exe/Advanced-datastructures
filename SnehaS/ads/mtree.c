#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int hash;
    struct Node *left, *right;
};

int hash(char *str) {
    int sum = 0;
    for (int i = 0; str[i] != '\0'; i++)
        sum += str[i];
    return sum;
}

struct Node* createNode(int hash) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->hash = hash;
    node->left = node->right = NULL;
    return node;
}

struct Node* buildTree(struct Node** leaves, int n) {
    if (n == 1)
        return leaves[0];

    int newSize = (n + 1) / 2;
    struct Node* parents[newSize];

    int j = 0;
    for (int i = 0; i < n; i += 2) {
        struct Node *left = leaves[i];
        struct Node *right;

        if (i + 1 < n)
            right = leaves[i + 1];
        else
            right = left; 

        int combinedHash = left->hash + right->hash;

        struct Node* parent = createNode(combinedHash);
        parent->left = left;
        parent->right = right;

        parents[j++] = parent;
    }

    return buildTree(parents, newSize);
}

void printTree(struct Node* root) {
    if (root == NULL)
        return;

    printf("%d ", root->hash);
    printTree(root->left);
    printTree(root->right);
}

int main() {
    int n;

    printf("Enter number of data blocks: ");
    scanf("%d", &n);

    char data[n][50];
    struct Node* leaves[n];

    printf("Enter data:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", data[i]);
        leaves[i] = createNode(hash(data[i]));
    }

    struct Node* root = buildTree(leaves, n);

    printf("\nMerkle Root: %d\n", root->hash);

    printf("Preorder Traversal of Tree:\n");
    printTree(root);

    return 0;
}
