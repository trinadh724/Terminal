#include "prompt.h"
#include "global.h"
#include "headers.h"

char string[2000];
struct utsname buffelo={0};
char usrname[2000];
int ll1,ll2;
extern int sucessflag;
void initial()
{
    uname(&buffelo);
    char * tem=getlogin();
    strcpy(usrname,tem);
}
void promtfirstpart(){
    //printf("\x1b[32m");
    //printf("\e[1m<%s@%s:\e[0m",usrname,buffelo.nodename);
    //printf("\x1b[0m");
    if(sucessflag==1)
    {
        printf(":')");
    }
    else printf(":'(");
    printf("<%s@%s",usrname,buffelo.nodename);
}
void prompt(char* currdir, char * homedir) {
    promtfirstpart();
    //printf("\x1b[34m");
    ll1=strlen(currdir);ll2=strlen(homedir);
    if(ll1<ll2)
    {
        //printf("\e[1m%s>\e[0m",currdir);
        printf("%s>",currdir);
    }
    else if(strncmp(homedir,currdir,ll2)==0)
    {
        //printf("\e[1m~%s>\e[0m",currdir+ll2);
        printf("%s>",currdir+ll2);
    }
    else
    {
        //printf("\e[1m%s>\e[0m",currdir);
        printf("%s>",currdir);
    }
    sucessflag=1;
    //printf("\x1b[0m")
}
