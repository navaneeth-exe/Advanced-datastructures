#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int time;
    int type;
    int val;
} Op;

struct Node {
    int sum;
    int min_prefix;
};

void update_tree(struct Node* tree, int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node].sum = val;
        tree[node].min_prefix = val;
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) update_tree(tree, 2 * node, start, mid, idx, val);
    else update_tree(tree, 2 * node + 1, mid + 1, end, idx, val);

    tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
    int right_min = tree[2 * node].sum + tree[2 * node + 1].min_prefix;
    tree[node].min_prefix = (tree[2 * node].min_prefix < right_min) ? tree[2 * node].min_prefix : right_min;
}

void insert_op(Op* log, int* count, int t, int type, int v, struct Node* tree, int max_t) {
    log[*count].time = t;
    log[*count].type = type;
    log[*count].val = v;
    (*count)++;
    update_tree(tree, 1, 0, max_t, t, type);
}

void delete_op(Op* log, int* count, int t, struct Node* tree, int max_t) {
    for (int i = 0; i < *count; i++) {
        if (log[i].time == t) {
            update_tree(tree, 1, 0, max_t, t, 0);
            for (int j = i; j < *count - 1; j++) log[j] = log[j+1];
            (*count)--;
            break;
        }
    }
}

int query_present_top(Op* log, int count) {
    int top_val = -1;
    int current_size = 0;
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (log[j].time > log[j+1].time) {
                Op temp = log[j]; log[j] = log[j+1]; log[j+1] = temp;
            }
        }
    }

    int stack[100], top = -1;
    for (int i = 0; i < count; i++) {
        if (log[i].type == 1) stack[++top] = log[i].val;
        else if (top >= 0) top--;
    }
    return (top >= 0) ? stack[top] : -1;
}

int main() {
    int max_t = 100;
    struct Node* tree = (struct Node*)calloc(4 * max_t, sizeof(struct Node));
    Op* log = (Op*)malloc(sizeof(Op) * 100);
    int count = 0;

    insert_op(log, &count, 10, 1, 50, tree, max_t);
    insert_op(log, &count, 30, 1, 100, tree, max_t);
    insert_op(log, &count, 20, -1, 0, tree, max_t);

    printf("Top at T=Current: %d\n", query_present_top(log, count));

    delete_op(log, &count, 20, tree, max_t);
    printf("Top after deleting T=20 Pop: %d\n", query_present_top(log, count));

    free(tree);
    free(log);
    return 0;
}
