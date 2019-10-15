#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
using namespace std;

const int maxn = 1005;
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,-1,0,1};
const int inf = (int)2e8;

int n,m,dis[3][maxn][maxn];
char s[maxn][maxn];

queue< pair<int,int> > Q;
void Bfs()
{
    fo(k,0,2)
    {
        while (!Q.empty()) Q.pop();
        fo(i,0,n-1)
            fo(j,0,m-1)
                if (s[i][j] == k + '1')
                    Q.push(make_pair(i,j)), dis[k][i][j] = 0;
        while (!Q.empty())
        {
            pair<int,int> now = Q.front(); Q.pop();
            int x = now.first, y = now.second;
            fo(i,0,3)
            {
                int xx = x + dx[i], yy = y + dy[i];
                if (!(xx >= 0 && xx < n)) continue;
                if (!(yy >= 0 && yy < m)) continue;
                if (s[xx][yy] == '#') continue;
                if (dis[k][xx][yy] > dis[k][x][y] + (s[x][y] == '.'))
                {
                    dis[k][xx][yy] = dis[k][x][y] + (s[x][y] == '.');
                    Q.push(make_pair(xx, yy));
                }
            }
        }
    }
}

int main()
{
    while (scanf("%d%d",&n,&m) != EOF)
    {
        fo(i,0,n-1) scanf("%s",s[i]);
        fo(i,0,n-1)
            fo(j,0,m-1)
                dis[0][i][j] = dis[1][i][j] = dis[2][i][j] = inf;
        Bfs();
        int ans = (int)1e9;
        fo(i,0,n-1)
            fo(j,0,m-1)
                ans = min(ans,dis[0][i][j]+dis[1][i][j]+dis[2][i][j]+(s[i][j]=='.'));
        if (ans >= inf) ans = -1;
        printf("%d\n", ans);
   }
   return 0;
}
