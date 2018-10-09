#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int getmin(int a, int b)
{
  return ((a<b)?a:b);
}

void dfs_visit(int v, int **graph, int *visited, int start_v, int *parent)
{
	int i;
	visited[start_v] = 1;
	for(i = 0; i < v; i++)
	{
		if(graph[start_v][i]!=0 && visited[i]==0)
		{
			dfs_visit(v, graph, visited, i, parent);
      parent[i] = start_v;
		}
	}
}

void dfs_traverse(int v, int **graph, int *t, int *parent, int *s)
{
	int i;
  int visited[v];
	for(i = 0; i<v; i++)
	{
		visited[i] = 0;
    parent[i] = -1;
	}
  dfs_visit(v, graph, visited, *s, parent);
  parent[*s] = -1;
	for(i = 0; i<v; i++)
	{
		if(visited[i]==0)
		{
			dfs_visit(v, graph, visited, i, parent);
		}
	}
}

int checkpath(int *parent, int *s, int *t)
{
  int i;
  for(i = *t; parent[i] != -1; i=parent[i])
  {
    if(parent[i] == *s)
    {
      return 1;
    }
  }
  return 0;
}

void create_residual_graph(int **graph, int **orggraph, int v)
{
  int x, y;
  for(x = 0; x < v; x++)
  {
    for(y = 0; y < v; y++)
    {
      if(orggraph[x][y] != 0)
      {
        graph[x][y] = orggraph[x][y] - graph[y][x];
      }
    }
  }
}

int fordFulkerson(int v, int **graph, int *s, int *t)
{
  int x, y, bottleneck, i;
  int parent[v];
  int **rgraph;
  rgraph = malloc(v*sizeof(*rgraph));
  for(i=0; i<v; i++)
  {
    rgraph[i] = malloc(v*sizeof(*rgraph[i]));
  }
  for(x=0; x<v; x++)
  {
    for(y=0; y<v; y++)
    {
      rgraph[x][y] = graph[x][y];
    }
  }
  int maxflow = 0;
  dfs_traverse(v, rgraph, t, parent, s);
  while(checkpath(parent, s, t))
  {
    bottleneck = INT_MAX;
    for(x = *t; x != *s; x = parent[x])
    {
      bottleneck = getmin(bottleneck, rgraph[parent[x]][x]);
    }
    for(x = *t; x != *s; x=parent[x])
    {
      if(graph[parent[x]][x] != 0)
      {
        rgraph[x][parent[x]] = rgraph[x][parent[x]] + bottleneck;
      }
      else
      {
        rgraph[x][parent[x]] = rgraph[x][parent[x]] - bottleneck;
      }
    }
    maxflow = maxflow + bottleneck;
    create_residual_graph(rgraph, graph, v);
    dfs_traverse(v, rgraph, t, parent, s);
  }
  return maxflow;
}

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
  if (argc!=2)
  {
    printf("Insufficient arguments. Run the program with file containing the input as argument\n");
		return 1;
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
			int v, e, **graph, i, j, v1, v2, w;
			fscanf(fp, "%d %d\n", &v, &e);
			graph = malloc(v*sizeof(*graph));
			for(i=0; i<v; i++)
			{
				graph[i] = malloc(v*sizeof(*graph[i]));
			}
			for(i=0; i<v; i++)
			{
				for(j=0; j<v; j++)
				{
					graph[i][j] = 0;
				}
			}
			for(i = 0; i<e; i++)
			{
				fscanf(fp, "%d %d %d\n", &v1, &v2, &w);
				graph[v1][v2]=w;
			}
			int s, t, maxflow;
      printf("Enter source vertex :");
      scanf("%d", &s);
      printf("Enter target vertex :");
      scanf("%d", &t);
			maxflow = fordFulkerson(v, graph, &s, &t);
      printf("The maximum flow is %d\n", maxflow);
			fclose(fp);
			return 0;
		}
	}
}
