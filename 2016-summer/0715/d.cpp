#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 505;

bitset<maxn> link[35],flag;
int n,m,N,ans,ots;
bool blank[35],a[35][35];

void dfs(int x,int cnt)
{
    if (cnt+ots >= ans) return;
    if (x > N)
    {
        ans = min(ans,cnt+ots);
        return;
    }
    bool check = 1;
    fo(i,1,N) if (a[x][i] && blank[i]) check = 0;
    if (check)
    {
        blank[x] = 1;
        bitset<maxn> tmp = flag;
        flag |= link[x];
        ots = flag.count();
        dfs(x+1,cnt);
        flag = tmp;
        ots = flag.count();
        blank[x] = 0;
    }
    dfs(x+1,cnt+1);
}

int main()
{
    freopen("d.in","r",stdin);
    freopen("d.out","w",stdout);
    while (~scanf("%d%d",&n,&m))
    {
        N = min(30,n);
        fo(i,1,N) link[i].reset();
        memset(a,0,sizeof a);
        memset(blank,0,sizeof blank);
        fo(i,1,m)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            if (u > 30) link[v].set(u);
            else if (v > 30) link[u].set(v);
            else a[u][v] = a[v][u] = 1;
        }
        ots = 0, ans = 30;
        flag.reset();
        dfs(1,0);
        printf("%d\n",ans);
    }
    return 0;
}
