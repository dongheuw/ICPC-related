#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 105;

int T,tag,N,cnt;

struct point
{
    int x,y;
}p[maxn];

bool cmpx(const point &a,const point &b)
{
    if(a.x == b.x) return a.y < b.y;
    else return a.x < b.x;
}

bool cmpy(const point &a,const point &b)
{
    if(a.y == b.y) return a.x < b.x;
    else return a.y > b.y;
}

inline int cross(point st,point a,point b)
{
    int x1 = a.x - st.x;
    int y1 = a.y - st.y;
    int x2 = b.x - st.x;
    int y2 = b.y - st.y;
    return x1 * y2 - x2 * y1;
}

bool cmp(const point &a,const point &b)
{
    int k = cross(p[1],a,b);
    if(k == 0) return cmpx(a,b);
    else return k < 0;
}

void Graham()
{
    sort(p + 2,p + N + 1,cmp);
    cnt = 2;    
    for(int i = 3; i <= N; ++i)
    {
        while(cnt >= 2 && cross(p[cnt - 1],p[cnt],p[i]) >= 0) cnt --;
        p[++cnt] = p[i];
    }
}

void Initialize()
{
    scanf("%d%d",&tag,&N);
    int st = -1;
    fo(i,1,N)
    {
        scanf("%d%d",&p[i].x,&p[i].y);
        if (st == -1 || cmpx(p[i],p[st])) st = i;
    }
    swap(p[1],p[st]);
}

void Print()
{
    printf("%d %d\n",tag,cnt);
    int st = -1;
    fo(i,1,cnt) if (st == -1 || cmpy(p[i],p[st])) st = i;
    swap(p[1],p[st]);
    sort(p + 2,p + cnt + 1,cmp);
    fo(i,1,cnt) printf("%d %d\n",p[i].x,p[i].y);
}

int main()
{
    freopen("g.in","r",stdin);
    freopen("g.out","w",stdout);
    for (scanf("%d",&T);T;T --)
    {
        Initialize();
        Graham();
        Print();
    }
    return 0;
}
