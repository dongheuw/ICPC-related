#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const double EPS = 1e-4;
const int maxn = 105;

int n,p;
double x,y,s,t[maxn],pre[maxn];
bool vi[maxn];
vector< pair<int,double> > E[maxn];

inline double sign(double x)
{
    return x < -EPS ? -1 : x > EPS;
}

struct Pool
{
    double x1,y1,x2,y2,d,len;
    void read()
    {
        scanf("%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&d);
        if (x1 > x2) swap(x1,x2);
        if (y1 > y2) swap(y1,y2);
        d = d/100*(x2-x1)*(y2-y1);
        len = 2*(x2-x1)+2*(y2-y1);
    }
    double approach(Pool & B)
    {
        if(x2 == B.x1 || x1 == B.x2)
        {
            return min(y2,B.y2) - max(y1,B.y1);
        }
        if(y2 == B.y1 || y1 == B.y2)
        {
            return min(x2,B.x2) - max(x1,B.x1);
        }
        return 0;
    }
}pool[maxn];

int main()
{
    while (scanf("%d%lf%lf%d%lf",&n,&x,&y,&p,&s) != EOF)
    {
        for (int i = 0;i < n;i ++) E[i].clear();
        p --;
        s /= 1000;
        for (int i = 0;i < n;i ++)
        {
            pool[i].read();
            for (int j = 0;j < i;j ++)
            {
                double approach = pool[i].approach(pool[j]);
                if(sign(approach) > 0)
                {
                    E[i].push_back(make_pair(j,approach));
                    E[j].push_back(make_pair(i,approach));
                }
            }
            t[i] = 1e30;
            vi[i] = 0;
            pre[i] = 0;
        }
        t[p] = pool[p].d / s;
        double ans = 0, length = 0;
        for (int i = 0;i < n;i ++)
        {
            vector<int> VT;
            for (int j = 0;j < n;j ++)
                if (!vi[j])
                {
                    if (VT.size() == 0 || sign(t[VT[0]]-t[j]) == 0) VT.push_back(j);
                    else if(sign(t[VT[0]]-t[j]) > 0) VT.clear(), VT.push_back(j);
                }
            if (VT.size() == 0) break;
            double needTime = t[VT[0]];
            if (sign(length))
               for (int j = 0;j < n;j ++)
               {
                   if (vi[j]) continue;
                   pool[j].d -= pre[j]/length*s*needTime;
               }
            ans += needTime;
            for (int k = 0;k < VT.size();k ++)
            {            
                int ID = VT[k];
                length += pool[ID].len;        
                for (int j = 0;j < E[ID].size();j ++)
                    if (vi[E[ID][j].first]) length -= 2*E[ID][j].second;
                vi[ID] = 1;
            }
            for (int j = 0;j < n;j ++)
            {
                if (vi[j]) continue;
                double speed = 0;
                for (int k = 0;k < E[j].size();k ++)
                    if (vi[E[j][k].first])
                        speed += E[j][k].second;
                pre[j] = speed;
                speed *= s / length;
                t[j] = pool[j].d / speed;
            }
        }
        printf("%.4f\n",ans);
    }
    return 0;
}
