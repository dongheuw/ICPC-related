#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 55;

int n,health,strength,power,mana;
int ms[maxn],mp[maxn],mm[maxn],f[maxn][maxn][maxn];
bool g[maxn][maxn][maxn];	
char ans[maxn];

int main()
{
  	while (scanf("%d%d%d%d%d",&n,&health,&strength,&power,&mana) != EOF)
  	{
		for (int i = 1;i <= n;i ++) scanf("%d%d%d",&ms[i],&mp[i],&mm[i]);
		memset(f,255,sizeof f);
		memset(g,0,sizeof g);
		memset(ans,0,sizeof ans);
		for (int i = 0;i <= mana;i ++) f[0][0][i] = health;
		for (int i = 1;i <= n;i ++)
		{
			for (int j = 0;j < i;j ++)
			{
				int new_str = strength+j;
				int new_pow = power+i-j-1;
				for (int k = mana;k >= 0;k --)
				{
					if (f[i-1][j][k] <= 0) continue;
					if (new_str >= ms[i])
						if (f[i][j+1][k] < f[i-1][j][k]-max(2*ms[i]-new_str,0))
						{
							f[i][j+1][k] = f[i-1][j][k]-max(2*ms[i]-new_str,0);
							g[i][j+1][k] = 0;
						}
					if (new_pow >= mp[i] && k >= mm[i])
						if (f[i][j][k-mm[i]] < f[i-1][j][k])
						{
							f[i][j][k-mm[i]] = f[i-1][j][k];
							g[i][j][k-mm[i]] = 1;
						}
				}
			}
		}
		bool flag = 0;
		int idx = 0,res = 0;
		for (int i = 0;i <= n;i ++)
			for (int j = 0;j <= mana;j ++)
				if (f[n][i][j] > 0)
					flag = 1, idx = i, res = j;
		if (flag)
		{
			int tot = n;
			while (tot)
			{
				if (g[tot][idx][res])
				{
					ans[tot] = 'E';
					res += mm[tot];
					tot --;
				}
				else
				{
					ans[tot] = 'D';
					idx --;
					tot --;
				}
			}
			printf("%s\n",ans+1);
		} else printf("UNLUCKY\n");
  	}
  	return 0;
}

