#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 100005;

int ansid,split;
long long ans;

struct KD_Node
{
	int x[2],id;
	bool operator < (const KD_Node &b)
	{
		fo(i,0,1)
			if (x[i] != b.x[i]) return x[i] < b.x[i];
		return 0;
	}
}A[maxn],T[maxn],dest;

bool cmp(const KD_Node &a,const KD_Node &b)
{
	return a.x[split] < b.x[split];
}

void Build(int l,int r,int d)
{
	if (l >= r) return;
	int mid = (l + r) >> 1;
	split = d & 1;
	nth_element(T+l,T+mid,T+r+1,cmp);
	Build(l,mid-1,d+1);
	Build(mid+1,r,d+1);
}

void Query(int l,int r,int d)
{
	if (l > r) return;
	int mid = (l + r) >> 1;
	long long dist = 0;
	fo(i,0,1) dist += (long long)(T[mid].x[i]-dest.x[i])*(T[mid].x[i]-dest.x[i]);
	if (dist && (dist < ans || (dist == ans && T[mid] < A[ansid])))
	{
		ans = dist;
		ansid = T[mid].id;
	}
	split = d & 1;
	long long rad = (long long)(dest.x[split]-T[mid].x[split])*(dest.x[split]-T[mid].x[split]);
	if (dest.x[split] < T[mid].x[split])
	{
		Query(l,mid-1,d+1);
		if (ans >= rad) Query(mid+1,r,d+1);
	} else
	{
		Query(mid+1,r,d+1);
		if (ans >= rad) Query(l,mid-1,d+1);
	}
}

int father[maxn];
int Get(int x)
{
	if (x == father[x]) return x;
	father[x] = Get(father[x]);
	return father[x];
}

int t,n,q;
int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d",&t);
	for (int cas = 1;cas <= t;cas ++)
	{
		printf("Case #%d:\n",cas);
		scanf("%d%d",&n,&q);
		fo(i,1,n)
		{
			scanf("%d%d",A[i].x,A[i].x+1);
			A[i].id = i;
			T[i] = A[i];
		}
		Build(1,n,0);
		fo(i,1,n) father[i] = i;
		fo(i,1,n)
		{
			dest = A[i];
			ans = 1ll << 62;
			Query(1,n,0);
			int u = Get(i), v = Get(ansid);
			father[u] = v;
		}
		fo(i,1,q)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			puts(Get(u)==Get(v)?"YES":"NO");
		}
	}
	return 0;
}
