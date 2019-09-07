
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
  int fd1;
  char* fil;
  char nm[100];
  string s="ann.myrc";
    printf("\n\n\n\n******************"
        "******************************************************************************************************"); 
    printf("\n\n\n\t****MY SHELL****"); 
   // printf("\n\n\t-USE AT YOUR OWN RISK-"); 
    printf("\n\n\n\n*******************"
        "*******************************************************************************************************"); 
    /*******************************set .myrc file********************************************/
    uid_t u=getuid();
    struct passwd *ps =getpwuid(u);
    char *usernam=ps->pw_name;
     char *home = ps->pw_dir;
     char* str4="$HOME: ";
     char * str5 = (char *) malloc(1 + strlen(str4)+ strlen(home) );
      strcpy(str6, str4);
      strcat(str6, home);
    //cout<<"usrnme is"<<usernam<<endl;
    printf("\n\n @%s", usernam);
    printf("$: ");
    fil =(char*)s.c_str();
    fd1 =open(fil, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR); //symbolic constants are provided fr mode
    if(fd1<0)
      cout<<"err creatng file\n";
    char* str1="USER: ";
    char * str3 = (char *) malloc(1 + strlen(str1)+ strlen(usernam) );
      strcpy(str3, str1);
      strcat(str3, usernam); //str3 contains the data to be written to myrc
    
    write(fd1,str3,strlen(str3));// usrname writtn to .myrc
    gethostname( nm, sizeof(nm));
    //fclose()
    write(fd1,nm,strlen(nm));
    write(fd1,str6,strlen(str6));

    close(fd1);
   // sleep(1); 
   
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