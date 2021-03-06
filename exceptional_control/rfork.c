//休眠父进程与子进程以随机时间，以暴露竞争
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#define MAX_SLEEP 100000

#define CONVERT(val) (((double)val)/(double)RAND_MAX)

pid_t Fork(void)
{

/*struct timeval */
/*{*/
/*	time_t      tv_sec;     // seconds */
/*	suseconds_t tv_usec;    // microseconds */
/*};*/

	static struct timeval time;
	unsigned bool, secs;	//
	pid_t pid;
	
	gettimeofday(&time, NULL);
	srand(time.tv_usec);	 //将time.tv_usec作为种子
	
	unsigned test;
	
	test = (unsigned)(CONVERT(rand()) + 0.5);
	bool = (unsigned)(CONVERT(rand()) + 0.5);	//前者在[0-1]之间均匀分布，总是向下取整，unsigned之后是0，+0.5后[0.5, 1.5],
	secs = (unsigned)(CONVERT(rand()) * MAX_SLEEP);
	
	if((pid = fork()) < 0)
		return pid;
	
	if(pid == 0)
	{
		if(bool)	//抛硬币决定谁睡眠
		{
			usleep(secs);
		}
	}
	else
	{
		if(!bool)
		{
			usleep(secs);
		}
	}
	
	return pid;
}

#include <errno.h>
#include <signal.h>
#define MAXBUF 8192

void handler2(int sig)
{
	pid_t pid;
	
	while((pid = waitpid(-1, NULL, 0)) > 0)
	{
		printf("Handler reaped child %d\n", (int)pid);	
	}
	if(errno != ECHILD)
	{
		printf("waitpid error\n");
		exit(0);
	}
		
	sleep(2);
	return;
} 

int main()
{
	int i, n;
	char buf[MAXBUF];
	
	signal(SIGCHLD, handler2);

	
	for(i = 0; i < 3; i++)
	{
		if(Fork() == 0)
		{
			printf("Hello from child %d\n", (int)getpid());
			sleep(1);
			exit(0);
		}
	}

	if((n = read(STDIN_FILENO, buf,sizeof(buf))) < 0)				//在这种系统中，当read被中断后，将返回用户一个错误条件，并设置errno = EINTR
	{
		exit(0);
	}
	
	printf("Parent processing input\n");
	while(1)
	{
		;
	}
	exit(0);
}


{
	{
		__jmpbuf = 
			{
				0, 
				-5367462688798308511, 
				4200976, 
				140737488347984, 
				0, 
				0, 
				-5367462688792017055, 
				5367462138855524193
			}, 
		__mask_was_saved = 0,
		__saved_mask = 
			{
				__val = 
					{
						0 <repeats 16 times>
					}
			}
	}
}

