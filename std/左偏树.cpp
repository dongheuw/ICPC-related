#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;
typedef long long LL;

const int maxn = 100005;
int N,M,n,B[maxn],C[maxn],L[maxn];
int tot,a[maxn],b[maxn<<1],c[maxn<<1],f[maxn];

struct Node
{
	int l,r,dis,key,size;
	LL sum;
	Node(){}
	Node(int _key){sum = key = _key;size = 1;dis = l = r = 0;}
}t[maxn];

void Add(int x,int y)
{
	tot ++;
	b[tot] = y;
	c[tot] = a[x];
	a[x] = tot;
}

int Merge(int a,int b)
{
	if (!a) return b;
	if (!b) return a;
	if (t[a].key < t[b].key) swap(a,b);
	t[a].r = Merge(t[a].r,b);
	if (t[t[a].l].dis < t[t[a].r].dis) swap(t[a].l,t[a].r);
	t[a].dis = t[t[a].r].dis + 1;
	t[a].size = t[t[a].l].size + t[t[a].r].size + 1;
	t[a].sum = t[t[a].l].sum + t[t[a].r].sum + t[a].key;
	return a;
}

void Work()
{
	static int q[maxn];
	int l = 0, r = 1;
	q[1] = 1;
	while (l < r)
	{
		int x = q[++l];
		for (int i = a[x];i;i = c[i]) q[++r] = b[i];
	}
	LL ans = 0;
	for (;r;r --)
	{
		int x = q[r];
		t[++n] = Node(C[x]);
		f[x] = n;
		for (int i = a[x];i;i = c[i]) f[x] = Merge(f[x],f[b[i]]);
		while (t[f[x]].sum > M) f[x] = Merge(t[f[x]].l,t[f[x]].r);
		ans = max(ans,(LL)t[f[x]].size*L[x]);
	}
	printf("%lld\n",ans);
}

void Initialize()
{
	scanf("%d%d",&N,&M);
	fo(i,1,N)
	{
		scanf("%d%d%d",&B[i],&C[i],&L[i]);
		if (B[i]) Add(B[i],i);
	}
	t[0].dis = -1;
}

int main()
{
	Initialize();
	Work();
	return 0;
}
