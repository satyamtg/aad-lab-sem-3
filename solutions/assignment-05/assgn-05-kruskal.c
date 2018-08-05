#define MAX 100
#include<stdio.h>
struct graph
{
	int u;
	int v;
	int w;
	int p;
	int rank;
}M[MAX],T[MAX];

void link(int x,int y)
{
    if(M[x].rank>M[y].rank)
        M[y].p=x;
    else
        M[x].p=y;
    if(M[x].rank==M[y].rank)
        M[y].rank=M[y].rank+1;
}

int find_set(int x)
{
    if(x!=M[x].p)
        M[x].p=find_set(M[x].p);
    return(M[x].p);
}

void make_union(int x,int y)
{
    link(find_set(x),find_set(y));
}

void make_set(int x)
{
    M[x].p=x;
    M[x].rank=0;
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
			int n,m,i,j,temp,c=0,k,ctr=0,sum=0;
			fscanf(fp, "%d %d", &n, &m);
			for(i=0;i<m;i++)
			{
				fscanf(fp, "%d %d %d", &M[i].u, &M[i].v, &M[i].w);
			}
			for(i=0;i<n;i++)
			{
				make_set(i);
			}
			for(i=0;i<m;i++)
			{
				for(j=i+1;j<m;j++)
				{
					if(M[i].w>M[j].w)
					{
						temp=M[i].w;
						M[i].w=M[j].w;
						M[j].w=temp;

						temp=M[i].u;
						M[i].u=M[j].u;
						M[j].u=temp;

						temp=M[i].v;
						M[i].v=M[j].v;
						M[j].v=temp;
					}
				}
			}
			for(i=0;i<m;i++)
		    {
		        if(find_set(M[i].u)!=find_set(M[i].v))
		        {
		            T[ctr].u=M[i].u;
		            T[ctr].v=M[i].v;
		            T[ctr].w=M[i].w;
		            ctr++;
		            make_union(M[i].u,M[i].v);
		        }
		    }
		    for(i=0;i<ctr;i++)
		        sum+=T[i].w;
		    for(i=0;i<ctr;i++)
		    {
		        printf("%d %d %d\n",T[i].u,T[i].v,T[i].w);
		    }
		    printf("%d\n",sum);
				fclose(fp);
		}
	}
return 0;
}
