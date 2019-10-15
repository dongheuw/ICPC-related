#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

typedef long long  LL;
using namespace std;

LL x,y,a,b,t;

struct node { LL x,y; };
vector<node> A;

bool cmp(const node &a,const node &b)
{
    return a.y > b.y;
}

int main()
{
    scanf("%lld",&x);
    for (LL i = 1;i <= 10000000LL || i*i*i <= x;i ++)
    {
        a = (i*i+i-(i+1)*i/2LL);
        b = (i*i+i-(i+1)*i*i/2LL-(i+1)*i+(i*(i+1)*(2*i+1)/6));
        y = x;
        t = (y-b)/a;
        if (i > t) continue;
        if (a*t + b == y)
            if (i == t)
            {
                node k;
                k.x = i, k.y = t;
                A.push_back(k);
            }
            else
            {
                node k;
                k.x = i, k.y = t;
                A.push_back(k);
                k.x = t, k.y = i;
                A.push_back(k);
            }
    }
    sort(A.begin(),A.end(),cmp);
    printf("%lu\n",A.size());
    for (unsigned i = 0;i < A.size();i ++) printf("%lld %lld\n",A[i].x,A[i].y);
}
