#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define sqr(x) ((x)*(x))

using namespace std;

int T,n,flag;
double Min,s1,s2,s3;

struct PT
{
    int x,y;
}L[1005];

bool cmp(const PT &a,const PT &b){ return a.x < b.x; }

int main()
{
    scanf("%d",&T);
    fo(cs,1,T)
    {
        scanf("%d",&n);
        Min = 99999; flag = 0;
        fo(i,1,n) scanf("%d %d",&L[i].x,&L[i].y);
        sort(L+1,L+n+1,cmp);
        fo(i,1,n-1)
            fo(j,i+1,n-1)
            {
                if (Min <= 2 * (L[j].x-L[i].x)) break;
                s1 = sqrt(double(sqr(L[i].x-L[j].x))+sqr(L[i].y-L[j].y));
                if (Min <= 2 * s1) continue;
                fo(k,j+1,n)
                {
                    int t1 = (L[i].x-L[j].x) * (L[j].y-L[k].y);
                    int t2 = (L[j].x-L[k].x) * (L[i].y-L[j].y);
                    if (t1 == t2) continue;
                    flag = 1;
                    s1 = sqrt((double(sqr(L[i].x-L[j].x))+sqr(L[i].y-L[j].y)));
                    s2 = sqrt((double(sqr(L[k].x-L[j].x))+sqr(L[k].y-L[j].y)));
                    s3 = sqrt((double(sqr(L[k].x-L[i].x))+sqr(L[k].y-L[i].y)));
                    Min = min(Min,s1+s2+s3);
                }
            }
        printf("Case %d: ",cs);
        if (flag) printf("%.3lf\n",Min); else printf("No Solution\n");
    }
}
