#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

int T,n;

struct node
{
    int a,b;
    bool operator <(const node &s)const{return a > s.a;}
}A[100005];

int main()
{
    scanf("%d",&T);
    fo(cs,1,T)
    {
        scanf("%d",&n);
        fo(i,1,n) scanf("%d%d",&A[i].a,&A[i].b);
        sort(A+1,A+1+n);
        int ans = 0x7fffffff, B = 0;
        A[n+1].a = 0;
        fo(i,1,n+1) B = max(B,A[i-1].b), ans = min(ans,A[i].a+B);
        printf("Case %d: %d\n",cs,ans);
    }
    return 0;
}
