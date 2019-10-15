#include<cstdio>
#inculde<cstring>
#include<algorith>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

int T,N;

int main()
{
	scanf("%d",&T);
	while (T --)
	{
		scanf("%d",&N);
		bool absurd = 0;
		int t = N, dig = 0, v1, bs = 0;
		while (t % 10 == 0) t /= 10, bs ++;
		for (int x = t;x;x /= 10) dig ++;
		double low = 0.95*N/bs, hig = 1.05*N/bs; //something wrong
		if (t % 10 == 5)
		{
			v1 = 2 * dig - 1;
			int st = t - (t % 10);
			if (low < st) absurd = 1;
			st = (t/10 + 1) * 10;
			if (hig > st) absurd = 1;
		} else
		{
			int st = t - (t % 10) + 5;
			v1 = 2 * dig;
			if (low < st && st < t) absurd = 1;
			if (t < st && st < hig) absurd = 1;
		}
		if (absurd == 1) printf("absurd\n"); else printf("not absurd\n");
	}
}
