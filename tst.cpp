#include<iostream>
#include<stdio.h>
using namespace std;

int main()
{
	char* arg[5];
	string s="wj";
	arg[0]=(char*)s.c_str();
	
	cout<<arg[0]<<endl;
	//cout<<arg[1]<<endl;

	return 0;
}