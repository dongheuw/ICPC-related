#include <cstdio>
#include <cstring>
#include <algorithm>

long long n;

int main()
{
	while (scanf("%lld",&n) != EOF)
	{
		if (n == 4) puts("0 2");
		else if (n == 5) puts("0 0");
		else if (n == 6) puts("6 9");
		else if (n & 1) printf("%lld 0\n",n*(n-3)/2);
		else printf("%lld %lld\n",n*(n-3)/2,n*(n-3)/2);
	}
	return 0;
}
