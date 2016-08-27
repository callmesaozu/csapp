#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	int i;
	
	printf("Command line arguments:\n");
	for(i = 0; argv[i] != NULL; i++)
	{
		printf("\targv[%2d]: %s\n", i, argv[i]);
	}
	
	printf("\n");
	printf("Environment variables:\n");
	for(i=0; envp[i] != NULL; i++)
	{
		printf("\tenvp[%2d]: %s\n", i, envp[i]);
	}
	
/*	int *num;*/
/*	num = malloc(sizeof(int));*/
	
	
	exit(0);
}
