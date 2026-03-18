#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    int isLeaf;
    struct Node *topLeft, *topRight, *bottomLeft, *bottomRight;
} Node;


Node* createLeaf(int val) {
    Node* n = malloc(sizeof(Node));
    n->val = val;
    n->isLeaf = 1;
    n->topLeft = n->topRight = n->bottomLeft = n->bottomRight = NULL;
    return n;
}

Node* createNode() {
    Node* n = malloc(sizeof(Node));
    n->isLeaf = 0;
    n->topLeft = n->topRight = n->bottomLeft = n->bottomRight = NULL;
    return n;
}


int isUniform(int grid[][4], int x, int y, int size) {
    int val = grid[x][y];
    for(int i = x; i < x + size; i++)
        for(int j = y; j < y + size; j++)
            if(grid[i][j] != val)
                return 0;
    return 1;
}

Node* buildQuadTree(int grid[][4], int x, int y, int size) {
    if(isUniform(grid, x, y, size))
        return createLeaf(grid[x][y]);

    Node* n = createNode();
    int newSize = size / 2;
    n->topLeft = buildQuadTree(grid, x, y, newSize);
    n->topRight = buildQuadTree(grid, x, y + newSize, newSize);
    n->bottomLeft = buildQuadTree(grid, x + newSize, y, newSize);
    n->bottomRight = buildQuadTree(grid, x + newSize, y + newSize, newSize);
    return n;
}


void printQuadTree(Node* n) {
    if(!n) return;
    if(n->isLeaf)
        printf("%d ", n->val);
    else {
        printf("X ");
        printQuadTree(n->topLeft);
        printQuadTree(n->topRight);
        printQuadTree(n->bottomLeft);
        printQuadTree(n->bottomRight);
    }
}

int main() {
    int grid[4][4] = {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 1, 1},
        {0, 0, 1, 1}
    };

    Node* root = buildQuadTree(grid, 0, 0, 4);
    printf("Quad Tree Preorder: ");
    printQuadTree(root);
    printf("\n");
    return 0;
}
