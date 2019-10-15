/*
数据   by 80中集训
【题目大意】
为了写论文，Alex经常要整理大量的数据。 这一次，Alex面临一个严峻的考验：他需要实现一个数据结构来维护一个点集。 

现在，二维平面上有N个点。Alex 需要实现以下三种操作：
1. 在点集里添加一个点；

2. 给出一个点，查询它到点集里所有点的曼哈顿距离的最小值；

3. 给出一个点，查询它到点集里所有点的曼哈顿距离的最大值。 

两个点的曼哈顿距离定义为它们的横坐标差的绝对值与纵坐标差的绝对值的和。这么困难的问题，Alex当然不会做，只好再次请你帮忙了。

【题解】
这题的最大值是比较好做的，维护已经插入过的点的四种状态的最小值。
即x+y,x-y,-x+y,-x-y，求答案时用询问的点对应的状态减去出现过的最小值，再取个max即可。
（参见最大曼哈顿距离http://blog.csdn.net/hedongnike/article/details/20649231）

最小值的维护：
这就用到CDQ分治了。
我们把所有操作和询问读进来，原本的点也当作插入操作。
然后我们得到了一个按照操作时间顺序的序列，有插入操作和询问操作。
注意到所有的询问操作只会被它前面的插入操作影响，我们从这里入手。
假设当前要处理的操作序列为[l,r]。
我们先二分出中间点mid。

先递归进去子问题[l,mid],[mid+1,r]

然后我们处理前半部分插入对后半部分询问的影响。
我们先标记前半部分的询问和后半部分的询问，然后把它们按x坐标排序。
然后便按x坐标顺序小到大做。
按照离散化后的y坐标建立两个树状数组，维护做到当前询问之前，插入的某个状态的最小值。
[设当前询问的点的坐标为(x0,y0)，我们分别考虑之前插入的点的y坐标大于y0的和小于y0的（计算曼哈顿距离的方式不同）]
（此处较难表达，请看代码或画图）
遇到插入的操作则插入相应的状态值到相应的树状数组，遇到询问则更新该询问的答案。

最后还要反过来按x坐标从大到小做，同样要用树状数组维护。
状态为（x+y,x-y,-x+y,-x-y），即为询问点的四个方向上计算曼哈顿距离所需状态。
*/

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
