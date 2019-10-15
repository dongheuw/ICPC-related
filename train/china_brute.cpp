#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

int N;

int gcd(int x,int y)
{
	if (!y) return x;
	else return gcd(y,x%y);
}

int main()
{
	freopen("china.in","r",stdin);
	freopen("china.ans","w",stdout);
	scanf("%d",&N);
	for (int i = N/2;i >= 1;i --)
		if (gcd(i,N) == 1)
		{
			printf("%d\n",i);
			break;
		}
	return 0;
}
