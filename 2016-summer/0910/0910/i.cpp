#include <bits/stdc++.h>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 2000005;
const int maxm = 200005;

int T,n,m,head[maxn],tot,S;
int dis[maxn];
set<int> link,tmp;

struct Edge
{
	int v,next;
}edge[maxm];

void Add(int u,int v)
{
	edge[tot].v = v;
	edge[tot].next = head[u];
	head[u] = tot ++;
}

void BFS()
{
	fo(i,1,n) dis[i] = 0x7f7f7f7f;
	link.clear(), tmp.clear();
	fo(i,1,n) if (i != S) link.insert(i);
	queue<int> Q;
	while (!Q.empty()) Q.pop();
	Q.push(S); dis[S] = 0;
	while (!Q.empty())
	{
		int u = Q.front(); Q.pop();
		for (int i = head[u];i != -1;i = edge[i].next)
		{
			int v = edge[i].v;
			if (link.count(v) == 0) continue;
			link.erase(v), tmp.insert(v);
		}
		for (set<int>::iterator it = link.begin();it != link.end();it ++)
			Q.push(*it), dis[*it] = dis[u] + 1;
		link.swap(tmp), tmp.clear();
	}
}

int main()
{
	freopen("i.in","r",stdin);
	freopen("i.out","w",stdout);
	for (scanf("%d",&T);T;T --)
	{
		scanf("%d%d",&n,&m);
		tot = 0;
		fo(i,1,n) head[i] = -1;
		fo(i,1,m)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			Add(u,v), Add(v,u);
		}
		scanf("%d",&S);
		BFS();
		int cnt = 0;
		fo(i,1,n)
			if (i != S)
			{
				cnt ++;
				if (dis[i] == 0x7f7f7f7f) dis[i] = -1;
				if (cnt == n-1) printf("%d\n",dis[i]);
				else printf("%d ",dis[i]);
			}
	}
	return 0;
}
