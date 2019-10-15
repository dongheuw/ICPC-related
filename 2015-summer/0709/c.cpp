#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 10005;
const int maxm = 100005;

int N,M,T,tot,a[maxm],b[maxm],c[maxm],list[maxn],ind[maxn];
int q[maxn];
bool missing,recheck;

void Insert(int x,int y)
{
	tot ++;
	b[tot] = y;
	c[tot] = a[x];
	a[x] = tot;
}

void Topsort()
{
	int l = 1,r = 0;
	fo(i,1,N) if (!ind[i]) q[++r] = i;
	fo(t,1,N)
	{
		if (l > r)
		{
			recheck = 1;
			return;
		} else
		if (l < r) missing = 1;
		list[++list[0]] = q[l];
		ind[q[l]] = -1;
		for (int i = a[q[l]];i;i = c[i])
			if (--ind[b[i]] == 0) q[++r] = b[i];
		l ++;
	}
}

int main()
{
	freopen("mid.in","r",stdin);
	freopen("c.out","w",stdout);
	scanf("%d",&T);
	while (T --)
	{
		scanf("%d%d",&N,&M);
		tot = 0;
		fo(i,1,N) ind[i] = a[i] = 0;
		fo(i,1,M)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			Insert(x,y);
			ind[y] ++;
		}
		list[0] = 0;
		missing = recheck = 0;
		Topsort();
		if (recheck) puts("recheck hints");
		else if (missing) puts("missing hints");
		else
		{
			fo(i,1,N-1) printf("%d ",list[i]);
			printf("%d\n",list[N]);
		}
	}
	return 0;
}
