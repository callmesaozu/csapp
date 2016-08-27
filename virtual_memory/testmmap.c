#include "../csapp.h"

int main()
{
	int *bufp;
	bufp = Mmap(NULL, 12, PROT_READ, MAP_PRIVATE|MAP_ANON, 0, 0);	//申请虚拟存储区
	int s;
	s = munmap(bufp, 12);	//删除虚拟存储区
	
	return 0;
}
