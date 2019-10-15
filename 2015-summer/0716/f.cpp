#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

typedef long long LL;

const int maxn = 2205;
const int maxm = 2200005;
const LL inf = 0x7fffffffffffffffll;

int T,n,m,tot,source,sink,lab[maxn],list[maxn];
int a[maxn],b[maxm],c[maxm];
LL d[maxm],maxflow;

inline void read(int &x)
{
    static char ch;
    x = 0;
    do ch = getchar(); while (ch < '0' || ch > '9');
    do x = x * 10 + ch - 48, ch = getchar(); while (ch >= '0' && ch <= '9');
}

void insert(int x,int y,LL z)
{
    tot ++;
    b[tot] = y;
    d[tot] = z;
    c[tot] = a[x];
    a[x] = tot;
}

void Initialize()
{
    read(n); read(m);
    source = 0; sink = n-1;
    tot = 1;
    fo(i,0,n) a[i] = 0;
    fo(i,1,m)
    {
        int x,y,z,d;
        read(x), read(y), read(z), read(d);
        insert(x,y,(LL)z*maxm+1), insert(y,x,0);
        if (d) insert(y,x,(LL)z*maxm+1), insert(x,y,0);
    }
}

inline bool bfs()
{
    int st,en;
    list[st=en=1] = source;
    memset(lab,255,sizeof lab);
    lab[source] = 0;
    while (st <= en)
    {
        int x = list[st];
        for(int i = a[x];i;i = c[i])
            if (d[i] && lab[b[i]] == -1)
            {
                lab[b[i]] = lab[x] + 1;
                list[++en] = b[i];  
            }
        st ++;
    }
    return lab[sink] > -1;
}

inline LL dfs(int x,LL flow)
{
    if (x == sink) return flow;
    LL ret = 0;
    for (int i = a[x];i;i = c[i])
        if (d[i] && lab[b[i]] == lab[x] + 1)
        {
            LL now = dfs(b[i],min(flow,d[i]));
            d[i] -= now;
            d[i^1] += now;
            flow -= now;
            ret += now;
            if (!flow) return ret;
        }
    lab[x] = -1;
    return ret;
}

void Work()
{
    maxflow = 0;
    while (bfs()) maxflow += dfs(source,inf);
}

int main()
{
    freopen("f.in","r",stdin);
    freopen("f.out","w",stdout);
    scanf("%d",&T);
    fo(cs,1,T)
    {
        Initialize();
        Work();
        printf("Case %d: %lld\n",cs,maxflow%maxm);
    }
}
