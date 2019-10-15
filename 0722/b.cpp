#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define sqr(x) ((x)*(x))

using namespace std;

const int maxn = 25;

int N,n,m,ans,d[maxn][maxn];
bool flag[210][210];

struct point
{
    int x,y;
}p[maxn];

struct triangle
{
    int a,b,c;
}t[maxn];

void Initialize()
{
    n = m = ans = 0;
    memset(flag,0,sizeof flag);
    fo(i,1,N)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        x += 100, y += 100;
        if (flag[x][y]) continue;
        flag[x][y] = 1;
        n ++; p[n].x = x, p[n].y = y;
    }
}

bool Similar(const triangle &t1,const triangle &t2)
{
    int a1 = t1.a, b1 = t1.b, c1 = t1.c;
    int a2 = t2.a, b2 = t2.b, c2 = t2.c;
    if (a1*b2 == b1*a2 && a1*c2 == c1*a2 && b1*c2 == c1*b2) return 1;
    else return 0;
}

void Construct(int *tmp,int i,int j,int k)
{
    tmp[0] = d[i][j], tmp[1] = d[j][k], tmp[2] = d[i][k];
    sort(tmp,tmp+3);
    m ++; t[m].a = tmp[0], t[m].b = tmp[1], t[m].c = tmp[2];
}

bool Collinear(const point &p0,const point &p1,const point &p2)
{
    int x1 = p0.x - p2.x, y1 = p0.y - p2.y;
    int x2 = p1.x - p2.x, y2 = p1.y - p2.y;
    if (x1 * y2 == x2 * y1) return 1;
    else return 0;
}

void Work()
{
    fo(i,1,n) fo(j,1,n) d[i][j] = sqr(p[i].x-p[j].x)+sqr(p[i].y-p[j].y);
    fo(i,1,n-2)
        fo(j,i+1,n-1)
            fo(k,j+1,n)
            {
                if (Collinear(p[i],p[j],p[k])) continue;
                int tmp[3];
                Construct(tmp,i,j,k);
            }
    fo(i,1,m)
    {
        int cnt = 1;
        fo(j,i+1,m) if (Similar(t[i],t[j])) cnt ++;
        ans = max(ans,cnt);
    }
    printf("%d\n",ans);
}

int main()
{
    freopen("b.in","r",stdin);
    freopen("b.out","w",stdout);
    while (scanf("%d",&N),N)
    {
        Initialize();
        Work();
    }
    return 0;
}
