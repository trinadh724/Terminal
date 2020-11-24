#include "overkill.h"
#include "global.h"
#include "headers.h"

extern struct node* head;
extern int sucessflag;
void overkill()
{
    int justfor;
    struct node * current=head;
    while(current!=NULL)
    {
        if(kill(current->pidlink,9)==-1)
        {
            sucessflag=-1;
            fprintf(stderr,"%s :",current->nameof);
            perror("Failed to kill process");
        }
        current = current->next;
    }
}