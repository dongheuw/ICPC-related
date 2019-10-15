#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 45;
const char c[4] = {'D','L','R','U'};

int T,d[2][maxn][4],st[2],en[2],f[maxn][maxn];
int fa0[maxn][maxn],fa1[maxn][maxn],dir[maxn][maxn],ans[3000];
bool can[2][maxn];

void Work()
{
    memset(dir,-1,sizeof dir);
    dir[st[0]][st[1]] = 5;
    queue<int> q1,q2;
    while (!q1.empty()) q1.pop();
    while (!q2.empty()) q2.pop();
    q1.push(st[0]), q2.push(st[1]);
    bool p[maxn][maxn];
    memset(p,1,sizeof p);
    p[st[0]][st[1]] = 0;
    while (!q1.empty()) 
    {
        int x = q1.front(); q1.pop();
        int y = q2.front(); q2.pop();
        fo(i,0,3)
        {
            int tx = d[0][x][i];
            int ty = d[1][y][i];
            if (tx && ty && can[0][tx] && can[1][ty])
                if (p[tx][ty])
                {
                    q1.push(tx), q2.push(ty);
                    p[tx][ty] = 0;
                    fa0[tx][ty] = x;
                    fa1[tx][ty] = y;
                    dir[tx][ty] = i; 
                }
        }
    }
}

void Print()
{
    int x = en[0], y = en[1];
    if (dir[x][y] == -1)
    {
        printf("-1\n");
        return;
    }
    int tot = 0, tx, ty;
    while (!(x == st[0] && y == st[1]))
    {
        ans[++tot] = dir[x][y];
        tx = fa0[x][y];
        ty = fa1[x][y];
        x = tx, y = ty;
    }
    for (int i = tot;i;i --) printf("%c",c[ans[i]]);
    printf("\n");
}

void Initialize(int cur)
{
    memset(d[cur],0,sizeof d[cur]);
    memset(can[cur],1,sizeof can[cur]);
    fo(i,1,6)
        fo(j,1,6)
        {
            int t = (i-1) * 6 + j, x;
            scanf("%d",&x);
            if (x & (1<<1)) d[cur][t][0] = t;
            else if (i < 6) d[cur][t][0] = t + 6;
            if (x & (1<<0)) d[cur][t][1] = t;
            else if (j > 1) d[cur][t][1] = t - 1;
            if (x & (1<<2)) d[cur][t][2] = t;
            else if (j < 6) d[cur][t][2] = t + 1;
            if (x & (1<<3)) d[cur][t][3] = t;
            else if (i > 1) d[cur][t][3] = t - 6;
            if ((x & (1<<4)) == 0) can[cur][t] = 0;
            if (x & (1<<5)) st[cur] = t;
            if (x & (1<<6)) en[cur] = t;
        }
}

int main()
{
    freopen("c.in","r",stdin);
    freopen("c.out","w",stdout);
    scanf("%d",&T);
    Initialize(1);
    fo(i,2,T)
    {
        Initialize(i & 1);
        Work();
        Print();
    }
    return 0;
}
