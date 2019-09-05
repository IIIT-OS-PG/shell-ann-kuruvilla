#include<bits/stdc++.h>
#include<stdio.h>
#include<iostream>
#include<string>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>  
#include "intial.h"
#include <stdlib.h>
#include <unistd.h>

using namespace std;

void to_background(vector<string> ve)
{
	pid_t p,r;
	int i;
	p=fork();
	if(p==0)
	{
		char* argss[NOOFFLAGS];
		for( i=0;i<ve.size()-1;i++)
			{
				argss[i]=(char*)ve[i].c_str();
				//cout<<arg[i]<<endl;
			}
			argss[i]=NULL;
		r=setsid();
		//cout<<"r"<<"hello";

		
		int devNull = open("/dev/null", O_WRONLY);
		dup2(devNull,STDOUT_FILENO);
		execvp(argss[0],argss);
	}
}
