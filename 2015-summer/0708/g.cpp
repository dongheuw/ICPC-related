#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 15;
int T,s[maxn][maxn],a[maxn],ans,flag[maxn];

void dfs(int x,int sum)
{
	if (x > 11)
	{
		if (sum > ans) ans = sum;
	} else
	{
		fo(i,1,11) 
			if (!flag[i] && s[i][x])
			{
				flag[i] = 1;
				dfs(x+1,sum+s[i][x]);
				flag[i] = 0;
			}
	}
}

int main()
{
	freopen("g.in","r",stdin);
	freopen("g.out","w",stdout);
	scanf("%d",&T);
	while (T --)
	{
		fo(i,1,11) fo(j,1,11) scanf("%d",&s[i][j]);
		ans = 0;
		memset(flag,0,sizeof (flag));
		dfs(1,0);
		printf("%d\n",ans);
	}
	return 0;
}
