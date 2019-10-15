#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <cmath>
#include <iostream>
#include <iomanip>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

struct point
{
	long double x, y, z;
	point():x(0.0),y(0.0),z(0.0){}
	point(long double X,long double Y,long double Z):x(X),y(Y),z(Z){}
};

int T,cs,n,w,q;
map<string,int> id;
string planet[65];
point p[65];
long double D[65][65];

long double Dist(point &p1, point &p2)
{
	return sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y)+(p2.z-p1.z)*(p2.z-p1.z));
}

int main()
{
	freopen("l.in","r",stdin);
	freopen("l.out","w",stdout);
	for (scanf("%d",&T);T;T --)
	{
		scanf("%d",&n);
		id.clear();
		fo(i,0,n-1)
		{
			cin >> planet[i] >> p[i].x >> p[i].y >> p[i].z;
			id[planet[i]] = i;
		}
		fo(i,0,n-1) fo(j,0,n-1) D[i][j] = -1.0;
		scanf("%d",&w);
		for (int i = 0; i<w; i++)
		{
			string x,y;
			cin >> x >> y;
			D[id[x]][id[y]] = 0.0;
		}
		fo(i,0,n-1)
			fo(j,0,n-1)
				if (D[i][j] < 0.0) D[i][j] = Dist(p[i],p[j]);
		fo(k,0,n-1)
			fo(i,0,n-1)
				fo(j,0,n-1)
					D[i][j] = min(D[i][j],D[i][k]+D[k][j]);
		printf("Case %d:\n",++cs);
		for (scanf("%d",&q);q;q --)
		{
			string x,y;
			cin >> x >> y;
			cout << "The distance from " << x << " to " << y << " is " << fixed << setprecision(0) << round(D[id[x]][id[y]]) << " parsecs." << endl;
		}
	}
	return 0;
}
