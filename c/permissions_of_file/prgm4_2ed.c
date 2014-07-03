//-l long format, displaying Unix file types, permissions, number of hard links, owner, group, size, date, and filename
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

#define BUFSZ 1024

int oct[9] = {	0400, 0200, 0100,
		0040, 0020, 0010,
		0004, 0002, 0001 };

int main(int argc, char* argv[])
{
	int x;
	int j;
	struct stat statbuf;
	struct passwd *pwd;
	
	for(x = 1; x < argc; x++)
	{
		pwd = getpwuid(getuid());
		char* usr_home = pwd->pw_dir;
		strcat(strcat(usr_home, "/"), argv[x]);
		//printf("%s's home directory, %s\n", pwd->pw_name, usr_home);
		if((stat(argv[x], &statbuf)) != -1)
		{
			printf("FILE %s\n", argv[x]);
			if(statbuf.st_uid == getuid())
			{
				//printf("%s has user access\n", argv[x]);
				printf("user: ");
				if(statbuf.st_mode & 0400)
				{
					printf("read ");
				}
				if(statbuf.st_mode & 0200)
				{
					printf("write ");
				}
				if(statbuf.st_mode & 0100)
				{
					printf("execute");
				}
				printf("\n");
			}
			if(statbuf.st_gid == getgid())
			{
				//printf("%s has group access\n", argv[x]);
				printf("group: ");
				if(statbuf.st_mode & 0040)
                                {
                                        printf("read ");
                                }
                                if(statbuf.st_mode & 0020)
                                {
                                        printf("write ");
                                }
                                if(statbuf.st_mode & 0010)
                                {
                                        printf("execute");
                                }

				printf("\n");
			}
			if(statbuf.st_gid != getgid() && statbuf.st_uid != getuid())
			{
				//printf("%s has other access\n", argv[x]);
				printf("other: ");
				if(statbuf.st_mode & 0004)
                                {
                                        printf("read ");
                                }
                                if(statbuf.st_mode & 0002)
                                {
                                        printf("write ");
                                }
                                if(statbuf.st_mode & 0001)
                                {
                                        printf("execute");
                                }
				printf("\n");
			}
		}
	}
}







































