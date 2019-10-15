#include <cstdio>
#include <cstring>
#include <ctime>
#include <cstdlib>
#define  fr(i,x,y) for(i=x;i<=y;++i)
int T=5;
int n,m;
int Random(int x){return rand()%x;}
int main()
{
	freopen("h.in","w",stdout);
	srand(time(0));
	int i,l,r;
	printf("%d\n",T);
	while(T--)
	{
		n=100000;//=Random(10)+1;
		printf("%d\n",n);
		fr(i,1,n)printf("%d%c",Random(100000)+1," \n"[i==n]);
		m=100000;//=Random(10)+1;
		printf("%d\n",m);
		while(m--)
		{
			l=Random(n)+1;
			r=Random(n)+1;
			if(l>r)l^=r^=l^=r;
			printf("%d %d\n",l,r);
		}
	}
}
