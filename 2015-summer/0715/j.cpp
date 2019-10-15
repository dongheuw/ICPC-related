#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define fo(i,a,b) for (int i = a;i <= b;i++)
#define fd(i,a,b) for (int i = a;i >= b;i--)

using namespace std;

typedef long long LL;

const int maxn = 100050;

int T,n;
LL K;
int sa[maxn],Rank[maxn],rk[maxn],tank[maxn],tmp[maxn],height[maxn],p[maxn];
char s[maxn];

void Initialize()
{
	scanf("%s %lld",s+1,&K);
	n = strlen(s+1);
	memset(tank,0,sizeof tank);
	fo(i,1,n) tank[s[i]] ++;
	fo(i,1,255) tank[i] += tank[i-1];
	fo(i,1,n) sa[tank[s[i]]--] = i;
	int j = 0;
	fo(i,1,n)
	{
		if (i == 1 || s[sa[i]] != s[sa[i-1]]) j ++;
		Rank[sa[i]] = j;
	}
	for (int k = 1;k <= n;k <<= 1)
	{
		j = 0;
		fo(i,n+1,n+k) tmp[++j] = i - k;
		fo(i,1,n) if (sa[i] > k) tmp[++j] = sa[i] - k;
		memset(tank,0,sizeof tank);
		fo(i,1,n) tank[Rank[tmp[i]]] ++;
		fo(i,1,n) tank[i] += tank[i-1];
		fd(i,n,1) sa[tank[Rank[tmp[i]]]--] = tmp[i];
		copy(Rank+1,Rank+1+n,rk+1);
		j = 0;
		fo(i,1,n)
		{
			if ((i == 1) || (rk[sa[i]] != rk[sa[i-1]]) || (rk[sa[i]] == rk[sa[i-1]] && rk[sa[i]+k] != rk[sa[i-1]+k])) j ++;
			Rank[sa[i]] = j;
		}
	}
	fo(i,1,n)
	{
		height[Rank[i]] = max(0,height[Rank[i-1]]-1);
		while (s[i+height[Rank[i]]] == s[sa[Rank[i]-1]+height[Rank[i]]]) height[Rank[i]] ++;	
	}
}

LL Check(int mid)
{
	LL res = 0;
	fo(i,1,mid) res += n - sa[i] + 1;
	int Min = height[mid+1];
	fo(i,mid+1,n)
	{
		res += Min;
		Min = min(Min,height[i+1]);
		if (!Min) break;
	}
	return res;
}

void Work(int cs)
{
	int l = 0, r = n;
	while (l < r)
	{
		int mid = (l + r + 1) >> 1;
		if (Check(mid) < K) l = mid;
		else r = mid - 1;
	}
	LL res = Check(l);
	l ++;
	p[l] = n - sa[l] + 1;
	fo(i,l+1,n) p[i] = min(p[i-1],height[i]);
	int x = n;
	fo(i,height[l]+1,n-sa[l]+1)
	{
		for (;x > l && p[x] < i;x --);
		if (res + (x-l+1) >= K)
		{
			printf("Case %d: ",cs);
			fo(j,1,i) printf("%c",s[sa[l]+j-1]);
			printf("\n");
			break;
		}
		res += x-l+1;
	}
}

int main()
{
	freopen("j.in","r",stdin);
	freopen("j.out","w",stdout);
	scanf("%d",&T);
	fo(cs,1,T)
	{
		Initialize();
		Work(cs);
	}
	return 0;
}
