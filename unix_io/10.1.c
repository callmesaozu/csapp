#include "../csapp.h"

int main()
{
	int fd1, fd2;
	
	fd1 = Open("foo.txt", O_RDONLY, 0);
	Close(fd1);
	fd2 = Open("baz.txt", O_RDONLY, 0);
	printf("fd2 = %d\n", fd2);
/*	printf("123\n");*/
/*	dup2(fd2, 1);	//标准输出重定向到将fd2*/
/*	char *abc;*/
/*	abc = "fd2 = ewe\n";*/
/*	Write(STDOUT_FILENO, abc, 11);*/
/*	printf("123\n");*/
	char c;
	fd1 = Open("baz.txt", O_RDONLY, 0);
	Read(fd2, &c, 1);
	Dup2(fd2, fd1);
	Read(fd1, &c, 1);
	printf("c = %c\n", c);
	exit(0);
}
