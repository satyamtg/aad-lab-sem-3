#include<stdio.h>
#include<stdlib.h>

struct Node
{
  int data;
  struct Node *left;
  struct Node *right;
  int height;
};

int max(int a, int b)
{
  return (a > b)? a : b;
}

int height(struct Node *N)
{
  if (N == NULL)
    return 0;
  return N->height;
}

struct Node* newNode(int data)
{
  struct Node* node = (struct Node*)malloc(sizeof(struct Node));
  node->data   = data;
  node->left   = NULL;
  node->right  = NULL;
  node->height = 1;
  return(node);
}

struct Node *rightRotate(struct Node *y)
{
  struct Node *x = y->left;
  struct Node *T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left), height(y->right))+1;
  x->height = max(height(x->left), height(x->right))+1;
  return x;
}

struct Node *leftRotate(struct Node *x)
{
  struct Node *y = x->right;
  struct Node *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left), height(x->right))+1;
  y->height = max(height(y->left), height(y->right))+1;
  return y;
}

int getBalance(struct Node *N)
{
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

struct Node* insert(struct Node* node, int data)
{
  if (node == NULL)
    return(newNode(data));
  if (data < node->data)
    node->left  = insert(node->left, data);
  else if (data > node->data)
    node->right = insert(node->right, data);
  else
    return node;
  node->height = 1 + max(height(node->left),height(node->right));
  int balance = getBalance(node);
  if (balance > 1 && data < node->left->data)
    return rightRotate(node);
  if (balance < -1 && data > node->right->data)
    return leftRotate(node);
  if (balance > 1 && data > node->left->data)
  {
    node->left =  leftRotate(node->left);
    return rightRotate(node);
  }
  if (balance < -1 && data < node->right->data)
  {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }
  return node;
}

void preOrder(struct Node *root)
{
  if(root != NULL)
  {
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
  }
}

int main()
{
  struct Node *root = NULL;
  root = insert(root, 10);
  root = insert(root, 20);
  root = insert(root, 30);
  root = insert(root, 40);
  root = insert(root, 50);
  root = insert(root, 25);
  printf("Preorder traversal of the constructed AVL tree is \n");
  preOrder(root);
  return 0;
}
