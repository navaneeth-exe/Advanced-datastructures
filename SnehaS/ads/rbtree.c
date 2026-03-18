#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct Node {
    int data, color;
    struct Node *left, *right, *parent;
};

struct Node *root, *NIL;
struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->color = RED;
    node->left = node->right = NIL;
    node->parent = NULL;
    return node;
}

void leftRotate(struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;

    if (y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rightRotate(struct Node *y) {
    struct Node *x = y->left;
    y->left = x->right;

    if (x->right != NIL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}

void fixInsert(struct Node *k) {
    while (k->parent && k->parent->color == RED) {
        if (k->parent == k->parent->parent->left) {
            struct Node *u = k->parent->parent->right;

            if (u->color == RED) {
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        } else {
            struct Node *u = k->parent->parent->left;

            if (u->color == RED) {
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void insert(int data) {
    struct Node *node = createNode(data);
    struct Node *y = NULL;
    struct Node *x = root;

    while (x != NIL) {
        y = x;
        if (data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    node->parent = y;

    if (y == NULL)
        root = node;
    else if (data < y->data)
        y->left = node;
    else
        y->right = node;

    if (node->parent == NULL) {
        node->color = BLACK;
        return;
    }

    if (node->parent->parent == NULL)
        return;

    fixInsert(node);
}

struct Node* search(struct Node* node, int key) {
    if (node == NIL || key == node->data)
        return node;
    if (key < node->data)
        return search(node->left, key);
    return search(node->right, key);
}

struct Node* minimum(struct Node* node) {
    while (node->left != NIL)
        node = node->left;
    return node;
}

void transplant(struct Node *u, struct Node *v) {
    if (u->parent == NULL)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;
}

void fixDelete(struct Node *x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            struct Node *s = x->parent->right;

            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->color == BLACK && s->right->color == BLACK) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->right->color == BLACK) {
                    s->left->color = BLACK;
                    s->color = RED;
                    rightRotate(s);
                    s = x->parent->right;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            struct Node *s = x->parent->left;

            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (s->right->color == BLACK && s->left->color == BLACK) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->left->color == BLACK) {
                    s->right->color = BLACK;
                    s->color = RED;
                    leftRotate(s);
                    s = x->parent->left;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void deleteValue(int data) {
    struct Node *z = search(root, data);
    if (z == NIL) {
        printf("Value not found\n");
        return;
    }

    struct Node *y = z;
    struct Node *x;
    int y_original_color = y->color;

    if (z->left == NIL) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == z)
            x->parent = y;
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == BLACK)
        fixDelete(x);
}

void inorder(struct Node *node) {
    if (node != NIL) {
        inorder(node->left);
        printf("%d(%s) ", node->data, node->color == RED ? "R" : "B");
        inorder(node->right);
    }
}

int main() {
    NIL = (struct Node*)malloc(sizeof(struct Node));
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL;

    root = NIL;

    int choice, value;

    while (1) {
        printf("\n1.Insert\n2.Delete\n3.Display\n4.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insert(value);
                break;

            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                deleteValue(value);
                break;

            case 3:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}
