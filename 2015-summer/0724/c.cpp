#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define inf ((~(0ULL))>>1) 

using namespace std;
typedef long long LL;

const int maxn = 1010;
const int maxm = 20010;

int T,p[maxn],n,m,Q,head[maxn],cnt,a[maxm],b[maxm];
LL ans[maxm],dis[maxn];

struct Edge
{
    int v,w,next;
}e[maxm*2];

void adde(int u,int v,int w)
{  
    e[cnt].v = v;
    e[cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt ++;
    e[cnt].v = u;
    e[cnt].w = w;
    e[cnt].next = head[v];
    head[v] = cnt ++;
}

bool vis[maxn];
void spfa(int u)
{
    queue<int> q;
    while (!q.empty()) q.pop();
    q.push(u);
    memset(vis,0,sizeof vis);
    fo(i,1,n) dis[i] = inf;
    dis[u] = 0; vis[u] = 1;
    while (!q.empty())
    {
        int x = q.front(); q.pop();
        vis[x] = 0;
        for (int i = head[x];i != -1;i = e[i].next)
        {
            int v = e[i].v;
            if (p[v] > p[u]) continue;
            if (dis[v] > dis[x] + e[i].w)
            {
                dis[v] = dis[x] + e[i].w;
                if (!vis[v])
                {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    fo(i,1,Q)
        if (dis[a[i]] != inf && dis[b[i]] != inf)
            ans[i] = min(ans[i],dis[a[i]]+dis[b[i]]+p[u]);
}  
int main()
{
    freopen("c.in","r",stdin);
    freopen("c.out","w",stdout);
    while (scanf("%d %d",&n,&m))
    {
        if (n == 0 && m == 0) break;
        fo(i,1,n) scanf("%d",&p[i]);
        memset(head,-1,sizeof head);  
        cnt = 0;
        fo(i,1,m)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            adde(u,v,w);
        }
        scanf("%d",&Q);
        fo(i,1,Q) scanf("%d%d",&a[i],&b[i]), ans[i] = inf;
        fo(i,1,n) spfa(i);
        fo(i,1,Q)
            if (ans[i] == inf) printf("-1\n");
            else printf("%lld\n",ans[i]);
        puts("");
    }
    return 0;
}

