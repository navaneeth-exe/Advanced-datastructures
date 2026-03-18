#include <stdio.h>
#include <stdlib.h>

#define MAX_POINTS 1

struct Point {
    int x, y;
};

struct Quad {
    int x, y, width, height;
    struct Point *point;

    struct Quad *NW, *NE, *SW, *SE;
};

struct Quad* createNode(int x, int y, int w, int h) {
    struct Quad* node = (struct Quad*)malloc(sizeof(struct Quad));
    node->x = x;
    node->y = y;
    node->width = w;
    node->height = h;
    node->point = NULL;
    node->NW = node->NE = node->SW = node->SE = NULL;
    return node;
}

int contains(struct Quad* node, struct Point p) {
    return (p.x >= node->x &&
            p.x < node->x + node->width &&
            p.y >= node->y &&
            p.y < node->y + node->height);
}

void subdivide(struct Quad* node) {
    int hw = node->width / 2;
    int hh = node->height / 2;

    node->NW = createNode(node->x, node->y, hw, hh);
    node->NE = createNode(node->x + hw, node->y, hw, hh);
    node->SW = createNode(node->x, node->y + hh, hw, hh);
    node->SE = createNode(node->x + hw, node->y + hh, hw, hh);
}

void insert(struct Quad* node, struct Point p) {
    if (!contains(node, p))
        return;

    if (node->point == NULL && node->NW == NULL) {
        node->point = (struct Point*)malloc(sizeof(struct Point));
        *(node->point) = p;
        return;
    }

    if (node->NW == NULL)
        subdivide(node);

    insert(node->NW, p);
    insert(node->NE, p);
    insert(node->SW, p);
    insert(node->SE, p);
}

void display(struct Quad* node) {
    if (node == NULL)
        return;

    if (node->point != NULL)
        printf("(%d, %d)\n", node->point->x, node->point->y);

    display(node->NW);
    display(node->NE);
    display(node->SW);
    display(node->SE);
}

int main() {
    int n;

    struct Quad* root = createNode(0, 0, 100, 100);

    printf("Enter number of points: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        struct Point p;
        printf("Enter x y: ");
        scanf("%d %d", &p.x, &p.y);
        insert(root, p);
    }

    printf("\nStored Points:\n");
    display(root);

    return 0;
}
