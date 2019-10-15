#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 1000005;
int T,N,tot,a[maxn],b[maxn],c[maxn];
int CNT,r[maxn][2],link[maxn],s[maxn];

struct node
{
	int Max,Min,add;
}t[maxn*4];

void read(int &x)
{
	char ch; x = 0;
	do ch = getchar(); while (ch < '0' || ch > '9');
	do x = x * 10 + ch - 48, ch = getchar(); while (ch >= '0' && ch <= '9');
}

void Add(int x,int y)
{
	tot ++;
	b[tot] = y;
	c[tot] = a[x];
	a[x] = tot;
}

void dfs(int x)
{
	r[x][0] = ++ CNT;
	for (int i = a[x];i;i = c[i]) dfs(b[i]);
	r[x][1] = CNT;
}

inline void Update(int z)
{
	t[z].Max = max(t[z*2].Max,t[z*2+1].Max);
	t[z].Min = min(t[z*2].Min,t[z*2+1].Min);
}

void Maketree(int z,int l,int r)
{
	if (l == r)
	{
		t[z].Max = t[z].Min = s[link[l]];
		t[z].add = 0;
		return;
	}
	t[z].add = 0;
	int mid = (l + r) >> 1;
	Maketree(z*2,l,mid);
	Maketree(z*2+1,mid+1,r);
	Update(z);
}

void Initialize()
{
	read(N);
	tot = 0;
	fo(i,1,N) a[i] = 0;
	fo(i,2,N)
	{
		int x;
		read(x);
		Add(x,i);
	}
	CNT = 0;
	dfs(1);
	fo(i,1,N) link[r[i][0]] = i;
	fo(i,1,N) read(s[i]);
	Maketree(1,1,N);
}

inline void Pushdown(int z)
{
	t[z*2].Max += t[z].add;
	t[z*2].Min += t[z].add;
	t[z*2].add += t[z].add;
	t[z*2+1].Max += t[z].add;
	t[z*2+1].Min += t[z].add;
	t[z*2+1].add += t[z].add;
	t[z].add = 0;
}

void Modify(int z,int l,int r,int x,int y,int c)
{
	if (x <= l && r <= y)
	{
		t[z].Max += c;
		t[z].Min += c;
		t[z].add += c;
		return;
	}
	int mid = (l + r) >> 1;
	Pushdown(z);
	if (x <= mid) Modify(z*2,l,mid,x,y,c);
	if (y > mid) Modify(z*2+1,mid+1,r,x,y,c);
	Update(z);
}

int Query_max(int z,int l,int r,int x,int y)
{
	if (x <= l && r <= y) return t[z].Max;
	int mid = (l + r) >> 1;
	Pushdown(z);
	int ret = 0;
	if (x <= mid) ret = max(ret,Query_max(z*2,l,mid,x,y));
	if (y > mid) ret = max(ret,Query_max(z*2+1,mid+1,r,x,y));
	return ret;
}

int Query_min(int z,int l,int r,int x,int y)
{
	if (x <= l && r <= y) return t[z].Min;
	int mid = (l + r) >> 1;
	Pushdown(z);
	int ret = 0x7fffffff;
	if (x <= mid) ret = min(ret,Query_min(z*2,l,mid,x,y));
	if (y > mid) ret = min(ret,Query_min(z*2+1,mid+1,r,x,y));
	return ret;
}

void Work()
{
	int Q;
	for (read(Q);Q;Q --)
	{
		char sig[5];
		scanf("%s",sig);
		if (sig[0] == 'Q')
		{
			int x,ans;
			read(x);
			ans = Query_max(1,1,N,r[x][0],r[x][1]) - Query_min(1,1,N,r[x][0],r[x][1]);
			printf("%d\n",ans);
		} else
		{
			int x,c;
			read(x), read(c);
			Modify(1,1,N,r[x][0],r[x][1],c);
		}
	}
}

int main()
{
	freopen("i.in","r",stdin);
	freopen("i.out","w",stdout);
	int cs = 0;
	for (read(T);T;T --)
	{
		cs ++;
		Initialize();
		Work();
	}
	return 0;
}
