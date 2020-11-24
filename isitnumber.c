#include "isitnumber.h"
#include "global.h"
#include "headers.h"

extern int sucessflag;
int isitnum(char* argpass)
{
    int signalnumber=0;
    for(int i=0;i<strlen(argpass);i++)
    {
        if(argpass[i]>='0'&&argpass[i]<='9')
        {
            signalnumber*=10;
            signalnumber+=argpass[i]-48;
            continue;
        }
        else 
        {
            sucessflag=-1;
            fprintf(stderr,"Given argument is not number\n");
            return -1;
        }
    }
    return signalnumber;
}