#include <stdlib.h>

int main()
{
	printf("enviroment pwd = %s\n",getenv("PWD"));
	setenv("PWD", "/home/lord/code/csapp/link", 1);
	printf("now the pwd = %s\n", getenv("PWD"));
	
	write(1, "hello, world\n", 13);
	//1是stdout, 2是stderr,详见唯知笔记
	//第二个参数是要写的字节序列
	//第三个参数是要写的字节数
	//return 0;
	exit(0); //exit(0);会有警告信息，但return不会
}
