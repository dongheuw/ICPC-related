#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int  i = a;i <= b;i ++)

using namespace std;

int n,c,t,a[25];
bool f[11005][11005];

int main()
{
    freopen("h.in","r",stdin);
    freopen("h.out","w",stdout);
    for (scanf("%d",&t);t;t --)
    {
        scanf("%d%d",&n,&c);
        fo(i,0,c-1) scanf("%d",&a[i]);
        fo(i,0,n) fo(j,0,n) f[i][j] = 0;
        f[0][0] = 1;
        fo(i,0,n-1)
            fo(j,0,n-1)
                if (f[i][j])
                    fo(k,0,c-1)
                        f[i+j+a[k]][j+a[k]] = 1;
        int ans = -1;
        fo(i,0,n)
            if (f[n][i]) ans = i;
        printf("%d\n",ans);
    }
    return 0;
}
