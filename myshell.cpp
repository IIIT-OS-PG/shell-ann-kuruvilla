#include<iostream>
#include<bits/stdc++.h>
#include<stdio.h>
#include<string>
#include <fstream> 
#include <map>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <cstdio>
#include <cstdlib>
#include<unistd.h>
#include<sys/types.h>
#include <sys/stat.h>
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
	//int 
	//vector<string> an;
	start_shell();
	pid_t pid,r,pr;
	int chidprocstatus,ree;
	int back_flg;
	int root_set=0;
	//vector<string> an;

	
	while(1)
	{
		char ch,pr;
		back_flg=0;
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
		string st7="~";
		 st7+='\0';	
		 string st9="alias";
		 st9+='\0';
		ch = cin.get();
		while(ch!='\n')
		{

		  if(ch!='\t')
		  {
		  	user_input+=ch;
		  	pr =ch;
		  	ch =cin.get();
		  }
		 
		}
		
	if(pr=='&')
	{
		cout<<"bck flg set\n";
		back_flg=1;
		//pr=(char*)"";
	}	

	if( user_input=="su root")
    {
      ree=setenv("PS1","#",1);
      //cout<<getenv("PS1");
      //cout<<"setenv done\n";
      root_set=1;
      
    }
    if(user_input=="sudo su")
    {
    	ree=setenv("PS1","#",1);
    }
    if(user_input=="exit")
    {
      ree=setenv("PS1","$",1);
      root_set=0;
      
    }

    // if(user_input=="cd ..")
		// {									/**************cd /home/user/Desktop**********************/

			
		// 	string homepath="";
		// 	char pathnam[1000];
		// 	if(v[1]==st7)
		// 	{
		// 		homepath ="/home/user";
		// 		pth=(char*)homepath.c_str();

		// 	}
		// 	else
		// 	{	
		// 	 pth = (char*)v[1].c_str();
		// 	 cout<<pth<<"pth set to\n";
		// 	}
		// 	int r=chdir(pth);
		// 	if(r==-1)
		// 		cout<<"ERR settng directry\n";
		// 	printf("%s\n", getcwd(pathnam, 1000));
		// 	exit(1);
			
		// }

	pid =fork();
	if(pid==0)
	{
		//child process
		int i,j,flag,k,re;
		flag=0;
		
		 ofstream fout;
		 ifstream fin; 
		 string lin;
		 char line[1000];
		vector<string> v;

		vector<string> vt;
		vector<string> v1;
		char* arg[NOOFFLAGS];
		char* arg1[NOOFFLAGS];
		char* pth;
	
		
		if(user_input=="$$")
		{
			cout<<getppid();
			exit(1);
		}
		if(user_input=="$?")
		{
			cout<<chidprocstatus<<"\n";
			exit(1);
		}
		
		if(user_input=="exit")
		{
			re=setenv("PS1","$",1);
			root_set=0;
			exit(1);
		}
		
		v=split_word(user_input);
		v1 =v;
		if(find(v.begin(),v.end(),st9)!=v.end())
		{
			//string aliasename = v[1];
			vector<string> lines;
			
			fout.open("aliases.txt",ios::app);  /*------------CREATE aliases.txt frst**********/
			 fout<<user_input<<endl;
			fout.close(); 
			
			 exit(1);

		}
		else if(user_input=="sudo su")
		{
			re =setenv("PS1","#",1);
			arg[0]=(char*)v[0].c_str();
			arg[1]=(char*)v[1].c_str();
			arg[2]=NULL;
			execvp(arg[0],arg);
		}
		else if( user_input=="su root")
		{
			re =setenv("PS1","#",1);
			//cout<<"in child sttng\n";
			arg[0]=(char*)v[0].c_str();
			arg[1]=(char*)v[1].c_str();
			arg[2]=NULL;
			execvp(arg[0],arg);
		}

		else if(find(v.begin(),v.end(),st5)!=v.end())
			 setalarm(v);
		/**********************MAKE TO BCKGRND****************/
		else if(find(v.begin(),v.end(),st3) !=v.end())
		{
			
			to_background(v);
		}

		/**********************HANDLING CD********************/
		// else if(v[0]==cd)
		// {									/**************cd /home/user/Desktop**********************/

			
		// 	string homepath="";
		// 	char pathnam[1000];
		// 	if(v[1]==st7)
		// 	{
		// 		homepath ="/home/user";
		// 		pth=(char*)homepath.c_str();

		// 	}
		// 	else
		// 	{	
		// 	 pth = (char*)v[1].c_str();
		// 	 cout<<pth<<"pth set to\n";
		// 	}
		// 	int r=chdir(pth);
		// 	if(r==-1)
		// 		cout<<"ERR settng directry\n";
		// 	printf("%s\n", getcwd(pathnam, 1000));
		// 	exit(1);
			
		// }
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
				int fd = open(filenm, O_RDWR | O_CREAT | O_TRUNC,S_IRUSR | S_IWUSR );
				dup2(fd,1);// redirect op to file
				execvp(arg[0],arg);
				close(fd);
				
			}
			/********************************BASIC COMMANDS**************************************/
			else
			{
			  fin.open("aliases.txt");
			   vector<string> line; 
			   vector<string> vt2;
			   vector<string> vt1;
			   int flgg;
			   user_input+='\0';
			   while (fin)
			   { 
			    getline(fin, lin);
			    vt1=split_word(lin);
			    
			     
			     flgg=0;
			    
			    	if(vt1[1]==user_input)
			    	{
			    		flgg=1;
			    		break;
			    		
			    	}
			    
			   
			   }
			   fin.close();
			    if(flgg==1)
			    {
			    	k=0;
			    	for(i=2;i<vt1.size();i++)
			    	{
			    		arg1[k]=(char*)vt1[i].c_str();
			    		cout<<arg1[k++];
			    	}
			    	arg1[k]=NULL;
			    
			    execvp(arg1[0],arg1);
			    }
			   
			  
				
			/************************************BASIC**************************************/

			for( i=0;i<v1.size();i++)
			{

				arg[i]=(char*)v1[i].c_str();
				//cout<<arg[i]<<endl;
			}
			//cout<<"\n";
			arg[i]=NULL;
			char* cmd= arg[0];
			if(execvp(cmd,arg)<0)
			{
				
				
				cout<<"Invalid command : Error in execvp\n";

			}
			exit(1);
	    	}

		}

	}

	else if( pid > 0)
	{
		if(back_flg==0)
		{
		  r =wait(&chidprocstatus);
		  cout<<"prnt waits\n";
		}

		cout<<getenv("PS1")<<" ";

	}

	else
	{
		cout<<"error creating child\n";
	}
}


	return 0;
}