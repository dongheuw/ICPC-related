#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 100100;
int n,m,a[maxn],b[maxn],c[maxn],d[maxn],father[maxn];
long long s;
vector<int> ans;

inline bool cmp(int lhs, int rhs) {return c[lhs] < c[rhs];}

int Get(int x)
{
	if (x == father[x]) return x;
	return father[x] = Get(father[x]);
}

int main()
{
	for (int t = 1;scanf("%d%d%lld",&n,&m,&s) != EOF;t ++)
	{
		if (t > 1) puts("");
		fo(i,1,m)
		{
			scanf("%d%d%d",&a[i],&b[i],&c[i]);
			d[i] = i;
		}
		sort(d+1,d+m+1,cmp);
		fo(i,1,n) father[i] = i;
		for (int i = m;i >= 1;i --)
		{
			int fx = Get(a[d[i]]), fy = Get(b[d[i]]);
			if (fx != fy) father[fy] = fx, d[i] = -1;
		}
		ans.clear();
		fo(i,1,m)
			if (d[i] != -1)
			{
				s -= c[d[i]];
				if (s >= 0) ans.push_back(d[i]);
				else break;
			}
		sort(ans.begin(),ans.end());
		printf("%lu\n",ans.size());
		for (unsigned i = 0;i < ans.size();i ++)
		{
			if (i > 0) putchar(' ');
			printf("%d",ans[i]);
		}
		puts("");
	}
	return 0;
}
