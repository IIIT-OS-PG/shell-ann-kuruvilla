#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<sys/wait.h> 
#include"splitwrd.h"

using namespace std;
/********************************FN FOR PIPED COMMANDS***************************/

void pipeimpl(vector<string> ve)
{
	 
	pid_t p,r,sta;
	string pi="|";
	pi+='\0';
	//int n= 2;
	int pipes[4];
	int i;
	pipe(pipes);
	pipe(pipes+2);
	char* args1[NOOFFLAGS];
	char* args2[NOOFFLAGS];
	char* args3[NOOFFLAGS];
	int k=0;
	for(i=0;ve[i]!=pi;i++)
	{
		args1[k]=(char*)ve[i].c_str();
		//cout<<args1[k]<<endl;
		k++;
	}
	args1[k]=NULL;
	i++;
	k=0;
	for(;ve[i]!=pi;i++)
	{
		args2[k]=(char*)ve[i].c_str();
		//cout<<args2[k]<<endl;
		k++;
	}
	args2[k]=NULL;
	i++;
	k=0;
	for(;i<ve.size();i++)
	{
		args3[k]=(char*)ve[i].c_str();
		//cout<<args3[k]<<endl;
		k++;
	}
	args3[k]=NULL;
		/***********************************************  EXECUTING FRST COMMND**********************************************/  
	if(fork() ==0 )
		    {

		    	dup2(pipes[1], 1);//write to write end of frst pipe
		    		close(pipes[0]);
		      		close(pipes[1]);
		     	 close(pipes[2]);
		      	close(pipes[3]);
		    //  cout<<"frst child\n";
		      execvp(args1[0], args1);
		      exit(1);
		    	
		    }
		
   /***********************************************  EXECUTING SCND COMMND****************************************/
     if (fork() == 0)
		{
	 
 
	  	dup2(pipes[0], 0); //read from read end of frst pipe
	  	dup2(pipes[3],1); //write to write end of scnd pipe
		  close(pipes[0]);
		  close(pipes[1]);
		  close(pipes[2]);
		  close(pipes[3]);
		 // cout<<"scnd child\n";

	  		execvp(args2[0], args2);
	  		

	  		exit(1);
		}


	
	if(fork()==0)
		{
			
			dup2(pipes[2],0);//read frm read end of scnd pipe
			close(pipes[0]);
			close(pipes[1]);
		  close(pipes[2]);
		  close(pipes[3]);
		  execvp(args3[0], args3);
		  exit(1);

		}
	


	
	 close(pipes[0]);
	 close(pipes[1]);
	  close(pipes[2]);
	close(pipes[3]);
   for (i = 0; i < 2; i++)   
      sta=wait(NULL);
  
}





/*int main()
{
	string vi="ps aux | grep root | wc -l";
	vector<string> v;
	v=split_word(vi);
	for(int i=0;i<v.size();i++)
		cout<<v[i]<<endl;
	pipeimpl(v);
	return 0;

}*/