#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 100005;

int N,M,tot,a[maxn],b[maxn*2],c[maxn*2];
int depth[maxn],father[maxn][18],up[maxn][18],down[maxn][18],far[maxn][3];

void Add(int x,int y)
{
	tot ++;
	b[tot] = y;
	c[tot] = a[x];
	a[x] = tot;
}

void Predfs(int x)
{
	for (int i = 0;i <= 17 && father[x][i];i ++) father[x][i+1] = father[father[x][i]][i];
	for (int i = a[x];i;i = c[i])
		if (b[i] != father[x][0])
		{
			depth[b[i]] = depth[x] + 1;
			father[b[i]][0] = x;
			Predfs(b[i]);
			if (far[b[i]][0]+1 >= far[x][0]) far[x][2] = far[x][1], far[x][1] = far[x][0], far[x][0] = far[b[i]][0] + 1;
			else if (far[b[i]][0]+1 >= far[x][1]) far[x][2] = far[x][1], far[x][1] = far[b[i]][0] + 1;
			else if (far[b[i]][0]+1 >= far[x][2]) far[x][2] = far[b[i]][0] + 1;
		}
}

void Predeal(int x)
{
	for (int i = 0;i <= 17 && father[x][i];i ++)
	{
		up[x][i+1] = max(up[x][i],up[father[x][i]][i]+(1<<i));
		down[x][i+1] = max(down[x][i]+(1<<i),down[father[x][i]][i]);
	}
	for (int i = a[x];i;i = c[i])
		if (b[i] != father[x][0])
		{
			if (far[x][0] == far[b[i]][0] + 1) down[b[i]][0] = far[x][1];
			else down[b[i]][0] = far[x][0];
			up[b[i]][0] = down[b[i]][0] + 1;
			Predeal(b[i]);
		}
}

void Initialize()
{
	scanf("%d",&N);
	fo(i,1,N-1)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		Add(x,y); Add(y,x);
	}
	depth[1] = 1; Predfs(1);
	Predeal(1);
}

int Get(int x,int d)
{
	for (int i = 17;i >= 0;i --)
		if (d >= (1<<i)) x = father[x][i], d -= (1<<i);
	return x;
}

int LCA(int x,int y)
{
	for (int j = 17;j >= 0;j --)
		if (depth[father[x][j]] >= depth[y]) x = father[x][j];
	if (x == y) return x;
	for (int j = 17;j >= 0;j --)
		if (father[x][j] != father[y][j])
			x = father[x][j], y = father[y][j];
	return father[x][0];
}

#define Dis(x,y) (depth[x]-depth[y])

int Calc1(int x,int y)
{
	int d = Dis(x,y),ret = 0,k = 0;
	for(int i = 17;i >= 0;i --)
		if (d >= (1<<i))
		{
			ret = max(ret,k+up[x][i]);
			k += (1<<i);
			d -= (1<<i);
			x = father[x][i];
		}
	return ret;
}

int Calc2(int x,int y)
{
	int d = Dis(x,y), ret = -1;
	for(int i = 17;i >= 0;i --)
		if (d >= (1<<i))
		{
			d -= (1<<i);
			ret = max(ret,d+down[x][i]);
			x = father[x][i];
		}
	return ret;
}

int Calc3(int u,int x,int y)
{
	int i = 0;
	int fx = far[Get(x,Dis(x,u)-1)][0]+1, fy = far[Get(y,Dis(y,u)-1)][0]+1;
	if (fx < fy) swap(fx,fy);
	if (fx == far[u][i]) i ++;
	if (fy == far[u][i]) i ++;
	return far[u][i];
}

void Work()
{
	for (scanf("%d",&M);M;M --)
	{
		int x,y,u,w,u2,w2;
		scanf("%d%d",&x,&y);
		if (depth[x] < depth[y]) swap(x,y);
		u = LCA(x,y);
		int dis = Dis(x,u) + Dis(y,u);
		w = Get(x,dis/2);
		u2 = Get(x,Dis(x,u)-1);
		w2 = Get(x,Dis(x,w)-1);
		int ans = max(far[x][0],Calc1(x,depth[w] >= depth[u2] ? w : u2));
		ans = max(ans,max(Calc2(dis&1 ? w : w2,u2)+Dis(y,u)+1,Calc1(u,1)+Dis(y,u)));
		if (y == u) ans = max(ans,Calc3(u,x,0));
		else ans = max(ans,max(Calc3(u,x,y)+Dis(y,u),max(far[y][0],Calc1(y,u2))));
		printf("%d\n",ans);
	}
}

int main()
{
	Initialize();
	Work();
	return 0;
}
