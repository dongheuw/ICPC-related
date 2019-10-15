#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 205;
const int maxm = 1000005;
const int inf = 0x7f7f7f7f; 

int T,n,m,tot,source,sink,ans;
int a[maxn],lab[maxn],b[maxm],c[maxm],d[maxm];

inline void read(int &x)
{
	static char ch;
	x = 0;
	do ch = getchar(); while (ch < '0' || ch > '9');
	do x = x * 10 + ch - 48, ch = getchar(); while (ch >= '0' && ch <= '9');
}

void insert(int x,int y,int z)
{
	tot ++;
	b[tot] = y;
	d[tot] = z;
	c[tot] = a[x];
	a[x] = tot;
}

void add(int x,int y,int z)
{
	insert(x,y,z);
	insert(y,x,0);
}

bool bfs()
{
	static int list[maxn];
	int st,en;
	list[st=en=1] = source;
	memset(lab,255,sizeof lab);
	lab[source] = 0;
	while (st <= en)
	{
		int x = list[st];
		for(int i = a[x];i;i = c[i])
			if (d[i] && lab[b[i]] == -1)
			{
				lab[b[i]] = lab[x] + 1;
				list[++en] = b[i];	
			}
		st ++;
	}
	return lab[sink] > -1;
}

int dfs(int x,int flow)
{
	if (x == sink) return flow;
	int ret = 0;
	for (int i = a[x];i;i = c[i])
		if (d[i] && lab[b[i]] == lab[x] + 1)
		{
			int now = dfs(b[i],min(flow,d[i]));
			d[i] -= now;
			d[i^1] += now;
			flow -= now;
			ret += now;
			if (!flow) return ret;
		}
	if (!ret) lab[x] = -1;
	return ret;
}

char s[maxn];
int A[maxn],B[maxn];
void Initialize()
{
	tot = 1;
	read(n);
	scanf("%s",s+1);
	source = n+10+1, sink = n+10+2;
	fo(i,0,sink) a[i] = 0;
	fo(i,0,9)
	{
		read(A[i]); read(B[i]);
		add(i+n+1,sink,B[i]-A[i]);
	}
	fo(i,1,n)
	{
		add(i,s[i]-48+n+1,inf);
		add(i,sink,A[s[i]-48]);
	}
	ans = 0;
	fo(i,1,n)
	{
		int sum = 0;
		fo(j,1,n)
		{
			int x;
			read(x);
			if (i != j)
			{
				sum += x;
				ans += x;
				add(i,j,x);
			}
		}
		add(source,i,sum);
	}
}

void Work()
{
	while (bfs()) ans -= dfs(source,inf);
}

int main(void)
{
	freopen("i.in","r",stdin);
	freopen("i.out","w",stdout);
	scanf("%d",&T);
	for (int cas = 1;cas <= T;cas ++)
	{
		Initialize();
		Work();
		printf("Case #%d: %d\n",cas,ans);
	}
	return 0;
}
