#include <stdio.h>

void f(void);

int x = 15213;
int y = 15212;

int main()
{
	f();
	printf("x = 0x%x y = 0x%x\n", x, y);//x = 0x0 y = 0x80000000
	return 0;
}

