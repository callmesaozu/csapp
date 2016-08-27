#include "../csapp.h"

int main()
{
	int *array, i, n;
	
	scanf("%d", &n);
	array = (int *)Malloc(n * sizeof(int));	//利用malloc函数动态分配数组空间，比下文的max方案要好
	for(i = 0; i < n; i++)
	{
		scanf("%d", &array[i]);
	}
	exit(0);
}

/*#include "../csapp.h"*/
/*#define MAXN 15213*/

/*int array[MAXN];*/

/*int main()*/
/*{*/
/*	int i, n;*/

/*	scanf("%d", n);*/
/*	if (n > MAXN)*/
/*		app_error("Input file too big");*/
/*	for (i = 0; i < n; i++)*/
/*		scanf("%d", &array[i]);*/
/*	exit(0);*/
/*}*/
