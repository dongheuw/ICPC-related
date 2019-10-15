#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 123456 + 5;

int n,m,tot,a[maxn],b[maxn*2],c[maxn*2],d[maxn];
bool mark[maxn],flag[maxn];

void Insert(int x,int y)
{
	tot ++;
	b[tot] = y;
	c[tot] = a[x];
	a[x] = tot;
}

void Add(int x,int y)
{
	Insert(x,y);
	Insert(y,x);
}

void dfs(int x,int p)
{
	if (p != -1) d[x] = d[p] + 1;
	if (mark[x]) flag[x] = 1;
	for (int i = a[x];i;i = c[i])
	{
		int y = b[i];
		if (y == p) continue;
		dfs(y,x);
		flag[x] |= flag[y];
	}
}

void Work()
{
	int maxd = 0,v1,v2;
	fo(i,1,n)
		if (mark[i])
		{
			v1 = i;
			dfs(i,-1);
			break;
		}
	int esum = 0;
	fo(i,1,n)
	{
		if (flag[i]) esum ++;
		if (mark[i] && d[i] > maxd) maxd = d[i], v1 = i;
	}
	esum = 2 * (esum-1);
	memset(d,0,sizeof d);
	dfs(v1,-1);
	maxd = 0; v2 = v1;
	fo(i,1,n)
		if (mark[i] && d[i] > maxd)
			maxd = d[i], v2 = i;
	printf("%d\n%d\n",min(v1,v2),esum-maxd);
}

void Initialize()
{
	scanf("%d%d",&n,&m);
	fo(i,1,n-1)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		Add(x,y);
	}
	fo(i,1,m)
	{
		int x;
		scanf("%d",&x);
		mark[x] = 1;
	}
}

int main()
{
	Initialize();
	Work();
}
