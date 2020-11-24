#include "ls.h"
#include "global.h"
#include "headers.h"

extern int sucessflag;
int ffnum=0;
char filename[10][200];
int ffls=-1,cls;
char* temls;
char* stls;
char *rwsym[]={"r","w","x"};
int ddls=0,dsl;
char buff[1000];
void ls(char* nameof,char* pare,int perm)
{
    struct stat sd={0};
    if(stat(nameof,&sd)!=-1)
    {
        if(perm%2!=1&&pare[0]=='.')return;
        if(perm/2==1)
        {
        if(S_ISDIR(sd.st_mode))printf("d");
        else if(S_ISLNK(sd.st_mode))printf("l");
        else printf("-");
        ddls=256;
        for(int i=0;i<9;i++)
        {
            dsl=sd.st_mode & ddls;
            if(dsl>0)printf("%s",rwsym[i%3]);
            else printf("-");
            ddls=ddls/2;
        }
        printf(" ");
        printf("%4ld ",sd.st_nlink);
        printf("%s ",getpwuid(sd.st_uid)->pw_name);
        printf("%s ",getgrgid(sd.st_gid)->gr_name);
        printf("%11ld ",sd.st_size);
        time_t ttime=sd.st_mtime;
        struct tm iter;
        localtime_r(&ttime,&iter);
        strftime(buff,100,"%b %e %k:%M",&iter);
        printf("%s ",buff);
        printf("%s\n",pare);
        }
        else printf("%s ",pare);
    }
    else
    {
        perror(pare);
    }
    
}
void implementls(char* dir,int perm,char* homedir)
{
    int nn;
    struct dirent ** files;
    if(dir[0]=='~')
    {
        strcpy(buff,homedir);
        strcat(buff,dir+1);
        strcpy(dir,buff);
    }
    nn=scandir(dir,&files,NULL,alphasort);
    if(nn<0)
    {
        sucessflag=-1;
        fprintf(stderr,"Error when scandir is used\n");
        perror(dir);
    }
    else
    {
        printf("%s:\n",dir);
        for(int i=0;i<nn;i++)
        {
            strcpy(buff,dir);
            if(buff[strlen(buff)-1]!='/')
            {
                strcat(buff,"/");
            }
            strcat(buff,files[i]->d_name);
            ls(buff,files[i]->d_name,perm);
            free(files[i]);
        }
        if(perm/2!=1)printf("\n");
        free(files);
    }
}
void commandls(char* cpassed,char* homedir)
{
    if(ffls==-1)
    {
        ffls=1;
        temls=(char*)malloc(1000*sizeof(char));
        stls=temls;
    }
    temls=stls;
    if(cpassed[strlen(cpassed)-1]=='\n')
    {
        cpassed[strlen(cpassed)-1]='\0';
    }
    temls=strtok(cpassed," \t");
    temls=strtok(NULL," \t");
    ffnum=0;
    cls=0;
    while(temls!=NULL)
    {
       if(temls[0]=='-')
       {
           for(int i=1;i<strlen(temls);i++)
           {
               if(temls[i]=='a')
               {
                   if(ffnum%2!=1)ffnum+=1;
               }
               else if(temls[i]=='l')
               {
                   if(ffnum/2!=1)ffnum+=2;
               }
               else
               {
                   sucessflag=-1;
                   fprintf(stderr,"Undefined flag for ls command\n");
                   return;
               }
               
           }
       }
       else if(temls[0]!=' '&&temls[0]!='\t'&&temls[0]!='\n')
       {
          strcpy(filename[cls],temls);
          cls++;
          if(cls>9)
          {
              sucessflag=-1;
              fprintf(stderr,"Too many directoires can you please reduce number of directories.");
              return;
          } 
       }
       temls=strtok(NULL," \t");
    }
    if(cls==0)
    {
        char verstr[]=".";
        implementls(verstr,ffnum,homedir);
    }
    else
    {
        for(int i=0;i<cls;i++)
        {
            implementls(filename[i],ffnum,homedir);
        }
    } 
}