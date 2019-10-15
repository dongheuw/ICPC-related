#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

const int maxn = 2005;
int n,a[maxn],b[maxn];

int query()
{
	fo(i,1,n) putchar('0'+a[i]);
	printf("\n");
	fflush(stdout);
	int ret;
	scanf("%d",&ret);
	if (ret == n) exit(0);
	return ret;
}

int main()
{
	srand(time(0));
	scanf("%d",&n);
	while (1)
	{
		fo(i,1,n) a[i] = rand() % 2;
		int ret = query();
		if (ret == n/2) break;
	}
	b[1] = 0;
	fo(i,2,n)
	{
		a[1] ^= 1;
		a[i] ^= 1;
		int ret = query();
		if (ret == n/2) b[i] = 1; else b[i] = 0;
		a[1] ^= 1;
		a[i] ^= 1;
	}
	fo(i,1,n) a[i] ^= b[i];
	query();
	fo(i,1,n) a[i] ^= 1;
	query();
	return 0;
}
