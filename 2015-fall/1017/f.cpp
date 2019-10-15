#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define LL long long
using namespace std;

const int maxn = 1000005;
int t,n,ans,f[maxn],fac[maxn],pos[maxn];

inline void read(int &N)
{
    N = 0;
    char C; C = getchar();
    while (C < '0' || C > '9') C = getchar();
    while (C >= '0' && C <= '9') N = 10*N + C - 48, C = getchar();
}

int Last(int num,int i)
{
    int ret = -1;
    while (num > 1)
    {
        int p = fac[num];
        ret = max(ret,pos[p]);
        pos[p] = i;
        while (num % p == 0) num /= p;
    }
    return ret;
}

int main()
{
    for(LL i = 2;i <= maxn;i ++)
        if (fac[i] == 0)
        {
            fac[i] = i;
            for(LL j=i*i;j<=maxn;j+=i) if (fac[j] == 0) fac[j] = i;
        }
    read(t);
    while(t --)
    {
        memset(pos,-1,sizeof pos);
        read(n);
        int p = -1; ans = 0;
        for(int i = 0;i < n;i ++)
        {
            int x;
            read(x);
            p = max(p,Last(x,i));
            ans = max(ans,i-p);
        }
        if (ans < 2) ans = -1;
        printf("%d\n",ans);
    }
    return 0;
}
