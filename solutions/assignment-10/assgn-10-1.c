#include<stdio.h>
#include<malloc.h>

struct Node
{
    int data;
    struct Node *left, *right;
};

struct Node *createNewNode(int data)
{
  struct Node *temp;
  temp = (struct Node *)malloc(sizeof(struct Node));
  temp->left = NULL;
  temp->right = NULL;
  temp->data = data;
  return temp;
}

void printPostorder(struct Node* node)
{
    if (node == NULL)
    {
      return;
    }
    else
    {
      printPostorder(node->left);
      printPostorder(node->right);
      printf("%d ",node->data);
    }
}

void printPreorder(struct Node* node)
{
    if (node == NULL)
    {
      return;
    }
    else
    {
      printf("%d ",node->data);
      printPreorder(node->left);
      printPreorder(node->right);
    }
}

int main()
{
    struct Node *root = createNewNode(1);
    root->left        = createNewNode(2);
    root->right       = createNewNode(3);
    root->left->left  = createNewNode(4);
    root->left->right = createNewNode(5);
    printf("Preorder: ");
    printPreorder(root);
    printf("\n");
    printf("Postorder: ");
    printPostorder(root);
    printf("\n");
    return 0;
}
