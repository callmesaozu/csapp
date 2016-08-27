#include "../csapp.h"

/*int main(int argc, char *argv[])*/
/*{*/
/*	int *p;*/
/*	//if ((argc == 2) && ())*/
/*	struct stat buf;*/
/*	int fp = stat(argv[1], &buf);	//查stat的参数时要用man 2 stat*/
/*	printf("size: %u\n",(unsigned)buf.st_size);*/
/*	int fd = open(argv[1], 0);*/
/*	p = mmap(NULL, (size_t)buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);*/
/*	Write(1, p, (size_t)buf.st_size);*/
/*	printf("\n");*/
/*		*/
/*	return 0;*/
/*}*/

//上面是我自己的程序，下面是书本上的

void mmapcopy(int fd, int size)
{
	char *bufp;
	bufp = Mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
	Write(1, bufp, size);
	return;
}

int main(int argc, char *argv[])
{
	struct stat st;
	int fd;
	
	if(argc != 2)
	{
		printf("usage: %s <filename>\n", argv[0]);
		exit(0);
	}
	
	fd = Open(argv[1], O_RDONLY, 0);
	fstat(fd, &st);
	mmapcopy(fd, st.st_size);
	exit(0);
}

/*#include <unistd.h>*/

/*定义函数：ssize_t write (int fd, const void * buf, size_t count);*/

/*函数说明：write()会把参数buf 所指的内存写入count 个字节到参数fd 所指的文件内. 当然, 文件读写位置也会随之移动.*/

/*返回值：如果顺利write()会返回实际写入的字节数. 当有错误发生时则返回-1, 错误代码存入errno 中.*/

/*错误代码：*/
/*EINTR 此调用被信号所中断.*/
/*EAGAIN 当使用不可阻断I/O 时 (O_NONBLOCK), 若无数据可读取则返回此值.*/
/*EADF 参数fd 非有效的文件描述词, 或该文件已关闭.*/


/*#include<sys/types.h>*/
/*#include<sys/stat.h>*/
/*#include<fcntl.h>*/
/*定义函数*/
/*int open( const char * pathname, int flags);*/
/*int open( const char * pathname,int flags, mode_t mode);*/
/*函数说明*/
/*参数pathname 指向欲打开的文件路径字符串。下列是参数flags 所能使用的旗标:*/
/*O_RDONLY 以只读方式打开文件*/
/*O_WRONLY 以只写方式打开文件*/
/*O_RDWR 以可读写方式打开文件。*/
/*上述三种旗标是互斥的，也就是不可同时使用，但可与下列的旗标利用OR(|)运算符组合。*/
/*O_CREAT 若欲打开的文件不存在则自动建立该文件。*/
/*O_EXCL 如果O_CREAT 也被设置，此指令会去检查文件是否存在。文件若不存在则建立该文件，否则将导致打开文件错误。此外，若O_CREAT与O_EXCL同时设置，并且欲打开的文件为符号连接，则会打开文件失败。*/
/*O_NOCTTY 如果欲打开的文件为终端机设备时，则不会将该终端机当成进程控制终端机。*/
/*O_TRUNC 若文件存在并且以可写的方式打开时，此旗标会令文件长度清为0，而原来存于该文件的 资料也会消失。*/
/*O_APPEND 当读写文件时会从文件尾开始移动，也就是所写入的数据会以附加的方式加入到文件后面。*/
/*O_NONBLOCK 以不可阻断的方式打开文件，也就是无论有无数据读取或等待，都会立即返回进程之中。*/
/*O_NDELAY 同O_NONBLOCK。*/
/*O_SYNC 以同步的方式打开文件。*/
/*O_NOFOLLOW 如果参数pathname 所指的文件为一符号连接，则会令打开文件失败。*/
/*O_DIRECTORY 如果参数pathname 所指的文件并非为一目录，则会令打开文件失败。*/
/*参数mode 组合*/
/*此为Linux2.2以后特有的旗标，以避免一些系统安全问题。参数mode 则有下列数种组合，只有在建立新文件时才会生效，此外真正建文件时的权限会受到umask值所影响，因此该文件权限应该为（mode-umaks）。*/
/*S_IRWXU 00700 权限，代表该文件所有者具有可读、可写及可执行的权限。*/
/*S_IRUSR 或S_IREAD， 00400权限，代表该文件所有者具有可读取的权限。*/
/*S_IWUSR 或S_IWRITE，00200 权限，代表该文件所有者具有可写入的权限。*/
/*S_IXUSR 或S_IEXEC， 00100 权限，代表该文件所有者具有可执行的权限。*/
/*S_IRWXG 00070权限，代表该文件用户组具有可读、可写及可执行的权限。*/
/*S_IRGRP 00040 权限，代表该文件用户组具有可读的权限。*/
/*S_IWGRP 00020权限，代表该文件用户组具有可写入的权限。*/
/*S_IXGRP 00010 权限，代表该文件用户组具有可执行的权限。*/
/*S_IRWXO 00007权限，代表其他用户具有可读、可写及可执行的权限。*/
/*S_IROTH 00004 权限，代表其他用户具有可读的权限*/
/*S_IWOTH 00002权限，代表其他用户具有可写入的权限。*/
/*S_IXOTH 00001 权限，代表其他用户具有可执行的权限。*/
/*返回值*/
/*若所有欲核查的权限都通过了检查则返回文件描述符，表示成功，只要有一个权限被禁止则返回-1。*/
