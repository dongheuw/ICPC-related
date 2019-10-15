#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define sqr(x) ((x)*(x))

using namespace std;

const int inf = (int)1e9;
const double eps = 1e-6;
const int maxn = 65;
const int maxa = 200005;

int T,cas,N,xmin,xmax,ymin,ymax,ans[maxa][3],tot;
double standard;

struct point
{
	int x,y;
}p[maxn];

double Area(const point &st,const point &a,const point &b)
{
	int x1 = a.x - st.x;
    int y1 = a.y - st.y;
    int x2 = b.x - st.x;
    int y2 = b.y - st.y;
    return fabs(double(x1) * y2 - x2 * y1) * 0.5;
}

bool IsIn(int x,int y)
{
	double area = 0;
	point t;
	t.x = x, t.y = y;
	fo(i,1,N)
	{
		double tmp;
		if (i == N) tmp = Area(t,p[N],p[1]);
		else tmp = Area(t,p[i],p[i+1]);
		if (tmp < eps) return 0;
		area += tmp;
	}
	if (fabs(standard-area) > eps) return 0;
	return 1;
}

void Work()
{
	for (int j = ymax;j >= ymin;j --)
	{
		int l = -1, r = -1;
		fo(i,xmin,xmax)
			if (IsIn(i,j))
			{
				if (l == -1) l = i;
				r = i;
			}
		if (l != -1)
		{
			tot ++;
			ans[tot][0] = j;
			ans[tot][1] = l;
			ans[tot][2] = r;
		}
	}
}

void Print()
{
	printf("%d %d\n",cas,tot);
	fo(i,1,tot) printf("%d %d %d\n",ans[i][0],ans[i][1],ans[i][2]);
}


void Initialize()
{
	tot = 0;
	standard = 0;
	xmax = ymax = -inf;
	xmin = ymin = inf;
	scanf("%d%d",&cas,&N);
	fo(i,1,N)
	{
		scanf("%d%d",&p[i].x,&p[i].y);
		xmax = max(xmax,p[i].x);
		ymax = max(ymax,p[i].y);
		xmin = min(xmin,p[i].x);
		ymin = min(ymin,p[i].y);
	}
	fo(i,2,N-1) standard += Area(p[1],p[i],p[i+1]);
}

int main()
{
	freopen("h.in","r",stdin);
	freopen("h.out","w",stdout);
	for (scanf("%d",&T);T;T --)
	{
		Initialize();
		Work();
		Print();
	}
	return 0;
}
