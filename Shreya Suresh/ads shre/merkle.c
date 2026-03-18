#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned long simpleHash(const char *data) {
    unsigned long hash = 0;
    while (*data) {
        hash = hash * 5 + *data;
        data++;
    }
    return hash;
}

typedef struct Node {
    unsigned long hash;
    struct Node *left, *right;
} Node;

Node* newLeaf(const char *data) {
    Node *n = malloc(sizeof(Node));
    n->hash = simpleHash(data);
    n->left = n->right = NULL;
    return n;
}

Node* mergeNodes(Node *left, Node *right) {
    Node *n = malloc(sizeof(Node));
    n->hash = left->hash ^ right->hash; 
    n->left = left;
    n->right = right;
    return n;
}

Node* buildMerkleTree(Node **nodes, int count) {
    if (count == 1)
        return nodes[0];

    int newCount = (count + 1) / 2; 
    Node **newLevel = malloc(newCount * sizeof(Node*));

    for (int i = 0, j = 0; i < count; i += 2, j++) {
        if (i + 1 < count)
            newLevel[j] = mergeNodes(nodes[i], nodes[i+1]);
        else
            newLevel[j] = nodes[i];
    }

    Node *root = buildMerkleTree(newLevel, newCount);
    free(newLevel);
    return root;
}

void printRoot(Node *root) {
    printf("Merkle Root: %lu\n", root->hash);
}

int main() {
    int n;
    printf("Enter number of data blocks: ");
    scanf("%d", &n);

    char data[256];
    Node **leaves = malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++) {
        printf("Enter data block %d: ", i+1);
        scanf("%s", data);
        leaves[i] = newLeaf(data);
    }

    Node *root = buildMerkleTree(leaves, n);
    printRoot(root);

    free(leaves);
    return 0;
}
