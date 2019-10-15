#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int T,cas;
char s[1005];

int main()
{
	freopen("e.in","r",stdin);
	freopen("e.out","w",stdout);
	scanf("%d",&T);
	while (T --)
	{
		scanf("%d %s",&cas,s);
		if (next_permutation(s,s+strlen(s))) printf("%d %s\n",cas,s);
		else printf("%d BIGGEST\n",cas);
	}
	return 0;
}
