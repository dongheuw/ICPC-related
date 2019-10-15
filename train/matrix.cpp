#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn = 10005;
int N,M,a[maxn];

int main()
{
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
	scanf("%d%d",&N,&M);
	for (int i = 1;i <= M;i ++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		a[x] ++, a[y] ++;
	}
	long long ans = 0;
	for (int i = 1;i <= N;i ++) ans += (long long)a[i] * a[i];
	printf("%lld\n",ans);
	return 0;
}
