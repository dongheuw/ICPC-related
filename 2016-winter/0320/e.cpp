#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 100005;

int n,a[maxn],ans = -1;

int main()
{
	scanf("%d",&n);
	for (int i = 1;i <= n;i ++) scanf("%d",&a[i]);
	std::sort(a+1,a+1+n);
	for (int i = 1;i <= n/2;i ++)
		if (ans == -1 || a[i]+a[n-i+1] < ans) ans = a[i] + a[n-i+1];
	printf("%d\n",ans);
}
