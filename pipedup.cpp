#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <string>
#include<bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<sys/wait.h> 
//#include"splitwrd.h"

using namespace std;
/********************************FN FOR PIPED COMMANDS***************************/

void pipeimpl(vector<string> ve)
{

	pid_t p,r,sta;

	string pi="|";
	pi+='\0';
	int i,j,n;
	ve.push_back(pi);

	 n=count(ve.begin(),ve.end(),pi);//no of pipes
	
	//cout<<"val of n:"<<n<<endl;
	n=n-1;
	int f,savefdw,savefdr = 0;
	// for(i=0;i<ve.size();i++)
	// {
	// 	cout<<ve[i]<<endl;

	// }
	//cout<<"vectr of wrds retrnd frm split fn\n";
	int k=0; //pointng to each wrd in ve
	i=0;
	while(i<=n)
	{
		//cout<<"val in the parent: "<<i<<endl;
		int pipes[2];
		pipe(pipes);
		f=0;
		//char* args1[10];
		//args1[0]="ls";
	//	args1[1]=NULL;
		char *args[10];
		for(;ve[k]!=pi;k++)
		{
			args[f]=(char*)ve[k].c_str();
			//cout<<"inside while " <<args[f]<<" ";
			f++;
			//cout<<"parnt fillng args "<<endl;
		}
		args[f]=NULL;
		k++;
		//cout<<k<<"value of k th word\n";
		
		pid_t pid= fork();	
		if(pid==-1)
		 cout<<"error\n";
		
		else if(pid==0)
		{
			
			if(i==0)//frst cmmnd
			{
				

				dup2(pipes[1],STDOUT_FILENO);
				if(execvp(args[0],args)<0)
				 cout<<"err in execvp\n";	

			}
		
			else if( i==n )
			{
				//cout<<"last cmnd\n";
				if(dup2(savefdr,STDIN_FILENO)<0)
					cout<<"error in dup";
					close(pipes[1]);
				if(execvp(args[0],args)<0)
				 cout<<"err in execvp\n";	

			}
			else
			{
				cout<<"intermediate cmnd\n";
				//cout<<"2nd command\n";
				if(dup2(savefdr,STDIN_FILENO)<0)
					cout<<"error in dup";
				
				if(dup2(pipes[1],STDOUT_FILENO)<0)
					cout<<"error in dup";
				 //close(pipes[0]);
				 //close(pipes[1]);
				if(execvp(args[0],args)<0)
				 cout<<"err in execvp\n";	
			}
		}
		//cout<<"done fork\n";
			r=wait(NULL);
			i++;
			// if(i==n+1)
			// {
			// 	close(pipes[1]);
			// 	close(pipes[0]);
			// }

		//savefdw =pipes[1]; //store write end of prev cmnd
		savefdr=pipes[0]; //store read end of prev pipe
		//cout<<"val of savefdw:"<<savefdw<<endl;
		//close(pipes[0]);
	    close(pipes[1]);
		}	

	//	close(pipes[0]);
	//	close(pipes[1]);

	}  
	
		
  

/*  vector<string> split_word(string s)
{
	
	vector<string> wrds;
	int i,l;
	l=s.size();
	i=0;
	string wrd="";
	while(i<l )
	{
		while(s[i]!='\0' && s[i]!=' ')
		 wrd+=s[i++];

		if(s[i]==' ')
		 {
		 	wrd+='\0';
		 	wrds.push_back(wrd);
		 	//if(wrd==st)
		 		//cout<<"same";
		 	wrd="";

		 }
		 i++;

	}
	wrd+='\0';
	//cout<<wrd<<"hi"<<endl;

	wrds.push_back(wrd);

	
return wrds;	
	
}

/*int main()
{
	
	string user_input;
	char ch;
	ch = cin.get();
		while(ch!='\n')
		{

		  if(ch!='\t')
		  {
		  	user_input+=ch;
		  	ch =cin.get();
		  }
		}
	vector<string> v;
	v=split_word(user_input);
	//for(int i=0;i<v.size();i++)
	//	cout<<v[i]<<endl;
	//cout <<"main"<<endl;
	pipeimpl(v);
	return 0;

}*/