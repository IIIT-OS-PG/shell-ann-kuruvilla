#include<iostream>
#include<bits/stdc++.h>
#include<stdio.h>

#include<string>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h> 
#include "intial.h"
#include<fcntl.h>
#include "splitwrd.h"
#include "pipedup.h"
#include "make_background.h"
#include "alarmset.h"

using namespace std;

int main()
{
	start_shell();
	pid_t pid,r,pr;
	
	//cout<<"WELCOME"<<endl;
	
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
		string st=">>";
			st+='\0';
		string st4=">";	
			st4+='\0';
		string st5="setalarm";	
			st5+='\0';
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

		if(user_input=="$$")
		{
			cout<<getppid();
			exit(1);
		}
		
		v=split_word(user_input);
		if(find(v.begin(),v.end(),st5)!=v.end())
			 setalarm(v);
		/**********************MAKE TO BCKGRND****************/
		else if(find(v.begin(),v.end(),st3) !=v.end())
		{
			
			to_background(v);
		}

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

		/******************************O/P REDIRECTION >>**************************/

		else 
		{

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
			int fd=open(filenm,O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
			dup2(fd,1);
			
			execvp(arg[0],arg);
			close(fd);
			//exit(1);
			}
				/******************************oupt redirection >*****************/
			else if(find(v.begin(),v.end(),st4)!=v.end())
			{
				for(i=0;v[i]!=st4;i++)
				{
				arg[i]=(char*)v[i].c_str();
				//cout<<arg[i]<<endl;
				}
				arg[i]=NULL;
				char* filenm = (char*)v[i+1].c_str();
				int fd = open(filenm,O_RDWR | O_CREAT | O_TRUNC,S_IRUSR | S_IWUSR );
				dup2(fd,1);// redirect op to file
				execvp(arg[0],arg);
				close(fd);
				
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
		//shmdt((void *) shmPTR);//prnt detached shrd memory
		//shmctl(shmID, IPC_RMID, NULL);//deleted shrd my
	}

	else
	{
		cout<<"error creating child\n";
	}
}


	return 0;
}