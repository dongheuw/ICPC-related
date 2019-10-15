#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const double eps = 1e-10;
int T,n,m;
double f[2505][55][55];

int main()
{
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	for (scanf("%d",&T);T;T --)
	{
		scanf("%d%d",&n,&m);
		memset(f,0,sizeof f);
		f[1][1][1] = 1;
		fo(k,1,n*m-1)
			fo(i,1,n)
				fo(j,1,m)
				{
					if (i < n || j < m) f[k+1][i][j] += f[k][i][j] * (i*j-k) / (n*m-k);
					f[k+1][i+1][j] += f[k][i][j] * (n-i) * j / (n*m-k);
					f[k+1][i][j+1] += f[k][i][j] * (m-j) * i / (n*m-k);
					f[k+1][i+1][j+1] += f[k][i][j] * (n-i) * (m-j) / (n*m-k);
				}
		double E = 0;
		fo(i,1,n*m) E += f[i][n][m] * i;
		printf("%.8lf\n",E);
	}
	return 0;
}
