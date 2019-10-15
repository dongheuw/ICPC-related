#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

typedef long long LL;

const int maxn = 2005;

int T,n,m,Q;
LL g[maxn][maxn],tfs[maxn];
int low[maxn],dfn[maxn],stack[maxn],instack[maxn],belong[maxn],vis[maxn],match[maxn],id[maxn];
int top,depth,tot;
vector<int> p[maxn],q[maxn];

void Merge()
{
    fo(i,0,tot-1) q[i].clear();
    fo(i,0,Q-1)
        fo(j,0,p[i].size()-1)
        {
            int t = p[i][j];
            if (belong[i] != belong[t]) q[belong[i]].push_back(belong[t]);
        }
}

void Tarjan(int s)
{
    low[s] = dfn[s] = ++ depth;
    stack[++top] = s;
    instack[s] = 1;
    fo(i,0,p[s].size()-1)
    {
        int t = p[s][i];
        if (dfn[t] == -1)
        {
            Tarjan(t);
            low[s] = min(low[t],low[s]);
        } else if(instack[t]) low[s] = min(dfn[t],low[s]);
    }
    if (dfn[s] == low[s])
    {
        int t;
        do{
            t = stack[top--];
            belong[t] = tot;
            instack[t] = 0;
        } while (s != t);
        tot ++;
    }
}

int dfs(int s)
{
    fo(i,0,q[s].size()-1)
    {
        int t = q[s][i];
        if (!vis[t])
        {
            vis[t] = 1;
            if (match[t] == -1 || dfs(match[t]))
            {
                match[t] = s;
                return 1;
            }
        }
    }
    return 0;
}
   
int Hungary()
{
    int cnt = 0;
    memset(match,-1,sizeof match);
    fo(i,0,tot-1)
    {
        memset(vis,0,sizeof(vis));
        cnt += dfs(i);
    }
    return tot - cnt - 1;
}

void Floyd()
{
    fo(k,0,n-1)
        fo(j,0,n-1)
            fo(i,0,n-1)
                if (g[j][k]+g[k][i] < g[j][i])
                    g[i][j] = g[j][i] = g[j][k] + g[k][i];
}

void Initfsalize()
{
    scanf("%d%d%d",&n,&m,&Q); 
    fo(i,0,n-1)
        fo(j,0,n-1)
            if (i == j) g[i][j]=0; else g[i][j] = (LL)(1)<<50;
    while (m --)
    {
        int s,t; LL v;
        scanf("%d%d%lld",&s,&t,&v);
        g[s][t] = g[t][s] = min(g[s][t],v);
    }
    Floyd();
    fo(i,0,Q-1) scanf("%d%lld",&id[i],&tfs[i]);
    fo(i,0,Q-1)
    {
        p[i].clear();
        fo(j,0,Q-1)
        {
            if (i == j) continue;
            if(tfs[i] <= tfs[j] && g[id[i]][id[j]] <= tfs[j]-tfs[i]) p[i].push_back(j);
        }
    }
}

void Work(int cs)
{
    memset(dfn,-1,sizeof dfn);
    top = depth = tot = 0;
    fo(i,0,Q-1) if (dfn[i] == -1) Tarjan(i);
    Merge();
    printf("Case %d: %d\n",cs,Hungary());
}

int main()
{
    freopen("j.in","r",stdin);
    freopen("j.out","w",stdout);
    scanf("%d",&T);
    fo(cs,1,T)
    {
        Initfsalize();
        Work(cs);
    }
}
