#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

int t,n,q,a[55];
std::bitset<90> f[11];
bool ans[55][55][55];

bool check(int x,int y,int z)
{
	fo(i,0,10) f[i].reset();
	f[0][0] = 1;
	fo(i,1,n)
	{
		if (i == x || i == y || i == z || a[i] > 87) continue;
		for (int j = 9;j >= 0;j --) f[j+1] |= f[j] << a[i];
		if (f[10][87]) return 1;
	}
	return 0;
}

bool g[51][11][90],rec[51][11][90],sol[51];
void solve()
{
	memset(g,0,sizeof g);
	memset(rec,0,sizeof rec);
	memset(sol,0,sizeof sol);
	g[0][0][0] = 1;
	fo(i,1,n)
	{
		if (a[i] > 87) continue;
		g[i][0][0] = 1;
		fo(j,1,10)
			fo(k,0,87)
			{
				g[i][j][k] = g[i-1][j][k];
				if (k >= a[i] && g[i-1][j-1][k-a[i]])
				{
					g[i][j][k] = 1;
					rec[i][j][k] = 1;
				}
			}
		if (g[i][10][87])
		{
			sol[0] = 1;
			for (int x = i,y = 10,z = 87;y > 0;)
			{
				if (rec[x][y][z])
				{
					sol[x] = 1;
					z -= a[x];
					x --;
					y --;
				} else x --;
			}
			break;
		}
	}
}

bool cmp(int x,int y,int z)
{
	return !sol[x] && !sol[y] && !sol[z];
}

int main()
{
	freopen("l.in","r",stdin);
	freopen("l.out","w",stdout);
	for (scanf("%d",&t);t;t --)
	{
		scanf("%d",&n);
		fo(i,1,n) scanf("%d",&a[i]);
		solve();
		fo(i,1,n)
			fo(j,i,n)
				fo(k,j,n)
				{
					if (!sol[0]) ans[i][j][k] = 0;
					else if (cmp(i,j,k)) ans[i][j][k] = 1;
					else ans[i][j][k] = check(i,j,k);
				}
		for (scanf("%d",&q);q;q --)
		{
			scanf("%d%d%d",&a[0],&a[1],&a[2]);
			std::sort(a,a+3);
			puts(ans[a[0]][a[1]][a[2]]?"Yes":"No");
		}
	}
	return 0;
}
