#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <string>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 10010;
const int inf = 0x3f3f3f3f;
int T,N,M,H,V,S;
char map[50][50];
int tot,a[maxn],b[maxn],c[maxn],d[maxn],e[maxn];
int s,t,sum;
vector<string> ans;
bool flag[maxn];

void Initialize()
{
	ans.clear();
	sum = 0;
	scanf("%d%d%d%d%d",&N,&M,&H,&V,&S);
	memset(flag,0,sizeof flag);
	fo(i,0,N-1)
	{
		scanf("%s",map[i]);
		fo(j,0,M-1) flag[map[i][j]-'a'] = 1;
	}
}

void Insert(int x,int y,int z)
{
	b[tot] = y;
	c[tot] = a[x];
	d[tot] = z;
	e[tot] = x;
	a[x] = tot ++;
}

void Add(int x,int y,int z)
{
	Insert(x,y,z);
	Insert(y,x,0);
}

queue<int> Q;
int lab[maxn];
bool BFS()
{
	memset(lab,255,sizeof lab);
	while (!Q.empty()) Q.pop();
	Q.push(s); lab[s] = 0;
	while (!Q.empty())
	{
		int x = Q.front(); Q.pop();
		for (int i = a[x];i;i = c[i])
			if (lab[b[i]] == -1 && d[i])
			{
				lab[b[i]] = lab[x] + 1;
				Q.push(b[i]);
			}
	}
	return lab[t] > -1;
}

int DFS(int x,int flow)
{
	if (x == t) return flow;
	int ret = 0;
	for (int i = a[x];i;i = c[i])
		if (d[i] && lab[x]+1 == lab[b[i]])
		{
			int now = DFS(b[i],min(flow,d[i]));
			d[i] -= now;
			d[i^1] += now;
			flow -= now;
			ret += now;
			if (!flow) return ret;
		}
	lab[x] = -1;
	return ret;
}

int Maxflow()
{
	int ret = 0;
	while (BFS()) ret += DFS(s,inf);
	return ret;
}

void Work(char color)
{
	vector<string> refer;
	char opt[50];
	pair<int,int> path[50][50];
	int c = 0, r = 0;
	fo(i,0,N-1)
		fo(j,0,M-1)
			if (map[i][j] == color)
			{
				r ++;
				int k = j;
				for (;k < M && map[i][k] == color;k ++) path[i][k].first = r;
				sprintf(opt,"h %d %d %d %d %c",i+1,j+1,i+1,k,color);
				refer.push_back(opt);
				j = k;
			}
	fo(j,0,M-1)
		fo(i,0,N-1)
			if (map[i][j] == color)
			{
				c ++;
				int k = i;
				for (;k < N && map[k][j] == color;k ++) path[k][j].second = c;
				sprintf(opt,"v %d %d %d %d %c",i+1,j+1,k,j+1,color);
				refer.push_back(opt);
				i = k;
			}
	s = 0, t = r+c+1;
	tot = 2;
	memset(a,0,sizeof a);
	fo(i,1,r) Add(s,i,H);
	fo(i,1,c) Add(r+i,t,V);
	fo(i,0,N-1)
		fo(j,0,M-1)
			if (map[i][j] == color)
			{
				Add(path[i][j].first,path[i][j].second+r,S);
				sprintf(opt,"s %d %d %c",i+1,j+1,color);
				refer.push_back(opt);
			}
	sum += Maxflow();
	BFS();
	for (int i = 0;i < tot;i += 2)
		if (lab[e[i]] > -1 && lab[b[i]] == -1) ans.push_back(refer[i/2-1]);
}

int main()
{
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);
	for (scanf("%d",&T);T;T --)
	{
		Initialize();
		fo(i,0,25)
		{
			if (!flag[i]) continue;
			Work('a'+i);
		}
		printf("%d %lu\n",sum,ans.size());
		for (unsigned i = 0;i < ans.size();i ++) printf("%s\n",ans[i].c_str());
		if (T) puts("");
	}
	return 0;
}
