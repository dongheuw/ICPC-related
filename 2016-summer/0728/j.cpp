#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 100010;
const int N = 1200010;
int t,n,f[maxn],a[maxn],T[N];

int Query(int i)
{
	i += maxn;
	int ret = 0;
	for (;i >= 1;i -= (i&(-i))) ret = max(ret,T[i]);
	return ret;
}

void Modify(int i,int x)
{
	i += maxn;
	for (;i < N;i += (i&(-i))) T[i] = max(T[i],x);
}

int main()
{
	freopen("j.in","r",stdin);
	freopen("j.out","w",stdout);
	scanf("%d",&t);
	for (int cas = 1;cas <= t;cas ++)
	{
		memset(T,255,sizeof T);
		memset(f,0,sizeof t);
		scanf("%d",&n);
		fo(i,1,n) scanf("%d",&a[i]);
		Modify(0,0);
		int cnt = 0, ans = 0;
		fo(i,1,n)
			if (a[i] == 0) cnt ++, ans ++;
			else
			{
				int cur = a[i] - cnt;
				f[i] = max(Query(cur-1)+cnt+1,1);
				Modify(cur,f[i]-cnt);
				ans = max(ans,f[i]);
			}
		printf("Case #%d: %d\n",cas,ans);
	}
	return 0;
}
