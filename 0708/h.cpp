#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 505;
int T,N,a[2][maxn];

int main()
{
	freopen("h.in","r",stdin);
	freopen("h.out","w",stdout);
	scanf("%d",&T);
	while (T --)
	{
		scanf("%d",&N);
		fo(i,1,N) scanf("%d",&a[1][i]);
		int x = 0;
		fo(t,1,4)
		{
			x ^= 1;
			fo(i,1,N-t) a[x^1][i] = a[x][i] - a[x][i+1]; 
		}
		bool yes = 1;
		fo(i,1,N-4) if (a[x^1][i] != 0) yes = 0;
		if (yes) printf("YES\n"); else printf("NO\n");
	}
	return 0;
}
