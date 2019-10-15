#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i < b;i ++)
#define OP(x) ((((x) - 1) ^ 1) + 1)
#define OP_DIR(x) ((x + 2) & 3)

using namespace std;

const int MAXL = 75;
const int MAXN = MAXL * MAXL * 2 + 10;
const int MAXM = MAXN * 12;
const int fx[] = {0, 1, 0, -1};
const int fy[] = {1, 0, -1, 0};
const int INF = 0x3f3f3f3f;

int N,S,T,n,m;
int id[MAXL + 1][MAXL + 1][2],map[MAXL + 1][MAXL + 1],edge_id[MAXL + 1][MAXL + 1][4];
int beg[MAXN + 1], en[MAXM + 1], nxt[MAXM + 1], c[MAXM + 1];
int tot_flow[2];
int tot = 0;

int ID(int x, int y, int flag)
{
    if (id[x][y][flag]) return id[x][y][flag];
    return id[x][y][flag] = N ++;
}

void Insert(int x,int y,int z)
{
	tot ++;
    nxt[tot] = beg[x];
    beg[x] = tot;
    en[tot] = y;
    c[tot] = z;
}

void AddEdge(int x, int y, int z)
{
    Insert(x,y,z);
    Insert(y,x,0);
}

int cur[MAXN + 1], d[MAXN + 1], pre[MAXN + 1], a[MAXN + 1], cnt[MAXN + 1];
int sap()
{
    int flow = 0;
    int now, tmp, u;
    a[u = S] = INF;
    cnt[0] = N;
    memcpy(cur, beg, sizeof(beg[0]) * N);
    while (d[S] < N)
    {
        for (now = cur[u]; now; now = nxt[now])
            if (c[now] && d[u] == d[en[now]] + 1) break;
        if (now)
        {
            tmp = en[now];
            pre[tmp] = cur[u] = now;
            a[tmp] = min(a[u], c[now]);
            if ((u = tmp) == T)
            {
                flow += (tmp = a[T]);
                do
                {
                    c[pre[u]] -= tmp;
                    c[OP(pre[u])] += tmp;
                    u = en[OP(pre[u])];
                } while (u != S);
                a[S] = INF;
            }
        }
        else
        {
            if ((--cnt[d[u]]) == 0) break;
            cur[u] = beg[u];
            d[u] = N;
            for (now = beg[u]; now; now = nxt[now])
                if (c[now] && d[u] > d[en[now]] + 1)
                    d[u] = d[en[now]] + 1, cur[u] = now;
            cnt[d[u]] ++;
            if (u != S) u = en[OP(pre[u])];
        }
    }
    return flow;
}

bool ans;
void Solve()
{
    ans = 1;
    if (tot_flow[0] != tot_flow[1] || sap() != tot_flow[0]) ans = 0;
}

const int UP    = 3;
const int DOWN  = 1;
const int LEFT  = 2;
const int RIGHT = 0;
void Print()
{
    if (!ans) printf("Impossible!\n");
    else
    {
        fo(i,0,n)
        {
            fo(j,0,m)
            {
                printf("%c", '.');
                printf("%c", c[edge_id[i][j][UP]] ? 'X' : '.');
                printf("%c", '.');
            }
            printf("\n");
            fo(j,0,m)
            {
                printf("%c", c[edge_id[i][j][LEFT]] ? 'X' : '.');
                printf("%c", map[i][j] ? 'O' : '.');
                printf("%c", c[edge_id[i][j][RIGHT]] ? 'X' : '.');
            }
            printf("\n");
            fo(j,0,m)
            {
                printf("%c", '.');
                printf("%c", c[edge_id[i][j][DOWN]] ? 'X' : '.');
                printf("%c", '.');
            }
            printf("\n");
        }
    }
}

void BuildGraph()
{
	fo(i,0,n) fo(j,0,m)
    	if (map[i][j])
        {
            if ((i + j) & 1)
            {
                for (int k = 0; k < 4; k ++)
                {
                    int x = i + fx[k];
                    int y = j + fy[k];
                    if (x >= 0 && x < n && y >= 0 && y < m && map[x][y])
                    {
                        AddEdge(ID(i, j, (map[i][j] == 2 ? (k & 1) : 0)), ID(x, y, (map[x][y] == 2 ? (k & 1) : 0)), 1);
                        edge_id[i][j][k] = edge_id[x][y][OP_DIR(k)] = tot;
                    }
                }
                if (map[i][j] == 2)
                {
                	AddEdge(S, ID(i, j, 0), 1);
                    AddEdge(S, ID(i, j, 1), 1);
                }
                else AddEdge(S, ID(i, j, 0), map[i][j]);
            }
            else
            {
                if (map[i][j] == 2)
                {
                    AddEdge(ID(i, j, 0), T, 1);
                    AddEdge(ID(i, j, 1), T, 1);
                }
                else AddEdge(ID(i, j, 0), T, map[i][j]);
            }
                tot_flow[(i + j) & 1] += map[i][j];
        }
}

void Initialize()
{
    scanf("%d%d", &n, &m);
    fo(i,0,n)
        fo(j,0,m)
            scanf("%d", &map[i][j]);
	N = 2;
	S = 0; T = 1;
	BuildGraph();
}

int main()
{
	Initialize();
	Solve();
	Print();
	return 0;
}
