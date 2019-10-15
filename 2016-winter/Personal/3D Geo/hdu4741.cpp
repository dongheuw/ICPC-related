#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int T;

struct Point
{
    double x,y,z;
    Point(double _x = 0,double _y = 0,double _z = 0)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    Point operator +(const Point &b)const
    {
        return Point(x + b.x, y + b.y,z + b.z);
    }
    Point operator -(const Point &b)const
    {
        return Point(x - b.x, y - b.y,z - b.z);
    }
    Point operator /(double k)
    {
        return Point(x/k,y/k,z/k);
    }
    Point operator *(double k)
    {
        return Point(x*k,y*k,z*k);
    }
    double operator *(const Point &b)const
    {
        return x*b.x + y*b.y + z*b.z;
    }
    Point operator ^(const Point &b)const
    {
        return Point(y*b.z - z *b.y,z*b.x - x*b.z, x*b.y - y * b.x);
    }
    void read()
    {
        scanf("%lf%lf%lf",&x,&y,&z);
    }
    void print()
    {
        printf("%.6lf %.6lf %.6lf",x,y,z);
    }
}A,B,C,D,mid1,mid2;

double norm(Point a)
{
    return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
}

int main()
{
    for (scanf("%d",&T);T;T--)
    {
        A.read(); B.read(); C.read(); D.read();
        Point p1 = (B-A);
        Point p2 = (D-C);
        Point p = p1^p2;
        double dd = (p*(A-C))/norm(p);
        dd = fabs(dd);
        printf("%.6lf\n",dd);

        double t1 = ( (C-A)^p2 )*(p1^p2);
        t1 /= norm(p1^p2)*norm(p1^p2);
        double t2 =  ( (C-A)^p1 )*(p1^p2);
        t2 /= norm(p1^p2)*norm(p1^p2);
        mid1 = A + (p1 * t1);
        mid2 = C + (p2 * t2);
        mid1.print(); printf(" ");
        mid2.print(); printf("\n");
    }
    return 0;
}
