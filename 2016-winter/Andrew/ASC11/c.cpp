#include <cstdio>
#include <cstring>
#include <algorithm>
#define abs(X) ((X)>0?(X):-(X))

using namespace std;
int n,Xn,Yn,Xp,Yp,X,Y;
long long sum,b;

int odd(int X)
{
	if (X >= 0) return (X+1)/2;
	else return X/2;
}

int even(int X)
{
	return X - odd(X);
}

void fun()
{
    sum += (long long)Xp*Yp - (long long)Xn*Yn;
    b += (long long)odd(Xp)*odd(Yp)+(long long)even(Xp)*even(Yp)-((long long)odd(Xn)*odd(Yn)+(long long)even(Xn)*even(Yn));

}

int main()
{
    while (scanf("%d",&n) != EOF)
    {
        sum = b = 0;
        scanf("%d%d",&X,&Y);
        Xp = X, Yp = Y;
        n --;
        while (n --)
        {
            scanf("%d%d",&Xn,&Yn);
            if (Yn == Yp) fun();
            Xp = Xn, Yp = Yn;
        }
        Xn = X, Yn = Y;
        if (Yn == Yp) fun();
		printf("%lld %lld\n",abs(b),abs(sum-b));
    }
    return 0;
}
