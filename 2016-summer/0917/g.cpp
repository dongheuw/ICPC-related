#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
using namespace std;

typedef long long ll;

const int maxn = 100005;

int T,n,m,a[maxn];
priority_queue<ll> Q;

bool Check(int k)
{
    while (!Q.empty()) Q.pop();
    ll s = 0, sum = 0;
    int tmp = n % (k-1);
    tmp = (tmp+k-3) % (k-1) + 2;
    a[0] = 1;
    fo(i,1,tmp) s += a[a[0]++];
    Q.push(-s);
    sum += s;
    ll front = s;
    for (int j = (n-tmp)/(k-1);j;j --)
    {
        s = 0;
        fo(i,1,k)
            if (a[0] <= n && a[a[0]] <= front) s += a[a[0]++];
            else
            {
                s += front;
                Q.pop();
                if (!Q.empty()) front = -Q.top();
                else front = 1 << 21;
            }
        sum += s;
        if (sum > m) return 0;
        Q.push(-s);
        if (s < front) front = s;
    }
    return 1;
}

int main()
{
    for (scanf("%d",&T);T;T --)
    {
        scanf("%d%d",&n,&m);
        fo(i,1,n) scanf("%d",&a[i]);
        sort(a+1,a+n+1);
        int L = 2, R = n;
        while (L <= R)
        {
            int mid = (L + R) >> 1;
            if (Check(mid)) R = mid - 1;
            else L = mid + 1;
        }
        printf("%d\n",L);
    }
    return 0;
}
