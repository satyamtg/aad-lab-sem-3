#include <stdio.h>
#include <stdlib.h>

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

void merge(int arr1[], int arr2[], int m, int n, int *mergedArr)
{
  int i = 0, j = 0, k = 0;
  while (i < m && j < n)
  {
    if (arr1[i] < arr2[j])
    {
      mergedArr[k] = arr1[i];
      i++;
    }
    else
    {
      mergedArr[k] = arr2[j];
      j++;
    }
    k++;
  }
  while (i < m)
  {
    mergedArr[k] = arr1[i];
    i++; k++;
  }
  while (j < n)
  {
    mergedArr[k] = arr2[j];
    j++;
    k++;
  }
}

void storeInorder(struct Node* Node, int inorder[], int *index_ptr)
{
  if (Node == NULL)
    return;
  storeInorder(Node->left, inorder, index_ptr);
  inorder[*index_ptr] = Node->data;
  (*index_ptr)++;
  storeInorder(Node->right, inorder, index_ptr);
}

struct Node* sortedArrayToBST(int arr[], int start, int end)
{
  int i;
  struct Node *temp = NULL;
  for(i = start; i<=end; i++)
  {
    temp = insert(temp, arr[i]);
  }
  return temp;
}

struct Node* mergeTrees(struct Node *root1, struct Node *root2, int m, int n)
{
  int arr1[m];
  int i = 0;
  storeInorder(root1, arr1, &i);
  int arr2[n];
  int j = 0;
  storeInorder(root2, arr2, &j);
  int z;
  z = m+n;
  int mergedArr[z];
  merge(arr1, arr2, m, n, mergedArr);
  return sortedArrayToBST (mergedArr, 0, m+n-1);
}

void printInorder(struct Node* Node)
{
  if (Node == NULL)
    return;
  printInorder(Node->left);
  printf("%d ", Node->data);
  printInorder(Node->right);
}

int main()
{
  struct Node *root1  = newNode(100);
  root1->left         = newNode(50);
  root1->right        = newNode(300);
  root1->left->left   = newNode(20);
  root1->left->right  = newNode(70);
  struct Node *root2  = newNode(80);
  root2->left         = newNode(40);
  root2->right        = newNode(120);
  struct Node *mergedTree = mergeTrees(root1, root2, 5, 3);
  printf ("Following is Inorder traversal of the merged tree \n");
  printInorder(mergedTree);
  return 0;
}
