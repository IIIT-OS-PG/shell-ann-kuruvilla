#include<iostream>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<bits/stdc++.h>
#include<sys/wait.h> 

using namespace std;

int main()
{
	char* arg[5];
	int i;
	pid_t pid,r;
	/*string s="wj";
	arg[0]=(char*)s.c_str();
	
	cout<<arg[0]<<endl;*/
	pid =fork();
	if(pid==0)
	{
	vector<string> v;
	v.push_back("ls");
	v.push_back("-l");
	v.push_back("-a");
	v.push_back("<<");
	v.push_back("1.txt");
	string st="<<";
	
	
		if( find(v.begin(),v.end(),st) != v.end())
		{
			cout<<"helo"<<endl;
			for(i=0;v[i]!="<<";i++)
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

		}
	}
	else
	{
		r=wait(NULL);
	}

	//cout<<arg[1]<<endl;

	return 0;
}