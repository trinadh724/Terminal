#include "echo.h"
#include "headers.h"

int len=0,curr;
char stri[2000],copyecho[2000];
char* stro;
char* temm;
int ff=-1,veco,che=-1;
void commandecho(char* passed)
{
    if(ff==-1)
    {
        ff=1;
        stro=(char*)malloc(2000*sizeof(char));
        temm=stro;
    }
    stro=temm;
    len=strlen(passed);
    strcpy(copyecho,passed);
    for(int i=0;i<len;i++)
    {
        if(passed[i]=='e')
        {
            curr=i;
            break;
        }
    }
    che=-1;
    if(passed[len-1]=='\n')che=1;
    stro=strtok(copyecho+curr+4," \t");
    while(stro!=NULL)
    {
        printf("%s ",stro);
        stro=strtok(NULL," \t");
    }
    if(che==-1)printf("\n");
}