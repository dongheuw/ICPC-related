#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#define  fr(i,x,y) for(i=x;i<=y;++i)
typedef long long LL;
int T=5;
int n;
int Random(int x){return rand()%x;}
LL Make(int bit)
{
	int i;
	LL ret=0;
	fr(i,1,bit)ret=ret*10+Random(10);
	return ret;
}
int main()
{
	freopen("j.in","w",stdout);
	int i;
	srand(time(0));
	printf("%d\n",T);
	while(T--)
	{
		n=1000;
		printf("%d %lld\n",n,Make(18));
		fr(i,1,n)printf("%d%c",(int)Make(9)," \n"[i==n]);
		fr(i,2,n)printf("%d %d\n",Random(i-1)+1,i);
	}
}
