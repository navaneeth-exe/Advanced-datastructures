#include <stdio.h>
#include <stdlib.h>

// -------- STRUCTURES --------

typedef struct {
    float x, y;
} Point;

typedef struct {
    float x, y, w, h; // center + half width/height
} Rectangle;

typedef struct QuadTree {

    Rectangle boundary;

    int capacity;
    int count;

    Point *points;

    int divided;

    struct QuadTree *nw;
    struct QuadTree *ne;
    struct QuadTree *sw;
    struct QuadTree *se;

} QuadTree;


// -------- FUNCTION: CREATE --------

QuadTree* createQuadTree(Rectangle boundary, int capacity) {
    QuadTree *qt = (QuadTree*)malloc(sizeof(QuadTree));

    qt->boundary = boundary;
    qt->capacity = capacity;
    qt->count = 0;

    qt->points = (Point*)malloc(sizeof(Point) * capacity);

    qt->divided = 0;

    qt->nw = qt->ne = qt->sw = qt->se = NULL;

    return qt;
}


// -------- FUNCTION: CONTAINS --------

int contains(Rectangle r, Point p) {
    return (p.x >= (r.x - r.w) &&
            p.x <= (r.x + r.w) &&
            p.y >= (r.y - r.h) &&
            p.y <= (r.y + r.h));
}


// -------- FUNCTION: SUBDIVIDE --------

void subdivide(QuadTree *qt) {

    float x = qt->boundary.x;
    float y = qt->boundary.y;
    float w = qt->boundary.w / 2;
    float h = qt->boundary.h / 2;

    Rectangle nw = {x - w, y - h, w, h};
    Rectangle ne = {x + w, y - h, w, h};
    Rectangle sw = {x - w, y + h, w, h};
    Rectangle se = {x + w, y + h, w, h};

    qt->nw = createQuadTree(nw, qt->capacity);
    qt->ne = createQuadTree(ne, qt->capacity);
    qt->sw = createQuadTree(sw, qt->capacity);
    qt->se = createQuadTree(se, qt->capacity);

    qt->divided = 1;
}


// -------- FUNCTION: INSERT --------

int insert(QuadTree *qt, Point p) {

    // Step 1: Check boundary
    if (!contains(qt->boundary, p))
        return 0;

    // Step 2: If space available
    if (qt->count < qt->capacity) {
        qt->points[qt->count++] = p;
        return 1;
    }

    // Step 3: If not divided, subdivide
    if (!qt->divided)
        subdivide(qt);

    // Step 4: Insert into correct child
    if (insert(qt->nw, p)) return 1;
    if (insert(qt->ne, p)) return 1;
    if (insert(qt->sw, p)) return 1;
    if (insert(qt->se, p)) return 1;

    return 0;
}


// -------- FUNCTION: PRINT --------

void printTree(QuadTree *qt) {

    // Print points in current node
    for (int i = 0; i < qt->count; i++) {
        printf("(%.1f, %.1f)\n", qt->points[i].x, qt->points[i].y);
    }

    // Recursively print children
    if (qt->divided) {
        printTree(qt->nw);
        printTree(qt->ne);
        printTree(qt->sw);
        printTree(qt->se);
    }
}


// -------- MAIN FUNCTION --------

int main() {

    // Step 1: Define boundary
    Rectangle boundary = {0, 0, 100, 100};

    // Step 2: Create QuadTree
    QuadTree *qt = createQuadTree(boundary, 4);

    // Step 3: Points to insert
    Point points[] = {
        {10, 20}, {-30, 40}, {50, -10}, {70, 80},
        {90, 90}, {-80, -70}, {25, 35}, {-60, 10}
    };

    int n = sizeof(points) / sizeof(points[0]);

    // Step 4: Insert points
    for (int i = 0; i < n; i++) {
        insert(qt, points[i]);
    }

    // Step 5: Print QuadTree
    printf("QuadTree Points:\n");
    printTree(qt);

    return 0;
}
