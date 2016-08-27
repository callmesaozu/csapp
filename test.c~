#include <stdio.h>

typedef struct 
{
	char *a;
	short b;
	char c;
	char d;
	double e;
	long long f;
	float g;
	void *h;
} U3;

typedef struct 
{
	double a;
	long long b;
	float c;
	char *d;
	void *e;
	short f;
	char g;
	char h;
} U4;

int func(int x, int *y)
{
	printf("x = %d, *y = %d\n", x, *y);
	return 0;
}


int main()
{
	short *p;
	short d = 3;
	p = &d;
	printf("p = %u\n", (int *)p);
	printf("(int *)p + 7 = %u\n", (int *)p + 7);
	printf("(int *)(p + 7) = %u\n", (int *)(p + 7));
	printf("sizeof p = %d\n", (int)sizeof(p));
	
	int (*fp)(int , int *);
	fp = func;
	int y = 1;
	int result = fp(3, &y);
	return 0;
}

