#include "prompt.h"
#include "input.h"
#include "redirection.h"
#include "pipe.h"
#include "global.h"
#include "overkill.h"
#include "headers.h"
extern char predirectory[2000];
extern int sucessflag;
int main()
{
    sucessflag=1;
    fprintf(stderr,"Welcome to My shell :)\n");
    signal(SIGINT,SIG_IGN);
    signal(SIGTSTP,SIG_IGN);
    while(storeio()==-1){}
    initial();
    allote();
    initi();
    char homedir[2000];
    getcwd(homedir,2000);
    strcpy(predirectory,homedir);
    char * currdir;
    currdir = (char*)malloc(2000*sizeof(char));
    strcpy(currdir,homedir);
    char  *defdir="~";
    char* input;
    char sinput[2000];
    int lenhome=strlen(homedir),lencurr;
    size_t size=2000;
    int character =1;
    input = (char*)malloc(2000*(sizeof(char)));
    while(1)
    {
        getcwd(currdir,2000);
        lencurr=strlen(currdir);
        if(lencurr==lenhome&&strcmp(homedir,currdir)==0)prompt(defdir,homedir);
        else
        prompt(currdir,homedir);
        size=2000;
        if(getline(&input,&size,stdin)==-1)
        {
            fprintf(stderr,"\nGood bye Have a nice day :)\n");
            break;
        }
        character=0;
        for(int i=0;i<strlen(input);i++)
        {
            if(input[i]!=' '&&input[i]!='\n'&&input[i]!='\t')
            {
                character=i;
                break;
            }
        }
        strcpy(sinput,input);
        for(int i=strlen(input)-1;i>=0;i--)
        {
            if(input[i]==' '||input[i]=='\n'||input[i]=='\t')
            {
                sinput[i]='\0';
            }
            else break;
        }
        if(strcmp(sinput+character,"quit")==0)
        {
            fprintf(stderr,"Good bye Have a nice day :)\n");
            break;
        }
        passedinput(input,homedir);
        if(restoreio()==-1)fprintf(stderr,"Trouble in restoring\n");
    }
    overkill();
    free(input);
    free(currdir);
}
