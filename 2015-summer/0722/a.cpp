#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define sqr(x) ((x)*(x))

using namespace std;

const int maxn = 1005;

struct edge
{
	int p1,p2,next;
	double dis;
}e[maxn*maxn];

int T,n,tot,father[maxn],mst[maxn],p[maxn];
double cost[maxn][maxn],x[maxn],y[maxn];
bool vis[maxn];

void Add(int u,int v,double dis)
{
	e[tot].p1 = u;
	e[tot].p2 = v;
	e[tot].dis = dis;
	tot ++;
}

bool cmp(const edge &a,const edge &b)
{
	return a.dis < b.dis;
}

double Dist(int i,int j)
{
	return sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]));
}

void Initialize()
{
	scanf("%d",&n);
	fo(i,0,n-1) scanf("%lf%lf%d",&x[i],&y[i],&p[i]);
	tot = 0;
	fo(i,0,n-1) fo(j,0,i-1) Add(i,j,Dist(i,j));
	fo(i,0,n) father[i] = i;
	sort(e,e+tot,cmp);
}

int Get(int x)
{
	if (father[x] == x) return x;
	father[x] = Get(father[x]);
	return father[x]; 
}

bool Combine(int x,int y)
{
	int fx = Get(x), fy = Get(y);
	if (fx == fy) return 0;
	father[fx] = fy;
	return 1;
}

void AddMst(int u,int v,double dis)
{
	e[tot].p1 = u;
	e[tot].p2 = v;
	e[tot].dis = dis;
	e[tot].next = mst[u];
	mst[u] = tot ++;
}

double Kruskal()
{
	double ret = 0;
	int m = tot, num = 0;
	memset(mst,-1,sizeof mst);
	fo(i,0,m-1)
	{
		if (Combine(e[i].p1,e[i].p2))
		{
			ret += e[i].dis;
			AddMst(e[i].p1,e[i].p2,e[i].dis);
			AddMst(e[i].p2,e[i].p1,e[i].dis);
			if (++ num == n-1) break;
		}
	}
	return ret;
}

void Maxcost(int st,int u,double mx)
{
	vis[u] = 1;
	for (int i = mst[u];i != -1;i = e[i].next)
	{
		int v = e[i].p2;
		if (vis[v]) continue;
		cost[st][v] = max(mx,e[i].dis);
		Maxcost(st,v,cost[st][u]);
	}
}

void Work()
{
	double Mst = Kruskal();
	double ans = 0;
	fo(i,0,n-1)
	{
		memset(vis,0,sizeof vis);
		Maxcost(i,i,0);
	}
	fo(i,0,n-1)
		fo(j,0,i-1)
			ans = max(ans,double(p[i]+p[j])/(Mst-cost[i][j]));
	printf("%.2lf\n",ans);
}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	for (scanf("%d",&T);T;T --)
	{
		Initialize();
		Work();
	}
	return 0;
}
