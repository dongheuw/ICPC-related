#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 200005;
int T,N,M,tot,top,top2,nsk;
int head[maxn],nex[maxn],point[maxn],low[maxn],dfn[maxn],stack[maxn];
int father[maxn],stack2[maxn],ind[maxn];
bool instack[maxn],visit[maxn],bz[maxn];

void Insert(int x,int y)
{
	tot ++;
	point[tot] = y;
	nex[tot] = head[x];
	head[x] = tot;
}

void fore(int x)
{
	for (stack2[top2=1]=x;father[stack2[top2]]!=stack2[top2];)
	{
		top2++; 
		stack2[top2] = father[stack2[top2-1]];
	}
	fo(i,1,top2) father[stack2[i]]=stack2[top2];
}

void merge(int x,int y)
{
	fore(x); fore(y);
	int xx = father[x];
	int yy = father[y];
	father[xx] = yy; 
}

void Tarjan(int x)
{
	stack[++top] = x; 
	instack[x] = 1; 
	visit[x] = 1; 
	low[x] = ++nsk; 
	dfn[x] = nsk;
	for (int i = head[x];i;i = nex[i])
		if (!visit[point[i]])
		{
			Tarjan(point[i]);
			dfn[x] = min(dfn[x],dfn[point[i]]);
		} else 
		if (instack[point[i]]) 
			dfn[x] = min(dfn[x],low[point[i]]);
	if (low[x] == dfn[x])
	{
		while (stack[top] != x) 
		{ 
			merge(stack[top],x); 
			instack[stack[top]] = 0; 
			top --; 
		}
		top --; 
		instack[x] = 0;
	}
}

int main()
{
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	scanf("%d",&T);
	while (T --)
	{
		scanf("%d%d",&N,&M);
		tot = 0;
		fo(i,1,N) head[i] = 0, instack[i] = 0, visit[i] = 0, low[i] = dfn[i] = 0;
		fo(i,1,M)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			x ++, y ++;
			Insert(x,y);
		}
		nsk = top = top2 = 0;
		fo(i,1,N) father[i] = i;
		fo(i,1,N) if (!visit[i]) Tarjan(i);
		fo(i,1,N) ind[i] = 0, bz[i] = 0; 
		fo(i,1,N)
		{
			bz[father[i]] = 1;
			for (int j = head[i];j;j = nex[j])
				if (father[i] != father[point[j]]) ind[father[point[j]]] ++;
		}
		int cnt = 0, x = 0;
		fo(i,1,N) if (bz[i] == 1 && ind[i] == 0) cnt ++, x = i;
		if (cnt > 1) printf("Confused\n"); else
		{
			fo(i,1,N) if (father[i] == x) printf("%d\n",i-1);
		}
		printf("\n");
	}
	return 0;
}
