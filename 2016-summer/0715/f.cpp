#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define fd(i,a,b) for (int i = a;i >= b;i --)

using namespace std;

const int maxn = 100005;
int n;
int a[maxn],c[maxn*2],f1[maxn],f2[maxn],tree[maxn/10+5];

int Query(int x)
{
	int ret = 0;
	for (;x > 0;x -= x&(-x)) ret = max(ret,tree[x]);
	return ret;
}

void Add(int x,int val)
{
	if (x == 0) return;
	for (;x <= 10000;x += x&(-x)) tree[x] = max(tree[x],val);
}

int Calc(int x)
{
	f1[0] = 0;
	memset(tree,0,sizeof tree);
	fo(i,x+1,x+n-1)
	{
		if(c[i] == 10000)
		{
			f1[i-x] = f1[i-x-1];
			continue;
		}
		int tmp = Query(10000-c[i]+1)+c[i];
		f1[i-x] = max(f1[i-x-1],tmp);
		Add(10000-c[i]+1,tmp);
	}

	f2[n] = 0;
	memset(tree,0,sizeof tree);
	fd(i,x+n-1,x+1)
	{
		if(c[i] == 10000)
		{
			f2[i-x] = f2[i-x+1];
			continue;
		}
		int tmp = Query(10000-c[i]+1)+c[i];
		f2[i-x] = max(f2[i-x+1],tmp);
		Add(10000-c[i]+1,tmp);
	}

	int ret = 0;
	fo(i,0,n-1) ret = max(ret,f1[i]+f2[i+1]);
	return ret;
}

int main()
{
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);
	while (~scanf("%d",&n))
	{
		fo(i,0,n-1)
		{
			scanf("%d",&a[i]);
			c[i] = a[i];
			c[i+n] = a[i];
		}
		int ans = 0;
		fo(i,0,n-1)
			if (a[i] == 10000) ans = max(ans,Calc(i));
		printf("%d\n",ans+10000);
	}
	return 0;
}
