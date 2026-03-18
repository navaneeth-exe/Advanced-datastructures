#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    int depth;
    struct TreeNode *lnode;
    struct TreeNode *rnode;
};

int fetch_depth(struct TreeNode *ptr) {
    return ptr ? ptr->depth : 0;
}

int get_max(int x, int y) {
    return (x > y) ? x : y;
}

struct TreeNode* create_leaf(int val) {
    struct TreeNode* entry = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    entry->data = val;
    entry->lnode = NULL;
    entry->rnode = NULL;
    entry->depth = 1;
    return entry;
}

struct TreeNode* pivot_right(struct TreeNode *target) {
    struct TreeNode *temp = target->lnode;
    struct TreeNode *bridge = temp->rnode;

    temp->rnode = target;
    target->lnode = bridge;

    target->depth = get_max(fetch_depth(target->lnode), fetch_depth(target->rnode)) + 1;
    temp->depth = get_max(fetch_depth(temp->lnode), fetch_depth(temp->rnode)) + 1;

    return temp;
}

struct TreeNode* pivot_left(struct TreeNode *target) {
    struct TreeNode *temp = target->rnode;
    struct TreeNode *bridge = temp->lnode;

    temp->lnode = target;
    target->rnode = bridge;

    target->depth = get_max(fetch_depth(target->lnode), fetch_depth(target->rnode)) + 1;
    temp->depth = get_max(fetch_depth(temp->lnode), fetch_depth(temp->rnode)) + 1;

    return temp;
}

int calc_drift(struct TreeNode *ptr) {
    return ptr ? fetch_depth(ptr->lnode) - fetch_depth(ptr->rnode) : 0;
}

struct TreeNode* push_node(struct TreeNode* curr, int val) {
    if (curr == NULL)
        return create_leaf(val);

    if (val < curr->data)
        curr->lnode = push_node(curr->lnode, val);
    else if (val > curr->data)
        curr->rnode = push_node(curr->rnode, val);
    else
        return curr;

    curr->depth = 1 + get_max(fetch_depth(curr->lnode), fetch_depth(curr->rnode));
    int bias = calc_drift(curr);

    // Left-heavy scenarios
    if (bias > 1) {
        if (val > curr->lnode->data) {
            curr->lnode = pivot_left(curr->lnode);
        }
        return pivot_right(curr);
    }

    // Right-heavy scenarios
    if (bias < -1) {
        if (val < curr->rnode->data) {
            curr->rnode = pivot_right(curr->rnode);
        }
        return pivot_left(curr);
    }

    return curr;
}

void print_ascending(struct TreeNode *root) {
    if (root) {
        print_ascending(root->lnode);
        printf("%d ", root->data);
        print_ascending(root->rnode);
    }
}

int main() {
    struct TreeNode *head = NULL;
    int limit, input;

    if (scanf("%d", &limit) != 1) return 0;

    for (int j = 0; j < limit; j++) {
        if (scanf("%d", &input) == 1) {
            head = push_node(head, input);
        }
    }

    print_ascending(head);
    return 0;
}
