#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
#define calc(a,b) (d[a] + d[b] - 2 * d[get_lca(a,b)])

using namespace std;

const int maxn = 200005;

typedef long long ll;

struct node
{
    int x[2];ll val;
}t[maxn * 3],glo[maxn];

ll d[maxn];
int lis[19][maxn * 2],ord[maxn],lg[maxn * 4],co;
int final[maxn],to[maxn * 2],nex[maxn * 2],cost[maxn * 2],tot;
int fa[maxn],dep[maxn],dfn[maxn],r[maxn],Ref[maxn],e[maxn][2],cnt,n;

void link(int u,int v,int c)
{
    to[++ tot] = v,nex[tot] = final[u],cost[tot] = c,final[u] = tot;
}

void dfs(int now,int pre)
{
    fa[now] = pre;
    dfn[Ref[++ cnt] = now] = cnt;
    dep[now] = dep[pre] + 1;
    ord[now] = ++ co;
    lis[0][co] = now;
    for(int i = final[now];i;i = nex[i])
        if (to[i] != pre)
        {
            int v = to[i];
            d[v] = d[now] + cost[i];
            dfs(v,now);
            ++ co;
            lis[0][co] = now;
        }
    r[Ref[++ cnt] = now] = cnt;
}

int cmp(const int &a,const int &b)
{
    return dep[a] > dep[b] ? b : a;
}

int get_lca(int a,int b)
{
    a = ord[a],b = ord[b];
    if (a > b) swap(a,b);
    int p = lg[b - a + 1];
    return cmp(lis[p][a],lis[p][b - (1 << p) + 1]);
}

void merge(const node &a,const node &b,node &c)
{
    if (a.val > b.val) c = a; else c = b;
    if (a.val == -1 || b.val == -1) return;
    for(int i = 0;i < 2;i ++)
        for(int j = 0;j < 2;j ++)
        {
            ll dis = calc(a.x[i],b.x[j]);
            if (dis > c.val) c.val = dis,c.x[0] = a.x[i],c.x[1] = b.x[j];
        }
}

void build(int l,int r,int jd)
{
    if (l == r) t[jd].x[0] = t[jd].x[1] = Ref[l]; else
    {
        int mid = l + r >> 1;
        build(l,mid,jd << 1),build(mid + 1,r,jd << 1 | 1);
        merge(t[jd << 1],t[jd << 1 | 1],t[jd]);
    }
}

void query(int l,int r,int i,int j,node &global,int jd)
{
    if (j < l || i > r) return;
    if (i <= l && r <= j)
    {
        node tmp;
        merge(global,t[jd],tmp);
        global = tmp;
        return;
    }
    int mid = l + r >> 1;
    query(l,mid,i,j,global,jd << 1),query(mid + 1,r,i,j,global,jd << 1 | 1);
}

void read(int &x)
{
    char c;
    while (c = getchar(),c < '0' || c > '9');
    x = c - 48;
    while (c = getchar(),c >= '0' && c <= '9') x = x * 10 + c - 48;
}

vector<int> in[maxn],out[maxn];

void work()
{
    tot = 0;
    cnt = 0;
    co = 0;
    scanf("%d", &n);
    for(int i = 1;i <= n;i ++) final[i] = 0;
    for(int i = 1;i < n;i ++)
    {
        int u,v,c;
        read(u),read(v),read(c);
        e[i][0] = u,e[i][1] = v;
        link(u,v,c),link(v,u,c);
    }
    dfs(1,0);
    for(int i = 1;i <= lg[co];i ++)
        for(int j = 1;j + (1 << i) - 1 <= co;j ++)
            lis[i][j] = cmp(lis[i - 1][j],lis[i - 1][j + (1 << (i - 1))]);
    build(1,cnt,1);
    int q;
    scanf("%d", &q);
    for(int i = 1;i <= q;i ++)
    {
        int k;
        scanf("%d", &k);
        static int lp[maxn],ava[maxn];
        set<int> po;
        po.clear();
        po.insert(1);
        int cn = 0;
        lp[++ cn] = r[1];
        glo[1].val = -1;
        for(int j = 1;j <= k;j ++)
        {
            int co;
            scanf("%d", &co);
            int u = e[co][0],v = e[co][1];
            if (fa[u] == v) swap(u,v);
            lp[++ cn] = dfn[v] - 1,lp[++ cn] = r[v];
            in[dfn[v] - 1].push_back(v),out[r[v]].push_back(v);
            ava[j] = v;
            glo[v].val = -1;
        }
        sort(lp + 1,lp + cn + 1);
        for(int j = 1;j <= cn;j ++)
        {
            int l = lp[j - 1] + 1,r = lp[j];
            if (l > r) continue;
            int bel = *po.rbegin();
            query(1,cnt,l,r,glo[bel],1);
            for(int k = 0;k < in[r].size();k ++) po.insert(in[r][k]);
            for(int k = 0;k < out[r].size();k ++) po.erase(out[r][k]);
        }
        ll ans = glo[1].val;
        for(int j = 1;j <= k;j ++) 
        {
            ans += glo[ava[j]].val;
            in[dfn[ava[j]] - 1].clear(),out[r[ava[j]]].clear();
        }
        printf("%lld\n", ans);
    }
}

int main()
{
    for(int i = 2;i <= 400000;i ++) lg[i] = lg[i / 2] + 1;
    work();
    return 0;
}
