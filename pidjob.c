#include "pidjob.h"
#include "global.h"
#include "headers.h"

extern struct node* head;
int getmestringofpid(char** argpass,int jobnumber)
{
    struct node* currcom;
    currcom = head;
    int coucou=1;
    while(currcom!=NULL)
    {
        if(currcom->pidlink==jobnumber)
        {
            jobnumber=currcom->pidlink;
            strcpy(argpass[0],currcom->nameof);
            return jobnumber;
        }
        currcom=currcom->next;
        coucou++;
    }
    return -1;
}
int getmepid(int jobnumber)
{
    struct node* currcom;
    currcom = head;
    int coucou=1;
    while(currcom!=NULL)
    {
        if(coucou==jobnumber)
        {
            jobnumber=currcom->pidlink;
            return jobnumber;
        }
        currcom=currcom->next;
        coucou++;
    }
    return -1;
}