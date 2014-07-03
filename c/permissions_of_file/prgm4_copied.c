#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdio.h>
#include <stdint.h>
struct dirent *dp;
struct stat   statbuf;
struct passwd *pwd;
struct group  *grp;
struct tm     *tm;
char datestring[256]; 
int main()
{
	DIR* dir;
	while((dp = readdir(dir)) != NULL) 
	{
		if (stat(dp->d_name, &statbuf) == -1)	
		    continue;
		
		printf("%10.10s", (statbuf.st_mode));
		printf("%4d", statbuf.st_nlink);
	
		if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
			printf(" %-8.8s", pwd->pw_name);
		else
			printf(" %-8d", statbuf.st_uid);
	 
		if ((grp = getgrgid(statbuf.st_gid)) != NULL)
			printf(" %-8.8s", grp->gr_name);
		else
			printf(" %-8d", statbuf.st_gid);
		
		printf(" %9jd", (intmax_t)statbuf.st_size);
		tm = localtime(&statbuf.st_mtime);
		
		strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
		printf(" %s %s\n", datestring, dp->d_name);
	}
}


