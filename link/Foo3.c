#include <stdio.h>

void f(void);

int x = 15213;

int main()
{
	f();
	printf("x = %d\n", x);//x = 15212
	return 0;
}

