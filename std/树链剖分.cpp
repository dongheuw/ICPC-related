#include<map>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 100005;
const int rge = 2000005;
int N,Q,cnt,node,tot;
int W[maxn],C[maxn],a[maxn],b[maxn*2],c[maxn*2];
int size[maxn],depth[maxn],father[maxn][18];
int range[maxn][2],r[maxn][2],belong[maxn];
int left[rge],right[rge],next[maxn];
map<int,int> root[maxn];

struct NODE
{
	int sum,v;
	NODE(){}
	NODE(int _sum,int _v){sum = _sum,v = _v;}
}tree[rge];

void Insert(int x,int y)
{
	tot ++;
	b[tot] = y;
	c[tot] = a[x];
	a[x] = tot;
}

void Predfs(int x)
{
	depth[x] = depth[father[x][0]] + 1;
	size[x] = 1;
	for (int i = a[x];i;i = c[i])
		if (b[i] != father[x][0])
		{
			father[b[i]][0] = x;
			Predfs(b[i]);
			size[x] += size[b[i]];
		}
}

void Update(int x)
{
	tree[x].sum = tree[left[x]].sum + tree[right[x]].sum;
	tree[x].v = max(tree[left[x]].v,tree[right[x]].v);
}

void Insert(int &x,int l,int r,int p,int v)
{
	if (!x) x = ++ node;
	if (l == r)
	{
		tree[x] = NODE(v,v);
		return;
	}
	int mid = (l + r) >> 1;
	if (p <= mid) Insert(left[x],l,mid,p,v);
	else Insert(right[x],mid+1,r,p,v);
	Update(x);
}

void Divide(int x)
{
	belong[x] = cnt;
	if (depth[x] < range[cnt][0])
	{
		range[cnt][0] = min(range[cnt][0],depth[x]);
		r[cnt][0] = x;
	}
	if (depth[x] > range[cnt][1])
	{
		range[cnt][1] = max(range[cnt][1],depth[x]);
		r[cnt][1] = x;
	}
	next[x] = 0;
	for (int i = a[x];i;i = c[i])
		if (b[i] != father[x][0])
			if (size[b[i]] > size[next[x]]) next[x] = b[i];
	if (next[x]) Divide(next[x]);
	for (int i = a[x];i;i = c[i])
		if (b[i] != father[x][0] && b[i] != next[x])
			++ cnt, Divide(b[i]);
}

int q[maxn];
void InsertToSeg()
{
	int l = 0, r = 1;
	q[1] = 1;
	while (l < r)
	{
		int x = q[++l];
		if (root[belong[x]].find(C[x]) == root[belong[x]].end()) root[belong[x]].insert(make_pair(C[x],++node));
		Insert(root[belong[x]][C[x]],range[belong[x]][0],range[belong[x]][1],depth[x],W[x]);
		for (int i = a[x];i;i = c[i])
			if (b[i] != father[x][0]) q[++r] = b[i];
	}
}

void DealFather()
{
	fo(j,1,17)
		fo(i,1,N)
			if (father[i][j-1])
				father[i][j] = father[father[i][j-1]][j-1];
}

int LCA(int x,int y)
{
	if (x == y) return x;
	if (depth[x] < depth[y]) swap(x,y);
	for (int j = 17;j >= 0;j --)
		if (depth[father[x][j]] >= depth[y]) x = father[x][j];
	if (x == y) return x;
	for (int j = 17;j >= 0;j --)
		if (father[x][j] != father[y][j]) x = father[x][j], y = father[y][j];
	return father[x][0];
}

void SubDivide()
{
	depth[1] = 1;
	Predfs(1);
	DealFather();
	cnt = 1;
	fo(i,1,N) range[i][0] = 0x7fffffff;
	Divide(1);
	InsertToSeg();
}

void Initialize()
{
	scanf("%d%d",&N,&Q);
	fo(i,1,N) scanf("%d%d",&W[i],&C[i]);
	fo(i,1,N-1)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		Insert(x,y);
		Insert(y,x);
	}
	SubDivide();
}

