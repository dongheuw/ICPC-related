
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long LL;

const int maxn = 30005;
LL x,st,ori,sum[maxn*4],num[maxn*4];
bool cov[maxn*4],tag;
int n,m,l,r;

void init()
{
   
}

void cut(int x,int l,int r)
{
    if(cov[x])
    {
		int m=(l+r)>>1;
        cov[x<<1]=cov[x<<1|1]=cov[x];
		num[x<<1]=num[x<<1|1]=num[x];
        sum[x<<1]=(m-l+1)*num[x];
        sum[x<<1|1]=(r-m)*num[x];
        cov[x]=0;
    }
}

void update(LL op,int L,int R,int l,int r,int x)
{
    if(L<=l&&r<=R)
    {
        cov[x]=1;
		num[x]=op;
        sum[x]=(r-l+1)*op;
        return;
    }
    cut(x,l,r);
    int m=(l+r)>>1;
    if(L<=m)update(op,L,R,l,m,x*2);
    if(R>m)update(op,L,R,m+1,r,x*2+1);
    sum[x]=sum[x<<1]+sum[x<<1|1];
}

LL query(int L,int R,int l,int r,int x)
{
    if(L<=l&&r<=R)return sum[x];
    cut(x,l,r);
    int m=(l+r)>>1;
    LL ret=0;
    if(L<=m)ret+=query(L,R,l,m,x*2);
    if(R>m)ret+=query(L,R,m+1,r,x*2+1);
    return ret;
}

void print(int l,int r,int x)
{
    if(l==r)
    {
        if(tag)printf(" ");
        else tag=1;
        printf("%lld",sum[x]);
        return ;
    }
	cut(x,l,r);
    int m=(l+r)>>1;
    print(l,m,x*2);
    print(m+1,r,x*2+1);
}

LL cal(LL x,int l,int r,bool up)
{
	if(x>=0)
	{
		if(up)return (x+r-l)/(r-l+1);
		else return x/(r-l+1);
	}
	else
	{
		x=-x;
		if(!up)return -(x+r-l)/(r-l+1);
		else return -x/(r-l+1);
	}
}

int main()
{
    while (scanf("%d%d",&n,&m) != EOF)
    {
        memset(sum,0,sizeof sum);
        memset(cov,0,sizeof cov);
        memset(num,0,sizeof num);
        tag = 0;
        for(int i=0;i<n;i++)
        {
            scanf("%lld",&x);
            update(x,i,i,0,n-1,1);
        }
        ori=sum[1];
        while(m--)
        {
            scanf("%d%d",&l,&r);
            l--;r--;
            st=query(l,r,0,n-1,1);
            if(ori>=sum[1])update(cal(st,l,r,1),l,r,0,n-1,1);
            else update(cal(st,l,r,0),l,r,0,n-1,1);
        }
        print(0,n-1,1);
        printf("\n\n");
    }
    return 0;
}
