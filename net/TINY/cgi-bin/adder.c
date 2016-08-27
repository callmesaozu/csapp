#include "../csapp.h"

int main(void)
{
	char *buf, *p;
	char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
	int n1 = 0, n2 = 0;
	
	if ((buf = getenv("QUERY_STRING")) != NULL)	//buf = 15000&213
	{
		p = strchr(buf, '&');					//p = &213
		*p = '\0';								//buf = 15000\0213,但我自己测试会引发段错误
		strcpy(arg1, buf);						//buf -> arg1 15000\0
		strcpy(arg2, p+1);						//buf -> arg2 213\0
		n1 = atoi(arg1);						//n1 = 15000
		n2 = atoi(arg2);						//n2 = 213
	}
	
	sprintf(content, "Welcome to add.com: ");	//将"Welcome to add.com: "写到content中
	sprintf(content, "%sTHE Internet addition portal.\r\n<p>", content);
	sprintf(content, "%sThe answer is: %d + %d = %d\r\n<p>", content, n1, n2, n1 + n2);
	sprintf(content, "%sThanks for visiting!\r\n", content);
	
	printf("Content-length: %d\r\n", (int)strlen(content));
	printf("Content-type: text/html\r\n\r\n");
	printf("%s", content);
	fflush(stdout);
	exit(0);
}
