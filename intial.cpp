
#include<stdio.h>
#include<iostream>
#include<string>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>  
#include "intial.h"
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
//#include <conio>
using namespace std;

void start_shell()
{
  //clear
  int fd1,re;
  char* fil;
  char nm[100];
  string s="ann.myrc";

    
    re = setenv("PS1","$",1); 
    printf("\n\n\n\n**********************************************************************************************************"); 
    printf("\n\n\n\t****MY SHELL****"); 
   // printf("\n\n\t-USE AT YOUR OWN RISK-"); 
    printf("\n\n\n\n**********************************************************************************************************\n\n"); 
    
    cout<<getenv("PS1")<<" "; // gets the value in currnt environmnt

/*******************************set .myrc file********************************************/

    uid_t u=getuid();
    struct passwd *ps =getpwuid(u);
    if(ps == NULL)
    {
      cout<<"err reading usrname\n";
    }
    char* p=(char*)"PATH ";

    char *path =(char*)"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";

     char *usernam=ps->pw_name;
     char *home = ps->pw_dir;


     
     char* str4=(char*)"HOME ";
     char * str5 = (char *) malloc(1 + strlen(str4)+ strlen(home) );
      strcpy(str5, str4);
      strcat(str5, home);
     
    //printf("\n\n @%s", usernam);
    //printf("$: ");
    char* str1=(char*)"USER ";
    char * str3 = (char *) malloc(1 + strlen(str1)+ strlen(usernam) );
     strcpy(str3, str1);
      strcat(str3, usernam); //str3 contains the data to be written to myrc
    char* ps1=(char*)"PS1 "; 
    fil =(char*)s.c_str();
    fd1 =open(fil, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR); //symbolic constants are provided fr mode
    if(fd1<0)
      cout<<"err creatng file\n";
    write(fd1,p,strlen(p));
   // write(fd1,"\n",2);
    write(fd1,path,strlen(path));
    write(fd1,"\n",2);
    write(fd1,str3,strlen(str3));// usrname writtn to .myrc
    gethostname( nm, sizeof(nm)); // nm contain HOSTNAME
    char *str7=(char*)"HOSTNAME ";
    char *str8 = (char*)malloc(1+strlen(str8) + strlen(nm));
    strcpy(str8,str7);
    strcat(str8,nm);
    write(fd1,"\n",2);
    write(fd1,str8,strlen(str8));
    write(fd1,"\n",2);
    write(fd1,str5,strlen(str5));
    write(fd1,"\n",2);
    write(fd1,ps1,strlen(ps1));
    write(fd1,"$",1);
    write(fd1,"\n",2);
    close(fd1);
    /********************************SET ENVIRONMNT VARIABLES for this shell process*********************************************/
    re =setenv("PATH","/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin",1);
    
    //re = setenv();
    sleep(1); 
   
}

void setmybashrc()
{
  /*int fd1= open("/home/user/.bashrc", O_RDONLY); 
  char line[10000];
  int cnt;

  int fd2 =open("mybashrc.txt",O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  if (fd1 < 0)  
    { 
        cout<<"cant open file\n";
        exit(1); 
    } 

    cnt=read(fd1,line,9999);
    write(fd2,line,cnt);*/

}

/*void split_word(char arr[MAXI])
{
  printf("jk\n");
}*/

/*void autocomplete(string s)
{

}*/