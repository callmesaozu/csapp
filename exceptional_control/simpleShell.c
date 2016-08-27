/*q✗ gcc -o simpleShell simpleShell.c csapp.c -lpthread */

/*该shell并不回收它的子进程*/

#include "csapp.h"

#define MAXARGS 128

void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);

int main()
{
	char cmdline[MAXLINE];
	
	while(1)
	{
		printf("> ");
		Fgets(cmdline, MAXLINE, stdin);
		if(feof(stdin))	//如果输入的长度超过MAXLINE，退出
		{
			exit(0);
		}
		
		eval(cmdline);
	}
}

void eval(char *cmdline)
{
	char *argv[MAXARGS];
	char buf[MAXLINE];
	int bg;
	pid_t pid;
	
	strcpy(buf, cmdline);	//cmdline -> buf
	bg = parseline(buf, argv);
	if(argv[0] == NULL)
		return;				//忽略空行
		
	if(!builtin_command(argv))
	{
		if((pid = Fork()) == 0)
		{
			if(execve(argv[0], argv, environ) < 0)	//如果运行失败
			{
				printf("%s: Command not found.\n", argv[0]);
			}
		}
		
		if(!bg)
		{
			int status;
			if(waitpid(pid, &status, 0) < 0)	//如果进程不存在
			{
				unix_error("waitfg: waitpid error");
			}
		}
		else
		{
			printf("%d %s", pid, cmdline);
		}
	}
	
	return;
}

int builtin_command(char **argv)
{
	if(!strcmp(argv[0], "quit"))
		exit(0);
	if(!strcmp(argv[0], "&"))
		return 1;
	return 0;
}

//解析一个输入行
int parseline(char *buf, char **argv)
{
	char *delim;
	int argc;
	int bg;
	
	buf[strlen(buf) - 1] = ' ';	//用空格替换行尾的换行符
	while(*buf && (*buf == ' '))//忽略行首的空格
		buf++;
		
	argc = 0;
	while((delim = strchr(buf, ' ')))	//strchr返回一个指向第一次出现‘ ’的指针
	{
		argv[argc++] = buf;
		*delim = '\0';
		buf = delim + 1;
		while(*buf && (*buf == ' '))
			buf++;
	}
	
	argv[argc] = NULL;
	
	if(argc == 0)
	{
		return 1;
	}
	
	if((bg = (*argv[argc - 1] == '&')) != 0)	//如果最后一个参数的首字母为'&',则将该参数置为空, 并且bg = 1
		argv[--argc] = NULL;
	
	return bg;
}
