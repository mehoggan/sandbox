#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ftw.h>

/*
	This function is called from the ftw function which
*/ 
int list(const char* name, const struct stat* status, int type)
{
	if(type == FTW_D)
		printf("%s\n", name);
	
	return 0;
}

int main(int argc, char* argv[])
{
	int list(const char*, const struct stat *, int);
	
	if(argc == 1)
		ftw(".", list, 1);
	else
		ftw(argv[1], list, 1);
}
