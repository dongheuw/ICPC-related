#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

const int maxn = 110;

int r,n[2],a[2][maxn],f[2][maxn];
bool vst[maxn],tmp[maxn][maxn],c[2][maxn];
long long two[maxn][2];

void Dfs(int u)
{
	vst[u] = 1;
	if (!vst[f[0][u]]) Dfs(f[0][u]);
	if (!vst[f[1][u]]) Dfs(f[1][u]);
}

int Calc(int o,int x)
{
	int ret = 0, s = 1;
	fo(i,0,n[o])
	{
		ret = (ret + a[o][i] * s) % r;
		s = s * x % r;
	}
	return ret;
}

bool Equal(bool a[],bool b[])
{
	fo(i,0,r-1) if (a[i] != b[i]) return 0;
	return 1;
}

int main()
{
	long long MaxInt = (long long)1e18;
	memset(two,0,sizeof two);
	two[0][0] = 1;
	fo(i,1,100)
	{
		two[i][0] = two[i-1][0] * 2;
		two[i][1] = two[i-1][1] * 2;
		if (two[i][0] >= MaxInt)
		{
			two[i][1] += two[i][0] / MaxInt;
			two[i][0] %= MaxInt;
		}
	}
	while (scanf("%d",&r) != EOF && r)
	{
		scanf("%d",&n[0]);
		for (int i = n[0];i >= 0;i --) scanf("%d",&a[0][i]);
		scanf("%d",&n[1]);
		for (int i = n[1];i >= 0;i --) scanf("%d",&a[1][i]);
		fo(i,0,r-1) f[0][i] = Calc(0,i);
		fo(i,0,r-1) f[1][i] = Calc(1,i);
		int cnt = 0;
		fo(i,0,r-1)
		{
			memset(c,0,sizeof c);
			memset(vst,0,sizeof vst);
			Dfs(i);
			fo(j,0,r-1)
				if (vst[j]) c[0][f[0][j]] = c[1][f[1][j]] = 1;
			bool check = 1;
			fo(j,0,r-1)
				if (vst[j] && (!c[0][j]|| !c[1][j]) || !vst[j] && (c[0][j] || c[1][j]))
				{
					check = 0;
					break;
				}
			if (check)
				fo(j,0,cnt-1)
					if (Equal(tmp[j],vst))
					{
						check = 0;
						break;
					}
			if (check)
			{
				fo(j,0,r-1) tmp[cnt][j] = vst[j];
				cnt ++;
			}
		}
		if (two[cnt][1] > 0) printf("%lld%018lld\n",two[cnt][1],two[cnt][0]);
		else printf("%lld\n",two[cnt][0]);
	}
	return 0;
}
