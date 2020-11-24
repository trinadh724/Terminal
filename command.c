#include "command.h"
#include "cd.h"
#include "pwd.h"
#include "overkill.h"
#include "echo.h"
#include "isitnumber.h"
#include "ls.h"
#include "background.h"
#include "foreground.h"
#include "pinfo.h"
#include "night.h"
#include "global.h"
#include "job.h"
#include "pidjob.h"
#include "redirection.h"
#include "headers.h"

char* strcommand[]={"cd","ls","echo","pwd"};
char* temcommand;
char* codecpp;
char* trincopy;
char* trinn;
int f=-1,testingback,llcommand,commre,grandchild,rere,statuscommand,wcommand,point;
int real;
char* argpass[20];
char * argpasscopy[20];
extern struct node* head;
extern int sucessflag;
char hisdup[200],rubb[150],hh[150],cpu[150],seten[]="";
void commandpassed(char* command,char* homedir)
{

    if(f==-1)
    {
        temcommand=(char*)malloc(1000*sizeof(char));
        trinn=temcommand;
        f=1;
        for(int i=0;i<20;i++)
        {
            argpass[i]=(char*)malloc(sizeof(100*sizeof(char)));
            argpasscopy[i]=argpass[i];
        }
    }
    for(int i=0;i<20;i++)
    {
        argpass[i]=argpasscopy[i];
    }
    temcommand=trinn;
    if(strlen(command)>0&&command[strlen(command)-1]=='\n')command[strlen(command)-1]='\0';
    strcpy(temcommand,command);
    temcommand=strtok(temcommand," \t");
    llcommand=0;
    while(temcommand!=NULL)
    {
        strcpy(argpass[llcommand],temcommand);
        llcommand++;
        temcommand=strtok(NULL," \t");
    }
    argpass[llcommand]=NULL;
    if(redirectionfinder(argpass)==-1){
        write(2,"Invalid argument for io redirection\n",strlen("Invalid argument for io redirection\n"));
        sucessflag=-1;
        return;
    }
    strcpy(command,"");
    int mytem=0;
    while(argpass[mytem]!=NULL)
    {
        strcat(command,argpass[mytem]);
        strcat(command," ");
        mytem++;
    }
    temcommand=trinn;
    if(strlen(command)>0&&command[strlen(command)-1]=='\n')command[strlen(command)-1]='\0';
    strcpy(temcommand,command);
    temcommand = strtok(temcommand," \t");
    if(temcommand==NULL)return;
    if(strlen(temcommand)>0&&temcommand[strlen(temcommand)-1]=='\n')temcommand[strlen(temcommand)-1]='\0';
    if(strcmp(temcommand,strcommand[0])==0)
    {
        temcommand = strtok(NULL," \t");
        if(temcommand!=NULL&&temcommand[strlen(temcommand)-1]!='\n')
        {
            trincopy=strtok(NULL," \t");
            if(trincopy==NULL)
            {
                cdcommand(temcommand,homedir);
            }
            else if(trincopy[0]==' '||trincopy[0]=='\t'||trincopy[0]=='\n')
            {
                cdcommand(temcommand,homedir);
            }
            else
            {
                sucessflag=-1;
                fprintf(stderr,"Too many arguments!!\n");
            }
        }
        else
        cdcommand(temcommand,homedir);
    }
    else if(strcmp(temcommand,"overkill")==0)
    {
        if(argpass[1]!=NULL)
        {
            sucessflag=-1;
            fprintf(stderr,"overkill:Too many arguments\n");
            return ;
        }
        overkill();
    }
    else if(strcmp(temcommand,"bg")==0)
    {
        if(argpass[1]==NULL||argpass[2]!=NULL)
        {
            sucessflag=-1;
            fprintf(stderr,"bg: Invalid command for bg command\n");
            return ;
        }
        int jobnumber = isitnum(argpass[1]);
        if(jobnumber==-1)
        {
            sucessflag=-1;
            fprintf(stderr,"No such process with this job number exist\n");
            return ;
        }
        jobnumber=getmepid(jobnumber);
        if(jobnumber==-1)
        {
            sucessflag=-1;
            fprintf(stderr,"No such process with this job number exist\n");
            return ;
        }
        if(kill(jobnumber,SIGCONT)==-1)
        {
            sucessflag=-1;
            perror("bg: Failed to continue the process");
            return ;
        }
    }
    else if(strcmp(temcommand,"fg")==0)
    {
        if(argpass[1]==NULL||argpass[2]!=NULL)
        {
            fprintf(stderr,"fg: Invalid command for fg command\n");
            sucessflag=-1;
            return ;
        }
        int jobnumber = isitnum(argpass[1]);
        if(jobnumber==-1)
        {
            sucessflag=-1;
            return;
        }
        jobnumber=getmepid(jobnumber);
        if(jobnumber==-1)
        {
            sucessflag=-1;
            fprintf(stderr,"No such process with this job number exist\n");
            return ;
        }
        if(getmestringofpid(argpass,jobnumber)==-1)
        {
            sucessflag=-1;
            fprintf(stderr,"fg: Not able to reset the name of the job's pid requested\n");
            return;
        }
        if(kill(jobnumber,SIGTSTP)==-1)
        {
            sucessflag=-1;
            perror("Failed to stop the process before converting to fg");
            return ;
        }
        corefg(argpass,jobnumber,1);
    }
    else if(strcmp(temcommand,"jobs")==0)
    {
        if(argpass[1]!=NULL)
        {
            sucessflag=-1;
            fprintf(stderr,"Invalid number of argumnts for jobs command\n");
            return;
        }
        struct node* currcom;
        currcom = head;
        int coucou=1,stst;
        while(currcom!=NULL)
        {
            if(job(currcom->pidlink)==-1)
            {
                printf("[%d] Stopped %s [%d]\n",coucou,currcom->nameof,currcom->pidlink);                    
            }
            else
            {
                printf("[%d] Running %s [%d]\n",coucou,currcom->nameof,currcom->pidlink);
            }
            currcom=currcom->next;
            coucou++;
        }
    }
    else if(strcmp(temcommand,"kjob")==0)
    {
        if(argpass[1]==NULL||argpass[2]==NULL||argpass[3]!=NULL)
        {
            sucessflag=-1;
            fprintf(stderr,"Invalid number of arguments for kjob\n");
            return ;
        }
        int jobnumber=0, signalnumber=0;
        jobnumber=isitnum(argpass[1]);
        if(jobnumber==-1)
        {
            sucessflag=-1;
            return;
        }
        signalnumber=isitnum(argpass[2]);
        if(signalnumber==-1)
        {
            sucessflag=-1;
            return;
        }
        jobnumber=getmepid(jobnumber);
        if(jobnumber==-1)
        {
            sucessflag=-1;
            fprintf(stderr,"Invalid jobnumber :(\n");
            return;
        }
        if(kill(jobnumber,signalnumber)==-1)
        {
            sucessflag=-1;
            perror("Failed to kill process");
        }
    }
    else if(strcmp(temcommand,"setenv")==0)
    {
        if(argpass[1]==NULL || (argpass[2]!=NULL&&argpass[3]!=NULL))
        {
            sucessflag=-1;
            fprintf(stderr,"setenv error: invalid number of arguments\n");
            return ;
        }
        if(argpass[2]==NULL)
        {
            if(setenv(argpass[1],seten,1)==-1)
            {
                sucessflag=-1;
                fprintf(stderr,"%s : ",argpass[1]);
                perror("Error when setenv is used");
                return;
            }
        }
        else
        {
            if(setenv(argpass[1],argpass[2],1)==-1)
            {
                sucessflag=-1;
                fprintf(stderr,"%s %s: ",argpass[1],argpass[2]);
                perror("Error when setenv is used");
                return;
            }
        }
    }
    else if(strcmp(temcommand,"unsetenv")==0)
    {
        if(argpass[1]==NULL||(argpass[2]!=NULL))
        {
            sucessflag=-1;
            fprintf(stderr,"unsetenv error: invalid number of arguments\n");
            return ;
        }
        if(unsetenv(argpass[1])==-1)
        {
            sucessflag=-1;
            fprintf(stderr,"%s : ",argpass[1]);
            perror("Error when unsetenv is used");
            return;
        }
    }
    else if(strcmp(temcommand,strcommand[3])==0)
    {
        temcommand=strtok(NULL," \t");
        if(temcommand==NULL||temcommand[0]=='\n'||temcommand[0]=='\t'||temcommand[0]==' ')pwdcommand();
        else
        {
            fprintf(stderr,"Too many commands for pwd!!\n");
            sucessflag=-1;
        }
    }
    else if(strcmp(temcommand,strcommand[2])==0)
    {
        commandecho(command);
    }
    else if(strcmp(temcommand,strcommand[1])==0)
    {
        commandls(command,homedir);
    }
    else if(strcmp(temcommand,"history")==0)
    {
        temcommand=strtok(NULL," \t");
        sprintf(hh,"%s%s",homedir,"/history.txt");
        if(temcommand==NULL||temcommand[0]==' '||temcommand[0]=='\t'||temcommand[0]=='\n')
        {
            long long given = 10;
            int totcou=0;
            FILE * fil3= fopen(hh,"r");
            if(fil3==NULL)
            {
                sucessflag=-1;
                perror("failed when opening fopen");
                return;
            }
            while(fgets(hisdup,200,fil3)!=NULL)totcou++;
            if(fclose(fil3))
            {
                sucessflag=-1;
                perror("error on closing");
                return;
            }
            FILE *fil1=fopen(hh,"r");
            if(given>totcou)given = totcou;
            totcou--;
            if(given>10)given = 10;
            int ii=0;
            while(fgets(hisdup,150,fil1)!=NULL)
            {
                if(ii>=totcou-given+1)
                {
                    printf("%s",hisdup);
                }
                ii++;
            }
            if(fclose(fil1))
            {
                sucessflag=-1;
                perror("error when closing");
                return;
            }
        }
        else
        {
            strcpy(rubb,temcommand);
            temcommand=strtok(NULL," \t");
            if(temcommand==NULL)
            {
                if(rubb[strlen(rubb)-1]=='\n')rubb[strlen(rubb)-1]='\0';
                for(int i=0;i<strlen(rubb);i++)
                {
                    if(rubb[i]>='0'&&rubb[i]<='9')continue;
                    else
                    {
                        sucessflag=-1; 
                        fprintf(stderr,"Invalid argument!!\n");
                        return ;
                    }
                }
                long long given = atol(rubb);
                int totcou=0;
                FILE * fil= fopen(hh,"r");
                if(fil==NULL)
                {
                    sucessflag=-1;
                    perror("failed when opening fopen");
                    return;
                }
                while(fgets(hisdup,200,fil)!=NULL)totcou++;
                if(fclose(fil))
                {
                    sucessflag=-1;
                    perror("error on closing");
                    return;
                }
                FILE *fil1=fopen(hh,"r");
                if(given>totcou)given = totcou;
                totcou--;
                if(given>20)given = 20;
                int ii=0;
                while(fgets(hisdup,150,fil1)!=NULL)
                {
                    if(ii>=totcou-given+1)
                    {
                        printf("%s",hisdup);
                    }
                    ii++;
                }
                if(fclose(fil1))
                {
                    sucessflag=-1;
                    perror("error when closing");
                    return;
                }
            }
            else
            {
                sucessflag=-1;
                fprintf(stderr,"Too many arguments!\n");
            }
        }
        
    }
    else if(strcmp(temcommand,"pinfo")==0)
    {
        char reu[150];
        int ffl=-1;;
        temcommand=strtok(NULL," \t");
        if(temcommand==NULL||temcommand[0]==' '||temcommand[0]=='\n'||temcommand[0]=='\t')
        {
            sprintf(reu,"%d",getpid());
            if(reu[strlen(reu)-1]=='\n')reu[strlen(reu)-1]='\0';
            pinfor(reu,homedir);
            return;
        }
        strcpy(reu,temcommand);
        temcommand=strtok(NULL," \t");
        if(temcommand==NULL||temcommand[0]=='\n')
        {
            if(reu[strlen(reu)-1]=='\n')
            {
                reu[strlen(reu)-1]='\0';
            }
            for(int i=0;i<strlen(reu);i++)
            {
                if(reu[i]>='0'&&reu[i]<='9')continue;
                else
                {
                    sucessflag=-1;
                    fprintf(stderr,"Invalid argument!!\n");
                    return ;
                }
                
            }
            pinfor(reu,homedir);
            return ;
        }
        sucessflag=-1;
        fprintf(stderr,"Too many argumewnts\n");   
    }
    else if(strcmp(temcommand,"nightswatch")==0)
    {
        temcommand=strtok(NULL," \t");
        if(temcommand==NULL||strcmp(temcommand,"-n")!=0)
        {
            sucessflag=-1;
            fprintf(stderr,"Wrong command for nightswatch command\n");
            return;
        }
        temcommand=strtok(NULL," \t");
        if(temcommand==NULL)
        {
            fprintf(stderr,"Wrong command for nightswatch\n");
            sucessflag=-1;
            return;
        }
        for(int i=0;i<strlen(temcommand);i++)
        {
            if(temcommand[i]>='0'&&temcommand[i]<='9')continue;
            else 
            {
                sucessflag=-1;
            fprintf(stderr,"Wrong command for nightswatch\n");
            return;                
            }
        }
        long long trinnum = atol(temcommand);
        temcommand=strtok(NULL," \t");
        if(temcommand==NULL||(strcmp(temcommand,"newborn")!=0&&strcmp(temcommand,"interrupt")!=0))
        {
            sucessflag=-1;
            fprintf(stderr,"Wrong command for nightswatch\n");
            return;
        }
        strcpy(cpu,temcommand);
        temcommand=strtok(NULL," \t");
        if(temcommand!=NULL)
        {
            sucessflag=-1;
            fprintf(stderr,"Too many arguments\n");
            return;
        }
        if(strcmp(cpu,"interrupt")==0)interrup(trinnum,1);
        else interrup(trinnum,2);
    }
    else if(command[0]!='\n')
    {
        for(int i=0;i<20;i++)
        {
            argpass[i]=argpasscopy[i];
        }
        testingback=-1;
        llcommand=strlen(command);
        if(strlen(command)>0&&command[strlen(command)-1]=='\n')command[llcommand-1]='\0';
        llcommand=strlen(command);
        for(int i=0;i<llcommand;i++)
        {
            if(command[i]=='&')
            {
                testingback=i;
                command[i]='\0';
                break;
            }
        }
        if(testingback!=-1)
        {
            for(int i=testingback;i<llcommand;i++)command[i]='\0';
        }
        temcommand=trinn;
        temcommand=strtok(command," \t");
        llcommand=0;
        while(temcommand!=NULL)
        {
            strcpy(argpass[llcommand],temcommand);
            llcommand++;
            temcommand=strtok(NULL," \t");
        }
        argpass[llcommand]=NULL;
        if(testingback==-1)
        {
       // printf("%d\n",testingback);
          foreground(argpass);
        }
        else
        {
            background(argpass);
        }
    }
    if(restoreio()==-1)
    {
        sucessflag=-1;
        write(2,"Trying to restore it",strlen("Trying to restore it"));
    }
}