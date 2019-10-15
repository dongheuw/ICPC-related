#include <cstdio>
#include <cmath>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
using namespace std;

const int maxn = 105;
int n,m,a[maxn];

int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        fo(i,1,n) scanf("%d",&a[i]);
        sort(a+1,a+1+n);
        int ans = 0;
        for (int i = n;i >= 1;i --)
        {
            ans ++;
            m = m-a[i];
            if (m <= 0) break;
        }
        printf("%d\n",ans);
    }
    return 0;
}
