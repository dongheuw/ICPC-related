#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

typedef long long LL;

using namespace std;
int A,B,C,D;
double X1,X2,Y1,Y2;

int main()
{
	while (scanf("%d%d%d%d",&A,&B,&C,&D) != EOF)
	{
		X1 = 1.0;
		if ((LL)C*B < (LL)D*A)
		{
			X2 = sqrt(1.0*D/A)*X1;
			X2 = max(X1*C/A,X2);
			X2 = min(X1*D/B,X2);
		}
		else
		{
			X2 = sqrt(1.0*C/B)*X1;
			X2 = min(X1*C/A,X2);
			X2 = max(X1*D/B,X2);
		}
		Y1 = max(A/X1,C/X2);
		Y2 = max(B/X1,D/X2);
		printf("%.15f\n",(X1+X2)*(Y1+Y2));
		printf("%.15f %.15f %.15f %.15f\n",X1,X2,Y1,Y2);
	}
	return 0;
}
