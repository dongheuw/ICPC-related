#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define fd(i,a,b) for (int i = a;i >= b;i --)
using namespace std;

const int maxn = 100010;

char s[maxn];
int n,cs,sa[maxn],height[maxn],Rank[maxn],tank[maxn],tmp[maxn];
int logn[maxn],f[20][maxn];

int LCP(int a,int b)
{
    a = Rank[a], b = Rank[b];
    if(a > b) swap(a,b);
    a ++;
    int t = logn[b - a + 1];
    return min(f[t][a],f[t][b-(1<<t)+1]);
}

void Solve()
{
    int ans = 0,ansL = 1,ansR = 1;
    fo(i,1,n-1) if(s[i] < s[ans]) ans = i;
    fo(i,1,n-1)
    {
        for (int j = 0;j+i < n-1;j += i)
        {
            int t = LCP(j,j+i), p = 0;
            if (t % i)
            {
                p = i - t % i;
                if (j < p) p = 0;
                t = max(t,LCP(j-p,j+i-p));
            }
            if (t/i+1 > ansR || (t/i+1 == ansR && Rank[j] < Rank[ans]))
            {
                ans = j - p;
                ansR = t / i + 1;
                ansL = ansR * i;
            }
        }
    }
    fo(i,0,n-2)
        if (LCP(i,i+ansL/ansR) >= ansL-ansL/ansR && Rank[i] < Rank[ans])
            ans = i;
    printf("Case %d: ",++cs);
    fo(i,ans,ans+ansL-1) putchar(s[i]);
    puts("");
}

void Build_SA()
{
    memset(tank,0,128*4);
    fo(i,0,n-1) tank[Rank[i] = s[i]] ++;
    fo(i,1,127) tank[i] += tank[i-1];
    fo(i,0,n-1) sa[--tank[Rank[i]]] = i;
    for (int k = 1;k < n;k <<= 1)
    {
        fo(i,0,n-1)
        {
            int j = sa[i] - k;
            if (j < 0) j += n;
            tmp[tank[Rank[j]]++] = j;
        }
        int j = tank[0] = sa[tmp[0]] = 0;
        fo(i,1,n-1)
        {
            if(Rank[tmp[i]] != Rank[tmp[i-1]] || Rank[tmp[i]+k] != Rank[tmp[i-1]+k]) tank[++j] = i;
            sa[tmp[i]] = j;
        }
        memcpy(Rank,sa,n*4);
        memcpy(sa,tmp,n*4);
    }
}

void Calc_height()
{
    for(int i = 0,k = 0;i < n;height[Rank[i++]] = k)
    {
        if (k > 0) k --;
        int j = sa[Rank[i] - 1];
        while (s[i + k] == s[j + k]) k ++;
    }
    logn[0] = -1;
    fo(i,1,n) logn[i] = (i&(i-1))==0 ? logn[i-1]+1 : logn[i-1];
    fo(i,1,n) f[0][i] = height[i];
    fo(i,1,logn[n])
        fo(j,1,n-(1<<i)+1)
            f[i][j] = min(f[i-1][j],f[i-1][j+(1<<(i-1))]);
}

int main()
{
    freopen("d.in","r",stdin);
    freopen("d.out","w",stdout);
    while (~scanf("%s",s))
    {
        if (s[0] == '#') break;
        n = strlen(s)+1;
        Build_SA();
        Calc_height();
        Solve();
    }
}
