#include <cstdio>
#include <cstring>
#include <algorithm>

int a,b;

int main()
{
	scanf("%d%d",&a,&b);
	if (a < b) printf("-1\n");
	else printf("%.9lf\n",(a+b)/(2.0*((a+b)/(2*b))));
	return 0;
}
