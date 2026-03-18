#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int key, degree;
    struct Node *parent, *child, *sibling;
} Node;

// Create node
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->degree = 0;
    newNode->parent = newNode->child = newNode->sibling = NULL;
    return newNode;
}

// Merge root lists
Node* mergeHeaps(Node* h1, Node* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    Node *head = NULL, *tail = NULL;

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

// Link trees
void linkTrees(Node* y, Node* z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
}

// Union heaps
Node* unionHeaps(Node* h1, Node* h2) {
    Node* newHead = mergeHeaps(h1, h2);
    if (!newHead) return NULL;

    Node *prev = NULL, *curr = newHead, *next = curr->sibling;

    while (next != NULL) {
        if ((curr->degree != next->degree) ||
            (next->sibling && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else {
            if (curr->key <= next->key) {
                curr->sibling = next->sibling;
                linkTrees(next, curr);
            } else {
                if (prev == NULL)
                    newHead = next;
                else
                    prev->sibling = next;

                linkTrees(curr, next);
                curr = next;
            }
        }
        next = curr->sibling;
    }

    return newHead;
}

// Insert
Node* insert(Node* heap, int key) {
    Node* temp = createNode(key);
    return unionHeaps(heap, temp);
}

// Find minimum
Node* getMin(Node* heap) {
    if (!heap) return NULL;

    Node *y = NULL, *x = heap;
    int min = x->key;

    while (x != NULL) {
        if (x->key < min) {
            min = x->key;
            y = x;
        }
        x = x->sibling;
    }

    return (y == NULL) ? heap : y;
}

// Reverse list
Node* reverseList(Node* node) {
    Node *prev = NULL, *curr = node, *next;

    while (curr) {
        next = curr->sibling;
        curr->sibling = prev;
        curr->parent = NULL;
        prev = curr;
        curr = next;
    }
    return prev;
}

// Extract minimum
Node* extractMin(Node* heap) {
    if (!heap) return NULL;

    Node *minNode = heap, *minPrev = NULL;
    Node *curr = heap, *prev = NULL;

    int min = heap->key;

    while (curr != NULL) {
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

    Node* child = reverseList(minNode->child);
    heap = unionHeaps(heap, child);

    printf("Extracted Min: %d\n", minNode->key);
    free(minNode);

    return heap;
}

// Display
void display(Node* heap) {
    if (!heap) {
        printf("Heap is empty\n");
        return;
    }

    Node* temp = heap;
    while (temp) {
        printf("B%d: ", temp->degree);

        Node* curr = temp;
        // Simple traversal (not full tree print)
        while (curr) {
            printf("%d ", curr->key);
            curr = curr->child;
        }
        printf("\n");

        temp = temp->sibling;
    }
}

// Main
int main() {
    Node* heap = NULL;
    int choice, value;

    while (1) {
        printf("\n--- Binomial Heap Menu ---\n");
        printf("1. Insert\n2. Find Min\n3. Extract Min\n4. Display\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                heap = insert(heap, value);
                break;

            case 2: {
                Node* min = getMin(heap);
                if (min)
                    printf("Minimum: %d\n", min->key);
                else
                    printf("Heap is empty\n");
                break;
            }

            case 3:
                heap = extractMin(heap);
                break;

            case 4:
                display(heap);
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
}
