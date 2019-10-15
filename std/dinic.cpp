#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 105;
const int maxm = 160000;

int n,m,tot,ans,maxflow,source,sink;
int w[maxn][maxn][2],e[maxn][maxn],lab[maxn*maxn];
int a[maxn*maxn],b[maxm],c[maxm],d[maxm];

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
	read(n);
	read(m);
	source = 0; sink = n*m+1;
	tot = 1;
	ans = 0;
	int x;
	fo(i,1,n)
		fo(j,1,m)
		{
			read(x);
			ans += x;
			w[i][j][0] += x * 2;
		}
	fo(i,1,n)
		fo(j,1,m)
		{
			read(x);
			ans += x;
			w[i][j][1] += x * 2;
		}
	memset(e,0,sizeof e);
	fo(i,1,n-1)
		fo(j,1,m)
		{
			read(x);
			ans += x;
			w[i][j][0] += x;
			w[i+1][j][0] += x;
			e[i][j] += x;
		}
	fo(i,1,n-1)
		fo(j,1,m)
		{
			read(x);
			ans += x;
			w[i][j][1] += x;
			w[i+1][j][1] += x;
			e[i][j] += x;
		}
	fo(i,1,n-1)
		fo(j,1,m)
		{
			insert((i-1)*m+j,i*m+j,e[i][j]);
			insert(i*m+j,(i-1)*m+j,e[i][j]);
		}
	memset(e,0,sizeof e);
	fo(i,1,n)
		fo(j,1,m-1)
		{
			read(x);
			ans += x;
			w[i][j][0] += x;
			w[i][j+1][0] += x;
			e[i][j] += x;
		}
	fo(i,1,n)
		fo(j,1,m-1)
		{
			read(x);
			ans += x;
			w[i][j][1] += x;
			w[i][j+1][1] += x;
			e[i][j] += x;
		}
	fo(i,1,n)
		fo(j,1,m-1)
		{
			insert((i-1)*m+j,(i-1)*m+j+1,e[i][j]);
			insert((i-1)*m+j+1,(i-1)*m+j,e[i][j]);
		}
	fo(i,1,n)
		fo(j,1,m)
		{
			insert(source,(i-1)*m+j,w[i][j][0]);
			insert((i-1)*m+j,source,0);
			insert((i-1)*m+j,sink,w[i][j][1]);
			insert(sink,(i-1)*m+j,0);
		}
}

inline bool bfs()
{
	static int list[maxn*maxn];
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
	while (bfs()) 
		maxflow += dfs(source,0x7fffffff);
	ans -= maxflow / 2;
}

void Print()
{
	printf("%d\n",ans);
}

int main(void)
{
	Initialize();
	Work();
	Print();
}
