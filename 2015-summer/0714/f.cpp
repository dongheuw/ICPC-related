#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

const int maxn = 105;

int T,cas,N,K,f[maxn][maxn][2];

int main()
{
    freopen("f.in","r",stdin);
    freopen("f.out","w",stdout);
    f[1][0][0] = f[1][0][1] = 1;
    fo(i,2,100)
    {
        f[i][0][0] = f[i-1][0][0] + f[i-1][0][1];
        f[i][0][1] = f[i-1][0][0];
        fo(j,1,i-1)
        {
            f[i][j][0] = f[i-1][j][0] + f[i-1][j][1];
            f[i][j][1] = f[i-1][j][0] + f[i-1][j-1][1];
        }
    }
    for (scanf("%d",&T);T;T --)
    {
        scanf("%d%d%d",&cas,&N,&K);
        printf("%d %d\n",cas,f[N][K][0]+f[N][K][1]);
    }
    return 0;
}
