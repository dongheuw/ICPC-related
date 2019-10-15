#include <set>
#include <map>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 15;
const int maxm = 1e6 + 15;
const int inf = 0x3f3f3f3f;
typedef long long ll;
const ll mod = 1e9 + 7;

struct Edge {
    int to, next;
} edge[maxm];

int ecnt, head[maxn];

ll quickPow(ll x, ll y) {
    ll res = 1;
    while(y) {
        if(y & 1) res = res * x % mod;
        y >>= 1; x = x * x % mod;
    }
    return res;
}

ll inv(ll x) {
    return quickPow(x, mod - 2);
}

void add(int u, int v) {
    edge[ecnt].to = v;
    edge[ecnt].next = head[u];
    head[u] = ecnt++;
}

ll w[maxn], ans[maxn], val[maxn], Sum;
int dfn[maxn], low[maxn], cnt, vis[maxn];

void init(int n) {
    Sum = cnt = ecnt = 0;
    memset(vis, 0, sizeof(int) * (n + 1));
    memset(dfn, 0, sizeof(int) * (n + 1));
    memset(head, -1, sizeof(int) * (n + 1));
}

void dfs(int u) {
    vis[u] = 1; val[u] = w[u];
    for(int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if(vis[v]) continue; dfs(v);
        val[u] = val[u] * val[v] % mod;     
    }
}

inline void add(ll &x, ll y) {
    x += y;
    if(x >= mod) 
        x -= mod;
}

ll tarjan(int fa, int u, int root) {
    ll res = w[u], sum = 0, pro = w[u];
    dfn[u] = low[u] = ++cnt; int chd = 0, fg = 0;
    for(int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if(!dfn[v]) {
            chd++; ll tmp = tarjan(u, v, root);         
            low[u] = min(low[u], low[v]);       
            if(!fa) add(sum, tmp);
            if(!fa && chd > 1) fg = 1;
            if(fa && low[v] >= dfn[u]) {
                add(sum, tmp);
                pro = pro * tmp % mod;
                fg = 1;
            }
            res = res * tmp % mod;
        }
        else if(v != fa)
            low[u] = min(low[u], dfn[v]);
    }
    if(!fg) {
        // 孤立点
        if(!fa and head[u] == -1) {ans[u] = (Sum - val[root] + mod) % mod; }
        else ans[u] = ((Sum - val[root] + mod) % mod + val[root] * inv(w[u]) % mod) % mod;
    }
    else {
        ll pre = val[root] * inv(pro) % mod;
        if(fa) add(sum, pre);
        ans[u] = (Sum - val[root] + mod) % mod;
        add(ans[u], sum);
    }
    return res;
}

int vec[maxn];

inline int read() {
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    int x = 0;
    while(isdigit(c)) {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x;
} 

int main() {
    freopen("f.in","r",stdin);
    freopen("f.out","w",stdout);
    int t; scanf("%d", &t);
    while(t--) {
        int n = read(), m = read(); init(n);
        for(int i = 1; i <= n; i++) w[i] = read();
        for(int i = 1; i <= m; i++) {
            int u = read(), v = read();
            add(u, v); add(v, u);
        }
        int tot = 0;
        for(int i = 1; i <= n; i++) {
            if(vis[i]) continue;
            vec[++tot] = i; dfs(i);
            add(Sum, val[i]);
        }
        for(int i = 1; i <= tot; i++)
            tarjan(0, vec[i], vec[i]);
        ll S = 0;
        for(int i = 1; i <= n; i++)
            add(S, ans[i] * i % mod);
        printf("%lld\n", S);
    }
    return 0;
}
