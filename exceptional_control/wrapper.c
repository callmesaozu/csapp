#include <stdio.h> 
#include <unistd.h>
#include <errno.h>  
#include <sys/types.h>


//int errno;
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
	if((pid = fork()) < 0)
	{
		fprintf(stderr, "fork error: %s\n", strerror(errno));
		exit(0);
	}
	if((pid = fork()) < 0)
	{
		unix_error("fork error");
	}
	pid = Fork();
//	int i;  
/*    for(i = 0; i < 140; ++i)  */
/*    {  */
/*        errno = i;  */
/*        printf("errno %d :\t\t%s\n",i,strerror(errno));  //这个会引起段错误*/
/*    } */
	int i;
	i = 3;
	
	unsigned int p = getpid();
	unsigned int pp = getppid();
	printf("the process %u's child process is %u\n", pp, p);
	
	if(pid > 0)
	{
		printf("in process %d, i = %d\n", (int)pid, ++i);	
	}
		if(pid == 0)
	{
		printf("in process %d, i = %d\n", (int)pid, --i);
		exit(0);
	}	
	return 0;
}
