#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 1005;
const int mod = 1000000007;

int n,f[maxn][maxn],sum[maxn][maxn];
char s[maxn];

int main()
{
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	while (scanf("%s",s+2) != EOF)
	{
		memset(f,0,sizeof f);
		memset(sum,0,sizeof sum);
		n = strlen(s+2);
		f[1][1] = sum[1][1] = 1;
		fo(i,2,n+1)
			fo(j,1,i)
			{
				if (s[i] == 'I' || s[i] == '?') f[i][j] = (f[i][j] + sum[i-1][j-1]) % mod;
				if (s[i] == 'D' || s[i] == '?')
				{
					int temp = ((sum[i-1][i-1]-sum[i-1][j-1])%mod+mod) % mod;
					f[i][j] = (f[i][j] + temp) % mod;
				}
				sum[i][j] = (sum[i][j-1] + f[i][j]) % mod;
			}
		printf("%d\n",sum[n+1][n+1]);
	}
	return 0;
}
