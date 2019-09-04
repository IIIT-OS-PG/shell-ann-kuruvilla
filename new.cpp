#include<bits/stdc++.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "new.h"
#include<string>
#include<vector>
//try c++11
using namespace std;


	
vector<string> split_word(string s)
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
		 	wrd="";

		 }
		 i++;

	}
	wrd+='\0';
	//cout<<wrd<<"hi"<<endl;
	wrds.push_back(wrd);

	
return wrds;	
	
}

