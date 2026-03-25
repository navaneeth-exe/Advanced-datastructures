#include <stdio.h>
#include <stdlib.h>

struct QuadNode {
    int x, y;
    struct QuadNode *NW;
    struct QuadNode *NE;
    struct QuadNode *SW;
    struct QuadNode *SE;
};

// Create a new node
struct QuadNode* createNode(int x, int y) {
    struct QuadNode* node = (struct QuadNode*)malloc(sizeof(struct QuadNode));
    node->x = x;
    node->y = y;
    node->NW = node->NE = node->SW = node->SE = NULL;
    return node;
}

// Insert a point into the quadtree
struct QuadNode* insert(struct QuadNode* root, int x, int y, int minX, int minY, int maxX, int maxY) {
    if (!root) {
        return createNode(x, y);
    }

    int midX = (minX + maxX) / 2;
    int midY = (minY + maxY) / 2;

    if (x <= midX && y <= midY)
        root->SW = insert(root->SW, x, y, minX, minY, midX, midY);
    else if (x <= midX && y > midY)
        root->NW = insert(root->NW, x, y, minX, midY + 1, midX, maxY);
    else if (x > midX && y <= midY)
        root->SE = insert(root->SE, x, y, midX + 1, minY, maxX, midY);
    else
        root->NE = insert(root->NE, x, y, midX + 1, midY + 1, maxX, maxY);

    return root;
}

// Search for a point
int search(struct QuadNode* root, int x, int y, int minX, int minY, int maxX, int maxY) {
    if (!root) return 0;
    if (root->x == x && root->y == y) return 1;

    int midX = (minX + maxX) / 2;
    int midY = (minY + maxY) / 2;

    if (x <= midX && y <= midY)
        return search(root->SW, x, y, minX, minY, midX, midY);
    else if (x <= midX && y > midY)
        return search(root->NW, x, y, minX, midY + 1, midX, maxY);
    else if (x > midX && y <= midY)
        return search(root->SE, x, y, midX + 1, minY, maxX, midY);
    else
        return search(root->NE, x, y, midX + 1, midY + 1, maxX, maxY);
}

// Display quadtree (preorder)
void display(struct QuadNode* root, int level) {
    if (!root) return;
    for (int i = 0; i < level; i++) printf("  ");
    printf("(%d,%d)\n", root->x, root->y);
    display(root->NW, level + 1);
    display(root->NE, level + 1);
    display(root->SW, level + 1);
    display(root->SE, level + 1);
}

// Interactive menu
int main() {
    struct QuadNode* root = NULL;
    int choice, x, y;
    int minX = 0, minY = 0, maxX = 100, maxY = 100; // Space boundary

    while (1) {
        printf("\n--- Quad Tree Menu ---\n");
        printf("1. Insert Point\n");
        printf("2. Search Point\n");
        printf("3. Display Quad Tree\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter x y coordinates: ");
                scanf("%d %d", &x, &y);
                root = insert(root, x, y, minX, minY, maxX, maxY);
                printf("Point (%d,%d) inserted.\n", x, y);
                break;

            case 2:
                printf("Enter x y coordinates to search: ");
                scanf("%d %d", &x, &y);
                if (search(root, x, y, minX, minY, maxX, maxY))
                    printf("Point (%d,%d) FOUND.\n", x, y);
                else
                    printf("Point (%d,%d) NOT FOUND.\n", x, y);
                break;

            case 3:
                printf("Quad Tree Structure:\n");
                display(root, 0);
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
}
