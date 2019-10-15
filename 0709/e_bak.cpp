#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 105;

int T,t,N,m,f[maxn][maxn][26];
int W[35][35][3];
char s[maxn];

int main()
{
	freopen("e.in","r",stdin);
	freopen("e.out","w",stdout);
	scanf("%d",&T);
	fo(cs,1,T)
	{
		scanf("%d%d",&N,&t);
		fo(i,0,25) W[i][0][0] = 0;
		fo(i,1,N)
		{
			char x,y,z;
			int w;
			scanf(" %c %c %c %d",&x,&y,&z,&w);
			x -= 65, y -= 65, z -= 65;
			W[x][0][0] ++;
			W[x][W[x][0][0]][0] = y;
			W[x][W[x][0][0]][1] = z;
			W[x][W[x][0][0]][2] = w;
		}
		printf("CASE #%d\n",cs);
		while (t --)
		{
			scanf("%d %s",&m,s+1);
			fo(i,1,m) s[i] -= 97;
			fo(i,1,m) fo(j,1,m) fo(k,0,25) f[i][j][k] = (int)1e9;
			fo(i,1,m) f[i][i][s[i]] = 0;
			fo(l,1,m)
				fo(i,1,m-l+1)
				{
					int j = i + l - 1;
					fo(k,0,25)
						fo(p,1,W[k][0][0])
							fo(mid,i,j-1)
								f[i][j][k] = min(f[i][j][k],f[i][mid][W[k][p][0]] + f[mid+1][j][W[k][p][1]] + W[k][p][2]);
				}
			if (f[1][m][0] < (int)1e9) printf("POSSIBLE WITH %d DIAMONDS\n",f[1][m][0]+m);
			else printf("IMPOSSIBLE\n");
		}
	}
	return 0;
}
