#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

int N,K;
string s[4];
map<string,int> rec;

int main()
{
	freopen("k.in","r",stdin);
	freopen("k.out","w",stdout);
	scanf("%d",&N);
	while (N --)
	{
		scanf("%d",&K);
		fo(i,0,K-1) cin >> s[i];
		sort(s,s+K);
		string temp;
		fo(i,1,(1<<K)-1)
		{
			temp = "";
			fo(j,0,K-1)
				if(i & (1 << j)) temp = temp + s[j] + "+";
			rec[temp] ++; 
		}
	} 
	scanf("%d",&N);
	while (N --)
	{
		scanf("%d",&K);
		string temp = ""; 
		fo(i,0,K-1) cin >> s[i];
		sort(s,s+K);
		fo(i,0,K-1) temp = temp + s[i] + "+";
		printf("%d\n",rec[temp]);
	} 
	return 0;
}
