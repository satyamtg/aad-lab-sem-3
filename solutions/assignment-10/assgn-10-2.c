#include <stdio.h>
#include <stdlib.h>

struct node
{
  int data;
  struct node *left;
  struct node *right;
};

struct node *newNode(int data)
{
  struct node *temp;
  temp = (struct node *)malloc(sizeof(struct node));
  temp->left = NULL;
  temp->right = NULL;
  temp->data = data;
  return temp;
}

struct node* constructTreeUtil (int pre[], int post[], int* preIndex, int l, int h, int size)
{
  if (*preIndex >= size || l > h)
    return NULL;
  struct node* root = newNode ( pre[*preIndex] );
  ++*preIndex;
  if (l == h)
    return root;
  int i;
  for (i = l; i <= h; ++i)
    if (pre[*preIndex] == post[i])
      break;
  if (i <= h)
  {
    root->left = constructTreeUtil (pre, post, preIndex, l, i, size);
    root->right = constructTreeUtil (pre, post, preIndex, i + 1, h, size);
  }
  return root;
}

struct node *constructTree (int pre[], int post[], int size)
{
  int preIndex = 0;
  return constructTreeUtil (pre, post, &preIndex, 0, size - 1, size);
}

void printInorder (struct node* node)
{
    if (node == NULL)
        return;
    printInorder(node->left);
    printf("%d ", node->data);
    printInorder(node->right);
}

int main ()
{
  int pre[] = {1, 2, 4, 8, 9, 5, 3, 6, 7};
  int post[] = {8, 9, 4, 5, 2, 6, 7, 3, 1};
  int size = sizeof( pre ) / sizeof( pre[0] );
  struct node *root = constructTree(pre, post, size);
  printf("Inorder traversal of the constructed tree: \n");
  printInorder(root);
  return 0;
}
