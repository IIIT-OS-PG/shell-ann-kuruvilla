
#include<stdio.h>
#include<iostream>
#include<string>
#include "intial.h"
#include <stdlib.h>
#include <unistd.h>
//#include <conio>


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

/*void split_word(char arr[MAXI])
{
  printf("jk\n");
}*/

/*void autocomplete(string s)
{

}*/