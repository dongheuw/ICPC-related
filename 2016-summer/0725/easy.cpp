#include <cstdio>
#include <cstring>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

int n,k,cnt[45],a[45][45],pos[45];

int main()
{
	freopen("easy.in","r",stdin);
	freopen("easy.out","w",stdout);
	scanf("%d%d",&n,&k);
	fo(i,0,n-1)
	{
		scanf("%d",&cnt[i]);
		fo(j,0,cnt[i]-1) scanf("%d",&a[i][j]);
		pos[i] = 0;
	}
	int ans = 0, i = 0;
	fo(p,0,999)
	{
		if (k == 0) break;
		int x = (pos[i] < cnt[i] ? a[i][pos[i]++] : 50);
		if (x >= ans) ans += x, k --;
		i = (i + 1) % n;
	}
	printf("%d\n",ans+k*50);
	return 0;
}
