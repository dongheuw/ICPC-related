#include <bits/stdc++.h>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

int M;

int main()
{
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);
	while (~scanf("%d",&M))
	{
		fo(i,1,M)
		{
			int b;
			scanf("%d",&b);
			int sum = 0, flag = 1;
			fo(j,1,b)
			{
				int x;
				scanf("%d",&x);
				if (x > 2*(b-1)) flag = 0;
				sum += x;
			}
			if (sum != (b-1)*b) flag = 0;
			puts(flag==1?"T":"F");
		}
	}
	return 0;
}
