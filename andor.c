#include "andor.h"
#include "pipe.h"
#include "headers.h"
#include "global.h"

extern int sucessflag;
void andor(char * tem, char* homedir)
{
    int preval=1,symbol=1,currind=0;
    for(int i=0;i<strlen(tem);i++)
    {
        if(tem[i]=='@'||tem[i]=='$'||i==strlen(tem)-1)
        {
            if(symbol==1)
            {
                if(tem[i]=='@')symbol=1;
                else symbol=0;
                if(preval==0)
                {
                    currind=i+1;
                }
                else
                {
                    if(i!=strlen(tem)-1)
                    tem[i]='\0';
                    sucessflag=1;
                    pipeit(tem+currind,homedir);
                    tem[i]=' ';
                    currind=i+1;
                    if(sucessflag!=1)preval=0;
                }
            }
            else
            {
                if(tem[i]=='@')symbol=1;
                else symbol=0;
                if(preval==1)
                {
                    currind=i+1;
                }
                else
                {
                    if(i!=strlen(tem)-1)
                    tem[i]='\0';
                    sucessflag=1;
                    pipeit(tem+currind,homedir);
                    tem[i]=' ';
                    currind=i+1;
                    if(sucessflag==1)preval=1;
                }
            }
        }
    }
    sucessflag=preval;
}