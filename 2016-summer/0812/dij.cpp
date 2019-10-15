#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cassert>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll mod=1000000007;
ll powmod(ll a,ll b) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
// head

const int N=101000;
vector<PII> e[N];
int dis[N];
int vis[N];
set<pair<int,int> > hs;
void dijkstra(int S,int n) {
	rep(i,0,n) dis[i]=1<<29,vis[i]=0;
	dis[S]=0;
	rep(i,0,n) hs.insert(mp(dis[i],i));
	rep(i,0,n) {
		int u=hs.begin()->se; hs.erase(hs.begin());
		vis[u]=1;
		rep(j,0,SZ(e[u])) {
			int v=e[u][j].fi;
			if (dis[v]>dis[u]+e[u][j].se) {
				hs.erase(mp(dis[v],v));
				dis[v]=dis[u]+e[u][j].se;
				hs.insert(mp(dis[v],v));
			}
		}
	}
}

int n,m,ty,u,v,w,bc,com,k,pos[20],g[20][20];
int dp[1<<16];
void dfs(int dep,int pre,int S,int cost) {
	dp[S]=min(dp[S],cost);
	if (dep==4) return;
	rep(i,0,k) dfs(dep+1,i,S|(1<<i),cost+g[pre][i]);
}
int main() {
	scanf("%d%d",&n,&m);
	rep(i,0,m) {
		scanf("%d%d%d%d",&ty,&u,&v,&w); --u; --v;
		if (ty==1) {
			e[u].pb(mp(v,w));
		} else {
			e[u].pb(mp(v,w));
			e[v].pb(mp(u,w));
		}
	}
	scanf("%d",&bc);
	scanf("%d",&com);
	scanf("%d",&k);
	rep(i,0,k) scanf("%d",&pos[i]);
	pos[k]=com;
	rep(i,0,k+1) --pos[i];
	rep(i,0,k+1) {
		dijkstra(pos[i],n);
		rep(j,0,k+1) g[i][j]=dis[pos[j]];
	}
	rep(i,0,(1<<k)) dp[i]=1<<29;
	dp[0]=0;
	dfs(0,k,0,bc);
	rep(S,1,(1<<k)) for (int nS=S;nS;nS=(nS-1)&S) dp[S]=min(dp[S],dp[nS]+dp[S-nS]);
	printf("%d\n",dp[(1<<k)-1]);
}
