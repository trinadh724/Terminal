#include "job.h"
#include "global.h"
#include "headers.h"

extern int sucessflag;
int job(int pid)
{
    char string1[2000];
    sprintf(string1,"%s%d","/proc/",pid);
    struct stat ver;
    if(stat(string1,&ver)<0)
    {
        sucessflag=-1;
        fprintf(stderr,"The given pid is not valid\n");
        return 2;
    }
    sprintf(string1,"%s%d%s","/proc/",pid,"/stat");
    FILE* file = fopen(string1,"r");
    if(file<0)
    {
        perror("file error");
        sucessflag=-1;
    }
    int sdsdl;
    fscanf(file,"%d ",&sdsdl);
    char stt[100];
    fscanf(file,"%s ",stt);
    char chh;
    long long varp;
    fscanf(file,"%c ",&chh);
    fclose(file);
    if(chh=='T')return -1;
    else return 0;
}