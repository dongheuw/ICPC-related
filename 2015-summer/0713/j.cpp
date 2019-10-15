#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

int N,t1,t2,t;

int main()
{
	freopen("j.in","r",stdin);
	freopen("j.out","w",stdout);
	scanf("%d%d%d",&N,&t1,&t2);
	for (;t/t1 + t/t2 < N;t ++);
	printf("%d %d\n",(t+t1-1)/t1+(t+t2-1)/t2,max((t+t1-1)/t1*t1,(t+t2-1)/t2*t2));
	return 0;
}
