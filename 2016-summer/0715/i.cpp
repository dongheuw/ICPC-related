
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <queue>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int INF = 0x7f7f7f7f;
const int maxn = 100005;

int n,m,head[maxn],tot;
long long a,b,dis[maxn];
set<int> link,tmp;

struct Edge
{
    int v,next;
}edge[maxn*10];

void Add(int u,int v)
{
    edge[tot].v = v;
    edge[tot].next = head[u];
    head[u] = tot ++;
}

void BFS()
{
    fo(i,0,n) dis[i] = INF;
    link.clear(), tmp.clear();
    fo(i,2,n) link.insert(i);
    queue<int> Q;
    while (!Q.empty()) Q.pop();
    Q.push(1); dis[1] = 0;
    while (!Q.empty())
    {
        int u = Q.front(); Q.pop();
        for (int i = head[u];i != -1;i = edge[i].next)
        {
            int v = edge[i].v;
            if (link.count(v) == 0) continue;
            link.erase(v), tmp.insert(v);
        }
        for (set<int>::iterator it = link.begin();it != link.end();it ++)
            Q.push(*it), dis[*it] = dis[u] + b;
        link.swap(tmp), tmp.clear();
    }
    printf("%lld\n",min(dis[n],a));
}

void SPFA()
{
    queue<int> Q;
    while (!Q.empty()) Q.pop();
    fo(i,0,n) dis[i] = INF;
    static bool inQ[maxn];
    memset(inQ,0,sizeof inQ);
    dis[1] = 0; Q.push(1);
    while (!Q.empty())
    {
        int u = Q.front(); Q.pop();
        inQ[u] = 0;
        for (int i = head[u];i != -1;i = edge[i].next)
        {
            int v = edge[i].v;
            if (dis[u] + a < dis[v])
            {
                dis[v] = dis[u] + a;
                if (!inQ[v]) inQ[v] = 1, Q.push(v);
            }
        }
    }
    printf("%lld\n",min(dis[n],b));
}

int main()
{
    freopen("i.in","r",stdin);
    freopen("i.out","w",stdout);
    while(~scanf("%d%d%lld%lld",&n,&m,&a,&b))
    {
        bool flag = 0;
        tot = 0;
        memset(head,255,sizeof head);
        fo(i,1,m)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            Add(u,v), Add(v,u);
            if ((u == 1 && v == n) || (u == n && v == 1)) flag = 1;
        }
        if (flag) BFS(); else SPFA();
    }
    return 0;
}
