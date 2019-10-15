#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 25;
const int maxm = 3005;

int T,n,m,tot,maxflow,source,sink,lab[maxn],list[maxn];
int a[maxn],b[maxm],c[maxm],d[maxm];

inline void read(int &x)
{
	static char ch;
	x = 0;
	do ch = getchar(); while (ch < '0' || ch > '9');
	do x = x * 10 + ch - 48, ch = getchar(); while (ch >= '0' && ch <= '9');
}

void insert(int x,int y,int z)
{
	tot ++;
	b[tot] = y;
	d[tot] = z;
	c[tot] = a[x];
	a[x] = tot;
}

void Initialize()
{
	read(n); read(m);
	source = 1; sink = n;
	tot = 1;
	fo(i,1,n) a[i] = 0;
	fo(i,1,m)
	{
		int x,y,z;
		read(x), read(y), read(z);
		insert(x,y,z);
		insert(y,x,0);
	}
}

inline bool bfs()
{
	int st,en;
	list[st=en=1] = source;
	memset(lab,255,sizeof lab);
	lab[source] = 0;
	while (st <= en)
	{
		int x = list[st];
		for(int i = a[x];i;i = c[i])
			if (d[i] && lab[b[i]] == -1)
			{
				lab[b[i]] = lab[x] + 1;
				list[++en] = b[i];	
			}
		st ++;
	}
	return lab[sink] > -1;
}

inline int dfs(int x,int flow)
{
	if (x == sink) return flow;
	int ret = 0;
	for (int i = a[x];i;i = c[i])
		if (d[i] && lab[b[i]] == lab[x] + 1)
		{
			int now = dfs(b[i],min(flow,d[i]));
			d[i] -= now;
			d[i^1] += now;
			flow -= now;
			ret += now;
			if (!flow) return ret;
		}
	lab[x] = -1;
	return ret;
}

void Work()
{
	maxflow = 0;
	while (bfs()) maxflow += dfs(source,0x7fffffff);
}

int main(void)
{
	scanf("%d",&T);
	fo(cs,1,T)
	{
		Initialize();
		Work();
		printf("Case %d: %d\n",cs,maxflow);
	}
}
