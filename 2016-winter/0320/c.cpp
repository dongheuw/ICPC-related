#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

int n;

struct Person
{
	int len;
	char name[256];
	int rank[100];
}a[1005];

bool cmp(const Person &a,const Person &b)
{
	int lim = max(a.rank[0],b.rank[0]);
	fo(i,1,lim)
	{
		if (a.rank[i] > b.rank[i]) return 1;
		if (a.rank[i] < b.rank[i]) return 0;
	}
	lim = max(a.len,b.len);
	fo(i,1,lim)
	{
		if (a.name[i] < b.name[i]) return 1;
		if (a.name[i] > b.name[i]) return 0;
	}
	return 1;
}

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	scanf("%d",&n);
	fo(i,1,n)
	{
		char s[100];
		scanf("%s",s+1);
		int len = strlen(s+1);
		a[i].len = len - 1;
		fo(j,1,len) a[i].name[j] = s[j];
		string cl; cin >> cl;
		while (cl != "class")
		{
			if (cl == "upper") a[i].rank[++a[i].rank[0]] = 1;
			if (cl == "lower") a[i].rank[++a[i].rank[0]] = -1;
			if (cl == "middle") a[i].rank[++a[i].rank[0]] = 0;
			cin >> cl;
		}
		fo(j,1,a[i].rank[0]/2)
			swap(a[i].rank[j],a[i].rank[a[i].rank[0]-j+1]);
	}
	sort(a+1,a+1+n,cmp);
	fo(i,1,n)
	{
		fo(j,1,a[i].len) printf("%c",a[i].name[j]);
		printf("\n");
	}
	return 0;
}
