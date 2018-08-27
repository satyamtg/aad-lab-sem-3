#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void print_parent_recursive(int *parent, int dest, int checkvalue)
{
	if(dest == -1)
	{
		return;
	}
	print_parent_recursive(parent, parent[dest], checkvalue);
	if(dest==checkvalue)
	{
		printf("%d", dest);
	}
	else
	{
		printf("%d-", dest);
	}
}

int get_min_vertex(int *shortest_path, int *finalized_vertex, int v)
{
	int min = INT_MAX;
	int i, min_vertex;
	for(i=0; i<v; i++)
	{
		if(finalized_vertex[i]==0 && shortest_path[i]<=min)
		{
			min=shortest_path[i];
			min_vertex = i;
		}
	}
	return min_vertex;
}

void print_result(int *shortest_path, int v, int *parent)
{
	int i;
	printf("%15s    %15s    %15s\n", "Vertex", "Min. Distance", "Shortest Path");
	for(i = 0; i < v; i++)
	{
		if(shortest_path[i]!=INT_MAX)
		{
			printf("%15d    %15d      ", i, shortest_path[i]);
			print_parent_recursive(parent, i, i);
			printf("\n");
		}
		else
		{
			printf("%15d    %15s      %s", i, "infinite", "unreachable");
			printf("\n");
		}
	}
}

void find_dijkstra_shortest_path(int v, int **graph, int src)
{
	int shortest_path[v];
	int finalized_vertex[v];
	int parent[v];
	int i = 0;
	int min_vertex;
	for(i = 0; i < v; i++)
	{
		shortest_path[i] = INT_MAX;
		finalized_vertex[i] = 0;
	}
	shortest_path[src] = 0;
	parent[src] = -1;
	for(i = 0; i < v; i++)
	{
		min_vertex = get_min_vertex(shortest_path, finalized_vertex, v);
		finalized_vertex[min_vertex] = 1;
		int z;
		for(z = 0; z < v; z++)
		{
			if(finalized_vertex[z] == 0 && ((shortest_path[min_vertex]+graph[min_vertex][z])<shortest_path[z]) && graph[min_vertex][z]!=0 && ((shortest_path[min_vertex]+graph[min_vertex][z])>=0))
			{
				shortest_path[z] = shortest_path[min_vertex]+graph[min_vertex][z];
				parent[z] = min_vertex;
			}
		}
	}
	print_result(shortest_path, v, parent);
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
			int v, e, **graph, i, j, s, v1, v2, w;
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
			printf("Enter source vertex :");
			scanf("%d", &s);
			find_dijkstra_shortest_path(v, graph, s);
			return 0;
		}
	}
}
