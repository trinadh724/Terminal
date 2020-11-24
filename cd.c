#include "cd.h"
#include "global.h"
#include "headers.h"

int cdcou=0;
char* cdtt;
extern char predirectory[2000];
char prepre[2000];
extern int sucessflag;
void cdcommand(char* flag,char* homedir)
{
    if(flag==NULL||flag[0]=='\n')
    {
        getcwd(prepre,2000);
        if(chdir(homedir)==-1)
        {
            perror("chdir failed");
            sucessflag=-1;
        }
        strcpy(predirectory,prepre);
        return;
    }
    if(flag[strlen(flag)-1]=='\n')
    flag[strlen(flag)-1]='\0';
    if(strcmp(flag,"-")==0)
    {
        getcwd(prepre,2000);
        int f=chdir(predirectory);
        printf("%s\n",predirectory);
        strcpy(predirectory,prepre);
    }
    else if(flag[0]!='~')
    {
        getcwd(prepre,2000);
        int f=chdir(flag);
        if(f<0)
        {
            perror(flag);
            sucessflag=-1;
            return;
        }
        strcpy(predirectory,prepre);
    }
    else
    {
        getcwd(prepre,2000);
        if(cdcou==0)cdtt=(char*)malloc(1000*sizeof(char));
        cdcou=1;
        strcpy(cdtt,homedir);
        strcat(cdtt,flag+1);
        int f=chdir(cdtt);
        if(f<0)
        {
            perror(cdtt);
            sucessflag=-1;
            return;
        }
        strcpy(predirectory,prepre);
    }
}