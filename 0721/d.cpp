#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

#define INF 1e15
#define eps 1e-9

const int maxn = 10005;
int T,n;
double a[maxn],b[maxn],c[maxn];

double Calc(double x)
{
    double ret = -INF;
    fo(i,0,n-1)
       ret = max(ret,a[i]*x*x+b[i]*x+c[i]);
    return ret;
}

int main()
{
    for (scanf("%d",&T);T;T --)
    {
        scanf("%d",&n);
        fo(i,0,n-1) scanf("%lf%lf%lf",&a[i],&b[i],&c[i]);
        double l = 0, r = 1000;
        while (r - l > eps)
        {
            double l1 = (2 * l + r) / 3;
            double r1 = (2 * r + l) / 3;
            if (Calc(l1) > Calc(r1)) l = l1;
            else r = r1;
        }
        printf("%.4lf\n",Calc(l));
    }
    return 0;
}
