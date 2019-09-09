#include<iostream>
#include<vector>
//#include<map>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<sys/wait.h>
#include<time.h>

using namespace std;

string msg;

void displaymsg(int s)
{
	cout<<msg<<"!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
	cout<<"\n";
}
void setalarm(vector<string> ve)
{	


	pid_t p;
	p=fork();
	if(p==0)
	{
		int i,siz,ho,mi,se;
		siz = ve.size();
		 msg = ve[siz-1];

		string h=ve[1];
		//cout<<h<<"val of h"<<endl;
		ho=(h[0]-'0')*10 + (h[1]-'0');
		mi = (h[3]-'0')*10 + (h[4]-'0');
		se = (h[6]-'0')*10 +(h[7]-'0');
		int secsy,diff;
		int ti = ho*3600 + mi*60 +se;
		time_t T= time(NULL);
		struct  tm tm = *localtime(&T);
		cout<<"systm time:"<<tm.tm_hour<<":"<<tm.tm_min<<":"<<tm.tm_sec<<endl;
		secsy = tm.tm_hour*3600 + tm.tm_min*60 + tm.tm_sec;
		diff=ti-secsy;
		signal(SIGALRM, displaymsg);
		alarm(diff);
		pause();
	}
	else
	{
		//wait(NULL);

		//cout<<"prnt";
	 
	}
	
	}