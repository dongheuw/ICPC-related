#include <cstdio>
#include <cstring>
#define  fr(i,x,y) for(i=x;i<=y;++i)
const int maxn=100010;
int T,n,m;
int a[maxn];
void Read()
{
	int i;
	scanf("%d",&n);
	fr(i,1,n)scanf("%d",&a[i]);
}
void Solve()
{
	int l,r,v,i;
	scanf("%d",&m);
	while(m--)
	{
		scanf("%d%d",&l,&r);
		v=a[l];
		fr(i,l+1,r)v%=a[i];
		printf("%d\n",v);
	}
}
int main()
{
	freopen("h.in","r",stdin);
	freopen("vio.out","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		Read();
		Solve();
	}
}
