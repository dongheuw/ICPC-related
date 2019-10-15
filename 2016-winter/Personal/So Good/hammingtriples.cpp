#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;
typedef long long LL;

const int maxn = 200005;
int N,M;
LL a[maxn],ans;

int main()
{
	scanf("%d%d",&N,&M);
	fo(i,1,M)
	{
		int s,f; scanf("%d%d",&s,&f);
		a[i] = (s+1)*N - f;
	}
	sort(a+1,a+1+M);
	fo(i,M+1,2*M) a[i] = a[i-M]+2*N;
	ans = (long long)M*(M-1)*(M-2)/6;
	fo(i,1,M)
	{
		int p = lower_bound(a+i,a+1+2*M,a[i]+N)-a-i-1;
		if (p >= 2) ans -= (LL)p*(p-1)/2;
	}
	if (!ans)
	{
		LL p1 = 0, p2 = 0;
		for (int i = 1;i <= M && a[i] == a[1];i ++,p1 ++);
		for (int i = M;i >= 1 && a[i] == a[M];i --,p2 ++);
		ans += p1 * p2 * ((LL)M-p1-p2);
	}
	printf("%lld\n",ans);
	return 0;
}
