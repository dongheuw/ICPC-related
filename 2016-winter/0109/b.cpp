#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = (int)2e5 + 10;

int n,a[maxn];
map<int,int> b;
long long ans;

int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	scanf("%d",&n);
	fo(i,0,n-1)
	{
		scanf("%d",&a[i]);
		b[a[i]] = i;
	}
	fo(i,1,n-1)
		if (b[i+1]-b[i] > 0) ans += b[i+1] - b[i];
		else ans += b[i] - b[i+1];
	printf("%lld\n",ans);
	return 0;
}
