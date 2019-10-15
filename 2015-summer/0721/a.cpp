#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

typedef long long LL;

const int maxdigit = 21;
const int maxsum = 2400;

int T;
LL digit[maxdigit],f[maxdigit][maxdigit][maxsum];

LL DP(LL p,int pivot,int pre,bool lim)
{
	if (pre < 0) return 0;
	if (p == -1) return (pre == 0);
	if (!lim && f[p][pivot][pre] != -1) return f[p][pivot][pre];
	LL ret = 0; int l = 9;
	if (lim) l = digit[p];
	fo(i,0,l) ret += DP(p-1,pivot,pre+(p-pivot)*i,lim && (i==l));
	if (!lim) f[p][pivot][pre] = ret;
	return ret;
}

LL Calc(LL x)
{
	int len = 0;
	while (x)
	{
		digit[len] = x % 10, x /= 10;
		len ++;
	}
	LL ret = 1 - len;
	fo(pivot,0,len-1) ret += DP(len-1,pivot,0,1);
	return ret;
} 

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	for (scanf("%d",&T);T;T --)
	{
		LL l,r;
		scanf("%lld%lld",&l,&r);
		memset(f,-1,sizeof f);
		printf("%lld\n",Calc(r)-Calc(l-1));
	}
	return 0;
}
