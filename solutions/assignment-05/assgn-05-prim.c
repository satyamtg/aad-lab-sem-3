#include <stdio.h>
#include <limits.h>

int print_prim_mst(int parent[], int n, int graph[n][n])
{
  int sum = 0;
  for (int i = 1; i < n; i++)
    {
      printf("%d %d %d\n", parent[i], i, graph[i][parent[i]]);
      sum = sum + graph[i][parent[i]];
    }
  printf("%d\n", sum);
}

int find_min_key(int key[], int mstSet[], int n)
{
  int min = INT_MAX, min_index;
  for (int v = 0; v < n; v++)
    if (mstSet[v] == 0 && key[v] < min)
        min = key[v], min_index = v;
  return min_index;
}

void min_spanning_tree_prim(int n, int graph[n][n])
{
  int parent[n];
  int key[n];
  int mstSet[n];
  for (int i = 0; i < n; i++)
     key[i] = INT_MAX, mstSet[i] = 0;
  key[0] = 0;
  parent[0] = -1;
  for (int count = 0; count < n-1; count++)
  {
     int u = find_min_key(key, mstSet, n);
     mstSet[u] = 1;
     for (int v = 0; v < n; v++)
       if (graph[u][v] && mstSet[v] == 0 && graph[u][v] <  key[v])
          parent[v]  = u, key[v] = graph[u][v];
  }
  print_prim_mst(parent, n, graph);
}

int main(int argc, char *argv[])
{
  FILE *fp = NULL;
  if (argc!=2)
  {
    printf("Insufficient arguments. Run the program with file containing the input as argument\n");
  }
  else
  {
    fp = fopen(argv[1],"r");
    if (!fp)
    {
        printf("\nERROR: Unable to read file %s\n",argv[1]);
        return 1;
    }
    else
    {
      int n, m;
      fscanf(fp, "%d %d", &n, &m);
      int i, j;
      int mat0[n][n];
      int mat1[n][n];
      for (i=0; i<n; i++)
      {
        for (j=0; j<n; j++)
        {
          mat0[i][j] = 0;
          mat1[i][j] = 0;
        }
      }
      int u,v,w;
      for (i=0; i<m; i++)
      {
        fscanf(fp, "%d %d %d", &u, &v, &w);
        mat0[u][v] = w;
        mat0[v][u] = w;
      }
      min_spanning_tree_prim(n, mat0);
      fclose(fp);
    }
  }
  return 0;
}
