#include<bits/stdc++.h>
using namespace std;


struct Trie{

	unordered_map<char, Trie*> mp;
	bool wrdend;
};

Trie* addnewnode()
{
	Trie *nod = new Trie;
	nod->wrdend= false;
	return nod;
}

void inserttotrie(struct Trie* &t,string word)		//one thng we cn do is whn user types a new cmnd insert to trie
{
	if(t==NULL)
	{
		t= addnewnode();
	}
	Trie *temp = t;
	int i;
	for(i=0;i<word.size();i++)
	{
		char lettr =word[i];
		if(temp->mp.find(lettr)== temp->mp.end())
		{
			temp->mp.insert(make_pair(lettr, addnewnode()));
		}
		
		 temp = temp->mp[lettr];	
	}
	temp->wrdend =true;
}

int main()
{
	int i;
	vector<string> library ={"ls","ls -l","ls -l -a","ls -lf -a","cd","cd .","cd ..","pwd","grep"};
	Trie *head = NULL;
	for(i=0;i<library.size();i++)
	{
		inserttotrie(head,library[i]);
	}

return 0;
}	