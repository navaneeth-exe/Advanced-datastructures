#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key, degree;
    struct Node *parent, *child, *sibling;
};

struct Node* head = NULL;

struct Node* createNode(int key) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->key = key;
    temp->degree = 0;
    temp->parent = temp->child = temp->sibling = NULL;
    return temp;
}

struct Node* merge(struct Node* h1, struct Node* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    struct Node *head, *tail;

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

void linkTrees(struct Node* y, struct Node* z) {
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

void insert(int key) {
    struct Node* temp = createNode(key);
    head = unionHeap(head, temp);
}

struct Node* getMin() {
    struct Node* temp = head;
    struct Node* minNode = temp;
    int min = temp->key;

    while (temp != NULL) {
        if (temp->key < min) {
            min = temp->key;
            minNode = temp;
        }
        temp = temp->sibling;
    }
    return minNode;
}

struct Node* reverse(struct Node* node) {
    struct Node *prev = NULL, *curr = node, *next;
    while (curr) {
        next = curr->sibling;
        curr->sibling = prev;
        curr->parent = NULL;
        prev = curr;
        curr = next;
    }
    return prev;
}

void extractMin() {
    if (!head) {
        printf("Heap empty\n");
        return;
    }

    struct Node *minPrev = NULL, *minNode = head;
    struct Node *prev = NULL, *curr = head;
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
        head = minNode->sibling;

    struct Node* child = reverse(minNode->child);
    head = unionHeap(head, child);

    printf("Deleted min: %d\n", minNode->key);
    free(minNode);
}

void display(struct Node* h) {
    while (h) {
        printf("B%d: ", h->degree);
        struct Node* c = h;
        while (c) {
            printf("%d ", c->key);
            c = c->child;
        }
        printf("\n");
        h = h->sibling;
    }
}

int main() {
    int choice, val;

    while (1) {
        printf("\n1.Insert\n2.Get Min\n3.Extract Min\n4.Display\n5.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                insert(val);
                break;

            case 2:
                if (head)
                    printf("Min: %d\n", getMin()->key);
                else
                    printf("Heap empty\n");
                break;

            case 3:
                extractMin();
                break;

            case 4:
                display(head);
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}
