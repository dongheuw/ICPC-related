#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 100005;
const int maxe = 200005;
const int inf = 0x3f3f3f3f;

struct Node
{
	int dis,idx;
	Node(){}
	Node(int dis,int idx):dis(dis),idx(idx){}
	bool operator<(const Node &a) const
	{
		if (dis != a.dis) return dis < a.dis;
		return idx < a.idx;
	}
	bool operator>(const Node &a) const
	{
		return a < *this;
	}
	bool operator<=(const Node &a) const
	{
		return !(a < *this);
	}
	bool operator>=(const Node &a) const
	{
		return !(*this < a);
	}
	Node operator+(const int &val) const
	{
		return Node(dis+val,idx);
	}
	Node operator-(const int &val) const
	{
		return Node(dis-val,idx);
	}
}node[maxn],S[maxn];

struct Edge
{
	int v,c;
	Edge *next;
}E[maxe],*H[maxn],*edge;

int Time,vis[maxn],siz[maxn],num[maxn],mart[maxn],ans[maxn],dis[maxn];
int Q[maxn],head,tail,size,root,cnt,n;

void Clear()
{
	edge = E;
	num[0] = n;
	memset(H,0,sizeof H);
	head = tail = 0;
	memset(ans,0,sizeof ans);
}

void Add(int u,int v,int c)
{
	edge->v = v;
	edge->c = c;
	edge->next = H[u];
	H[u] = edge ++;
}

void SPFA()
{
	while (head != tail)
	{
		int u = Q[head ++];
		if (head == maxn) head = 0;
		vis[u] = Time - 1;
		for (Edge *e = H[u];e;e = e->next)
		{
			int v = e->v;
			Node tmp = node[u] + e->c;
			if (node[v] > tmp)
			{
				node[v] = tmp;
				if (vis[v] != Time)
				{
					vis[v] = Time;
					Q[tail ++] = v;
					if (tail == maxn) tail = 0;
				}
			}
		}
	}
}

void Get_siz(int u,int fa = 0)
{
	siz[u] = 1;
	for (Edge *e = H[u];e;e = e->next)
	{
		int v = e->v;
		if (v != fa && vis[v] != Time)
		{
			Get_siz(v,u);
			siz[u] += siz[v];
		}
	}
}

void Get_root(int u,int fa = 0)
{
	num[u] = 0;
	for (Edge *e = H[u];e;e = e->next)
	{
		int v = e->v;
		if (v != fa && vis[v] != Time)
		{
			Get_root(v,u);
			num[u] = max(num[u],siz[v]);
		}
	}
	num[u] = max(num[u],size-siz[u]);
	if (num[u] < num[root]) root = u;
}

void Get_dis(int u,int val,int fa = 0)
{
	dis[u] = val;
	S[++cnt] = node[u] - val;
	for (Edge *e = H[u];e;e = e->next)
	{
		int v = e->v;
		if (v != fa && vis[v] != Time) Get_dis(v,dis[u]+e->c,u);
	}
}

int Search(const Node &x)
{
	int l = 0, r = cnt;
	while (l < r)
	{
		int m = (l + r + 1) >> 1;
		if (S[m] <= x) l = m;
		else r = m - 1;
	}
	return r;
}

void Get_ans(int u,int sign,int fa = 0)
{
	if (!mart[u])
	{
		int tmp = Search(Node(dis[u],u));
		ans[u] += (cnt-tmp) * sign;
	}
	for (Edge *e = H[u];e;e = e->next)
	{
		int v = e->v;
		if (v != fa && vis[v] != Time) Get_ans(v,sign,u);
	}
}

void Deal(int u,int val,int sign)
{
	cnt = 0;
	Get_dis(u,val);
	sort(S+1,S+cnt+1);
	Get_ans(u,sign);
}

void Divide(int u)
{
	Get_siz(u);
	size = siz[u];
	root = 0;
	Get_root(u);
	vis[root] = Time;
	Deal(root,0,1);
	for (Edge *e = H[root];e;e = e->next) if (vis[e->v] != Time) Deal(e->v,e->c,-1);
	for (Edge *e = H[root];e;e = e->next) if (vis[e->v] != Time) Divide(e->v);
}

void Work()
{
	Clear();
	fo(i,1,n-1)
	{
		int x,y,c;
		scanf("%d%d%d",&x,&y,&c);
		Add(x,y,c), Add(y,x,c);
	}
	fo(i,1,n)
	{
		scanf("%d",&mart[i]);
		if (mart[i])
		{
			node[i] = Node(0,i);
			Q[tail ++] = i;
		} else node[i] = Node(inf,0);
	}
	Time ++; SPFA();
	Time ++; Divide(1);
	int ret = 0;
	fo(i,1,n) ret = max(ret,ans[i]);
	printf("%d\n",ret);
}

int main()
{
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);
	Time = 0;
	memset(vis,0,sizeof vis);
	while (~scanf("%d",&n)) Work();
	return 0;
}
