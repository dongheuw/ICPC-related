#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 200005;
int N;

void read(int &x)
{
	char ch;
	x = 0;
	do ch = getchar(); while (ch < '0' || ch > '9');
	do x = x * 10 + ch - 48, ch = getchar(); while (ch >= '0' && ch <= '9');
}

struct Tree
{
	int etot,e[maxn][2];
	int tot,a[maxn],b[maxn<<1],c[maxn<<1],id[maxn<<1];
	int CNT,father[maxn],dfn[maxn][2],list[maxn];
	bool flag[maxn];
	void Add(int,int,int);
	void Read();
	void dfs(int);
}T[2];

void Tree::Add(int x,int y,int i)
{
	tot ++;
	b[tot] = y; c[tot] = a[x]; a[x] = tot;
	id[tot] = i;
}
	
void Tree::Read()
{
	fo(i,2,N)
	{
		int x; read(x);
		etot ++, e[etot][0] = i, e[etot][1] = x;
		Add(x,i,etot), Add(i,x,etot);
	}
}

int I[maxn];
void Tree::dfs(int x)
{
	dfn[x][0] = ++CNT;
	list[CNT] = x;
	for (I[x] = a[x];I[x];I[x] = c[I[x]])
		if (b[I[x]] != father[x])
			father[b[I[x]]] = x, dfs(b[I[x]]);
	dfn[x][1] = CNT;
}

void Initialize()
{
	read(N);
	T[0].Read(); T[1].Read();
	T[0].dfs(1); T[1].dfs(1);
}

int Del[2][maxn];
void Work()
{
	Del[0][0] = 1; read(Del[0][1]);
	puts("Blue"); printf("%d\n",Del[0][1]);
	T[0].flag[Del[0][1]] = 1;
	for (int i = 1;;i ^= 1)
	{
		Del[i][0] = 0;
		fo(j,1,Del[i^1][0])
		{
			int u = T[i^1].e[Del[i^1][j]][0], v = T[i^1].e[Del[i^1][j]][1];
			if (T[i^1].dfn[u][0] > T[i^1].dfn[v][0]) swap(u,v);
			
			fo(k,T[i^1].dfn[v][0],T[i^1].dfn[v][1])
			{
				int x = T[i^1].list[k];
				for (int p = T[i].a[x];p;p = T[i].c[p])
					while (p && T[i].flag[T[i].id[T[i].c[p]]]) T[i].c[p] = T[i].c[T[i].c[p]];
				
				for (int p = T[i].a[x];p;p = T[i].c[p])
				{
					if (T[i].flag[T[i].id[p]]) continue;
					int y = T[i].b[p];
					if (T[i^1].dfn[v][0] <= T[i^1].dfn[y][0] && T[i^1].dfn[y][0] <= T[i^1].dfn[v][1]) continue;
					T[i].flag[T[i].id[p]] = 1;
					Del[i][++Del[i][0]] = T[i].id[p];
				}
			}
		}
		if (!Del[i][0]) break;
		puts(i?"Red":"Blue");
		sort(Del[i]+1,Del[i]+1+Del[i][0]);
		fo(j,1,Del[i][0]) printf(j==Del[i][0]?"%d\n":"%d ",Del[i][j]);
	}
}

int main()
{
	Initialize();
	Work();
	return 0;
}
