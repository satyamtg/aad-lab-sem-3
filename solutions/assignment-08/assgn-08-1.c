#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void print_matrix(int **graph, int v)
{
	printf("The shortest-path matrix for all possible pairs: \n\n");
	int i, j;
	for(i = 0; i < v; i++)
	{
		for(j = 0; j < v; j++)
		{
			if(graph[i][j] != INT_MAX)
			{
				printf("%15d  ", graph[i][j]);
			}
			else
			{
				printf("%15s  ", "INFINITE");
			}
		}
		printf("\n");
	}
}

void mkshortest_floyd(int v, int **graph)
{
	int i, j, k;
	for(i = 0; i < v; i++)
	{
		for(j = 0; j < v; j++)
		{
			for(k = 0; k < v; k++)
			{
				if(graph[i][k]!=INT_MAX && graph[k][j]!=INT_MAX && (graph[i][j] > graph[i][k] + graph[k][j]))
				{
					graph[i][j] = graph[i][k] + graph[k][j];
				}
			}
		}
	}
	print_matrix(graph, v);
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
					graph[i][j] = INT_MAX;
				}
			}
			for(i = 0; i<e; i++)
			{
				fscanf(fp, "%d %d %d\n", &v1, &v2, &w);
				graph[v1][v2]=w;
			}
			mkshortest_floyd(v, graph);
			fclose(fp);
			return 0;
		}
	}
}
