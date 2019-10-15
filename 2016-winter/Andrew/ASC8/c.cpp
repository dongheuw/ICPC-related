#include <cstdio>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 3005;
int cas,n,a[maxn];
short f[maxn][maxn];
unordered_map<int,short> M;

int main()
{
	while (scanf("%d", &n) != EOF)
	{
		if (cas) puts(""); cas ++;
		fo(i,0,n-1)
		{
			scanf("%d",&a[i]);
			fo(j,i+1,n-1) f[i][j] = 1;
		}
		short ans = 0;
		pair<int,int> p;
		p.first = a[0];
		M.clear();
		for (int i = n-1;i >= 0;i --)
		{
			for (int j = i-1;j >= 0;j --)
			{
				unordered_map<int,short>::iterator it = M.find(a[j]+a[i]);
				if (it != M.end()) f[j][i] = f[i][it->second] + 1;
				if (f[j][i] > ans)
				{
					ans = f[j][i];
					p = make_pair(a[j],a[i]);
				}
			}
			M[a[i]] = i;
		}
		printf("%d\n%d",ans+1,p.first);
		fo(i,1,ans)
		{
			printf(" %d", p.second);
			p = make_pair(p.second, p.first+p.second);
		}
		puts("");
	}
	return 0;
}
