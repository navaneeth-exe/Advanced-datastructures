#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 4

// Point structure
typedef struct {
    int x, y;
} Point;

// Rectangle boundary
typedef struct {
    int x, y;      // center
    int w, h;      // half width & height
} Boundary;

// Quadtree node
typedef struct Quadtree {
    Boundary boundary;
    Point points[CAPACITY];
    int count;
    int divided;

    struct Quadtree *nw, *ne, *sw, *se;
} Quadtree;

// Create Quadtree node
Quadtree* createQuadtree(Boundary boundary) {
    Quadtree* qt = (Quadtree*)malloc(sizeof(Quadtree));
    qt->boundary = boundary;
    qt->count = 0;
    qt->divided = 0;
    qt->nw = qt->ne = qt->sw = qt->se = NULL;
    return qt;
}

// Check if point inside boundary
int contains(Boundary b, Point p) {
    return (p.x >= (b.x - b.w) &&
            p.x <= (b.x + b.w) &&
            p.y >= (b.y - b.h) &&
            p.y <= (b.y + b.h));
}

// Subdivide
void subdivide(Quadtree* qt) {
    int x = qt->boundary.x;
    int y = qt->boundary.y;
    int w = qt->boundary.w / 2;
    int h = qt->boundary.h / 2;

    Boundary nw = {x - w, y - h, w, h};
    Boundary ne = {x + w, y - h, w, h};
    Boundary sw = {x - w, y + h, w, h};
    Boundary se = {x + w, y + h, w, h};

    qt->nw = createQuadtree(nw);
    qt->ne = createQuadtree(ne);
    qt->sw = createQuadtree(sw);
    qt->se = createQuadtree(se);

    qt->divided = 1;
}

// Insert point
int insert(Quadtree* qt, Point p) {
    if (!contains(qt->boundary, p))
        return 0;

    if (qt->count < CAPACITY) {
        qt->points[qt->count++] = p;
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

// Check rectangle overlap
int intersects(Boundary a, Boundary b) {
    return !(b.x - b.w > a.x + a.w ||
             b.x + b.w < a.x - a.w ||
             b.y - b.h > a.y + a.h ||
             b.y + b.h < a.y - a.h);
}

// Range query
void query(Quadtree* qt, Boundary range) {
    if (!intersects(qt->boundary, range))
        return;

    for (int i = 0; i < qt->count; i++) {
        if (contains(range, qt->points[i])) {
            printf("(%d, %d)\n", qt->points[i].x, qt->points[i].y);
        }
    }

    if (qt->divided) {
        query(qt->nw, range);
        query(qt->ne, range);
        query(qt->sw, range);
        query(qt->se, range);
    }
}

// Display all points
void display(Quadtree* qt) {
    for (int i = 0; i < qt->count; i++) {
        printf("(%d, %d)\n", qt->points[i].x, qt->points[i].y);
    }

    if (qt->divided) {
        display(qt->nw);
        display(qt->ne);
        display(qt->sw);
        display(qt->se);
    }
}

// Main
int main() {
    Boundary boundary = {0, 0, 50, 50};
    Quadtree* qt = createQuadtree(boundary);

    int choice, x, y;

    while (1) {
        printf("\n--- Quadtree Menu ---\n");
        printf("1. Insert Point\n2. Display Points\n3. Range Query\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter x y: ");
                scanf("%d %d", &x, &y);
                insert(qt, (Point){x, y});
                break;

            case 2:
                printf("All Points:\n");
                display(qt);
                break;

            case 3: {
                Boundary range;
                printf("Enter range center (x y): ");
                scanf("%d %d", &range.x, &range.y);
                printf("Enter half width & height: ");
                scanf("%d %d", &range.w, &range.h);

                printf("Points in range:\n");
                query(qt, range);
                break;
            }

            case 4:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
}
