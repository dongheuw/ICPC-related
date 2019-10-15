#include <cstdio>
#include <cstring>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define max(a,b) ((a)>(b)?(a):(b))

using namespace std;

const int maxn = 110;
const int mod = 100000000;

int n,m,k,id[maxn],order[maxn],cnt;
vector<int> g[maxn],gt[maxn];
bool vst[maxn],lnk[maxn][maxn];
long long c[maxn][maxn][20],dp[maxn][maxn][20],tmp[20];
int inDu[maxn],outDu[maxn],pointNum[maxn],start[maxn];

void dfs1(int u)
{
	vst[u] = 1;
	for (unsigned i = 0;i < g[u].size();i ++)
		if (!vst[g[u][i]]) dfs1(g[u][i]);
	order[cnt++] = u;
}

void dfs2(int u)
{
	vst[u] = 1; id[u] = cnt;
	for (unsigned i = 0;i < gt[u].size();i ++)
		if (!vst[gt[u][i]]) dfs2(gt[u][i]);
}

void show(long long a[])
{
	long long len = max(a[0],1);
	while (len > 1 && a[len] == 0) len --;
	for (int i = len;i > 0;i --)
		if (i == len) printf("%lld",a[i]);
	else printf("%08lld",a[i]);
	printf("\n");
}

void assign(long long b[],long long a[])
{
	for (int i = 0;i <= 10;i ++) b[i] = a[i];
}

long long d[20];
void add(long long c[],long long a[],long long b[])
{
	for (int i = 0;i <= 10;i ++) d[i] = 0;
	d[0] = max(a[0],b[0]);
	for (int i = 1;i <= d[0];i ++) d[i] = a[i] + b[i];
	for (int i = 1;i <= d[0];i ++)
		if (d[i] >= mod)
		{
			d[i+1] ++;
			d[i] -= mod;
			if (i == d[0]) d[0] ++;
		}
	assign(c,d);
}

void mult(long long c[],long long a[],long long b[])
{
	for (int i = 1;i <= 10;i ++) c[i] = 0;
	c[0] = a[0] + b[0] - 1;
	for (int i = 1;i <= a[0];i ++)
		for (int j = 1;j <= b[0];j ++)
			c[i+j-1] += a[i] * b[j];
	for (int i = 1;i <= c[0];i ++)
		if (c[i] >= mod)
		{
			c[i+1] += c[i] / mod;
			c[i] %= mod;
			if (i == c[0]) c[0] ++;
		}
}

void solve()
{
	memset(vst,0,sizeof vst);
	cnt = 0;
	for (int i = 1;i <= n;i ++)
		if (!vst[i]) dfs1(i);
	cnt = 0;
	memset(vst,0,sizeof vst);
	for (int i = n-1;i >= 0;i --)
		if (!vst[order[i]])
			dfs2(order[i]), cnt ++;
	memset(lnk,0,sizeof lnk);
	for (int i = 1;i <= n;i ++)
		for (unsigned j = 0;j < g[i].size();j ++)
			lnk[id[i]][id[g[i][j]]] = 1;
	memset(inDu,0,sizeof inDu);
	memset(outDu,0,sizeof outDu);
	for (int i = 0;i < cnt;i ++)
		for (int j = 0;j < cnt;j ++)
			if (i != j && lnk[i][j])
				outDu[i] ++, inDu[j] ++;
	int cc = 0;
	for (int i = 0;i < cnt;i ++)
		if (outDu[i] == 0 || inDu[i] == 0)
			start[i] = 1, cc ++;
		else start[i] = 0;
	if (cc > k) printf("0\n");
	else
	{
		memset(pointNum,0,sizeof pointNum);
		for (int i = 1;i <= n;i ++) pointNum[id[i]] ++;
		memset(dp,0,sizeof dp);
		for (int i = start[0];i <= k;i ++)
			assign(dp[0][i],c[pointNum[0]][i]);
		for (int i = 1;i < cnt;i ++)
			for (int j = 0;j <= k;j ++)
				for (int d = start[i];d <= pointNum[i] && d <= j;d ++)
				{
					mult(tmp,dp[i-1][j-d],c[pointNum[i]][d]);
					add(dp[i][j],dp[i][j],tmp);
				}
		show(dp[cnt-1][k]);
	}
}

int main()
{
	c[1][0][0] = c[1][0][1] = 1;
	c[1][1][0] = c[1][1][1] = 1;
	for (int i = 2;i <= 100;i ++)
	{
		c[i][0][0] = c[i][0][1] = 1;	
		for (int j = 1;j <= i;j ++)
			add(c[i][j],c[i-1][j-1],c[i-1][j]);
	}
	while (scanf("%d%d%d",&n,&m,&k) != EOF)
	{
		for (int i = 1;i <= n;i ++)
			g[i].clear(), gt[i].clear();
		for (int i = 0;i < m;i ++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			g[u].push_back(v);
			gt[v].push_back(u);
		}
		solve();
		printf("\n");
	}
	return 0;
}
