#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define fd(i,a,b) for (int i = a;i >= b;i --)

using namespace std;

const int maxn = 200005; //200005

int T,N;
char s[maxn];
int sa[maxn],Rank[maxn],rk[maxn],tmp[maxn],tank[maxn],height[maxn];
int nxt[maxn];

void BuildSA(char *s)
{
	memset(tank,0,sizeof tank);
	fo(i,1,N) tank[(int)s[i]] ++;
	fo(i,1,255) tank[i] += tank[i-1];
	fd(i,N,1) sa[tank[(int)s[i]]--] = i;
	int j = 0;
	fo(i,1,N)
	{
		if (i == 1 || s[sa[i]] != s[sa[i-1]]) j ++;
		Rank[sa[i]] = j;
	}
	for (int k = 1;k <= N;k <<= 1)
	{
		int j = 0;
		fo(i,N+1,N+k) tmp[++j] = i-k;
		fo(i,1,N) if (sa[i] > k) tmp[++j] = sa[i]-k;
		memset(tank,0,(N+1)*4);
		fo(i,1,N) tank[Rank[tmp[i]]] ++;
		fo(i,1,N) tank[i] += tank[i-1];
		fd(i,N,1) sa[tank[Rank[tmp[i]]]--] = tmp[i];
		copy(Rank+1,Rank+1+N,rk+1);
		j = 0;
		fo(i,1,N)
		{
			if ((i == 1) || ((rk[sa[i]] != rk[sa[i-1]]) || (rk[sa[i]] == rk[sa[i-1]] && rk[sa[i]+k] != rk[sa[i-1]+k]))) j ++;
			Rank[sa[i]] = j;
		}
	}
	s[N+1] = '!';
	fo(i,1,N)
	{
		if (Rank[i] == 1) continue;
		height[Rank[i]] = max(0,height[Rank[i-1]]-1);
		while (s[i+height[Rank[i]]] == s[sa[Rank[i]-1]+height[Rank[i]]]) height[Rank[i]] ++;
	}
}

int main()
{
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);
	scanf("%d",&T);
	for (int cas = 1;cas <= T;cas ++)
	{
		char x[3];
		scanf("%s",x);
		scanf("%s",s+1);
		N = strlen(s+1);
		BuildSA(s);
		nxt[N+1] = N+1;
		fd(i,N,1)
			if (s[i] == x[0]) nxt[i] = i; else nxt[i] = nxt[i+1];
		long long ans = 0;
		fo(i,1,N)
		{
			if (nxt[sa[i]] > N) continue;
			int tmp = max(height[i],nxt[sa[i]]-sa[i]);
			ans += N-sa[i]+1-tmp;
		}
		printf("Case #%d: %lld\n",cas,ans);
	}
	return 0;
}
