#include "csapp.h"

/*void handler(int sig)*/
/*{*/
/*	static int beeps = 0;	//忘了第七章的内容了，static变量是在.data段中的*/
/*	printf("BEEP\n");*/
/*	if(++beeps < 5)*/
/*	{*/
/*		Alarm(1);*/
/*	}*/
/*	else*/
/*	{*/
/*		printf("BOOM!\n");*/
/*		exit(0);*/
/*	}*/
/*}*/

/*void handler(int sig)*/
/*{*/
/*	printf("Caught SIGINT\n");*/
/*	exit(0);*/
/*}*/

/*unsigned int snooze(unsigned int secs)*/
/*{*/
/*	unsigned int rt = sleep(secs);*/
/*	printf("slept for %u of %u secs\n", secs - rt, secs);*/
/*	return rt;*/
/*}*/

/*void handler(int sig)*/
/*{*/
/*	return;*/
/*}*/



/*pid_t pid;*/
/*int counter = 2;*/

/*void handler1(int sig)*/
/*{*/
/*	counter = counter - 1;*/
/*	printf("%d", counter);*/
/*	fflush(stdout);*/
/*	exit(0);*/
/*}*/


jmp_buf buf;
int error1 = 0;
int error2 = 1;

void foo(void), bar(void);

int main(int argc, char *argv[], char *envp[])
{
/*	char *s;*/
/*	FILE *fp;*/
/*	fp = fopen("./test.rag", "rt");*/
/*	char *buf = fgets(s, MAXLINE, fp);	//从stdin输入最多10-1个字符到buf和s中,当遇到EOF时就停止*/
/*	printf("now the buf is %s\n", buf);*/
/*	printf("now the s is %s\n", s);*/
/*	*/
/*	char *q = strchr(s, '程');*/
/*	printf("%s\n", q);*/
	
	//int c;
	//while((c = fgetc(fp)) != EOF )
	//	putchar(c);		//putchar,将c当做字符输出

	
	
/*	char ss[10];*/
/*	fgets(ss, 10, stdin);	*/
/*	if(feof(stdin))*/
/*	{*/
/*		printf("the end of file\n");*/
/*		exit(0);*/
/*	}*/
/*	printf("end \n");*/
/*	fclose(fp);*/


/*	char * s= "Significance Testing .......................................................................................... 376";*/
/*	printf("%s\n", s);*/
/*	char * delim;*/
/*	delim = strchr(s, 'T');*/
/*	printf("%s\n", delim);*/

/*	pid_t pd;*/
/*	pd = getpgrp();*/
/*	printf("the process group id = %d\n", pd);*/
/*	pd = getpid();*/
/*	printf("the process id = %d\n", pd);*/
/*	if(setpgid(0, 0) < 0)*/
/*	{*/
/*		printf("change pgid error\n");*/
/*		exit(0);*/
/*	}*/
/*	printf("now the pgid is changed.\n");*/
/*	pd = getpgrp();*/
/*	printf("the process group id = %d\n", pd);*/
/*	pd = getpid();*/
/*	printf("the process id = %d\n", pd);*/

/*	pid_t pid;*/
/*	*/
/*	if((pid = Fork()) == 0)*/
/*	{*/
/*		printf("child process puased...\n");*/
/*		Pause();*/
/*		printf("control should never reach here!\n");*/
/*		exit(0);*/
/*	}*/
/*	sleep(2);*/
/*	Kill(pid, SIGKILL);*/
/*	printf("child process %d is killed.\n", pid);*/

/*	Signal(SIGALRM,handler);	//安装SIGALRM handler*/
/*	Alarm(1);		//next alarm will be delivered in 1s*/
/*	*/
/*	while(1)*/
/*	{*/
/*		; //signal handler returns control here each time;*/
/*	}*/

/*	if((signal(SIGINT, handler)) == SIG_ERR)*/
/*	{*/
/*		unix_error("signal error");*/
/*	}*/
/*	*/
/*	pause();	//等待直到接收信号*/

	//8.7
/*	unsigned int rt = (unsigned) (*argv[1]) - '0';*/
/*	putchar(rt);*/
/*	printf("rt = %u\n", rt);*/
/*	if((signal(SIGINT, handler)) == SIG_ERR)*/
/*		unix_error("signal error");*/
/*		*/
/*	snooze(rt);*/
	
/*	//还是书上的代码好*/
/*	if(argc != 2)*/
/*	{*/
/*		fprintf(stderr, "usage: %s <secs>\n", argv[0]);*/
/*		exit(0);*/
/*	}*/
/*	*/
/*	if((signal(SIGINT, handler)) == SIG_ERR)*/
/*		unix_error("signal error\n");*/
/*		*/
/*	(void) snooze(atoi(argv[1]));*/
/*	exit(0);*/



/*	signal(SIGUSR1, handler1);*/
/*	*/
/*	printf("%d", counter);*/
/*	fflush(stdout);*/
/*	*/
/*	if((pid = fork()) == 0)*/
/*	{*/
/*		while(1){};*/
/*	}*/
/*	*/
/*	kill(pid, SIGUSR1);*/
/*	waitpid(-1, NULL, 0);*/
/*	counter = counter + 1;*/
/*	printf("%d", counter);*/
/*	printf("\n");*/
/*	exit(0);*/

	int rc;
	
	rc = setjmp(buf);
	if(rc == 0)
		foo();
	else if (rc == 1)
		printf("Detected an error1 condition in foo\n");
	else if (rc == 2)
		printf("Detected an error2 condition in foo\n");
	else
		printf("Unknown error condition in foo\n");
		
	
	if(!sigsetjmp(buf, 2))	//如果直接返回，则sigsetjmp返回0
		printf("dsad\n");
	exit(0);
}

void foo(void)
{
	if(error1)
	{
		longjmp(buf, 1);
	}
	bar();
}

void bar(void)
{
	if(error2)
	{
		longjmp(buf, 2);
	}
}


