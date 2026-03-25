#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 1

// Point
typedef struct {
    int x, y;
} Point;

// Rectangle boundary
typedef struct {
    int x, y, w, h;
} Boundary;

// Quadtree node
typedef struct Quadtree {
    Boundary boundary;
    Point *point;
    int divided;

    struct Quadtree *nw, *ne, *sw, *se;
} Quadtree;

// Create node
Quadtree* createNode(int x, int y, int w, int h) {
    Quadtree* qt = (Quadtree*)malloc(sizeof(Quadtree));
    qt->boundary.x = x;
    qt->boundary.y = y;
    qt->boundary.w = w;
    qt->boundary.h = h;
    qt->point = NULL;
    qt->divided = 0;
    qt->nw = qt->ne = qt->sw = qt->se = NULL;
    return qt;
}

// Check if point inside boundary
int contains(Boundary b, Point p) {
    return (p.x >= b.x - b.w &&
            p.x <= b.x + b.w &&
            p.y >= b.y - b.h &&
            p.y <= b.y + b.h);
}

// Subdivide
void subdivide(Quadtree* qt) {
    int x = qt->boundary.x;
    int y = qt->boundary.y;
    int w = qt->boundary.w / 2;
    int h = qt->boundary.h / 2;

    qt->nw = createNode(x - w, y - h, w, h);
    qt->ne = createNode(x + w, y - h, w, h);
    qt->sw = createNode(x - w, y + h, w, h);
    qt->se = createNode(x + w, y + h, w, h);

    qt->divided = 1;
}

// Insert point
int insert(Quadtree* qt, Point p) {
    if (!contains(qt->boundary, p))
        return 0;

    if (qt->point == NULL && !qt->divided) {
        qt->point = (Point*)malloc(sizeof(Point));
        *(qt->point) = p;
        return 1;
    }

    if (!qt->divided)
        subdivide(qt);

    if (insert(qt->nw, p)) return 1;
    if (insert(qt->ne, p)) return 1;
    if (insert(qt->sw, p)) return 1;
    if (insert(qt->se, p)) return 1;

    return 0;
}

// Search point
int search(Quadtree* qt, Point p) {
    if (!qt || !contains(qt->boundary, p))
        return 0;

    if (qt->point && qt->point->x == p.x && qt->point->y == p.y)
        return 1;

    if (qt->divided) {
        return search(qt->nw, p) ||
               search(qt->ne, p) ||
               search(qt->sw, p) ||
               search(qt->se, p);
    }

    return 0;
}

// Check rectangle intersection
int intersects(Boundary a, Boundary b) {
    return !(b.x - b.w > a.x + a.w ||
             b.x + b.w < a.x - a.w ||
             b.y - b.h > a.y + a.h ||
             b.y + b.h < a.y - a.h);
}

// Range query
void rangeQuery(Quadtree* qt, Boundary range) {
    if (!qt || !intersects(qt->boundary, range))
        return;

    if (qt->point && contains(range, *(qt->point))) {
        printf("(%d, %d)\n", qt->point->x, qt->point->y);
    }

    if (qt->divided) {
        rangeQuery(qt->nw, range);
        rangeQuery(qt->ne, range);
        rangeQuery(qt->sw, range);
        rangeQuery(qt->se, range);
    }
}

// Display tree
void display(Quadtree* qt, int level) {
    if (!qt) return;

    for (int i = 0; i < level; i++)
        printf("  ");

    printf("Node [%d,%d]\n", qt->boundary.x, qt->boundary.y);

    if (qt->point) {
        for (int i = 0; i < level + 1; i++)
            printf("  ");
        printf("Point (%d,%d)\n", qt->point->x, qt->point->y);
    }

    if (qt->divided) {
        display(qt->nw, level + 1);
        display(qt->ne, level + 1);
        display(qt->sw, level + 1);
        display(qt->se, level + 1);
    }
}

// Main
int main() {
    int choice, x, y, w, h;
    Quadtree* root = createNode(0, 0, 100, 100);
    Point p;
    Boundary range;

    while (1) {
        printf("\n--- Quadtree Menu ---\n");
        printf("1. Insert Point\n");
        printf("2. Search Point\n");
        printf("3. Range Query\n");
        printf("4. Display Tree\n");
        printf("5. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter x y: ");
                scanf("%d %d", &p.x, &p.y);
                if (insert(root, p))
                    printf("Inserted\n");
                else
                    printf("Out of bounds\n");
                break;

            case 2:
                printf("Enter x y: ");
                scanf("%d %d", &p.x, &p.y);
                if (search(root, p))
                    printf("Found\n");
                else
                    printf("Not Found\n");
                break;

            case 3:
                printf("Enter center(x y) and half width height: ");
                scanf("%d %d %d %d", &range.x, &range.y, &range.w, &range.h);
                printf("Points in range:\n");
                rangeQuery(root, range);
                break;

            case 4:
                display(root, 0);
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid!\n");
        }
    }
}