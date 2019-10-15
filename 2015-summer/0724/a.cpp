#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 1005;
int T,n,m,a[maxn],b[maxn],c[maxn];

bool cmp1(int x,int y){return x > y;}
bool cmp2(int x,int y){return (x%10<y%10) || (x%10==y%10&&x<y);}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	for (scanf("%d",&T);T;T --)
	{
		scanf("%d%d",&n,&m);
		fo(i,0,n-1) scanf("%d",&a[i]);
		fo(i,0,m-1) scanf("%d",&b[i]);
		sort(a,a+n,cmp1);
		int x = 0;
		fo(i,1,n-1)
		{
			if (a[i] != a[i-1]) x ++;
			a[x] = a[i];
		}
		n = x + 1, x = 0;
		sort(b,b+m,cmp1);
		fo(i,1,m-1)
		{
			if (b[i] != b[i-1]) x ++;
			b[x] = b[i];
		}
		m = x + 1;
		int ans = 0;
		for (int i = 0,j = 0;i < n && j < m;)
		{
			int now = 0, k = i;
			while (i < n && j < m && a[i] == b[j])
				now ++, i ++, j ++;
			if (now > ans)
			{
				ans = now;
				for (int t = 0;k < i;k ++,t ++) c[t] = a[k];
			}
			if (a[i] > b[j]) i ++; else j ++;
		}
		if (ans == 0) printf("NONE\n");
		else
		{
			fo(i,0,ans-2) printf("%d ",c[i]);
			printf("%d\n",c[ans-1]);
			sort(c,c+ans,cmp2);
			fo(i,0,ans-2) printf("%d ",c[i]);
			printf("%d\n",c[ans-1]);
		}
	}
	return 0;
}
