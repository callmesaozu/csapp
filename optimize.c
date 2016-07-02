#include <stdio.h>
int counter = 0;

int main()
{
	printf("counter++ = %d\n", f1());
	printf("counter  = %d\n", counter);
	printf("c++ = %d\n", f2());
	printf("counter  = %d\n", counter);
	printf("func1 = %d\n", func1());
	printf("counter  = %d\n", counter);
	printf("func2 = %d\n", func2());
	printf("counter  = %d\n", counter);
	return 0;
}


int f1()
{
	return counter++;//可见C++是先返回C,再++，++C则相反
}

int f2()
{
	return ++counter;
}

int func1()
{
	return f1()+f1() +f1()+f1();
}

int func2()
{
	return 4 * f1();
}

