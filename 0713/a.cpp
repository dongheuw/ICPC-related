#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

typedef long long LL;

const int maxn = 200005;

int N;
LL a[maxn],mi = (int)1e18;

int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	scanf("%d",&N);
	fo(i,1,N) scanf("%lld",&a[i]), mi = min(a[i],mi);
	fo(x,1,mi)
	{
		LL sg = 0;
		fo(i,1,N) sg ^= (a[i]-x);
		if (!sg)
		{
			printf("%d\n",x-1);
			break;
		}
	}
	return 0;
}
