#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int N = 8;
const int dir[8][2] = {{0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};

int map[N][N],n,m,k,cnt,ans;

int CalcSum()
{
    int s = 0;
    int sum[N];
    memset(sum,0,sizeof sum);
    fo(i,0,n-1) fo(j,0,m-1) sum[map[i][j]] ++;
    fo(i,1,k) if(sum[i] >= 3) s += sum[i] * sum[i];
    return s;
}

bool Check(int x, int y)
{
    return x >= 0 && y >= 0 && x < n && y < m;
}

void Dfs(int x,int y,int col,bool vis[][N])
{
    fo(i,0,7)
    {
        int tx = x + dir[i][0], ty = y + dir[i][1];
        if (Check(tx,ty) && !vis[tx][ty] && map[tx][ty] == col)
        {
            vis[tx][ty] = 1;
            map[tx][ty] = 0;
            cnt ++;
            Dfs(tx,ty,col,vis);
        }
    }
}

void ClearGem()
{
    fo(i,0,m-1)
    {
        int k = n - 1;
        for (int j = n-1;j >= 0;j --) if (map[j][i]) map[k--][i] = map[j][i];
        while (k >= 0) map[k--][i] = 0;
    }
    int k = 0;
    fo(i,0,m-1)
        if (map[n-1][i])
        {
            if (i != k)
                fo(j,0,n-1)
                    map[j][k] = map[j][i], map[j][i] = 0;
            k ++;
        }
}

void Solve(int now)
{
    if (CalcSum() + now <= ans) return;
    bool vis[N][N];
    int tmp[N][N], t;
    memset(vis,0,sizeof vis);
    fo(i,0,n-1)
        fo(j,0,m-1)
        {
            if (!map[i][j]) vis[i][j] = 1;
            if (vis[i][j]) continue;
            cnt = 0;
            fo(ii,0,n-1) fo(jj,0,m-1) tmp[ii][jj] = map[ii][jj];
            Dfs(i,j,map[i][j],vis);
            if (cnt < 3)
            {
                fo(ii,0,n-1) fo(jj,0,m-1) map[ii][jj] = tmp[ii][jj];
                continue;
            }
            ClearGem();
            t = now + cnt * cnt;
            ans = max(ans, t);
            Solve(t);
            fo(ii,0,n-1) fo(jj,0,m-1) map[ii][jj] = tmp[ii][jj];
        }
}

int main()
{
    freopen("j.in","r",stdin);
    freopen("j.out","w",stdout);
    while(scanf("%d%d%d",&n,&m,&k) != EOF)
    {
        fo(i,0,n-1) fo(j,0,m-1) scanf("%d",&map[i][j]);
        ans = 0;
        Solve(0);
        printf("%d\n",ans);
    }
    return 0;
}
