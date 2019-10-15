#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define eps 1e-4

using namespace std;

int T,N;

bool cmp(int x,int y)
{
	int xx = 0, yy = 0;
	for (;x % 10 == 0;x /= 10);
	for (;y % 10 == 0;y /= 10);
	for (int i = x;i;i /= 10) xx ++;
	for (int i = y;i;i /= 10) yy ++;
	xx *= 2; yy *= 2;
	if (x % 10 == 5) xx --;
	if (y % 10 == 5) yy --;
	return xx < yy;
}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d",&T);
	while (T --)
	{
		scanf("%d",&N);
		bool absurd = 0;
		int t = N, bs = 1, temp = 0;
		while (t % 10 == 0) t /= 10, bs *= 10;
		int low = int(0.95 * N + 0.99), hig = int(1.05 * N);
		if (low <= (t/10*10 + 5) * bs && (t/10*10 + 5) * bs <= hig) absurd = 1, temp = t/10*10 + 5;
		if (low <= ((t/10+1)*10 + 5) * bs && ((t/10+1)*10 + 5) * bs <= hig) absurd = 1, temp = (t/10+1)*10 + 5;
		if (low <= (t/10*10 - 5) * bs && (t/10*10 - 5) * bs <= hig) absurd = 1, temp = t/10*10 - 5;
		if (low <= (t/10*10) * bs && (t/10*10) * bs <= hig) absurd = 1, temp = t/10*10;
		if (low <= ((t/10+1)*10) * bs && ((t/10+1)*10) * bs <= hig) absurd = 1, temp = (t/10+1)*10;
		if (absurd == 1 && cmp(temp,t)) printf("absurd\n"); else printf("not absurd\n");
	}
	return 0;
}
