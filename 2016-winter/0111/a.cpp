#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

int n;
double ans;

int main()
{
	while (~scanf("%d",&n))
	{
		if (n == 1) ans = 0;
		else ans = 1.0/(sin(acos(-1)*1.0/n));
		printf("%.8lf\n",ans+1.0);
	}
	return 0;
}
