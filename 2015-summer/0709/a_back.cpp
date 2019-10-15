#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;
typedef long long LL;

const int maxn = 100005;

LL N,K,ans;
int T,tot;
int fac[maxn][2];

void Findfactor()
{
	LL temp = K;
	tot = 0;
	for (int i = 2;i <= (int)sqrt(K);i ++)
	{
		if (temp % i == 0)
		{
			tot ++;
			fac[tot][0] = i, fac[tot][1] = 0;
			while (temp % i == 0) temp /= i, fac[tot][1] ++;
		}
	}
	if (temp != 1)
	{
		tot ++;
		fac[tot][0] = temp, fac[tot][1] = 1;
	}
}

int main()
{

	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d",&T);
	while (T --)
	{
		scanf("%lld%lld",&N,&K);
		Findfactor();
		ans = (LL)1e18;
		fo(i,1,tot)
		{
			LL cnt = 0;
			for (LL p = fac[i][0];p <= N;p *= fac[i][0]) cnt += N / p;
			if (cnt / fac[i][1] < ans) ans = cnt / fac[i][1];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
