#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

const int maxn = 35;
const int dx[] = {0,0,-1,1};
const int dy[] = {-1,1,0,0};
int T,N,M,a[maxn][maxn],b[maxn][maxn],c[maxn][maxn];

void Update(int x,int y)
{
	a[x][y] = (a[x][y] + 2 * c[x][y]) % 3;
	fo(k,0,3)
	{
		int xx = x + dx[k], yy = y + dy[k];
		if (xx > 0 && xx <= N && yy > 0 && yy <= M)
			a[xx][yy] = (a[xx][yy] + c[x][y]) % 3;			
	}
}

int main()
{
	freopen("1004.in","r",stdin);
	freopen("1004.out","w",stdout);
	srand(time(0));
	for (scanf("%d",&T);T;T --)
	{
		scanf("%d%d",&N,&M);
		fo(i,1,N)
			fo(j,1,M) scanf("%d",&a[i][j]), b[i][j] = a[i][j];
		bool done = 0;
		while (1)
		{
			fo(i,1,N) fo(j,1,M) a[i][j] = b[i][j];
			memset(c,0,sizeof c);
			fo(i,1,N)
			{
				c[i][1] = rand() % 3;
				Update(i,1);
			}
			fo(j,2,M)
			{
				fo(i,1,N) c[i][j] = (3 - a[i][j-1]) % 3;
				fo(i,1,N) Update(i,j);
			}
			bool ok = 1;
			fo(i,1,N)
				if (a[i][M])
				{
					ok = 0;
					break;
				}
			if (ok)
			{
				done = 1;
				break;
			}
		}
		if (done)
		{
			int ans = 0;
			fo(i,1,N)
				fo(j,1,M) ans += c[i][j];
			printf("%d\n",ans);
			fo(i,1,N)
				fo(j,1,M)
					for (;c[i][j];c[i][j] --)
						printf("%d %d\n",i,j);
		}
	}
	return 0;
}
