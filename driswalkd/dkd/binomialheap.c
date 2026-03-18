#include <stdio.h>
#include <stdlib.h>

struct BinomialNode {
    int val, degree;
    struct BinomialNode *parent, *child, *sibling;
};


struct BinomialNode* create_node(int k) {
    struct BinomialNode* n = (struct BinomialNode*)malloc(sizeof(struct BinomialNode));
    n->val = k;
    n->degree = 0;
    n->parent = n->child = n->sibling = NULL;
    return n;
}


struct BinomialNode* link_trees(struct BinomialNode* y, struct BinomialNode* z) {
    if (y->val > z->val) { 
        struct BinomialNode* temp = y; y = z; z = temp;
    }
    z->parent = y;
    z->sibling = y->child;
    y->child = z;
    y->degree++;
    return y;
}


struct BinomialNode* merge_heaps(struct BinomialNode* h1, struct BinomialNode* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    struct BinomialNode *head = NULL, **pos = &head;
    while (h1 && h2) {
        if (h1->degree <= h2->degree) {
            *pos = h1; h1 = h1->sibling;
        } else {
            *pos = h2; h2 = h2->sibling;
        }
        pos = &((*pos)->sibling);
    }
    *pos = h1 ? h1 : h2;
    return head;
}


struct BinomialNode* union_heaps(struct BinomialNode* h1, struct BinomialNode* h2) {
    struct BinomialNode* res = merge_heaps(h1, h2);
    if (!res) return NULL;

    struct BinomialNode *prev = NULL, *curr = res, *next = res->sibling;
    while (next) {
        if ((curr->degree != next->degree) || (next->sibling && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else {
            if (curr->val <= next->val) {
                curr->sibling = next->sibling;
                link_trees(curr, next);
            } else {
                if (!prev) res = next;
                else prev->sibling = next;
                link_trees(next, curr);
                curr = next;
            }
        }
        next = curr->sibling;
    }
    return res;
}


struct BinomialNode* insert(struct BinomialNode* head, int val) {
    return union_heaps(head, create_node(val));
}


struct BinomialNode* find_min(struct BinomialNode* head) {
    struct BinomialNode *min_node = head;
    while (head) {
        if (head->val < min_node->val) min_node = head;
        head = head->sibling;
    }
    return min_node;
}

struct BinomialNode* extract_min(struct BinomialNode** head) {
    if (!*head) return NULL;

    struct BinomialNode *min_node = *head, *prev_min = NULL;
    struct BinomialNode *curr = *head, *prev = NULL;

    while (curr) {
        if (curr->val < min_node->val) {
            min_node = curr;
            prev_min = prev;
        }
        prev = curr;
        curr = curr->sibling;
    }

    if (prev_min) prev_min->sibling = min_node->sibling;
    else *head = min_node->sibling;

    struct BinomialNode *child = min_node->child, *rev_child = NULL;
    while (child) {
        struct BinomialNode* next = child->sibling;
        child->sibling = rev_child;
        rev_child = child;
        child = next;
    }

    *head = union_heaps(*head, rev_child);
    return min_node;
}

int main() {
    struct BinomialNode* heap = NULL;
    heap = insert(heap, 15);
    heap = insert(heap, 10);
    heap = insert(heap, 20);

    struct BinomialNode* m = extract_min(&heap);
    printf("Extracted Min: %d\n", m->val);
    free(m);

    return 0;
}
