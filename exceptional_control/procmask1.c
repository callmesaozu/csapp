#include "csapp.h"

void handler(int sig)
{
	pid_t pid;
	while((pid = waitpid(-1, NULL, 0)) > 0)	//显然，这是父进程调用deletejob， 而信号是子进程一结束就传给父进程的，而这里是要回收所有的僵尸进程
		deletejob(pid);
	if(errno != ECHILD)
		unix_error("waitpid error");
}

/*int main(int argc, char **argv)*/
/*{*/
/*	int pid;*/
/*	*/
/*	Signal(SIGCHLD, handler);*/
/*	initjobs();*/
/*	*/
/*	while(1)*/
/*	{*/
/*		if((pid = Fork()) == 0)*/
/*		{*/
/*			Execve("/bin/date", argv, NULL);*/
/*		}*/
/*		*/
/*		addjob(pid);*/
/*	}*/
/*	*/
/*	exit(0);*/
/*}*/

//上例中，deletejob和addjob存在竞争关系，如果子进程在addjob之前结束，则deletejob不做任何操作，而下一步addjob会将已结束的子进程id添加到job中，导致该id永久驻留在job中
//下面是解决办法
int main(int argc, char **argv)
{
	int pid;
	sigset_t mask;
	
	Signal(SIGCHLD, handler);
	initjobs();
	
	while(1)
	{
		//在创建子进程之前先将信号阻塞
		Sigemptyset(&mask);
		Sigaddset(&mask, SIGCHLD);
		Sigprocmask(SIG_BLOCK, &mask, NULL);
		if((pid = Fork()) == 0)
		{
			//子进程中，由于子进程继承了父进程的阻塞集合，在调用Execve之前还要解除子进程的被阻塞信号
			Sigprocmask(SIG_UNBLOCK, &mask, NULL);
			Execve("/bin/date", argv, NULL);
		}
		
		addjob(pid);
		//添加完pid后，再解除阻塞，这样就不会在子进程退出之前就delete
		Sigprocmask(SIG_UNBLOCK, &mask, NULL);
	}
	
	exit(0);
}
