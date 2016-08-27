//按顺序回收僵尸进程

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h> 

void unix_error(char *msg)	//unix-style error
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

pid_t Fork(void)
{
	pid_t pid;
    
    if((pid = fork()) < 0)
    {
    	unix_error("Fork error");
    }
    return pid;
}

#define N 2

int main()
{
	int status, i;
	pid_t pid[N], retpid;
	
	for(i = 0; i < N; i++)
	{
		if((pid[i] = Fork()) == 0)
		{
			exit(100 + i);
		}
	}
	
	i = 0;
	while((retpid = waitpid(pid[i++], &status, 0)) > 0)	//如果waitpid正常执行
	{
		if(WIFEXITED(status))
		{
			printf("child %d terminated normally with exit status = %d\n", 
					retpid, WEXITSTATUS(status));
		}
		else
		{
			printf("child %d terminated abnormally\n", retpid);
		}
	}
	
	if(errno != ECHILD)
	{
		unix_error("waitpid error");
	}
	
	exit(0);
}
