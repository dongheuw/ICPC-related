#include <iostream>

using namespace std;

long long n,a[100005];

long long dp(long long n)
{
    if(n < 12) return n;
    if(n < 100000)
    {
        if (a[n]) return a[n];
        a[n] = dp(n/2)+dp(n/3)+dp(n/4);
        return a[n];
    }
    return (dp(n/2)+dp(n/3)+dp(n/4));
}

int main()
{
    while (cin>>n) cout<<dp(n)<<endl;
    return 0;
}
