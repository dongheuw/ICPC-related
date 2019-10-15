#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 10005;
int cs,n,m,pre[maxn];
vector<int> a[maxn];
bool vis[maxn];

int main()
{
    freopen("h.in","r",stdin);
    freopen("h.out","w",stdout);
    scanf("%d%d",&n,&m);
    while (n+m > 0)
    {
        fo(i,1,n) a[i].clear();
        fo(i,1,m)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            a[u].push_back(v), a[v].push_back(u);
        }
        queue <int> Q;
        while (!Q.empty()) Q.pop();
        memset(vis,0,sizeof vis);
        memset(pre,0,sizeof pre);
        Q.push(vis[1] = 1);
        int ans = 0;
        while (!Q.empty())
        {
            int x = Q.front();
            Q.pop();
            for (unsigned i = 0;i < a[x].size();i ++) pre[a[x][i]] = x;
            fo(i,1,n)
                if (!vis[i] && pre[i] != x)
                {
                    vis[i] = 1;
                    Q.push(i);
                    ans ++;
                }
        }
        printf("Case %d: %d\n",++cs,ans);
        scanf("%d%d",&n,&m);
    }
    return 0;
}
