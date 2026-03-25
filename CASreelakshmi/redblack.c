#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct Node {
    int data;
    int color;
    struct Node *left, *right, *parent;
};

struct Node *root = NULL;

// Create node
struct Node* createNode(int data) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = data;
    n->color = RED;
    n->left = n->right = n->parent = NULL;
    return n;
}

// Left rotate
void leftRotate(struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;

    if (y->left)
        y->left->parent = x;

    y->parent = x->parent;

    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Right rotate
void rightRotate(struct Node *y) {
    struct Node *x = y->left;
    y->left = x->right;

    if (x->right)
        x->right->parent = y;

    x->parent = y->parent;

    if (!y->parent)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// Fix insertion
void fixInsert(struct Node *z) {
    while (z->parent && z->parent->color == RED) {
        struct Node *gp = z->parent->parent;

        if (z->parent == gp->left) {
            struct Node *u = gp->right;

            if (u && u->color == RED) {
                z->parent->color = BLACK;
                u->color = BLACK;
                gp->color = RED;
                z = gp;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                gp->color = RED;
                rightRotate(gp);
            }
        } else {
            struct Node *u = gp->left;

            if (u && u->color == RED) {
                z->parent->color = BLACK;
                u->color = BLACK;
                gp->color = RED;
                z = gp;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                gp->color = RED;
                leftRotate(gp);
            }
        }
    }
    root->color = BLACK;
}

// Insert
void insert(int data) {
    struct Node *z = createNode(data);
    struct Node *y = NULL;
    struct Node *x = root;

    while (x) {
        y = x;
        if (data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (!y)
        root = z;
    else if (data < y->data)
        y->left = z;
    else
        y->right = z;

    fixInsert(z);
}

// Search
struct Node* search(struct Node* root, int key) {
    if (!root || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);
    return search(root->right, key);
}

// Inorder
void inorder(struct Node *root) {
    if (!root) return;
    inorder(root->left);
    printf("%d(%s) ", root->data, root->color==RED?"R":"B");
    inorder(root->right);
}

// Display tree (simple)
void display(struct Node *root, int space) {
    if (!root) return;

    space += 5;
    display(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++) printf(" ");
    printf("%d(%s)\n", root->data, root->color==RED?"R":"B");

    display(root->left, space);
}

// Main menu
int main() {
    int choice, value;

    while (1) {
        printf("\n--- Red-Black Tree Menu ---\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Inorder Traversal\n");
        printf("4. Display Tree\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insert(value);
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (search(root, value))
                    printf("Found\n");
                else
                    printf("Not Found\n");
                break;

            case 3:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 4:
                printf("Tree structure:\n");
                display(root, 0);
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}
