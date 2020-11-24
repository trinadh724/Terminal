#include "foreground.h"
#include "global.h"
#include "job.h"
#include "headers.h"
int forechild,statfore;
extern struct node * head;
extern int sucessflag;
extern int copyofstdin;
extern int copyofstdout;
void corefg(char** argument,int forechild,int type)
{
           //  printf("%d %d\n",tcgetpgrp(STDOUT_FILENO),getpgrp());
    setpgid(forechild,forechild);
    if(signal(SIGTTOU,SIG_IGN)==SIG_ERR)
    {
        sucessflag=-1;
        perror("Signal");
        return;
    }
    if(signal(SIGTTIN,SIG_IGN)==SIG_ERR)
    {
        sucessflag=-1;
        perror("Signal");
        return;
    }
    if(tcsetpgrp(copyofstdin,forechild)==-1)
    {
    }
    if(type!=0)
    {
        if(kill(forechild,SIGCONT)==-1)
        {
            sucessflag=-1;
            perror("fg: Failed to run the process after converting to fg");
            return ;
        }
    }
    if(waitpid(forechild,&statfore,WUNTRACED)<0)
    {
        sucessflag=-1;
        perror("wait error");
        return;
    }
    if(type!=0)removefromll(forechild);
    if(WIFSTOPPED(statfore))
    {
        sucessflag=-1;
        insertintolist(forechild,argument[0]);
        if(signal(SIGCHLD,handleback)==SIG_ERR)perror("signal failed");
    }
    if(WIFEXITED(statfore))
    {
        if(WEXITSTATUS(statfore)!=0)sucessflag=-1;
    }
    if(WIFSIGNALED(statfore))
    {
        sucessflag=-1;
    }
    if(tcsetpgrp(copyofstdin,getpid())==-1)
    {
        // perror("tcsetpgrp is error");
    }
    signal(SIGTTOU,SIG_DFL);
    signal(SIGTTIN,SIG_DFL);
}
void foreground(char** argument)
{
    int cc=0;
    forechild = fork();
    if(forechild<0)
    {
        sucessflag=-1;
        perror("fork failed while executing foreground");
    }
    if(forechild==0)
    {
        signal(SIGINT,SIG_DFL);
        signal(SIGTSTP,SIG_DFL);
        setpgid(0,0);
        for(int tt=0;tt<20000;tt++);
        tcsetpgrp(copyofstdin, getpgrp());
        if(execvp(argument[0],argument)<0)
        {
            write(2,argument[0],strlen(argument[0]));
            perror(": Invalid command failed when execvp is used (fg process)");
            exit(-1);
        }
        else exit(0);
    }
    else
    {
        corefg(argument,forechild,0);
    }
}