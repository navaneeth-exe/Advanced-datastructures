#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data, degree;
    struct Node *child, *sibling, *parent;
};


struct Node* newNode(int key) {
    struct Node* t = (struct Node*)malloc(sizeof(struct Node));
    t->data = key;
    t->degree = 0;
    t->child = t->sibling = t->parent = NULL;
    return t;
}


struct Node* mergeTrees(struct Node* a, struct Node* b) {
    if (a->data > b->data) {
        struct Node* temp = a;
        a = b;
        b = temp;
    }
    b->parent = a;
    b->sibling = a->child;
    a->child = b;
    a->degree++;
    return a;
}

// Merge root lists
struct Node* mergeRootLists(struct Node* h1, struct Node* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    struct Node* head = NULL;
    struct Node** pos = &head;

    while (h1 && h2) {
        if (h1->degree <= h2->degree) {
            *pos = h1;
            h1 = h1->sibling;
        } else {
            *pos = h2;
            h2 = h2->sibling;
        }
        pos = &((*pos)->sibling);
    }

    *pos = (h1) ? h1 : h2;
    return head;
}

struct Node* heapify(struct Node* head) {
    if (!head) return NULL;

    struct Node *prev = NULL, *curr = head, *next = curr->sibling;

    while (next) {
        if (curr->degree != next->degree ||
            (next->sibling && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else {
            if (curr->data <= next->data) {
                curr->sibling = next->sibling;
                curr = mergeTrees(curr, next);
            } else {
                if (!prev) head = next;
                else prev->sibling = next;
                curr = mergeTrees(next, curr);
            }
        }
        next = curr->sibling;
    }
    return head;
}

// Insert a key into binomial heap
struct Node* insert(struct Node* heap, int key) {
    struct Node* temp = newNode(key);
    heap = mergeRootLists(heap, temp);
    return heapify(heap);
}


void printTree(struct Node* h) {
    while (h) {
        printf("%d ", h->data);
        printTree(h->child);
        h = h->sibling;
    }
}


void printHeap(struct Node* h) {
    while (h) {
        printf("B%d: ", h->degree);
        printTree(h);
        printf("\n");
        h = h->sibling;
    }
}


int main() {
    struct Node* heap = NULL;

    heap = insert(heap, 10);
    heap = insert(heap, 20);
    heap = insert(heap, 5);
    heap = insert(heap, 30);
    heap = insert(heap, 15);

    printHeap(heap);
    return 0;
}
