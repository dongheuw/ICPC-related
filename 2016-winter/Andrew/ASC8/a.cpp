#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

int n;

int main()
{
	while (scanf("%d", &n) != EOF)
	{
		fo(i,1,n-1)
			fo(j,1,n)
			{
				printf("%d", j > i ? 1 : 0);
				putchar(j == n ? '\n' : ' ');
			}
		fo(j,1,n-1) printf("%d ", 0);
		printf("100\n");
	}
	return 0;
}
