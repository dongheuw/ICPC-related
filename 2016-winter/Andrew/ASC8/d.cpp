#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

int n;
long long ans[8],f[8][1<<14];

void Update(int d,int mask,int i,long long v)
{
	if (d + n == i)
	{
		f[d][mask] += v;
		return;
	}
	int x = (mask >> i) & 1;
	int y = (mask >> (i+1)) & 1;
	if (x == 0 && y == 1) Update(d,mask^(1<<i)^(1<<(i+1)),i+1,v);
	Update(d,mask,i+1,v);
}

int main()
{
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	for (n = 1;n <= 7;n ++)
	{
		memset(f,0,sizeof f);
		f[0][(1<<n)-1] = 1;
		fo(i,0,n-1)
			fo(j,0,(1<<(n+i))-1)
				if (f[i][j]) Update(i+1,j<<1,0,f[i][j]);
		fo(i,0,(1<<(n+n))-1) ans[n] += f[n][i] * f[n][i];
	}
	for (int t = 1;scanf("%d",&n) != EOF;t ++)
	{
		if (t > 1) puts("");
		printf("%lld\n",ans[n]);
	}
	return 0;
}
