#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n,a[50005],b[50005];

int main()
{
	while (scanf("%d",&n) != EOF)
	{
		for (int i = 1;i<=n;i++) scanf("%d",&a[i]), b[i] = a[i] - i;
		sort(b+1,b+n+1);
		int cnt = 1, inc = 0, t = b[1];
		for (int i = 1;i < n;i ++)
		{
			if (b[i] == b[i+1]) cnt ++; else cnt = 1;
			if (inc < cnt) inc = cnt, t = b[i];
		}
		if (b[n] == b[n-1])
		{
			inc = inc > cnt ? inc : cnt;
			t = b[n];
		}
		if (n == 1) printf("0\n");
		else printf("%d\n",n-inc);
		for (int i = 1;i <= n;i ++) a[i] = i + t;
		for (int i = 1;i < n;i ++) printf("%d ",a[i]);
		printf("%d\n",a[n]);
	}
}
