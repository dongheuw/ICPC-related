#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;
typedef long long LL;

const int maxn = 100005;
int n,r,w,h,len;
LL f[maxn];
pair<LL,LL> a[maxn];

int main()
{
	scanf("%d%d%d%d",&n,&r,&w,&h);
	fo(i,1,n)
	{
		LL x,y;
		scanf("%lld%lld",&x,&y);
		a[i].first = r*x+y, a[i].second = -r*x+y;
	}
	sort(a+1,a+1+n);
	f[0] = -1e18;
	fo(i,1,n)
		if (a[i].second >= f[len]) f[++len] = a[i].second;
		else
		{
			int p = lower_bound(f+1,f+1+len,a[i].second) - f;
			f[p] = a[i].second;
		}
	printf("%d\n",len);
	return 0;
}
