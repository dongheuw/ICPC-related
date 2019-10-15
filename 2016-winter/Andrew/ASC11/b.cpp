#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int m,n;
unsigned f[9][1<<18],ans[9][9];

int main()
{
	for (int n = 1;n <= 8;n ++)
	{
		int m = n + 1, mm = (1 << m) - 1;
		memset(f,0,sizeof f);
		f[1][(1<<(m*2))-2] = 1;
		for (int i = 1;i <= 8;i ++)
		{
			for (int j = 0;j < (1<<(m*2));j ++)
			{
				if (f[i][j] == 0) continue;
				int a = j >> m;
				int b = j & mm;
				if (b != 0 && b == (b&((a&(a<<1))|(a&(b<<1))|((a<<1)&(b>>1)))))
					ans[n][i] += f[i][j];
				if (i == 8) continue;
				int s = (i&1)?(1<<m):(1<<n);
				for (int c = 1;c < s;c ++)
					if (b == (b&((a&(a<<1))|(a&c&~(c<<1))|((a<<1)&(c<<1)&~c)|(a&(b<<1))|((a<<1)&(b>>1)))))
					{
						if (i&1) f[i+1][(b<<n)^c] += f[i][j];
						else f[i+1][(b<<m)^(c<<1)] += f[i][j];
					}
			}
		}
	}
	while (scanf("%d%d",&m,&n) != EOF) printf("%u\n",ans[m][n]);
	return 0;
}
