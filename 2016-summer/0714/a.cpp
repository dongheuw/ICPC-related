#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int mod0 = 137;
const int mod1 = 491;
const int maxn = 1005;

char M[maxn][maxn],a[maxn][maxn];

typedef unsigned long long ull;
ull H[maxn],H0[maxn],H1[maxn],nM[maxn][maxn];
map<ull,int> s;

int n,m,t,q,p,cs,ans;

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	H1[0] = H0[0] = 1;
	fo(i,1,1000)
	{
		H0[i] = H0[i-1] * mod0;
		H1[i] = H1[i-1] * mod1;
	}
	scanf("%d%d%d%d%d",&n,&m,&t,&p,&q);
	while (n+m+t+p+q > 0)
	{
		ans = 0, s.clear();
		fo(i,0,n-1) scanf("%s",M[i]);
		while (t--)
		{
			fo(i,0,p-1) scanf("%s",a[i]);
			ull tM;
			fo(i,0,p-1)
			{
				tM = 0;
				for (int j = q-1;j >= 0;j --) tM = tM * mod0 + a[i][j];
				H[i] = tM;
			}
			tM = 0;
			for (int i = p-1;i >= 0;i --) tM = tM * mod1 + H[i];
			s[tM] ++;
		}
		fo(i,0,n-1)
		{
			H[m] = 0;
			for (int j = m-1;j >= 0;j --) H[j] = H[j+1] * mod0 + M[i][j];
			for (int j = 0;j + q <= m;j ++) nM[i][j] = H[j] - H[j+q] * H0[q];
		}
		for (int j = 0;j + q <= m;j ++)
		{
			H[n] = 0;
			for (int i = n-1;i >= 0;i --) H[i] = H[i+1] * mod1 + nM[i][j];
			for (int i = 0;i+p <= n;i ++)
			{
				map<ull,int>::iterator it = s.find(H[i]-H[i+p]*H1[p]);
				if (it != s.end())
				{
					ans += it->second;
					s.erase(it);
				}
			}
		}
		printf("Case %d: %d\n",++cs,ans);
		scanf("%d%d%d%d%d",&n,&m,&t,&p,&q);
	}
	return 0;
}
