#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define fd(i,a,b) for (int i = a;i >= b;i --)

using namespace std;
typedef long long LL;

const int maxn = 201005;
const LL INF = (LL)1e11;
int N,Q;
LL ans[maxn];

struct OP
{
	int op,id,flag;
	LL x,y;
	OP(){}
	OP(int _op,LL _x,LL _y,int i){op=_op,x=_x,y=_y,id=i;}
}A[maxn];

void Initialize()
{
	scanf("%d",&N);
	fo(i,1,N)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		A[i] = OP(0,x,y,i);
	}
	scanf("%d",&Q);
	fo(i,1,Q)
	{
		int op,x,y;
		scanf("%d%d%d",&op,&x,&y);
		N ++;
		A[N] = OP(op,x,y,N);
	}
	fo(i,1,N) ans[i] = INF;
}

LL xy,x_y,_xy,_x_y;
inline void Update(LL x,LL y)
{
	xy = min(xy,x+y);
	x_y = min(x_y,x-y);
	_xy = min(_xy,-x+y);
	_x_y = min(_x_y,-x-y);
}

void Task_max()
{
	xy = INF, x_y = INF, _xy = INF, _x_y = INF;
	fo(i,1,N)
	{
		if (A[i].op == 0) Update(A[i].x,A[i].y);
		if (A[i].op == 2) 
		{
			ans[A[i].id] = max(A[i].x+A[i].y-xy,A[i].x-A[i].y-x_y);
			ans[A[i].id] = max(ans[A[i].id],max(-A[i].x+A[i].y-_xy,-A[i].x-A[i].y-_x_y));
		}
	}
}

inline bool cmpx(const OP &a,const OP &b)
{
	return a.x < b.x;
}

struct OPER
{
	int id;
	LL y;
	OPER(){}
	OPER(LL _y,int i){y=_y,id = i;}
}B[maxn];

int ord[maxn];
inline bool cmpy(const OPER &a,const OPER &b)
{
	return a.y < b.y;
}

int Discretize(int l,int r)
{
	sort(B+l,B+r+1,cmpy);
	int j = 0;
	fo(i,l,r)
	{
		if (i == 1 || B[i].y != B[i-1].y) j ++;
		ord[B[i].id] = j;
	}
	return j;
}

LL up[maxn],down[maxn];

inline int lowbit(int x){return x & (-x);}

void Ins_up(int x,LL v)
{
	while (x)
	{
		up[x] = max(up[x],v);
		x -= lowbit(x);
	}
}

LL Query_up(int x,int lim)
{
	LL ret = -INF;
	while (x <= lim)
	{
		ret = max(ret,up[x]);
		x += lowbit(x);
	}
	return ret;
}

void Ins_down(int x,LL v,int lim)
{
	while (x <= lim)
	{
		down[x] = max(down[x],v);
		x += lowbit(x);
	}
}

LL Query_down(int x)
{
	LL ret = -INF;
	while (x)
	{
		ret = max(ret,down[x]);
		x -= lowbit(x); 
	}
	return ret;
}

void Solve(int l,int r)
{
	if (l == r) return;
	int mid = (l+r) >> 1;
	Solve(l,mid);
	Solve(mid+1,r);
	// Prepare
	fo(i,l,r) A[i].flag = -1;
	fo(i,l,mid) if (A[i].op == 0) A[i].flag = 0;
	fo(i,mid+1,r) if (A[i].op == 1) A[i].flag = 1;
	sort(A+l,A+r+1,cmpx);
	int tot = 0;
	fo(i,l,r) 
		if (A[i].flag == 0 || A[i].flag == 1)
			B[++tot] = OPER(A[i].y,i);
	// Work
	int lim = Discretize(1,tot);
	fill(up+1,up+lim+1,-INF);
	fill(down+1,down+lim+1,-INF);
	fo(i,l,r)
		if (A[i].flag == 0)
		{
			Ins_up(ord[i],A[i].x-A[i].y);
			Ins_down(ord[i],A[i].x+A[i].y,lim);	
		} else
		if (A[i].flag == 1)
		{
			ans[A[i].id] = min(ans[A[i].id],A[i].x-A[i].y-Query_up(ord[i],lim));
			ans[A[i].id] = min(ans[A[i].id],A[i].x+A[i].y-Query_down(ord[i]));
		}
	fill(up+1,up+lim+1,-INF);
	fill(down+1,down+lim+1,-INF);
	fd(i,r,l)
		if (A[i].flag == 0)
		{
			Ins_up(ord[i],-A[i].x-A[i].y);
			Ins_down(ord[i],-A[i].x+A[i].y,lim);
		} else
		if (A[i].flag == 1)
		{
			ans[A[i].id] = min(ans[A[i].id],-A[i].x-A[i].y-Query_up(ord[i],lim));
			ans[A[i].id] = min(ans[A[i].id],-A[i].x+A[i].y-Query_down(ord[i]));
		}
}

void Task_min()
{
	Solve(1,N);
}

void Print()
{
	fo(i,1,N)
		if (ans[i] != INF) printf("%lld\n",ans[i]);
}

int main()
{
	Initialize();
	Task_max();
	Task_min();
	Print();
	return 0;
}
