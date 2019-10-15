#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define eps 1e-8

using namespace std;

const int maxn = 50005;
const double pi = acos(-1);

int N,p;
double R,r,ans;

struct Point
{
	double x,y;
	Point(){}
	Point(double _x,double _y){x=_x,y=_y;}
}a[maxn],C;

template<class T> T sqr(T x){return x*x;}
double dis(Point a,Point b){return sqr(a.x-b.x)+sqr(a.y-b.y);}
double dist(Point a,Point b){return sqrt(dis(a,b));}

void Update(int i,int j,int k)
{
	double a1 = 2*(a[j].x-a[i].x), b1 = 2*(a[j].y-a[i].y);
	double c1 = -((a[i].x+a[j].x)*(a[j].x-a[i].x)+(a[i].y+a[j].y)*(a[j].y-a[i].y));
	double a2 = 2*(a[k].x-a[i].x), b2 = 2*(a[k].y-a[i].y);
	double c2 = -((a[i].x+a[k].x)*(a[k].x-a[i].x)+(a[i].y+a[k].y)*(a[k].y-a[i].y));
	double s = a1*b2-a2*b1;
	if (fabs(s) > eps) C = Point((b1*c2-b2*c1)/s,(a2*c1-a1*c2)/s);
}

int main()
{
	freopen("amplifier.in","r",stdin);
	freopen("amplifier.out","w",stdout);
	scanf("%d",&N);
	fo(i,1,N) scanf("%lf%lf",&a[i].x,&a[i].y);
	scanf("%lf%d",&r,&p);
	r = r*pi/180;
	fo(i,1,N)
	{
		double x = a[i].x, y = a[i].y;
		a[i].x = (x*cos(r)+y*sin(r))/p;
		a[i].y = y*cos(r)-x*sin(r);
	}
	random_shuffle(a+1,a+1+N);
	if (N == 1) printf("0.000\n");
	else
	{
		C = Point((a[1].x+a[2].x)/2,(a[1].y+a[2].y)/2);
		R = dis(C,a[1]);
		fo(i,3,N)
		{
			if (dis(C,a[i]) < R+eps) continue;
			C = Point((a[1].x+a[i].x)/2,(a[1].y+a[i].y)/2);
			R = dis(C,a[1]);
			fo(j,2,i-1)
			{
				if (dis(C,a[j]) < R+eps) continue;
				C = Point((a[i].x+a[j].x)/2,(a[i].y+a[j].y)/2);
				R = dis(C,a[i]);
				fo(k,1,j-1)
				{
					if (dis(C,a[k]) < R+eps) continue;
					Update(i,j,k);
					R = dis(C,a[i]);
				}
			}
		}
		printf("%.3f\n",sqrt(R));
	}
	return 0;
}
