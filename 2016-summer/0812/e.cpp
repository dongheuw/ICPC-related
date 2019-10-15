#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

#define BUF_SIZE 100000
bool IOerror=0;
inline char nc(){
    static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
    if (p1==pend){
        p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
        if (pend==p1){IOerror=1;return -1;}
        //{printf("IO error!\n");system("pause");for (;;);exit(0);}
    }
    return *p1++;
}
inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
inline void read(int &x){
    char ch=nc();
    x=0;
    for (;blank(ch);ch=nc());
    if (IOerror)return;
    for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
}

const int maxn = 50005;
vector< pair<int,int> > e[maxn];
int n,m,k,initial,company,pos[maxn],dist[maxn];
int g[25][25],f[1<<18];
bool vis[maxn];

set< pair<int,int> > Q;
void Dijkstra(int st)
{
	fo(i,0,n-1) dist[i] = 1 << 29;
	dist[st] = 0;
	fo(i,0,n-1) Q.insert(make_pair(dist[i],i));
	fo(i,0,n-1)
	{
		int u = Q.begin()->second; Q.erase(Q.begin());
		for (unsigned j = 0;j < e[u].size();j ++)
		{
			int v = e[u][j].first;
			if (dist[u] + e[u][j].second < dist[v])
			{
				Q.erase(make_pair(dist[v],v));
				dist[v] = dist[u] + e[u][j].second;
				Q.insert(make_pair(dist[v],v));
			}
		}
	}
}

void Initialize()
{
	read(n), read(m);
	fo(i,1,m)
	{
		int op,u,v,w;
		read(op), read(u), read(v), read(w);
		u --, v --;
		e[u].push_back(make_pair(v,w));
		if (op == 2) e[v].push_back(make_pair(u,w));
	}
	read(initial);
	read(company);
	read(k);
	fo(i,0,k-1) read(pos[i]);
	pos[k] = company;
	fo(i,0,k) pos[i] --;
	fo(i,0,k)
	{
		Dijkstra(pos[i]);
		fo(j,0,k) g[i][j] = dist[pos[j]];
	}
}

void dfs(int x,int pre,int sta,int cost)
{
	f[sta] = min(f[sta],cost);
	if (x == 4) return;
	fo(i,0,k-1) dfs(x+1,i,sta|(1<<i),cost+g[pre][i]);
}

void Work()
{
	fo(i,0,(1<<k)-1) f[i] = 1 << 29;
	f[0] = 0;
	dfs(0,k,0,initial);
	fo(sta,0,(1<<k)-1)
		for (int sub = sta;sub;sub = (sub-1)&sta)
			f[sta] = min(f[sta],f[sub]+f[sta^sub]);
	printf("%d\n",f[(1<<k)-1]);
	/*for (int sta = 0;sta < (1<<k);sta ++)
	{
		for (int sub = sta;sub;sub = (sub-1)&sta)
	}*/
}

int main()
{
	freopen("e.in","r",stdin);
	freopen("e.out","w",stdout);
	Initialize();
	Work();
	return 0;
}
