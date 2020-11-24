#include "input.h"
#include "pipe.h"
#include "global.h"
#include "headers.h"
#include "andor.h"
char* tem;
char* copy;
char** temp;
int c=0;
char  hist[25][150];
char  history[150],htt[150];
extern int sucessflag;
void initi()
{
    temp=(char**)malloc(25*sizeof(char*));
    for(int i=0;i<25;i++)temp[i]=(char*)malloc(400*sizeof(char));
    tem=(char*)malloc(2000*sizeof(char));
    copy=tem;
}
void passedinput(char* input,char* homedir)
{
    sucessflag=1;
    tem=copy;
    strcpy(tem,input);
    tem = strtok(tem,";");
    c=0;
    while(tem!=NULL&&c<25)
    {
        temp[c]=tem;
        tem=strtok(NULL,";");
        c++;
    }
    int fflah=-1;
    for(int i=0;i<strlen(input);i++)
    {
        if(input[i]!=' '&&input[i]!='\n'&&input[i]!='\t')
        {
            fflah=i;
            break;
        }
    }
    if(fflah==-1)return;
    for(int i=strlen(input)-1;i>=0;i--)
    {
        if(input[i]!=' '&&input[i]!='\n'&&input[i]!='\t')
        {
            input[i+1]='\n';
            input[i+2]='\0';
            break;
        }
        input[i]='\0';
    }
    if(fflah!=-1)
    {
        sprintf(htt,"%s%s",homedir,"/history.txt");
        int fdf=open(htt,O_CREAT,0777);
        chmod(htt,0777);
        close(fdf);
        FILE* file = fopen(htt,"r");
        if(file==NULL)
        {
            sucessflag=-1;
            perror("failure in fopen1");
            return;
        }
        int ccou=0;
        while(fgets(history,150,file)!=NULL)
        {
            strcpy(hist[ccou],history);
            ccou++;
        }
        if(fclose(file))
        {
            perror("failed to close");
            sucessflag=-1;
        }
        if(strcmp(hist[ccou-1],input+fflah)!=0)
        {
        if(ccou<=19)
        {
            FILE *file1= fopen(htt,"w");
            if(file1==NULL)
            {
                sucessflag=-1;
                perror("failure in fopen");
                return ;
            }
            for(int i=0;i<ccou;i++)fputs(hist[i],file1);
            fputs(input+fflah,file1);
            if(fclose(file1))
            {
                perror("failed to close");
                sucessflag=-1;
            }
        }
        else
        {
            FILE *file2=fopen(htt,"w");
              if(file2==NULL)
            {
                sucessflag=-1;
                perror("failure in fopen");
                return ;
            }
            for(int i=1;i<=19;i++)fputs(hist[i],file2);
            fputs(input+fflah,file2);
            if(fclose(file2))
            {
                perror("failed to close");
                sucessflag=-1;
            }
        }
        }
    }
    if(tem!=NULL)
    {
        sucessflag=-1;
        fprintf(stderr,"Too many arguments than allowed limit please reduce the number less than 24 commands!!\n");
    }
    for(int i=0;i<c;i++)
    {
        andor(temp[i],homedir);
    }
}