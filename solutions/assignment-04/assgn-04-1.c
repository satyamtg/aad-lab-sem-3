#define N 4
#define MAX 100
#define MIN 0

#include <stdio.h>
#include <stdlib.h>

int to_1d_array(int col, int i, int j)
{
	return(col*i+j);
}

void matrix_mul(int *a, int *b,int *c, int n, int colsize)
{

	if(n==1)
	{
		*(c) =*(c)+(*(a) * *(b));
	}
	else
	{
		matrix_mul(a+to_1d_array(colsize, 0, 0), b+to_1d_array(colsize, 0, 0), c+to_1d_array(colsize, 0, 0), n/2, colsize);
		matrix_mul(a+to_1d_array(colsize, 0, n/2), b+to_1d_array(colsize, n/2, 0), c+to_1d_array(colsize, 0, 0), n/2, colsize);
		matrix_mul(a+to_1d_array(colsize, 0, 0), b+to_1d_array(colsize, 0, n/2), c+to_1d_array(colsize, 0, n/2), n/2, colsize);
		matrix_mul(a+to_1d_array(colsize, 0, n/2), b+to_1d_array(colsize, n/2, n/2), c+to_1d_array(colsize, 0, n/2), n/2, colsize);
		matrix_mul(a+to_1d_array(colsize, n/2, 0), b+to_1d_array(colsize, 0, 0), c+to_1d_array(colsize, n/2, 0), n/2, colsize);
		matrix_mul(a+to_1d_array(colsize, n/2, n/2), b+to_1d_array(colsize, n/2, 0), c+to_1d_array(colsize, n/2, 0), n/2, colsize);
		matrix_mul(a+to_1d_array(colsize, n/2, 0), b+to_1d_array(colsize, 0, n/2), c+to_1d_array(colsize, n/2, n/2), n/2, colsize);
		matrix_mul(a+to_1d_array(colsize, n/2, n/2), b+to_1d_array(colsize, n/2, n/2), c+to_1d_array(colsize, n/2, n/2), n/2, colsize);
	}
}

void display_square_matrix(int *a,int n)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			printf("%d ", *((a+i*n) + j));
		}
		printf("\n");
	}
}


int main()
{
	int c[N][N];
	int a[N][N];
	int b[N][N];
	int n = N;
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			a[i][j] = (rand() % (MAX - MIN + 1)) + MIN;
		}
	}
	for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				b[i][j] = (rand() % (MAX - MIN + 1)) + MIN;
			}
		}
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			c[i][j]=0;
		}
	}
	printf("\nRandomly generated matrix 1:\n\n");
	display_square_matrix((int *)a, n);
	printf("\nRandomly generated matrix 2:\n\n");
	display_square_matrix((int *)b, n);
	matrix_mul((int *)a, (int *)b, (int *)c, n, n);
	printf("\nResultant matrix after multiplication of the two matrices:\n\n");
	display_square_matrix((int *)c, n);
	return 0;
}
