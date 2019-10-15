#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

int n,p,q;
char a[200];

int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	scanf("%d%d%d",&n,&p,&q);
	scanf("%s",a+1);
	fo(i,0,100)
	{
		fo(j,0,100)
			if (i*p + j*q == n)
			{
				printf("%d\n",i+j);
				fo(k,1,i*p)
				{
					printf("%c",a[k]);
					if (k % p == 0) printf("\n");
				}
				fo(k,i*p+1,n)
				{
					printf("%c",a[k]);
					if ((k-i*p) % q == 0) printf("\n");
				}
				return 0;
			}
	}
	printf("-1\n");
	return 0;
}
