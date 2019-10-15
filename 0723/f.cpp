#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 4000005;
int Max,Min,Sum,r,c,m,tot,root[maxn];

struct Node
{
	int x,sum,mx,mn,add,cov,ls,rs;
	Node(){sum = mx = mn = add = cov = ls = rs = 0;}
}t[maxn];

void Build(int &z,int l,int r)
{
	if (!z) z = ++ tot;
	if (l == r) return;
	int mid = (l + r) / 2;
	Build(t[z].ls,l,mid);
	Build(t[z].rs,mid+1,r);
}

void Reset(int r,int c)
{
	fo(i,1,tot) root[i] = 0, t[i] = Node();
	tot = 0;
	fo(i,1,r) Build(root[i],1,c);
}

void Setcov(int z,int l,int r,int cov)
{
	t[z].cov = cov;
	t[z].sum = cov * (r-l+1);
	t[z].mx = t[z].mn = cov;
	t[z].add = 0;
}

void Setadd(int z,int l,int r,int add)
{
	if (t[z].cov != 0)
	{
		t[z].cov += add;
		t[z].sum = t[z].cov * (r-l+1);
		t[z].mx = t[z].mn = t[z].cov;
	} else
	{
		t[z].add += add;
		t[z].sum += add * (r-l+1);
		t[z].mx += add;
		t[z].mn += add;
	}
}

void Pushdown(int z,int l,int r)
{
	int ls = t[z].ls, rs = t[z].rs;
	int mid = (l + r) / 2;
	if (t[z].cov != 0)
	{
		Setcov(ls,l,mid,t[z].cov);
		Setcov(rs,mid+1,r,t[z].cov);
		t[z].cov = 0;
	}
	if (t[z].add != 0)
	{
		Setadd(ls,l,mid,t[z].add);
		Setadd(rs,mid+1,r,t[z].add);
		t[z].add = 0;
	}
}

void Pushup(int z)
{
	int ls = t[z].ls, rs = t[z].rs;
	t[z].sum = t[ls].sum + t[rs].sum;
	t[z].mx = max(t[ls].mx,t[rs].mx);
	t[z].mn = min(t[ls].mn,t[rs].mn);
}

void Add(int z,int l,int r,int x,int y,int add)
{
	if (x <= l && r <= y) Setadd(z,l,r,add);
	else
	{
		Pushdown(z,l,r);
		int mid = (l + r) / 2;
		if (x <= mid) Add(t[z].ls,l,mid,x,y,add);
		if (y >= mid+1) Add(t[z].rs,mid+1,r,x,y,add);
		Pushup(z);
	}

}

void Cover(int z,int l,int r,int x,int y,int cov)
{
	if (x <= l && r <= y) Setcov(z,l,r,cov);
	else
	{
		Pushdown(z,l,r);
		int mid = (l + r) / 2;
		if (x <= mid) Cover(t[z].ls,l,mid,x,y,cov);
		if (y >= mid+1) Cover(t[z].rs,mid+1,r,x,y,cov);
		Pushup(z);
	}
}

void Query(int z,int l,int r,int x,int y)
{
	if (x <= l && r <= y)
	{
		Sum += t[z].sum;
		Max = max(Max,t[z].mx);
		Min = min(Min,t[z].mn);
	}
	else
	{
		Pushdown(z,l,r);
		int mid = (l + r) / 2;
		if (x <= mid) Query(t[z].ls,l,mid,x,y);
		if (y >= mid+1) Query(t[z].rs,mid+1,r,x,y);
	}
}

int main()
{
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);
	while (scanf("%d%d%d",&r,&c,&m) == 3)
	{
		 Reset(r,c);
		 while (m --)
		 {
		 	int sig,x1,y1,x2,y2,v;
		 	scanf("%d",&sig);
		 	if (sig == 1)
		 	{
		 		scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&v);
		 		fo(i,x1,x2) Add(root[i],1,c,y1,y2,v);
		 	} else
		 	if (sig == 2)
		 	{
		 		scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&v);
		 		fo(i,x1,x2) Cover(root[i],1,c,y1,y2,v);
		 	} else
		 	{
		 		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		 		Max = (int)-1e9; Min = (int)1e9; Sum = 0;
		 		fo(i,x1,x2) Query(root[i],1,c,y1,y2);
		 		printf("%d %d %d\n",Sum,Min,Max);
		 	}
		 }
	}
	return 0;
}
