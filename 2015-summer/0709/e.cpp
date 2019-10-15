#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 105;

int T,t,N,m,f[maxn][maxn][26];
int M[maxn],L[maxn],R[maxn],W[maxn];
char s[maxn];

int main()
{
	freopen("e.in","r",stdin);
	freopen("e.out","w",stdout);
	scanf("%d",&T);
	fo(cs,1,T)
	{
		scanf("%d%d",&N,&t);
		fo(i,1,N)
		{
			scanf(" %c %c %c %d",&M[i],&L[i],&R[i],&W[i]);
			L[i] -= 65, R[i] -= 65, M[i] -= 65;
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
					fo(mid,i,j-1)
						fo(p,1,N)
							f[i][j][M[p]] = min(f[i][j][M[p]],f[i][mid][L[p]] + f[mid+1][j][R[p]] + W[p]);
				}
			if (f[1][m][0] < (int)1e9) printf("POSSIBLE WITH %d DIAMONDS\n",f[1][m][0]+m);
			else printf("IMPOSSIBLE\n");
		}
	}
	return 0;
}
