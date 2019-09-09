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
	start_shell();
	pid_t pid,r,pr;
	int chidprocstatus;
	//int back_flg=0;
	// int    shmID;
 //     int    *shmPTR;
 //     shmID = shmget(IPC_PRIVATE, 2*sizeof(int), IPC_CREAT | 0666);
 //     if (shmID < 0) {
 //          printf(" shmget error \n");
 //          exit(1);
 //     }
 //     shmPTR = (int *) shmat(shmID, NULL, 0);
 //     if (shmPTR == (int*)-1) {
 //          printf(" shmat error \n");
 //          exit(1);
 //     }
 //     shmPTR[0]=0;
	
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
		int i,j,flag,k,re,root_set;
		flag=0;
		//back_flg=0;
		root_set=0;
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
		if(user_input=="$?")
		{
			cout<<chidprocstatus<<"\n";
			exit(1);
		}
		if( user_input=="su root")
		{
			re=setenv("PS1","#",1);
			cout<<getenv("PS1");
			root_set=1;
			exit(1);
		}
		if(user_input=="exit" && root_set==1)
		{
			re=setenv("PS1","$",1);
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
			// fin.open("aliases.txt");     
			//  while (fin)
			//  { 
			//    getline(fin, lin);
			//    lines.push_back(lin);
			   
			//   }
			  // for(i=0;i<lines.size();i++)
			  // 	cout<<lines[i]<<endl;
			   //fin.close();
			  // if(find(lines.begin(),lines.end(),user_input) != lines.end())
			  //    {	
			  //    	auto ite=find(lines.begin(),lines.end(),user_input);
			  //    	string to_split = *ite;
			  //    	//cout<<to_split<<"spli\n";
			  //    	vt =split_word(to_split);
			  //    	k=0;
			  //    	for(i=2;i<vt.size();i++)
			  //    	{
			  //    		arg[k++]=(char*)vt[i].c_str();
			  //    	}
			  //    	arg[k]=NULL;
			  //    	execvp(arg[0],arg);
			  //    }
			 exit(1);

		}

		else if(find(v.begin(),v.end(),st5)!=v.end())
			 setalarm(v);
		/**********************MAKE TO BCKGRND****************/
		else if(find(v.begin(),v.end(),st3) !=v.end())
		{
			// shmID = shmget(IPC_PRIVATE, 2*sizeof(int), 0666);
			// shmPTR = (int *) shmat(shmID, NULL, 0);

			// shmPTR[0]=1;
			to_background(v);
		}

		/**********************HANDLING CD********************/
		else if(v[0]==cd)
		{
			//cout<<"cd hndl\n";
			string homepath="";
			char pathnam[1000];
			if(v[1]==st7)
			{
				homepath ="/home/user";
				pth=(char*)homepath.c_str();

			}
			else
			{	
			 pth = (char*)v[1].c_str();
			}
			int r=chdir(pth);
			printf("%s\n", getcwd(pathnam, 1000));
			//exit(1);
			
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
			    //cout<<lin<<"frm file"<<endl;
			    vt1=split_word(lin);
			    //cout<< vt1[0]<<endl;
			    //cout<<vt1[1]<<endl;
			   //line.push_back(lin);
			  // cout<<lin<<endl;
			     
			     flgg=0;
			    
			    	if(vt1[1]==user_input)
			    	{
			    		flgg=1;
			    		break;
			    		//cout<<"same\n";
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
			   
			  // for(i=0;i<line.size();i++)
			     //{
			   	  //cout<<line[i]<<"opp"<<endl;
			   	  // string to_split = line[i];
			       // vector<string> vt1=split_word(to_split);
			    	 // cout<< vt1[0]<<"spi";
			    	 // for(j=0;j<vt1.size();j++)
			    	 // {
			    	 // 	//cout<<vt1[j]<<" ";
			    	 // 	//cout<<user_input<<"usrin";
			    	 // 	user_input+='\0';
			    	 // 	 if(vt1[1]==user_input)
			    	 // 	 {
			   	 	// 		flgg=1;
			   	 	// 		//cout<<"her";
			   	 	// 		vt2=vt1;
			   	 	// 		break;
			   	 	// 	    }
			   	 	//}
			    	// if(flgg==1)
			    	 //	break;
			  //  }
			 //    if(flgg==1)
			 //    {
				//     k=0;
				//    for( i=2;i<vt2.size();i++)
				// 	{
				// 		//cout<<vt2[i];
				// 		//cout<<"he";
				// 	  arg1[k]=(char*)vt2[i].c_str();
				// 	//cout<<arg[k]<<endl;
				// 	 k++;
				// 	}
				// 	 arg1[k]=NULL;
				// 	 execvp(arg1[0],arg1);
				// }
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
		//if(!back_flg)
		 r =wait(&chidprocstatus);
		//  if(shmPTR[0]==0)
		//   r =wait(&chidprocstatus);
		// shmdt((void *) shmPTR);
		// shmctl(shmID, IPC_RMID, NULL);//deleted shrd my
		

	}

	else
	{
		cout<<"error creating child\n";
	}
}


	return 0;
}