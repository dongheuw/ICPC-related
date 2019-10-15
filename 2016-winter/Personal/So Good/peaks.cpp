#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

typedef pair<int,int> PI;
typedef vector<PI> VECPI;

const int maxN = 2005;
const int maxn = maxN*maxN;
const int dx[8] = {-1,-1,-1,0,0,1,1,1};
const int dy[8] = {-1,0,1,-1,1,-1,0,1};

int N,M,col,numc;
int belong[maxN][maxN],height[maxN][maxN];
int peak[maxn],f[maxn],h[maxn],pos[maxn];
int top[maxn],cnt[maxn];
bool flag[maxn];
VECPI s[maxn];
PI ans[maxn];

inline bool cmp(int x,int y){return h[x] > h[y];}
inline bool cmpPI(const PI &a,const PI &b){return a.first != b.first ? a.first > b.first : a.second > b.second;}
inline int getfather(int x){return f[x] != x ? f[x]=getfather(f[x]) : x;}

void floodfill(int i,int j)
{
	belong[i][j] = col;
	s[col].push_back(PI(i,j));
	fo(w,0,7)
	{
		int x = i + dx[w];
		int y = j + dy[w];
		if (!x || !y || x > N || y > M || belong[x][y]) continue;
		if (height[i][j] == height[x][y]) floodfill(x,y);
	}
}

void Merge(int x,int y,int H)
{
	int fx = getfather(x);
	int fy = getfather(y);
	if (fx != fy)
	{
		if (top[fx] == top[fy]) f[fy] = fx,cnt[fx] += cnt[fy];
		else
		{
			if (top[fx] < top[fy]) swap(fx,fy);
			f[fy] = fx;
			fo(i,1,cnt[fy]) ans[++numc] = PI(top[fy],H);
		}
	}
}

void Initialize()
{
	scanf("%d%d",&N,&M);
	fo(i,1,N) fo(j,1,M) scanf("%d",&height[i][j]);
	fo(i,1,N) fo(j,1,M) 
		if (!belong[i][j])
		{
			++ col, floodfill(i,j);
			h[col] = height[i][j];
		}
	fo(i,1,col) peak[i] = 1,f[i] = pos[i] = i;
	fo(i,1,N) fo(j,1,M)
		fo(k,0,7)
		{
			int x = i + dx[k];
			int y = j + dy[k];
			if (height[i][j] > height[x][y]) peak[belong[x][y]] = 0;
		}
	fo(i,1,col) if (peak[i]) top[i] = h[i], cnt[i] = 1;
}

void Work()
{
	sort(pos+1,pos+col+1,cmp);
	fo(item,1,col)
	{
		int x = pos[item];
		flag[x] = 1;
		for (VECPI::iterator k = s[x].begin();k != s[x].end();k ++)
		{
			int i = k->first;
			int j = k->second;
			fo(w,0,7)
			{
				int xi = i + dx[w];
				int yi = j + dy[w];
				if (belong[xi][yi] != x && flag[belong[xi][yi]]) Merge(belong[xi][yi],x,h[x]);
			}
		}
	}
	int F = getfather(col);
	fo(i,1,cnt[F]) ans[++numc] = PI(top[F],0);
	sort(ans+1,ans+numc+1,cmpPI);
	printf("%d\n",numc);
	fo(i,1,numc) printf("%d %d\n",ans[i].first,ans[i].second);
}

int main()
{
	Initialize();
	Work();
	return 0;
}
