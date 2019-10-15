#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

typedef long long LL;

const int maxn = 505;

int n,m,lk[maxn],ans;
LL p[maxn],t[maxn][maxn];
pair<int,LL> a[maxn],b[maxn];
vector<int> e[maxn];
bool vis[maxn];

bool Augment(int x)
{
	vis[x] = 1;
	for (unsigned i = 0;i < e[x].size();i ++)
	{
		int y = e[x][i];
		if (lk[y] == -1 || (!vis[lk[y]] && Augment(lk[y])))
		{
			lk[y] = x;
			return 1;
		}
	}
	return 0;
}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d",&n,&m);
	fo(i,1,n) scanf("%lld",&p[i]);
	fo(i,1,n)
		fo(j,1,n)
		{
			scanf("%lld",&t[i][j]);
			if (i != j) t[i][j] += p[j];
		}
	fo(i,1,m)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		a[i] = make_pair(x,z);
		b[i] = make_pair(y,t[x][y]+z);
	}
	fo(k,1,n)
		fo(i,1,n)
			fo(j,1,n)
				if (t[i][j] > t[i][k] + t[k][j])
					t[i][j] = t[i][k] + t[k][j];
	fo(i,1,m)
	{
		e[i].clear();
		fo(j,1,m)
		{
			if (i != j && b[i].second+t[b[i].first][a[j].first] <= a[j].second)
				e[i].push_back(j);
		}
	}
	memset(lk,-1,sizeof lk);
	fo(i,1,m)
	{
		memset(vis,0,sizeof vis);
		if (Augment(i)) ans ++;
	}
	printf("%d\n",m-ans);
	return 0;
}
