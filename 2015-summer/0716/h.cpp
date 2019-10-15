#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

int N,f[1050000],ans;

int main()
{
    freopen("h.in","r",stdin);
    freopen("h.out","w",stdout);
    while (1)
    {
        scanf("%d",&N);
        if (N < 0) break;
        memset(f,0,sizeof f);
        fo(i,1,N)
        {
            int x,v;
            scanf("%d%d",&x,&v);
            f[x] = v;
        }
        fo(i,0,19)
            fo(j,1,(1<<20)-1)
                if ((j>>i) & 1) f[j] += f[j^(1<<i)];
        ans = 0;
        fo(i,0,(1<<20)-1) ans = max(ans,f[i]);
        printf("%d\n",ans);
    }
    return 0;
}
