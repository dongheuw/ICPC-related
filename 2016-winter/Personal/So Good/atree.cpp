#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define fd(i,a,b) for (int i = a;i >= b;i --)

using namespace std;

typedef long long LL;

const int maxn = 100010;
const int maxm = 2*maxn;
int T,N,tot,maxbit;
int A[maxn],father[maxn];
int a[maxn],b[maxm],c[maxm],bfs[maxn];
LL cntand,cntor,cntxor,all;
LL x1[maxn],x0[maxn],a1[maxn],o0[maxn];

inline void read(int &x)
{
	static char ch;
	x = 0;
	do ch = getchar(); while (ch < '0' || ch > '9');
	do x = x * 10 + ch - 48, ch = getchar(); while (ch >= '0' && ch <= '9');
}

inline void Add(int x,int y)
{
	tot ++;
	b[tot] = y;
	c[tot] = a[x];
	a[x] = tot;
}

inline void Insert(int x,int y)
{
	Add(x,y);
	Add(y,x);
}

inline void Set()
{
	memset(a,0,(N+1)*4);
	memset(father,0,(N+1)*4);
	tot = 0;
	cntand = cntor = cntxor = 0;
	all = (LL)N * N;
}

void Initialize()
{
	read(N);
	Set();
	fo(i,1,N) read(A[i]);
	fo(i,1,N-1)
	{
		int x,y;
		read(x),read(y);
		Insert(x,y);
	}
	maxbit = 0;
	fo(i,1,N) 
	{
		int cnt = 0;
		int x = A[i];
		while (x)
		{
			cnt ++;
			x /= 2;
		}
		maxbit = max(maxbit,cnt);
	}
}

LL sand1,sor0,sxor1,sxor0;
LL and1,or0,xor1;

inline void Resume()
{
	memset(x0,0,(N+1)*8);
	memset(x1,0,(N+1)*8);
	memset(a1,0,(N+1)*8);
	memset(o0,0,(N+1)*8);
	and1 = or0 = xor1 = 0;
}

void DP(int x,int k)
{
	sand1 = sor0 = sxor1 = sxor0 = 0;
	for (int i = a[x];i;i = c[i])
		if (b[i] != father[x])
		{
			sand1 += a1[b[i]];
			sor0 += o0[b[i]];
			sxor1 += x1[b[i]];
			sxor0 += x0[b[i]];
			if (A[x] & (1 << k))
			{
				a1[x] += a1[b[i]];
				x1[x] += x0[b[i]];
				x0[x] += x1[b[i]];
			} else 
			{
				o0[x] += o0[b[i]];
				x0[x] += x0[b[i]];
				x1[x] += x1[b[i]];
			}
		}
}

void Count(int x,int k)
{
	int flag = A[x] & (1 << k);
	for (int i = a[x];i;i = c[i])
	{
		int v = b[i];
		if (father[x] == v) continue;

		if (flag)
		{
			and1 += a1[v] * (sand1 - a1[v]);
			xor1 += x1[v] * (sxor1 - x1[v]);
			xor1 += x0[v] * (sxor0 - x0[v]);
		} else 
		{
			or0 += o0[v] * (sor0 - o0[v]);
			xor1 += x1[v] * (sxor0 - x0[v]);
			xor1 += x0[v] * (sxor1 - x1[v]); 
		}
	}
	if (flag)
	{
		and1 += a1[x] * 2 + 1;
		a1[x] ++;
		xor1 += x1[x] * 2 + 1;
		x1[x] ++;
	} else 
	{
		or0 += o0[x] * 2 + 1;
		o0[x] ++;
		x0[x] ++;
		xor1 += x1[x] * 2;
	}
}

void DEAL(int k)
{
	fd(i,N,1)
	{
		DP(bfs[i],k);
		Count(bfs[i],k);
	}
	cntand += and1 * (1 << k);
	cntor += (all - or0) * (1 << k);
	cntxor += xor1 * (1 << k);
}

void Bfs()
{
	int l = 0;
	int r = 1;
	bfs[1] = 1;
	while (l < r)
	{
		int x = bfs[++l];
		for (int i = a[x];i;i = c[i])
			if (b[i] != father[x])
			{
				father[b[i]] = x;
				bfs[++r] = b[i];
			}
	}
}

void Work()
{
	Bfs();
	fo(i,1,maxbit)
	{
		Resume();
		DEAL(i-1);
	}
}

void Print()
{
	printf("%.3f ",(double)cntand/all);
	printf("%.3f ",(double)cntor/all);
	printf("%.3f\n",(double)cntxor/all);
}

int main()
{
	scanf("%d",&T);
	while (T --)
	{
		Initialize();
		Work();
		Print();
	}
	return 0;
}
