#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 105;
int n,m;

map<int,int> f,g;

struct Node
{
	int t,v;
}a[maxn];

int main()
{
	freopen("j.in","r",stdin);
	freopen("j.out","w",stdout);
	while (~scanf("%d%d",&n,&m))
	{
		fo(i,1,n) scanf("%d%d",&a[i].t,&a[i].v);
		f.clear();
		f[0] = 0;
		fo(i,1,n)
		{
			g.clear();
			for (map<int,int>::iterator it = f.begin();it != f.end();it ++)
			{
				int t = it->first, v = it->second;
				if (t + a[i].t <= m)
				{
					if (g.count(t+a[i].t))
					{
						if (g[t+a[i].t] < v+a[i].v)
							g[t+a[i].t] = v + a[i].v;
					} else g[t+a[i].t] = v + a[i].v;
				}
			}
			for (map<int,int>::iterator it = g.begin();it != g.end();it ++)
			{
				int t = it->first, v = it->second;
				if (f.count(t))
				{
					if (v > f[t]) f[t] = v;
				} else f[t] = v;
			}
			for (map<int,int>::iterator it = f.begin();it != f.end();it ++)
			{
				for (map<int,int>::iterator jt = f.begin();jt != it && jt != f.end();jt ++)
					if ()
			}
		}
		int ans = 0;
		for (map<int,int>::iterator it = f.begin();it != f.end();it ++)
			if (it->second > ans) ans = it->second;
		printf("%d\n",ans);
	}
	return 0;
}
