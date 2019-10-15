#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
#define eps 1e-8

using namespace std;

const int maxn = 1205;

struct Point
{
    double x,y;
}p[maxn];

double a[maxn][maxn];
int n,color[maxn],ans[maxn];

double Dist(int i,int j)
{
    return sqrt((p[i].x-p[j].x)*(p[i].x-p[j].x)+(p[i].y-p[j].y)*(p[i].y-p[j].y));
}

bool Judge(double limit)
{
    memset(color,0,sizeof color);
    queue<int> Q;
    for (int i = 1;i <= n;i ++)
        if (!color[i])
        {
            color[i] = 1;
            Q.push(i);
            while (!Q.empty())
            {
                int u = Q.front(); Q.pop();
                for (int v = 1;v <= n;v ++)
                {
                    if (a[u][v] > limit-eps) continue;
                    if (color[u] == color[v]) return 0;
                    if (color[v] == 0)
                    {
                        color[v] = 3 - color[u];
                        Q.push(v);
                    }
                }
            }
        }
    for (int i = 1;i <= n;i ++) ans[i] = color[i];
    return 1;
}

    

int main()
{
    while (scanf("%d",&n) != EOF)
    {
        for (int i = 1;i <= n;i ++) scanf("%lf%lf",&p[i].x,&p[i].y);
        for (int i = 1;i <= n;i ++)
            for (int j = 1;j <= n;j ++)
                a[i][j] = (i == j ? 1e20 : Dist(i,j));
        double low = 0,high = 40000;
        while (high-low > eps)
        {
            double mid = (low+high)*0.5;
            if (Judge(mid)) low = mid;
            else high = mid;
        }
        printf("%.7f\n",low/2);
        for (int i = 1;i <= n;i ++) printf(i==n?"%d\n":"%d ",ans[i]);
    }
    return 0;
}
