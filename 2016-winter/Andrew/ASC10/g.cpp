#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int maxn = 205;

int n,c;
double a[2][3],f[maxn][maxn];
int pre[maxn][maxn];

double Dist(double *a,double x,double y)
{
	return fabs(a[0] * x + a[1] * y + a[2]);
}

void Print(int n,int k,char c)
{
	if (n > 0)
	{
		Print(n-1,k-pre[n][k],' ');
		printf("%d%c",pre[n][k]+1,c);
	}
}

void rLine(double *a)
{
	static double x1,y1,x2,y2,z;
	scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
	a[0] = y1 - y2;
	a[1] = x2 - x1;
	a[2] = x1 * y2 - x2 * y1;
	z = sqrt(a[0]*a[0]+a[1]*a[1]);
	a[0] /= z;
	a[1] /= z;
	a[2] /= z;
}


int main()
{
	while (scanf("%d%d",&n,&c) != EOF)
	{
		rLine(a[0]);
		rLine(a[1]);
		f[0][0] = 0;
		for (int i = 1;i <= n;i ++)
		{
			double x,y,z,u,v;
			scanf("%lf%lf%lf",&x,&y,&z);
			u = Dist(a[0],x,y) * z;
			v = Dist(a[1],x,y) * z;
			f[i][0] = f[i-1][0] + u;
			pre[i][0] = 0;
			for (int j = 1;j < i;j ++)
				if (f[i-1][j] + u <= f[i-1][j-1] + v)
					f[i][j] = f[i-1][j] + u, pre[i][j] = 0;
				else f[i][j] = f[i-1][j-1] + v, pre[i][j] = 1;
			f[i][i] = f[i-1][i-1] + v, pre[i][i] = 1;
		}
		int k = -1;
		for (int j = (n-c+1)/2;j <= (n+c)/2;j ++)
			if (k == -1 || f[n][j] <= f[n][k]) k = j;
		Print(n,k,'\n');
		puts("");
	}
	return 0;
}
