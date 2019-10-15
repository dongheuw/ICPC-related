#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 2005;
const double eps = 1e-5;

int n,m,k;
double p1,p2,p3,p4,c[maxn],pp[maxn],f[2][maxn];

int main()
{
    freopen("i.in","r",stdin);
    freopen("i.out","w",stdout);
    while(scanf("%d%d%d%lf%lf%lf%lf",&n,&m,&k,&p1,&p2,&p3,&p4)!=EOF)
    {
        if(p4 < eps)
        {
            printf("0.00000\n");
            continue;
        }
        double p = p2/(1-p1);
        double p41 = p4/(1-p1);
        double p31 = p3/(1-p1);
        pp[0] = 1.0;
        fo(i,1,n) pp[i] = p*pp[i-1];

        int cur = 1;
        f[1][1] = p41/(1-p);
        c[1] = p41;
        fo(i,2,n)
        {
            fo(j,2,k) c[j] = p31*f[cur][j-1] + p41;
            fo(j,k+1,i) c[j] = p31*f[cur][j-1];

            double tmp = c[1] * pp[i-1];
            fo(j,2,k) tmp += c[j] * pp[i-j];
            fo(j,k+1,i) tmp += c[j] * pp[i-j];
            
            f[cur^1][i] = tmp / (1-pp[i]);
            f[cur^1][1] = p * f[cur^1][i] + c[1];
            fo(j,2,i-1) f[cur^1][j] = p*f[cur^1][j-1] + c[j];
            cur ^= 1;
        }
        printf("%.5lf\n",f[cur][m]);
    }
    return 0;
}
