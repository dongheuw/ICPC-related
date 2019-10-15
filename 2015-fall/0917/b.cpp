#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for(inti=a;i<=b;i++)
using namespace std;

typedef long long LL;

char str[100010];
int len,m,q;
LL b[100010];

const int Max = 100010;

int num[Max];
int sa[Max],Rank[Max],height[Max];
int wa[Max],wb[Max],wv[Max],wd[Max];

int cmp(int *r,int a,int b,int l)
{
	return r[a]==r[b]&&r[a+l]==r[b+l];
}

void da(int *r,int n,int m)
{
	int i,j,p,*x=wa,*y=wb,*t;
	for(i=0;i<m;i++)wd[i]=0;
	for(i=0;i<n;i++)wd[x[i]=r[i]]++;
	for(i=1;i<m;i++)wd[i]+=wd[i-1];
	for(i=n-1;i>=0;i--)sa[--wd[x[i]]]=i;
	for(j=1,p=1;p<n;j*=2,m=p)
	{
		for(p=0,i=n-j;i<n;i++)y[p++]=i;
		for(i=0;i<n;i++)if(sa[i]>=j)y[p++]=sa[i]-j;
		for(i=0;i<n;i++)wv[i]=x[y[i]];
		for(i=0;i<m;i++)wd[i]=0;
		for(i=0;i<n;i++)wd[wv[i]]++;
		for(i=1;i<m;i++)wd[i]+=wd[i-1];
		for(i=n-1;i>=0;i--)sa[--wd[wv[i]]]=y[i];
		for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}

void calHeight(int *r,int n)
{
	int i,j,k=0;
	for(i=1;i<=n;i++)Rank[sa[i]]=i;
	for(i=0;i<n;height[Rank[i++]]=k)
	for(k?k--:0,j=sa[Rank[i]-1];r[i+k]==r[j+k];k++);
}

void Initialize()
{
	len=strlen(str);
	m=30;
	for(int i=0;i<=len;i++)num[i]=str[i]-'a'+1;
	num[len]=0;
	da(num,len+1,m);
	calHeight(num,len);
}

void Work()
{
	b[0]=0;
	for(int i=1;i<=len;i++)b[i]=b[i-1]+(len-sa[i]-height[i]);
	scanf("%d",&q);
	int l=0,r=0;
	while(q--)
	{
		LL v;
		scanf("%lld",&v);
		LL k=(l^r^v)+1;
		if(k>b[len])
		{
			l=r=0;
			printf("%d %d\n",l,r);
			continue;
		}
		int fnd=lower_bound(b+1,b+len+1,k)-b-1;
		int strl=k-b[fnd];
		l=sa[fnd+1];
		r=sa[fnd+1]+height[fnd+1]+strl-1;
		int d=r-l+1;
		while(fnd+1<len&&height[fnd+2]>=d)
		{
			fnd++;
			l=min(l,sa[fnd+1]);
			r=min(r,l+d-1);
		}
		l++;r++;
		printf("%d %d\n",l,r);
	}
}

int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	while(~scanf("%s",str))
	{
		Initialize();
		Work();
	}
	return 0;
}
