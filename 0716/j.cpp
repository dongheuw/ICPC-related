#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 1005;
const long long inf = 0x7ffffffffffffffll;

int T,N,M,Q,b[maxn][2],l[maxn];
long long a[maxn][maxn];
bool vis[maxn];
vector<int> c[maxn];

bool find(int k)
{
    for (int i = 0;i < c[k].size();i ++)
        if (!vis[c[k][i]])
        {
            vis[c[k][i]] = 1;
            if (l[c[k][i]] == -1 || find(l[c[k][i]]))
            {
                l[c[k][i]] = k;
                return 1;
            }
        }
    return 0;
}

int main()
{
    freopen("j.in","r",stdin);
    freopen("j.out","w",stdout);
    scanf("%d",&T);
    fo(cs,1,T)
    {
        scanf("%d%d%d",&N,&M,&Q);
        fo(i,0,N-1) fo(j,0,N-1) a[i][j] = inf;
        fo(i,0,N-1) a[i][i] = 0;
        fo(i,0,M-1)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            if (z < a[x][y]) a[x][y] = z;
            a[y][x] = a[x][y];
        }
        fo(k,0,N-1)
            fo(i,0,N-1)
                fo(j,0,N-1)
                    a[i][j] = min(a[i][j],a[i][k]+a[k][j]);
        fo(i,0,Q-1)
        {
            scanf("%d%d",&b[i][0],&b[i][1]);
            c[i].clear();
            l[i] = -1;
        }
        fo(i,0,Q-1)
            fo(j,0,Q-1)
                if (i != j && b[j][1]-b[i][1] >= a[b[i][0]][b[j][0]])
                    c[i].push_back(j);
        int ans = Q-1;
        fo(i,0,Q-1)
        {
            memset(vis,0,sizeof vis);
            if (find(i)) ans --;
        }
        printf("Case %d: %d\n",cs,ans);
    }
    return 0;
}
