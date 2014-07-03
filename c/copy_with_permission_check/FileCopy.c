#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<pwd.h>
#include <fcntl.h>

struct stat file_Check;
FILE* file_in;
FILE* file_out;

int check_permissions(char* file)
{
    printf("Checking file permissions for %s\n", file);
    int status;
    if((status = stat(file, &file_Check)) == -1)
    {
        perror("ERROR");
        fprintf(stderr, "Could not stat file %s\n", file);
    }
    if(file_Check.st_uid != getuid() && file_Check.st_gid != getgid())
    {
        fprintf(stderr, "ACCESS DENIED: You are not the owner and are not in the group to use this file.\n");
        status = -1;
    }
    if(!(file_Check.st_mode & S_IRWXU) || !(file_Check.st_mode & S_IWUSR) || !(file_Check.st_mode & S_IWUSR))
    {
        fprintf(stderr, "ACCESS DENIED: No read or write permissions on %s\n", file);
        status = -1;
    }
    return status;
}

int copy(char* from, char* to)
{
    int status;
    char BUFFER[20];
    size_t read;
    size_t write;
    file_in = fopen(from, "r");
    file_out = fopen(to, "w");
    while((read = fread(BUFFER, 1, 20, file_in) != 0))
    {
        if((write = fwrite(BUFFER, 1, 20, file_out)) == -1)
        {
            perror("FAILURE");
            exit(1);
        }
    }

    fclose(file_in);
    fclose(file_out);
    return status;
}

int main(int argc, char* argv[])
{
    int loop;
    int status;
    char* file1;
    char* file2;

    if(argc < 3)
    {
        fprintf(stderr, "START ERROR: To few arguments specified\n");
        exit(0);
    }
    else if(argc > 3)
    {
        printf("TO MANY FILES: Ignoring ");
        for(loop = 3; loop < argc; loop++)
        {
            printf("%s ", argv[loop]);
        }
        printf("\n");
    }
    else
    {
        file1 = argv[1];
        status = check_permissions(file1);
        file2 = argv[2];
        status = check_permissions(file2);
        status = copy(file1, file2);
    }
}
