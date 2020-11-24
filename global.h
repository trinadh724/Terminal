#ifndef __GLOBAL_H
#define __GLOBAL_H

struct node{
    int pidlink;
    char* nameof;
    struct node* next;
};
void insertintolist(int valpid,char* command);
void handleback(int ssignal);
void removefromll(int jobnumber);
#endif