#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;
const int maxn = 505;
int T,n,m,req[10] = {6,2,5,5,4,5,6,3,7,6};
typedef long long LL;
LL f[maxn][2][2][2];

LL dp(int r,int c,int x,int y)
{
	if (r < 0) return 0;
	LL &ret = f[r][c][x][y];
	if (ret != -1) return ret;
	if (r == 0 && c == 0 && x && y) return ret = 1;
	if (r == req[1] && c && x && y) return ret = 1;
	if (!r) return 0;
	ret = 0;
	if (!x && !y)
	{
		fo(i,0,9)
			fo(j,0,9)
			{
				int carry = (i+j+c) / 10, cur = (i+j+c) % 10;
				ret += dp(r-req[i]-req[j]-req[cur],carry,0,0);
				if (i) ret += dp(r-req[i]-req[j]-req[cur],carry,1,0);
				if (j) ret += dp(r-req[i]-req[j]-req[cur],carry,0,1);
				if (i && j) ret += dp(r-req[i]-req[j]-req[cur],carry,1,1);
				ret %= m;
			}
	} else
	if (!x)
	{
		fo(i,0,9)
		{
			int carry = (i+c) / 10, cur = (i+c) % 10;
			ret += dp(r-req[i]-req[cur],carry,0,y);
			if (i) ret += dp(r-req[i]-req[cur],carry,1,y);
			ret %= m;
		}
	} else
	if (!y)
	{
		fo(i,0,9)
		{
			int carry = (i+c) / 10, cur = (i+c) % 10;
			ret += dp(r-req[i]-req[cur],carry,x,0);
			if (i) ret += dp(r-req[i]-req[cur],carry,x,1);
			ret %= m;
		}
	}
	return ret;
}

int main()
{
	freopen("t.in","r",stdin);
	freopen("t.out","w",stdout);
	scanf("%d",&T);
	fo(t,1,T)
	{
		scanf("%d%d",&n,&m);
		memset(f,-1,sizeof f);
		printf("Case #%d: %lld\n",t,dp(n-3,0,0,0));
	}
	return 0;
}
