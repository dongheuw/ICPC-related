
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <queue>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

typedef long long LL;
const int INF = 1e9+7;
const int maxn = 100100;

int n,m;
LL a,b,dis[maxn];
set<int> st,ts;

int head[maxn],tot;

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

void BFS()
{
    fo(i,0,n) dis[i] = INF;
    st.clear(), ts.clear();
    fo(i,2,n) st.insert(i);
    queue<int> Q;
    while (!Q.empty()) Q.pop();
    Q.push(1); dis[1] = 0;
    while (!Q.empty())
    {
        int u = Q.front(); Q.pop();
        for (int i = head[u];i != -1;i = edge[i].next)
        {
            int v = edge[i].v;
            if (st.count(v) == 0) continue;
            st.erase(v), ts.insert(v);
        }
        for (set<int>::iterator it = st.begin();it != st.end();it ++)
            Q.push(*it), dis[*it] = dis[u] + b;
        st.swap(ts), ts.clear();
    }
    printf("%lld\n",min(dis[n],a));
}

int main()
{
    while(~scanf("%d%d%lld%lld",&n,&m,&a,&b))
    {
        memset(head,255,sizeof head);
        tot = 0;
        bool flag = 0;
        for(int i=0;i<m;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            if(u>v)swap(u,v);
            Add(u,v), Add(v,u);
            if (u == 1 && v == n) flag = 1;
        }
        if (flag) BFS(); else SPFA();
    }
    return 0;
}
