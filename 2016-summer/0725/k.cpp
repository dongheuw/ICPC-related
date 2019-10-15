#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;
 
const int maxn = 100025;

int n,m,a[maxn],b[maxn];
bool flag[maxn];
vector<int> Ou[maxn],In[maxn];
 
void dfs(int v,int cnt)
{
	if (cnt == n)
	{
		for (int i = 0;i < n;i ++) printf("%d ",a[i]+1);
		printf("1\n");
		exit(0);
	}
	if (0 < cnt && cnt < n && v == 0) return;
	for (unsigned j = 0;j < Ou[v].size();j ++)
		if (!flag[Ou[v][j]])
		{
			flag[Ou[v][j]] = 1;
			a[cnt+1] = Ou[v][j];
			dfs(Ou[v][j],cnt+1);
			flag[Ou[v][j]] = 0;
		}
}
 
int main()
{
	freopen("king.in","r",stdin);
	freopen("king.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i = 0;i < n;i ++) Ou[i].clear(), In[i].clear();
	for (int i = 0;i < m;i ++)
	{
		scanf("%d%d",&a[i],&b[i]);
		a[i]--, b[i]--;
		Ou[a[i]].push_back(b[i]);
		In[b[i]].push_back(a[i]);
	}
	for (int i = 0;i < n;i ++)
		if (Ou[i].size() == 1)
		{
			int u = Ou[i][0];
			for (unsigned j = 0;j < In[u].size();j ++)
			{
				int v = In[u][j];
				if (v != i) Ou[v].erase(find(Ou[v].begin(),Ou[v].end(),u));
			}
			In[u].resize(1);
			In[u][0] = i;
		}
	for (int i = 0;i < n;i ++)
		if (Ou[i].empty() || In[i].empty())
		{
			puts("There is no route, Karl!");
			return 0;
		}
	for (int i = 0;i < n;i ++) flag[i] = 0;
	a[0] = 0;
	dfs(0,0);
	puts("There is no route, Karl!");
	return 0;
}
