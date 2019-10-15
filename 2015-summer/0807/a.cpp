#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 100010;

int T,len,n,a[26];
char s[maxn],r[10],rd[10];

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	for (scanf("%d",&T);T;T --)
	{
		fo(i,0,25) a[i] = i;
		scanf("%s",s+1);
		len = strlen(s+1);
		scanf("%d",&n);
		fo(i,1,n)
		{
			scanf("%s",r);
			scanf("%s",rd);
			fo(j,0,25) if (a[j] == rd[0]-65) a[j] = r[0]-65;
		}
		fo(i,1,len)
		{
			if (a[i] == '_') printf("_");
			else printf("%c",a[s[i]-65]+65);
		}
		puts("");
	}
	return 0;
}
