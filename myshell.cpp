#include<iostream>
#include<stdio.h>
#include<string>
#include<unistd.h>
#include<iostream>
#include<vector>
#include<sys/types.h>
#include<sys/wait.h> 
#include "intial.h"
#include "new.h"

using namespace std;

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
		vector<string> v;
		char* arg[NOOFFLAGS];
		char* arg1[4];
		arg1[0]=(char*)"ls";
		arg1[1]=(char*)"-l";
		arg1[2]=(char*)"-a";
		arg1[3]=NULL;
		char ch;
		string user_input;
		printf("enter command\n");
		//fgets(user_input,MAXI,stdin);
		ch = cin.get();
		while(ch!='\n')
		{

		  if(ch!='\t')
		  {
		  	user_input+=ch;
		  	ch =cin.get();
		  }
		  else
		  {
		  	//autocomplete(user_input);
		  	break;
		  }
		}

		//cout<<user_input;
		v=split_word(user_input);
		for( i=0;i<v.size();i++)
		{

		arg[i]=(char*)v[i].c_str();
		//cout<<arg[i]<<endl;
		}
		//cout<<"\n";
		arg[i]=NULL;
		char* cmd= arg[0];
		execv("ls",arg1);
		exit(1);

	}

	else if( pid > 0)
	{
		
		r =wait(NULL);
	}

	else
	{
		cout<<"error creating child\n";
	}


	return 0;
}