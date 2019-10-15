#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

#define eps 1e-4
#define INF 0x3f3f3f3f

int head[110],cnt,id[110][110];
int n,m,l[110],vis[110],flag[600],num;
double sum[110][110];
struct node
{
	int u,v;
	double w;
	int next,id;
}edge[2100],p[600];

queue<int> Q;
vector<int> vec;

void add(int u,int v,double w,int id)
{
	edge[cnt].u = u;edge[cnt].v = v;edge[cnt].w = w;
	edge[cnt].next = head[u];edge[cnt].id = id;head[u] = cnt++;
	edge[cnt].u = v;edge[cnt].v = u;edge[cnt].w = 0;
	edge[cnt].next = head[v];edge[cnt].id = id;head[v] = cnt++;
}
int bfs(int s,int t)
{
	int u,v;
	memset(l,-1,sizeof l);
	while (!Q.empty()) Q.pop();
	Q.push(s);
	l[s] = 0;
	while (!Q.empty())
	{
		u = Q.front();
		Q.pop();
		for (int i = head[u];i != -1;i = edge[i].next)
		{
			v = edge[i].v;
			if (l[v] == -1 && edge[i].w >= eps)
			{
				l[v] = l[u] + 1;
				Q.push(v);
			}
		}
	}
	return l[t] > 0;;
}

double dfs(int u,int t,double flow)
{
	if (u == t) return flow;
	double temp,ret = 0;
	for (int i = head[u];i != -1;i = edge[i].next)
	{
		int v = edge[i].v;
		if (l[v] == l[u] + 1 && edge[i].w >= eps && (temp = dfs(v,t,min(flow,edge[i].w))))
		{
			edge[i].w -= temp;
			edge[i^1].w += temp;
			ret += temp;
			flow -= temp;
			if (flow < eps) break;
		}
	}
	if (ret >= eps) return ret;
	l[u] = -1;
	return 0;
}

double solve(double mid)
{
	double ans = 0,temp;
	memset(head,-1,sizeof head);
	memset(flag,0,sizeof flag);
	cnt = num = 0;
	for (int i = 0;i < m;i++)
	{
		if (p[i].w - mid < 0)
		{
			flag[i] = 1;
			num ++;
			ans += p[i].w-mid;
			continue;
		}
		add(p[i].u,p[i].v,p[i].w-mid,i);
		add(p[i].v,p[i].u,p[i].w-mid,i);
	}
	while (bfs(1,n))
		while ((temp = dfs(1,n,INF)) >= eps) ans += temp;
	return ans;
}

void f_dfs(int u)
{
	for (int i = head[u];i != -1;i = edge[i].next)
	{
		int v = edge[i].v;
		if (vis[v] || edge[i].w < eps) continue;
		vis[v] = 1;
		f_dfs(v);
	}
}

void f()
{
	memset(vis,0,sizeof vis);
	vis[1] = 1;
	f_dfs(1);
	for (int i = 0;i < cnt;i += 2)
	{
		int u = edge[i].u, v = edge[i].v;
		if (vis[u] && !vis[v] && edge[i].w < eps && !flag[ id[u][v] ])
		{
			flag[id[u][v]] = 1;
			num ++;
		}
	}
}

int main()
{
	double low,mid,high,temp;
	while (scanf("%d %d", &n, &m) != EOF)
	{
		low = mid = high = 0.0;
		memset(head,-1,sizeof head);
		cnt = 0;
		for (int i = 0;i < m;i++)
		{
			scanf("%d %d %lf", &p[i].u,&p[i].v,&p[i].w);
			id[p[i].u][p[i].v] = id[p[i].v][p[i].u] = i;
			high += p[i].w;
		}
		while (high - low >= eps)
		{
			mid = (high + low) / 2.0;
			temp = solve(mid);
			if (fabs(temp) < eps) break;
			if (temp < 0) high = mid;
			else low = mid;
		}
		f();
		printf("%d\n", num);
		for (int i = 0;i < m && num;i++)
		{
			if (!flag[i]) continue;
			num --;
			if (num) printf("%d ", i+1);
			else printf("%d\n", i+1);
		}
		printf("\n");
	}
	return 0;
}
