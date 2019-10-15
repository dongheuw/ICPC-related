#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 100005;

int cur,last,p[maxn],len;
char s[maxn];

int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	while (~scanf("%s",s+1))
	{
		len = strlen(s+1);
		cur = last = 0;
		memset(p,0,sizeof p);
		fo(i,1,len)
		{
			if (s[i] == '[') cur = 0;
			else if (s[i] == ']') cur = last;
			else
			{
				p[i] = p[cur];
				p[cur] = i;
				if (cur == last) last = i;
				cur = i;
			}
		}
		for (int i = p[0];i != 0;i = p[i]) printf("%c",s[i]);
		printf("\n");
		memset(s,0,sizeof s);
	}
	return 0;
}
