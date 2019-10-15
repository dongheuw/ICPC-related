#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
///LOOP
#define REP(i, n) for(int i = 0; i < n; i++)
#define FF(i, a, b) for(int i = a; i < b; i++)
#define FFF(i, a, b) for(int i = a; i <= b; i++)
#define FD(i, a, b) for(int i = a - 1; i >= b; i--)
#define FDD(i, a, b) for(int i = a; i >= b; i--)
///INPUT
#define RI(n) scanf("%d", &n)
#define RII(n, m) scanf("%d%d", &n, &m)
#define RIII(n, m, k) scanf("%d%d%d", &n, &m, &k)
#define RIV(n, m, k, p) scanf("%d%d%d%d", &n, &m, &k, &p)
#define RV(n, m, k, p, q) scanf("%d%d%d%d%d", &n, &m, &k, &p, &q)
#define RFI(n) scanf("%lf", &n)
#define RFII(n, m) scanf("%lf%lf", &n, &m)
#define RFIII(n, m, k) scanf("%lf%lf%lf", &n, &m, &k)
#define RFIV(n, m, k, p) scanf("%lf%lf%lf%lf", &n, &m, &k, &p)
#define RS(s) scanf("%s", s)
///OUTPUT
#define PN printf("\n")
#define PI(n) printf("%d\n", n)
#define PIS(n) printf("%d ", n)
#define PS(s) printf("%s\n", s)
#define PSS(s) printf("%s ", n)
#define PC(n) printf("CASE# %d:\n", n)
///OTHER
#define PB(x) push_back(x)
#define CLR(a, b) memset(a, b, sizeof(a))
#define CPY(a, b) memcpy(a, b, sizeof(b))
#define display(A, n, m) {REP(i, n){REP(j, m)PIS(A[i][j]);PN;}}
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int MOD = 1000000007;
const int INFI = 1e9 * 2;
const LL LINFI = 1e17;
const double eps = 1e-6;
const double pi = acos(-1.0);
const int N = 8;
const int M = 26;
const int move[8][2] = {0,1,0,-1,1,0,-1,0,1,1,1,-1,-1,1,-1,-1};

int map[N][N];
int n, m, k, cnt, ans;

int getsum()
{
    int s = 0;
    int sum[N];
    CLR(sum, 0);
    REP(i, n)REP(j, m)sum[map[i][j]]++;
    FFF(i, 1, k)if(sum[i] >= 3)s += sum[i] * sum[i];
    return s;
}

bool check(int x, int y)
{
    return x >= 0 && y >= 0 && x < n && y < m;
}

void dfs(int x,int y,int col,bool vis[][N])
{
    fo(i,0,7)
    {
        int tx = x + move[i][0], ty = y + move[i][1];
        if (check(tx,ty) && !vis[tx][ty] && map[tx][ty] == col)
        {
            vis[tx][ty] = 1;
            map[tx][ty] = 0;
            cnt ++;
            dfs(tx,ty,col,vis);
        }
    }
}

void movegem()
{
    fo(i,0,m-1)
    {
        int k = n - 1;
        for (int j = n-1;j >= 0;j --) 
            if (map[j][i]) map[k--][i] = map[j][i];
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

void solve(int now)
{
    if (getsum() + now <= ans) return;
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
            dfs(i,j,map[i][j],vis);
            if (cnt < 3)
            {
                fo(ii,0,n-1) fo(jj,0,m-1) map[ii][jj] = tmp[ii][jj];
                continue;
            }
            movegem();
            t = now + cnt * cnt;
            ans = max(ans, t);
            solve(t);
            fo(ii,0,n-1) fo(jj,0,m-1) map[ii][jj] = tmp[ii][jj];
        }
}

int main()
{
    freopen("j.in","r",stdin);
    freopen("j.out","w",stdout);
    while(scanf("%d%d%d",&n,&m,&k) != EOF)
    {
        fo(i,0,n-1) fo(j,0,n-1) scanf("%d",&map[i][j]);
        ans = 0;
        solve(0);
        printf("%d\n",ans);
    }
    return 0;
}
