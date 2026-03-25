#include <stdio.h>
#include <stdlib.h>
struct node
 {
    int d, h;
    struct node *l, *r;
};
int max(int a, int b) 
{ 
    return a > b ? a : b; 
}
int height(struct node *n) 
{ 
   return n ? n->h : 0; 
}
struct node* newNode(int d) 
{
    struct node* n = malloc(sizeof(struct node));
    n->d = d; n->l = n->r = NULL; n->h = 1;
    return n;
}
struct node* rightRotate(struct node* y) 
{
    struct node* x = y->l;
    y->l = x->r;
    x->r = y;
    y->h = max(height(y->l), height(y->r)) + 1;
    x->h = max(height(x->l), height(x->r)) + 1;
    return x;
}
struct node* leftRotate(struct node* x) 
{
    struct node* y = x->r;
    x->r = y->l;
    y->l = x;
    x->h = max(height(x->l), height(x->r)) + 1;
    y->h = max(height(y->l), height(y->r)) + 1;
    return y;
}
int balance(struct node* n) 
{
    return n ? height(n->l) - height(n->r) : 0;
}
struct node* insert(struct node* r, int d) 
{
    if (!r) return newNode(d);
    if (d < r->d) r->l = insert(r->l, d);
    else if (d > r->d) r->r = insert(r->r, d);
    else return r;
    r->h = 1 + max(height(r->l), height(r->r));
    if (balance(r) > 1 && d < r->l->d) return rightRotate(r);
    if (balance(r) < -1 && d > r->r->d) return leftRotate(r);
    if (balance(r) > 1 && d > r->l->d) {
        r->l = leftRotate(r->l);
        return rightRotate(r);
    }
    if (balance(r) < -1 && d < r->r->d) {
        r->r = rightRotate(r->r);
        return leftRotate(r);
    }
    return r;
}
void inorder(struct node* r) {
    if (r) {
        inorder(r->l);
        printf("%d ", r->d);
        inorder(r->r);
    }
}
int main() 
{
    struct node* root = NULL;
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 10);
    inorder(root);
}