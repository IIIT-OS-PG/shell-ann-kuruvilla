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
#include "pipeimple.h"
#include "make_background.h"

using namespace std;

int main()
{
	start_shell();
	pid_t pid,r,pr;
	cout<<"WELCOME"<<endl;
	//commandexec();
	//pid_t myshell=getpid();
	 //cout<<myshell<<endl;
	 //pid_t myshellgrup=getpgid(myshell);
	 //cout<<"shell grup id:"<<myshellgrup<<endl;

	while(1)
	{
	pid =fork();
	if(pid==0)
	{
		//child process
		int i,j,flag;
		flag=0;
		vector<string> v;
		vector<string> v1;
		char* arg[NOOFFLAGS];
		char* pth;
		
		char ch;
		string user_input;
		string cd="cd";
		cd+='\0';
		string st2="|";
		st2+='\0';
		string st3="&";
		st3+='\0';
		
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

		
		v=split_word(user_input);
		/**********************MAKE TO BCKGRND****************/
		if(find(v.begin(),v.end(),st3) !=v.end())
			to_background(v);

		/**********************HANDLING CD********************/
		else if(v[0]==cd)
		{
			char pathnam[1000];
			pth = (char*)v[1].c_str();
			int r=chdir(pth);
			

			printf("%s\n", getcwd(pathnam, 1000));
			
		}
		/*********************PIPE COMMANDS********************************/
		else if(find(v.begin(),v.end(),st2) != v.end())
			pipeimpl(v);

		else 
		{
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
			//char *file
			char* filenm = (char*)v[i+1].c_str();
			int fd=open(filenm,O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
			dup2(fd,1);
			
			execvp(arg[0],arg);
			close(fd);
			//exit(1);
			}
			/********************************BASIC COMMANDS**************************************/
			else
			{
			
			
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

	}

	else if( pid > 0)
	{
		
		r =wait(NULL);

	}

	else
	{
		cout<<"error creating child\n";
	}
}


	return 0;
}