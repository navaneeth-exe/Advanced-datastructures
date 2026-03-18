#include <stdio.h>
#include <stdlib.h>

struct BinomialNode {
    int key;
    int degree;
    struct BinomialNode* parent;
    struct BinomialNode* child;
    struct BinomialNode* sibling;
};

struct BinomialNode* heap = NULL;

// Create new node
struct BinomialNode* createNode(int key) {
    struct BinomialNode* node = (struct BinomialNode*)malloc(sizeof(struct BinomialNode));
    node->key = key;
    node->degree = 0;
    node->parent = node->child = node->sibling = NULL;
    return node;
}

// Merge two root lists
struct BinomialNode* merge(struct BinomialNode* h1, struct BinomialNode* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    struct BinomialNode* head = NULL;
    struct BinomialNode* tail = NULL;

    if (h1->degree <= h2->degree) {
        head = tail = h1;
        h1 = h1->sibling;
    } else {
        head = tail = h2;
        h2 = h2->sibling;
    }

    while (h1 && h2) {
        if (h1->degree <= h2->degree) {
            tail->sibling = h1;
            tail = h1;
            h1 = h1->sibling;
        } else {
            tail->sibling = h2;
            tail = h2;
            h2 = h2->sibling;
        }
    }

    tail->sibling = (h1) ? h1 : h2;
    return head;
}

// Link two binomial trees
void linkTree(struct BinomialNode* y, struct BinomialNode* z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
}

// Union two heaps
struct BinomialNode* unionHeaps(struct BinomialNode* h1, struct BinomialNode* h2) {
    struct BinomialNode* newHeap = merge(h1, h2);
    if (!newHeap) return NULL;

    struct BinomialNode* prev = NULL;
    struct BinomialNode* curr = newHeap;
    struct BinomialNode* next = curr->sibling;

    while (next) {
        if ((curr->degree != next->degree) ||
            (next->sibling && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else {
            if (curr->key <= next->key) {
                curr->sibling = next->sibling;
                linkTree(next, curr);
            } else {
                if (!prev) newHeap = next;
                else prev->sibling = next;
                linkTree(curr, next);
                curr = next;
            }
        }
        next = curr->sibling;
    }

    return newHeap;
}

// Insert key
void insert(int key) {
    struct BinomialNode* node = createNode(key);
    heap = unionHeaps(heap, node);
    printf("Inserted %d\n", key);
}

// Find minimum node
struct BinomialNode* findMin(struct BinomialNode* h) {
    if (!h) return NULL;
    struct BinomialNode* min = h;
    struct BinomialNode* curr = h->sibling;

    while (curr) {
        if (curr->key < min->key)
            min = curr;
        curr = curr->sibling;
    }
    return min;
}

// Extract minimum node
void extractMin() {
    if (!heap) {
        printf("Heap is empty!\n");
        return;
    }

    struct BinomialNode* minPrev = NULL;
    struct BinomialNode* minNode = heap;
    struct BinomialNode* prev = NULL;
    struct BinomialNode* curr = heap;

    int minKey = curr->key;

    // Find minimum
    while (curr) {
        if (curr->key < minKey) {
            minKey = curr->key;
            minPrev = prev;
            minNode = curr;
        }
        prev = curr;
        curr = curr->sibling;
    }

    // Remove minNode from root list
    if (!minPrev) heap = minNode->sibling;
    else minPrev->sibling = minNode->sibling;

    // Reverse minNode's children and make new heap
    struct BinomialNode* child = minNode->child;
    struct BinomialNode* newHeap = NULL;
    while (child) {
        struct BinomialNode* next = child->sibling;
        child->sibling = newHeap;
        child->parent = NULL;
        newHeap = child;
        child = next;
    }

    heap = unionHeaps(heap, newHeap);
    printf("Extracted min: %d\n", minNode->key);
    free(minNode);
}

// Display heap (simple)
void display(struct BinomialNode* h) {
    if (!h) return;

    printf("B%d\n", h->degree);
    printf("Root: %d\n", h->key);
    printf("Children: ");
    struct BinomialNode* child = h->child;
    while (child) {
        printf("%d ", child->key);
        child = child->sibling;
    }
    printf("\n\n");

    display(h->sibling);
    display(h->child);
}

// Interactive menu
int main() {
    int choice, key;

    while (1) {
        printf("\n--- Binomial Heap Menu ---\n");
        printf("1. Insert\n");
        printf("2. Find Min\n");
        printf("3. Extract Min\n");
        printf("4. Display Heap\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(key);
                break;

            case 2: {
                struct BinomialNode* minNode = findMin(heap);
                if (minNode) printf("Minimum: %d\n", minNode->key);
                else printf("Heap is empty\n");
                break;
            }

            case 3:
                extractMin();
                break;

            case 4:
                printf("Heap Structure:\n");
                display(heap);
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
}
