#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

int n;

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	while (scanf("%d",&n) != EOF)
	{
		bool ok = 1;
		fo(i,1,n)
		{
			int x,r;
			scanf("%d",&x);
			r = (int)sqrt(x);
			if (r * r != x) ok = 0;
		}
		puts(ok?"Yes":"No");
	}
	return 0;
}
