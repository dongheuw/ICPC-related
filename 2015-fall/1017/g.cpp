#include <iostream>

using namespace std;

long long n,f[100005];

long long dfs(long long n)
{
    if(n < 12) return n;
    if(n <= 100000)
    {
        if (f[n]) return f[n];
        f[n] = dfs(n/2) + dfs(n/3) + dfs(n/4);
        return f[n];
    }
    return (dfs(n/2) + dfs(n/3) + dfs(n/4));
}

int main()
{
    while (cin >> n) cout << dfs(n) << endl;
    return 0;
}
