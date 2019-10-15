#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int T;
long long N,S1,V1,S2,V2;

int main()
{
	scanf("%d",&T);
	for (int cs = 1;cs <= T;cs ++)
	{
		scanf("%lld%lld%lld%lld%lld",&N,&S1,&V1,&S2,&V2);
		if (1.0*V1/S1 < 1.0*V2/S2) swap(S1,S2), swap(V1,V2);
		long long ans = N / S1 * V1 + N % S1 / S2 * V2;
		for (long long i = N/S1-1;i >= max(0ll,N/S1-50);i --)
			ans = max(ans,i*V1+(N-i*S1)/S2*V2);
		printf("Case #%d: %lld\n",cs,ans);
	}
}
