#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

int getmax(int a, int b)
{
	if(a>b)
	{return a;}
	else
	{return b;}
}

void getlcs( char *str1, char *str2, int m, int n )
{
   int L[m+1][n+1];
   for (int i=0; i<=m; i++)
   {
     for (int j=0; j<=n; j++)
     {
       if (i == 0 || j == 0)
         L[i][j] = 0;
       else if (str1[i-1] == str2[j-1])
         L[i][j] = L[i-1][j-1] + 1;
       else
         L[i][j] = getmax(L[i-1][j], L[i][j-1]);
     }
   }
   int index = L[m][n];
   char lcs[index+1];
   lcs[index] = '\0';
   int i = m, j = n;
   while (i > 0 && j > 0)
   {
      if (str1[i-1] == str2[j-1])
      {
          lcs[index-1] = str1[i-1];
          i--; j--; index--;
      }
      else if (L[i-1][j] > L[i][j-1])
         i--;
      else
         j--;
   }
   printf("String 1: %s\nString 2: %s\nOutput :%lu(%s)\n",str1, str2, strlen(lcs), lcs );
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
			char str1[1000];
			char str2[1000];
      fscanf(fp, "%s\n", str1);
      fscanf(fp, "%s\n", str2);
      int m = 0, n = 0, i;
			m = strlen(str1);
			n = strlen(str2);
			getlcs(str1, str2, m, n);
			fclose(fp);
			return 0;
		}
	}
}
