#include<unistd.h>
#include<bits/stdc++.h>
#include<fcntl.h>
#include<sys/wait.h> 

using namespace std;

int main()
{
	pid_t pid,r;
	int flg=0;
	int i=0;
	char* arg[6];
	string s="annku";
	string st="";
	for(i=0;i<s.size();i++)
	 st+=s[i];
	st+='\0';
	s+='\0';
	if(st==s)
		cout<<"same\n";
	i=0;


	pid =fork();
	if(pid==0)
	{
		string st="<<";

		vector<string> v;
		cout<<"heloooo";
	v.push_back("ls");
	v.push_back("-l");
	v.push_back("-a");
	v.push_back("<<");
	v.push_back("1.txt");
	flg=1;

		
		if(flg==1)
		{
			cout<<"helo";
			while(v[i].compare(st)!=0)
			{
				arg[i]=(char*)v[i].c_str();
				//cout<<arg[i]<<endl;
				i++;
			}
			arg[i]=NULL;
			char* filenm = (char*)v[i].c_str();
			int fd=open("1.txt",O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
			if(fd ==1)
				cout<<"print error\n";
			dup2(fd,1);
			
			execvp(arg[0],arg);
			close(fd);
			//exit(1);
		}
		else
		{
			cout<<"no direction\n";
		}
}

	else if( pid > 0)
	{
		
		r =wait(NULL);
	}

	else
	{
		cout<<"child nt creatd\n";
	}
	return 0;
}