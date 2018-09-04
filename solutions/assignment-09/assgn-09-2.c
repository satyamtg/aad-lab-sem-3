#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void print_topological_order(int v, int *finishtime)
{
	int i, j;
	printf("The topological order of the vertices are: \n\n");
	for(i = 2*v, j=0; i>=0; i--)
	{
		if (finishtime[i]!= -1)
		{
			if(j<v-1)
			{
				printf("%d-", finishtime[i]);
				j++;
			}
			else
			{
				printf("%d", finishtime[i]);
			}
		}
	}
	printf("\n");
}

void dfs_visit(int v, int **graph, int *discoverytime, int *finishtime, int *t, int start_v)
{
	*t = *t + 1;
	int i;
	discoverytime[start_v]=*t;
	for(i = 0; i < v; i++)
	{
		if(graph[start_v][i]!=INT_MAX && discoverytime[i]==-1)
		{
			dfs_visit(v, graph, discoverytime, finishtime, t, i);
		}
	}
	*t = *t + 1;
	finishtime[*t]=start_v;
}

void dfs_traverse(int v, int **graph, int *discoverytime, int *finishtime)
{
	int i;
	int t = 0;
	for(i = 0; i<v; i++)
	{
		discoverytime[i]=-1;
	}
	for(i = 0; i<(2*v + 1); i++)
	{
		finishtime[i]=-1;
	}
	for(i = 0; i<v; i++)
	{
		if(discoverytime[i]==-1)
		{
			dfs_visit(v, graph, discoverytime, finishtime, &t, i);
		}
	}
	print_topological_order(v, finishtime);
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
			int dv = 2*v +1;
			int discoverytime[v], finishtime[dv];
			dfs_traverse(v, graph, discoverytime, finishtime);
			fclose(fp);
			return 0;
		}
	}
}
