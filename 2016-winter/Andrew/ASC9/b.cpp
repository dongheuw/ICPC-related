#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 1100;

int n,m,p[maxn],q[maxn],e[maxn][maxn];
vector<int> ans,ep[maxn],eq[maxn];

void topsort(int n,vector<int> e[maxn],int v[maxn])
{
	static int c[maxn];
	int m = 0;
	memset(c,0,(n+1)*4);
	fo(i,0,n-1)
		for (vector<int>::iterator j = e[i].begin();j != e[i].end();j ++)
			c[*j] ++;
	fo(i,0,n-1) if (c[i] == 0) v[m++] = i;
	fo(i,0,m-1)
		for (vector<int>::iterator j = e[v[i]].begin();j != e[v[i]].end();j ++)
			if (--c[*j] == 0) v[m++] = *j;
}

int main()
{
	while (scanf("%d%d",&n,&m) != EOF)
	{
		fo(i,0,n-1)
		{
			ep[i].clear();
			eq[i].clear();
			fo(j,0,n-1) e[i][j] = -1;
		}
		fo(i,0,m-1)
		{
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			ep[--a].push_back(--b);
			if (c == 0) eq[a].push_back(b);
			else eq[b].push_back(a);
			e[a][b] = e[a][b] == -1 ? i : -2;
		}
		topsort(n,ep,p);
		topsort(n,eq,q);
		ans.clear();
		bool ok = 1;
		fo(i,0,n-1)
		{
			for (int j = find(p,p+n,q[i])-p;j > i;j --)
			{
				if (e[p[j-1]][p[j]] == -2) ok = 0;
				if (!ok) break;
				if (e[p[j-1]][p[j]] != -1)
				{
					ans.push_back(e[p[j-1]][p[j]]);
					swap(e[p[j-1]][p[j]],e[p[j]][p[j-1]]);
				}
				swap(p[j-1],p[j]);
			}
			if (!ok) break;
		}
		if (ok)
		{
			printf("%d\n",(int)ans.size());
			for (unsigned i = 0;i < ans.size();i ++)
			{
				if (i > 0) putchar(' ');
				printf("%d",ans[i]+1);
			}
			puts("");
		}
		else puts("-1");
		puts("");
	}
	return 0;
}
