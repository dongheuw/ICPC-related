#include <bits/stdc++.h>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

int n,m;

int main()
{
	freopen("g.in","r",stdin);
	freopen("g.out","w",stdout);
	while (~scanf("%d%d",&m,&n))
	{
		/*int plus;
		if (m < 4) plus = -1;
		else plus = (m-1) / 4;
		if (n >= m+plus) puts("T");
		else puts("F");*/
		/*if (m < 4) puts(n>=m-1?"T":"F");
		else if (m % 4 == 0) puts(n>=m?"T":"F");
		else puts(n>m?"T":"F");*/
		long long s;
		if (m % 2 == 0) s = (long long)m/2*(long long)m/2;
		else s = (long long)m/2*(long long)(m/2+1);
		puts(n>=s?"T":"F");
	}
	return 0;
}