void Modify(int x,int l,int r,int p,int v)
{
	if (l == r)
	{
		tree[x] = NODE(v,v);
		return;
	}
	int mid = (l + r) >> 1;
	if (p <= mid) Modify(left[x],l,mid,p,v);
	else Modify(right[x],mid+1,r,p,v);
	Update(x);
}

int Querysum(int z,int l,int r,int x,int y)
{
	if (x <= l && r <= y) return tree[z].sum;
	int mid = (l + r) >> 1;
	int ret = 0;
	if (x <= mid) ret += Querysum(left[z],l,mid,x,y);
	if (y > mid) ret += Querysum(right[z],mid+1,r,x,y);
	return ret;
}

int Querymax(int z,int l,int r,int x,int y)
{
	if (x <= l && r <= y) return tree[z].v;
	int mid = (l + r) >> 1;
	int ret = 0;
	if (x <= mid) ret = max(ret,Querymax(left[z],l,mid,x,y));
	if (y > mid) ret = max(ret,Querymax(right[z],mid+1,r,x,y));
	return ret; 
}

int QuerySUM(int x,int y,int col)
{
	int lca = LCA(x,y);
	int ret = 0;
	while (belong[x] != belong[lca])
	{
		int cur = belong[x];
		if (root[cur].find(col) != root[cur].end())
			ret += Querysum(root[cur][col],range[cur][0],range[cur][1],range[cur][0],depth[x]);
		x = father[r[cur][0]][0];
	}
	while (belong[y] != belong[lca])
	{
		int cur = belong[y];
		if (root[cur].find(col) != root[cur].end())
			ret += Querysum(root[cur][col],range[cur][0],range[cur][1],range[cur][0],depth[y]);
		y = father[r[cur][0]][0];
	}
	int cur = belong[x];
	if (root[cur].find(col) != root[cur].end())
			ret += Querysum(root[cur][col],range[cur][0],range[cur][1],min(depth[x],depth[y]),max(depth[x],depth[y]));
	return ret;
}

int QueryMAX(int x,int y,int col)
{
	int lca = LCA(x,y);
	int ret = 0;
	while (belong[x] != belong[lca])
	{
		int cur = belong[x];
		if (root[cur].find(col) != root[cur].end())
			ret = max(ret,Querymax(root[cur][col],range[cur][0],range[cur][1],range[cur][0],depth[x]));
		x = father[r[cur][0]][0];
	}
	while (belong[y] != belong[lca])
	{
		int cur = belong[y];
		if (root[cur].find(col) != root[cur].end())
			ret = max(ret,Querymax(root[cur][col],range[cur][0],range[cur][1],range[cur][0],depth[y]));
		y = father[r[cur][0]][0];
	}
	int cur = belong[x];
	if (root[cur].find(col) != root[cur].end())
			ret = max(ret,Querymax(root[cur][col],range[cur][0],range[cur][1],min(depth[x],depth[y]),max(depth[x],depth[y])));
	return ret;
}

void Work()
{
	while (Q --)
	{
		char op[5];
		int x,y;
		scanf("%s",op); scanf("%d%d",&x,&y);
		if (op[0] == 'C')
		{
			if (op[1] == 'C') 
			{
				int cur = belong[x];
				Modify(root[cur][C[x]],range[cur][0],range[cur][1],depth[x],0);
				C[x] = y;
				if (root[cur].find(C[x]) == root[cur].end()) root[cur].insert(make_pair(C[x],++node));
				Insert(root[cur][C[x]],range[cur][0],range[cur][1],depth[x],W[x]);
			}
			else
			{
				int cur = belong[x];
				W[x] = y;
				Modify(root[cur][C[x]],range[cur][0],range[cur][1],depth[x],y);
			}
		} else
		{
			if (op[1] == 'S') printf("%d\n",QuerySUM(x,y,C[y]));
			else printf("%d\n",QueryMAX(x,y,C[y]));
		}
	}
}

int main()
{
	freopen("travel.in","r",stdin);
	freopen("travel.out","w",stdout);
	Initialize();
	Work();
	return 0;
}
