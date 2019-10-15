#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<iostream>

#define fo(i,a,b) for (int i = a;i <= b;i++)
#define fd(i,a,b) for (int i = a;i >= b;i--)
using namespace std;

const int maxn = 200050;

int n;
int sa[maxn],rank[maxn],rk[maxn],tank[maxn],tmp[maxn],height[maxn];
char s[maxn];

int main(void)
{
	freopen("jz1598.in","r",stdin);
	freopen("jz1598.out","w",stdout);
	
	cin >> (s+1);
	n = strlen(s+1);
	memset(tank,0,sizeof tank);
	fo(i,1,n) tank[s[i]] ++;
	fo(i,1,255) tank[i] += tank[i-1];
	fo(i,1,n) sa[tank[s[i]]--] = i;
	int j = 0;
	fo(i,1,n)
	{
		if (i == 1 || s[sa[i]] != s[sa[i-1]]) j ++;
		rank[sa[i]] = j;
	}
	for (int k = 1;k <= n;k <<= 1)
	{
		j = 0;
		fo(i,n+1,n+k) tmp[++j] = i - k;
		fo(i,1,n) if (sa[i] > k) tmp[++j] = sa[i] - k;
		memset(tank,0,sizeof tank);
		fo(i,1,n) tank[rank[tmp[i]]] ++;
		fo(i,1,n) tank[i] += tank[i-1];
		fd(i,n,1) sa[tank[rank[tmp[i]]]--] = tmp[i];
		copy(rank+1,rank+1+n,rk+1);
		j = 0;
		fo(i,1,n)
		{
			if ((i == 1) || (rk[sa[i]] != rk[sa[i-1]]) || (rk[sa[i]] == rk[sa[i-1]] && rk[sa[i]+k] != rk[sa[i-1]+k]))
				j ++;
			rank[sa[i]] = j;
		}
	}
	fo(i,1,n)
	{
		height[rank[i]] = max(0,height[rank[i-1]]-1);
		while (s[i+height[rank[i]]] == s[sa[rank[i]-1]+height[rank[i]]]) height[rank[i]] ++;	
	}
	int ans = 0;
	fo(i,1,n)
		if (height[i] > height[i-1]) ans += height[i] - height[i-1];
	cout<<ans<<endl;
	
	return 0;
}
