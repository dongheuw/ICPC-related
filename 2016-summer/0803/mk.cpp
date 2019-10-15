#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

int main()
{
	freopen("h.in","w",stdout);
	int t = 15;
	srand(time(0));
	printf("%d\n",t);
	while (t --)
	{
		int n = 1000;
		int s = rand() % 1000 + 1;
		printf("%d %d\n",n,s);
		for (int i = 1;i <= n;i ++) printf("%d ",rand()%100 + 1);
		printf("\n");
	}
}
