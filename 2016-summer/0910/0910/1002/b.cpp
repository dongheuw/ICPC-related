#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define  fr(i,x,y) for(i=x;i<=y;++i)
#define  frd(i,x,y) for(i=x;i>=y;--i)
using namespace std;
const int maxn=100010;
const int maxnum=1000010;
const int maxblo=350;
struct Block{
	int gcd,cnt_l,cnt_r;
	int l[20],r[20];
}blo[maxblo][maxblo];
int n,m,N,blo_sz,bj,bj1;
int a[maxn],bel[maxn];
int vis[maxnum],vis1[maxnum];
int que[20],que1[20];
void Read()
{
	int i;
	fr(i,1,n)scanf("%d",&a[i]);
}
int Gcd(int a,int b)
{
	int t;
	while(b)
	{
		t=a;
		a=b;
		b=t%b;
	}
	return a;
}
void Pretreat()
{
	int i,j,v;
	N=(int)sqrt(n*1.0);
	fr(i,1,n)bel[i]=(i-1)/N+1;
	blo_sz=bel[i];
	bj=0;
	fr(i,1,blo_sz-1)
	{
		v=a[(i-1)*N+1];
		vis[v]=++bj;
		que[que[0]=1]=v;
		cnt=0;
		fr(j,(i-1)*N+2,n)
		{
			v=Gcd(v,a[j]);
			if(vis[v]!=bj)vis[v]=bj,++cnt,que[++que[0]]=v;
			if(j%N==0)
			{
				blo[i][j/N].gcd=v;
				blo[i][j/N].cnt_l=cnt;
				sort(que+1,que+que[0]+1);
				memcpy(blo[i][j/N].l,que,(que[0]+1)*sizeof(int));
			}
		}
	}
	frd(i,blo_sz-1,1)
	{
		v=a[i*N];
		vis[v]=++bj;
		que[que[0]=1]=v;
		cnt=0;
		frd(j,i,1)
		{
			v=Gcd(v,a[j]);
			if(vis[v]!=bj)vis[v]=bj,++cnt,que[++que[0]]=v;
			if((j-1)%N==0)
			{
				blo[j/N][i].cnt_r=cnt;
				sort(que+1,que+que[0]+1);
				memcpy(blo[j/n][i].r,que,(que[0]+1)*sizeof(int));
			}
		}
	}
}
void Solve()
{
	int i,j,l,r,x;
	bj1=0;
	while(m--)
	{
		scanf("%d%d",&l,&r);
		
	}
}
int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	while(~scanf("%d%d",&n,&m))
	{
		Read();
		Pretreat();
		Solve();
	}
}
