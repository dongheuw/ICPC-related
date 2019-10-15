#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<string>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

int T,N,d;
string s;
int cnt[26];

int main()
{
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);
	scanf("%d\n",&T);
	while (T --)
	{
		getline(cin,s);
		N = s.size();
		memset(cnt,0,sizeof (cnt));
		fo(i,0,N-1) cnt[s[i]-65] ++;
		int big = 0, c = 0;
		char maxchar;
		fo(i,0,25) if (cnt[i] > big) big = cnt[i], maxchar = 65+i;
		fo(i,0,25) if (cnt[i] == big) c ++;
		if (c == 1)
		{
			d = (26+maxchar-'E')%26;
			printf("%d ",d);
			fo(i,0,N-1)
				if (s[i] != ' ') putchar(65+(s[i]-65-d+26)%26);
				else putchar(' ');
			puts("");
		} else puts("NOT POSSIBLE");
	}
	return 0;
}
