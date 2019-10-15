#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define fo(i,a,b) for (int i = a;i <= b;i++)
#define fd(i,a,b) for (int i = a;i >= b;i--)

using namespace std;

typedef long long LL;

const int maxn = 100050;

int T,n,pw[maxn],sum[maxn],f[21][maxn];
LL K;
int sa[maxn],Rank[maxn],rk[maxn],tank[maxn],tmp[maxn],height[maxn];
char s[maxn];

int heightmin(int x,int y){return height[x] < height[y] ? x : y;}

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
	fo(i,1,n) f[0][i] = i;
	fo(i,1,20)
		for (int j = 1;j+(1<<i)-1 <= n;j ++)
			f[i][j] = heightmin(f[i-1][j],f[i-1][j+(1<<(i-1))]);
}

int Query(int l,int r)
{
	if (l > r) swap(l,r);
	l ++;
	if (l == r) return f[0][l];
	int k = r - l + 1;
	return heightmin(f[pw[k]][l],f[pw[k]][r-(1<<pw[k])+1]);
}

void Work(int cs)
{
    sum[0] = 0;
    fo(i,1,n) sum[i] = sum[i-1] + n - sa[i];
    int h = 0, pos = 0, len;
    int l = 1, r = n;
    while (l < r)
    {
    	int mid = Query(l,r) - 1;
    	if (K <= LL(height[mid+1]-h)*(r-l+1))
    	{
    		pos = l;
    		len = h + K / (r-l+1) + (K % (r-l+1) != 0);
    		break;
    	}
    	K -= LL(height[mid+1]-h)*(r-l+1);
    	if (K <= sum[mid]-sum[l-1]-(LL)height[mid+1]*(mid-l+1)) r = mid;
    	else
    	{
    		K -= sum[mid]-sum[l-1]-(LL)height[mid+1]*(mid-l+1);
    		l = mid + 1;
    	}
    	h = height[mid+1];
    }
    if (!pos) pos = l, len = h + K;
    printf("Case %d: ",cs);
    fo(i,0,len-1) printf("%c",s[sa[pos]+i]);
    printf("\n");
}

int main()
{
	freopen("j.in","r",stdin);
	freopen("j.out","w",stdout);
	for (int i = 1,j = 0;i < maxn;i ++)
    {
        if (i > 1 << (j+1)) j ++ ;
        pw[i] = j ;
    }
	scanf("%d",&T);
	fo(cs,1,T)
	{
		Initialize();
		Work(cs);
	}
	return 0;
}
