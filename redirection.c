#include "redirection.h"
#include "global.h"
#include "headers.h"

extern int sucessflag;
int inputfd=-1,outputfd;
extern int copyofstdin;
extern int copyofstdout;
int storeio()
{
    copyofstdin = dup(STDIN_FILENO);
    if(copyofstdin==-1)
    {
        perror("Failed to store the copy of stdin");
        sucessflag=-1;
    }
    copyofstdout = dup(STDOUT_FILENO);
    if(copyofstdout==-1)
    {sucessflag=-1;
    perror("Failed to store the copy of the stdout");
    }
    if(copyofstdin==-1||copyofstdout==-1)return -1;
}
int restoreio()
{
    if(dup2(copyofstdin,STDIN_FILENO)==-1)
    {
        sucessflag=-1;
        perror("Error while restoring deafult stdin");
        return -1;
    }
    if(dup2(copyofstdout,STDOUT_FILENO)==-1)
    {
        sucessflag=-1;
        perror("Error while restoring default stdout");
        return -1;
    }
    if(inputfd!=-1)
    {
        if(close(inputfd)==-1)
        {
            sucessflag=-1;
            perror("Error while closing the file");
            return -1;
        }
        inputfd=-1;
    }
    return 0;
}
int redirectionfinder(char ** argument)
{
    int cc=0,indcount=0;
    inputfd=-1;
    while(argument[cc]!=NULL)
    {
        if(strcmp(argument[cc],"<")==0)
        {
            if(argument[cc+1]!=NULL)
            {
                inputfd = open(argument[cc+1],O_RDONLY);
                if(inputfd==-1)
                {
                    sucessflag=-1;
                   // write(2,argument[cc+1],sizeof(argument[cc+1]));
                   perror("Error upon reading the input file");
                    return -1; 
                }
                else 
                {
                    if(dup2(inputfd,STDIN_FILENO)==-1)
                    {
                        sucessflag=-1;
                        perror("Error which changing default input stream");
                        return -1;
                    }
                    cc++;
                }
            }
            else
            {
                return -1;
            }
            
        }
        else if(strcmp(argument[cc],">")==0||strcmp(argument[cc],">>")==0)
        {
            if(argument[cc+1]!=NULL)
            {
                if(strcmp(argument[cc],">")==0)
                    inputfd = open(argument[cc+1],O_CREAT|O_WRONLY|O_TRUNC,0644);
                else
                    inputfd = open(argument[cc+1],O_CREAT|O_WRONLY|O_APPEND,0644);
                if(inputfd==-1)
                {
                    sucessflag=-1;
                    perror("Error while reading the outputfile");
                    return -1;
                }
                else
                {
                    if(dup2(inputfd,STDOUT_FILENO)==-1)
                    {
                        sucessflag=-1;
                        perror("Error while changing the default outputstream");
                        return -1;
                    }
                    cc++;
                }
                
            }
            else return -1;
        }
        else
        {
            strcpy(argument[indcount],argument[cc]);
            indcount++;
        }
        cc++;
    }
    if(argument[indcount]!=NULL)argument[indcount]=NULL;
}