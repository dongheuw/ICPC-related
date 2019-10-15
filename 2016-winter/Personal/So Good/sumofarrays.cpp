#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;

typedef long long LL;
typedef double LD;

const int N = int(3e5 + 5);
const LD pi = acos(-1);
const LD eps = 1e-6;

struct comp
{
	LD x,y;
	comp(){}
	comp(LD X,LD Y):x(X),y(Y){}
};

comp operator+(comp a,comp b){return comp(a.x+b.x,a.y+b.y);}
comp operator-(comp a,comp b){return comp(a.x-b.x,a.y-b.y);}
comp operator*(comp a,comp b){return comp(a.x*b.x - a.y*b.y,a.x*b.y + b.x*a.y);}

int trans[N];
comp pa[N],pb[N];
int m,cn;

int tc[N+N],na[N],nb[N];
int ta[N],tb[N],fa,fb;
int a[N],b[N],n;

void maketrans()
{
	int t(0);
	for(int i=1;i<cn;i<<=1) ++t;
	for(int i=0,p,tp,j;i<cn;i++)
	{
		for(p=0,tp=i,j=0;j<t;j++,tp>>=1) p = (p<<1) + (tp&1);
		trans[i] = p;
	}
}

comp tp[N];
void dft(comp *a,int sign=1)
{
	for(int i=0;i<cn;i++) tp[trans[i]] = a[i];
	for(int m=2;m<=cn;m<<=1)
	{
		int hal = m>>1;
		for(int i=0;i<hal;i++)
		{
			comp it (cos(i*sign*pi/hal),sin(i*sign*pi/hal));
			for(int j=i;j<cn;j+=m)
			{
				comp u = tp[j],v = tp[j+hal] * it;
				tp[j] = u+v,tp[j+hal] = u-v;
			}
		}
	}
	for(int i=0;i<cn;i++) a[i] = tp[i];
}

void draft(int *g)
{
	int a,b,c,d,e,f;
	scanf("%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f);
	g[0] = a,g[1] = b;
	for(int i=2;i<n;i++) g[i] = (LL(g[i-1])*c + LL(g[i-2])*d + e) % f;
}

int main()
{
	while(scanf("%d",&n) > 0)
	{
		draft(a);
		draft(b);
		
		memset(ta,0,sizeof(ta));
		memset(tb,0,sizeof(tb));
		memset(tc,0,sizeof(tc));
		fa = 0,fb = 0;
		
		for(int i=0;i<n;i++)
		{
			++ta[a[i]],++tb[b[i]];
			if(a[i]>fa) fa=a[i];
			if(b[i]>fb) fb=b[i];
		}
		
		int L=10;
		
		na[fa+1] = nb[fb+1] = N;
		for(int i=fa;i>=0;i--) na[i] = ta[i]>=L ? i : na[i+1];
		for(int i=fb;i>=0;i--) nb[i] = tb[i]>=L ? i : nb[i+1];
		
		for(int i=na[0];i<=fa;i=na[i+1]) for(int j=nb[0];j<=fb;j=nb[j+1]) 
		tc[i+j] += min(ta[i],tb[j]) - L + 1;
		
		m = max(fa,fb) + 1;
		for(cn=1;cn<m;cn<<=1);
		cn<<=1,maketrans();
		
		for(int ip=1;ip<L;ip++)
		{
			for(int i=0;i<cn;i++)
			{
				pa[i] = comp(ta[i] >= ip,0);
				pb[i] = comp(tb[i] >= ip,0);
			}
			
			dft(pa),dft(pb);
			for(int i=0;i<cn;i++) pa[i] = pa[i] * pb[i];
			dft(pa,-1);
			
			for(int i=0;i<cn;i++) tc[i] += int(pa[i].x / cn + eps);
		}
		
		int ansa(-1),ansb(0);
		for(int i=fa+fb;i>=0;i--) if(tc[i]>ansa) ansa=tc[i],ansb=i;
		printf("%d %d\n",ansa,ansb);
	}
	
	return 0;
}
