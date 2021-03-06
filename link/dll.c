#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int x[2] = {1, 2};
int y[2] = {3, 4};
int z[2];

int main()
{
	void *handle;
	void (*addvec)(int *, int *, int *, int);
	char *error;
	
	//动态加载包含addvec()的共享库
	handle = dlopen("./libvector.so", RTLD_LAZY);
	if(!handle)
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}
	
	//获得一个指向刚才加载的addvec()的指针
	addvec = dlsym(handle, "addvec");
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", error);
		exit(1);
	}
	
	//现在可以像其他函数一样调用addvec()函数了
	addvec(x, y, z, 2);
	printf("z = [%d, %d]\n", z[0], z[1]);
	
	//卸载共享库
	if(dlclose(handle) < 0)
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}
	return 0;
}
