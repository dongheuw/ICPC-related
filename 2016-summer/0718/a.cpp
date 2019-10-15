#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int  i = a;i <= b;i ++)

using namespace std;
int T,len;
char s[55],st[55];

bool Check(char t)
{
	fo(i,1,len) s[i] = st[i];
	fo(i,1,len) if (s[i] == t) return 0;
	fo(i,1,len) if (s[i] == '?') s[i] = t;
	int a[3], k = 0, pos = 0;
	a[0] = a[1] = a[2] = 0;
	int b[3];
	b[0] = b[1] = b[2] = 1;
	fo(i,1,len)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			if (a[k] == 0 && s[i] == '0' && (s[i+1] >= '0' && s[i+1] <= '9')) return 0;
			a[k] = a[k] * 10 + s[i] - 48;
		}
		else
		{
			if (i == 1)
			{
				b[0] = -1;
				continue;
			}
			if (!(s[i-1] >= '0' && s[i-1] <= '9'))
			{
				b[k] = -1;
				continue;
			}
			if (s[i] != '=') pos = i;
			k ++;
		}
	}
	fo(i,0,2) a[i] *= b[i];
	if (s[pos] == '+')
	{
		if (a[0] + a[1] == a[2]) return 1;
	} else
	if (s[pos] == '-')
	{
		if (a[0] - a[1] == a[2]) return 1;
	} else
	if (s[pos] == '*')
	{
		if ((long long)a[0] * (long long)a[1] == (long long)a[2]) return 1;
	}
	return 0;
}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	for (scanf("%d",&T);T;T --)
	{
		scanf("%s",s+1);
		len = strlen(s+1);
		fo(i,1,len) st[i] = s[i];
		bool ok = 0;
		fo(i,0,9)
			if (Check(i+48))
			{
				printf("%d\n",i);
				ok = 1;
				break;
			}
		if (!ok) printf("-1\n");
	}
	return 0;
}
