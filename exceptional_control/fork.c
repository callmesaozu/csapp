
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

int main()
{
	pid_t pid;
    int x = 1;
    
    pid  = Fork();
    if(pid == 0)
    {
    	printf("child : x = %d\n", ++x);
    	sleep(1);
    	exit(0);
    }
    
    int stat;
    waitpid(pid, &stat, 0);
    printf("is process %d stopped normally? %d\n", pid, WIFEXITED(stat));
    
    printf("parent: x = %d\n", --x);
    exit(0);    
}
