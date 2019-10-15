#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 25;
const int maxp = 1005;
int T,n,m,p,dmg[maxn];
long long fac[maxn],f[maxn][maxn][maxp],sum[maxn],P,Q;

void dfs(int a,int b,long long k)
{
    if (a+1 == b || a+b == n+m)
    {
        P -= k * fac[b] * fac[n+m-a-b] * sum[b];
        return;
    }
    if (a < n) dfs(a+1,b,k*(n-a));
    if (b < m) dfs(a,b+1,k);
}

long long gcd(long long a,long long b)
{
    if (!b) return a; else return gcd(b,a%b);
}

int main()
{
    //freopen("h.in","r",stdin);
    //freopen("h.out","w",stdout);
    fac[0] = 1;
    fo(i,1,20) fac[i] = fac[i-1] * i;
    for (scanf("%d",&T);T;T --)
    {
        scanf("%d%d%d",&p,&n,&m);
        int tot = 0;
        fo(i,1,m) scanf("%d",&dmg[i]), tot += dmg[i];
        if (tot < p)
        {
            puts("0/1");
            continue;
        }
        memset(f,0,sizeof f);
        f[0][0][0] = 1;
        fo(i,1,m)
            fo(j,0,i-1)
                fo(k,0,p)
                {
                    f[i][j][k] += f[i-1][j][k];
                    f[i][j+1][min(p,k+dmg[i])] += f[i-1][j][k];
                }
        sum[0] = 1;
        fo(j,1,m)
        {
            sum[j] = 0;
            fo(k,0,p-1) sum[j] += f[m][j][k];
        }
        P = Q = fac[n+m];        
        dfs(0,0,1);
        long long d = gcd(P,Q);
        printf("%I64d/%I64d\n",P/d,Q/d);
    }
    return 0;
}
