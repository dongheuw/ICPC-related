#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

int a,v1,v2;

int main()
{
	freopen("1010.in","r",stdin);
	freopen("1010.out","w",stdout);
    while (~scanf("%d%d%d",&a,&v1,&v2))
    {
    	if (!a) puts("0.00000");
		else if (v1 <= v2) puts("Infinity");
		else printf("%.5lf\n",(double) a * v1 / (v1 + v2) / (v1 - v2));
	}
	return 0;
}
