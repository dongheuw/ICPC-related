#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

inline void READ(int &x)
{
	static char c;
	x=0;
	do c=getchar(); while (c<'0' || c>'9');
	do x=x*10+c-48, c=getchar(); while (c>='0' && c<='9');
}

const int maxn=200005;

typedef pair<int,int> PI;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)

int N, M, A[maxn], f[maxn<<1], ans[maxn];
vector<PI> Q[maxn];

#define pos(l,r) (((l)+(r))|((l)!=(r)))

void Ins(int l, int r, int q, int v)
{
	int mid((l+r)>>1), &now=f[pos(l,r)], &son1=f[pos(l,mid)], &son2=f[pos(mid+1,r)];
	if (l==r)
	{
		now=v;
		return;
	}
	if (q<=mid) Ins(l,mid,q,v);
	else Ins(mid+1,r,q,v);
	now=min(son1,son2);
}

int Find(int l, int r, int v)
{
	if (l==r) return l;
	int mid((l+r)>>1);
	return f[pos(l,mid)]>=v?Find(mid+1,r,v):Find(l,mid,v);
}

int main()
{
	READ(N), READ(M);
	for (int i=1;i<=N;i++) READ(A[i]);
	for (int i=1;i<=M;i++)
	{
		int l, r;
		READ(l), READ(r);
		Q[r].push_back(mkp(l,i));
	}
	for (int i=1;i<=N;i++)
	{
		if (A[i]<=N) Ins(0,N-1,A[i],i);
		for (vector<PI>::iterator j=Q[i].begin();j!=Q[i].end();j++)
			ans[j->se]=Find(0,N-1,j->fi);
	}
	for (int i=1;i<=M;i++) printf("%d\n",ans[i]);
	return 0;
}
