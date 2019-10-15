#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

typedef long long LL;

const int maxn = 1005;
const int inf = 1000000007;


int n,m,L,s,t,a[maxn][maxn],b[maxn][maxn];
int e[maxn][3];
std::queue<int> Q;
bool flag[maxn];
LL dist[2][maxn];
void spfa(int idx)
{
	while (!Q.empty())
	{
		int x = Q.front(); Q.pop();
		fo(i,1,b[x][0])
			if (a[x][b[x][i]] && a[x][b[x][i]] < inf && dist[idx][x] + a[x][b[x][i]] < dist[idx][b[x][i]])
			{
				dist[idx][b[x][i]] = dist[idx][x] + a[x][b[x][i]];
				if (!flag[b[x][i]])
				{
					Q.push(b[x][i]);
					flag[b[x][i]] = 1;
				}
			}
		flag[x] = 0;
	}
}

int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	scanf("%d%d%d%d%d",&n,&m,&L,&s,&t);
	s ++, t ++;
	fo(i,1,m)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		u ++, v ++;
		e[i][0] = u, e[i][1] = v, e[i][2] = w;
		a[u][v] = w, a[v][u] = w;
		b[u][++b[u][0]] = v;
		b[v][++b[v][0]] = u;
	}
	memset(dist,10,sizeof dist);
	dist[0][s] = 0; dist[1][t] = 0;
	Q.push(s); flag[s] = 1; spfa(0);
	Q.push(t); flag[t] = 1; spfa(1);
	bool ok = 0;
	if (dist[0][t] == L)
	{
		ok = 1;
		fo(i,1,m)
			if (e[i][2] == 0) e[i][2] = inf;
	} else
	{
		fo(i,1,m)
			if (e[i][2] == 0)
			{
				LL tmp1 = inf, tmp2 = inf, tmp;
				if (dist[0][e[i][0]] < inf && dist[1][e[i][1]] < inf)
					tmp1 = dist[0][e[i][0]] + dist[1][e[i][1]];
				if (dist[0][e[i][1]] < inf && dist[1][e[i][0]] < inf)
					tmp2 = dist[0][e[i][1]] + dist[1][e[i][0]];
				tmp = std::min(tmp1,tmp2);
				if (tmp < L) e[i][2] = a[e[i][0]][e[i][1]] = a[e[i][1]][e[i][0]] = L - tmp;
				else e[i][2] = a[e[i][0]][e[i][1]] = a[e[i][1]][e[i][0]] = 1;
				Q.push(e[i][0]); flag[e[i][0]] = 1;
				Q.push(e[i][1]); flag[e[i][1]] = 1; spfa(0);
				Q.push(e[i][0]); flag[e[i][0]] = 1;
				Q.push(e[i][1]); flag[e[i][1]] = 1; spfa(1);
				if (dist[0][t] == L)
				{
					ok = 1;
					fo(j,i+1,m) if (e[j][2] == 0) e[j][2] = inf;
					break;
				}
			}
	}
	if (ok)
	{
		puts("YES");
		fo(i,1,m) printf("%d %d %d\n",e[i][0]-1,e[i][1]-1,e[i][2]);
	} else puts("NO");
	return 0;
}
