#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 10005;
int T,N,cnt,cas;
int a[maxn],tree[maxn],ax[maxn],st[maxn];

inline int lowbit(int x) {return x & (-x);}

void Add(int x)
{
	for (int i = x;i <= N;i += lowbit(i)) tree[i] ++;
}

int Query(int x)
{
	int ret = 0;
	for (int i = x;i;i -= lowbit(i)) ret += tree[i];
	return ret;
}

int main()
{
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	scanf("%d",&T);
	while (T --)
	{
		st[0] = cnt = 0;
		memset(tree,0,sizeof tree);
		scanf("%d%d",&cas,&N);
		fo(i,1,N)
		{
			scanf("%d",&a[i]);
			ax[++cnt] = a[i];
		}
		sort(ax+1,ax+1+cnt);
		cnt = unique(ax+1,ax+1+cnt) - ax - 1;
		int low = 0x3f3f3f3f, high = -1;
		fo(i,1,N)
		{
			int v = lower_bound(ax+1,ax+1+cnt,a[i]) - ax;
			Add(v);
			low = min(low,v), high = max(high,v);
			if (i == 1)
			{
				st[++st[0]] = ax[v];
				continue;
			}
			if (i & 1)
			{
				int l = low, r = high, ret;
				while (l <= r)
				{
					int mid = (l + r) >> 1;
					int sum = Query(mid);
					if (sum <= i/2) l = mid + 1;
					else ret = mid, r = mid - 1;
				}
				st[++st[0]] = ax[ret];
			}
		}
		printf("%d %d\n",cas,st[0]);
		for (int i = 1, c = 0;i <= st[0];i ++)
		{
			printf("%d",st[i]);
			c ++;
			if (i < st[0] && c < 10) printf(" ");
			else if (i < st[0] && c == 10) c = 0, printf("\n");
			else printf("\n");
		}
	}
	return 0;
}
