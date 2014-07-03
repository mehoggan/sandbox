//-l long format, displaying Unix file types, permissions, number of hard links, owner, group, size, date, and filename
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define BUFSZ 1024

int oct[9] = {	0400, 0200, 0100,
		0040, 0020, 0010,
		0004, 0002, 0001 };

const char perm[10] = "rwxrwxrwx";

int main(int argc, char* argv[])
{
	int x;
	int j;
	struct stat statbuf;
	struct passwd *pwd;
	struct group *grp;
	
	char* ftime;	

	for(x = 1; x < argc; x++)
	{
		char usr_perm[10];
		if(stat(argv[x], &statbuf) == -1)
		{
			printf("File \"%s\" does not exist\n", argv[x]);
			exit(0);
		}
		for(j = 0; j < 9; j++)
		{
			if(statbuf.st_mode & oct[j])
			{
				//printf("%d\n", (statbuf.st_mode & oct[j]));
				usr_perm[j] = perm[j];
			}
			else
			{
				//printf("%d\n", (statbuf.st_mode & oct[j]));
				usr_perm[j] = '-';
			}
		}


		printf("-%s.", usr_perm);
		
		printf(" %d", statbuf.st_nlink);		

		pwd = getpwuid(statbuf.st_uid);		
		printf(" %s", pwd->pw_name);

		grp = getgrgid(statbuf.st_gid);
		printf(" %s", grp->gr_name);

		printf(" %d", statbuf.st_size);

		char t[ 100 ] = "";
		localtime( &statbuf.st_mtime);
		strftime(t, 100, " %Y-%m-%d %H:%M ", localtime( &statbuf.st_mtime));
		printf("%s", t);

		printf(" %s\n", argv[x]);		
	}
}
