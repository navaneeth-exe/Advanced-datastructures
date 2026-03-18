#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Point {
    int x, y;
} Point;

typedef struct Node {
    Point pos;
    struct Node *nw, *ne, *sw, *se;
} Node;

Node* create_node(int x, int y) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->pos.x = x;
    n->pos.y = y;
    n->nw = n->ne = n->sw = n->se = NULL;
    return n;
}

Node* insert(Node* root, int x, int y) {
    if (!root) return create_node(x, y);
    if (x < root->pos.x && y >= root->pos.y) root->nw = insert(root->nw, x, y);
    else if (x >= root->pos.x && y >= root->pos.y) root->ne = insert(root->ne, x, y);
    else if (x < root->pos.x && y < root->pos.y) root->sw = insert(root->sw, x, y);
    else root->se = insert(root->se, x, y);
    return root;
}

bool search(Node* root, int x, int y) {
    if (!root) return false;
    if (root->pos.x == x && root->pos.y == y) return true;
    if (x < root->pos.x && y >= root->pos.y) return search(root->nw, x, y);
    else if (x >= root->pos.x && y >= root->pos.y) return search(root->ne, x, y);
    else if (x < root->pos.x && y < root->pos.y) return search(root->sw, x, y);
    else return search(root->se, x, y);
}

void range_query(Node* root, int x1, int y1, int x2, int y2) {
    if (!root) return;
    if (root->pos.x >= x1 && root->pos.x <= x2 && root->pos.y >= y1 && root->pos.y <= y2)
        printf("Point in range: (%d, %d)\n", root->pos.x, root->pos.y);

    if (x1 < root->pos.x || y1 >= root->pos.y) range_query(root->nw, x1, y1, x2, y2);
    if (x2 >= root->pos.x || y1 >= root->pos.y) range_query(root->ne, x1, y1, x2, y2);
    if (x1 < root->pos.x || y2 < root->pos.y) range_query(root->sw, x1, y1, x2, y2);
    if (x2 >= root->pos.x || y2 < root->pos.y) range_query(root->se, x1, y1, x2, y2);
}

Node* delete_node(Node* root, int x, int y) {
    if (!root) return NULL;

    if (root->pos.x == x && root->pos.y == y) {
        Node *nw = root->nw, *ne = root->ne, *sw = root->sw, *se = root->se;
        free(root);
        Node* new_root = NULL;
        void reinsert(Node* n) {
            if (!n) return;
            new_root = insert(new_root, n->pos.x, n->pos.y);
            reinsert(n->nw); reinsert(n->ne);
            reinsert(n->sw); reinsert(n->se);
            free(n);
        }
        reinsert(nw); reinsert(ne); reinsert(sw); reinsert(se);
        return new_root;
    }

    if (x < root->pos.x && y >= root->pos.y) root->nw = delete_node(root->nw, x, y);
    else if (x >= root->pos.x && y >= root->pos.y) root->ne = delete_node(root->ne, x, y);
    else if (x < root->pos.x && y < root->pos.y) root->sw = delete_node(root->sw, x, y);
    else root->se = delete_node(root->se, x, y);
    return root;
}

int main() {
    Node* root = NULL;
    root = insert(root, 10, 10);
    insert(root, 5, 15);
    insert(root, 15, 15);
    insert(root, 5, 5);
    
    printf("Range Query (0,0 to 12,12):\n");
    range_query(root, 0, 0, 12, 12);
    
    root = delete_node(root, 5, 5);
    return 0;
}
