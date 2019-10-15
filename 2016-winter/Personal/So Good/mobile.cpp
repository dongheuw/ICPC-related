#include <cstdio>
#include <algorithm>
#include <cmath>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
using namespace std;

const int maxn = 1000005;
int n,N,L,tot,top;
int stack[maxn];
double a[maxn][2],ans;

double P(int i,int j)
{
	return (a[i][0]+a[j][0]+(a[i][1]*a[i][1]-a[j][1]*a[j][1])/(a[i][0]-a[j][0]))/2;
}

double dist(int i,double x)
{
	return sqrt((a[i][0]-x)*(a[i][0]-x)+a[i][1]*a[i][1]);
}

int main()
{
	freopen("mobile.in","r",stdin);
	freopen("mobile.out","w",stdout);
	scanf("%d%d",&n,&L);
	fo(i,1,n)
	{
		double x,y;
		scanf("%lf%lf",&x,&y);
		if (a[N][0] != x || !N)
		{
			a[++N][0] = x;
			a[N][1] = y;
		} else
		if (a[N][0] == x && abs(y)<abs(a[N][1])) a[N][1] = y;
	}
	fo(i,1,N)
	{
		while (top > 1 && P(stack[top],i)<P(stack[top],stack[top-1])) top --;
		stack[++top] = i;
	}
	fo(i,1,top-1)
	{
		double p = P(stack[i],stack[i+1]);
		if (p > 0 && p < L) ans = max(ans,dist(stack[i],p));
	}
	double dis0 = 1e10,disL = 1e10;
	fo(i,1,top)
	{
		dis0 = min(dis0,dist(stack[i],0));
		disL = min(disL,dist(stack[i],L));
	}
	printf("%.5f\n",max(ans,max(dis0,disL)));
	return 0;
}
