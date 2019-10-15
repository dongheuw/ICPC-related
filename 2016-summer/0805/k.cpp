#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define g(i,x) max(f[i][x][0],f[i][x][1])

using namespace std;

const int maxn = 100005;
int T,n,a[maxn][2],f[maxn][2][2];

int main()
{
	freopen("k.in","r",stdin);
	freopen("k.out","w",stdout);
	for (scanf("%d",&T);T;T --)
	{
		scanf("%d",&n);
		fo(i,1,n) scanf("%d",&a[i][0]);
		fo(i,1,n) scanf("%d",&a[i][1]);
		int ans = 0;
		fo(i,1,n)
		{
			fo(x,0,1)
			{
				f[i][x][0] = max(g(i-1,x),g(i-1,x^1));
				f[i][x][1] = max(f[i-1][x][0],g(i-1,x^1)) + a[i][x];
				if (g(i,x) > ans) ans = g(i,x);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
