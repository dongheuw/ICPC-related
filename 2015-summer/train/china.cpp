#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 2005;

int N,a[maxn],k[maxn];
char s[maxn];

void div2()
{
	int ret = 0;
	fo(i,1,N)
	{
		ret = ret * 10 + a[i];
		k[i] = ret / 2;
		ret %= 2;
	}
	if (!k[1])
	{
		fo(i,2,N) k[i-1] = k[i];
		k[0] = N - 1;
	} else k[0] = N;
}

void dec1()
{
	a[a[0]] --;
	for (int i = a[0];i >= 1;i --)
	{
		if (a[i] >= 0) break;
		else a[i] += 10, a[i-1] --;
	}
	if (!a[1])
	{
		fo(i,2,a[0]) a[i-1] = a[i];
		a[0] --;
	}
}

int main()
{
	freopen("china.in","r",stdin);
	freopen("china.out","w",stdout);
	scanf("%s",s+1);
	N = strlen(s+1);
	fo(i,1,N) a[i] = s[i] - 48;
	a[0] = N;
	if (a[N] % 2 != 0)
	{
		dec1(), div2();
		fo(i,1,k[0]) printf("%d",k[i]);
	}
	else
	{
		div2();
		int t;
		if (N != 1) t = a[N] + a[N-1] * 10; else t = a[N];
		fo(i,0,k[0]) a[i] = k[i];
		if (t % 4 == 0) dec1();
		else dec1(), dec1();
		fo(i,1,a[0]) printf("%d",a[i]);
	}
	printf("\n");
	return 0;
}
