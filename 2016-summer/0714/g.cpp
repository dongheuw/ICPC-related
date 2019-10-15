#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

long long L;
int cs;

long long Mul(long long a,long long b)
{
	long long ret = 0;
	while (b)
	{
		if (b & 1) ret = (ret + a) % L;
		a = (a + a) % L;
		b >>= 1;
	}
	return ret;
}

bool Check(long long k)
{
	long long ret = 1, a = 10;
	while (k)
	{
		if (k & 1) ret = Mul(ret,a);
		a = Mul(a,a);
		k >>= 1;
	}
	return ret == 1;
}

int main()
{
	freopen("g.in","r",stdin);
	freopen("g.out","w",stdout);
	while (~scanf("%lld",&L))
	{
		if (L == 0) break;
		printf("Case %d: ",++cs);
		if (L % 16 == 0 || L % 5 == 0)
		{
			puts("0");
			continue;
		}
		L *= 9;
		while (L % 2 == 0) L /= 2;
		long long phi = L, tmp = L;
		for (long long i = 2;i*i <= L;i ++)
			if (tmp % i == 0)
			{
				phi = phi/i*(i-1);
				while (tmp % i == 0) tmp /= i;
			}
		if (tmp > 1) phi = phi/tmp*(tmp-1);
		long long ans = (long long)1e18;
		for (long long i = 1;i*i <= phi;i ++)
			if (phi % i == 0)
			{
				if (Check(i)) ans = min(ans,i);
				else if (Check(phi/i)) ans = min(ans,phi/i);
			}
		printf("%lld\n",ans);
	}
	return 0;
}
