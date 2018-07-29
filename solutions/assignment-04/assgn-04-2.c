#define N 4
#define MAX 100
#define MIN 0

#include <stdio.h>
#include <stdlib.h>

int to_1d_array(int col, int i, int j)
{
	return(col*i+j);
}

void add_square_matrix(int *a, int *b, int *c, int n, int acol, int bcol, int col)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			*(c+col*i+j) = *(a+acol*i+j) + *(b+bcol*i+j);
		}
	}
}

void sub_square_matrix(int *a, int *b, int *c, int n,int acol, int bcol, int col)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			*(c+col*i+j) = *(a+acol*i+j) - *(b+bcol*i+j);
		}
	}
}

void display_square_matrix(int *a,int n)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			printf("%d ", *(a+i*n+j));
		}
		printf("\n");
	}
}


void matrix_mul(int *a, int *b,int *c, int n, int acolsize, int bcolsize, int colsize)
{
	if(n==1)
	{
		*(c) =*(a) * *(b);
	}
	else
	{
		int s1[n/2][n/2];
		int s2[n/2][n/2];
		int s3[n/2][n/2];
		int s4[n/2][n/2];
		int s5[n/2][n/2];
		int s6[n/2][n/2];
		int s7[n/2][n/2];
		int s8[n/2][n/2];
		int s9[n/2][n/2];
		int s10[n/2][n/2];
		sub_square_matrix(b+to_1d_array(bcolsize, 0, n/2), b+to_1d_array(bcolsize, n/2, n/2), (int *)s1, n/2, bcolsize, bcolsize, n/2);
		add_square_matrix(a+to_1d_array(acolsize, 0, 0), a+to_1d_array(acolsize, 0, n/2), (int *)s2, n/2, acolsize, acolsize, n/2);
		add_square_matrix(a+to_1d_array(acolsize, n/2, 0), a+to_1d_array(acolsize, n/2, n/2), (int *)s3, n/2, acolsize, acolsize, n/2);
		sub_square_matrix(b+to_1d_array(bcolsize, n/2, 0), b+to_1d_array(bcolsize, 0, 0), (int *)s4, n/2, bcolsize, bcolsize, n/2);
		add_square_matrix(a+to_1d_array(acolsize, 0, 0), a+to_1d_array(acolsize, n/2, n/2), (int *)s5, n/2, acolsize, acolsize, n/2);
		add_square_matrix(b+to_1d_array(bcolsize, 0, 0), b+to_1d_array(bcolsize, n/2, n/2), (int *)s6, n/2, bcolsize, bcolsize, n/2);
		sub_square_matrix(a+to_1d_array(acolsize, 0, n/2), a+to_1d_array(acolsize, n/2, n/2), (int *)s7, n/2, acolsize, acolsize, n/2);
		add_square_matrix(b+to_1d_array(bcolsize, n/2, 0), b+to_1d_array(bcolsize, n/2, n/2), (int *)s8, n/2, bcolsize, bcolsize, n/2);
		sub_square_matrix(a+to_1d_array(acolsize, 0, 0), a+to_1d_array(acolsize, n/2, 0), (int *)s9, n/2, acolsize, acolsize, n/2);
		add_square_matrix(b+to_1d_array(bcolsize, 0, 0), b+to_1d_array(bcolsize, 0, n/2), (int *)s10, n/2, bcolsize, bcolsize, n/2);
		int p1[n/2][n/2];
		int p2[n/2][n/2];
		int p3[n/2][n/2];
		int p4[n/2][n/2];
		int p5[n/2][n/2];
		int p6[n/2][n/2];
		int p7[n/2][n/2];
		matrix_mul(a+to_1d_array(acolsize, 0, 0), (int *)s1, (int *)p1, n/2, acolsize, n/2, n/2);
		matrix_mul((int *)s2, b+to_1d_array(bcolsize, n/2, n/2), (int *)p2, n/2, n/2, bcolsize, n/2);
		matrix_mul((int *)s3, b+to_1d_array(bcolsize, 0, 0), (int *)p3, n/2, n/2, bcolsize, n/2);
		matrix_mul(a+to_1d_array(acolsize, n/2, n/2), (int *)s4, (int *)p4, n/2, acolsize, n/2, n/2);
		matrix_mul((int *)s5, (int *)s6, (int *)p5, n/2, n/2, n/2, n/2);
		matrix_mul((int *)s7, (int *)s8, (int *)p6, n/2, n/2, n/2, n/2);
		matrix_mul((int *)s9, (int *)s10, (int *)p7, n/2, n/2, n/2, n/2);
		add_square_matrix((int *)p5, (int *)p4, c+to_1d_array(colsize, 0, 0), n/2, n/2, n/2, colsize);
		sub_square_matrix(c+to_1d_array(colsize, 0, 0), (int *)p2, c+to_1d_array(colsize, 0, 0), n/2, colsize, n/2, colsize);
		add_square_matrix(c+to_1d_array(colsize, 0, 0), (int *)p6, c+to_1d_array(colsize, 0, 0), n/2, colsize, n/2, colsize);
		add_square_matrix((int *)p1, (int *)p2, c+to_1d_array(colsize, 0, n/2), n/2, n/2, n/2, colsize);
		add_square_matrix((int *)p3, (int *)p4, c+to_1d_array(colsize, n/2, 0), n/2, n/2, n/2, colsize);
		add_square_matrix((int *)p5, (int *)p1, c+to_1d_array(colsize, n/2, n/2), n/2, n/2, n/2, colsize);
		sub_square_matrix(c+to_1d_array(colsize, n/2, n/2), (int *)p3, c+to_1d_array(colsize, n/2, n/2), n/2, colsize, n/2, colsize);
		sub_square_matrix(c+to_1d_array(colsize, n/2, n/2), (int *)p7, c+to_1d_array(colsize, n/2, n/2), n/2, colsize, n/2, colsize);
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
	matrix_mul((int *)a, (int *)b, (int *)c, n, n, n, n);
	printf("\nResultant matrix after multiplication of the two matrices:\n\n");
	display_square_matrix((int *)c, n);
	return 0;
}
