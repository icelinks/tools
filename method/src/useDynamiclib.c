#include<stdio.h>
#include<stdlib.h>
#include<dlfcn.h>

int main()
{
	char *filename = "./libadd.so";
	void *handle;
	int (*add)(int,int);

	handle = dlopen(filename,RTLD_LAZY);
	if(!handle)
	{
		fprintf(stderr,"%s\n",dlerror());
		return -1;
	}

	add = dlsym(handle,"add");
	if(!add)
	{
		fprintf(stderr,"%s\n",dlerror());
		return -1;
	}
	
	printf("The answer is %d\n",add(3,4));

	if(dlclose(handle)<0)
	{
		fprintf(stderr,"%s\n",dlerror());
		return -1;
	}

	return 0;
}

