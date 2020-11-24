#include "night.h"
#include "headers.h"
#include "global.h"

extern int sucessflag;
char intcpu[400];
int conc;
extern int copyofstdin;
extern int copyofstdout;
void showthread()
{
    FILE * ipl= fopen("/proc/interrupts","r");
    if(ipl==NULL)
    {
        sucessflag=-1;
        perror("fopen failed");
        return;
    }
    fgets(intcpu,400,ipl);
    if(conc==-1)printf("%s",intcpu+6);
    conc=1;
    int fftt=-1;
    while(fgets(intcpu,400,ipl)!=NULL)
    {
    for(int i=0;i<strlen(intcpu);i++)
    {
        if(intcpu[i]!=' ')
        {
            if(intcpu[i-1]==' '&&intcpu[i]=='1'&&intcpu[i+1]==':')fftt=1;
            intcpu[i]=' ';
            intcpu[i+1]=' ';
            break;
        }
    }
    if(fftt==-1)continue;
    for(int i=0;i<strlen(intcpu);i++)
    {
        if(!(intcpu[i]>='0'&&intcpu[i]<='9')&&intcpu[i]!=' '&&intcpu[i]!='\t')
        {
            intcpu[i]='\n';
            intcpu[i+1]='\0';
            break;
        }
    }
    printf("\r%s",intcpu+6);
    if(fclose(ipl))
    {
        sucessflag=-1;
        perror("Error while closing");
    }
    break;
    return;
    }
}
void recentpro()
{
    FILE* ipl2=fopen("/proc/loadavg","r");
    if(ipl2==NULL)
    {
        sucessflag=-1;
        perror("Fopen failed");
        return;
    }
    fgets(intcpu,400,ipl2);
    for(int i=strlen(intcpu);i>=0;i--)
    {
        if(intcpu[i]==' ')
        {
            printf("%s",intcpu+i+1);
            if(fclose(ipl2))
            {
                perror("Error while closing file");
                sucessflag=-1;
            }
            return;
        }
    }   
}
int getfunction()
{
  
    int chtrin;
    struct termios old;
    struct termios new;
    if(tcgetattr(STDIN_FILENO,&old)==-1)
    {
        sucessflag=-1;
        perror("tcgetattr failed");
        return 1;
    }
    new = old;
    new.c_lflag &= ~(ICANON|ECHO);
    if(tcsetattr(STDIN_FILENO,TCSANOW,&new)==-1)
    {
        sucessflag=-1;
        perror("tcsetattr failed");
        return 1;
    }
    if(ioctl(0,FIONREAD,&chtrin)==-1)
    {
        sucessflag=-1;
        perror("ioctl failed");
        return 1;
    }
    if(chtrin>0)
    {
        chtrin=getchar();
    }
    if(tcsetattr(STDIN_FILENO,TCSANOW,&old)==-1)
    {
        sucessflag=-1;
        perror("tcsetattr failed");
        return 1;
    }
    if(chtrin=='q')return 0;
    else return 1;
}
void interrup(long long number,int con)
{
    conc=-1;
    int numtrin=1;
    clock_t time = clock();
    number=number*CLOCKS_PER_SEC;
    char chch;
    if(con==1)showthread();
    else recentpro();
    while (numtrin==1)
    {
        time = clock();
        while(clock()<time+number)
        {
           numtrin=getfunction();
           if(numtrin!=1)
           {
               printf("\r");
               return;
           }
        }
        if(numtrin!=1)
        {
            printf("\r");
            return;
        } 
        if(con==1)
        showthread();
        else
        {
            recentpro();
        }
    }
    printf("\r");
    return;
}