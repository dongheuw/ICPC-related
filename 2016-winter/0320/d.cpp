#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int a[2][3];

int main()
{
	for (int i = 0;i < 2;i ++)
		for (int j = 0;j < 3;j ++)
			scanf("%d",&a[i][j]);
	sort(a[0],a[0]+3);
	sort(a[1],a[1]+3);
	bool ok = 1;
	for (int j = 0;j < 3;j ++)
		if (a[0][j] != a[1][j])
		{
			ok = 0;
			break;
		}
	if (a[0][0]*a[0][0] + a[0][1]*a[0][1] != a[0][2]*a[0][2]) ok = 0;
	puts(ok?"YES":"NO");
}
