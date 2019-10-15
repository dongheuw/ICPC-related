#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
using namespace std;

int n,m,ans,a[15];

int main()
{
    scanf("%d%d",&n,&m);
    fo(i,1,n)
    {
        int x;
        scanf("%d",&x);
        a[x] ++;
    }
    fo(i,1,m)
        fo(j,i+1,m)
            ans += a[i]*a[j];
    printf("%d\n",ans);
    return 0;
}
