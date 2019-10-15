#include <cstdio>
#include <cstring>
#include <algorithm>

long long m,n,l,f[100];

int main()
{
	f[1] = 1;
	for (int i = 2;i <= 60;i ++) f[i] = f[i-1] + f[i-2];
	while (scanf("%lld%lld",&m,&n) != EOF)
	{
		l = 1;
		for (int i = 3;f[i] <= m || f[i] <= n;i ++)
			if (m % f[i] == 0 || n % f[i] == 0) l = f[i];
		printf("%lld\n\n",m*n-m*n/l);
	}
	return 0;
}
