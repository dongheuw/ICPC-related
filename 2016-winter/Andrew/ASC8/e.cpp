#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

typedef long long LL;
LL a,m,fac;

int Phi(int n)
{
    int m = floor(sqrt(n+0.5));
    int ret = n;
    fo(i,2,m)
    {
        if (n % i == 0) ret = ret/i*(i-1);
        while (n % i == 0) n /= i;
    }
    if (n > 1) ret = ret/n*(n-1);
    return ret;
}

LL Mul(LL a,LL b,LL mod)
{
    LL ret = 0;
    while (b > 0)
    {
        if (b & 1) ret = (ret+a)%mod;
        b >>= 1;
        a = (a+a)%mod;
    }
    return ret;
}

LL Pow(LL a,LL b,LL mod)
{
    LL ret = 1;
    while (b > 0)
    {
        if (b & 1) ret = Mul(ret,a,mod);
        b >>= 1;
        a = Mul(a,a,mod);
    }
    return ret;
}

LL Solve(LL a,LL mod)
{
    if (mod == 1) return 0;
    LL t = Phi(mod);
    return Pow(a,t,mod)%mod * Pow(a,Solve(a,t),mod)%mod;
}

int main()
{
    for (int t = 1;scanf("%lld %lld",&a,&m) != EOF;t ++)
    {
        if (t > 1) puts("");
        fac = 1;
        fo(i,2,m) fac *= i;
        printf("%lld\n",Solve(a,fac));
    }
    return 0;
}
