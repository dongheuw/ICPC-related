#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 100005;

int n,m,last[maxn],now,K;

struct Edge
{
    int u,v,w,sig,id;
}e[maxn];

bool cmp(const Edge &a,const Edge &b)
{
    if (a.w == b.w) return a.sig > b.sig;
    return a.w < b.w;
}

bool cmp2(const Edge &a,const Edge &b) {return a.id < b.id;}

bool flag;
void Work()
{
    fo(i,1,m)
    {
        if (e[i].sig == 0)
        {
            for (;;)
            {
                if (K >= now+1)
                {
                    flag = 1;
                    break;
                }
                if (last[K] + 1 <= now)
                {
                    e[i].u = K, e[i].v = last[K] + 1;
                    last[K] ++;
                    break;
                } else K ++;
            }
        } else
        if (e[i].sig == 1)
        {
            e[i].u = 1, e[i].v = ++ now;
            K = 2;
        } 
        if (flag) break;
    }
    if (flag)
    {
        printf("-1\n");
        return;
    }
    sort(e+1,e+m+1,cmp2);
    fo(i,1,m)
        printf("%d %d\n",e[i].u,e[i].v);
}

void Initialize()
{
    now = 1;
    flag = 0;
    K = 2;
    fo(i,1,n) last[i] = i;
    fo(i,1,m) scanf("%d%d",&e[i].w,&e[i].sig), e[i].id = i;
    sort(e+1,e+m+1,cmp);
}
 
int main()
{
    while (scanf("%d%d",&n,&m) != EOF)
    {
        Initialize();
        Work();
    }
    return 0;
}
