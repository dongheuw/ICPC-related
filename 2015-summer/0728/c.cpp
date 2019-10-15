#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

int T,n,m,len[55],c[55][55];
char a[55][15];

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	for (scanf("%d",&T);T;T --)
	{
		scanf("%d%d",&n,&m);
		fo(i,1,n) scanf("%s",a[i]+1), len[i] = strlen(a[i]+1);
		fo(i,1,n)
			fo(j,1,n)
			{
				if (i == j) continue;
				int l = min(len[i],len[j]);
				bool checked = 0;
				fo(k,2,l)
				{
					bool ok = 1;
					for (int x = 1, y = len[j]-k+1;x <= l;x ++, y --)
						if (a[i][x] != a[j][y])
						{
							ok = 0;
							break;
						}
					if (ok)
					{
						checked = 1;
						break;
					}
				}
				if (checked) c[i][j] = 1; else c[i][j] = 0;
			}
		
	}
	return 0;
}
