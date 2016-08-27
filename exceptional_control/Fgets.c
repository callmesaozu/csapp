#include "Fgets.h"
#include "unix_error.h"

void unix_error(char *msg);	//unix-style error

char *Fgets(char *s, int size, FILE *stream)
{
	char *buf;
	buf = NULL;
	
	if((buf = fgets(s, size, stream)) == NULL )
	{
		unix_error("Fgets error");
	}
	
	return buf;
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
