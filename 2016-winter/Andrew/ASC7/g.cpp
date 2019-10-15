#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

const int r[][6] = {{1,0,0,0,0,1},{0,0,-1,-1,0,0}};
const int c[][6] = {{-1,1,1,-1,-1,-1},{1,1,1,1,-1,-1}};

int n,t;
char a[1005][1005];

int main()
{
	freopen("g.in","r",stdin);
	freopen("g.out","w",stdout);
	scanf("%d",&n);
	while (n)
	{
		memset(a,0,sizeof a);
		fo(i,0,n-1) scanf("%s",a[n-1-i]+1);
		bool ans = 0;
		fo(p,0,5)
		{
			bool flag = 1;
			fo(i,0,n-1)
				fo(j,1,(n-i)*2-1)
					if (a[i][j] == '1' && a[i+r[j%2][p]][j+c[j%2][p]] == '0')
					{
						flag = 0;
						break;
					}
			if (flag)
			{
				ans = 1;
				break;
			}
		}
		printf("Puzzle %d\n",++t);
		puts(ans?"Parts can be separated":"Parts cannot be separated");
		scanf("%d",&n);
	}
	return 0;
}
