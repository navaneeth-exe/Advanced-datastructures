#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int hash_node(unsigned int a, unsigned int b) {
    return (a * 31 + b) ^ 0xDEADBEEF;
}

struct MerkleTree {
    unsigned int *nodes;
    int leaf_count;
    int total_nodes;
};

struct MerkleTree* build_tree(unsigned int *data, int n) {
    struct MerkleTree* tree = (struct MerkleTree*)malloc(sizeof(struct MerkleTree));
    tree->leaf_count = n;
    tree->total_nodes = 2 * n - 1;
    tree->nodes = (unsigned int*)malloc(sizeof(unsigned int) * tree->total_nodes);

    for (int i = 0; i < n; i++) {
        tree->nodes[n - 1 + i] = data[i];
    }

    for (int i = n - 2; i >= 0; i--) {
        tree->nodes[i] = hash_node(tree->nodes[2 * i + 1], tree->nodes[2 * i + 2]);
    }

    return tree;
}

unsigned int get_root(struct MerkleTree* tree) {
    return tree->nodes[0];
}

int verify(struct MerkleTree* tree, unsigned int val, int idx) {
    int pos = tree->leaf_count - 1 + idx;
    return tree->nodes[pos] == val;
}

void print_tree(struct MerkleTree* tree) {
    for (int i = 0; i < tree->total_nodes; i++) {
        printf("%08X ", tree->nodes[i]);
    }
    printf("\nRoot: %08X\n", tree->nodes[0]);
}

int main() {
    unsigned int dataset[] = {0x1111, 0x2222, 0x3333, 0x4444};
    int n = 4;

    struct MerkleTree* m_tree = build_tree(dataset, n);
    print_tree(m_tree);

    if (verify(m_tree, 0x3333, 2)) {
        printf("Valid\n");
    }

    free(m_tree->nodes);
    free(m_tree);
    return 0;
}
