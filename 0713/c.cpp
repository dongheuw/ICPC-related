#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

typedef long long LL;

const int maxn = 505;
const int mod = 1000000009;

pair<int,int> a[maxn*2];
int N,K;
LL f[2][maxn][maxn],ans;

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	scanf("%d%d",&N,&K);
	fo(i,1,N) scanf("%d",&a[i].first), a[i].second = 0;
	fo(i,N+1,2*N) scanf("%d",&a[i].first), a[i].second = 1;
	sort(a+1,a+1+2*N);
	if ((N+K) % 2 == 0)
	{
		f[0][0][0] = 1;
		int cnt1 = 0, cnt2 = 0;
		fo(i,1,2*N)
		{
			int cur = (i-1) % 2;
			fo(x,0,N)
				fo(y,0,N)
				{
					if (!f[cur][x][y]) continue;
					f[cur^1][x][y] = (f[cur^1][x][y] + f[cur][x][y]) % mod;
					if (!a[i].second)
						f[cur^1][x+1][y] = (f[cur^1][x+1][y] + f[cur][x][y] * (cnt2-x-y) % mod) % mod;
					else f[cur^1][x][y+1] = (f[cur^1][x][y+1] + f[cur][x][y] * (cnt1-x-y) % mod) % mod;
				}
			if (!a[i].second) cnt1 ++; else cnt2 ++;
			memset(f[cur],0,sizeof f[cur]);
		}
		ans = f[0][(N+K)/2][(N-K)/2];
	} else ans = 0;
	printf("%lld\n",ans);
	return 0;
}
