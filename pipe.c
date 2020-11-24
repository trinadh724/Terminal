#include "pipe.h"
#include "global.h"
#include "command.h"
#include "redirection.h"
#include "headers.h"

char** ptemp;
char* ptem;
char* pcopy;
int pcp;
extern int sucessflag;
void allote()
{
    ptemp=(char**)malloc(25*sizeof(char*));
    for(int i=0;i<25;i++)ptemp[i]=(char*)malloc(400*sizeof(char));
    ptem=(char*)malloc(2000*sizeof(char));
    pcopy=ptem;
}
void pipeit(char* input,char* homedir)
{
    ptem=pcopy;
    strcpy(ptem,input);
    ptem = strtok(ptem,"|");
    pcp=0;
    while(ptem!=NULL&&pcp<25)
    {
        ptemp[pcp]=ptem;
        ptem=strtok(NULL,"|");
        pcp++;
    }
    int pipearr[25][2],vvar,ffll=-1;
    for(int i=0;i<pcp;i++)
    {
        ffll=1;
        vvar=i;
        if(pipe(pipearr[i])==-1)
        {
            sucessflag=-1;
            perror("Error while creating a ppe");
            return;
        }
        if(i!=0)
        {
            if(dup2(pipearr[i-1][0],STDIN_FILENO)==-1)
            {
                sucessflag=-1;
                perror("Error while doing duplication");
                return ;
            }
        }
        if(i!=pcp-1)
        {
            if(dup2(pipearr[i][1],STDOUT_FILENO)==-1)
            {
                sucessflag=-1;
                perror("Error while doing duplication");
                return ;
            }
        }
        sucessflag=1;
        commandpassed(ptemp[i],homedir);
        restoreio();
        if(close(pipearr[i][1])==-1)
        {
            sucessflag=-1;
            perror("Error while closing the pipe's write end");
            return ;
        }
        if(i!=0)
        {
            if(close(pipearr[i-1][0])==-1)
            {
                sucessflag=-1;
                perror("Error while closing the read end");
                return;
            }        
        }
    }
    if(close(pipearr[vvar][0])==-1&&ffll==-1)
    {
        sucessflag=-1;
        perror("Error while closing the read end");
        return;
    }
}