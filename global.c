#include "global.h"
#include "headers.h"

struct node * head=NULL;
char predirectory[2000];
int sucessflag;
int copyofstdin,copyofstdout;
void insertintolist(int valpid,char* command)
{
    struct node* curr;
    curr=head;
    if(head==NULL)
    {
        head=(struct node*)malloc(sizeof(struct node));
        head->pidlink=valpid;
        head->nameof=(char*)malloc(100*sizeof(char));
        strcpy(head->nameof,command);
        head->next=NULL;
    }
    else
    {
        while(curr->next!=NULL)
        {
            curr=curr->next;
        }
        struct node* currback;
        currback=(struct node*)malloc(sizeof(struct node));
        curr->next=currback;
        currback->pidlink=valpid;
        currback->nameof=(char*)malloc(100*sizeof(char));
        strcpy(currback->nameof,command);
        currback->next=NULL;
    }
}
void handleback(int ssignal)
{
    struct node * curr;
    struct node* prev=NULL;
    struct node* nnext = NULL; 
    int status;
    curr=head;
    while(curr!=NULL)
    {
        if(waitpid(curr->pidlink,&status,WNOHANG)>0)
        {
            if(WIFEXITED(status))
            {
                fprintf(stderr,"\n%s with pid %d exited normally with exit status %d\n",curr->nameof,curr->pidlink,WEXITSTATUS(status));
                if(prev!=NULL)
                prev->next=curr->next;
                else
                {
                    head = curr->next;   
                }
                nnext=curr->next;
                free(curr);
                curr=prev;
            }
            else if(WIFSIGNALED(status))
            {
                fprintf(stderr,"\n%s with pid %d exited abnormally\n",curr->nameof,curr->pidlink);
                if(prev!=NULL)
                prev->next=curr->next;
                else
                {
                    head = curr->next;
                }
                nnext=curr->next;
                free(curr);
                curr=prev;
            }
        }
        prev=curr;
        if(prev==NULL)
        curr=nnext;
        else
        curr=curr->next;
    }
}
void removefromll(int pidnumber)
{
    struct node * curr;
    struct node* prev=NULL;
    struct node* nnext = NULL; 
    int status;
    curr=head;
    while(curr!=NULL)
    {
        if(curr->pidlink==pidnumber)
        {
            if(prev!=NULL)
            prev->next=curr->next;
            else
            {
                head = curr->next;   
            }
            nnext=curr->next;
            free(curr);
            curr=prev;
        }
        prev=curr;
        if(prev==NULL)
        curr=nnext;
        else
        curr=curr->next;
    }
}