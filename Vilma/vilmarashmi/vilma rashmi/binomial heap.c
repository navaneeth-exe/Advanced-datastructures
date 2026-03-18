#include <stdio.h>
#include <stdlib.h>
struct Node {
    int key, degree;
    struct Node *parent, *child, *sibling;
};
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->degree = 0;
    newNode->parent = newNode->child = newNode->sibling = NULL;
    return newNode;
}
struct Node* merge(struct Node* h1, struct Node* h2) {
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
void linkTree(struct Node* y, struct Node* z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
}
struct Node* unionHeap(struct Node* h1, struct Node* h2) {
    struct Node* newHead = merge(h1, h2);
    if (!newHead) return NULL;

    struct Node *prev = NULL, *curr = newHead, *next = curr->sibling;

    while (next != NULL) {
        if ((curr->degree != next->degree) ||
            (next->sibling && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else {
            if (curr->key <= next->key) {
                curr->sibling = next->sibling;
                linkTree(next, curr);
            } else {
                if (prev == NULL)
                    newHead = next;
                else
                    prev->sibling = next;

                linkTree(curr, next);
                curr = next;
            }
        }
        next = curr->sibling;
    }

    return newHead;
}
struct Node* insert(struct Node* heap, int key) {
    struct Node* temp = createNode(key);
    return unionHeap(heap, temp);
}
struct Node* getMin(struct Node* heap) {
    struct Node* minNode = heap;
    struct Node* curr = heap;

    int min = heap->key;

    while (curr != NULL) {
        if (curr->key < min) {
            min = curr->key;
            minNode = curr;
        }
        curr = curr->sibling;
    }
    return minNode;
}
struct Node* reverse(struct Node* node) {
    struct Node *prev = NULL, *curr = node, *next;

    while (curr) {
        curr->parent = NULL;
        next = curr->sibling;
        curr->sibling = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
struct Node* extractMin(struct Node* heap) {
    if (!heap) return NULL;

    struct Node *minNode = heap, *minPrev = NULL;
    struct Node *curr = heap, *prev = NULL;

    int min = heap->key;

    while (curr) {
        if (curr->key < min) {
            min = curr->key;
            minNode = curr;
            minPrev = prev;
        }
        prev = curr;
        curr = curr->sibling;
    }

    if (minPrev)
        minPrev->sibling = minNode->sibling;
    else
        heap = minNode->sibling;

    struct Node* child = reverse(minNode->child);

    return unionHeap(heap, child);
}
void printHeap(struct Node* heap) {
    while (heap) {
        printf("B%d: ", heap->degree);
        struct Node* curr = heap;
        while (curr) {
            printf("%d ", curr->key);
            curr = curr->child;
        }
        printf("\n");
        heap = heap->sibling;
    }
}
int main() {
    struct Node* heap = NULL;

    heap = insert(heap, 10);
    heap = insert(heap, 20);
    heap = insert(heap, 5);
    heap = insert(heap, 30);

    printf("Heap after insertions:\n");
    printHeap(heap);

    heap = extractMin(heap);
    printf("\nHeap after extracting min:\n");
    printHeap(heap);

    return 0;
}
