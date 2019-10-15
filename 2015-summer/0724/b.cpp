#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define fo(i,a,b) for(int i = a;i <= b;i ++)

using namespace std;

typedef long long LL;

const int maxn = 50005;

int T,n,I,R,cnt,head[maxn],son[maxn];
LL dist[maxn],cost[maxn];

struct Edge
{
    int u,v,next;
    Edge(){};
    Edge(int _u,int _v,int _next){u = _u,v = _v,next = _next;}
}e[maxn*2];

void add(int u,int v)
{
    e[cnt] = Edge(u,v,head[u]);
    head[u] = cnt ++;
}

void dfs(int u,int pre)
{
    dist[u] = 0;
    son[u] = 1;
    for(int i = head[u];i != -1;i = e[i].next)
    {
        int v = e[i].v;
        if (v == pre) continue;
        dfs(v,u);
        son[u] += son[v], dist[u] += dist[v] + son[v];
    }
}

void dp(int u,int pre)
{
    if (u != 1) cost[u] = cost[pre]+n-son[u]-son[u];
    for(int i = head[u];i != -1;i = e[i].next)
    {
        int v = e[i].v;
        if (v == pre) continue;
        dp(v,u);
    }
}

int main()
{
    freopen("b.in","r",stdin);
    freopen("b.out","w",stdout);
    for (scanf("%d",&T);T;T --)
    {
        scanf("%d%d%d",&n,&I,&R);
        cnt = 0;
        memset(head,-1,sizeof head);
        fo(i,0,n-2)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            add(u,v), add(v,u);
        }
        dfs(1,0);
        memset(cost,0,sizeof cost);
        cost[1] = dist[1];
        dp(1,0);

        LL Min = cost[1];
        fo(i,2,n) Min = min(Min,cost[i]);
        cout << Min*I*I*R << endl;

        bool flag = 0;
        fo(i,1,n)
            if (cost[i] == Min)
            {
                if (!flag) flag = 1, printf("%d",i);
                else printf(" %d",i);
            }
        printf("\n\n");
    }
    return 0;
}
