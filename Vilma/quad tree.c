#include <stdio.h>
#include <stdlib.h>
#define CAPACITY 2
typedef struct {
    int x, y;
} Point;
typedef struct Quad {
    int x, y, w, h;
    int count;
    Point points[CAPACITY];

    struct Quad *nw, *ne, *sw, *se;
} Quad;
Quad* createQuad(int x, int y, int w, int h) {
    Quad* q = (Quad*)malloc(sizeof(Quad));
    q->x = x; q->y = y;
    q->w = w; q->h = h;
    q->count = 0;
    q->nw = q->ne = q->sw = q->se = NULL;
    return q;
}
int contains(Quad* q, Point p) {
    return (p.x >= q->x && p.x < q->x + q->w &&
            p.y >= q->y && p.y < q->y + q->h);
}
void subdivide(Quad* q) {
    int hw = q->w / 2;
    int hh = q->h / 2;

    q->nw = createQuad(q->x, q->y, hw, hh);
    q->ne = createQuad(q->x + hw, q->y, hw, hh);
    q->sw = createQuad(q->x, q->y + hh, hw, hh);
    q->se = createQuad(q->x + hw, q->y + hh, hw, hh);
}
int insert(Quad* q, Point p) {
    if (!contains(q, p))
        return 0;

    if (q->count < CAPACITY) {
        q->points[q->count++] = p;
        return 1;
    }

    if (q->nw == NULL)
        subdivide(q);

    if (insert(q->nw, p)) return 1;
    if (insert(q->ne, p)) return 1;
    if (insert(q->sw, p)) return 1;
    if (insert(q->se, p)) return 1;

    return 0;
}
void printQuad(Quad* q, int level) {
    if (q == NULL) return;

    printf("Level %d: (%d,%d,%d,%d) -> ", level, q->x, q->y, q->w, q->h);

    for (int i = 0; i < q->count; i++)
        printf("(%d,%d) ", q->points[i].x, q->points[i].y);

    printf("\n");

    printQuad(q->nw, level + 1);
    printQuad(q->ne, level + 1);
    printQuad(q->sw, level + 1);
    printQuad(q->se, level + 1);
}
int main() {
    Quad* root = createQuad(0, 0, 8, 8);

    Point pts[] = {{1,1}, {2,5}, {6,6}, {7,2}, {3,3}};
    int n = 5;

    for (int i = 0; i < n; i++)
        insert(root, pts[i]);

    printQuad(root, 0);

    return 0;
}
