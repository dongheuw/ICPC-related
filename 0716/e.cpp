#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define pb push_back

using namespace std;

const int maxn = 1005;
const int maxm = 50005;
const int inf = (int)1e8;

int T,n,m;
int d[maxn],q[maxn],path[maxn];
bool vis[maxn],ban[maxm],flag;

struct verti
{
	int v,w,id;
	verti(int a,int b,int c)
	{
		v = a; w = b; id = c;
	}
};
vector<verti> V[maxn];


void SPFA()
{
	queue<int> Q;
	memset(vis,0,sizeof vis);
	fo(i,0,n) d[i] = inf;
	d[0] = 0; vis[0] = 1; Q.push(0);
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop(), vis[u] = 0;
		int s = V[u].size();
		fo(i,0,s-1)
		{
			int id = V[u][i].id;
			if (ban[id]) continue;
			int v = V[u][i].v;
			int w = V[u][i].w;
			if (d[u] + w < d[v])
			{
				d[v] = d[u] + w;
				if (flag)
				{
					path[v] = u;
					q[v] = id;
				}
				if (!vis[v])
				{
					Q.push(v);
					vis[v] = 1;
				}
			}
		}
	}
}

int main()
{
	freopen("e.in","r",stdin);
	freopen("e.out","w",stdout);
	for (scanf("%d",&T);T;T --)
	{
		scanf("%d%d",&n,&m);
		fo(i,0,n) V[i].clear();
		fo(i,0,m-1)
		{
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			a --, b --;
			V[a].pb(verti(b,c,i));
			V[b].pb(verti(a,c,i));
		}
		flag = 1;
		memset(ban,0,sizeof ban);
		SPFA();
		flag = 0;
		if (d[n-1] == inf)
		{
			printf("-1\n");
			continue;
		}
		int ans = inf;
		bool did = 1;
		for (int i = n-1;i;i = path[i])
		{
			ban[q[i]] = 1;
			SPFA();
			ban[q[i]] = 0;
			if (d[n-1] == inf)
			{
				ans = -1;
				break;
			}
			if (did) ans = d[n-1], did = 0;
			else ans = max(ans,d[n-1]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
