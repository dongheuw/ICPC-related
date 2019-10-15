#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

const int maxn = 200005;

int father[maxn],cnt[maxn],id[maxn];
long long sum[maxn];
int n,m,tot;

inline int Get(int x)
{
    if (x == father[x]) return x;
    father[x] = Get(father[x]);
    return father[x];
}

void Remove(int x)
{
    int fx = Get(id[x]);
    sum[fx] -= x, cnt[fx] --;
    id[x] = ++ tot;
    sum[id[x]] = x, cnt[id[x]] = 1, father[id[x]] = id[x];
}

void Combine(int x,int y)
{
    int fx = Get(x), fy = Get(y);
    father[fx] = fy, cnt[fy] += cnt[fx], sum[fy] += sum[fx];
}

int main ()
{
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    while (scanf("%d%d",&n,&m) == 2)
    {
        fo(i,0,n) sum[i] = father[i] = id[i] = i,cnt[i] = 1;
        tot = n;
        while (m --)
        {
            int op,x,y;
            scanf("%d",&op);
            switch (op)
            {
                case 1:
                    scanf("%d%d",&x,&y);
                    if (Get(id[x]) != Get(id[y])) Combine(id[x],id[y]);
                    break;
                case 2:
                    scanf("%d%d",&x,&y);
                    if (Get(id[x]) != Get(id[y])) Remove(x),Combine(id[x],id[y]);
                    break;
                case 3:
                    scanf("%d",&x);
                    int fx = Get(id[x]);
                    printf("%d %lld\n",cnt[fx],sum[fx]);
                break;
            }
        }
    }
    return 0;
}
