#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
#define eps (1e-6)
int dblcmp(double a)
{
    if(fabs(a)<eps) return 0;
    return a>0?1:-1;
}
struct Point
{
    double x,y;
    Point(){}
    Point(double a,double b){x=a;y=b;}
};
struct Line
{
    Point x,y;
    Line(){}
    Line(Point a,Point b){x=a;y=b;}
}data[2000];
double dot(double x1,double y1,double x2,double y2)
{
    return x1*x2+y1*y2;
}
double dotdet(Point a,Point b,Point c)
{
    return dot(b.x-a.x,b.y-a.y,c.x-a.x,c.y-a.y);
}
int betweenCmp(Point a,Point b,Point c)
{
    return dblcmp(dotdet(a,b,c));
}
double det(double x1,double y1,double x2,double y2)
{
    return x1*y2-x2*y1;
}
double cross(Point a,Point b,Point c)
{
    return det(b.x-a.x,b.y-a.y,c.x-a.x,c.y-a.y);
}
int segCross(Point a,Point b,Point c,Point d,Point &p)
{
    double s1,s2,s3,s4;
    int d1,d2,d3,d4;
    d1=dblcmp(s1=cross(a,b,c));
    d2=dblcmp(s2=cross(a,b,d));
    d3=dblcmp(s3=cross(c,d,a));
    d4=dblcmp(s4=cross(c,d,b));
    if((d1^d2)==-2&&(d3^d4)==-2)
    {
        p.x=(c.x*s2-d.x*s1)/(s2-s1);
        p.y=(c.y*s2-d.y*s1)/(s2-s1);
        return 1;
    }
    if(d1==0&&betweenCmp(c,a,b)<=0||
        d2==0&&betweenCmp(d,a,b)<=0||
        d3==0&&betweenCmp(a,c,d)<=0||
        d4==0&&betweenCmp(b,c,d)<=0)
        return 2;
    return 0;
}
bool judge(Point a,Point b,Line line,Point &p)
{
    Point tmp;
    tmp.x=b.x-a.x;    tmp.y=b.y-a.y;
    tmp.x=tmp.x*10000+a.x;
    tmp.y=tmp.y*10000+a.y;
    return segCross(a,tmp,line.x,line.y,p);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        Point o;
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            double a,b,c,d;
            scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
            data[i]=Line(Point(a,b),Point(c,d));
        }
        scanf("%lf%lf",&o.x,&o.y);
        int res=0;
        for(int i=0;i<n;i++)
        {
            Point p;
            int cnt1=0,cnt2=0;
            for(int j=0;j<n;j++)
            {
                if(judge(o,data[i].x,data[j],p)) cnt1++;
                if(judge(o,data[i].y,data[j],p)) cnt2++;
            }
            res=max(res,max(cnt1,cnt2));
        }
        printf("%d\n",res);
    }
    return 0;
}
