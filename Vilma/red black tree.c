#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct Node {
    int data;
    int color;
    struct Node *left, *right, *parent;
};

struct Node* root = NULL;
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->color = RED;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}
void rotateLeft(struct Node** root, struct Node* pt) {
    struct Node* right_child = pt->right;

    pt->right = right_child->left;
    if (pt->right != NULL)
        pt->right->parent = pt;

    right_child->parent = pt->parent;

    if (pt->parent == NULL)
        *root = right_child;
    else if (pt == pt->parent->left)
        pt->parent->left = right_child;
    else
        pt->parent->right = right_child;

    right_child->left = pt;
    pt->parent = right_child;
}
void rotateRight(struct Node** root, struct Node* pt) {
    struct Node* left_child = pt->left;

    pt->left = left_child->right;
    if (pt->left != NULL)
        pt->left->parent = pt;

    left_child->parent = pt->parent;

    if (pt->parent == NULL)
        *root = left_child;
    else if (pt == pt->parent->left)
        pt->parent->left = left_child;
    else
        pt->parent->right = left_child;

    left_child->right = pt;
    pt->parent = left_child;
}
void fixViolation(struct Node** root, struct Node* pt) {
    struct Node *parent = NULL, *grandparent = NULL;

    while (pt != *root && pt->color == RED && pt->parent->color == RED) {
        parent = pt->parent;
        grandparent = parent->parent;

        if (parent == grandparent->left) {
            struct Node* uncle = grandparent->right
            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                pt = grandparent;
            } else{
                if (pt == parent->right) {
                    rotateLeft(root, parent);
                    pt = parent;
                    parent = pt->parent;
                }
                rotateRight(root, grandparent);
                int temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                pt = parent;
            }
        } else {
            struct Node* uncle = grandparent->left;

            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                pt = grandparent;
            } else {
                if (pt == parent->left) {
                    rotateRight(root, parent);
                    pt = parent;
                    parent = pt->parent;
                }

                rotateLeft(root, grandparent);
                int temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                pt = parent;
            }
        }
    }

    (*root)->color = BLACK;
}
void insert(int data) {
    struct Node* pt = createNode(data);

    struct Node *y = NULL;
    struct Node *x = root;

    while (x != NULL) {
        y = x;
        if (pt->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    pt->parent = y;

    if (y == NULL)
        root = pt;
    else if (pt->data < y->data)
        y->left = pt;
    else
        y->right = pt;

    fixViolation(&root, pt);
}
void inorder(struct Node* root) {
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
int main() {
    insert(10);
    insert(20);
    insert(30);
    insert(15);
    insert(25);

    printf("Inorder traversal:\n");
    inorder(root);

    return 0;
}
