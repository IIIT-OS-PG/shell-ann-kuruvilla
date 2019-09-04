#include<iostream>
#include<bits/stdc++.h>
#include<stdio.h>
#include<string>
#include<unistd.h>
#include<iostream>
#include<sys/types.h>
#include<sys/wait.h> 
#include "intial.h"
#include<fcntl.h>
#include "new.h"

using namespace std;

int main()
{
	start_shell();
	pid_t pid,r,pr;
	//commandexec();

	pid =fork();
	if(pid==0)
	{
		//child process
		int i,j,flag;
		flag=0;
		vector<string> v;
		vector<string> v1;
		char* arg[NOOFFLAGS];
		/*char* arg1[4];
		arg1[0]=(char*)"ls";
		arg1[1]=(char*)"-l";
		arg1[2]=(char*)"-a";
		arg1[3]=NULL;*/
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
		

		string st="<<";
			st+='\0';
		

		if(find( v.begin(),v.end(),st) != v.end() )
		{
			
			for(i=0;v[i]!=st;i++)
			{
				arg[i]=(char*)v[i].c_str();
				//cout<<arg[i]<<endl;
			}
			arg[i]=NULL;
			char* filenm = (char*)v[i].c_str();
			int fd=open("1.txt",O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
			dup2(fd,1);
			
			execvp(arg[0],arg);
			close(fd);
			//exit(1);
		}
		else
		{
			cout<<"No redirection\n";
			
			for( i=0;i<v.size();i++)
			{

				arg[i]=(char*)v[i].c_str();
				//cout<<arg[i]<<endl;
			}
			//cout<<"\n";
			arg[i]=NULL;
			char* cmd= arg[0];
			execvp(cmd,arg);
			exit(1);
	    }

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