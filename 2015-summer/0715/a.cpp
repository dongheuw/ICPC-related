#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

int T,n,x,y;
long long a,b;

int main()
{
	scanf("%d",&T);
	fo(cs,1,T)
	{
		scanf("%d",&n);
		a = b = 0;
		fo(i,0,n-1)
		{
			scanf("%d%d",&x,&y);
			while (x > 1 && y > 1)
			{
				x >>= 1;
				y >>= 1;
			}
			if (x == 1) b += y-1;
			if (y == 1) a += x-1;
			
		}
		printf("Case %d: ",cs);
		printf(a > b ? "Alice\n" : "Bob\n");
	}
	return 0;
}
