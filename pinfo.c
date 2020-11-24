#include "pinfo.h"
#include "global.h"
#include "headers.h"
 char strinadh[1000];
extern int sucessflag;
void pinfor(char* pid,char* homedir)
{
    char string1[2000];
    sprintf(string1,"%s%s","/proc/",pid);
    struct stat ver;
    if(stat(string1,&ver)<0)
    {
        fprintf(stderr,"The given pid is not valid\n");
        sucessflag=-1;
        return ;
    }
    sprintf(string1,"%s%s%s","/proc/",pid,"/stat");
    FILE* file = fopen(string1,"r");
    if(file<0)
    {
        sucessflag=-1;
        perror("file error");
    }
    int sdsdl;
    fscanf(file,"%d ",&sdsdl);
    printf("pid -- %d\n",sdsdl);
    char stt[100];
    fscanf(file,"%s ",stt);
    char chh;
    long long varp;
    fscanf(file,"%c ",&chh);
    printf("process Status -- %c\n",chh);
    for(int i=4;i<=23;i++)fscanf(file,"%lld ",&varp);
    printf("memory -- %lld {Virtual Memory}\n",varp);
    fclose(file);
    sprintf(string1,"%s%s%s","/proc/",pid,"/exe");
    ssize_t len = readlink(string1,strinadh,1000);
    if(len<0)
    {
        printf("Unsucessful in readlink\n");
        sucessflag=-1;
    }
    strinadh[len]='\0';
    len = strlen(strinadh);
    if(strlen(homedir)>len)
    printf("Executable path -- %s\n",strinadh);
    else
    {
        if(strncmp(homedir,strinadh,strlen(homedir))==0)
        printf("Executable path -- ~%s\n",strinadh+strlen(homedir));
        else
        {
            printf("Executable path -- %s\n",strinadh);
        }
        
    }
}