#include <stdio.h>

int switch_eg(int x)
{
	x = 3;
	
	return x;
}

int main()
{
	int a = 103;
	printf("switch_eg(%d) = ", a);
	switch_eg(a);
	printf("%d\n", a);
	return 0;
}

