#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 100005;

int n,a[maxn],b[maxn];

int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	while (~scanf("%d",&n))
	{
		fo(i,0,n-1) scanf("%d",&a[i]);
		long long ans = 0;
		for (int i = 10;i <= (int)1e9;i *= 10)
		{
			fo(j,0,n-1) b[j] = a[j] % i;
			sort(b,b+n);
			fo(j,0,n-1)
			{
				int t = i - b[j];
				if (b[n-1] >= t)
				{
					int pos = lower_bound(b,b+n,t)-b;
					if (pos > j) ans += n-pos;
					else ans += n-(j+1);
				}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
