#include <cstdio>
#include <cstring>
#include <algorithm>

#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

int T,N,M;
bool used[200010],flag;

struct Point
{
    int x,y;
}P[100005];

int Abs(int x)
{
    if (x < 0) x = -x;
    return x;
}

int dist(int x,int y)
{
    return Abs(P[x].x-P[y].x)+Abs(P[x].y-P[y].y);
}

int main()
{
    freopen("1011.in","r",stdin);
    freopen("1011.out","w",stdout);
    for (scanf("%d",&T);T;T --)
    {
        scanf("%d%d",&N,&M);
        fo(i,1,N) scanf("%d%d",&P[i].x,&P[i].y);
        fo(i,0,2*M) used[i] = 0;
        flag = 0;
        fo(i,1,N-1)
        {
            fo(j,i+1,N)
            {
                int tmp = dist(i,j);
                if (used[tmp])
                {
                    flag = 1;
                    break;
                }
                used[tmp] = 1;
            }
            if (flag) break;
        }
        if (flag) puts("YES"); else puts("NO");
    }
}
