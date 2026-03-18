#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Node structure
typedef struct Node {
    int key, degree;
    struct Node *parent, *child, *sibling;
} Node;

// Create a new node
Node* createNode(int key) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->key = key;
    temp->degree = 0;
    temp->parent = temp->child = temp->sibling = NULL;
    return temp;
}

// Merge root lists
Node* mergeRootLists(Node* h1, Node* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    Node *head = NULL, *tail = NULL;

    if (h1->degree <= h2->degree) {
        head = h1;
        h1 = h1->sibling;
    } else {
        head = h2;
        h2 = h2->sibling;
    }

    tail = head;

    while (h1 && h2) {
        if (h1->degree <= h2->degree) {
            tail->sibling = h1;
            h1 = h1->sibling;
        } else {
            tail->sibling = h2;
            h2 = h2->sibling;
        }
        tail = tail->sibling;
    }

    tail->sibling = (h1) ? h1 : h2;
    return head;
}

// Link two binomial trees
void linkTrees(Node* y, Node* z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
}

// Union of heaps
Node* unionHeap(Node* h1, Node* h2) {
    Node* newHead = mergeRootLists(h1, h2);
    if (!newHead) return NULL;

    Node *prev = NULL, *curr = newHead, *next = curr->sibling;

    while (next) {
        if ((curr->degree != next->degree) ||
            (next->sibling && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else {
            if (curr->key <= next->key) {
                curr->sibling = next->sibling;
                linkTrees(next, curr);
            } else {
                if (!prev)
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
    return unionHeap(heap, temp);
}

// Find minimum
Node* getMin(Node* heap) {
    if (!heap) return NULL;

    Node* y = NULL;
    Node* x = heap;
    int min = INT_MAX;

    while (x) {
        if (x->key < min) {
            min = x->key;
            y = x;
        }
        x = x->sibling;
    }
    return y;
}

// Reverse linked list
Node* reverseList(Node* node) {
    Node* prev = NULL;
    while (node) {
        Node* next = node->sibling;
        node->sibling = prev;
        node->parent = NULL;
        prev = node;
        node = next;
    }
    return prev;
}

// Extract minimum
Node* extractMin(Node* heap) {
    if (!heap) return NULL;

    Node *minNode = heap, *minPrev = NULL;
    Node *curr = heap, *prev = NULL;

    int min = curr->key;

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

    Node* child = reverseList(minNode->child);
    free(minNode);

    return unionHeap(heap, child);
}

// Search node
Node* search(Node* heap, int key) {
    if (!heap) return NULL;
    if (heap->key == key) return heap;

    Node* res = search(heap->child, key);
    if (res) return res;

    return search(heap->sibling, key);
}

// Decrease key
void decreaseKey(Node* heap, int oldKey, int newKey) {
    Node* node = search(heap, oldKey);
    if (!node) {
        printf("Key not found!\n");
        return;
    }

    node->key = newKey;
    Node* parent = node->parent;

    while (parent && node->key < parent->key) {
        int temp = node->key;
        node->key = parent->key;
        parent->key = temp;

        node = parent;
        parent = parent->parent;
    }
}

// Delete key
Node* deleteKey(Node* heap, int key) {
    decreaseKey(heap, key, INT_MIN);
    return extractMin(heap);
}

// Display heap
void display(Node* heap, int level) {
    if (!heap) return;

    for (int i = 0; i < level; i++)
        printf("  ");

    printf("%d\n", heap->key);

    display(heap->child, level + 1);
    display(heap->sibling, level);
}

// Main menu
int main() {
    Node* heap = NULL;
    int choice, value, newValue;

    while (1) {
        printf("\n--- Binomial Heap Menu ---\n");
        printf("1. Insert\n");
        printf("2. Find Min\n");
        printf("3. Extract Min\n");
        printf("4. Decrease Key\n");
        printf("5. Delete Key\n");
        printf("6. Display Heap\n");
        printf("7. Exit\n");
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
                printf("Min extracted.\n");
                break;

            case 4:
                printf("Enter old key: ");
                scanf("%d", &value);
                printf("Enter new key: ");
                scanf("%d", &newValue);
                decreaseKey(heap, value, newValue);
                break;

            case 5:
                printf("Enter key to delete: ");
                scanf("%d", &value);
                heap = deleteKey(heap, value);
                break;

            case 6:
                printf("Heap structure:\n");
                display(heap, 0);
                break;

            case 7:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
}