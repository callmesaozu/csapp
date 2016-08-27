#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//*argv[] = (*argv)[]

int main(int argc, char **argv, char **envp)
{
	//const char filename[6] = "./fork";
	char *test = "name\n";
	printf("%s", test);
	printf("the envps are as follows: \n");

	//printf("%s\n", envp[1]);
	char *ec = envp[0];
	int i = 0;
	while(ec)
	{
		printf("\t");
		printf("%s\n", ec);
		i++;
		ec = envp[i];
		//ec = ;
	}
	
	ec = argv[0];
	i = 0;
	printf("the argvs are as follows: \n");
	while(ec)
	{
		printf("\t");
		printf("%s\n", ec);
		i++;
		ec = argv[i];
		//ec = ;
	}
	
	
	printf("running fork...\n");
	i = execve("./fork", argv, envp);
	printf("status = %d\n", i);
	
	printf("process fork is exited\n");
	

	return 0;
}
