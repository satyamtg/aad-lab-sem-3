#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void print_topological_order(int v, int *finishtime)
{
	int i, j;
	printf("The topological order of the vertices are: \n\n");
	for(i = 0, j=0; i<v; i++)
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
	printf("\n");
}

void dfs_visit(int v, int **graph, int *discoverytime, int *finishtime, int *t, int start_v, int *topoorder, int *o)
{
	*t = *t + 1;
	int i;
	discoverytime[start_v]=*t;
	for(i = 0; i < v; i++)
	{
		if(graph[start_v][i]!=INT_MAX && discoverytime[i]==-1)
		{
			dfs_visit(v, graph, discoverytime, finishtime, t, i, topoorder, o);
		}
	}
	*t = *t + 1;
	finishtime[start_v]=*t;
	*o = *o - 1;
	topoorder[*o]=start_v;
}

void dfs_traverse(int v, int **graph, int *discoverytime, int *finishtime, int *topoorder)
{
	int i;
	int t = 0;
	int o = v;
	for(i = 0; i<v; i++)
	{
		discoverytime[i]=-1;
		finishtime[i]=-1;
		topoorder[i]=INT_MIN;
	}
	for(i = 0; i<v; i++)
	{
		if(discoverytime[i]==-1)
		{
			dfs_visit(v, graph, discoverytime, finishtime, &t, i, topoorder, &o);
		}
	}
	print_topological_order(v, topoorder);
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
			int v, e, **graph, i, j, v1, v2, w = 1;
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
				fscanf(fp, "%d %d\n", &v1, &v2);
				graph[v1][v2]=w;
			}
			int discoverytime[v], finishtime[v], topoorder[v];
			dfs_traverse(v, graph, discoverytime, finishtime, topoorder);
			fclose(fp);
			return 0;
		}
	}
}
