#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 100005; // 100005
int T,N,A[maxn],tot,a[maxn],b[maxn],c[maxn];
int maxv,rt,idx[maxn],idx_inv[maxn],tree[maxn*2];
bool father[maxn];

long long K,ans;

void Add(int u,int v)
{
	tot ++;
	b[tot] = v;
	c[tot] = a[u];
	a[u] = tot;
}

int Query(int x)
{
	int ret = 0;
	for (;x;x -= x&(-x)) ret += tree[x];
	return ret;
}

void Modify(int x,int v)
{
	for (;x <= maxv;x += x&(-x)) tree[x] += v;
}

long long chart[maxn*2];
void Discretize()
{
	chart[0] = 0;
	fo(i,1,N) chart[++chart[0]] = A[i];
	fo(i,1,N)
		if (A[i]) chart[++chart[0]] = K / A[i];
		else chart[++chart[0]] = (int)2e9;
	sort(chart+1,chart+1+chart[0]);
	chart[0] = unique(chart+1,chart+1+chart[0]) - chart - 1;
	fo(i,1,N)
	{
		if (A[i]) idx_inv[i] = lower_bound(chart+1,chart+1+chart[0],K/A[i]) - chart;
		else idx_inv[i] = chart[0];
		idx[i] = lower_bound(chart+1,chart+1+chart[0],A[i]) - chart;
	}
	maxv = chart[0];
}

void dfs(int x)
{
	ans += Query(idx_inv[x]);
	Modify(idx[x],1);
	for (int i = a[x];i;i = c[i]) dfs(b[i]);
	Modify(idx[x],-1);
}

int main()
{
	freopen("j.in","r",stdin);
	freopen("j.out","w",stdout);
	for (scanf("%d",&T);T;T --)
	{
		scanf("%d%lld",&N,&K);
		tot = 0;
		fo(i,1,N)
		{
			father[i] = 0;
			a[i] = 0;
		}
		fo(i,1,N) scanf("%d",&A[i]);
		fo(i,1,N-1)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			Add(u,v);
			father[v] = 1;
		}
		Discretize();
		fo(i,1,N)
			if (!father[i])
			{
				rt = i;
				break;
			}
		ans = 0;
		dfs(rt);
		printf("%lld\n",ans);
	}
	return 0;
}
