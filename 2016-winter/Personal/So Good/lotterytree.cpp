#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 105;
int N,P,a[maxn][maxn],vis[maxn],sta[maxn];

bool dfs(int x,int N,bool f[maxn][maxn])
{
	fo(i,1,N)
		if (!vis[i] && f[x][i])
		{
			vis[i] = 1;
			if (!sta[i] || dfs(sta[i],N,f)) return sta[i] = x, 1;
		}
	return 0;
}

bool DP(int x,int X,int Y)
{
	if ((int)(double(X)*P/Y) == (int)(double(X+1)*P/Y-1e-5)) return 1;
	if (!a[x][0]) return 0;
	
	bool f[maxn][maxn];
	memset(f,0,sizeof f);
	fo(i,1,a[x][0])
		fo(j,1,a[x][0]) f[i][j] = DP(a[x][j],a[x][0]*X+i-1,a[x][0]*Y);
		
	memset(sta,0,sizeof sta);
	fo(i,1,a[x][0])
	{
		memset(vis,0,sizeof vis);
		if (!dfs(i,a[x][0],f)) return 0;
	}
	return 1;
}

int main()
{
	while (scanf("%d%d",&N,&P) == 2)
	{
		memset(a,0,sizeof a);
		fo(i,1,N-1)
		{
			int x; scanf("%d",&x);
			a[x][++a[x][0]] = i;
		}
		puts(DP(0,0,1)?"YES":"NO");
	}
	return 0;
}
