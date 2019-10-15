#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define sqr(x) ((x)*(x))
using namespace std;

const double PI = acos(-1.0);
const double eps = 1e-8;

double x,y,r,X1,Y1,X2,Y2,ans;

struct point
{
    double x,y;
    point(){}
    point(double _x,double _y){x = _x, y = _y;}
};
vector<point> V;

double tri(const point &u,const point &v)
{
    return u.x*v.y - u.y*v.x;
}

double arc(const point &u,const point &v)
{
    double t = atan2(v.y,v.x) - atan2(u.y,u.x);
    while (t > PI) t -= 2*PI;
    while (t < -PI) t += 2*PI;
    return sqr(r)*t;
}

void Calc(const point &u,const point &v,double r)
{
    double a = sqr(v.x - u.x) + sqr(v.y - u.y);
    double b = 2 * ((v.x - u.x) * u.x + (v.y - u.y) * u.y);
    double c = sqr(u.x) + sqr(u.y) - r * r;
    double d = sqr(b) - 4*a*c;
    V.push_back(u);
    if (d < 0)return;
    d = sqrt(d);
    double t1 = (-b+d)/(2*a);
    double t2 = (-b-d)/(2*a);
    if (t1 > t2) swap(t1,t2);
    if (t1 > eps && t1 < 1-eps) V.push_back(point(u.x+(v.x-u.x)*t1,u.y+(v.y-u.y)*t1));
    if (t2 > eps && t2 < 1-eps && t2 - t1 > eps) V.push_back(point(u.x+(v.x-u.x)*t2,u.y+(v.y-u.y)*t2));

}

int main()
{
    for (int t = 1;scanf("%lf%lf%lf",&x,&y,&r) != EOF;t ++)
    {
        if (t > 1) puts("");
        V.clear();
        scanf("%lf%lf%lf%lf",&X1,&Y1,&X2,&Y2);
        X1 -= x, Y1 -= y, X2 -= x, Y2 -= y;
        Calc(point(X1,Y1),point(X1,Y2),r);
        Calc(point(X1,Y2),point(X2,Y2),r);
        Calc(point(X2,Y2),point(X2,Y1),r);
        Calc(point(X2,Y1),point(X1,Y1),r);
        ans = 0;
        V.push_back(V[0]);
        for (unsigned i = 1;i < V.size();i++)
            if (sqr((V[i-1].x+V[i].x)/2) + sqr((V[i-1].y+V[i].y)/2) < sqr(r)) ans += tri(V[i-1],V[i]);
            else ans += arc(V[i-1],V[i]);
        printf("%.10lf\n",fabs(ans)*0.5);
    }
    return 0;
}
