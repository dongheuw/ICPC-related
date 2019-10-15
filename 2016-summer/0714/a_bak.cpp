#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;
int cs,n,m,t,p,q;
char a[1005][1005];
long long row[1005][1005],col[1005][1005],R[55],C[55];
long long hr[1005][1005],hc[1005][1005],rh,ch;

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d%d%d%d",&n,&m,&t,&p,&q);
	while (n+m+t+p+q > 0)
	{
		fo(i,1,n) scanf("%s",a[i]+1);
		fo(i,1,n)
			fo(j,1,n-q+1)
			{
				row[i][j] = 0;
				fo(k,j,j+q-1)
					if (a[i][k] == '0') row[i][j] += (1LL<<(k-j));
			}
		fo(i,1,n-p+1)
			fo(j,1,n)
			{
				col[i][j] = 0;
				fo(k,i,i+p-1)
					if (a[k][j] == '0') col[i][j] += (1LL<<(k-i));
			}
		fo(i,1,n-p+1)
			fo(j,1,n-q+1)
			{
				hr[i][j] = 0;
				fo(k,j,j+q-1) hr[i][j] += col[i][k] * (1LL<<(k-j));
			}
		fo(i,1,n-p+1)
			fo(j,1,n-q+1)
			{
				hc[i][j] = 0;
				fo(k,i,i+p-1) hc[i][j] += row[k][j] * (1LL<<(k-i));
			}
		int ans = 0;
		fo(c,1,t)
		{
			fo(i,1,p) scanf("%s",a[i]+1);
			memset(R,0,sizeof R);
			memset(C,0,sizeof C);
			fo(i,1,p)
				fo(k,1,q)
					if (a[i][k] == '0') R[i] += (1LL<<(k-1));
			fo(j,1,q)
				fo(k,1,p)
					if (a[k][j] == '0') C[j] += (1LL<<(k-1));
			rh = ch = 0;
			fo(i,1,q) rh += C[i] * (1LL<<(i-1));
			fo(i,1,p) ch += R[i] * (1LL<<(i-1));
			bool Match = 0;
			fo(i,1,n-p+1)
			{
				fo(j,1,n-q+1)
					if (hr[i][j] == rh && hc[i][j] == ch)
					{
						Match = 1;
						break;
					}
				if (Match) break;
			}
			if (Match) ans ++;
		}
		printf("Case %d: %d\n",++cs,ans);
		scanf("%d%d%d%d%d",&n,&m,&t,&p,&q);
	}
	return 0;
}
