#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

void list(char *fn){
        char new[200];
        struct DIR *dp;
        struct dirent *d;
        if((dp=opendir(fn))!=NULL){
                printf("%s\n",fn);
                char *p;
                while(d=readdir(dp)){
                        p=d->d_name;
                        if(*p!='.' || (*++p!='.' && *p!='\0')){
                                strcpy(new,fn);
                                strcat(new,"/");
                                strcat(new,d->d_name);
                                list(new);
                        }
                }
                closedir(dp);
        }
}

int main(int argc, char *argv[]){
        int i;
        struct DIR *dp;
        if(argc==1) list((char*)getenv("PWD"));
        else for(i=1;i<argc;i++)
                if((dp=opendir(argv[i]))!=NULL) list(argv[i]);
                else printf("No such directory `%s`\n",argv[i]);
}
