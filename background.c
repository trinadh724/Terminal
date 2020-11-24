#include "background.h"
#include "global.h"
#include "headers.h"

int backpid;
// struct node{
//     int pidlink;
//     char* nameof;
//     struct node* next;
// };
// struct node * head=NULL;
extern struct node* head;
extern int sucessflag;
void background(char ** arguments)
{
    backpid=fork();
    if(backpid<0)
    {
        perror("Fork failed");
        sucessflag=-1;
        return;
    }
    if(backpid==0)
    {
        signal(SIGINT,SIG_DFL);
        signal(SIGTSTP,SIG_DFL);
        if(setpgid(0,0)==-1)perror("setpgid failed");
        if(execvp(arguments[0],arguments)<0)
        {
            write(2,"\n",strlen("\n"));
            write(2,arguments[0],strlen(arguments[0]));
            perror(": Error when command is passed to execvp (bg process)");
            exit(-1);
        }
    }
    else
    {
        if(setpgid(backpid,backpid)==-1)perror("setpgid failed");
        fprintf(stderr,"[1]+    %d\n",backpid);
        insertintolist(backpid,arguments[0]);
        if(signal(SIGCHLD,handleback)==SIG_ERR)perror("signal failed");
    }
}