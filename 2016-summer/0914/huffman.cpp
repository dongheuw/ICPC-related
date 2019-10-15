#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 105;
int n,cntu[maxn],cntv[maxn];
multimap< pair<int,int>,int > R;
char ans[maxn][maxn*2],a[maxn*2];

bool dfs(int u,int v,int cur)
{
	if (!cntu[u] || !cntv[v]) return 0;
	map< pair<int,int>,int >::iterator it = R.find(make_pair(u,v));
	if (it != R.end())
	{
		fo(i,1,cur-1) ans[it->second][i] = a[i];
		ans[it->second][cur] = 0;
		R.erase(it);
		cntu[u] --, cntv[v] --;
		return 1;
	}
	a[cur] = '0';
	if (!dfs(u+1,v,cur+1)) return 0;
	a[cur] = '1';
	if (!dfs(u,v+1,cur+1)) return 1;
	return 1;
}

int main()
{
	freopen("huffman.in","r",stdin);
	freopen("huffman.out","w",stdout);
	while (~scanf("%d",&n))
	{
		if (!n) break;
		memset(cntu,0,sizeof cntu);
		memset(cntv,0,sizeof cntv);
		R.clear();
		fo(i,1,n)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			cntu[u] ++, cntv[v] ++;
			R.insert(make_pair(make_pair(u,v),i));
		}
		if (dfs(0,0,1) && R.empty())
		{
			puts("Yes");
			fo(i,1,n)
			{
				for (int j = 1;ans[i][j] != 0;j ++) printf("%c",ans[i][j]);
				printf("\n");
			}
		} else puts("No");
	}
	return 0;
}
