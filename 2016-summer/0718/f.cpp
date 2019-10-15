#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

const int maxn = 256;
const int mod = 1000000009;

typedef long long LL;

int T,R,C,N;
LL G[maxn][maxn],F[maxn][maxn],c[maxn][maxn];

void Mult(LL a[][maxn],LL b[][maxn])
{
	fo(i,0,N-1)
		fo(j,0,N-1)
		{
			c[i][j] = 0;
			fo(k,0,N-1)
			{
				c[i][j] += a[i][k] * b[k][j];
				c[i][j] %= mod;
			}
		}
	fo(i,0,N-1)
		fo(j,0,N-1) a[i][j] = c[i][j];
}

int ok(int S,int col,int row)
{
	return S & (1 << (col*R + row));
}

bool Check(int S,int next)
{
	fo(r,0,R-1)
	{
		if (!ok(next,0,r)) continue;
		if (r-2 >= 0 && ok(S,1,r-2)) return 0;
		if (r-1 >= 0 && ok(S,0,r-1)) return 0;
		if (r+1 < R && ok(S,0,r+1)) return 0;
		if (r+2 < R && ok(S,1,r+2)) return 0;
	}
	return 1;
}

int main()
{
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);
	for (scanf("%d",&T);T;T --)
	{
		scanf("%d%d",&R,&C);
		memset(G,0,sizeof G);
		N = 1 << (2*R);
		fo(i,0,N-1)
			fo(j,0,(1<<R)-1)
				if (Check(i,j))
				{
					int k = (i >> R) | (j << R);
					G[i][k] = 1;
				}
		memset(F,0,sizeof F);
		fo(i,0,N) F[i][i] = 1;
		while (C)
		{
			if (C&1) Mult(F,G);
			Mult(G,G);
			C >>= 1;
		}
		LL ans = 0;
		fo(i,0,N-1) ans = (ans + F[0][i]) % mod;
		printf("%lld\n",ans);
	}
	return 0;
}
