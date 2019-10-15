#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 55;
const int maxf = 1005;
int T,N,cas,floor,f[maxn][maxf];

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	fo(i,0,1000) f[1][i] = i;
	fo(i,2,50)
		fo(j,1,1000)
		{
			if (i <= j) f[i][j] = f[i-1][j-1] + f[i][j-1] + 1;
			else f[i][j] = f[j][j];
			if (f[i][j] > 1005) f[i][j] = 1005;
		}
	for (scanf("%d",&T);T;T --)
	{
		scanf("%d%d%d",&cas,&N,&floor);
		printf("%d %d\n",cas,lower_bound(f[N],f[N]+1000,floor)-f[N]);
	}
}
