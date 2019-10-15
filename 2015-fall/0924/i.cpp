#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 505;
int T,x,y,n,a,b,cost[maxn][maxn][4];
bool vis[maxn][maxn][4];
char mp[maxn][maxn];

void Initialize()
{
	scanf("%d",&n);
	memset(cost,0,sizeof cost);
	fo(i,0,n-1)
	{
		scanf("%s",mp[i]);
		fo(j,0,n-1)
		{
			if (mp[i][j] == 'M') x = i, y = j;
			else if (mp[i][j] == 'N')
			{
				cost[i][j][0] = cost[i][j][1] = cost[i][j][2] = cost[i][j][3] = 1;
				if (i-1 >= 0) cost[i-1][j][0] = 1;
				if (j+1 < n) cost[i][j+1][1] = 1;
				if (j-1 >= 0) cost[i][j-1][3] = 1;
				if (i+1 < n) cost[i+1][j][2] = 1;
			} else
			if (mp[i][j] == 'W')
			{
				cost[i][j][0] = cost[i][j][1] = cost[i][j][2] = cost[i][j][3] = 1;
				if (i-1 >= 0) cost[i-1][j][1] = 1;
				if (j+1 < n) cost[i][j+1][2] = 1;
				if (j-1 >= 0) cost[i][j-1][0] = 1;
				if (i+1 < n) cost[i+1][j][3] = 1;
			} else
			if (mp[i][j] == 'S')
			{
				cost[i][j][0] = cost[i][j][1] = cost[i][j][2] = cost[i][j][3] = 1;
				if (i-1 >= 0) cost[i-1][j][2] = 1;
				if (j+1 < n) cost[i][j+1][3] = 1;
				if (j-1 >= 0) cost[i][j-1][1] = 1;
				if (i+1 < n) cost[i+1][j][0] = 1;
			} else
			if (mp[i][j] == 'E')
			{
				cost[i][j][0] = cost[i][j][1] = cost[i][j][2] = cost[i][j][3] = 1;
				if (i-1 >= 0) cost[i-1][j][3] = 1;
				if (j+1 < n) cost[i][j+1][0] = 1;
				if (j-1 >= 0) cost[i][j-1][2] = 1;
				if (i+1 < n) cost[i+1][j][1] = 1;
			} else if (mp[i][j] == 'T') a = i, b = j;
		}
	}
}

struct Sta
{
	int x,y,step;
};

bool operator < (Sta a,Sta b){return a.step > b.step;}

int dx[] = {-1,0,1,0,0};
int dy[] = {0,1,0,-1,0};
priority_queue<Sta> Q;
int Work(int x,int y)
{
	memset(vis,0,sizeof vis);
	while (!Q.empty()) Q.pop();
	Sta st; st.x = x, st.y = y, st.step = 0;
	vis[x][y][0] = 1; Q.push(st);
	while (!Q.empty())
	{
		Sta u = Q.top(); Q.pop();
		if (u.x == a && u.y == b) return u.step;
		fo(i,0,4)
		{
			int xx = u.x + dx[i], yy = u.y + dy[i];
			if (xx < 0 || xx >= n || yy < 0 || yy >= n) continue;
			if (mp[xx][yy] == '#') continue;
			Sta next = u;
			if (cost[xx][yy][u.step%4] || cost[u.x][u.y][u.step%4])
			{
				if (xx == u.x && yy == u.y && !vis[xx][yy][(u.step+1)%4])
				{
					next.step ++;
					vis[xx][yy][next.step%4] = 1;
					Q.push(next);
				} else if (!vis[xx][yy][(u.step+3)%4])
				{
					next.x = xx, next.y = yy;
					next.step += 3;
					vis[xx][yy][next.step%4] = 1;
					Q.push(next);
				}
			} else if (!vis[xx][yy][(u.step+1)%4])
			{
				next.x = xx, next.y = yy; next.step ++;
				vis[xx][yy][next.step%4] = 1;
				Q.push(next);
			}
		}
	}
	return -1;
}

int main()
{
	freopen("i.in","r",stdin);
	freopen("i.out","w",stdout);
	scanf("%d",&T);
	fo(cs,1,T)
	{
		Initialize();
		printf("Case #%d: %d\n",cs,Work(x,y));
	}
	return 0;
}
