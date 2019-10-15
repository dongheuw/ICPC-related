#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 100005;
const int maxm = 1000005;

typedef long long ll;
const ll mod = (ll)1e9 + 7;

struct Edge
{
	int to,nxt;
}e[maxm];

int ecnt,hed[maxn];
ll w[maxn],ans[maxn],val[maxn],Sum;
int dfn[maxn],low[maxn],cnt,vis[maxn],vec[maxn];

template <class T>
void read(T &x)
{
	char ch; x = 0;
	do ch = getchar(); while (ch < '0' || ch > '9');
	do x = x * 10 + ch - 48, ch = getchar(); while (ch >= '0' && ch <= '9');
}

ll Pow(ll x,ll y)
{
	ll ret = 1;
	while (y)
	{
		if (y & 1) ret = ret * x % mod;
		y >>= 1;
		x = x * x % mod;
	}
	return ret;
}

void Add(ll &x,ll y)
{
	x += y;
	if (x >= mod) x -= mod;
}

void Addedge(int u,int v)
{
	e[ecnt].to = v;
	e[ecnt].nxt = hed[u];
	hed[u] = ecnt ++;
}

void dfs(int u)
{
	vis[u] = 1; val[u] = w[u];
	for (int i = hed[u];~i;i = e[i].nxt)
	{
		int v = e[i].to;
		if (vis[v]) continue;
		dfs(v);
		val[u] = val[u] * val[v] % mod;
	}
}

ll Tarjan(int fa,int u,int root)
{
	ll ret = w[u], sum = 0, pro = w[u];
	dfn[u] = low[u] = ++cnt;
	int chd = 0;
	bool flag = 0;
	for (int i = hed[u];~i;i = e[i].nxt)
	{
		int v = e[i].to;
		if (!dfn[v])
		{
			chd ++;
			ll tmp = Tarjan(u,v,root);
			low[u] = min(low[u],low[v]);  
			if (!fa) Add(sum,tmp);
			if (!fa && chd > 1) flag = 1;
			if (fa && low[v] >= dfn[u])
			{
				Add(sum,tmp);
				pro = pro * tmp % mod;
				flag = 1;
			}
			ret = ret * tmp % mod;
		}
		else if (v != fa) low[u] = min(low[u],dfn[v]);
	}
	if (!flag) //isolated
	{
		if (!fa && hed[u] == -1) ans[u] = (Sum - val[root] + mod) % mod;
		else ans[u] = ((Sum - val[root] + mod) % mod + val[root] * Pow(w[u],mod-2) % mod) % mod;
	}
	else
	{
		ll pre = val[root] * Pow(pro,mod-2) % mod;
		if (fa) Add(sum,pre);
		ans[u] = (Sum - val[root] + mod) % mod;
		Add(ans[u],sum);
	}
	return ret;
}

int main()
{
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);
	int t,n,m;
	for (scanf("%d",&t);t;t --)
	{
		read(n), read(m);
		Sum = cnt = ecnt = 0;
		memset(vis,0,4*(n+1));
		memset(dfn,0,4*(n+1));
		memset(hed,255,4*(n+1));
		fo(i,1,n) read(w[i]);
		fo(i,1,m)
		{
			int u,v;
			read(u), read(v);
			Addedge(u,v), Addedge(v,u);
		}
		int tot = 0;
		fo(i,1,n)
		{
			if (vis[i]) continue;
			vec[++tot] = i;
			dfs(i), Add(Sum,val[i]);
		}
		fo(i,1,tot) Tarjan(0,vec[i],vec[i]);
		ll Ans = 0;
		fo(i,1,n) Add(Ans,ans[i]*i%mod);
		printf("%lld\n",Ans);
	}
	return 0;
}
