#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 1005;

int T,cas,M,a[maxn];

int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	scanf("%d",&T);
	while (T --)
	{
		scanf("%d%d",&cas,&M);
		int sum = 0;
		fo(i,1,M) scanf("%d",&a[i]), sum += a[i];
		int cur = 0;
		fo(i,1,M)
		{
			cur += a[i];
			if (sum % cur != 0) continue;
			bool ok = 1;
			for (int j = i+1,t = 0;j <= M;j ++)
			{
				t += a[j];
				if (t > cur)
				{
					ok = 0;
					break;
				}
				if (t == cur) t = 0;
			}
			if (ok)
			{
				printf("%d %d\n",cas,cur);
				break;
			}
		}
	}
	return 0;
}
