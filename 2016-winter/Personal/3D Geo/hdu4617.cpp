#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const double inf = 1e18;

int T,n;

struct C
{
    double x,y,z;
    double a_x,a_y,a_z;
    double b_x,b_y,b_z;
    double n_x,n_y,n_z;
    double r;
}Cir[40];
 
double norm_x,norm_y,norm_z,AB_x,AB_y,AB_z;

double getDist(C A,C B)
{
    double len_norm,len_she;
    norm_x=A.n_y*B.n_z-A.n_z*B.n_y;
    norm_y=-A.n_x*B.n_z+A.n_z*B.n_x;
    norm_z=A.n_x*B.n_y-A.n_y*B.n_x;
    len_norm=sqrt(norm_x*norm_x+norm_y*norm_y+norm_z*norm_z);

    AB_x=A.x-B.x;
    AB_y=A.y-B.y;
    AB_z=A.z-B.z;
    len_she=fabs(AB_x*norm_x+AB_y*norm_y+AB_z*norm_z);
    return len_she/len_norm;
}

int main()
{
    for (scanf("%d",&T);T;T --)
    {
        scanf("%d",&n);
        for(int i = 0;i < n;i ++)
        {
            scanf("%lf%lf%lf",&Cir[i].x,&Cir[i].y,&Cir[i].z);
            scanf("%lf%lf%lf",&Cir[i].a_x,&Cir[i].a_y,&Cir[i].a_z);
            scanf("%lf%lf%lf",&Cir[i].b_x,&Cir[i].b_y,&Cir[i].b_z);
            Cir[i].n_x=(Cir[i].a_y-Cir[i].y)*(Cir[i].b_z-Cir[i].z)-(Cir[i].a_z-Cir[i].z)*(Cir[i].b_y-Cir[i].y);
            Cir[i].n_y=-(Cir[i].a_x-Cir[i].x)*(Cir[i].b_z-Cir[i].z)+(Cir[i].a_z-Cir[i].z)*(Cir[i].b_x-Cir[i].x);
            Cir[i].n_z=(Cir[i].a_x-Cir[i].x)*(Cir[i].b_y-Cir[i].y)-(Cir[i].a_y-Cir[i].y)*(Cir[i].b_x-Cir[i].x);
            Cir[i].r=sqrt((Cir[i].x-Cir[i].a_x)*(Cir[i].x-Cir[i].a_x)+(Cir[i].y-Cir[i].a_y)*(Cir[i].y-Cir[i].a_y)+(Cir[i].z-Cir[i].a_z)*(Cir[i].z-Cir[i].a_z));
        }
        bool flag = 1;
        double dist,ans = inf;
        for(int i = 0;i < n-1 && flag;i ++)
            for(int j = i+1;j < n;j ++)
            {
                dist=getDist(Cir[i],Cir[j]);
                ans=min(dist-(Cir[i].r+Cir[j].r),ans);
                if(ans <= 0)
                {
                    flag = 0;
                    break;
                }
            }
        if (flag) printf("%.2lf\n",ans);
        else puts("Lucky");
    }
    return 0;
}
