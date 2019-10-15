#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int T;
char s[20005];
pair<int,int> a[105];
bool r[105];

int main()
{
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	scanf("%d",&T);getchar();
	for (int t = 1;t <= T;t ++)
	{
		gets(s+1);
		int len = strlen(s+1);
		for (int i = 1;i <= len;i += 4)
		{
			int tmp = 0;
			for (int j = i;j < i+4;j ++)
				tmp += ((s[j] >= 'a' && s[j] <= 'z') || (s[j] >= 'A' && s[j] <= 'Z'));
			a[t].first += tmp * tmp * tmp;
		}
		a[t].second = t;
	}
	sort(a+1,a+1+T);
	for (int i = 1;i <= T/2;i ++) r[a[i].second] = 1;
	for (int i = 1;i <= T;i ++) puts(r[i]?"random":"block");
	return 0;
}
