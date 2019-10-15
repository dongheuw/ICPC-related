#include <cstdio>
#include <cstring>
#define  fr(i,x,y) for(i=x;i<=y;++i)
#define  frd(i,x,y) for(i=x;i>=y;--i)
#define  frk(k,x,z) for(k=first[x];z=edge[k].y,k;k=edge[k].nxt)
typedef long long LL;
const int maxn=100010;
struct Edge{int y,nxt;}edge[maxn];
LL K,ans;
int T,n,E_cnt;
int a[maxn],first[maxn],que[maxn];
void Insert(int x,int y){edge[++E_cnt]=(Edge){y,first[x]};first[x]=E_cnt;}
void Read()
{
	int i,x,y;
	scanf("%d%lld",&n,&K);
	fr(i,1,n)scanf("%d",&a[i]);
	memset(first+1,0,n*sizeof(int));E_cnt=0;
	fr(i,2,n)
	{
		scanf("%d%d",&x,&y);
		Insert(x,y);
	}
}
void Solve()
{
	int i,j,x,k,y;
	ans=0;
	fr(i,1,n)
	{
		que[que[0]=1]=i;
		fr(j,1,que[0])
		{
			x=que[j];
			frk(k,x,y)
			{
				que[++que[0]]=y;
				if((LL)a[i]*a[y]<=K)ans++;
			}
		}
	}
	printf("%lld\n",ans);
}
int main()
{
	freopen("j.in","r",stdin);
	freopen("vio.out","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		Read();
		Solve();
	}
}
