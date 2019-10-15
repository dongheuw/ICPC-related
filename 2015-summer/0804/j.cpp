#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 205;
const int MNode = 205 * 500;
int T,N,M,K,tot,num,a[maxn][maxn],p[maxn],used[maxn],ans[MNode];
vector<int> g[MNode];
bool vis[maxn];

bool Find(int x)
{
	for (int i = 0;i < g[x].size();i ++)
		if (!vis[g[x][i]])
		{
			vis[g[x][i]] = 1;
			if (!used[g[x][i]] || Find(used[g[x][i]]))
			{
				used[g[x][i]] = x;
				return 1;
			}
		}
	return 0;
}

int Hungary()
{
	int ret = 0;
	memset(used,0,sizeof used);
	for (int i = tot-1;i >= 0;i --)
		for (int j = i*K;j < (i+1)*K;j ++)
		{
			memset(vis,0,sizeof vis);
			if (Find(j)) ret ++, ans[i] ++;
		}
	return ret;
}

void dfs(int x)
{
	vis[p[num ++] = x] = 1;
	fo(i,1,N) if (!vis[i] && a[x][i]) dfs(i);
}

int main()
{
	freopen("j.in","r",stdin);
	freopen("j.out","w",stdout);
	for (scanf("%d",&T);T;T --)
	{
		scanf("%d%d%d",&N,&M,&K);
		memset(a,0,sizeof a);
		for (int i = 0;i < MNode;i ++) g[i].clear();
		tot = 0;
		fo(i,1,M)
		{
			int sig,x,y,z;
			scanf("%d",&sig);
			if (sig == 1)
			{
				scanf("%d",&x);
				num = 0;
				memset(vis,0,sizeof vis);
				dfs(x);
				for (int i = 0;i < num;i ++)
					for (int j = tot*K;j < (tot+1)*K;j ++)
						g[j].push_back(p[i]);
				tot ++;
			} else if (sig == 2)
			{
				scanf("%d%d",&x,&y);
				a[x][y] = a[y][x] = 1;
			} else
			{
				for (scanf("%d",&z);z;z --)
				{
					scanf("%d%d",&x,&y);
					a[x][y] = a[y][x] = 0;
				}
			}
		}
		memset(ans,0,sizeof ans);
		int ret = Hungary();
		printf("%d\n",ret);
		for (int i = 0;i < tot;i ++) printf("%d%c",ans[i],i==tot-1?'\n':' ');
	}
	return 0;
}
