#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h> 
#include "intial.h"
#include "new.h"


int main()
{
	start_shell();
	pid_t pid,r;
	//commandexec();

	pid =fork();
	if(pid==0)
	{
		//child process
		int i,j;
		char* arg[NOOFFLAGS];
		char user_input[MAXI];
		printf("enter command\n");
		fgets(user_input,MAXI,stdin);


		split_word(user_input,arg);

		
		
		
		//exit(0);

	}

	else if( pid > 0)
	{
		//parent process
		r =wait(NULL);
	}

	else
	{
		printf("error creating child\n");
	}


	return 0;
}