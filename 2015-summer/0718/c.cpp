#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 205;
const int inf = (int)1e9;

int n,t[maxn],d[maxn],f[maxn][maxn][2],sol[maxn][maxn][2];

void Print(int l,int r,int p)
{
	if (l == r) printf("%d\n",l+1);
	else if (sol[l][r][p] == 0) printf("%d ",l+1), Print(l+1,r,0);
	else printf("%d ",r+1), Print(l,r-1,1);
}

int Solve(int l,int r,int p)
{
	int &ret = f[l][r][p];
	if (ret != -1) return ret;
	if (l == r) return ret = 0;
	ret = inf;
	int temp = d[l+1] - d[l] + Solve(l+1,r,0);
	if (t[l] > temp)
	{
		if (p != 0) temp += d[r] - d[l];
		if (temp < ret) ret = temp, sol[l][r][p] = 0;
	}

	temp = d[r] - d[r-1] + Solve(l,r-1,1);
	if (t[r] > temp)
	{
		if (p != 1) temp += d[r] - d[l];
		if (temp < ret) ret = temp, sol[l][r][p] = 1;
	}
	return ret;
}

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	while (scanf("%d",&n) != EOF)
	{
		fo(i,0,n-1) scanf("%d",&t[i]);
		fo(i,0,n-1) scanf("%d",&d[i]);
		memset(f,-1,sizeof f);
		if (Solve(0,n-1,0) == inf) printf("Mission Impossible\n");
		else Print(0,n-1,0);
	}
	return 0;
}
