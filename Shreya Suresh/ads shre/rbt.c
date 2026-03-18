#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *left, *right, *parent;
    bool color;
} Node;

Node* newNode(int data) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = data;
    n->left = n->right = n->parent = NULL;
    n->color = true;
    return n;
}

void leftRotate(Node **root, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rightRotate(Node **root, Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;

    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

void fixInsert(Node **root, Node *k) {
    while (k->parent != NULL && k->parent->color) {
        Node *u;
        if (k->parent == k->parent->parent->left) {
            u = k->parent->parent->right;

            if (u != NULL && u->color) { 
                k->parent->color = false;
                u->color = false;
                k->parent->parent->color = true;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(root, k);
                }
                k->parent->color = false;
                k->parent->parent->color = true;
                rightRotate(root, k->parent->parent);
            }
        } else {
            u = k->parent->parent->left;

            if (u != NULL && u->color) {
                k->parent->color = false;
                u->color = false;
                k->parent->parent->color = true;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) { 
                    k = k->parent;
                    rightRotate(root, k);
                }
                k->parent->color = false;
                k->parent->parent->color = true;
                leftRotate(root, k->parent->parent);
            }
        }
    }
    (*root)->color = false; 
}

void insert(Node **root, int key) {
    Node *node = newNode(key);
    Node *parent = NULL, *current = *root;

    while (current != NULL) {
        parent = current;
        if (key < current->data)
            current = current->left;
        else
            current = current->right;
    }

    node->parent = parent;
    if (parent == NULL)
        *root = node;
    else if (key < parent->data)
        parent->left = node;
    else
        parent->right = node;

    fixInsert(root, node);
}

void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    Node *root = NULL;

    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 15);

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    return 0;
}
