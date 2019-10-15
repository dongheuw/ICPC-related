#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

const int maxn = 1005;
const int mod = (int)1e9 + 7;
int T,n,s,a[maxn],f[maxn][maxn][16];

inline void read(int &x)
{
    static char ch;
    x = 0;
    do ch = getchar(); while (ch < '0' || ch > '9');
    do x = x * 10 + ch - 48, ch = getchar(); while (ch >= '0' && ch <= '9');
}

inline int inc(int x,int y)
{
    return (x + y) - (x + y >= mod ? mod : 0);
}

int main()
{
    //freopen("h.in","r",stdin);
    //freopen("h.out","w",stdout);
    for (scanf("%d",&T);T;T --)
    {
        read(n); read(s);
        fo(i,1,n) read(a[i]);
        f[0][0][0] = 1;
        fo(i,1,n)
            fo(j,0,s)
                fo(k,0,15)
                {
                    f[i][j][k] = f[i-1][j][k];
                    if (j >= a[i])
                    {
                        /*if (f[i][j][k] + f[i-1][j-a[i]][k] >= mod)
                            f[i][j][k] = f[i][j][k] + f[i-1][j-a[i]][k] - mod;
                        else f[i][j][k] = f[i][j][k] + f[i-1][j-a[i]][k];*/
                        f[i][j][k] = inc(f[i][j][k],f[i-1][j-a[i]][k]);
                    }
                    if (j >= a[i] && (k & 1))
                    {
                        /*if (f[i][j][k] + f[i-1][j-a[i]][k^1] >= mod)
                            f[i][j][k] = f[i][j][k] + f[i-1][j-a[i]][k^1] - mod;
                        else f[i][j][k] = f[i][j][k] + f[i-1][j-a[i]][k^1];*/
                        f[i][j][k] = inc(f[i][j][k],f[i-1][j-a[i]][k^1]);   
                    }
                    if (j >= a[i] && (k & 2))
                    {
                        /*if (f[i][j][k] + f[i-1][j-a[i]][k^2] >= mod)
                            f[i][j][k] = f[i][j][k] + f[i-1][j-a[i]][k^2] - mod;
                        else f[i][j][k] = f[i][j][k] + f[i-1][j-a[i]][k^2];*/
                        f[i][j][k] = inc(f[i][j][k],f[i-1][j-a[i]][k^2]);
                    }
                    if (k & 4)
                    {
                        /*if (f[i][j][k] + f[i-1][j][k^4] >= mod)
                            f[i][j][k] = f[i][j][k] + f[i-1][j][k^4] - mod;
                        else f[i][j][k] = f[i][j][k] + f[i-1][j][k^4];*/
                        f[i][j][k] = inc(f[i][j][k],f[i-1][j][k^4]);
                    }
                    if (k & 8)
                    {
                        /*if (f[i][j][k] + f[i-1][j][k^8] >= mod)
                            f[i][j][k] = f[i][j][k] + f[i-1][j][k^8] - mod;
                        else f[i][j][k] = f[i][j][k] + f[i-1][j][k^8];*/
                        f[i][j][k] = inc(f[i][j][k],f[i-1][j][k^8]);
                    }
                }
        int ans = 0;
        fo(i,1,s)
            if (ans + f[n][i][15] >= mod) ans = ans + f[n][i][15] - mod;
            else ans = ans + f[n][i][15];
        printf("%d\n",ans);
    }
    return 0;
}
