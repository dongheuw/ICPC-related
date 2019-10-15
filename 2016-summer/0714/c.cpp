#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 205;
int cs,n,m,t,a[maxn][maxn],c[maxn][maxn],p[maxn];
bool flag[maxn];

bool dfs(int x)
{
	fo(i,1,a[x][0])
		if (!flag[a[x][i]])
		{
			flag[a[x][i]] = 1;
			if (!p[a[x][i]] || dfs(p[a[x][i]]))
			{
				p[a[x][i]] = x;
				return 1;
			}
		}
	return 0;
}

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	scanf("%d%d%d",&n,&m,&t);
	while (n+m+t > 0)
	{
		memset(c,0,sizeof c);
		fo(i,1,t)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			c[u][v] = 1;
		}
		memset(a,0,sizeof a);
		fo(i,1,n)
			fo(j,1,m)
				if (c[i][j] == 0) a[i][++a[i][0]] = j;
		int match = 0;
		memset(p,0,sizeof p);
		fo(i,1,n)
		{
			memset(flag,0,sizeof flag);
			if (dfs(i)) match ++;
		}
		printf("Case %d: %d\n",++cs,n+m-match);
		scanf("%d%d%d",&n,&m,&t);
	}
	return 0;
}
