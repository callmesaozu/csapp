#include <stdio.h>
int foo(int A[], int m)
{
	int i = 1;
	int j;
	for(j = 0; j < m; ++j)
	{
		//循环的步长越短，空间局部性就越好
		//局部性越好的程序通常运行越快
		i += A[j];
		A[j] = 1;
	}
	return i;
}

int sumarray3d(int a[N][N][N])
{
	int i,j,k, sum = 0;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			for(k = 0; k < N; k++)
			{
				sum += a[k][i][j];//sum += a[i][j][k]比sum += a[k][i][j]快;
			}
		}
	}
	return sum;
}
int main()
{
	int A[1000];
	int x;
	x = foo(A, 1000);
	printf("x = %d\n", x);
	x = foo(A, 1000);
	printf("x = %d\n", x);
	return 0;
}
