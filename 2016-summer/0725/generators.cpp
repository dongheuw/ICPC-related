#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 20005;

bool flag[maxn];
int n,k,opt[maxn],opt2[maxn];

int main()
{
	freopen("generators.in","r",stdin);
	freopen("generators.out","w",stdout);
	scanf("%d%d",&n,&k);
	int ans = 0;
	int cps = (int)1e9, pos = -1;
	fo(i,0,n-1)
	{
		int x,a,b,c;
		scanf("%d%d%d%d",&x,&a,&b,&c);
		fo(j,0,c) flag[j] = false;
		vector <int> V;
		while (!flag[x])
		{
			V.push_back(x);
			flag[x] = 1;
			x = (x * a + b) % c;
		}
		int m = -1, mp = -1;
		for (unsigned i = 0;i < V.size();i ++)
			if (V[i] > m)
			{
				m = V[i];
				mp = i;
			}
		int m2 = -1, mp2 = -1;
		for (unsigned i = 0;i < V.size();i ++)
			if (V[i] % k != m % k && V[i] > m2)
			{
				m2 = V[i];
				mp2 = i;
			}
		opt[i] = mp;
		opt2[i] = mp2;
		ans += m;
		if (mp2 != -1 && m - m2 < cps)
		{
			cps = m - m2;
			pos = i;
		}
	}
	if (ans % k == 0 && cps == (int)1e9)
	{
		printf("%d\n",-1);
		return 0;
	}
	if (ans % k == 0)
	{
		ans -= cps;
		opt[pos] = opt2[pos];
	}
	printf("%d\n",ans);
	fo(i,0,n-1) printf("%d%c",opt[i],i==n-1?'\n':' ');
	return 0;
}
