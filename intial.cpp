
#include<stdio.h>
#include<iostream>
#include<string>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>  
#include "intial.h"
#include <stdlib.h>
#include <unistd.h>
//#include <conio>
using namespace std;

void start_shell()
{
	//clear(); 
    printf("\n\n\n\n******************"
        "************************"); 
    printf("\n\n\n\t****MY SHELL****"); 
   // printf("\n\n\t-USE AT YOUR OWN RISK-"); 
    printf("\n\n\n\n*******************"
        "***********************"); 
    char* username = getenv("USER"); 
    printf("\n\n\nUSER is: @%s", username); 
    printf("\n"); 
    sleep(1); 
   // clear(); 
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