#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

long long n,m,k;

int main()
{
    freopen("e.in","r",stdin);
    freopen("e.out","w",stdout);
    while (~scanf("%lld%lld%lld",&n,&m,&k))
    {
        long long ans = 0;
        for (long long i = 1;i <= n;i ++)
        {
            if (k-2*i <= 0) break;
            long long  lim = min((k-2*i)/2,m);
            ans += (n-i+1)*(lim*(m+1)-(lim+1)*lim/2);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
