#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define INF 0x3f3f3f3f

using namespace std;

const int maxn = 120;
const int maxm = 100005;
int N,M,S,T,tot;
int a[maxn],b[maxm],c[maxm],d[maxm],cost[maxm];

void Insert(int x,int y,int z,int co)
{
    tot ++;
    b[tot] = y;
    d[tot] = z;
    cost[tot] = co;
    c[tot] = a[x];
    a[x] = tot;
}

void Add(int x,int y,int z,int co)
{
    Insert(x,y,z,co);
    Insert(y,x,0,-co);
}

void Initialize()
{
    tot = 1;
    S = 1; T = N + 1;
    fo(i,1,T) a[i] = 0;
    fo(i,2,N)
    {
        int v;
        scanf("%d",&v);
        Add(i,T,INF,-v);
    }
    fo(i,1,M)
    {
        int x,y,c,z;
        scanf("%d%d%d%d",&x,&y,&c,&z);
        Add(x,y,c,z);
        Add(y,x,c,z);
    }
}

int q[maxn*10],pre[maxn],dist[maxn],MinD[maxn];
bool flag[maxn];
bool SPFA()
{
    int l = 0, r = 1;
    fo(i,0,T) dist[i] = INF;
    memset(flag,0,(T+1));
    q[1] = S; flag[S] = 1;
    dist[S] = 0; MinD[S] = INF;
    while (l < r)
    {
        int x = q[++l];
        for (int i = a[x];i;i = c[i])
            if (d[i] && dist[x]+cost[i] < dist[b[i]])
            {
                dist[b[i]] = dist[x] + cost[i];
                MinD[b[i]] = min(MinD[x],d[i]);
                pre[b[i]] = i;
                if (!flag[b[i]])
                {
                    q[++r] = b[i];
                    flag[b[i]] = 1;
                }
            }
        flag[x] = 0;
    }
    return dist[T] < INF;
}

void Work()
{
    int ans = 0;
    while (SPFA())
    {
        if (dist[T] >= 0) break;
        for (int x = T,i = pre[T];i;x = b[i^1],i = pre[x])
        {
            d[i] -= MinD[T];
            d[i^1] += MinD[T];
        }
        ans += MinD[T] * dist[T];
    }
    printf("%d\n",-ans);
}

int main()
{
    while (scanf("%d%d",&N,&M) != EOF)
    {
        Initialize();
        Work();
    }
    return 0;
}
