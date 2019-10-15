#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
LL a,b,ans,val;
LL Gcd(LL a,LL b)
{
	LL t;
	while(b)
	{
		t=a;
		a=b;
		b=t%b;
	}
	return a;
}
void Check(int x)
{
	LL _a,_b,v;
	if(a%x==0)_a=a;
	else _a=a+(x-a%x);
	_b=b+_a-a;
	v=_a/Gcd(_a,_b)*_b;
	if(v<val)val=v,ans=_a-a;
	else if(v==val&&_a-a<ans)val=v,ans=_a-a;
}
int main()
{
	int i,t;
	while(~scanf("%lld%lld",&a,&b))
	{
		if(a>b)swap(a,b);
		if(a==0)printf("0\n");
		else
		{
			t=b-a;
			val=a/Gcd(a,b)*b;
			ans=0;
			for(i=1;i*i<=t;i++)if(t%i==0)
			{
				Check(i);
				Check(t/i);
			}
			printf("%lld\n",ans);
		}
	}
}
close
