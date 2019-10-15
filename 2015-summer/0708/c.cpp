#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 100005;
int T,N,s0,s1;
int pass[2][maxn],dribble[2][maxn],f[2][maxn];

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	scanf("%d",&T);
	while (T --)
	{
		scanf("%d%d%d%d%d",&N,&f[0][1],&f[1][1],&s0,&s1);
		fo(i,1,N-1) scanf("%d",&pass[0][i]);
		fo(i,1,N-1) scanf("%d",&dribble[0][i]);
		fo(i,1,N-1) scanf("%d",&pass[1][i]);
		fo(i,1,N-1) scanf("%d",&dribble[1][i]);
		fo(i,2,N)
		{
			fo(j,0,1)
				f[j][i] = min(f[j][i-1]+dribble[j][i-1],f[j^1][i-1]+pass[j^1][i-1]);
		}
		printf("%d\n",min(f[0][N]+s0,f[1][N]+s1));
	}
	return 0;
}
